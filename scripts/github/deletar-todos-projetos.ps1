# --- SCRIPT: Deletar Todos os Projetos do GitHub ---
# ATENÇÃO: Esta operação é IRREVERSÍVEL!
# Encoding UTF-8 para evitar problemas com caracteres especiais
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

$ghPath = "C:\Program Files\GitHub CLI\gh.exe"

# Verifica se o CLI existe
if (-not (Test-Path $ghPath)) {
    Write-Host "ERRO: GitHub CLI não encontrado em: $ghPath" -ForegroundColor Red
    exit 1
}

Write-Host "=== DELETANDO TODOS OS PROJETOS ===" -ForegroundColor Red
Write-Host "ATENÇÃO: Esta operação é IRREVERSÍVEL!" -ForegroundColor Yellow
Write-Host "Executando automaticamente..." -ForegroundColor Yellow
Write-Host ""

Write-Host "--- PASSO 1: BUSCANDO PROJETOS ---" -ForegroundColor Cyan

# 1. Pega a lista de todos os projetos
$projectsJson = & $ghPath project list --owner "@me" --format json 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "ERRO ao buscar projetos: $projectsJson" -ForegroundColor Red
    exit 1
}

if (-not $projectsJson) {
    Write-Host "Nenhum projeto encontrado." -ForegroundColor Yellow
    exit 0
}

try {
    $jsonData = $projectsJson | ConvertFrom-Json

    # O JSON retorna um objeto com propriedade "projects" que é um array
    if ($jsonData.projects) {
        $projects = $jsonData.projects
    } elseif ($jsonData -is [array]) {
        $projects = $jsonData
    } else {
        $projects = @()
    }

    # Garante que é um array
    if (-not ($projects -is [array])) {
        if ($projects) {
            $projects = @($projects)
        } else {
            $projects = @()
        }
    }

    if ($projects.Count -eq 0) {
        Write-Host "Nenhum projeto encontrado." -ForegroundColor Yellow
        exit 0
    }

    Write-Host "Encontrados $($projects.Count) projeto(s)." -ForegroundColor Yellow
    Write-Host ""

    # Lista os projetos que serão deletados
    Write-Host "Projetos que serão deletados:" -ForegroundColor Cyan
    foreach ($p in $projects) {
        $projectTitle = if ($p.title) { $p.title } else { "Sem título" }
        $projectUrl = if ($p.url) { $p.url } else { "N/A" }
        Write-Host "  - $projectTitle (ID: $($p.number), URL: $projectUrl)" -ForegroundColor Gray
    }
    Write-Host ""
    Write-Host "Iniciando deleção de $($projects.Count) projeto(s)..." -ForegroundColor Yellow
    Write-Host ""

    Write-Host "--- PASSO 2: DELETANDO PROJETOS ---" -ForegroundColor Yellow
    Write-Host ""

    # 2. Deleta um por um
    $deletados = 0
    $falhas = 0

    foreach ($p in $projects) {
        # Verifica se o projeto tem número válido
        if (-not $p.number -or $p.number -eq "") {
            Write-Host "Pulando projeto sem ID válido: $($p.title)" -ForegroundColor Yellow
            $falhas++
            continue
        }

        $projectTitle = if ($p.title) { $p.title } else { "Sem título" }
        Write-Host "Deletando projeto: $projectTitle (ID: $($p.number))..." -NoNewline

        # gh project delete não tem flag --yes, remove ele
        $result = & $ghPath project delete $p.number --owner "@me" 2>&1

        if ($LASTEXITCODE -eq 0) {
            Write-Host " [OK]" -ForegroundColor Green
            $deletados++
        } else {
            Write-Host " [ERRO]" -ForegroundColor Red
            Write-Host "  Detalhe: $result" -ForegroundColor Yellow
            $falhas++
        }
    }

    Write-Host ""
    Write-Host "=== RESULTADO ===" -ForegroundColor Cyan
    Write-Host "Projetos deletados: $deletados" -ForegroundColor Green
    Write-Host "Falhas: $falhas" -ForegroundColor $(if ($falhas -gt 0) { "Red" } else { "Gray" })
    Write-Host "Total processados: $($projects.Count)" -ForegroundColor Gray

} catch {
    Write-Host "ERRO ao processar projetos: $_" -ForegroundColor Red
    Write-Host "Resposta JSON: $projectsJson" -ForegroundColor Yellow
    exit 1
}

Write-Host ""
Write-Host "=== CONCLUÍDO ===" -ForegroundColor Cyan
