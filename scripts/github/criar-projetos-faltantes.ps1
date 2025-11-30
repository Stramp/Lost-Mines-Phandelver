# --- SCRIPT: criar-projetos-faltantes ---
# Encoding UTF-8 para evitar problemas com caracteres especiais
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

# ===== CONFIGURAÇÃO =====
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"

# Projetos a criar
$projetos = @(
    "Narrative & Quest Design",
    "Art & World Building"
)

# ===== FUNÇÃO PARA CRIAR PROJETO =====
function Create-Project {
    param([string]$projectName)

    Write-Host "Criando projeto: $projectName" -ForegroundColor Cyan

    # Verifica se já existe
    $projectsJson = & $ghPath project list --owner "@me" --format json 2>&1
    if ($LASTEXITCODE -eq 0) {
        try {
            $projects = $projectsJson | ConvertFrom-Json
            if ($projects.projects) {
                $existingProject = $projects.projects | Where-Object { $_.title -eq $projectName } | Sort-Object number -Descending | Select-Object -First 1
                if ($existingProject) {
                    Write-Host "  [AVISO] Projeto já existe: $($existingProject.url)" -ForegroundColor Yellow
                    return $existingProject.url
                }
            }
        } catch {
            Write-Host "  [AVISO] Erro ao verificar projetos existentes: $_" -ForegroundColor Yellow
        }
    }

    # Cria projeto
    $projectJson = & $ghPath project create --title $projectName --owner "@me" --format json 2>&1

    if ($LASTEXITCODE -eq 0) {
        try {
            $projectObj = $projectJson | ConvertFrom-Json
            Write-Host "  [OK] Projeto criado: $($projectObj.url)" -ForegroundColor Green
            return $projectObj.url
        } catch {
            Write-Host "  [ERRO] Erro ao processar JSON: $_" -ForegroundColor Red
            return $null
        }
    } else {
        Write-Host "  [ERRO] Falha ao criar projeto: $projectJson" -ForegroundColor Red
        return $null
    }
}

# ===== EXECUÇÃO =====
Write-Host "=== CRIANDO PROJETOS FALTANTES ===" -ForegroundColor Cyan
Write-Host ""

$criados = 0
$jaExistem = 0
$falhas = 0

foreach ($projetoNome in $projetos) {
    $resultado = Create-Project -projectName $projetoNome

    if ($resultado) {
        if ($resultado -match "já existe") {
            $jaExistem++
        } else {
            $criados++
        }
    } else {
        $falhas++
    }
    Write-Host ""
}

Write-Host "=== RESULTADO ===" -ForegroundColor Cyan
Write-Host "Criados: $criados" -ForegroundColor Green
Write-Host "Já existiam: $jaExistem" -ForegroundColor Yellow
Write-Host "Falhas: $falhas" -ForegroundColor $(if ($falhas -gt 0) { "Red" } else { "Gray" })
Write-Host ""
Write-Host "=== CONCLUÍDO ===" -ForegroundColor Cyan
