# Script para executar todos os testes por categoria
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"

# Categorias de testes
$testCategories = @(
    "MyProject2.Utils",
    "MyProject2.CreateSheet.PointBuy",
    "MyProject2.CreateSheet.Multiclass",
    "MyProject2.CreateSheet.RaceBonus",
    "MyProject2.CreateSheet.Core",
    "MyProject2.CharacterCreation",
    "MyProject2.CharacterData",
    "MyProject2.Integration"
)

Write-Host "========================================="
Write-Host "Executando TODOS os testes por categoria"
Write-Host "========================================="
Write-Host ""

$results = @{}

foreach ($category in $testCategories) {
    Write-Host "----------------------------------------"
    Write-Host "Executando: $category"
    Write-Host "----------------------------------------"
    
    # Limpa log
    $logPath = "Saved\Logs\MyProject2.log"
    if (Test-Path $logPath) {
        Remove-Item $logPath -Force -ErrorAction SilentlyContinue
    }
    
    $process = Start-Process -FilePath $EditorPath -ArgumentList @(
        $ProjectPath,
        "-ExecCmds=Automation RunTests $category; Quit",
        "-unattended",
        "-nopause",
        "-testexit=Automation Test Queue Empty",
        "-log",
        "-NullRHI",
        "-NoSplash",
        "-Noshadercompile"
    ) -NoNewWindow -Wait -PassThru
    
    # Aguarda um pouco para o log ser escrito
    Start-Sleep -Seconds 2
    
    $successCount = 0
    $failedCount = 0
    $totalTests = 0
    
    if (Test-Path $logPath) {
        $logContent = Get-Content $logPath -ErrorAction SilentlyContinue
        $successCount = ($logContent | Select-String -Pattern "Result=\{Success\}").Count
        $failedCount = ($logContent | Select-String -Pattern "Result=\{Failed\}").Count
        
        # Tenta encontrar total de testes
        $testQueueLine = $logContent | Select-String -Pattern "tests performed"
        if ($testQueueLine) {
            $match = [regex]::Match($testQueueLine.Line, "(\d+)\s+tests performed")
            if ($match.Success) {
                $totalTests = [int]$match.Groups[1].Value
            }
        }
    }
    
    $results[$category] = @{
        Success = $successCount
        Failed = $failedCount
        Total = $totalTests
        ExitCode = $process.ExitCode
    }
    
    Write-Host "  Sucesso: $successCount"
    Write-Host "  Falha: $failedCount"
    Write-Host "  Total: $totalTests"
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

foreach ($category in $testCategories) {
    $result = $results[$category]
    $totalSuccess += $result.Success
    $totalFailed += $result.Failed
    $grandTotal += $result.Total
    
    $status = if ($result.Failed -eq 0) { "✅" } else { "❌" }
    Write-Host "$status $category : $($result.Success) sucesso, $($result.Failed) falha, $($result.Total) total"
}

Write-Host ""
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
}

