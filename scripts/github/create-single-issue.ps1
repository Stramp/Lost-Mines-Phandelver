# --- SCRIPT: create-single-issue ---
# Cria uma única issue no GitHub com todos os parâmetros necessários
# Encoding UTF-8 para evitar problemas com caracteres especiais
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# ===== CONFIGURAÇÃO =====
$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"

# Projetos GitHub
$projetos = @{
    "Core Engineering" = @{ Nome = "Core Engineering" }
    "Narrative & Quest Design" = @{ Nome = "Narrative & Quest Design" }
    "Art & World Building" = @{ Nome = "Art & World Building" }
}

# ===== FUNÇÕES AUXILIARES =====

function Get-ProjectForIssue {
    param(
        [string[]]$labels, 
        [string]$categoria
    )
    
    $labelsLower = $labels | ForEach-Object { $_.ToLower() }
    $categoriaLower = if ($categoria) { $categoria.ToLower() } else { "" }
    
    $projectScores = @{
        "Core Engineering" = 0
        "Narrative & Quest Design" = 0
        "Art & World Building" = 0
    }
    
    foreach ($label in $labelsLower) {
        if ($label -match "^sys:|^type:") { $projectScores["Core Engineering"] += 3 }
        if ($label -match "infraestrutura|fundacao|data-tables|data-driven|criacao-personagem|combate|spellcasting|rest|save|load|persistencia|ui|ux|inventario") { 
            $projectScores["Core Engineering"] += 3 
        }
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

function Push-NewTask {
    param(
        [string]$repo,
        [string]$title,
        [string]$body,
        [string]$assignee,
        [string[]]$labels,
        [string]$milestone,
        [string]$project
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
    
    # Retorna o output do comando
    return $cmdOutput
}

# ===== FUNÇÃO PRINCIPAL =====

function Create-SingleIssue {
    param(
        [Parameter(Mandatory=$true)]
        [string]$Title,              # Título da issue (obrigatório)
        
        [Parameter(Mandatory=$false)]
        [string]$Body = "",           # Corpo/descrição da issue (markdown)
        
        [Parameter(Mandatory=$false)]
        [string[]]$Labels = @(),      # Array de labels
        
        [Parameter(Mandatory=$false)]
        [string]$Milestone = "",      # Milestone associado
        
        [Parameter(Mandatory=$false)]
        [string]$Categoria = "",      # Categoria (para determinar projeto automaticamente)
        
        [Parameter(Mandatory=$false)]
        [string]$Assignee = "@me",    # Responsável pela issue (padrão: eu)
        
        [Parameter(Mandatory=$false)]
        [string]$Project = ""         # Projeto GitHub (se não informado, determina automaticamente)
    )

    Write-Host "=== CRIANDO ISSUE ===" -ForegroundColor Cyan
    Write-Host ""

    # Valida título
    if (-not $Title) {
        Write-Host "  [ERRO] Título é obrigatório" -ForegroundColor Red
        return $null
    }

    # Determina projeto automaticamente se não foi informado
    if (-not $Project) {
        $selectedProjectName = Get-ProjectForIssue -labels $Labels -categoria $Categoria
        $Project = if ($selectedProjectName) { $projetos[$selectedProjectName].Nome } else { "Core Engineering" }
        Write-Host "  [INFO] Projeto determinado automaticamente: $Project" -ForegroundColor Gray
    }

    # Exibe informações
    Write-Host "  Título: $Title" -ForegroundColor White
    Write-Host "  Body: $($Body.Length) caracteres" -ForegroundColor Gray
    Write-Host "  Labels: $($Labels.Count) label(s)" -ForegroundColor Gray
    if ($Labels.Count -gt 0) {
        Write-Host "    - $($Labels -join ', ')" -ForegroundColor DarkGray
    }
    Write-Host "  Milestone: $(if ($Milestone) { $Milestone } else { '(nenhum)' })" -ForegroundColor Gray
    Write-Host "  Projeto: $Project" -ForegroundColor Gray
    Write-Host "  Assignee: $Assignee" -ForegroundColor Gray
    Write-Host ""

    # Cria a issue
    Write-Host "  Criando issue..." -ForegroundColor Yellow
    $cmdOutput = Push-NewTask -repo $meuRepo -title $Title -body $Body -assignee $Assignee -labels $Labels -milestone $Milestone -project $Project

    # Verifica se foi criada com sucesso
    if ($LASTEXITCODE -eq 0) {
        # Extrai a URL da issue criada
        $issueUrl = ($cmdOutput | Select-String -Pattern "https://github\.com/.*/issues/(\d+)").Matches.Value
        $issueNumber = ($issueUrl -match "issues/(\d+)$").Groups[1].Value
        
        Write-Host "  [OK] Issue criada com sucesso!" -ForegroundColor Green
        Write-Host ""
        Write-Host "=== RESULTADO ===" -ForegroundColor Cyan
        Write-Host "  Issue: #$issueNumber" -ForegroundColor White
        Write-Host "  URL: $issueUrl" -ForegroundColor White
        Write-Host "  Projeto: $Project" -ForegroundColor White
        Write-Host ""
        
        return @{
            Number = [int]$issueNumber
            Url = $issueUrl
            Project = $Project
        }
    } else {
        Write-Host "  [ERRO] Falha ao criar issue" -ForegroundColor Red
        Write-Host "  Erro: $cmdOutput" -ForegroundColor Red
        return $null
    }
}

# ===== EXECUÇÃO =====

# Se chamado com parâmetros, cria a issue
if ($args.Count -gt 0) {
    # Exemplo de uso via linha de comando:
    # .\create-single-issue.ps1 -Title "Minha Issue" -Body "Descrição" -Labels @("bug", "enhancement")
    
    Write-Host "Use a função Create-SingleIssue diretamente no PowerShell:" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Exemplo:" -ForegroundColor Cyan
    Write-Host '  Create-SingleIssue -Title "Refatorar scripts" -Body "Descrição da refatoração" -Labels @("refatoração", "enhancement") -Categoria "infraestrutura"' -ForegroundColor Gray
    Write-Host ""
    Write-Host "Ou importe o script e use:" -ForegroundColor Cyan
    Write-Host '  . .\create-single-issue.ps1' -ForegroundColor Gray
    Write-Host '  Create-SingleIssue -Title "Minha Issue" -Body "Descrição" -Labels @("bug")' -ForegroundColor Gray
} else {
    Write-Host "=== CREATE SINGLE ISSUE ===" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Este script fornece a função Create-SingleIssue para criar uma única issue no GitHub." -ForegroundColor White
    Write-Host ""
    Write-Host "Uso:" -ForegroundColor Yellow
    Write-Host '  . .\create-single-issue.ps1' -ForegroundColor Gray
    Write-Host '  Create-SingleIssue -Title "Título da Issue" -Body "Descrição" -Labels @("label1", "label2")' -ForegroundColor Gray
    Write-Host ""
    Write-Host "Parâmetros:" -ForegroundColor Yellow
    Write-Host "  -Title (obrigatório): Título da issue" -ForegroundColor Gray
    Write-Host "  -Body (opcional): Corpo/descrição da issue (markdown)" -ForegroundColor Gray
    Write-Host "  -Labels (opcional): Array de labels (ex: @('bug', 'enhancement'))" -ForegroundColor Gray
    Write-Host "  -Milestone (opcional): Milestone associado" -ForegroundColor Gray
    Write-Host "  -Categoria (opcional): Categoria para determinar projeto automaticamente" -ForegroundColor Gray
    Write-Host "  -Assignee (opcional): Responsável (padrão: '@me')" -ForegroundColor Gray
    Write-Host "  -Project (opcional): Projeto GitHub (se não informado, determina automaticamente)" -ForegroundColor Gray
    Write-Host ""
    Write-Host "Exemplos:" -ForegroundColor Yellow
    Write-Host '  # Issue simples' -ForegroundColor DarkGray
    Write-Host '  Create-SingleIssue -Title "Corrigir bug" -Body "Descrição do bug"' -ForegroundColor Gray
    Write-Host ""
    Write-Host '  # Issue com labels e categoria' -ForegroundColor DarkGray
    Write-Host '  Create-SingleIssue -Title "Nova feature" -Body "Descrição" -Labels @("enhancement", "feature") -Categoria "infraestrutura"' -ForegroundColor Gray
    Write-Host ""
    Write-Host '  # Issue completa' -ForegroundColor DarkGray
    Write-Host '  Create-SingleIssue -Title "Refatorar código" -Body "Descrição" -Labels @("refatoração") -Milestone "v1.0" -Categoria "código" -Project "Core Engineering"' -ForegroundColor Gray
}

