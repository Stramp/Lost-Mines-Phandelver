# Script para executar apenas o teste de RaceBonusMotor
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
$TestName = "MyProject2.CreateSheet.RaceBonusMotor"

Write-Host "========================================="
Write-Host "Executando: $TestName"
Write-Host "========================================="
Write-Host ""

# Limpa log
$logPath = "Saved\Logs\MyProject2.log"
if (Test-Path $logPath) {
    Remove-Item $logPath -Force -ErrorAction SilentlyContinue
}

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

# Aguarda um pouco para o log ser escrito
Start-Sleep -Seconds 5

# Verifica resultados
if (Test-Path $logPath) {
    $logContent = Get-Content $logPath -ErrorAction SilentlyContinue
    
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
    
    Write-Host "=== RESULTADOS ==="
    Write-Host "Sucesso: $successCount"
    Write-Host "Falha: $failedCount"
    Write-Host "Total: $totalTests"
    Write-Host ""
    
    if ($failedCount -eq 0 -and $successCount -gt 0) {
        Write-Host "✅ TODOS OS TESTES PASSARAM!" -ForegroundColor Green
    } elseif ($failedCount -gt 0) {
        Write-Host "❌ ALGUNS TESTES FALHARAM!" -ForegroundColor Red
        Write-Host ""
        Write-Host "Testes que falharam:"
        $logContent | Select-String -Pattern "Result=\{Failed\}" | ForEach-Object {
            if ($_.Line -match "Name=\{(.+?)\}") {
                Write-Host "  ❌ $($matches[1])" -ForegroundColor Red
            }
        }
    } else {
        Write-Host "⚠️ Nenhum teste executado ou log não contém resultados" -ForegroundColor Yellow
    }
    
    # Verifica se há erros de crash
    $crashErrors = $logContent | Select-String -Pattern "Fatal error|Null assigned|NotNull|Crash"
    if ($crashErrors) {
        Write-Host ""
        Write-Host "=== ERROS DE CRASH ENCONTRADOS ===" -ForegroundColor Red
        $crashErrors | Select-Object -Last 10 | ForEach-Object {
            Write-Host "  ❌ $($_.Line)" -ForegroundColor Red
        }
    }
    
    # Mostra últimos resultados
    Write-Host ""
    Write-Host "=== ÚLTIMOS 30 RESULTADOS ==="
    $logContent | Select-String -Pattern "Test Completed|Result=|RaceBonus" | Select-Object -Last 30 | ForEach-Object {
        if ($_.Line -match "Result=\{Success\}") {
            Write-Host "✅ $($_.Line)" -ForegroundColor Green
        } elseif ($_.Line -match "Result=\{Failed\}") {
            Write-Host "❌ $($_.Line)" -ForegroundColor Red
        } else {
            Write-Host "   $($_.Line)"
        }
    }
} else {
    Write-Host "❌ Log não encontrado em $logPath" -ForegroundColor Red
    Write-Host ""
    Write-Host "Procurando logs recentes:"
    Get-ChildItem "Saved\Logs" -Filter "*.log" -ErrorAction SilentlyContinue | 
        Sort-Object LastWriteTime -Descending | 
        Select-Object -First 3 | 
        ForEach-Object { 
            Write-Host "  $($_.Name) - $($_.LastWriteTime)"
        }
}

