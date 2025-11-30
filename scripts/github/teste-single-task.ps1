# --- SCRIPT DE TESTE - PROCESSA APENAS 1 TASK ---
# Encoding UTF-8 para evitar problemas com caracteres especiais
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"
$projectOwner = "Stramp"

# Projetos GitHub
$projetos = @{
    "Core Engineering" = @{ Nome = "Core Engineering" }
    "Narrative & Quest Design" = @{ Nome = "Narrative & Quest Design" }
    "Art & World Building" = @{ Nome = "Art & World Building" }
}

# ===== FUNÇÕES AUXILIARES =====

function Get-ProjectId {
    param([string]$projectUrl, [string]$owner)

    if ($projectUrl -match "projects/(\d+)") {
        $projectNumber = $matches[1]
        Write-Host "    [DEBUG] Obtendo Project ID para projeto #$projectNumber..." -ForegroundColor DarkGray

        $query = @"
query {
  user(login: "$owner") {
    projectV2(number: $projectNumber) {
      id
    }
  }
}
"@
        $projectInfo = & $ghPath api graphql -f query=$query 2>&1

        if ($LASTEXITCODE -eq 0) {
            Write-Host "    [DEBUG] GraphQL response recebido" -ForegroundColor DarkGray
            try {
                $projectData = $projectInfo | ConvertFrom-Json
                if ($projectData.data -and $projectData.data.user -and $projectData.data.user.projectV2) {
                    $projectId = $projectData.data.user.projectV2.id
                    Write-Host "    [DEBUG] Project ID: $projectId" -ForegroundColor DarkGray
                    return $projectId
                } else {
                    Write-Host "    [DEBUG] ERRO: Estrutura de resposta inesperada" -ForegroundColor Red
                    Write-Host "    [DEBUG] Response: $projectInfo" -ForegroundColor Yellow
                }
            } catch {
                Write-Host "    [DEBUG] ERRO ao parsear JSON: $_" -ForegroundColor Red
                Write-Host "    [DEBUG] Response: $projectInfo" -ForegroundColor Yellow
            }
        } else {
            Write-Host "    [DEBUG] ERRO na chamada GraphQL: $projectInfo" -ForegroundColor Red
        }
    } else {
        Write-Host "    [DEBUG] ERRO: URL do projeto não contém número válido: $projectUrl" -ForegroundColor Red
    }

    return $null
}

function Get-IssueNodeId {
    param([string]$issueNumber, [string]$repo, [string]$owner)
    $repoOwner, $repoName = $repo.Split('/')
    $query = "query { repository(owner: `"$repoOwner`", name: `"$repoName`") { issue(number: $issueNumber) { id } } }"
    $issueInfo = & $ghPath api graphql -f query=$query 2>&1
    if ($LASTEXITCODE -eq 0) {
        try {
            $issueData = $issueInfo | ConvertFrom-Json
            return $issueData.data.repository.issue.id
        } catch { }
    }
    return $null
}

function Add-ProjectItem {
    param([string]$projectId, [string]$issueNodeId)
    if (-not $projectId -or -not $issueNodeId) { return $false }
    $mutation = "mutation { addProjectV2ItemById(input: {projectId: `"$projectId`" contentId: `"$issueNodeId`"}) { item { id } } }"
    $result = & $ghPath api graphql -f query=$mutation 2>&1
    if ($LASTEXITCODE -eq 0) {
        try {
            $resultData = $result | ConvertFrom-Json
            if ($resultData.data.addProjectV2ItemById) { return $true }
        } catch {
            if ($result -match "already has this item" -or $result -match "Item already exists") { return $true }
        }
    }
    return $false
}

function Get-ProjectForIssue {
    param([string[]]$labels, [string]$categoria)
    $labelsLower = $labels | ForEach-Object { $_.ToLower() }
    $categoriaLower = if ($categoria) { $categoria.ToLower() } else { "" }
    $projectScores = @{
        "Core Engineering" = 0
        "Narrative & Quest Design" = 0
        "Art & World Building" = 0
    }
    foreach ($label in $labelsLower) {
        if ($label -match "^sys:|^type:") { $projectScores["Core Engineering"] += 3 }
        if ($label -match "infraestrutura|fundacao|data-tables|data-driven|criacao-personagem|combate|spellcasting|rest|save|load|persistencia|ui|ux|inventario") { $projectScores["Core Engineering"] += 3 }
        if ($label -match "^quest:|^writ:|^act:") { $projectScores["Narrative & Quest Design"] += 3 }
        if ($label -match "narrativa|dialogos|quests|missao") { $projectScores["Narrative & Quest Design"] += 3 }
        if ($label -match "^art:|^stage:") { $projectScores["Art & World Building"] += 3 }
        if ($label -match "environment|character|visual|mapa|level-design") { $projectScores["Art & World Building"] += 3 }
    }
    if ($categoriaLower -match "fundação|infraestrutura|data|sistema|código|combate|spellcasting|personagem") {
        $projectScores["Core Engineering"] += 2
    }
    if ($categoriaLower -match "narrativa|quest|missão|diálogo|história") {
        $projectScores["Narrative & Quest Design"] += 2
    }
    if ($categoriaLower -match "arte|visual|mapa|level|environment|character") {
        $projectScores["Art & World Building"] += 2
    }
    $maxScore = ($projectScores.Values | Measure-Object -Maximum).Maximum
    if ($maxScore -eq 0) { return "Core Engineering" }
    $selectedProject = $projectScores.GetEnumerator() | Where-Object { $_.Value -eq $maxScore } | Select-Object -First 1
    return $selectedProject.Key
}

function Get-OrCreateProject {
    param([string]$projectName, [string]$owner)

    Write-Host "    [DEBUG] Buscando projeto: '$projectName'..." -ForegroundColor DarkGray
    $projectsJson = & $ghPath project list --owner "@me" --format json 2>&1

    if ($LASTEXITCODE -eq 0) {
        try {
            $projects = $projectsJson | ConvertFrom-Json
            Write-Host "    [DEBUG] Encontrados $($projects.projects.Count) projetos" -ForegroundColor DarkGray

            # Lista todos os projetos para debug
            foreach ($p in $projects.projects) {
                Write-Host "    [DEBUG] Projeto: '$($p.title)' (número: $($p.number))" -ForegroundColor DarkGray
            }

            $existingProject = $projects.projects | Where-Object { $_.title -eq $projectName } | Sort-Object number -Descending | Select-Object -First 1

            if ($existingProject) {
                Write-Host "    [DEBUG] Projeto encontrado: $($existingProject.url)" -ForegroundColor DarkGray
                $projectUrl = $existingProject.url
                $projectId = Get-ProjectId -projectUrl $projectUrl -owner $owner
                # Retorna mesmo sem ID (vai usar fallback CLI)
                return @{ Name = $projectName; Url = $projectUrl; Id = $projectId }
            } else {
                Write-Host "    [DEBUG] Projeto '$projectName' não encontrado na lista" -ForegroundColor Yellow
            }
        } catch {
            Write-Host "    [DEBUG] ERRO ao processar lista de projetos: $_" -ForegroundColor Red
        }
    } else {
        Write-Host "    [DEBUG] ERRO ao listar projetos: $projectsJson" -ForegroundColor Red
    }

    Write-Host "  Criando projeto: $projectName..." -ForegroundColor Yellow
    $projectJson = & $ghPath project create --title $projectName --owner "@me" --format json 2>&1

    if ($LASTEXITCODE -eq 0) {
        Write-Host "    [DEBUG] Comando de criação executado com sucesso" -ForegroundColor DarkGray
        try {
            $projectObj = $projectJson | ConvertFrom-Json
            Write-Host "    [DEBUG] Projeto criado: $($projectObj.url)" -ForegroundColor DarkGray
            $projectUrl = $projectObj.url
            $projectId = Get-ProjectId -projectUrl $projectUrl -owner $owner
            # Retorna mesmo sem ID (vai usar fallback CLI)
            return @{ Name = $projectName; Url = $projectUrl; Id = $projectId }
        } catch {
            Write-Host "    [DEBUG] ERRO ao processar JSON de criação: $_" -ForegroundColor Red
            Write-Host "    [DEBUG] Saída: $projectJson" -ForegroundColor Yellow
        }
    } else {
        Write-Host "    [DEBUG] ERRO ao criar projeto: $projectJson" -ForegroundColor Red
    }

    return $null
}

# Função principal: cria ou atualiza task
function createOrUpdateTask {
    param([string]$taskName)

    Write-Host "`n=== PROCESSANDO TASK: $taskName ===" -ForegroundColor Cyan

    # Monta caminho do arquivo (busca na pasta ciclos da documentação)
    # Script está em: F:\UNREAL GAME\MyProject2\scripts\github/
    # Documentação está em: F:\UNREAL GAME\minasphandelver\Documentacao\04-Planning\ciclos/
    if (-not $PSScriptRoot) {
        $PSScriptRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
    }
    # Sobe 3 níveis: github -> scripts -> MyProject2 -> UNREAL GAME
    $unrealGameRoot = Split-Path -Parent (Split-Path -Parent (Split-Path -Parent $PSScriptRoot))
    $pastaCiclos = Join-Path $unrealGameRoot "minasphandelver\Documentacao\04-Planning\ciclos"
    $taskFile = "$taskName.md"
    $taskPath = Join-Path $pastaCiclos $taskFile

    # Tenta encontrar em subpastas também
    if (-not (Test-Path $taskPath)) {
        $taskPath = Get-ChildItem -Path $pastaCiclos -Filter $taskFile -Recurse | Select-Object -First 1 -ExpandProperty FullName
    }

    if (-not $taskPath -or -not (Test-Path $taskPath)) {
        Write-Host "ERRO: Arquivo não encontrado: $taskFile" -ForegroundColor Red
        return $false
    }

    Write-Host "Arquivo encontrado: $taskPath" -ForegroundColor Gray

    # Lê o conteúdo do arquivo
    $linhas = Get-Content -Path $taskPath -Encoding UTF8

    # Variáveis para montagem
    $milestoneArg = ""
    $statusArg = ""
    $labelsArray = @()
    $bodyLines = @()
    $categoria = ""

    # --- PARSEAMENTO LINHA A LINHA ---
    foreach ($linha in $linhas) {
        # Extrai Categoria
        if ($linha -match "\*\*Categoria:\*\*\s*(.*)") {
            $categoria = $matches[1].Trim()
        }

        # Extrai Milestone
        if ($linha -match "\*\*Milestone:\*\*\s*(.*)") {
            $m = $matches[1].Trim()
            if ($m) { $milestoneArg = $m }
            continue
        }

        # Extrai Status
        if ($linha -match "\*\*Status:\*\*\s*(?:.*?)(Pendente|Em Progresso|Concluído|Bloqueado)(?:.*)") {
            $statusMatch = $matches[1]
            if ($statusMatch) {
                $statusArg = $statusMatch.ToLower()
                if ($statusArg -match "bloqueado") {
                    $labelsArray += "Status: Blocked"
                } else {
                    $statusLabel = "status-$statusArg"
                    $labelsArray += $statusLabel
                }
            }
            continue
        }

        # Extrai Labels
        if ($linha -match "\*\*Label:\*\*\s*(.*)") {
            $l = $matches[1].Trim()
            if ($l) {
                $l.Split(',') | ForEach-Object {
                    $label = $_.Trim()
                    if ($label) {
                        $labelsArray += $label
                    }
                }
            }
            continue
        }

        # Extrai Prioridade
        if ($linha -match "\*\*Prioridade:\*\*\s*(?:.*)(Crítica|Alta|Média|Baixa)(?:.*)") {
            $prioridade = $matches[1]
            if ($prioridade -match "Crítica") {
                $labelsArray += "P0: Critical"
            } elseif ($prioridade -match "Alta") {
                $labelsArray += "P1: High"
            } elseif ($prioridade -match "Média") {
                $labelsArray += "P2: Medium"
            } elseif ($prioridade -match "Baixa") {
                $labelsArray += "P3: Low"
            }
        }

        # Mantém o resto no corpo
        $bodyLines += $linha
    }

    # Reconstrói o corpo
    $finalBody = $bodyLines -join "`r`n"

    # Remove duplicatas de labels
    $uniqueLabels = $labelsArray | Select-Object -Unique

    Write-Host "  Milestone: $milestoneArg" -ForegroundColor Gray
    Write-Host "  Labels: $($uniqueLabels -join ', ')" -ForegroundColor Gray

    # ===== BUSCA ISSUE EXISTENTE =====
    Write-Host "`nBuscando issue existente: '$taskName'..." -ForegroundColor Cyan

    $existingIssue = $null

    # Busca usando gh issue list (mais confiável) - busca por título exato ou com "teste"
    Write-Host "  Buscando via gh issue list..." -ForegroundColor Gray
    $issueListOutput = & $ghPath issue list --repo $meuRepo --search "$taskName" --state all --limit 20 2>&1

    if ($LASTEXITCODE -eq 0 -and $issueListOutput) {
        # Parseia saída: NUMBER<TAB>STATE<TAB>TITLE...
        # Busca título exato ou com "teste" no final
        $issueNumbers = @()
        foreach ($line in $issueListOutput) {
            # Aceita título exato ou com "teste" no final
            $pattern = "^\d+\s+(OPEN|CLOSED)\s+$([regex]::Escape($taskName))(\s+teste)?$"
            if ($line -match $pattern) {
                $issueNumbers += [int]($line -split '\s+')[0]
            }
        }

        if ($issueNumbers.Count -gt 0) {
            # Pega a mais recente (maior número)
            $mostRecentNumber = ($issueNumbers | Sort-Object -Descending)[0]
            Write-Host "  Encontradas $($issueNumbers.Count) issues. Usando a mais recente: #$mostRecentNumber" -ForegroundColor Green

            # Busca detalhes da issue
            $issueDetailsJson = & $ghPath api "repos/$meuRepo/issues/$mostRecentNumber" 2>&1
            if ($LASTEXITCODE -eq 0 -and $issueDetailsJson) {
                try {
                    $issueData = $issueDetailsJson | ConvertFrom-Json -ErrorAction SilentlyContinue
                    # Aceita título exato ou com "teste" no final
                    if ($issueData -and ($issueData.title -eq $taskName -or $issueData.title -eq "$taskName teste")) {
                        $existingIssue = $issueData
                        Write-Host "  [OK] Issue confirmada: #$($existingIssue.number) (state: $($existingIssue.state), title: $($existingIssue.title))" -ForegroundColor Green
                    }
                } catch {
                    Write-Host "  Erro ao parsear detalhes: $_" -ForegroundColor Yellow
                }
            }
        }
    }

    # Se ainda não encontrou, tenta busca direta na API (pode ter mais de 100 issues)
    if (-not $existingIssue) {
        Write-Host "  Tentando busca direta na API..." -ForegroundColor Gray
        # Busca página por página até encontrar ou esgotar
        $page = 1
        $found = $false
        while ($page -le 5 -and -not $found) {
            $allIssuesJson = & $ghPath api "repos/$meuRepo/issues?state=open&per_page=100&page=$page" 2>&1
            if ($LASTEXITCODE -eq 0 -and $allIssuesJson) {
                try {
                    $allIssuesData = $allIssuesJson | ConvertFrom-Json -ErrorAction SilentlyContinue
                    if ($allIssuesData -and $allIssuesData.Count -gt 0) {
                        $matchingIssues = $allIssuesData | Where-Object { $_.title -eq $taskName }
                        if ($matchingIssues) {
                            $existingIssue = $matchingIssues | Sort-Object -Property number -Descending | Select-Object -First 1
                            Write-Host "  [OK] Issue encontrada na página ${page}: #$($existingIssue.number)" -ForegroundColor Green
                            $found = $true
                        }
                        $page++
                    } else {
                        break
                    }
                } catch {
                    break
                }
            } else {
                break
            }
        }
    }

    # ===== ATUALIZA OU CRIA =====
    if ($existingIssue) {
        # ATUALIZA ISSUE EXISTENTE
        Write-Host "`n[ATUALIZANDO] Issue #$($existingIssue.number)..." -ForegroundColor Cyan

        # Usa o título original (sem "teste")
        $updateArgs = @(
            "issue", "edit", $existingIssue.number,
            "--repo", $meuRepo,
            "--title", $taskName
        )

        # Adiciona milestone
        if ($milestoneArg) {
            $updateArgs += "--milestone", $milestoneArg
        }

        # Busca labels atuais da issue e remove antes de adicionar novos
        Write-Host "  Buscando labels atuais da issue..." -ForegroundColor Gray
        $currentLabelsJson = & $ghPath issue view $existingIssue.number --repo $meuRepo --json labels 2>&1
        if ($LASTEXITCODE -eq 0 -and $currentLabelsJson) {
            try {
                $currentLabels = ($currentLabelsJson | ConvertFrom-Json).labels.name
                if ($currentLabels) {
                    Write-Host "  Labels atuais: $($currentLabels -join ', ')" -ForegroundColor Gray
                    # Remove cada label atual individualmente
                    foreach ($label in $currentLabels) {
                        $updateArgs += "--remove-label", $label
                    }
                }
            } catch {
                Write-Host "  [AVISO] Não foi possível obter labels atuais" -ForegroundColor Yellow
            }
        }

        # Adiciona novos labels
        if ($uniqueLabels.Count -gt 0) {
            Write-Host "  Adicionando novos labels: $($uniqueLabels -join ', ')" -ForegroundColor Gray
            foreach ($label in $uniqueLabels) {
                $updateArgs += "--add-label", $label
            }
        }

        # Usa --body-file com stdin para passar o corpo (evita problemas com caracteres especiais)
        $updateArgs += "--body-file", "-"

        $updateOutput = $finalBody | & $ghPath $updateArgs 2>&1

        if ($LASTEXITCODE -eq 0) {
            Write-Host "  [OK] Issue atualizada com sucesso!" -ForegroundColor Green
            Write-Host "  URL: $($existingIssue.html_url)" -ForegroundColor Gray

            # Classifica e adiciona ao projeto
            $selectedProject = Get-ProjectForIssue -labels $uniqueLabels -categoria $categoria
            Write-Host "  Classificada em: $selectedProject" -ForegroundColor Yellow

            Write-Host "  Buscando/criando projeto: $($projetos[$selectedProject].Nome)..." -ForegroundColor Gray
                    $projectInfo = Get-OrCreateProject -projectName $projetos[$selectedProject].Nome -owner $projectOwner
                    if ($projectInfo -and $projectInfo.Url) {
                        Write-Host "  Projeto encontrado/criado: $($projectInfo.Url)" -ForegroundColor Gray

                        # Tenta adicionar via GraphQL primeiro
                        if ($projectInfo.Id) {
                            Write-Host "  Obtendo Issue Node ID..." -ForegroundColor Gray
                            $issueNodeId = Get-IssueNodeId -issueNumber $existingIssue.number -repo $meuRepo -owner $projectOwner
                            if ($issueNodeId) {
                                Write-Host "  Issue Node ID: $issueNodeId" -ForegroundColor Gray
                                Write-Host "  Adicionando ao projeto via GraphQL..." -ForegroundColor Gray
                                $added = Add-ProjectItem -projectId $projectInfo.Id -issueNodeId $issueNodeId
                                if ($added) {
                                    Write-Host "  [OK] Adicionada ao projeto: $selectedProject" -ForegroundColor Green
                                }
                            }
                        }

                        # Fallback: usa --add-project no gh issue edit se GraphQL falhar
                        if (-not $added) {
                            Write-Host "  Tentando adicionar via --add-project..." -ForegroundColor Gray
                            $addResult = & $ghPath issue edit $existingIssue.number --repo $meuRepo --add-project $selectedProject 2>&1
                            if ($LASTEXITCODE -eq 0) {
                                Write-Host "  [OK] Adicionada ao projeto via CLI: $selectedProject" -ForegroundColor Green
                            } else {
                                Write-Host "  [AVISO] Não foi possível adicionar ao projeto" -ForegroundColor Yellow
                                Write-Host "  Detalhe: $addResult" -ForegroundColor DarkGray
                            }
                        }
                    } else {
                        Write-Host "  [ERRO] Não foi possível obter/criar projeto" -ForegroundColor Red
                    }

            return $true
        } else {
            Write-Host "  [ERRO] Falha ao atualizar issue" -ForegroundColor Red
            Write-Host "  Detalhe: $updateOutput" -ForegroundColor Yellow
            return $false
        }
    } else {
        # CRIA NOVA ISSUE
        Write-Host "`n[CRIANDO] Nova issue..." -ForegroundColor Yellow

        $issueArgs = @(
            "issue", "create",
            "--repo", $meuRepo,
            "--title", $taskName,
            "--assignee", "@me"
        )

        # Adiciona milestone
        if ($milestoneArg) {
            $issueArgs += "--milestone", $milestoneArg
        }

        # Adiciona labels
        if ($uniqueLabels.Count -gt 0) {
            foreach ($label in $uniqueLabels) {
                $issueArgs += "--label", $label
            }
        }

        # Usa --body-file com stdin
        $issueArgs += "--body-file", "-"

        $cmdOutput = $finalBody | & $ghPath $issueArgs 2>&1

        if ($LASTEXITCODE -eq 0) {
            # Extrai URL da issue criada
            $issueUrl = ($cmdOutput | Select-String -Pattern "https://github\.com/.*/issues/(\d+)").Matches.Value

            if ($issueUrl) {
                Write-Host "  [OK] Issue criada com sucesso!" -ForegroundColor Green
                Write-Host "  URL: $issueUrl" -ForegroundColor Gray

                # Extrai número da issue
                if ($issueUrl -match "issues/(\d+)") {
                    $issueNumber = $matches[1]

                    # Classifica e adiciona ao projeto
                    $selectedProject = Get-ProjectForIssue -labels $uniqueLabels -categoria $categoria
                    Write-Host "  Classificada em: $selectedProject" -ForegroundColor Yellow

                    Write-Host "  Buscando/criando projeto: $($projetos[$selectedProject].Nome)..." -ForegroundColor Gray
                    $projectInfo = Get-OrCreateProject -projectName $projetos[$selectedProject].Nome -owner $projectOwner
                    if ($projectInfo -and $projectInfo.Url) {
                        Write-Host "  Projeto encontrado/criado: $($projectInfo.Url)" -ForegroundColor Gray

                        # Tenta adicionar via GraphQL primeiro
                        $added = $false
                        if ($projectInfo.Id) {
                            Write-Host "  Obtendo Issue Node ID..." -ForegroundColor Gray
                            $issueNodeId = Get-IssueNodeId -issueNumber $issueNumber -repo $meuRepo -owner $projectOwner
                            if ($issueNodeId) {
                                Write-Host "  Issue Node ID: $issueNodeId" -ForegroundColor Gray
                                Write-Host "  Adicionando ao projeto via GraphQL..." -ForegroundColor Gray
                                $added = Add-ProjectItem -projectId $projectInfo.Id -issueNodeId $issueNodeId
                                if ($added) {
                                    Write-Host "  [OK] Adicionada ao projeto: $selectedProject" -ForegroundColor Green
                                }
                            }
                        }

                        # Fallback: usa --add-project no gh issue edit se GraphQL falhar
                        if (-not $added) {
                            Write-Host "  Tentando adicionar via --add-project..." -ForegroundColor Gray
                            $addResult = & $ghPath issue edit $issueNumber --repo $meuRepo --add-project $selectedProject 2>&1
                            if ($LASTEXITCODE -eq 0) {
                                Write-Host "  [OK] Adicionada ao projeto via CLI: $selectedProject" -ForegroundColor Green
                            } else {
                                Write-Host "  [AVISO] Não foi possível adicionar ao projeto" -ForegroundColor Yellow
                                Write-Host "  Detalhe: $addResult" -ForegroundColor DarkGray
                            }
                        }
                    } else {
                        Write-Host "  [ERRO] Não foi possível obter/criar projeto" -ForegroundColor Red
                    }
                }

                return $true
            } else {
                Write-Host "  [AVISO] Issue criada mas URL não encontrada" -ForegroundColor Yellow
                Write-Host "  Saída: $cmdOutput" -ForegroundColor Gray
                return $true
            }
        } else {
            Write-Host "  [ERRO] Falha ao criar issue" -ForegroundColor Red
            Write-Host "  Detalhe: $cmdOutput" -ForegroundColor Yellow
            return $false
        }
    }
}

# ===== EXECUÇÃO DO TESTE =====
Write-Host "--- TESTE: createOrUpdateTask ---" -ForegroundColor Cyan

# Testa com a task "02-04-skill-datatable"
$result = createOrUpdateTask -taskName "02-04-skill-datatable"

if ($result) {
    Write-Host "`n[SUCESSO] Teste concluído!" -ForegroundColor Green
} else {
    Write-Host "`n[ERRO] Teste falhou!" -ForegroundColor Red
}

Write-Host "`n--- TESTE CONCLUÍDO ---" -ForegroundColor Cyan
