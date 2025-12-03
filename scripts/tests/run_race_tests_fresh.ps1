# Script para rodar testes do RaceBonusMotor com log novo
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
$TestName = "MyProject2.CreateSheet.RaceBonusMotor"

Write-Host "Rodando testes: $TestName"
Write-Host ""

# Remove logs antigos
Get-ChildItem "Saved\Logs" -Filter "*.log" | Where-Object { $_.LastWriteTime -lt (Get-Date).AddMinutes(-5) } | Remove-Item -Force -ErrorAction SilentlyContinue

$timestamp = Get-Date -Format "yyyyMMdd_HHmmss"
$logFile = "Saved\Logs\TestRun_$timestamp.log"

Write-Host "Log será salvo em: $logFile"
Write-Host ""

$process = Start-Process -FilePath $EditorPath -ArgumentList @(
    $ProjectPath,
    "-ExecCmds=Automation RunTests $TestName; Quit",
    "-unattended",
    "-nopause",
    "-testexit=Automation Test Queue Empty",
    "-log=$logFile",
    "-NullRHI",
    "-NoSplash",
    "-Noshadercompile"
) -NoNewWindow -Wait -PassThru

Write-Host "Processo finalizado com código: $($process.ExitCode)"
Write-Host ""

# Aguarda para garantir que o log foi escrito
Start-Sleep -Seconds 8

# Verifica o log gerado
if (Test-Path $logFile) {
    Write-Host "=== Log gerado: $logFile ==="
    Write-Host ""
    Write-Host "=== Resultados dos Testes ==="
    Get-Content $logFile -Tail 400 | Select-String -Pattern "Test Completed.*Result" | Select-Object -Last 10
    Write-Host ""
    Write-Host "=== Resumo ==="
    $content = Get-Content $logFile
    $success = ($content | Select-String -Pattern "Test Completed.*Result=\{Success\}").Count
    $fail = ($content | Select-String -Pattern "Test Completed.*Result=\{Fail\}").Count
    Write-Host "Sucesso: $success"
    Write-Host "Falha: $fail"
    Write-Host ""
    
    if ($fail -gt 0) {
        Write-Host "=== Teste que falhou ==="
        Get-Content $logFile -Tail 500 | Select-String -Pattern "Test Completed.*Result=\{Fail\}" -Context 0,2 | Select-Object -Last 1
        Write-Host ""
        Write-Host "=== Verificando Warning vs Error ==="
        Get-Content $logFile -Tail 500 | Select-String -Pattern "Warning.*Referências|Error.*Referências" | Select-Object -Last 3
    } else {
        Write-Host "✅ Todos os testes passaram!"
    }
} else {
    Write-Host "Log não encontrado. Verificando logs mais recentes..."
    Get-ChildItem "Saved\Logs" -Filter "*.log" | Sort-Object LastWriteTime -Descending | Select-Object -First 3 | ForEach-Object {
        Write-Host "$($_.Name) - $($_.LastWriteTime)"
    }
}

