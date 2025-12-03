# Script para verificar resultados de testes
$logPath = "Saved\Logs\MyProject2.log"

Write-Host "Verificando log: $logPath"
Write-Host ""

if (Test-Path $logPath) {
    Write-Host "=== TESTES ENCONTRADOS NO LOG ==="
    Write-Host ""
    
    $logContent = Get-Content $logPath
    
    # Procura por resultados
    $testResults = $logContent | Select-String -Pattern "Test Completed|Result="
    $successCount = ($logContent | Select-String -Pattern "Result=\{Success\}").Count
    $failedCount = ($logContent | Select-String -Pattern "Result=\{Failed\}").Count
    
    # Procura por total de testes
    $testQueueLine = $logContent | Select-String -Pattern "tests performed"
    $totalTests = 0
    if ($testQueueLine) {
        $match = [regex]::Match($testQueueLine.Line, "(\d+)\s+tests performed")
        if ($match.Success) {
            $totalTests = [int]$match.Groups[1].Value
        }
    }
    
    Write-Host "Sucesso: $successCount"
    Write-Host "Falha: $failedCount"
    Write-Host "Total: $totalTests"
    Write-Host ""
    
    # Mostra últimos resultados
    Write-Host "=== ÚLTIMOS 20 RESULTADOS ==="
    $testResults | Select-Object -Last 20 | ForEach-Object {
        if ($_.Line -match "Result=\{Success\}") {
            Write-Host "✅ $($_.Line)" -ForegroundColor Green
        } elseif ($_.Line -match "Result=\{Failed\}") {
            Write-Host "❌ $($_.Line)" -ForegroundColor Red
        } else {
            Write-Host "   $($_.Line)"
        }
    }
} else {
    Write-Host "Log não encontrado em $logPath"
    Write-Host ""
    Write-Host "Procurando logs recentes:"
    Get-ChildItem "Saved\Logs" -Filter "*.log" -ErrorAction SilentlyContinue | 
        Sort-Object LastWriteTime -Descending | 
        Select-Object -First 5 | 
        ForEach-Object { 
            Write-Host "  $($_.Name) - $($_.LastWriteTime)"
        }
}
