@echo off
REM Script rápido para executar testes sem abrir o editor
REM Baseado na documentação oficial da Epic Games
REM Uso: run_tests_quick.bat [test_filter]
REM Exemplo: run_tests_quick.bat MyProject2.Data.Tables.FeatDataTable

setlocal

set "UE_PATH=C:\Program Files\Epic Games\UE_5.7"
set "PROJECT_PATH=F:\UNREAL GAME\MyProject2\MyProject2.uproject"
set "TEST_FILTER=%1"

if "%TEST_FILTER%"=="" (
    set "TEST_FILTER=MyProject2"
    echo Executando todos os testes MyProject2...
) else (
    echo Executando testes: %TEST_FILTER%
)

echo.
echo ========================================
echo Executando Testes Rápidos (Terminal)
echo ========================================
echo.
echo NOTA: A inicialização do Unreal Engine pode levar 1-2 minutos.
echo       Isso é normal - aguarde até ver os resultados dos testes.
echo.

REM Comando baseado na documentação oficial da Epic Games:
REM https://dev.epicgames.com/documentation/en-us/unreal-engine/write-cplusplus-tests-in-unreal-engine
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
    echo.
    echo Logs salvos em: Saved\Logs\
    exit /b 0
) else (
    echo.
    echo ========================================
    echo ❌ Alguns testes falharam!
    echo ========================================
    echo.
    echo Verifique os logs em: Saved\Logs\
    exit /b 1
)
