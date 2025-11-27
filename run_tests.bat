@echo off
REM Script para executar testes automatizados do projeto
REM Uso: run_tests.bat [test_filter]
REM Exemplo: run_tests.bat MyProject2.Data.Tables.FeatDataTable

setlocal

set "UE_PATH=C:\Program Files\Epic Games\UE_5.7"
set "PROJECT_PATH=F:\UNREAL GAME\MyProject2\MyProject2.uproject"
set "TEST_FILTER=%1"

if "%TEST_FILTER%"=="" (
    set "TEST_FILTER=MyProject2"
    echo Running all MyProject2 tests...
) else (
    echo Running tests matching: %TEST_FILTER%
)

echo.
echo ========================================
echo Executando Testes Automatizados
echo ========================================
echo.

REM Comando baseado na documentação oficial da Epic Games
"%UE_PATH%\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "%PROJECT_PATH%" ^
    -ExecCmds="Automation RunTests %TEST_FILTER%" ^
    -unattended ^
    -nopause ^
    -nullrhi ^
    -NoSound ^
    -NoSplash ^
    -testexit="Automation Test Queue Empty" ^
    -log ^
    -stdout

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo ✅ Todos os testes passaram!
    echo ========================================
    exit /b 0
) else (
    echo.
    echo ========================================
    echo ❌ Alguns testes falharam!
    echo ========================================
    exit /b 1
)
