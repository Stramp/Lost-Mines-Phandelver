@echo off
REM Script rápido para executar testes sem abrir o editor
REM Baseado na documentação oficial da Epic Games
REM Uso: run_tests_quick.bat [test_filter]
REM Exemplo: run_tests_quick.bat MyProject2.Data.Tables.FeatDataTable
REM Sem filtro: roda todos os testes MyProject2

setlocal enabledelayedexpansion

set "UE_PATH=C:\Program Files\Epic Games\UE_5.7"
set "PROJECT_PATH=F:\UNREAL GAME\MyProject2\MyProject2.uproject"
set "TEST_FILTER=%1"
set "TEMP_LOG=%TEMP%\unreal_tests_quick_%RANDOM%.log"

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

REM Executa testes e captura output em arquivo temporário
"%UE_PATH%\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "%PROJECT_PATH%" ^
    -ExecCmds="Automation RunTests %TEST_FILTER%" ^
    -unattended ^
    -nopause ^
    -nullrhi ^
    -NoSound ^
    -NoSplash ^
    -testexit="Automation Test Queue Empty" ^
    -log ^
    -stdout > "%TEMP_LOG%" 2>&1

REM Extrai quantos testes foram encontrados/rodados da linha "Found X automation tests"
set /a TOTAL_RUN=0
for /f "tokens=4" %%a in ('findstr /C:"Found" /C:"automation tests" "%TEMP_LOG%"') do (
    set "TOTAL_RUN=%%a"
)

REM Se não encontrou na linha "Found", tenta contar pelos "Test Started"
if !TOTAL_RUN! EQU 0 (
    findstr /C:"Test Started" "%TEMP_LOG%" >nul
    if !errorlevel! equ 0 (
        for /f %%a in ('findstr /C:"Test Started" "%TEMP_LOG%"') do set /a TOTAL_RUN+=1
    )
)

REM Conta testes que passaram
set /a PASSED=0
findstr /C:"Test Completed. Result={Success}" "%TEMP_LOG%" >nul
if !errorlevel! equ 0 (
    for /f %%a in ('findstr /C:"Test Completed. Result={Success}" "%TEMP_LOG%"') do set /a PASSED+=1
)

REM Conta testes que falharam
set /a FAILED=0
findstr /C:"Test Completed. Result={Fail}" "%TEMP_LOG%" >nul
if !errorlevel! equ 0 (
    for /f %%a in ('findstr /C:"Test Completed. Result={Fail}" "%TEMP_LOG%"') do set /a FAILED+=1
)

REM Se TOTAL_RUN ainda for 0, usa PASSED + FAILED
if !TOTAL_RUN! EQU 0 (
    set /a TOTAL_RUN=!PASSED!+!FAILED!
)

REM Para o total no projeto, vamos usar o mesmo valor dos rodados por enquanto
REM (listar todos dobra o tempo de execução)
set /a TOTAL_IN_PROJECT=!TOTAL_RUN!

REM Mostra resumo
echo.
echo ========================================
echo 📊 Total de testes no projeto: !TOTAL_IN_PROJECT!
echo 🎯 Total de testes rodados: !TOTAL_RUN!
echo ✅ Passaram: !PASSED!
echo ========================================

if %FAILED% EQU 0 (
    echo.
    echo Logs salvos em: Saved\Logs\
    del "%TEMP_LOG%" >nul 2>&1
    exit /b 0
) else (
    echo.
    echo ❌ Lista de testes que falharam
    echo.

    REM Extrai e mostra nomes dos testes que falharam
    for /f "usebackq tokens=*" %%a in (`findstr /C:"Test Completed. Result={Fail}" "%TEMP_LOG%"`) do (
        REM Extrai nome do teste (procura Name={...} na linha)
        set "LINE=%%a"
        REM Procura por "Name={" e extrai o conteúdo até "}"
        call :extract_name "!LINE!"
    )
    goto :skip_extract

    :extract_name
    set "LINE=%~1"
    set "NAME_START=!LINE:*Name={=!"
    if not "!NAME_START!"=="!LINE!" (
        REM Encontrou Name={, agora extrai até }
        for /f "tokens=1 delims=}" %%b in ("!NAME_START!") do (
            set "TEST_NAME=%%b"
            REM Remove qualquer caractere { ou = do início
            :clean_name
            if "!TEST_NAME:~0,1!"=="{" (
                set "TEST_NAME=!TEST_NAME:~1!"
                goto clean_name
            )
            if "!TEST_NAME:~0,1!"=="=" (
                set "TEST_NAME=!TEST_NAME:~1!"
                goto clean_name
            )
            echo - !TEST_NAME!
        )
    )
    goto :eof

    :skip_extract
    echo.
    echo Logs salvos em: Saved\Logs\
    del "%TEMP_LOG%" >nul 2>&1
    exit /b 1
)
