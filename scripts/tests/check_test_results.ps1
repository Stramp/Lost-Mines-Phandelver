# Script para verificar resultados dos testes
Start-Sleep -Seconds 8

$logs = Get-ChildItem "Saved\Logs" -Filter "*.log" | Sort-Object LastWriteTime -Descending | Select-Object -First 1

if ($logs) {
    Write-Host "Log mais recente: $($logs.Name)"
    Write-Host ""
    Write-Host "=== Resultados dos Testes ==="
    Get-Content $logs.FullName -Tail 400 | Select-String -Pattern "Test Completed.*Result" | Select-Object -Last 10
    Write-Host ""
    Write-Host "=== Resumo ==="
    $content = Get-Content $logs.FullName
    $success = ($content | Select-String -Pattern "Test Completed.*Result=\{Success\}").Count
    $fail = ($content | Select-String -Pattern "Test Completed.*Result=\{Fail\}").Count
    Write-Host "Sucesso: $success"
    Write-Host "Falha: $fail"
    Write-Host ""
    
    if ($fail -gt 0) {
        Write-Host "=== Teste que falhou ==="
        Get-Content $logs.FullName -Tail 500 | Select-String -Pattern "Test Completed.*Result=\{Fail\}" -Context 0,3 | Select-Object -Last 1
        Write-Host ""
        Write-Host "=== Verificando se é Warning ou Error ==="
        Get-Content $logs.FullName -Tail 500 | Select-String -Pattern "Warning.*Referências|Error.*Referências" | Select-Object -Last 3
    } else {
        Write-Host "✅ Todos os testes passaram!"
    }
} else {
    Write-Host "Nenhum log encontrado"
}

