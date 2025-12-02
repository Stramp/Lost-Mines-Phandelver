# --- SCRIPT: create-task-branch ---
# Encoding UTF-8 para evitar problemas com caracteres especiais
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# ===== CONFIGURAÇÃO =====
$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"

$unrealGameRoot = Split-Path -Parent (Split-Path -Parent (Split-Path -Parent $PSScriptRoot))
$pastaCiclos = Join-Path $unrealGameRoot "minasphandelver\Documentacao\04-Planning\ciclos"

# ===== FUNÇÕES AUXILIARES =====

function Get-TaskTitleFromFile {
    param([string]$filePath)

    if (-not (Test-Path $filePath)) {
        Write-Host "  [ERRO] Arquivo não encontrado: $filePath" -ForegroundColor Red
        return $null
    }

    try {
        $linhas = Get-Content -Path $filePath -Encoding UTF8 -ErrorAction Stop

        foreach ($linha in $linhas) {
            # Procura primeira linha com # (título)
            if ($linha -match "^#\s+(.+)$") {
                $titulo = $matches[1].Trim()
                return $titulo
            }
        }

        Write-Host "  [ERRO] Título não encontrado no arquivo" -ForegroundColor Red
        return $null
    } catch {
        Write-Host "  [ERRO] Erro ao ler arquivo: $_" -ForegroundColor Red
        return $null
    }
}

function Get-IssueByTitle {
    param([string]$title)

    Write-Host "  Buscando issue: `"$title`"..." -ForegroundColor Gray

    try {
        # Usa busca sem aspas e depois filtra pelo título exato
        $searchQuery = "$title in:title"
        $issueJson = & $ghPath issue list --repo $meuRepo --search $searchQuery --json number,url,title --limit 10 2>&1

        if ($LASTEXITCODE -eq 0 -and $issueJson) {
            $issues = $issueJson | ConvertFrom-Json

            if ($issues -and $issues.Count -gt 0) {
                # Procura issue com título exato
                $exactMatch = $issues | Where-Object { $_.title -eq $title } | Select-Object -First 1

                if ($exactMatch) {
                    Write-Host "  [OK] Issue encontrada: #$($exactMatch.number)" -ForegroundColor Green
                    return $exactMatch
                } else {
                    Write-Host "  [AVISO] Issues encontradas mas nenhuma com título exato:" -ForegroundColor Yellow
                    Write-Host "    Esperado: `"$title`"" -ForegroundColor Yellow
                    foreach ($issue in $issues | Select-Object -First 3) {
                        Write-Host "    Encontrado: `"$($issue.title)`"" -ForegroundColor Yellow
                    }
                    return $null
                }
            }
        }

        Write-Host "  [ERRO] Issue não encontrada no GitHub" -ForegroundColor Red
        Write-Host "  Debug: Search query = `"$searchQuery`"" -ForegroundColor Gray
        return $null
    } catch {
        Write-Host "  [ERRO] Erro ao buscar issue: $_" -ForegroundColor Red
        return $null
    }
}

function Convert-FileNameToBranchFormat {
    param([string]$fileName)

    # Remove extensão .md
    $baseName = $fileName -replace '\.md$', ''

    # Extrai ciclo e subciclo (ex: 01-01-setup-projeto → 01-01)
    if ($baseName -match '^(\d+)-(\d+)-(.+)$') {
        $ciclo = [int]$matches[1]  # Remove zeros à esquerda automaticamente
        $subciclo = [int]$matches[2]
        $nome = $matches[3]

        # Formato: 1x1-setup-projeto
        return "$ciclo`x$subciclo-$nome"
    }

    # Se não seguir o padrão, retorna o nome sem extensão
    return $baseName
}

function Move-CardToInProgress {
    param(
        [int]$issueNumber
    )

    Write-Host "  Movendo card para 'In Progress'..." -ForegroundColor Gray

    try {
        # Lista projetos do usuário/organização
        $projectsJson = & $ghPath project list --owner Stramp --limit 100 --json id,title 2>&1

        if ($LASTEXITCODE -ne 0) {
            Write-Host "  [AVISO] Não foi possível listar projetos (gh CLI pode não ter permissão)" -ForegroundColor Yellow
            return $false
        }

        $projects = $projectsJson | ConvertFrom-Json

        if (-not $projects -or $projects.Count -eq 0) {
            Write-Host "  [AVISO] Nenhum projeto encontrado" -ForegroundColor Yellow
            return $false
        }

        # Procura projeto que contenha a issue (geralmente o primeiro projeto ativo)
        $targetProject = $projects | Select-Object -First 1

        if (-not $targetProject) {
            Write-Host "  [AVISO] Projeto não encontrado" -ForegroundColor Yellow
            return $false
        }

        Write-Host "  Projeto: $($targetProject.title)" -ForegroundColor Gray

        # Busca o item (card) da issue no projeto
        $itemJson = & $ghPath project item-list $($targetProject.id) --owner Stramp --format json 2>&1

        if ($LASTEXITCODE -ne 0) {
            Write-Host "  [AVISO] Não foi possível listar items do projeto" -ForegroundColor Yellow
            return $false
        }

        $items = $itemJson | ConvertFrom-Json

        # Procura o item que corresponde à issue
        # O formato do JSON pode variar, tenta diferentes propriedades
        $targetItem = $null
        foreach ($item in $items) {
            if ($item.content -and $item.content.number -eq $issueNumber) {
                $targetItem = $item
                break
            }
            elseif ($item.contentId -and $item.contentId -match "issue_$issueNumber") {
                $targetItem = $item
                break
            }
        }

        if (-not $targetItem) {
            Write-Host "  [AVISO] Card da issue #$issueNumber não encontrado no projeto" -ForegroundColor Yellow
            Write-Host "  (Issue pode não estar adicionada ao projeto ainda)" -ForegroundColor Gray
            return $false
        }

        # Busca colunas do projeto via API
        $columnsJson = & $ghPath api "projects/$($targetProject.id)/columns" --jq '.[] | {id: .id, name: .name}' 2>&1

        if ($LASTEXITCODE -ne 0 -or -not $columnsJson) {
            Write-Host "  [AVISO] Não foi possível listar colunas do projeto" -ForegroundColor Yellow
            return $false
        }

        $columns = $columnsJson | ConvertFrom-Json

        # Procura coluna "In Progress" (várias variações possíveis)
        $inProgressColumn = $columns | Where-Object {
            $_.name -match "In Progress|InProgress|in-progress|Doing|Em Progresso|Em Andamento"
        } | Select-Object -First 1

        if (-not $inProgressColumn) {
            Write-Host "  [AVISO] Coluna 'In Progress' não encontrada no projeto" -ForegroundColor Yellow
            Write-Host "  Colunas disponíveis: $($columns.name -join ', ')" -ForegroundColor Gray
            return $false
        }

        Write-Host "  Coluna encontrada: $($inProgressColumn.name)" -ForegroundColor Gray

        # Move o card para a coluna In Progress usando API
        # Obtém o ID do item (card)
        $itemId = $targetItem.id

        # Obtém a coluna atual do item (se houver)
        $currentColumnId = $targetItem.columnId

        # Se já está na coluna In Progress, não precisa mover
        if ($currentColumnId -eq $inProgressColumn.id) {
            Write-Host "  [OK] Card já está em '$($inProgressColumn.name)'" -ForegroundColor Green
            return $true
        }

        # Move o item para a coluna In Progress usando a API do GitHub Projects
        # API do GitHub Projects v2: POST /projects/columns/{column_id}/moves
        # Formato do body: {"position": "top", "item_id": "item_id"}
        $bodyJson = @{
            position = "top"
            item_id = $itemId
        } | ConvertTo-Json -Compress

        $moveResult = & $ghPath api -X POST "projects/columns/$($inProgressColumn.id)/moves" `
            --input "$bodyJson" 2>&1

        # Método alternativo: usa gh project item-edit se disponível
        if ($LASTEXITCODE -ne 0) {
            Write-Host "  [AVISO] Tentando método alternativo..." -ForegroundColor Yellow

            # Tenta usar gh project item-edit (se disponível na versão do gh CLI)
            $editResult = & $ghPath project item-edit $itemId --owner Stramp --field-id "Status" --single-select-option-id "$($inProgressColumn.id)" 2>&1

            if ($LASTEXITCODE -eq 0) {
                Write-Host "  [OK] Card movido para '$($inProgressColumn.name)'" -ForegroundColor Green
                return $true
            } else {
                Write-Host "  [AVISO] Não foi possível mover card automaticamente" -ForegroundColor Yellow
                Write-Host "  Mova manualmente o card da issue #$issueNumber para 'In Progress' no GitHub Project" -ForegroundColor Gray
                Write-Host "  URL do projeto: https://github.com/users/Stramp/projects" -ForegroundColor Gray
                return $false
            }
        } else {
            Write-Host "  [OK] Card movido para '$($inProgressColumn.name)'" -ForegroundColor Green
            return $true
        }

    } catch {
        Write-Host "  [AVISO] Erro ao mover card: $_" -ForegroundColor Yellow
        Write-Host "  (Card pode ser movido manualmente no GitHub Project)" -ForegroundColor Gray
        return $false
    }
}

function Create-TaskBranch {
    param(
        [string]$taskFile,
        [switch]$Force
    )

    Write-Host "=== CREATE TASK BRANCH ===" -ForegroundColor Cyan
    Write-Host ""

    # Validações iniciais
    if (-not (Test-Path $pastaCiclos)) {
        Write-Host "[ERRO] Pasta de ciclos não encontrada: $pastaCiclos" -ForegroundColor Red
        return $false
    }

    # Verifica se está em repositório Git
    $gitRoot = git rev-parse --show-toplevel 2>$null
    if (-not $gitRoot) {
        Write-Host "[ERRO] Não está em um repositório Git" -ForegroundColor Red
        return $false
    }

    Write-Host "Repositório Git: $gitRoot" -ForegroundColor Gray
    Write-Host ""

    # Resolve caminho do arquivo
    $filePath = $null

    # Se já é caminho completo
    if (Test-Path $taskFile) {
        $filePath = $taskFile
    }
    # Se é apenas nome do arquivo, busca na pasta ciclos
    elseif (Test-Path (Join-Path $pastaCiclos $taskFile)) {
        $filePath = Join-Path $pastaCiclos $taskFile
    }
    # Tenta buscar recursivamente
    else {
        $foundFile = Get-ChildItem -Path $pastaCiclos -Filter $taskFile -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1
        if ($foundFile) {
            $filePath = $foundFile.FullName
        }
    }

    if (-not $filePath) {
        Write-Host "[ERRO] Arquivo não encontrado: $taskFile" -ForegroundColor Red
        Write-Host "  Procurou em: $pastaCiclos" -ForegroundColor Gray
        return $false
    }

    Write-Host "Arquivo: $filePath" -ForegroundColor Gray
    Write-Host ""

    # Extrai título do arquivo
    $taskTitle = Get-TaskTitleFromFile -filePath $filePath
    if (-not $taskTitle) {
        return $false
    }

    Write-Host "Título da task: $taskTitle" -ForegroundColor Yellow
    Write-Host ""

    # Busca issue no GitHub
    $issue = Get-IssueByTitle -title $taskTitle
    if (-not $issue) {
        return $false
    }

    Write-Host ""

    # Converte nome do arquivo para formato de branch
    $fileName = Split-Path -Leaf $filePath
    $branchSuffix = Convert-FileNameToBranchFormat -fileName $fileName

    # Monta nome da branch: feat/issue-123__1x1-setup-projeto
    $branchName = "feat/issue-$($issue.number)__$branchSuffix"

    Write-Host "Nome da branch: $branchName" -ForegroundColor Cyan
    Write-Host ""

    # Verifica se branch já existe localmente
    $currentBranch = git rev-parse --abbrev-ref HEAD 2>$null
    $branchExistsLocal = git show-ref --verify --quiet "refs/heads/$branchName" 2>$null

    if ($LASTEXITCODE -eq 0) {
        # Branch existe localmente
        if ($currentBranch -eq $branchName) {
            Write-Host "[OK] Já está na branch: $branchName" -ForegroundColor Green
            Write-Host "  Conectada com: Issue #$($issue.number) - $taskTitle" -ForegroundColor Gray
            Write-Host "  URL: $($issue.url)" -ForegroundColor Gray
            return $true
        } else {
            if ($Force) {
                Write-Host "[AVISO] Branch já existe localmente. Fazendo checkout..." -ForegroundColor Yellow
                git checkout $branchName 2>&1 | Out-Null
                if ($LASTEXITCODE -eq 0) {
                    Write-Host "[OK] Checkout realizado: $branchName" -ForegroundColor Green
                    Write-Host "  Conectada com: Issue #$($issue.number) - $taskTitle" -ForegroundColor Gray
                    Write-Host "  URL: $($issue.url)" -ForegroundColor Gray
                    return $true
                } else {
                    Write-Host "[ERRO] Falha ao fazer checkout da branch" -ForegroundColor Red
                    return $false
                }
            } else {
                Write-Host "[ERRO] Branch já existe localmente: $branchName" -ForegroundColor Red
                Write-Host "  Use -Force para fazer checkout da branch existente" -ForegroundColor Yellow
                return $false
            }
        }
    }

    # Cria nova branch conectada com a issue no GitHub
    Write-Host "Criando branch conectada com issue: $branchName..." -ForegroundColor Cyan

    # Usa GitHub CLI para criar branch conectada com a issue
    $ghResult = & $ghPath issue develop $($issue.number) --repo $meuRepo --name $branchName --checkout 2>&1

    if ($LASTEXITCODE -eq 0) {
        Write-Host "[OK] Branch criada e conectada com sucesso!" -ForegroundColor Green
        Write-Host ""

        # Tenta mover card para "In Progress"
        Move-CardToInProgress -issueNumber $issue.number

        Write-Host ""
        Write-Host "=== RESUMO ===" -ForegroundColor Cyan
        Write-Host "  Branch: $branchName" -ForegroundColor White
        Write-Host "  Issue: #$($issue.number) - $taskTitle" -ForegroundColor White
        Write-Host "  URL: $($issue.url)" -ForegroundColor White
        Write-Host ""
        Write-Host "Branch conectada com issue #$($issue.number) no GitHub" -ForegroundColor Green
        return $true
    } else {
        # Fallback: cria branch localmente se GitHub CLI falhar
        Write-Host "[AVISO] GitHub CLI falhou, criando branch localmente..." -ForegroundColor Yellow
        git checkout -b $branchName 2>&1 | Out-Null

        if ($LASTEXITCODE -eq 0) {
            Write-Host "[OK] Branch criada localmente (não conectada no GitHub)" -ForegroundColor Yellow
            Write-Host "  Para conectar, use: gh issue develop $($issue.number) --name $branchName" -ForegroundColor Gray
            return $true
        } else {
            Write-Host "[ERRO] Falha ao criar branch" -ForegroundColor Red
            return $false
        }
    }
}

# ===== EXECUÇÃO =====

# Verifica se foi chamado com parâmetros
if ($args.Count -gt 0) {
    $taskFile = $args[0]
    $force = $args -contains "-Force" -or $args -contains "--force"

    Create-TaskBranch -taskFile $taskFile -Force:$force
} else {
    Write-Host "Uso: .\create-task-branch.ps1 <arquivo.md> [-Force]" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Exemplos:" -ForegroundColor Cyan
    Write-Host "  .\create-task-branch.ps1 01-01-setup-projeto.md" -ForegroundColor Gray
    Write-Host "  .\create-task-branch.ps1 fase-1\01-fundacao\01-01-setup-projeto.md" -ForegroundColor Gray
    Write-Host "  .\create-task-branch.ps1 01-01-setup-projeto.md -Force" -ForegroundColor Gray
    Write-Host ""
    Write-Host "O script irá:" -ForegroundColor Cyan
    Write-Host "  1. Ler o arquivo .md e extrair o título" -ForegroundColor Gray
    Write-Host "  2. Buscar a issue no GitHub pelo título" -ForegroundColor Gray
    Write-Host "  3. Criar branch no formato: feat/issue-123__1x1-setup-projeto" -ForegroundColor Gray
    Write-Host "  4. Fazer checkout automaticamente" -ForegroundColor Gray
    Write-Host "  5. Tentar mover card do projeto de 'TODO' para 'In Progress'" -ForegroundColor Gray
}
