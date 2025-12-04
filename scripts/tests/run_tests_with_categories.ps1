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
# Função: Extrai issues e subcategorias dos fullTestPath
# ============================================================================
function Get-TestCategories {
    param($jsonContent)

    # Estrutura: Issues > Subcategorias > Testes
    # Exemplo: Issue-1.2 > FLogContext > [testes]
    $issues = @{}

    if ($jsonContent.tests) {
        foreach ($test in $jsonContent.tests) {
            $fullTestPath = $test.fullTestPath

            # Extrai issue e subcategoria do formato: "MyProject2.Logging.LoggingSystem.Issue-1.2/ FLogContext.nomeDoTeste"
            # Regex: captura "Issue-X.X" seguido de "/ " ou " " e depois o nome da subcategoria até o próximo ponto
            if ($fullTestPath -match "Issue-(\d+\.\d+)[/ ]+([^\.]+)\.?") {
                $issueNumber = "Issue-$($matches[1])"
                $subcategory = $matches[2].Trim()

                # Cria estrutura de issue se não existir
                if (-not $issues.ContainsKey($issueNumber)) {
                    $issues[$issueNumber] = @{
                        Name = $issueNumber
                        Subcategories = @{}
                        Count = 0
                        Success = 0
                        Failed = 0
                    }
                }

                # Cria subcategoria se não existir
                if (-not $issues[$issueNumber].Subcategories.ContainsKey($subcategory)) {
                    $issues[$issueNumber].Subcategories[$subcategory] = @{
                        Name = $subcategory
                        Count = 0
                        Success = 0
                        Failed = 0
                    }
                }

                # Conta testes
                $issues[$issueNumber].Count++
                $issues[$issueNumber].Subcategories[$subcategory].Count++

                if ($test.state -eq "Success") {
                    $issues[$issueNumber].Success++
                    $issues[$issueNumber].Subcategories[$subcategory].Success++
                } elseif ($test.state -eq "Fail") {
                    $issues[$issueNumber].Failed++
                    $issues[$issueNumber].Subcategories[$subcategory].Failed++
                }
            }
        }
    }

    return $issues
}

# ============================================================================
# Função: Exibe menu hierárquico de issues e subcategorias
# ============================================================================
function Select-Category {
    param($issues)

    Write-Host ""
    Write-Host "=== ISSUES DISPONÍVEIS ===" -ForegroundColor Cyan
    Write-Host ""

    $issueList = @()
    $index = 1

    # Opção "Todas"
    Write-Host "[0] Todas" -ForegroundColor Yellow
    $issueList += "Todas"

    # Ordena issues por número (1.2 antes de 1.3, etc.)
    $sortedIssues = $issues.Values | Sort-Object {
        if ($_.Name -match "Issue-(\d+)\.(\d+)") {
            $major = [int]$matches[1]
            $minor = [int]$matches[2]
            return $major * 1000 + $minor
        } else {
            return 99999
        }
    }

    # Mostra menu de issues
    foreach ($issue in $sortedIssues) {
        $status = ""
        if ($issue.Failed -gt 0) {
            $status = " [X] $($issue.Failed) falharam"
        }
        Write-Host "[$index] $($issue.Name) ($($issue.Count) testes$status)" -ForegroundColor $(if ($issue.Failed -gt 0) { "Red" } else { "Green" })
        $issueList += $issue.Name
        $index++
    }

    Write-Host ""
    $selectedIssueIndex = Read-Host "Escolha uma issue (número)"

    try {
        $selectedIssueIndex = [int]$selectedIssueIndex
        if ($selectedIssueIndex -lt 0 -or $selectedIssueIndex -ge $issueList.Count) {
            Write-Host "Opção inválida. Usando 'Todas'." -ForegroundColor Yellow
            return @{ Issue = "Todas"; Subcategory = "Todas" }
        }

        $selectedIssue = $issueList[$selectedIssueIndex]

        # Se escolheu "Todas", retorna
        if ($selectedIssue -eq "Todas") {
            return @{ Issue = "Todas"; Subcategory = "Todas" }
        }

        # Mostra subcategorias da issue selecionada
        $issueData = $issues[$selectedIssue]
        Write-Host ""
        Write-Host "=== SUBCATEGORIAS DE $selectedIssue ===" -ForegroundColor Cyan
        Write-Host ""

        $subcategoryList = @()
        $subIndex = 0

        # Opção "Todas" para subcategorias
        Write-Host "[$subIndex] Todas subcategorias" -ForegroundColor Yellow
        $subcategoryList += "Todas"
        $subIndex++

        # Ordena subcategorias alfabeticamente
        $sortedSubcategories = $issueData.Subcategories.Values | Sort-Object Name

        foreach ($subcategory in $sortedSubcategories) {
            $subStatus = ""
            if ($subcategory.Failed -gt 0) {
                $subStatus = " [X] $($subcategory.Failed) falharam"
            }
            Write-Host "[$subIndex] $($subcategory.Name) ($($subcategory.Count) testes$subStatus)" -ForegroundColor $(if ($subcategory.Failed -gt 0) { "Red" } else { "Green" })
            $subcategoryList += $subcategory.Name
            $subIndex++
        }

        Write-Host ""
        $selectedSubcategoryIndex = Read-Host "Escolha uma subcategoria (número)"

        try {
            $selectedSubcategoryIndex = [int]$selectedSubcategoryIndex
            if ($selectedSubcategoryIndex -ge 0 -and $selectedSubcategoryIndex -lt $subcategoryList.Count) {
                return @{
                    Issue = $selectedIssue
                    Subcategory = $subcategoryList[$selectedSubcategoryIndex]
                }
            } else {
                Write-Host "Opção inválida. Usando todas subcategorias." -ForegroundColor Yellow
                return @{ Issue = $selectedIssue; Subcategory = "Todas" }
            }
        } catch {
            Write-Host "Opção inválida. Usando todas subcategorias." -ForegroundColor Yellow
            return @{ Issue = $selectedIssue; Subcategory = "Todas" }
        }

    } catch {
        Write-Host "Opção inválida. Usando 'Todas'." -ForegroundColor Yellow
        return @{ Issue = "Todas"; Subcategory = "Todas" }
    }
}

# ============================================================================
# Função: Exibe resultados filtrados por issue e subcategoria
# ============================================================================
function Show-TestResults {
    param($jsonContent, $selection)

    $selectedIssue = $selection.Issue
    $selectedSubcategory = $selection.Subcategory

    Write-Host ""
    Write-Host "=== RESULTADOS DOS TESTES" -NoNewline
    if ($selectedIssue -ne "Todas") {
        Write-Host " ($selectedIssue" -NoNewline -ForegroundColor Cyan
        if ($selectedSubcategory -ne "Todas") {
            Write-Host " / $selectedSubcategory" -NoNewline -ForegroundColor Cyan
        }
        Write-Host ")" -NoNewline -ForegroundColor Cyan
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

            # Filtra por issue e subcategoria
            if ($selectedIssue -ne "Todas") {
                # Verifica se o teste pertence à issue selecionada
                if ($fullTestPath -notmatch "Issue-(\d+\.\d+)") {
                    continue
                }
                $testIssue = "Issue-$($matches[1])"
                if ($testIssue -ne $selectedIssue) {
                    continue
                }

                # Se subcategoria específica foi selecionada, filtra por ela
                if ($selectedSubcategory -ne "Todas") {
                    # Extrai subcategoria do fullTestPath: "Issue-X.X/ Subcategory.nomeDoTeste"
                    if ($fullTestPath -match "Issue-(\d+\.\d+)[/ ]+([^\.]+)\.?") {
                        $testSubcategory = $matches[2].Trim()
                        if ($testSubcategory -ne $selectedSubcategory) {
                            continue
                        }
                    } else {
                        continue
                    }
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

        # 2. Extrai issues e subcategorias e permite seleção hierárquica
        $issues = Get-TestCategories -jsonContent $jsonContent
        $selection = Select-Category -issues $issues

        # 3. Exibe resultados filtrados
        Show-TestResults -jsonContent $jsonContent -selection $selection

    } catch {
        Write-Host "Erro ao processar JSON: $_" -ForegroundColor Red
        Write-Host "Verificando se o arquivo existe e está acessível..." -ForegroundColor Gray
    }
} else {
    Write-Host "Arquivo de resultados não encontrado (POSSIVEL CRASH DO EDITOR): $TestResultsFile" -ForegroundColor Yellow
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

