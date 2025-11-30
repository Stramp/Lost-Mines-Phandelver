# PowerShell script to show Windows notification
# Uses MessageBox (always works, more visible than toast)
param(
    [string]$Title = "Git LFS Alert!",
    [string]$Message = "Storage usage is high!",
    [int]$Duration = 10
)

# Load Windows Forms for MessageBox
Add-Type -AssemblyName System.Windows.Forms

# Show MessageBox (always works, appears on top)
[System.Windows.Forms.MessageBox]::Show($Message, $Title, [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Warning)
