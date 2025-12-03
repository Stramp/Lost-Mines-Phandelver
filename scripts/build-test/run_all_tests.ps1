# Script para executar TODOS os testes do projeto
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"

Write-Host "========================================="
Write-Host "Executando TODOS os testes do projeto"
Write-Host "========================================="
Write-Host ""

# Limpa log anterior
$logPath = "Saved\Logs\MyProject2.log"
if (Test-Path $logPath) {
    Remove-Item $logPath -Force
}

$process = Start-Process -FilePath $EditorPath -ArgumentList @(
    $ProjectPath,
    "-ExecCmds=Automation RunTests MyProject2; Quit",
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

# Verifica log do Unreal
if (Test-Path $logPath) {
    Write-Host "========================================="
    Write-Host "RESUMO DOS TESTES (últimas 500 linhas)"
    Write-Host "========================================="
    Write-Host ""
    
    $logContent = Get-Content $logPath
    
    # Procura por resultados de testes
    $testResults = $logContent | Select-String -Pattern "Test Completed|Test Failed|tests performed|Test Queue Empty"
    
    Write-Host "=== RESULTADOS ENCONTRADOS ==="
    $testResults | ForEach-Object { Write-Host $_.Line }
    Write-Host ""
    
    # Conta sucessos e falhas
    $successCount = ($logContent | Select-String -Pattern "Result=\{Success\}").Count
    $failedCount = ($logContent | Select-String -Pattern "Result=\{Failed\}").Count
    
    Write-Host "=== ESTATÍSTICAS ==="
    Write-Host "Testes com Sucesso: $successCount"
    Write-Host "Testes com Falha: $failedCount"
    Write-Host ""
    
    # Mostra últimas linhas do log
    Write-Host "=== ÚLTIMAS 200 LINHAS DO LOG ==="
    $logContent | Select-Object -Last 200 | ForEach-Object { Write-Host $_ }
} else {
    Write-Host "Log do Unreal não encontrado em $logPath"
}

