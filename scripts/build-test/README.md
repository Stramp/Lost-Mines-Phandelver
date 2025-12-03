# Scripts de Build e Teste

Esta pasta contém scripts para compilar e executar testes do projeto MyProject2.

## 📋 Scripts Disponíveis

### Build (Compilação)

#### `build.ps1` (PowerShell)
Script principal para compilar o projeto no Windows.

**Uso:**
```powershell
.\build.ps1 [Configuration]
```

**Configurações disponíveis:**
- `Development` (padrão) - Compilação de desenvolvimento
- `DebugGame` - Compilação com debug
- `Test` - Compilação para testes
- `Shipping` - Compilação para release

**Exemplos:**
```powershell
.\build.ps1              # Compila em Development
.\build.ps1 DebugGame    # Compila em DebugGame
```

**Nota:** Este script usa `UnrealBuildTool.exe` diretamente para compilação.

#### `build.sh` (Git Bash)
Versão do script de build para Git Bash/Linux.

**Uso:**
```bash
./build.sh [Configuration]
```

### Testes

#### `run_tests.bat` (Windows CMD)
Script principal para executar testes automatizados.

**Uso:**
```batch
run_tests.bat [test_filter]
```

**Exemplos:**
```batch
run_tests.bat                              # Roda todos os testes MyProject2
run_tests.bat MyProject2.Utils.ACHelpers  # Roda apenas testes ACHelpers
run_tests.bat MyProject2.Utils.PointBuy    # Roda apenas testes PointBuy
```

**Características:**
- Mostra resumo de testes (total, passaram, falharam)
- Lista testes que falharam
- Usa arquivo temporário para logs

#### `run_tests_quick.bat` (Windows CMD)
Versão rápida do script de testes (sem abrir editor).

**Uso:**
```batch
run_tests_quick.bat [test_filter]
```

**Diferenças do `run_tests.bat`:**
- Execução mais rápida
- Menos informações no output
- Ideal para execução frequente

#### `run_tests.ps1` (PowerShell)
Script PowerShell para executar testes específicos.

**Uso:**
```powershell
.\run_tests.ps1
```

**Nota:** Este script está configurado para um teste específico. Edite a variável `$TestName` para mudar.

#### `check_test_results.ps1` (PowerShell)
Script para verificar resultados de testes executados anteriormente.

**Uso:**
```powershell
.\check_test_results.ps1
```

### Testes Específicos

#### `run_race_tests_fresh.ps1`
Script para executar testes relacionados a Race Bonus.

#### `run_race_bonus_tests.ps1`
Script para executar testes específicos de Race Bonus Motor.

## 🚀 Fluxo de Trabalho Recomendado

### 1. Compilar o Projeto

**PowerShell:**
```powershell
cd scripts\build-test
.\build.ps1
```

**Git Bash:**
```bash
cd scripts/build-test
./build.sh
```

### 2. Executar Testes

**Todos os testes:**
```batch
run_tests.bat
```

**Testes específicos:**
```batch
run_tests.bat MyProject2.Utils.ACHelpers
run_tests.bat MyProject2.Utils.PointBuyHelpers
run_tests.bat MyProject2.Utils.CalculationHelpers
```

### 3. Verificar Resultados

Os resultados dos testes são exibidos no terminal e também salvos em:
- `Saved\Logs\MyProject2.log` - Log completo do Unreal Engine
- Arquivos temporários em `%TEMP%` (removidos automaticamente)

## 📝 Notas Importantes

### Compilação
- A primeira compilação pode levar vários minutos
- Compilações subsequentes são mais rápidas (incremental)
- Use `Development` para desenvolvimento diário
- Use `DebugGame` apenas quando precisar debuggar

### Testes
- A inicialização do Unreal Engine pode levar 1-2 minutos
- Isso é normal - aguarde até ver os resultados
- Testes são executados em modo headless (sem interface gráfica)
- Logs detalhados estão em `Saved\Logs\MyProject2.log`

### Filtros de Teste
Os filtros seguem o padrão do Unreal Engine Automation:
- `MyProject2` - Todos os testes do projeto
- `MyProject2.Utils` - Todos os testes de Utils
- `MyProject2.Utils.ACHelpers` - Testes específicos de ACHelpers
- `MyProject2.CreateSheet` - Todos os testes de CreateSheet

## 🔧 Troubleshooting

### Erro: "UnrealBuildTool não encontrado"
- Verifique se o Unreal Engine 5.7 está instalado em `C:\Program Files\Epic Games\UE_5.7`
- Verifique se o caminho `Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe` existe
- Ajuste a variável `UE_PATH` nos scripts se necessário

### Erro: "Projeto não encontrado"
- Verifique se o caminho do projeto está correto
- Ajuste a variável `PROJECT_PATH` nos scripts se necessário

### Testes não executam
- Certifique-se de que o projeto foi compilado primeiro
- Verifique se os testes existem no projeto
- Consulte o log em `Saved\Logs\MyProject2.log`

### Compilação muito lenta
- Primeira compilação sempre é lenta
- Use Unreal Build Accelerator (UBA) se disponível
- Considere usar `run_tests_quick.bat` para testes mais rápidos

## 📚 Referências

- [Unreal Engine Automation Testing](https://docs.unrealengine.com/5.0/en-US/automation-technical-guide-for-unreal-engine/)
- [Unreal Build Tool (UBT)](https://docs.unrealengine.com/5.0/en-US/using-the-unreal-build-tool-in-unreal-engine/)

---

**Última atualização:** 2025-01-25

