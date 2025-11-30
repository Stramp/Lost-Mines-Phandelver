# Script para deletar TODAS as issues permanentemente
# ATENÇÃO: Operação irreversível!

$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"

Write-Host "=== DELETANDO TODAS AS ISSUES ===" -ForegroundColor Red
Write-Host "ATENÇÃO: Esta operação é IRREVERSÍVEL!" -ForegroundColor Yellow
Write-Host ""

# 1. Lista todas as issues (limite alto para garantir)
Write-Host "Buscando todas as issues..." -ForegroundColor Cyan
$issues = & $ghPath issue list --repo $meuRepo --state all --limit 5000 --json number 2>&1 | ConvertFrom-Json

# 2. Loop para deletar uma por uma
if ($issues) {
    Write-Host "Encontradas $($issues.Count) issues. Iniciando deleção..." -ForegroundColor Yellow
    Write-Host ""
    
    $deleted = 0
    $failed = 0
    $total = $issues.Count
    $current = 0
    
    foreach ($item in $issues) {
        $current++
        $percent = [math]::Round(($current / $total) * 100)
        
        # Calcula barra de progresso (20 caracteres)
        $filled = [math]::Round(($current / $total) * 20)
        $empty = 20 - $filled
        $progressBar = "[" + ("|" * $filled) + ("_" * $empty) + "]"
        
        Write-Host "Deletando issue #$($item.number)..." -NoNewline
        $result = & $ghPath issue delete $item.number --repo $meuRepo --yes 2>&1
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host " [OK] $progressBar $percent%" -ForegroundColor Green
            $deleted++
        } else {
            Write-Host " [ERRO] $progressBar $percent%" -ForegroundColor Red
            Write-Host "  Detalhe: $result" -ForegroundColor Yellow
            $failed++
        }
    }
    
    Write-Host ""
    Write-Host "=== RESULTADO ===" -ForegroundColor Cyan
    Write-Host "Deletadas: $deleted" -ForegroundColor Green
    Write-Host "Falhas: $failed" -ForegroundColor $(if ($failed -gt 0) { "Red" } else { "Gray" })
    Write-Host "Total processadas: $($issues.Count)" -ForegroundColor Gray
} else {
    Write-Host "Nenhuma task encontrada para deletar." -ForegroundColor Gray
}

Write-Host ""
Write-Host "=== CONCLUÍDO ===" -ForegroundColor Cyan

