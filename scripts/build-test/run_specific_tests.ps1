# Script para executar testes específicos conhecidos
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"

# Lista de testes específicos conhecidos
$testSuites = @(
    "MyProject2.Utils.PointBuyHelpers",
    "MyProject2.Utils.ACHelpers",
    "MyProject2.Utils.ComponentHelpers",
    "MyProject2.Utils.CalculationHelpers",
    "MyProject2.Utils.CharacterSheetHelpers",
    "MyProject2.CreateSheet.PointBuy.PointBuyMotor",
    "MyProject2.CreateSheet.PointBuy.PointBuyValidator",
    "MyProject2.CreateSheet.MulticlassMotor",
    "MyProject2.CreateSheet.RaceBonusMotor",
    "MyProject2.CreateSheet.Core.CharacterSheetCore"
)

Write-Host "========================================="
Write-Host "Executando Testes Específicos"
Write-Host "========================================="
Write-Host ""

$results = @{}

foreach ($testSuite in $testSuites) {
    Write-Host "----------------------------------------"
    Write-Host "Executando: $testSuite"
    Write-Host "----------------------------------------"
    
    # Limpa log
    $logPath = "Saved\Logs\MyProject2.log"
    if (Test-Path $logPath) {
        Remove-Item $logPath -Force -ErrorAction SilentlyContinue
    }
    
    $process = Start-Process -FilePath $EditorPath -ArgumentList @(
        $ProjectPath,
        "-ExecCmds=Automation RunTests $testSuite; Quit",
        "-unattended",
        "-nopause",
        "-testexit=Automation Test Queue Empty",
        "-log",
        "-NullRHI",
        "-NoSplash",
        "-Noshadercompile"
    ) -NoNewWindow -Wait -PassThru
    
    # Aguarda um pouco para o log ser escrito
    Start-Sleep -Seconds 3
    
    $successCount = 0
    $failedCount = 0
    $totalTests = 0
    $testDetails = @()
    
    if (Test-Path $logPath) {
        $logContent = Get-Content $logPath -ErrorAction SilentlyContinue
        
        # Procura por resultados de testes
        $testLines = $logContent | Select-String -Pattern "Test Completed|Test Failed"
        foreach ($line in $testLines) {
            if ($line.Line -match "Result=\{Success\}") {
                $successCount++
            } elseif ($line.Line -match "Result=\{Failed\}") {
                $failedCount++
                # Extrai nome do teste que falhou
                if ($line.Line -match "Name=\{(.+?)\}") {
                    $testDetails += "  ❌ $($matches[1])"
                }
            }
        }
        
        # Tenta encontrar total de testes
        $testQueueLine = $logContent | Select-String -Pattern "tests performed"
        if ($testQueueLine) {
            $match = [regex]::Match($testQueueLine.Line, "(\d+)\s+tests performed")
            if ($match.Success) {
                $totalTests = [int]$match.Groups[1].Value
            }
        }
    }
    
    $results[$testSuite] = @{
        Success = $successCount
        Failed = $failedCount
        Total = $totalTests
        ExitCode = $process.ExitCode
        Details = $testDetails
    }
    
    $status = if ($failedCount -eq 0) { "✅" } else { "❌" }
    Write-Host "  $status Sucesso: $successCount | Falha: $failedCount | Total: $totalTests"
    
    if ($testDetails.Count -gt 0) {
        Write-Host "  Testes que falharam:"
        $testDetails | ForEach-Object { Write-Host $_ }
    }
    Write-Host ""
}

# Resumo final
Write-Host "========================================="
Write-Host "RESUMO FINAL"
Write-Host "========================================="
Write-Host ""

$totalSuccess = 0
$totalFailed = 0
$grandTotal = 0
$failedSuites = @()

foreach ($testSuite in $testSuites) {
    $result = $results[$testSuite]
    $totalSuccess += $result.Success
    $totalFailed += $result.Failed
    $grandTotal += $result.Total
    
    $status = if ($result.Failed -eq 0 -and $result.Success -gt 0) { "✅" } elseif ($result.Failed -gt 0) { "❌" } else { "⚠️" }
    Write-Host "$status $testSuite"
    Write-Host "   Sucesso: $($result.Success) | Falha: $($result.Failed) | Total: $($result.Total)"
    
    if ($result.Failed -gt 0) {
        $failedSuites += $testSuite
    }
    Write-Host ""
}

Write-Host "========================================="
Write-Host "TOTAL GERAL"
Write-Host "========================================="
Write-Host "Sucesso: $totalSuccess"
Write-Host "Falha: $totalFailed"
Write-Host "Total: $grandTotal"
Write-Host ""

if ($totalFailed -eq 0) {
    Write-Host "✅ TODOS OS TESTES PASSARAM!" -ForegroundColor Green
} else {
    Write-Host "❌ ALGUNS TESTES FALHARAM!" -ForegroundColor Red
    Write-Host ""
    Write-Host "Suites com falhas:"
    $failedSuites | ForEach-Object { Write-Host "  - $_" }
}

