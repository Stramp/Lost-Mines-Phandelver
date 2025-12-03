# Script para rodar testes individuais por task (1.1 até 3.1)
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
Write-Host "Executando Testes por Task (1.1 até 3.1)"
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

        $process = Start-Process -FilePath $EditorPath -ArgumentList @(
            $ProjectPath,
            "-ExecCmds=Automation RunTests $testSpec; Quit",
            "-unattended",
            "-nopause",
            "-testexit=Automation Test Queue Empty",
            "-log",
            "-NullRHI",
            "-NoSplash",
            "-Noshadercompile"
        ) -NoNewWindow -Wait -PassThru

        $exitCode = $process.ExitCode
        $successCount = 0
        $failureCount = 0
        $totalCount = 0

        # Aguarda um pouco para o log ser escrito
        Start-Sleep -Seconds 3

        if (Test-Path $CurrentLogFile) {
            $logContent = Get-Content $CurrentLogFile -ErrorAction SilentlyContinue
            $successCount = ($logContent | Select-String -Pattern "Result=\{Success\}").Count
            $failureCount = ($logContent | Select-String -Pattern "Result=\{Failed\}").Count

            # Procura por total de testes
            $testQueueLine = $logContent | Select-String -Pattern "tests performed"
            if ($testQueueLine) {
                $match = [regex]::Match($testQueueLine.Line, "(\d+)\s+tests performed")
                if ($match.Success) {
                    $totalCount = [int]$match.Groups[1].Value
                }
            }

            # Verifica se houve crash
            $crashErrors = $logContent | Select-String -Pattern "Fatal error|Null assigned|NotNull|Crash"
            if ($crashErrors -or $exitCode -ne 0) {
                $allPassed = $false
                Write-Host "    ❌ CRASH ou ERRO (Exit Code: $exitCode)" -ForegroundColor Red
            } elseif ($failureCount -gt 0) {
                $allPassed = $false
                Write-Host "    ❌ Falhas: $failureCount" -ForegroundColor Red
            } elseif ($successCount -gt 0 -and $failureCount -eq 0) {
                Write-Host "    ✅ Sucesso: $successCount" -ForegroundColor Green
            } else {
                Write-Host "    ⚠️ Nenhum resultado encontrado" -ForegroundColor Yellow
            }
        } else {
            $allPassed = $false
            Write-Host "    ❌ Log não encontrado (possível crash)" -ForegroundColor Red
        }

        $taskSuccess += $successCount
        $taskFailure += $failureCount
        $taskTotal += $totalCount
    }

    $status = if ($allPassed -and $taskTotal -gt 0) { "✅ PASSOU" } elseif ($taskTotal -eq 0) { "⚠️ SEM TESTES" } else { "❌ FALHOU" }

    $Results[$taskNumber] = @{
        "Status" = $status;
        "Success" = $taskSuccess;
        "Failure" = $taskFailure;
        "Total" = $taskTotal
    }

    Write-Host "  Status: $status" -ForegroundColor $(if ($status -eq "✅ PASSOU") { "Green" } elseif ($status -eq "⚠️ SEM TESTES") { "Yellow" } else { "Red" })
    Write-Host ""
}

Write-Host "========================================="
Write-Host "RESUMO FINAL"
Write-Host "========================================="
Write-Host ""

foreach ($taskNumber in $Results.Keys | Sort-Object) {
    $res = $Results[$taskNumber]
    $statusIcon = if ($res.Status -eq "✅ PASSOU") { "✅" } elseif ($res.Status -eq "⚠️ SEM TESTES") { "⚠️" } else { "❌" }
    Write-Host "$statusIcon Task $taskNumber : $($res.Status) ($($res.Success) sucesso, $($res.Failure) falha, $($res.Total) total)"
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

