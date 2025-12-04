# Script para rodar testes do RaceBonusMotor
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
$TestName = "MyProject2.CreateSheet.RaceBonusMotor"

Write-Host "Executando testes: $TestName"
Write-Host ""

# Remove logs anteriores
if (Test-Path "Saved\Logs\MyProject2.log") { Remove-Item "Saved\Logs\MyProject2.log" -Force }

$process = Start-Process -FilePath $EditorPath -ArgumentList @(
    $ProjectPath,
    "-ExecCmds=Automation RunTests $TestName; Quit",
    "-unattended",
    "-nopause",
    "-testexit=Automation Test Queue Empty",
    "-log",
    "-NullRHI",
    "-NoSplash",
    "-Noshadercompile"
) -NoNewWindow -Wait -PassThru

Write-Host "Processo finalizado com código: $($process.ExitCode)"
Write-Host ""

# Aguarda um pouco para garantir que os arquivos foram escritos
Start-Sleep -Seconds 3

# Verifica log do Unreal
$logPath = "Saved\Logs\MyProject2.log"
if (Test-Path $logPath) {
    Write-Host "=== Resultados dos Testes ===" 
    Get-Content $logPath -Tail 500 | Select-String -Pattern "Test Completed.*Result" | Select-Object -Last 10
    Write-Host ""
    Write-Host "=== Resumo ==="
    $success = (Get-Content $logPath | Select-String -Pattern "Test Completed.*Result=\{Success\}").Count
    $fail = (Get-Content $logPath | Select-String -Pattern "Test Completed.*Result=\{Fail\}").Count
    Write-Host "Sucesso: $success"
    Write-Host "Falha: $fail"
}

