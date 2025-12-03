# Script para rodar testes individuais por task usando a forma correta do Unreal Engine
# Baseado na documentação oficial: https://dev.epicgames.com/documentation/en-us/unreal-engine/automation-test-framework-in-unreal-engine

$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
$LogDir = "Saved\Logs"
$CurrentLogFile = "$LogDir\MyProject2.log"

# Mapeamento de Tasks para Testes
$TaskTests = @{
    "1.1" = @()  # Setup Projeto - sem testes específicos
    "1.2" = @()  # Sistema de Logging MVP - sem testes específicos
    "1.3" = @("MyProject2.Utils.ComponentHelpers")  # Arquitetura de Componentes
    "1.4" = @("MyProject2.Utils.DataTableHelpers", "MyProject2.Utils.DataTableRowHandleHelpers")  # Data Tables Base
    "1.5" = @("MyProject2.CharacterSheetDataAssetHelpers", "MyProject2.Characters.Data.Loaders", "MyProject2.Characters.Data.Validators")  # Data Assets Base
    "1.6" = @("MyProject2.SaveGame.SaveGameHelpers")  # Sistema de Salvamento
    "1.7" = @("MyProject2.Characters.Components.Input.InputActionManagerComponent")  # Sistema de Input
    "1.9" = @("MyProject2.Characters.MovementHelpers")  # Sistema de Física
    "2.1" = @("MyProject2.CreateSheet.RaceBonusHelpers")  # Data Table de Raças
    "2.2" = @()  # Data Table de Classes - sem testes específicos
    "2.3" = @()  # Data Table de Backgrounds - sem testes específicos
    "2.4" = @()  # Data Table de Skills - sem testes específicos
    "2.5" = @("MyProject2.Data.Tables.ProficiencyDataTable")  # Data Table de Proficiências
    "2.6" = @()  # Data Table de Itens Básicos - sem testes específicos
    "3.1" = @("MyProject2.Utils.PointBuyHelpers", "MyProject2.CreateSheet.PointBuy.PointBuyMotor", "MyProject2.CreateSheet.PointBuy.PointBuyValidator")  # Point Buy MVP
    "3.2" = @("MyProject2.CreateSheet.RaceBonusMotor")  # Race Bonus MVP
    "3.5" = @("MyProject2.Utils.ACHelpers")  # AC Base MVP
}

$Results = @{}

Write-Host "========================================="
Write-Host "Executando Testes por Task (Forma Correta)"
Write-Host "Branch: feature/task-587-ac-base-mvp"
Write-Host "========================================="
Write-Host ""

foreach ($taskNumber in $TaskTests.Keys | Sort-Object) {
    $testSpecs = $TaskTests[$taskNumber]
    
    Write-Host "----------------------------------------"
    Write-Host "Task $taskNumber"
    Write-Host "----------------------------------------"
    
    if ($testSpecs.Count -eq 0) {
        Write-Host "  ⚠️ Sem testes específicos" -ForegroundColor Yellow
        $Results[$taskNumber] = @{
            "Status" = "Sem Testes";
            "Success" = 0;
            "Failure" = 0;
            "Total" = 0
        }
        Write-Host ""
        continue
    }
    
    $taskSuccess = 0
    $taskFailure = 0
    $taskTotal = 0
    $allPassed = $true
    
    foreach ($testSpec in $testSpecs) {
        Write-Host "  Executando: $testSpec" -ForegroundColor Cyan
        
        # Limpa log antes de cada execução
        if (Test-Path $CurrentLogFile) {
            Remove-Item $CurrentLogFile -Force -ErrorAction SilentlyContinue
        }
        
        # Forma correta de executar testes conforme documentação do Unreal Engine
        # Usa -Game para modo headless e -ExecCmds para executar comandos de automação
        $process = Start-Process -FilePath $EditorPath -ArgumentList @(
            $ProjectPath,
            "-Game",
            "-Unattended",
            "-NoPause",
            "-NullRHI",
            "-NoSplash",
            "-NoShaderCompile",
            "-Log",
            "-ExecCmds=Automation RunTests $testSpec; Quit"
        ) -NoNewWindow -Wait -PassThru -RedirectStandardOutput "test_output_temp.txt" -RedirectStandardError "test_error_temp.txt"
        
        $exitCode = $process.ExitCode
        
        # Aguarda mais tempo para garantir que o log foi escrito completamente
        Start-Sleep -Seconds 5
        
        $successCount = 0
        $failureCount = 0
        $totalCount = 0
        $crashDetected = $false
        
        if (Test-Path $CurrentLogFile) {
            $logContent = Get-Content $CurrentLogFile -ErrorAction SilentlyContinue -Raw
            
            # Padrões corretos para capturar resultados dos testes
            # Procura por linhas como: "Test: MyProject2.Utils.PointBuyHelpers.CalculatePointBuyCost.deve calcular custo correto para score 15 (9 pontos) - Result: Success"
            $successMatches = [regex]::Matches($logContent, "Result:\s*Success", [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)
            $failureMatches = [regex]::Matches($logContent, "Result:\s*Failed", [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)
            
            $successCount = $successMatches.Count
            $failureCount = $failureMatches.Count
            
            # Procura por resumo de testes executados
            $summaryMatch = [regex]::Match($logContent, "(\d+)\s+tests?\s+performed", [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)
            if ($summaryMatch.Success) {
                $totalCount = [int]$summaryMatch.Groups[1].Value
            }
            
            # Verifica se houve crash
            if ($logContent -match "Fatal error|Null assigned|NotNull|Crash|Assertion failed") {
                $crashDetected = $true
            }
            
            # Se não encontrou pelo padrão, tenta padrões alternativos
            if ($successCount -eq 0 -and $failureCount -eq 0) {
                # Tenta padrão alternativo: "Test Passed" ou "Test Failed"
                $successMatches2 = [regex]::Matches($logContent, "Test\s+Passed", [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)
                $failureMatches2 = [regex]::Matches($logContent, "Test\s+Failed", [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)
                
                if ($successMatches2.Count -gt 0 -or $failureMatches2.Count -gt 0) {
                    $successCount = $successMatches2.Count
                    $failureCount = $failureMatches2.Count
                }
            }
        }
        
        # Verifica arquivos de saída também
        if (Test-Path "test_output_temp.txt") {
            $outputContent = Get-Content "test_output_temp.txt" -ErrorAction SilentlyContinue -Raw
            if ($outputContent) {
                $outputSuccess = ([regex]::Matches($outputContent, "Result:\s*Success", [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)).Count
                $outputFailure = ([regex]::Matches($outputContent, "Result:\s*Failed", [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)).Count
                if ($outputSuccess -gt 0 -or $outputFailure -gt 0) {
                    $successCount = [Math]::Max($successCount, $outputSuccess)
                    $failureCount = [Math]::Max($failureCount, $outputFailure)
                }
            }
        }
        
        # Determina status
        if ($crashDetected -or ($exitCode -ne 0 -and $exitCode -ne -1)) {
            $allPassed = $false
            Write-Host "    ❌ CRASH ou ERRO (Exit Code: $exitCode)" -ForegroundColor Red
        } elseif ($failureCount -gt 0) {
            $allPassed = $false
            Write-Host "    ❌ Falhas: $failureCount, Sucessos: $successCount" -ForegroundColor Red
        } elseif ($successCount -gt 0 -and $failureCount -eq 0) {
            Write-Host "    ✅ Sucessos: $successCount" -ForegroundColor Green
        } elseif ($totalCount -gt 0) {
            Write-Host "    ⚠️ Total: $totalCount (sem detalhes de sucesso/falha)" -ForegroundColor Yellow
        } else {
            Write-Host "    ⚠️ Nenhum resultado encontrado" -ForegroundColor Yellow
        }
        
        $taskSuccess += $successCount
        $taskFailure += $failureCount
        if ($totalCount -gt 0) {
            $taskTotal = [Math]::Max($taskTotal, $totalCount)
        } else {
            $taskTotal += ($successCount + $failureCount)
        }
        
        # Limpa arquivos temporários
        if (Test-Path "test_output_temp.txt") { Remove-Item "test_output_temp.txt" -Force -ErrorAction SilentlyContinue }
        if (Test-Path "test_error_temp.txt") { Remove-Item "test_error_temp.txt" -Force -ErrorAction SilentlyContinue }
    }
    
    $status = if ($allPassed -and $taskTotal -gt 0) { "✅ PASSOU" } elseif ($taskTotal -eq 0) { "⚠️ SEM TESTES" } else { "❌ FALHOU" }
    
    $Results[$taskNumber] = @{
        "Status" = $status;
        "Success" = $taskSuccess;
        "Failure" = $taskFailure;
        "Total" = $taskTotal
    }
    
    Write-Host "  Status: $status (Sucessos: $taskSuccess, Falhas: $taskFailure, Total: $taskTotal)" -ForegroundColor $(if ($status -eq "✅ PASSOU") { "Green" } elseif ($status -eq "⚠️ SEM TESTES") { "Yellow" } else { "Red" })
    Write-Host ""
}

Write-Host "========================================="
Write-Host "RESUMO FINAL"
Write-Host "========================================="
Write-Host ""

foreach ($taskNumber in $Results.Keys | Sort-Object) {
    $res = $Results[$taskNumber]
    $statusIcon = if ($res.Status -eq "✅ PASSOU") { "✅" } elseif ($res.Status -eq "⚠️ SEM TESTES") { "⚠️" } else { "❌" }
    Write-Host "$statusIcon Task $taskNumber : $($res.Status) (Sucessos: $($res.Success), Falhas: $($res.Failure), Total: $($res.Total))"
}

Write-Host ""
Write-Host "========================================="
Write-Host "LISTA SIMPLES"
Write-Host "========================================="
Write-Host ""

foreach ($taskNumber in $Results.Keys | Sort-Object) {
    $res = $Results[$taskNumber]
    $status = if ($res.Status -eq "✅ PASSOU") { "✅ PASSOU" } elseif ($res.Status -eq "⚠️ SEM TESTES") { "⚠️ SEM TESTES" } else { "❌ FALHOU" }
    Write-Host "Task $taskNumber : $status"
}

