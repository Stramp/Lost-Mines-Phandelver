# Script para compilar o projeto Unreal Engine
# Uso: .\build.ps1 [Configuration]
# Configurações: Development (padrão), DebugGame, Test, Shipping
#
# Exemplo:
#   .\build.ps1              - Compila em Development
#   .\build.ps1 DebugGame    - Compila em DebugGame

param(
    [string]$Configuration = "Development"
)

$UEPath = "C:\Program Files\Epic Games\UE_5.7"
$ProjectPath = "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
$UBTPath = "$UEPath\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"

Write-Host "========================================"
Write-Host "Compilando MyProject2"
Write-Host "========================================"
Write-Host "Configuração: $Configuration"
Write-Host ""

if (-not (Test-Path $UBTPath)) {
    Write-Host "❌ UnrealBuildTool não encontrado em: $UBTPath" -ForegroundColor Red
    exit 1
}

if (-not (Test-Path $ProjectPath)) {
    Write-Host "❌ Projeto não encontrado em: $ProjectPath" -ForegroundColor Red
    exit 1
}

# Usa UnrealBuildTool.exe diretamente
& $UBTPath MyProject2Editor Win64 $Configuration $ProjectPath -waitmutex

if ($LASTEXITCODE -ne 0) {
    Write-Host ""
    Write-Host "❌ Erro na compilação! Código: $LASTEXITCODE" -ForegroundColor Red
    exit $LASTEXITCODE
}

Write-Host ""
Write-Host "✅ Compilação concluída com sucesso!" -ForegroundColor Green
Write-Host ""

