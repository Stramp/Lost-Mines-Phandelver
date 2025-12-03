# Script para rodar testes com seleção de categorias
$EditorPath = "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor.exe"
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"

# Limpa a pasta de resultados antes de executar os testes
$TestResultsPath = "Saved\TestResults"
if (Test-Path $TestResultsPath) {
    Remove-Item -Path $TestResultsPath -Recurse -Force -ErrorAction SilentlyContinue
    Write-Host "Pasta de resultados limpa: $TestResultsPath" -ForegroundColor Gray
}

# ============================================================================
# Função: Executa todos os testes
# ============================================================================
function Run-AllTests {
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
}

# ============================================================================
# Função: Lê o JSON e mostra resumo total
# ============================================================================
function Get-TestResultsSummary {
    param($jsonContent)

    $successCount = 0
    $failedCount = 0

    if ($jsonContent.tests) {
        foreach ($test in $jsonContent.tests) {
            $state = $test.state
            if ($state -eq "Success") {
                $successCount++
            } elseif ($state -eq "Fail") {
                $failedCount++
            }
        }
    }

    return @{
        Total = $successCount + $failedCount
        Success = $successCount
        Failed = $failedCount
    }
}

# ============================================================================
# Função: Extrai categorias únicas dos fullTestPath
# ============================================================================
function Get-TestCategories {
    param($jsonContent)

    $categories = @{}

    if ($jsonContent.tests) {
        foreach ($test in $jsonContent.tests) {
            $fullTestPath = $test.fullTestPath

            # Extrai a categoria (ex: "MyProject2.CharacterCreation.Step1_ChooseRace")
            # Pega tudo até o último ponto antes do nome do teste
            if ($fullTestPath -match "^([^.]+(?:\.[^.]+)*)\.") {
                $category = $matches[1]

                # Conta testes por categoria
                if (-not $categories.ContainsKey($category)) {
                    $categories[$category] = @{
                        Name = $category
                        Count = 0
                        Success = 0
                        Failed = 0
                    }
                }

                $categories[$category].Count++
                if ($test.state -eq "Success") {
                    $categories[$category].Success++
                } elseif ($test.state -eq "Fail") {
                    $categories[$category].Failed++
                }
            }
        }
    }

    return $categories
}

# ============================================================================
# Função: Exibe menu de categorias e retorna a escolhida
# ============================================================================
function Select-Category {
    param($categories)

    Write-Host ""
    Write-Host "=== CATEGORIAS DISPONÍVEIS ===" -ForegroundColor Cyan
    Write-Host ""

    $categoryList = @()
    $index = 1

    # Opção "Todas"
    Write-Host "[0] Todas" -ForegroundColor Yellow
    $categoryList += "Todas"

    # Lista categorias
    foreach ($category in ($categories.Values | Sort-Object Name)) {
        $status = ""
        if ($category.Failed -gt 0) {
            $status = " [X] $($category.Failed) falharam"
        }
        Write-Host "[$index] $($category.Name) ($($category.Count) testes$status)" -ForegroundColor $(if ($category.Failed -gt 0) { "Red" } else { "Green" })
        $categoryList += $category.Name
        $index++
    }

    Write-Host ""
    $selectedIndex = Read-Host "Escolha uma categoria (número)"

    try {
        $selectedIndex = [int]$selectedIndex
        if ($selectedIndex -ge 0 -and $selectedIndex -lt $categoryList.Count) {
            return $categoryList[$selectedIndex]
        } else {
            Write-Host "Opção inválida. Usando 'Todas'." -ForegroundColor Yellow
            return "Todas"
        }
    } catch {
        Write-Host "Opção inválida. Usando 'Todas'." -ForegroundColor Yellow
        return "Todas"
    }
}

# ============================================================================
# Função: Exibe resultados filtrados por categoria
# ============================================================================
function Show-TestResults {
    param($jsonContent, $selectedCategory)

    Write-Host ""
    Write-Host "=== RESULTADOS DOS TESTES" -NoNewline
    if ($selectedCategory -ne "Todas") {
        Write-Host " ($selectedCategory)" -NoNewline -ForegroundColor Cyan
    }
    Write-Host " ===" -ForegroundColor Cyan
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

            # Filtra por categoria se necessário
            if ($selectedCategory -ne "Todas") {
                if ($fullTestPath -notlike "$selectedCategory.*") {
                    continue
                }
            }

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

            if (-not $hasEvents) {
                Write-Host "  (nenhum evento de erro ou warning)"
            }

            # Local
            Write-Host "Local: $fullTestPath"

            # Linha de separação inferior
            Write-Host ""
        }

        if ($successCount -eq 0 -and $failedCount -eq 0) {
            Write-Host "Nenhum resultado de teste encontrado" -ForegroundColor Yellow
        } else {
            Write-Host "=== RESUMO ===" -ForegroundColor Cyan
            Write-Host "Total: $($successCount + $failedCount) testes | [V] $successCount passaram | [X] $failedCount falharam" -ForegroundColor Cyan
        }
    } else {
        Write-Host "Estrutura JSON inválida: não encontrou array 'tests'" -ForegroundColor Yellow
    }

    Write-Host ""
    Write-Host "=== FIM DOS RESULTADOS ===" -ForegroundColor Cyan
}

# ============================================================================
# MAIN
# ============================================================================

# 1. Roda todos os testes
Run-AllTests

# 2. Lê o arquivo JSON
$TestResultsFile = "Saved\TestResults\index.json"

if (Test-Path $TestResultsFile) {
    try {
        $jsonContent = Get-Content $TestResultsFile -Raw -ErrorAction SilentlyContinue | ConvertFrom-Json

        # 1a. Mostra resumo total
        $summary = Get-TestResultsSummary -jsonContent $jsonContent
        Write-Host ""
        Write-Host "=== RESUMO GERAL ===" -ForegroundColor Cyan
        Write-Host "Total: $($summary.Total) testes | [V] $($summary.Success) passaram | [X] $($summary.Failed) falharam" -ForegroundColor Cyan

        # 2. Extrai categorias e permite seleção
        $categories = Get-TestCategories -jsonContent $jsonContent
        $selectedCategory = Select-Category -categories $categories

        # 3. Exibe resultados filtrados
        Show-TestResults -jsonContent $jsonContent -selectedCategory $selectedCategory

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

