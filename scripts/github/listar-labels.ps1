# --- SCRIPT: Listar Labels do GitHub ---
# Encoding UTF-8 para evitar problemas com caracteres especiais
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"

Write-Host "=== LISTANDO LABELS DO GITHUB ===" -ForegroundColor Cyan
Write-Host "Repositório: $meuRepo" -ForegroundColor Gray
Write-Host ""

# Busca todas as labels
Write-Host "Buscando labels..." -ForegroundColor Yellow
$labelsJson = & $ghPath api repos/$meuRepo/labels 2>&1

if ($LASTEXITCODE -eq 0 -and $labelsJson) {
    try {
        $labels = $labelsJson | ConvertFrom-Json -ErrorAction SilentlyContinue

        # Garante que é um array
        if (-not ($labels -is [array])) {
            if ($labels) {
                $labels = @($labels)
            } else {
                $labels = @()
            }
        }

        if ($labels.Count -eq 0) {
            Write-Host "Nenhuma label encontrada no repositório." -ForegroundColor Yellow
            exit 0
        }

        # Ordena por nome
        $labelsOrdenadas = $labels | Sort-Object name

        Write-Host "Total de labels: $($labels.Count)" -ForegroundColor Green
        Write-Host ""
        Write-Host "NOME | COR" -ForegroundColor Cyan
        Write-Host ("-" * 50) -ForegroundColor Gray

        foreach ($label in $labelsOrdenadas) {
            Write-Host "$($label.name.PadRight(40)) | #$($label.color)" -ForegroundColor White
        }

        Write-Host ""
        Write-Host "=== RESUMO ===" -ForegroundColor Cyan
        Write-Host "Total: $($labels.Count) labels" -ForegroundColor Gray

    } catch {
        Write-Host "ERRO ao processar labels: $_" -ForegroundColor Red
        Write-Host "Resposta: $labelsJson" -ForegroundColor Yellow
    }
} else {
    Write-Host "ERRO ao buscar labels" -ForegroundColor Red
    Write-Host "Detalhe: $labelsJson" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "=== CONCLUÍDO ===" -ForegroundColor Cyan
