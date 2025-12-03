# Script automático para configurar issue #772
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"
$issueNumber = 772

Write-Host "=== CONFIGURAÇÃO AUTOMÁTICA ISSUE #$issueNumber ===" -ForegroundColor Cyan
Write-Host ""

# Função auxiliar para executar query GraphQL
function Invoke-GraphQL {
    param([string]$Query)
    
    $tempFile = [System.IO.Path]::GetTempFileName()
    try {
        # Remove BOM e escreve sem quebras de linha extras
        $utf8NoBom = New-Object System.Text.UTF8Encoding $false
        [System.IO.File]::WriteAllText($tempFile, $Query, $utf8NoBom)
        $result = & $ghPath api graphql -F query=@$tempFile 2>&1
        return $result
    } finally {
        Remove-Item $tempFile -Force -ErrorAction SilentlyContinue
    }
}

# 1. Buscar node ID da issue
Write-Host "[1/4] Buscando issue..." -ForegroundColor Yellow
$issueQuery = "query { repository(owner: `"Stramp`", name: `"Lost-Mines-Phandelver`") { issue(number: $issueNumber) { id title url } } }"
$issueData = Invoke-GraphQL -Query $issueQuery

if ($LASTEXITCODE -ne 0) {
    Write-Host "  [ERRO] Não foi possível buscar issue" -ForegroundColor Red
    Write-Host "  Erro: $issueData" -ForegroundColor Red
    exit 1
}

$issueJson = $issueData | ConvertFrom-Json
$issueNodeId = $issueJson.data.repository.issue.id
$issueTitle = $issueJson.data.repository.issue.title
$issueUrl = $issueJson.data.repository.issue.url

Write-Host "  [OK] Issue encontrada: $issueTitle" -ForegroundColor Green
Write-Host "  URL: $issueUrl" -ForegroundColor Gray

# 2. Buscar projeto "Core Engineering"
Write-Host ""
Write-Host "[2/4] Buscando projeto..." -ForegroundColor Yellow

$projectQuery = "query { user(login: `"Stramp`") { projectV2(number: 25) { id title fields(first: 20) { nodes { ... on ProjectV2Field { id name } ... on ProjectV2SingleSelectField { id name options { id name } } } } } } }"
$projectData = Invoke-GraphQL -Query $projectQuery

if ($LASTEXITCODE -ne 0) {
    Write-Host "  [ERRO] Não foi possível buscar projeto" -ForegroundColor Red
    exit 1
}

$projectJson = $projectData | ConvertFrom-Json
$projectId = $projectJson.data.user.projectV2.id
$projectTitle = $projectJson.data.user.projectV2.title

Write-Host "  [OK] Projeto: $projectTitle" -ForegroundColor Green

# Buscar campo Status
$statusField = $projectJson.data.user.projectV2.fields.nodes | Where-Object { $_.name -eq "Status" } | Select-Object -First 1

if (-not $statusField) {
    Write-Host "  [AVISO] Campo 'Status' não encontrado" -ForegroundColor Yellow
    exit 1
}

# Buscar opção "In Progress"
$inProgressOption = $statusField.options | Where-Object {
    $_.name -match "In Progress|InProgress|in-progress|Doing|Em Progresso|Em Andamento"
} | Select-Object -First 1

if (-not $inProgressOption) {
    Write-Host "  [AVISO] Opção 'In Progress' não encontrada" -ForegroundColor Yellow
    Write-Host "  Opções disponíveis:" -ForegroundColor Gray
    $statusField.options | ForEach-Object { Write-Host "    - $($_.name)" -ForegroundColor Gray }
    exit 1
}

Write-Host "  [OK] Opção encontrada: $($inProgressOption.name)" -ForegroundColor Green

# 3. Adicionar issue ao projeto
Write-Host ""
Write-Host "[3/4] Adicionando issue ao projeto..." -ForegroundColor Yellow

$addMutation = "mutation { addProjectV2ItemById(input: { projectId: `"$projectId`" contentId: `"$issueNodeId`" }) { item { id } } }"
$addResult = Invoke-GraphQL -Query $addMutation

$itemId = $null

if ($LASTEXITCODE -eq 0) {
    $addJson = $addResult | ConvertFrom-Json
    if ($addJson.data.addProjectV2ItemById -and $addJson.data.addProjectV2ItemById.item) {
        $itemId = $addJson.data.addProjectV2ItemById.item.id
        Write-Host "  [OK] Issue adicionada ao projeto" -ForegroundColor Green
    } else {
        Write-Host "  [AVISO] Issue pode já estar no projeto" -ForegroundColor Yellow
        
        # Buscar item existente
        $findQuery = "query { user(login: `"Stramp`") { projectV2(number: 25) { items(first: 100) { nodes { id content { ... on Issue { number } } } } } } }"
        $findData = Invoke-GraphQL -Query $findQuery
        if ($LASTEXITCODE -eq 0) {
            $findJson = $findData | ConvertFrom-Json
            $foundItem = $findJson.data.user.projectV2.items.nodes | Where-Object { $_.content.number -eq $issueNumber } | Select-Object -First 1
            if ($foundItem) {
                $itemId = $foundItem.id
                Write-Host "  [OK] Item encontrado no projeto" -ForegroundColor Green
            }
        }
    }
} else {
    Write-Host "  [AVISO] Não foi possível adicionar: $addResult" -ForegroundColor Yellow
}

# 4. Mover para "In Progress"
if ($itemId -and $inProgressOption) {
    Write-Host ""
    Write-Host "[4/4] Movendo para '$($inProgressOption.name)'..." -ForegroundColor Yellow
    
    $updateMutation = "mutation { updateProjectV2ItemFieldValue(input: { projectId: `"$projectId`" itemId: `"$itemId`" fieldId: `"$($statusField.id)`" value: { singleSelectOptionId: `"$($inProgressOption.id)`" } }) { projectV2Item { id } } }"
    $updateResult = Invoke-GraphQL -Query $updateMutation
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "  [OK] Movido para '$($inProgressOption.name)'" -ForegroundColor Green
    } else {
        Write-Host "  [AVISO] Não foi possível mover: $updateResult" -ForegroundColor Yellow
    }
} else {
    Write-Host ""
    Write-Host "[4/4] Pulando movimento (item ou opção não encontrados)" -ForegroundColor Yellow
    if (-not $itemId) {
        Write-Host "  Item ID não encontrado" -ForegroundColor Red
    }
    if (-not $inProgressOption) {
        Write-Host "  Opção 'In Progress' não encontrada" -ForegroundColor Red
    }
}

Write-Host ""
Write-Host "=== CONCLUÍDO ===" -ForegroundColor Cyan
Write-Host "Issue #$issueNumber configurada" -ForegroundColor Green
Write-Host "URL: $issueUrl" -ForegroundColor Gray
