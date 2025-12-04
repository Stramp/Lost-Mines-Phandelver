# Script para rodar testes do Unreal Engine
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
$TestName = "MyProject2.CreateSheet.RaceBonusMotor"

Write-Host "Executando TODOS os testes do projeto: $TestName"
Write-Host ""

# Remove arquivos de saída anteriores
if (Test-Path "test_output.txt") { Remove-Item "test_output.txt" -Force }
if (Test-Path "test_errors.txt") { Remove-Item "test_errors.txt" -Force }

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
) -NoNewWindow -Wait -PassThru -RedirectStandardOutput "test_output.txt" -RedirectStandardError "test_errors.txt"

Write-Host "Processo finalizado com código: $($process.ExitCode)"
Write-Host ""

# Aguarda um pouco para garantir que os arquivos foram escritos
Start-Sleep -Seconds 5

if (Test-Path "test_output.txt") {
    Write-Host "=== Saída dos Testes (últimas 200 linhas) ===" 
    $output = Get-Content "test_output.txt" -Tail 200
    $output | Select-String -Pattern "Test|Pass|Fail|Succeeded|Failed|PointBuy|Spec|Describe|It|Error|Warning" | Select-Object -Last 150
    Write-Host ""
    Write-Host "Total de linhas no arquivo: $((Get-Content 'test_output.txt').Count)"
}

if (Test-Path "test_errors.txt") {
    Write-Host ""
    Write-Host "=== Erros ===" 
    Get-Content "test_errors.txt" | Select-String -Pattern "Error|Fatal|Exception|Crash" | Select-Object -Last 50
}

# Verifica log do Unreal
$logPath = "Saved\Logs\MyProject2.log"
if (Test-Path $logPath) {
    Write-Host ""
    Write-Host "=== Log do Unreal (últimas 100 linhas relevantes) ===" 
    Get-Content $logPath -Tail 500 | Select-String -Pattern "Test|Pass|Fail|Succeeded|Failed|PointBuy|Spec|Describe|It|Automation|Error|Fatal" | Select-Object -Last 100
}

