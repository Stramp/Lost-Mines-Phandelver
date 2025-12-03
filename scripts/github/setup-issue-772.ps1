# Script para configurar completamente a issue #772
# Encoding UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# ===== CONFIGURAÇÃO =====
$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"
$issueNumber = 772

Write-Host "=== CONFIGURANDO ISSUE #$issueNumber ===" -ForegroundColor Cyan
Write-Host ""

# 1. Adicionar ao board usando API
Write-Host "[1/3] Adicionando ao board..." -ForegroundColor Yellow

# Lista projetos do usuário
$projectsJson = & $ghPath api user/projects --jq '.[] | select(.state == "open") | {id: .id, name: .name}' 2>&1

if ($LASTEXITCODE -eq 0 -and $projectsJson) {
    $projects = $projectsJson | ConvertFrom-Json
    
    # Procura projeto "Core Engineering"
    $targetProject = $projects | Where-Object { $_.name -match "Core Engineering" } | Select-Object -First 1
    
    if (-not $targetProject) {
        # Usa o primeiro projeto aberto
        $targetProject = $projects | Select-Object -First 1
    }
    
    if ($targetProject) {
        Write-Host "  Projeto: $($targetProject.name)" -ForegroundColor Gray
        
        # Busca issue node ID
        $issueData = & $ghPath api "repos/$meuRepo/issues/$issueNumber" --jq '{id: .node_id, url: .url}' 2>&1
        
        if ($LASTEXITCODE -eq 0 -and $issueData) {
            $issueInfo = $issueData | ConvertFrom-Json
            
            # Adiciona ao projeto usando GraphQL API
            $projectId = $targetProject.id
            $itemId = $issueInfo.id
            
            $mutation = @"
mutation {
  addProjectV2ItemById(input: {
    projectId: "$projectId"
    contentId: "$itemId"
  }) {
    item {
      id
    }
  }
}
"@
            
            $mutationResult = $mutation | & $ghPath api graphql -f query="$mutation" 2>&1
            
            if ($LASTEXITCODE -eq 0) {
                Write-Host "  [OK] Issue adicionada ao projeto" -ForegroundColor Green
                
                # 2. Mover para "In Progress"
                Write-Host ""
                Write-Host "[2/3] Movendo para 'In Progress'..." -ForegroundColor Yellow
                
                # Busca colunas do projeto
                $columnsJson = & $ghPath api "projects/$($targetProject.id)/columns" --jq '.[] | {id: .id, name: .name}' 2>&1
                
                if ($LASTEXITCODE -eq 0 -and $columnsJson) {
                    $columns = $columnsJson | ConvertFrom-Json
                    $inProgressColumn = $columns | Where-Object {
                        $_.name -match "In Progress|InProgress|in-progress|Doing|Em Progresso|Em Andamento"
                    } | Select-Object -First 1
                    
                    if ($inProgressColumn) {
                        Write-Host "  Coluna: $($inProgressColumn.name)" -ForegroundColor Gray
                        
                        # Busca o item no projeto
                        $itemsJson = & $ghPath api "projects/columns/$($inProgressColumn.id)/cards" --jq '.[] | {id: .id, content_url: .content_url}' 2>&1
                        
                        if ($LASTEXITCODE -eq 0 -and $itemsJson) {
                            $items = $itemsJson | ConvertFrom-Json
                            $targetItem = $items | Where-Object { $_.content_url -match "issues/$issueNumber" } | Select-Object -First 1
                            
                            if ($targetItem) {
                                # Move para a coluna In Progress
                                $bodyJson = @{
                                    position = "top"
                                    column_id = $inProgressColumn.id
                                } | ConvertTo-Json -Compress
                                
                                $moveResult = & $ghPath api -X POST "projects/columns/cards/$($targetItem.id)/moves" --input "$bodyJson" 2>&1
                                
                                if ($LASTEXITCODE -eq 0) {
                                    Write-Host "  [OK] Movido para 'In Progress'" -ForegroundColor Green
                                } else {
                                    Write-Host "  [AVISO] Não foi possível mover: $moveResult" -ForegroundColor Yellow
                                }
                            } else {
                                Write-Host "  [AVISO] Item não encontrado na coluna" -ForegroundColor Yellow
                            }
                        }
                    } else {
                        Write-Host "  [AVISO] Coluna 'In Progress' não encontrada" -ForegroundColor Yellow
                    }
                }
            } else {
                Write-Host "  [AVISO] Não foi possível adicionar ao projeto: $mutationResult" -ForegroundColor Yellow
            }
        }
    } else {
        Write-Host "  [AVISO] Nenhum projeto encontrado" -ForegroundColor Yellow
    }
} else {
    Write-Host "  [AVISO] Não foi possível listar projetos" -ForegroundColor Yellow
}

# 3. Verificar branch
Write-Host ""
Write-Host "[3/3] Verificando branch..." -ForegroundColor Yellow

$currentBranch = git rev-parse --abbrev-ref HEAD 2>$null

if ($currentBranch -match "issue.*772|refactor.*test") {
    Write-Host "  [OK] Branch correta: $currentBranch" -ForegroundColor Green
} else {
    Write-Host "  [AVISO] Branch atual: $currentBranch" -ForegroundColor Yellow
    Write-Host "  Branch esperada deveria conter 'issue-772' ou 'refactor'" -ForegroundColor Gray
}

Write-Host ""
Write-Host "=== CONCLUÍDO ===" -ForegroundColor Cyan
Write-Host "Issue #$issueNumber configurada" -ForegroundColor Green
Write-Host "URL: https://github.com/$meuRepo/issues/$issueNumber" -ForegroundColor Gray

