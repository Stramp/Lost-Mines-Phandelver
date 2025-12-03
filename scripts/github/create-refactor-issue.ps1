# Script para criar issue de refatoração, label, adicionar ao board e criar branch
# Encoding UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# ===== CONFIGURAÇÃO =====
$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"

# Título e descrição da issue
$issueTitle = "refactor(scripts): reorganize test scripts and add category selection"
$issueBody = @"
## Descrição

Refatoração dos scripts de teste para melhor organização e adição de funcionalidade de seleção de categorias.

## Mudanças Realizadas

- Removidos scripts antigos de teste (run_tests_by_task, run_all_tests, etc.)
- Criado `run_tests_simple.ps1` com exibição de resultados baseada em JSON
- Criado `run_tests_with_categories.ps1` com seleção interativa de categorias
- Atualizado `MyProject2.Build.cs` para suporte a automation tests

## Arquivos Afetados

- `scripts/build-test/run_tests_simple.ps1` (novo)
- `scripts/build-test/run_tests_with_categories.ps1` (novo)
- `Source/MyProject2/MyProject2.Build.cs` (modificado)
- Scripts antigos removidos

## Benefícios

- Interface mais limpa e organizada
- Possibilidade de filtrar testes por categoria
- Melhor visualização de resultados (Error/Warning apenas)
- Código mais modular e reutilizável
"@

Write-Host "=== CRIANDO ISSUE DE REFATORAÇÃO ===" -ForegroundColor Cyan
Write-Host ""

# 1. Criar label "refatoração" se não existir
Write-Host "[1/5] Verificando label 'refatoração'..." -ForegroundColor Yellow
$labelExists = & $ghPath label list --repo $meuRepo --json name | ConvertFrom-Json | Where-Object { $_.name -eq "refatoração" }

if (-not $labelExists) {
    Write-Host "  Criando label 'refatoração'..." -ForegroundColor Gray
    $labelResult = & $ghPath label create "refatoração" --repo $meuRepo --description "Refatoração de código" --color "0E8A16" 2>&1
    if ($LASTEXITCODE -eq 0) {
        Write-Host "  [OK] Label criado" -ForegroundColor Green
    } else {
        Write-Host "  [AVISO] Erro ao criar label: $labelResult" -ForegroundColor Yellow
    }
} else {
    Write-Host "  [OK] Label já existe" -ForegroundColor Green
}

# 2. Criar a issue
Write-Host ""
Write-Host "[2/5] Criando issue..." -ForegroundColor Yellow
$issueResult = $issueBody | & $ghPath issue create --repo $meuRepo --title $issueTitle --label "refatoração" --assignee "@me" --body-file "-" 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "  [ERRO] Falha ao criar issue: $issueResult" -ForegroundColor Red
    exit 1
}

# Extrai número da issue da URL
$issueUrl = ($issueResult | Select-String -Pattern "https://github\.com/.*/issues/(\d+)").Matches.Value
$issueNumber = ($issueResult | Select-String -Pattern "https://github\.com/.*/issues/(\d+)").Matches.Groups[1].Value

if (-not $issueNumber) {
    Write-Host "  [ERRO] Não foi possível extrair número da issue" -ForegroundColor Red
    exit 1
}

Write-Host "  [OK] Issue criada: #$issueNumber" -ForegroundColor Green
Write-Host "  URL: $issueUrl" -ForegroundColor Gray

# 3. Adicionar ao board (projeto)
Write-Host ""
Write-Host "[3/5] Adicionando ao board..." -ForegroundColor Yellow

# Lista projetos
$projectsJson = & $ghPath project list --owner Stramp --limit 100 --json id,title 2>&1

if ($LASTEXITCODE -eq 0 -and $projectsJson) {
    $projects = $projectsJson | ConvertFrom-Json
    
    # Procura projeto "Core Engineering" (padrão para refatoração)
    $targetProject = $projects | Where-Object { $_.title -match "Core Engineering" } | Select-Object -First 1
    
    if (-not $targetProject) {
        # Se não encontrar, usa o primeiro projeto
        $targetProject = $projects | Select-Object -First 1
    }
    
    if ($targetProject) {
        Write-Host "  Projeto: $($targetProject.title)" -ForegroundColor Gray
        
        # Adiciona issue ao projeto
        $addResult = & $ghPath project item-add $($targetProject.id) --owner Stramp --url $issueUrl 2>&1
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "  [OK] Issue adicionada ao projeto" -ForegroundColor Green
        } else {
            Write-Host "  [AVISO] Não foi possível adicionar ao projeto automaticamente" -ForegroundColor Yellow
            Write-Host "  Adicione manualmente: $issueUrl" -ForegroundColor Gray
        }
    } else {
        Write-Host "  [AVISO] Nenhum projeto encontrado" -ForegroundColor Yellow
    }
} else {
    Write-Host "  [AVISO] Não foi possível listar projetos" -ForegroundColor Yellow
}

# 4. Mover para "In Progress"
Write-Host ""
Write-Host "[4/5] Movendo para 'In Progress'..." -ForegroundColor Yellow

# Busca projetos novamente
$projectsJson = & $ghPath project list --owner Stramp --limit 100 --json id,title 2>&1

if ($LASTEXITCODE -eq 0 -and $projectsJson) {
    $projects = $projectsJson | ConvertFrom-Json
    $targetProject = $projects | Where-Object { $_.title -match "Core Engineering" } | Select-Object -First 1
    
    if (-not $targetProject) {
        $targetProject = $projects | Select-Object -First 1
    }
    
    if ($targetProject) {
        # Busca colunas
        $columnsJson = & $ghPath api "projects/$($targetProject.id)/columns" --jq '.[] | {id: .id, name: .name}' 2>&1
        
        if ($LASTEXITCODE -eq 0 -and $columnsJson) {
            $columns = $columnsJson | ConvertFrom-Json
            $inProgressColumn = $columns | Where-Object {
                $_.name -match "In Progress|InProgress|in-progress|Doing|Em Progresso|Em Andamento"
            } | Select-Object -First 1
            
            if ($inProgressColumn) {
                # Busca o item da issue no projeto
                $itemsJson = & $ghPath project item-list $($targetProject.id) --owner Stramp --format json 2>&1
                
                if ($LASTEXITCODE -eq 0 -and $itemsJson) {
                    $items = $itemsJson | ConvertFrom-Json
                    $targetItem = $items | Where-Object {
                        ($_.content -and $_.content.number -eq [int]$issueNumber) -or
                        ($_.contentId -and $_.contentId -match "issue_$issueNumber")
                    } | Select-Object -First 1
                    
                    if ($targetItem) {
                        $itemId = $targetItem.id
                        $bodyJson = @{
                            position = "top"
                            item_id = $itemId
                        } | ConvertTo-Json -Compress
                        
                        $moveResult = & $ghPath api -X POST "projects/columns/$($inProgressColumn.id)/moves" --input "$bodyJson" 2>&1
                        
                        if ($LASTEXITCODE -eq 0) {
                            Write-Host "  [OK] Movido para 'In Progress'" -ForegroundColor Green
                        } else {
                            Write-Host "  [AVISO] Não foi possível mover automaticamente" -ForegroundColor Yellow
                        }
                    } else {
                        Write-Host "  [AVISO] Item não encontrado no projeto" -ForegroundColor Yellow
                    }
                }
            } else {
                Write-Host "  [AVISO] Coluna 'In Progress' não encontrada" -ForegroundColor Yellow
            }
        }
    }
}

# 5. Criar branch vinculada
Write-Host ""
Write-Host "[5/5] Criando branch vinculada..." -ForegroundColor Yellow

$branchName = "refactor/issue-$issueNumber__reorganize-test-scripts"

# Verifica se já está na branch
$currentBranch = git rev-parse --abbrev-ref HEAD 2>$null

if ($currentBranch -eq $branchName) {
    Write-Host "  [OK] Já está na branch: $branchName" -ForegroundColor Green
} else {
    # Verifica se branch existe
    $branchExists = git show-ref --verify --quiet "refs/heads/$branchName" 2>$null
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "  Branch já existe, fazendo checkout..." -ForegroundColor Gray
        git checkout $branchName 2>&1 | Out-Null
        if ($LASTEXITCODE -eq 0) {
            Write-Host "  [OK] Checkout realizado" -ForegroundColor Green
        }
    } else {
        # Cria branch conectada com a issue
        Write-Host "  Criando branch: $branchName" -ForegroundColor Gray
        $branchResult = & $ghPath issue develop $issueNumber --repo $meuRepo --name $branchName --checkout 2>&1
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "  [OK] Branch criada e conectada" -ForegroundColor Green
        } else {
            # Fallback: cria localmente
            Write-Host "  [AVISO] GitHub CLI falhou, criando localmente..." -ForegroundColor Yellow
            git checkout -b $branchName 2>&1 | Out-Null
            if ($LASTEXITCODE -eq 0) {
                Write-Host "  [OK] Branch criada localmente" -ForegroundColor Green
            }
        }
    }
}

Write-Host ""
Write-Host "=== RESUMO ===" -ForegroundColor Cyan
Write-Host "  Issue: #$issueNumber - $issueTitle" -ForegroundColor White
Write-Host "  URL: $issueUrl" -ForegroundColor White
Write-Host "  Branch: $branchName" -ForegroundColor White
Write-Host ""
Write-Host "[OK] Tudo configurado!" -ForegroundColor Green

