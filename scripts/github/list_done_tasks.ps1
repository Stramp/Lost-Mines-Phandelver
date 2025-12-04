# Script para listar tasks concluídas do GitHub
Write-Host "Listando tasks concluídas (DONE)..." -ForegroundColor Cyan
Write-Host ""

# Lista todas as issues (abertas e fechadas)
$issues = gh issue list --state all --limit 200 --json number,title,state,body,labels | ConvertFrom-Json

# Filtra apenas as fechadas (DONE)
$doneIssues = $issues | Where-Object { $_.state -eq "closed" }

Write-Host "=== TASKS CONCLUÍDAS (DONE) ===" -ForegroundColor Green
Write-Host ""

$doneIssues | ForEach-Object {
    $branch = ""
    $issueNumber = $_.number
    
    # Busca branch no body com múltiplos padrões
    if ($_.body) {
        # Padrão 1: "Branch: feature/xxx" ou "Branch: `feature/xxx`"
        if ($_.body -match '(?i)Branch[:\s]+[`]?([^\s\n`]+)') {
            $branch = $matches[1]
        }
        # Padrão 2: "branch: feature/xxx"
        elseif ($_.body -match '(?i)branch[:\s]+([^\s\n]+)') {
            $branch = $matches[1]
        }
        # Padrão 3: Apenas "feature/xxx" no texto
        elseif ($_.body -match 'feature/([^\s\n`]+)') {
            $branch = "feature/$($matches[1])"
        }
        # Padrão 4: "Feature/xxx"
        elseif ($_.body -match 'Feature/([^\s\n`]+)') {
            $branch = "Feature/$($matches[1])"
        }
    }
    
    # Se não encontrou, busca na issue completa
    if ([string]::IsNullOrEmpty($branch) -or $branch -eq "**") {
        try {
            $fullIssue = gh issue view $issueNumber --json body | ConvertFrom-Json
            if ($fullIssue.body) {
                if ($fullIssue.body -match '(?i)Branch[:\s]+[`]?([^\s\n`]+)') {
                    $branch = $matches[1]
                } elseif ($fullIssue.body -match 'feature/([^\s\n`]+)') {
                    $branch = "feature/$($matches[1])"
                }
            }
        } catch {
            # Ignora erros
        }
    }
    
    # Remove backticks se houver
    $branch = $branch -replace '`', ''
    
    # Se ainda não encontrou, mostra como "N/A"
    if ([string]::IsNullOrEmpty($branch) -or $branch -eq "**") {
        $branch = "N/A"
    }
    
    Write-Host "#$issueNumber - $($_.title)" -ForegroundColor Yellow
    Write-Host "  Branch: $branch" -ForegroundColor Gray
    Write-Host ""
}

Write-Host "Total: $($doneIssues.Count) tasks concluídas" -ForegroundColor Green

