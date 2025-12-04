# Script simples para rodar testes
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe"
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"

# Limpa a pasta de resultados antes de executar os testes
$TestResultsPath = "Saved\TestResults"
if (Test-Path $TestResultsPath) {
    Remove-Item -Path $TestResultsPath -Recurse -Force -ErrorAction SilentlyContinue
    Write-Host "Pasta de resultados limpa: $TestResultsPath" -ForegroundColor Gray
}

Write-Host "Executando" -NoNewline

$arguments = "`"$ProjectPath`" -nosplash -Unattended -nopause -ExecCmds=`"Automation RunTests MyProject2; Quit`" -log -ReportOutputPath=`"F:\UNREAL GAME\MyProject2\Saved\TestResults`""
$process = Start-Process -FilePath $EditorPath -ArgumentList $arguments -PassThru

# Animação de loading enquanto o processo está rodando
$dots = @(".", "..", "...","....",".....","......",".......","........",".........",".........","..........","...........")
$counter = 0

while (-not $process.HasExited) {
    $dot = $dots[$counter % $dots.Length]
    # Limpa a linha e escreve a nova (espaços para apagar pontos anteriores)
    Write-Host ("`rExecutando" + $dot + (" " * 20)) -NoNewline
    $counter++
    Start-Sleep -Milliseconds 300
}


# Aguarda um pouco para o JSON ser escrito completamente
Start-Sleep -Seconds 5

# Lê o arquivo index.json dos resultados dos testes
$TestResultsFile = "Saved\TestResults\index.json"

if (Test-Path $TestResultsFile) {
    try {
        $jsonContent = Get-Content $TestResultsFile -Raw -ErrorAction SilentlyContinue | ConvertFrom-Json

        Write-Host ""
        Write-Host "=== RESULTADOS DOS TESTES ===" -ForegroundColor Cyan
        Write-Host ""

        $successCount = 0
        $failedCount = 0

        # Processa os testes do JSON
        if ($jsonContent.tests) {
            foreach ($test in $jsonContent.tests) {
                $testDisplayName = $test.testDisplayName
                $fullTestPath = $test.fullTestPath
                $state = $test.state
                $entries = $test.entries

                # Determina se passou ou falhou
                if ($state -eq "Success") {
                    $status = "[V] PASSOU"
                    $statusColor = "Green"
                    $successCount++
                } elseif ($state -eq "Fail") {
                    $status = "[X] FALHOU"
                    $statusColor = "Red"
                    $failedCount++
                } else {
                    continue
                }

                # Linha de separação superior
                Write-Host "============ $status ===============" -ForegroundColor $statusColor

                # Expectativa
                Write-Host "Expectativa: $testDisplayName"

                # EventLog (apenas Error e Warning, ignora Info)
                Write-Host "EventLog:"
                $hasEvents = $false
                if ($entries -and $entries.Count -gt 0) {
                    foreach ($entry in $entries) {
                        if ($entry.event -and $entry.event.message) {
                            $message = $entry.event.message
                            $eventType = $entry.event.type

                            # Filtra: mostra tudo EXCETO Info
                            if ($eventType -ne "Info") {
                                # Determina cor baseado no tipo
                                if ($eventType -eq "Error") {
                                    Write-Host "  >>> $message" -ForegroundColor Red
                                    $hasEvents = $true
                                } elseif ($eventType -eq "Warning") {
                                    Write-Host "  >>> $message" -ForegroundColor Yellow
                                    $hasEvents = $true
                                } else {
                                    # Outros tipos (não Info, não Error, não Warning)
                                    Write-Host "  >>> $message"
                                    $hasEvents = $true
                                }
                            }
                            # Ignora Info
                        }
                    }
                }



                # Local
                Write-Host "Local: $fullTestPath"

                # Linha de separação inferior
                Write-Host ""
            }

            if ($successCount -eq 0 -and $failedCount -eq 0) {
                Write-Host "Nenhum resultado de teste encontrado no JSON" -ForegroundColor Yellow
            } else {
                Write-Host "=== RESUMO ===" -ForegroundColor Cyan
                Write-Host "Total: $($successCount + $failedCount) testes | [V] $successCount passaram | [X] $failedCount falharam" -ForegroundColor Cyan
            }
        } else {
            Write-Host "Estrutura JSON inválida: não encontrou array 'tests'" -ForegroundColor Yellow
        }

        Write-Host ""
        Write-Host "=== FIM DOS RESULTADOS ===" -ForegroundColor Cyan
    } catch {
        Write-Host "Erro ao processar JSON: $_" -ForegroundColor Red
        Write-Host "Verificando se o arquivo existe e está acessível..." -ForegroundColor Gray
    }
} else {
    Write-Host "Arquivo de resultados não encontrado: $TestResultsFile" -ForegroundColor Yellow
    Write-Host "Verificando se a pasta existe..." -ForegroundColor Gray
    if (Test-Path "Saved\TestResults") {
        $jsonFiles = Get-ChildItem -Path "Saved\TestResults" -Filter "*.json" -ErrorAction SilentlyContinue
        if ($jsonFiles) {
            Write-Host "Arquivos .json encontrados:" -ForegroundColor Gray
            $jsonFiles | ForEach-Object { Write-Host "  $($_.Name)" -ForegroundColor Gray }
        } else {
            Write-Host "Nenhum arquivo .json encontrado na pasta" -ForegroundColor Gray
        }
    }
}

