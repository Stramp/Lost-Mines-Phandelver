# Testes de Criação de Personagem D&D 5e

## 📋 Visão Geral

Este diretório contém todos os testes para o processo de criação de personagem D&D 5e, organizados por passo seguindo a metodologia **TDD (Test-Driven Development)**.

## 🎯 Estrutura de Testes

### Step 1: Choose a Race
**Arquivo:** `Step1_ChooseRaceTests.cpp`

**Testes:**
- ✅ Aplicação de racial traits
- ✅ Aplicação de ability score increases
- ✅ Seleção de subraces
- ✅ Languages automáticos
- ✅ Variant Human (feat, skill, ability choices)

### Step 2: Choose a Class
**Arquivo:** `Step2_ChooseClassTests.cpp`

**Testes:**
- ✅ Carregamento de proficiências da classe
- ✅ Carregamento de features da classe
- ✅ Cálculo de Hit Die
- ✅ Validação de requisitos de multiclass
- ✅ Cálculo de proficiency bonus

### Step 3: Determine Ability Scores
**Arquivo:** `Step3_DetermineAbilityScoresTests.cpp`

**Testes:**
- ✅ Point Buy (já implementado)
- ❌ Standard Array (NÃO IMPLEMENTADO - testes devem falhar)
- ❌ Roll 4d6 drop lowest (NÃO IMPLEMENTADO - testes devem falhar)

### Step 4: Describe Your Character
**Arquivo:** `Step4_DescribeCharacterTests.cpp`

**Testes (todos devem falhar até implementação):**
- ❌ Personality Traits
- ❌ Ideals
- ❌ Bonds
- ❌ Flaws

### Step 5: Choose Equipment
**Arquivo:** `Step5_ChooseEquipmentTests.cpp`

**Testes (todos devem falhar até implementação):**
- ❌ Starting Equipment da classe
- ❌ Starting Equipment do background
- ❌ Equipment choices
- ❌ Carrying Capacity
- ❌ Armor Class

### Teste de Integração Completo
**Arquivo:** `../Integration/CompleteCharacterCreationE2ETests.cpp`

**Testes:**
- ✅ Criação completa de personagem (todos os 6 passos)
- ✅ Criação completa com Variant Human

## 🔴 Testes que Devem Falhar (TDD Red)

Seguindo TDD, os seguintes testes devem **FALHAR** até que as funcionalidades sejam implementadas:

1. **Standard Array** - `Step3_DetermineAbilityScoresTests.cpp`
2. **Roll 4d6 drop lowest** - `Step3_DetermineAbilityScoresTests.cpp`
3. **Personality Traits** - `Step4_DescribeCharacterTests.cpp`
4. **Ideals** - `Step4_DescribeCharacterTests.cpp`
5. **Bonds** - `Step4_DescribeCharacterTests.cpp`
6. **Flaws** - `Step4_DescribeCharacterTests.cpp`
7. **Starting Equipment** - `Step5_ChooseEquipmentTests.cpp`
8. **Carrying Capacity** - `Step5_ChooseEquipmentTests.cpp`
9. **Armor Class** - `Step5_ChooseEquipmentTests.cpp`
10. **Proteção contra adição manual de proficiências** - `CharacterSheetDataAssetLoadersTests.cpp`

## ✅ Testes Corrigidos

### Testes de Proficiências
Os testes em `CharacterSheetDataAssetLoadersTests.cpp` foram corrigidos para validar que o sistema **IMPEDE** adições manuais de proficiências. Estes testes devem falhar até que a proteção seja implementada.

## 📝 Notas Importantes

1. **TDD Red-Green-Refactor**: Todos os testes seguem o ciclo TDD:
   - **Red**: Teste escrito que falha (define comportamento esperado)
   - **Green**: Implementação mínima que faz teste passar
   - **Refactor**: Melhoria do código mantendo testes passando

2. **Testes que Falham São Esperados**: Testes para funcionalidades não implementadas devem falhar. Isso indica o que precisa ser implementado.

3. **Organização por Passo**: Testes organizados seguindo os 6 passos do D&D 5e conforme documentação oficial.

4. **Teste de Integração**: O teste completo valida todo o processo de criação, falhando nos passos não implementados.

## 🚀 Próximos Passos

1. Executar todos os testes para verificar quais estão falhando (como esperado)
2. Implementar funcionalidades faltantes baseadas nos testes
3. Refatorar código mantendo testes passando
4. Adicionar novos testes conforme necessário

## 📚 Referências

- [D&D Beyond - Step-By-Step Characters](https://www.dndbeyond.com/sources/dnd/basic-rules-2014/step-by-step-characters)
- `.cursor/rules/test-driven-development.mdc` - Metodologia TDD
- `.cursor/rules/testing.mdc` - Padrões de testes
- `memorias/regras-algoritmicas-criacao-ficha-dnd.md` - Regras algorítmicas
