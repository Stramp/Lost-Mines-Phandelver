#!/usr/bin/env python3
"""
Git LFS Usage Monitor for GitHub
Monitors Git LFS storage and bandwidth usage with visual alerts.

Usage:
    python scripts/check-git-lfs-usage.py

Requirements:
    pip install requests colorama
    pip install win10toast  # Optional: for Windows toast notifications

Configuration:
    Edit scripts/git-lfs-config.json to set your GitHub token and thresholds.
"""

import json
import os
import sys
import requests
from pathlib import Path

try:
    from colorama import init, Fore, Back, Style
    init(autoreset=True)
except ImportError:
    # Fallback if colorama not installed
    class Fore:
        RED = GREEN = YELLOW = BLUE = CYAN = RESET = ""
    class Back:
        RED = YELLOW = GREEN = RESET = ""
    class Style:
        BRIGHT = RESET = ""

# Windows Toast Notifications (using PowerShell - more reliable)
import subprocess
import platform

HAS_TOAST = platform.system() == "Windows"

# ============================================================================
# Configuration
# ============================================================================

SCRIPT_DIR = Path(__file__).parent.absolute()
CONFIG_FILE = SCRIPT_DIR / "git-lfs-config.json"
DEFAULT_CONFIG = {
    "github_token": "",
    "github_username": "",
    "alert_threshold_storage": 80,  # Alert at 80% storage usage
    "alert_threshold_bandwidth": 80,  # Alert at 80% bandwidth usage
    "warning_threshold_storage": 60,  # Warning at 60% storage usage
    "warning_threshold_bandwidth": 60,  # Warning at 60% bandwidth usage
    "free_plan_storage_gb": 1.0,  # Free plan: 1 GB storage
    "free_plan_bandwidth_gb": 1.0  # Free plan: 1 GB bandwidth/month
}

# ============================================================================
# Helper Functions
# ============================================================================

def load_config():
    """Load configuration from JSON file or create default."""
    if CONFIG_FILE.exists():
        try:
            with open(CONFIG_FILE, 'r', encoding='utf-8') as f:
                config = json.load(f)
                # Merge with defaults to ensure all keys exist
                return {**DEFAULT_CONFIG, **config}
        except json.JSONDecodeError:
            print(f"{Fore.RED}Error: Invalid JSON in {CONFIG_FILE}")
            return DEFAULT_CONFIG
    else:
        # Create default config file
        with open(CONFIG_FILE, 'w', encoding='utf-8') as f:
            json.dump(DEFAULT_CONFIG, f, indent=2)
        print(f"{Fore.YELLOW}Created default config file: {CONFIG_FILE}")
        print(f"{Fore.YELLOW}Please edit it and add your GitHub token and username.")
        return DEFAULT_CONFIG

def format_bytes(bytes_value):
    """Format bytes to human-readable format."""
    for unit in ['B', 'KB', 'MB', 'GB', 'TB']:
        if bytes_value < 1024.0:
            return f"{bytes_value:.2f} {unit}"
        bytes_value /= 1024.0
    return f"{bytes_value:.2f} PB"

def format_gb(gb_value):
    """Format GB to readable format."""
    if gb_value < 1.0:
        return f"{gb_value * 1024:.2f} MB"
    return f"{gb_value:.2f} GB"

def show_windows_notification(title, message, duration=10):
    """Show Windows toast notification using PowerShell script (native, reliable)."""
    if not HAS_TOAST:
        return False

    try:
        # Use PowerShell script file for reliable notifications
        script_path = SCRIPT_DIR / "show-toast.ps1"

        if not script_path.exists():
            return False

        # Escape message for PowerShell (replace % with %% to avoid issues)
        safe_title = title.replace('"', '`"').replace('%', '%%')
        safe_message = message.replace('"', '`"').replace('%', '%%')

        subprocess.run(
            [
                "powershell",
                "-ExecutionPolicy", "Bypass",
                "-File", str(script_path),
                "-Title", safe_title,
                "-Message", safe_message,
                "-Duration", str(duration)
            ],
            capture_output=True,
            timeout=5,
            check=False
        )
        return True
    except Exception:
        # Silently fail if notification doesn't work
        return False

def print_progress_bar(percentage, width=50, label=""):
    """Print a colored progress bar."""
    filled = int(width * percentage / 100)
    # Use ASCII characters for Windows compatibility
    bar = '#' * filled + '-' * (width - filled)

    if percentage >= 90:
        color = Fore.RED + Style.BRIGHT
    elif percentage >= 70:
        color = Fore.YELLOW + Style.BRIGHT
    else:
        color = Fore.GREEN

    print(f"{label}{color}[{bar}]{Style.RESET_ALL} {percentage:.1f}%")

def get_local_lfs_usage(config, username):
    """Get local Git LFS file sizes as fallback when API is unavailable."""
    import subprocess
    import os

    try:
        # Get current directory (should be project root)
        project_root = os.getcwd()

        # Run git lfs ls-files to get LFS file info
        result = subprocess.run(
            ['git', 'lfs', 'ls-files'],
            cwd=project_root,
            capture_output=True,
            text=True,
            timeout=10
        )

        if result.returncode != 0:
            return None

        # Parse output to calculate total size
        total_bytes = 0
        file_count = 0

        for line in result.stdout.strip().split('\n'):
            if line:
                # Format: OID -a- 12345 filename
                parts = line.split()
                if len(parts) >= 3:
                    try:
                        size = int(parts[2])
                        total_bytes += size
                        file_count += 1
                    except (ValueError, IndexError):
                        continue

        total_gb = total_bytes / (1024 ** 3)

        return {
            'storage_used_gb': total_gb,
            'storage_limit_gb': config.get('free_plan_storage_gb', 1.0),
            'bandwidth_used_gb': 0,  # Can't determine bandwidth from local files
            'bandwidth_limit_gb': config.get('free_plan_bandwidth_gb', 1.0),
            'username': username,
            'is_local': True,
            'file_count': file_count
        }
    except Exception as e:
        print(f"{Fore.YELLOW}Warning: Could not calculate local LFS usage: {e}")
        return None

def get_github_lfs_usage(config):
    """Get Git LFS usage from GitHub API."""
    token = config.get('github_token', '').strip()
    username = config.get('github_username', '').strip()

    if not token:
        print(f"{Fore.RED}Error: GitHub token not configured in {CONFIG_FILE}")
        print(f"{Fore.YELLOW}Get your token from: https://github.com/settings/tokens")
        return None

    if not username:
        print(f"{Fore.YELLOW}Warning: GitHub username not configured. Trying to get from API...")

    headers = {
        'Authorization': f'token {token}',
        'Accept': 'application/vnd.github.v3+json',
    }

    # Try to get user info first
    if not username:
        try:
            user_response = requests.get('https://api.github.com/user', headers=headers, timeout=10)
            if user_response.status_code == 200:
                username = user_response.json().get('login', '')
        except Exception as e:
            print(f"{Fore.YELLOW}Warning: Could not get username from API: {e}")

    # Get billing info (requires token with billing scope)
    # Note: For personal accounts, try the billing endpoint
    # For organizations, use: /orgs/{org}/settings/billing
    try:
        # Try personal account billing endpoint first
        billing_url = 'https://api.github.com/user/settings/billing'
        response = requests.get(billing_url, headers=headers, timeout=10)

        # If 404, the billing API might not be available for personal accounts
        # In that case, we'll use a workaround to estimate usage
        if response.status_code == 404:
            print(f"{Fore.YELLOW}Note: Billing API not available for personal accounts.")
            print(f"{Fore.YELLOW}GitHub billing info is only available via web interface:")
            print(f"{Fore.CYAN}  https://github.com/settings/billing")
            print(f"{Fore.YELLOW}For now, showing local LFS file sizes...")
            return get_local_lfs_usage(config, username)

        if response.status_code == 401:
            print(f"{Fore.RED}Error: Invalid token or missing 'read:org' permission")
            print(f"{Fore.YELLOW}Token needs 'read:org' scope for billing access")
            return None
        elif response.status_code == 403:
            print(f"{Fore.RED}Error: Token doesn't have billing access")
            print(f"{Fore.YELLOW}Token needs 'read:org' or 'admin:org' scope")
            return None
        elif response.status_code != 200:
            print(f"{Fore.RED}Error: GitHub API returned status {response.status_code}")
            print(f"Response: {response.text[:200]}")
            return None

        data = response.json()

        # Extract LFS data
        lfs_data = data.get('git_lfs', {})

        return {
            'storage_used_gb': lfs_data.get('total_gigabytes_bandwidth_used', 0),
            'storage_limit_gb': config.get('free_plan_storage_gb', 1.0),
            'bandwidth_used_gb': lfs_data.get('total_gigabytes_bandwidth_used', 0),
            'bandwidth_limit_gb': config.get('free_plan_bandwidth_gb', 1.0),
            'username': username,
            'is_local': False
        }

    except requests.exceptions.RequestException as e:
        print(f"{Fore.RED}Error connecting to GitHub API: {e}")
        return None

# ============================================================================
# Main Function
# ============================================================================

def main():
    """Main function to check and display Git LFS usage."""
    print(f"{Fore.CYAN}{Style.BRIGHT}{'='*60}")
    print(f"{Fore.CYAN}{Style.BRIGHT}Git LFS Usage Monitor")
    print(f"{Fore.CYAN}{Style.BRIGHT}{'='*60}{Style.RESET_ALL}\n")

    # Load configuration
    config = load_config()

    # Get usage data
    usage_data = get_github_lfs_usage(config)

    if not usage_data:
        print(f"\n{Fore.YELLOW}Could not retrieve usage data.")
        print(f"{Fore.YELLOW}Please check your token and permissions.")
        sys.exit(1)

    # Calculate percentages
    storage_used = usage_data['storage_used_gb']
    storage_limit = usage_data['storage_limit_gb']
    storage_percentage = (storage_used / storage_limit * 100) if storage_limit > 0 else 0

    bandwidth_used = usage_data['bandwidth_used_gb']
    bandwidth_limit = usage_data['bandwidth_limit_gb']
    bandwidth_percentage = (bandwidth_used / bandwidth_limit * 100) if bandwidth_limit > 0 else 0

    # Display results
    is_local = usage_data.get('is_local', False)
    username = usage_data.get('username', 'Unknown')

    if is_local:
        print(f"{Fore.CYAN}GitHub User: {Fore.WHITE}{username}")
        print(f"{Fore.YELLOW}[!] Using LOCAL LFS file sizes (GitHub API unavailable)")
        file_count = usage_data.get('file_count', 0)
        print(f"{Fore.YELLOW}   Files tracked: {file_count}")
        print(f"{Fore.YELLOW}   For accurate GitHub usage, check: https://github.com/settings/billing\n")
    else:
        print(f"{Fore.CYAN}GitHub User: {Fore.WHITE}{username}\n")

    # Storage usage
    print(f"{Fore.BLUE}{Style.BRIGHT}Storage Usage:{Style.RESET_ALL}")
    print(f"  Used: {format_gb(storage_used)} / {format_gb(storage_limit)}")
    print_progress_bar(storage_percentage, label="  ")

    # Bandwidth usage (only show if not local)
    if not is_local:
        print(f"\n{Fore.BLUE}{Style.BRIGHT}Bandwidth Usage (This Month):{Style.RESET_ALL}")
        print(f"  Used: {format_gb(bandwidth_used)} / {format_gb(bandwidth_limit)}")
        print_progress_bar(bandwidth_percentage, label="  ")
    else:
        print(f"\n{Fore.YELLOW}Bandwidth Usage: Not available (check GitHub web interface)")

    # Alerts
    print(f"\n{Fore.CYAN}{Style.BRIGHT}{'='*60}{Style.RESET_ALL}\n")

    alerts = []
    warnings = []

    # Check storage thresholds
    if storage_percentage >= config['alert_threshold_storage']:
        alerts.append(f"{Fore.RED}{Style.BRIGHT}[!] ALERT: Storage usage at {storage_percentage:.1f}%!")
    elif storage_percentage >= config['warning_threshold_storage']:
        warnings.append(f"{Fore.YELLOW}[!] Warning: Storage usage at {storage_percentage:.1f}%")

    # Check bandwidth thresholds (only if not local)
    if not is_local:
        if bandwidth_percentage >= config['alert_threshold_bandwidth']:
            alerts.append(f"{Fore.RED}{Style.BRIGHT}[!] ALERT: Bandwidth usage at {bandwidth_percentage:.1f}%!")
        elif bandwidth_percentage >= config['warning_threshold_bandwidth']:
            warnings.append(f"{Fore.YELLOW}[!] Warning: Bandwidth usage at {bandwidth_percentage:.1f}%")

    # Display alerts and warnings
    if alerts:
        print(f"{Back.RED}{Fore.WHITE}{Style.BRIGHT}  ALERTS  {Style.RESET_ALL}\n")
        for alert in alerts:
            # Remove emoji for Windows compatibility
            alert_text = alert.replace('⚠️', '[!]').replace('⚠', '[!]')
            print(f"  {alert_text}")
        print()

        # Show Windows toast notification for alerts (only alerts, not warnings)
        # Determine which alert triggered
        if storage_percentage >= config['alert_threshold_storage']:
            alert_message = f"Storage usage at {storage_percentage:.1f}%!"
            detail_message = f"Used: {format_gb(storage_used)} / {format_gb(storage_limit)}"
        elif not is_local and bandwidth_percentage >= config['alert_threshold_bandwidth']:
            alert_message = f"Bandwidth usage at {bandwidth_percentage:.1f}%!"
            detail_message = f"Used: {format_gb(bandwidth_used)} / {format_gb(bandwidth_limit)}"
        else:
            # Fallback (shouldn't happen, but just in case)
            alert_message = f"Storage: {storage_percentage:.1f}%"
            detail_message = f"Used: {format_gb(storage_used)} / {format_gb(storage_limit)}"

        show_windows_notification(
            "Git LFS Alert!",
            f"{alert_message}\n{detail_message}",
            duration=15
        )

    if warnings:
        print(f"{Back.YELLOW}{Fore.BLACK}{Style.BRIGHT}  WARNINGS  {Style.RESET_ALL}\n")
        for warning in warnings:
            # Remove emoji for Windows compatibility
            warning_text = warning.replace('⚠️', '[!]').replace('⚠', '[!]')
            print(f"  {warning_text}")
        print()

    if not alerts and not warnings:
        print(f"{Fore.GREEN}[OK] All usage levels are within safe limits.\n")

    # Recommendations
    if storage_percentage > 50 or bandwidth_percentage > 50:
        print(f"{Fore.CYAN}{Style.BRIGHT}Recommendations:{Style.RESET_ALL}")
        if storage_percentage > 50:
            print(f"  • Review and remove unused large files from Git history")
            print(f"  • Consider using .gitignore for temporary files")
            print(f"  • Optimize .gitattributes to track only essential files")
        if bandwidth_percentage > 50:
            print(f"  • Reduce frequency of large file updates")
            print(f"  • Use local branches for testing before pushing")
        print()

    # Exit code
    sys.exit(1 if alerts else 0)

if __name__ == '__main__':
    main()
