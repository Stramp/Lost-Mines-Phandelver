# 🧪 Como Executar os Testes

## ✅ Status

**Todos os 24 testes estão implementados e compilando corretamente!**

## 🚀 Métodos de Execução

### Método 1: Automation Tool no Editor (Recomendado) ⭐

1. **Abra o projeto no Unreal Editor**
2. **Window → Developer Tools → Automation Tool**
3. **Na aba "Tests":**
   - Filtre por `MyProject2` na busca
   - Você verá:
     - `MyProject2.Data.Tables.FeatDataTable` (6 testes)
     - `MyProject2.Utils.DataTableHelpers` (5 testes)
     - `MyProject2.Utils.CharacterSheetHelpers` (10 testes)
     - `MyProject2.Utils.ComponentHelpers` (3 testes)
4. **Selecione os testes desejados**
5. **Clique em "Start Tests"**

### Método 2: Linha de Comando (Terminal)

```bash
# Todos os testes
run_tests.bat

# Teste específico
run_tests.bat MyProject2.Data.Tables.FeatDataTable

# Versão rápida (otimizada)
run_tests_quick.bat
```

**Nota:** A inicialização do Unreal Engine via linha de comando pode levar 1-2 minutos. Isso é normal - o engine precisa carregar módulos e sistemas antes de executar os testes. O script fecha automaticamente quando termina.

**Comando baseado na documentação oficial:**
- [Write C++ Tests](https://dev.epicgames.com/documentation/en-us/unreal-engine/write-cplusplus-tests-in-unreal-engine)

### Método 3: Editor com Console

1. Abra o projeto no Editor
2. Pressione `~` (til) para abrir o console
3. Digite: `Automation RunTests MyProject2`

## 📊 Testes Disponíveis

### FeatDataTable (6 testes)
- ✅ GetPrerequisites com FeatureData vazio
- ✅ GetPrerequisites com string vazia
- ✅ GetPrerequisites com string única
- ✅ GetPrerequisites com múltiplas strings (vírgula)
- ✅ GetPrerequisites com trim de espaços
- ✅ GetPrerequisites ignorando strings vazias

### DataTableHelpers (5 testes)
- ✅ FindFeatRow com DataTable nullptr
- ✅ FindFeatRow com FeatName NAME_None
- ✅ FindFeatRow por FC_ID
- ✅ FindFeatRow por Name
- ✅ FindFeatRow com feat inexistente

### CharacterSheetHelpers (10 testes)
- ✅ MeetsFeatPrerequisites com Row nullptr
- ✅ MeetsFeatPrerequisites sem pré-requisitos
- ✅ MeetsFeatPrerequisites com pré-requisito atendido
- ✅ MeetsFeatPrerequisites com pré-requisito não atendido
- ✅ MeetsFeatPrerequisites com múltiplos pré-requisitos atendidos
- ✅ MeetsFeatPrerequisites com qualquer pré-requisito não atendido
- ✅ ValidateAbilityScorePrerequisite com NAME_None
- ✅ ValidateAbilityScorePrerequisite com score atendido
- ✅ ValidateAbilityScorePrerequisite com score não atendido
- ✅ ValidateAbilityScorePrerequisite com ability não no map

### ComponentHelpers (3 testes)
- ✅ FindCharacterDataComponent com componente presente
- ✅ FindCharacterDataComponent com Owner nullptr
- ✅ FindCharacterDataComponent sem componente

## ✅ Verificação Rápida

**Para verificar se os testes estão registrados:**

1. Abra o Editor
2. Window → Developer Tools → Automation Tool
3. Procure por "MyProject2" na busca
4. Se aparecerem 4 grupos de testes, está tudo OK! ✅

## 🔍 Troubleshooting

**Testes não aparecem no Automation Tool?**
- Verifique se o projeto compilou com sucesso
- Verifique se os arquivos `.cpp` de teste estão no projeto
- Recompile o projeto

**Erro ao executar testes?**
- Verifique os logs no Output Log do Editor
- Certifique-se de que todas as dependências estão corretas
