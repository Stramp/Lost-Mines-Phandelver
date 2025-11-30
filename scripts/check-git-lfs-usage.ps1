# Git LFS Usage Monitor for GitHub (PowerShell)
# Monitors Git LFS storage and bandwidth usage with visual alerts.
#
# Usage:
#   .\scripts\check-git-lfs-usage.ps1
#
# Requirements:
#   - PowerShell 5.1+ (Windows)
#   - GitHub Personal Access Token with 'read:org' scope
#
# Configuration:
#   Edit scripts/git-lfs-config.json to set your GitHub token and thresholds.

param(
    [string]$ConfigFile = "scripts\git-lfs-config.json"
)

# ============================================================================
# Configuration
# ============================================================================

$ErrorActionPreference = "Stop"

# Colors
function Write-ColorOutput($ForegroundColor, $Message) {
    $fc = $host.UI.RawUI.ForegroundColor
    $host.UI.RawUI.ForegroundColor = $ForegroundColor
    Write-Output $Message
    $host.UI.RawUI.ForegroundColor = $fc
}

function Format-Bytes {
    param([double]$Bytes)

    $units = @("B", "KB", "MB", "GB", "TB")
    $value = $Bytes
    $unitIndex = 0

    while ($value -ge 1024 -and $unitIndex -lt $units.Length - 1) {
        $value /= 1024
        $unitIndex++
    }

    return "{0:N2} {1}" -f $value, $units[$unitIndex]
}

function Format-GB {
    param([double]$GB)

    if ($GB -lt 1.0) {
        return "{0:N2} MB" -f ($GB * 1024)
    }
    return "{0:N2} GB" -f $GB
}

function Show-ProgressBar {
    param(
        [double]$Percentage,
        [int]$Width = 50,
        [string]$Label = ""
    )

    $filled = [math]::Floor($Width * $Percentage / 100)
    $empty = $Width - $filled

    $bar = "█" * $filled + "░" * $empty

    if ($Percentage -ge 90) {
        Write-ColorOutput "Red" "$Label[$bar] $([math]::Round($Percentage, 1))%"
    }
    elseif ($Percentage -ge 70) {
        Write-ColorOutput "Yellow" "$Label[$bar] $([math]::Round($Percentage, 1))%"
    }
    else {
        Write-ColorOutput "Green" "$Label[$bar] $([math]::Round($Percentage, 1))%"
    }
}

function Load-Config {
    param([string]$ConfigPath)

    $defaultConfig = @{
        github_token = ""
        github_username = ""
        alert_threshold_storage = 80
        alert_threshold_bandwidth = 80
        warning_threshold_storage = 60
        warning_threshold_bandwidth = 60
        free_plan_storage_gb = 1.0
        free_plan_bandwidth_gb = 1.0
    }

    if (Test-Path $ConfigPath) {
        try {
            $config = Get-Content $ConfigPath | ConvertFrom-Json
            # Merge with defaults
            foreach ($key in $defaultConfig.Keys) {
                if (-not $config.PSObject.Properties.Name -contains $key) {
                    $config | Add-Member -MemberType NoteProperty -Name $key -Value $defaultConfig[$key]
                }
            }
            return $config
        }
        catch {
            Write-ColorOutput "Red" "Error: Invalid JSON in $ConfigPath"
            return $defaultConfig
        }
    }
    else {
        # Create default config
        $defaultConfig | ConvertTo-Json -Depth 10 | Set-Content $ConfigPath
        Write-ColorOutput "Yellow" "Created default config file: $ConfigPath"
        Write-ColorOutput "Yellow" "Please edit it and add your GitHub token and username."
        return $defaultConfig
    }
}

function Get-GitHubLfsUsage {
    param(
        [PSCustomObject]$Config
    )

    $token = $Config.github_token.Trim()
    $username = $Config.github_username.Trim()

    if ([string]::IsNullOrEmpty($token)) {
        Write-ColorOutput "Red" "Error: GitHub token not configured in $ConfigFile"
        Write-ColorOutput "Yellow" "Get your token from: https://github.com/settings/tokens"
        return $null
    }

    $headers = @{
        "Authorization" = "token $token"
        "Accept" = "application/vnd.github.v3+json"
    }

    # Try to get username from API if not configured
    if ([string]::IsNullOrEmpty($username)) {
        try {
            $userResponse = Invoke-RestMethod -Uri "https://api.github.com/user" -Headers $headers -Method Get -ErrorAction Stop
            $username = $userResponse.login
        }
        catch {
            Write-ColorOutput "Yellow" "Warning: Could not get username from API: $_"
        }
    }

    # Get billing info
    try {
        $billingUrl = "https://api.github.com/user/settings/billing"
        $response = Invoke-RestMethod -Uri $billingUrl -Headers $headers -Method Get -ErrorAction Stop

        $lfsData = $response.git_lfs

        return @{
            storage_used_gb = if ($lfsData.total_gigabytes_bandwidth_used) { $lfsData.total_gigabytes_bandwidth_used } else { 0 }
            storage_limit_gb = $Config.free_plan_storage_gb
            bandwidth_used_gb = if ($lfsData.total_gigabytes_bandwidth_used) { $lfsData.total_gigabytes_bandwidth_used } else { 0 }
            bandwidth_limit_gb = $Config.free_plan_bandwidth_gb
            username = $username
        }
    }
    catch {
        $statusCode = $_.Exception.Response.StatusCode.value__
        if ($statusCode -eq 401) {
            Write-ColorOutput "Red" "Error: Invalid token or missing 'read:org' permission"
            Write-ColorOutput "Yellow" "Token needs 'read:org' scope for billing access"
        }
        elseif ($statusCode -eq 403) {
            Write-ColorOutput "Red" "Error: Token doesn't have billing access"
            Write-ColorOutput "Yellow" "Token needs 'read:org' or 'admin:org' scope"
        }
        else {
            Write-ColorOutput "Red" "Error connecting to GitHub API: $_"
        }
        return $null
    }
}

# ============================================================================
# Main
# ============================================================================

Write-ColorOutput "Cyan" "============================================================"
Write-ColorOutput "Cyan" "Git LFS Usage Monitor"
Write-ColorOutput "Cyan" "============================================================"
Write-Output ""

# Load configuration
$config = Load-Config -ConfigPath $ConfigFile

# Get usage data
$usageData = Get-GitHubLfsUsage -Config $config

if ($null -eq $usageData) {
    Write-Output ""
    Write-ColorOutput "Yellow" "Could not retrieve usage data."
    Write-ColorOutput "Yellow" "Please check your token and permissions."
    exit 1
}

# Calculate percentages
$storageUsed = $usageData.storage_used_gb
$storageLimit = $usageData.storage_limit_gb
$storagePercentage = if ($storageLimit -gt 0) { ($storageUsed / $storageLimit * 100) } else { 0 }

$bandwidthUsed = $usageData.bandwidth_used_gb
$bandwidthLimit = $usageData.bandwidth_limit_gb
$bandwidthPercentage = if ($bandwidthLimit -gt 0) { ($bandwidthUsed / $bandwidthLimit * 100) } else { 0 }

# Display results
Write-ColorOutput "Cyan" "GitHub User: $($usageData.username)"
Write-Output ""

# Storage usage
Write-ColorOutput "Blue" "Storage Usage:"
Write-Output "  Used: $(Format-GB $storageUsed) / $(Format-GB $storageLimit)"
Show-ProgressBar -Percentage $storagePercentage -Label "  "

# Bandwidth usage
Write-Output ""
Write-ColorOutput "Blue" "Bandwidth Usage (This Month):"
Write-Output "  Used: $(Format-GB $bandwidthUsed) / $(Format-GB $bandwidthLimit)"
Show-ProgressBar -Percentage $bandwidthPercentage -Label "  "

# Alerts
Write-Output ""
Write-ColorOutput "Cyan" "============================================================"
Write-Output ""

$alerts = @()
$warnings = @()

# Check storage thresholds
if ($storagePercentage -ge $config.alert_threshold_storage) {
    $alerts += "⚠️  ALERT: Storage usage at $([math]::Round($storagePercentage, 1))%!"
}
elseif ($storagePercentage -ge $config.warning_threshold_storage) {
    $warnings += "⚠️  Warning: Storage usage at $([math]::Round($storagePercentage, 1))%"
}

# Check bandwidth thresholds
if ($bandwidthPercentage -ge $config.alert_threshold_bandwidth) {
    $alerts += "⚠️  ALERT: Bandwidth usage at $([math]::Round($bandwidthPercentage, 1))%!"
}
elseif ($bandwidthPercentage -ge $config.warning_threshold_bandwidth) {
    $warnings += "⚠️  Warning: Bandwidth usage at $([math]::Round($bandwidthPercentage, 1))%"
}

# Display alerts and warnings
if ($alerts.Count -gt 0) {
    Write-ColorOutput "Red" "  ALERTS"
    Write-Output ""
    foreach ($alert in $alerts) {
        Write-ColorOutput "Red" "  $alert"
    }
    Write-Output ""
}

if ($warnings.Count -gt 0) {
    Write-ColorOutput "Yellow" "  WARNINGS"
    Write-Output ""
    foreach ($warning in $warnings) {
        Write-ColorOutput "Yellow" "  $warning"
    }
    Write-Output ""
}

if ($alerts.Count -eq 0 -and $warnings.Count -eq 0) {
    Write-ColorOutput "Green" "✓ All usage levels are within safe limits."
    Write-Output ""
}

# Recommendations
if ($storagePercentage -gt 50 -or $bandwidthPercentage -gt 50) {
    Write-ColorOutput "Cyan" "Recommendations:"
    if ($storagePercentage -gt 50) {
        Write-Output "  • Review and remove unused large files from Git history"
        Write-Output "  • Consider using .gitignore for temporary files"
        Write-Output "  • Optimize .gitattributes to track only essential files"
    }
    if ($bandwidthPercentage -gt 50) {
        Write-Output "  • Reduce frequency of large file updates"
        Write-Output "  • Use local branches for testing before pushing"
    }
    Write-Output ""
}

# Exit code
exit $(if ($alerts.Count -gt 0) { 1 } else { 0 })
