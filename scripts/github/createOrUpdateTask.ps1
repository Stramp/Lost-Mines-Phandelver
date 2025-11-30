# --- SCRIPT: createOrUpdateTask ---
# Encoding UTF-8 para evitar problemas com caracteres especiais
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# ===== CONFIGURAÇÃO =====
$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"

$unrealGameRoot = Split-Path -Parent (Split-Path -Parent (Split-Path -Parent $PSScriptRoot))
$pastaCiclos = Join-Path $unrealGameRoot "minasphandelver\Documentacao\04-Planning\ciclos"

# Projetos GitHub
$projetos = @{
    "Core Engineering" = @{ Nome = "Core Engineering" }
    "Narrative & Quest Design" = @{ Nome = "Narrative & Quest Design" }
    "Art & World Building" = @{ Nome = "Art & World Building" }
}

# ===== FUNÇÕES AUXILIARES =====

function Push-NewTask {
    # Define os parâmetros da função (todos obrigatórios)
    param(
        [string]$repo,              # Repositório no formato "usuario/repositorio"
        [string]$title,              # Título da issue/task
        [string]$body,               # Corpo/descrição da issue
        [string]$assignee,           # Responsável pela issue
        [string[]]$labels,           # Array de labels
        [string]$milestone,          # Milestone associado
        [string]$project             # Nome do projeto GitHub
    )

    # Monta array com argumentos do comando gh issue create
    $issueArgs = @(
        "issue", "create",
        "--repo", $repo,
        "--title", $title,
        "--assignee", $assignee
    )

    # Adiciona milestone se não estiver vazio
    if ($milestone) {
        $issueArgs += "--milestone", $milestone
    }

    # Adiciona project se não estiver vazio
    if ($project) {
        $issueArgs += "--project", $project
    }

    # Adiciona cada label ao array de argumentos
    foreach ($label in $labels) {
        $issueArgs += "--label", $label
    }

    # Adiciona flag para passar body via stdin
    $issueArgs += "--body-file", "-"


    # Executa o comando passando o body via pipe (stdin)
    $cmdOutput = $body | & $ghPath $issueArgs 2>&1
    Write-Host "  [DEBUG] -: $($cmdOutput)" -ForegroundColor Gray
    # Retorna o output do comando
    return $cmdOutput
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

# ===== FUNÇÕES PRINCIPAIS =====

function Create-Task {
    # Define os parâmetros da função
    param(
        [string]$taskName,        # Nome/título da task
        [string]$body = "",       # Corpo/descrição da task (markdown)
        [string]$milestone = "",  # Milestone associado (opcional)
        [string[]]$labels = @(),  # Array de labels (opcional)
        [string]$assignee = "@me", # Responsável pela task (padrão: eu)
        [string]$project = ""     # Projeto GitHub onde adicionar (opcional)
    )

    # Exibe log informando que está criando a task
    Write-Host "Criando task: $taskName" -ForegroundColor Cyan

    # Valida parâmetros obrigatórios
    if (-not $taskName) {
        Write-Host "  [ERRO] taskName é obrigatório" -ForegroundColor Red
        return $null
    }

    # Garante valores padrão para parâmetros opcionais
    if (-not $body) { $body = "" }
    if (-not $assignee) { $assignee = "@me" }
    if (-not $labels) { $labels = @() }
    if (-not $milestone) { $milestone = "" }
    if (-not $project) { $project = "" }

    # Valida e exibe valores antes de chamar Push-NewTask
    Write-Host "  [DEBUG] Valores validados:" -ForegroundColor Gray
    Write-Host "    repo: $meuRepo" -ForegroundColor Gray
    Write-Host "    title: $taskName" -ForegroundColor Gray
    Write-Host "    body: $($body.Length) caracteres" -ForegroundColor Gray
    Write-Host "    assignee: $assignee" -ForegroundColor Gray
    Write-Host "    labels: $($labels.Count) label(s)" -ForegroundColor Gray
    if ($labels.Count -gt 0) {
        Write-Host "      - $($labels -join ', ')" -ForegroundColor DarkGray
    }
    Write-Host "    milestone: $(if ($milestone) { $milestone } else { '(vazio)' })" -ForegroundColor Gray
    Write-Host "    project: $(if ($project) { $project } else { '(vazio)' })" -ForegroundColor Gray

    # Valida se valores obrigatórios estão corretos
    if (-not $meuRepo) {
        Write-Host "  [ERRO] meuRepo não configurado" -ForegroundColor Red
        return $null
    }



    # Chama a função Push-NewTask para executar o comando
    $cmdOutput = Push-NewTask -repo $meuRepo -title $taskName -body $body -assignee $assignee -labels $labels -milestone $milestone -project $project

    # Verifica se o comando foi executado com sucesso (exit code 0)
    if ($LASTEXITCODE -eq 0) {
        # Extrai a URL da issue criada do output usando regex
        $issueUrl = ($cmdOutput | Select-String -Pattern "https://github\.com/.*/issues/(\d+)").Matches.Value
        # Exibe log de sucesso com a URL
        Write-Host "  [OK] Task criada: $issueUrl" -ForegroundColor Green
        # Retorna a URL da issue criada
        return $issueUrl
    } else {
        # Se falhou, exibe log de erro com o output do comando
        Write-Host "  [ERRO] Falha ao criar task: $cmdOutput" -ForegroundColor Red
        # Retorna null indicando falha
        return $null
    }
}

function Get-TasksData {
    param([System.IO.FileInfo]$arquivo)

    try {
        # Lê o arquivo completo como Raw para pegar o body
        $bodyCompleto = Get-Content -Path $arquivo.FullName -Encoding UTF8 -Raw -ErrorAction Stop

        # Lê o arquivo linha por linha para extrair o header
        $linhas = Get-Content -Path $arquivo.FullName -Encoding UTF8 -ErrorAction Stop

        # Extrai informações do header
        $titulo = ""
        $fase = ""
        $categoria = ""
        $status = ""
        $prioridade = ""
        $milestone = ""
        $labels = @()

        foreach ($linha in $linhas) {
            if ($linha -match "^#\s+(.+)" -and -not $titulo) {
                $titulo = $matches[1].Trim()
            }
            if ($linha -match "\*\*Fase:\*\*\s*(.+)") {
                $fase = $matches[1].Trim()
            }
            if ($linha -match "\*\*Categoria:\*\*\s*(.+)") {
                $categoria = $matches[1].Trim()
            }
            if ($linha -match "\*\*Status:\*\*\s*(.+)") {
                $status = $matches[1].Trim()
            }
            if ($linha -match "\*\*Prioridade:\*\*\s*(.+)") {
                $prioridade = $matches[1].Trim()
            }
            if ($linha -match "\*\*Milestone:\*\*\s*(.+)") {
                $milestone = $matches[1].Trim()
            }
            if ($linha -match "\*\*Label:\*\*\s*(.+)") {
                $labelsString = $matches[1].Trim()
                $labels = $labelsString -split "," | ForEach-Object { $_.Trim() } | Where-Object { $_ }
            }
            if ($linha -match "^---$" -and $titulo) {
                break
            }
        }

        # Determina o projeto baseado nos labels e categoria
        $selectedProjectName = Get-ProjectForIssue -labels $labels -categoria $categoria
        $projectName = if ($selectedProjectName) { $projetos[$selectedProjectName].Nome } else { "" }

        # Retorna objeto compatível com Push-NewTask
        return [PSCustomObject]@{
            repo = $meuRepo
            title = $titulo
            body = $bodyCompleto
            assignee = "@me"
            labels = $labels
            milestone = $milestone
            project = $projectName
        }

    } catch {
        # Retorna null em caso de erro
        return $null
    }
}

function Get-ListTaskInFolder {
    param([int]$limit = 0)

    if (-not (Test-Path $pastaCiclos)) {
        return @()
    }

    # Busca todos os arquivos .md (exceto índices e READMEs)
    $arquivos = Get-ChildItem -Path $pastaCiclos -Filter *.md -Recurse | Where-Object {
        $_.Name -notmatch "^(00-indice|README|ESTRUTURA)" -and
        $_.Name -notmatch "^(00-|README|ESTRUTURA)"
    } | Sort-Object FullName

    if ($arquivos.Count -eq 0) {
        return @()
    }

    # Aplica limite se especificado
    if ($limit -gt 0 -and $limit -lt $arquivos.Count) {
        $arquivos = $arquivos | Select-Object -First $limit
    }

    return $arquivos
}

function Get-TasksFromGitHub {
    # Busca todas as issues do GitHub (limite de 1000 para garantir que pega todas)
    $issuesJson = & $ghPath issue list --repo $meuRepo --state "all" --limit 1000 --json "number,title,url,state" 2>&1

    $tasksList = @()

    if ($LASTEXITCODE -eq 0 -and $issuesJson) {
        try {
            $issues = $issuesJson | ConvertFrom-Json -ErrorAction Stop

            # Se retornou um objeto único (não array), converte para array
            if ($issues -isnot [Array]) {
                $issues = @($issues)
            }

            if ($issues -and $issues.Count -gt 0) {
                foreach ($issue in $issues) {
                    # Cria objeto no mesmo formato de Get-TasksData
                    $taskObject = [PSCustomObject]@{
                        Titulo = $issue.title
                        Arquivo = $issue.title  # Usa title como Arquivo já que não temos arquivo
                        CaminhoCompleto = ""  # Não temos caminho
                        Fase = ""
                        Categoria = ""
                        Status = $issue.state
                        Prioridade = ""
                        Milestone = ""
                        Labels = @()
                        Number = $issue.number  # Adiciona número da issue
                        Url = $issue.url  # Adiciona URL da issue
                    }

                    $tasksList += $taskObject
                }
            }
        } catch {
            # Log do erro para debug
            Write-Host "  [DEBUG] Erro ao processar issues: $_" -ForegroundColor Red
        }
    } else {
        # Log se o comando falhou
        Write-Host "  [DEBUG] Comando falhou ou retornou vazio. ExitCode: $LASTEXITCODE" -ForegroundColor Yellow
    }

    return $tasksList
}

function Get-NewTasks {
    param(
        [array]$listTasksArquivos,  # Lista de arquivos (System.IO.FileInfo)
        [array]$tasksGitHub          # Lista de tasks do GitHub
    )

    $newTasks = @()

    # Processa cada arquivo e compara com tasks do GitHub
    foreach ($arquivo in $listTasksArquivos) {
        # Processa o arquivo para obter o título (que é usado como título da issue)
        $taskData = Get-TasksData -arquivo $arquivo

        if (-not $taskData) {
            # Se não conseguiu processar, pula
            continue
        }

        # Extrai o nome do arquivo e o título para comparação
        $arquivoName = $arquivo.Name -replace '\.md$', ''
        $arquivoTitle = $taskData.title

        # Verifica se existe no GitHub comparando tanto pelo nome do arquivo quanto pelo título
        $existeNoGitHub = $false
        foreach ($taskGitHub in $tasksGitHub) {
            $gitHubTitle = $taskGitHub.Titulo
            $gitHubArquivo = $taskGitHub.Arquivo -replace '\.md$', ''

            # Compara pelo título (mais confiável) ou pelo nome do arquivo
            if ($gitHubTitle -eq $arquivoTitle -or $gitHubArquivo -eq $arquivoName) {
                $existeNoGitHub = $true
                break
            }
        }

        # Se não existe no GitHub, adiciona à lista de novas
        if (-not $existeNoGitHub) {
            $newTasks += $arquivo
        }
    }

    return $newTasks
}

function Get-MilestoneForTask {
    param([object]$task)

    # Retorna o milestone do objeto task se existir
    if ($task.Milestone) {
        return $task.Milestone
    }

    # Se não tiver milestone no objeto, retorna vazio
    return ""
}

function Uploading-NewTasks {
    param([array]$newTasks)

    $criadas = 0
    $falhas = 0
    $total = $newTasks.Count
    $current = 0

    foreach ($arquivo in $newTasks) {
        $current++
        $percent = [math]::Round(($current / $total) * 100)

        # Calcula barra de progresso (20 caracteres)
        $filled = [math]::Round(($current / $total) * 20)
        $empty = 20 - $filled
        $progressBar = "[" + ("|" * $filled) + ("_" * $empty) + "]"

        # Processa o arquivo usando Get-TasksData para obter o objeto completo
        $taskData = Get-TasksData -arquivo $arquivo

        if (-not $taskData) {
            Write-Host " [ERRO] Falha ao processar arquivo: $($arquivo.Name)" -ForegroundColor Red
            $falhas++
            continue
        }

        $taskName = $arquivo.Name -replace '\.md$', ''
        Write-Host "Criando: $taskName..." -NoNewline

        # Usa o objeto taskData que já tem todas as informações (body, labels, milestone, project)
        $result = Push-NewTask -repo $taskData.repo -title $taskData.title -body $taskData.body -assignee $taskData.assignee -labels $taskData.labels -milestone $taskData.milestone -project $taskData.project

        # Verifica se o comando foi executado com sucesso (exit code 0)
        if ($LASTEXITCODE -eq 0) {
            Write-Host " [OK] $progressBar $percent%" -ForegroundColor Green
            $criadas++
        } else {
            Write-Host " [ERRO] $progressBar $percent%" -ForegroundColor Red
            $falhas++
        }
    }

    return [PSCustomObject]@{
        Criadas = $criadas
        Falhas = $falhas
    }
}

function Update-TasksList {
    param([int]$limit = 0)

    # Usa a função Get-ListTaskInFolder para pegar a lista de arquivos
    $listTasksArquivos = Get-ListTaskInFolder -limit $limit


    if ($listTasksArquivos.Count -gt 0) {
        Write-Host "=== LISTA DE TASKS recebidas DA DOCUMENTAÇÃO ===" -ForegroundColor Cyan
        Write-Host "Total: $($listTasksArquivos.Count)" -ForegroundColor Gray
        Write-Host ""

    } else {
        Write-Host "  Lista vazia." -ForegroundColor Yellow
        return @()
    }

    # Busca tasks do GitHub usando função única
    $tasksGitHub = Get-TasksFromGitHub

    if ($tasksGitHub.Count -gt 0) {
        Write-Host "Total GITHUB tasks: $($tasksGitHub.Count)" -ForegroundColor Green
    } else {
        Write-Host "  Nenhuma task no GitHub." -ForegroundColor Yellow
    }




    Write-Host "=== LISTA DE TASKS A ENVIAR ===" -ForegroundColor Cyan

    # Compara listas e pega apenas tasks novas
    $newTasks = Get-NewTasks -listTasksArquivos $listTasksArquivos -tasksGitHub $tasksGitHub

    # Garante que é um array (mesmo quando há apenas 1 item)
    if ($newTasks -isnot [Array]) {
        $newTasks = @($newTasks)
    }
    if (-not $newTasks) {
        $newTasks = @()
    }

    Write-Host "Total: $($newTasks.Count)" -ForegroundColor Gray

    if ($newTasks.Count -eq 0) {
        Write-Host " >>> Nenhuma task nova para enviar. <<<" -ForegroundColor Yellow
        return @()
    }


    Write-Host "=== ENVIANDO NOVAS TASKS ===" -ForegroundColor Cyan
    $resultado = Uploading-NewTasks -newTasks $newTasks


    Write-Host "Tasks criadas: $($resultado.Criadas)" -ForegroundColor Green
    Write-Host "Falhas: $($resultado.Falhas)" -ForegroundColor $(if ($resultado.Falhas -gt 0) { "Red" } else { "Gray" })



    Write-Host ""
    Write-Host "=== EXECUÇÃO PARADA ===" -ForegroundColor Yellow

    return @()
}



# Atualiza tasks no GitHub
$tasksAdicionadas = Update-TasksList
