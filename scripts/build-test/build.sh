#!/bin/bash
# Script para compilar o projeto Unreal Engine (Git Bash)
# Uso: ./build.sh [Configuration]
# Configurações: Development (padrão), DebugGame, Test, Shipping

UE_PATH="/c/Program Files/Epic Games/UE_5.7"
PROJECT="F:\UNREAL GAME\MyProject2\MyProject2.uproject"
CONFIGURATION="${1:-Development}"

echo "========================================"
echo "Compilando MyProject2"
echo "========================================"
echo "Configuração: $CONFIGURATION"
echo ""

"$UE_PATH/Engine/Build/BatchFiles/RunUBT.sh" MyProject2Editor Win64 "$CONFIGURATION" -Project="$PROJECT" -TargetType=Editor -WaitMutex -FromMsBuild

if [ $? -ne 0 ]; then
    echo ""
    echo "❌ Erro na compilação!"
    exit 1
fi

echo ""
echo "✅ Compilação concluída com sucesso!"
echo ""

