# Revisão de Arquitetura de Dados - Melhorias Identificadas

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Resumo Executivo</b></summary>

> Este documento identifica melhorias na arquitetura de dados baseadas em:
>
> - Análise dos JSONs existentes
> - Comparação com princípios de Data-Oriented Design
> - Alinhamento com padrões de jogos AAA (Baldur's Gate 3)
> - Consistência com documentação de arquitetura
>
> **Status:** 🔴 Crítico | 🟡 Médio | 🟢 Baixo

</details>

</details>

## 🔴 Crítico - Problemas Identificados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>1. MulticlassRequirements em Formato Antigo</b></summary>

> **Problema:** `ClassDataTable.json` ainda usa formato antigo de `MulticlassRequirements` (string "STR/13|DEX/13") ao invés da estrutura normalizada.
>
> **Localização:** `Content/Data/JSON/ClassDataTable.json`
>
> **Formato Atual (❌ ERRADO):**
>
> ```json
> "MulticlassRequirements": [
> "STR/13|DEX/13"
> ]
> ```
>
> **Formato Esperado (✅ CORRETO):**

> ```json
> "MulticlassRequirementGroups": [
> {
> "Operator": "OR",
> "Requirements": [
> {"AbilityID": "ABL_Strength", "Value": 13},
> {"AbilityID": "ABL_Dexterity", "Value": 13}
> ]
> }
> ]
> ```
>
> **Impacto:**
> - ❌ Código C já suporta formato novo (com fallback para antigo)
> - ❌ Documentação indica que formato novo foi implementado
> - ❌ Inconsistência entre código e dados
>
> **Solução:**
> - Executar script de migração `scripts/migrate_multiclass_requirements.py`
> - Validar JSON após migração
> - Testar no Unreal Engine
>
> **Status Atual:**
> - ⚠️ 12 classes ainda usam formato antigo
> - ✅ 12 classes já migradas para formato novo
> - ✅ Código C suporta ambos os formatos (compatibilidade mantida)
>
> **Prioridade:** 🔴 Crítico (inconsistência entre código e dados)
>
</details>
> **Impacto:**
> - ❌ Validação falha para LanguageDataTable (falsos positivos)
> - ❌ Inconsistência entre documentação e código
>
> **Solução:**
> - ✅ Corrigido prefixo no validador de `LANG_` para `PL_`
> - [ ] Validar todos os JSONs após correção
>
> **Status:** ✅ Corrigido
>
> **Prioridade:** ✅ Resolvido
>
</details>
---

## 🟡 Médio - Melhorias Recomendadas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>3. Verificar Consistência de Prefixos em ProficiencyDataTable</b></summary>

> **Problema:** `ProficiencyDataTable` contém proficiências de diferentes tipos (Weapon, Armor, Tool, Language, etc.) com prefixos diferentes, mas o validador só verifica `PW_`.
>

> **Localização:** `Content/Data/JSON/ProficiencyDataTable.json`
>
> **Análise:**
> - ✅ Weapon proficiencies usam `PW_` (ex: `PW_Simple_Weapons`)
> - ✅ Armor proficiencies usam `PA_` (ex: `PA_Light_Armor`)
> - ✅ Shield proficiencies usam `PS_` (ex: `PS_Shields`)
> - ✅ Tool proficiencies usam `PT_` (ex: `PT_Thieves_Tools`)
> - ✅ Language proficiencies usam `PL_` (ex: `PL_Common`) - **Inconsistente!**
> - ✅ Skill proficiencies usam `PSK_` (ex: `PSK_Acrobatics`) - **Inconsistente!**
>
> **Problema:**
> - Language proficiencies deveriam estar em `LanguageDataTable`, não em `ProficiencyDataTable`
> - Skill proficiencies deveriam estar em `SkillDataTable`, não em `ProficiencyDataTable`
>
> **Solução:**
> - Remover Language e Skill proficiencies de `ProficiencyDataTable`
> - Usar referências via `FDataTableRowHandle` quando necessário
> - Atualizar validador para aceitar múltiplos prefixos em `ProficiencyDataTable`
>
> **Prioridade:** 🟡 Médio (organização de dados)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>4. Verificar Uso Consistente de FDataTableRowHandle</b></summary>

> **Problema:** Verificar se todas as referências entre tabelas usam `FDataTableRowHandle` ao invés de strings/IDs diretos.
>

> **Análise Necessária:**
> - ✅ `RaceDataTable` usa `TraitHandles`, `LanguageHandles`, `SubraceHandles` (correto)
> - ✅ `ClassDataTable` usa `WeaponProficiencyHandles`, `ArmorProficiencyHandles`, `SavingThrowHandles` (correto)
> - ⚠️ Verificar se há referências diretas por string/ID que deveriam ser Handles
>
> **Solução:**
> - Auditoria completa de todas as referências
> - Converter referências diretas para `FDataTableRowHandle` quando apropriado
> - Documentar casos onde referência direta é aceitável (ex: `AbilityID` em arrays pequenos)
>
> **Prioridade:** 🟡 Médio (type safety)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>5. Verificar Estrutura "Flat" dos JSONs</b></summary>

> **Problema:** Verificar se todos os JSONs seguem estrutura "flat" (plana) ao invés de profundamente aninhada.
>
> **Princípio:** JSONs relacionais e planos, não profundamente aninhados (o importador do Unreal quebra com estruturas muito aninhadas).
>
> **Análise Necessária:**
>
> - Verificar profundidade máxima de aninhamento em cada JSON
> - Identificar estruturas que poderiam ser "achatadas"
> - Verificar se há arrays de objetos complexos que poderiam ser referências
>
> **Solução:**
>
> - Auditoria de estrutura de cada JSON
> - Refatorar estruturas profundamente aninhadas
> - Documentar casos onde aninhamento é necessário
>
> **Prioridade:** 🟡 Médio (compatibilidade com importador)

</details>

</details>

## 🟢 Baixo - Otimizações Futuras

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>6. Considerar Structure of Arrays (SoA) para Hot-Paths</b></summary>

> **Problema:** Estrutura atual usa Array of Structures (AoS), que pode ser ineficiente para hot-paths.
>

> **Análise:**
> - Estrutura atual (AoS) é adequada para maioria dos casos
> - SoA só é necessário para hot-paths com milhares de entidades
> - Trade-off: legibilidade vs performance
>
> **Solução:**
> - Fazer profiling de performance atual
> - Identificar hot-paths que se beneficiariam de SoA
> - Implementar SoA apenas se necessário (após profiling)
>
> **Prioridade:** 🟢 Baixo (otimização futura)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>7. Serialização Binária para Saves</b></summary>

> **Problema:** Saves atuais provavelmente usam JSON, que é ineficiente para dados grandes.
>

> **Análise:**
> - JSON é adequado para Data Tables (dados estáticos)
> - Saves (dados dinâmicos) podem se beneficiar de formato binário
> - FlatBuffers ou Protobuf são opções
>
> **Solução:**
> - Implementar serialização binária para saves (futuro)
> - Manter JSON para Data Tables (adequado para dados estáticos)
>
> **Prioridade:** 🟢 Baixo (otimização futura)
>
</details>
---

## 📋 Checklist de Correções

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Ações Imediatas</b></summary>

> ### 🔴 Crítico
>

> - [ ] Corrigir `MulticlassRequirements` em `ClassDataTable.json` (formato antigo → novo)
> - [ ] Corrigir prefixo no validador (`LANG_` → `PL_`)
> - [ ] Validar todos os JSONs após correções
>
</details>
    ### 🟡 Médio

    - [ ] Auditoria de `ProficiencyDataTable` (remover Language/Skill proficiencies)
    - [ ] Verificar uso consistente de `FDataTableRowHandle`
    - [ ] Verificar estrutura "flat" dos JSONs

    ### 🟢 Baixo

    - [ ] Profiling de performance (identificar hot-paths)
    - [ ] Considerar SoA para hot-paths (se necessário)
    - [ ] Considerar serialização binária para saves (futuro)

---

## 📊 Comparação: Antes vs Depois

| Aspecto | Antes (Atual) | Depois (Ideal) |
|---------|---------------|----------------|
| **MulticlassRequirements** | ❌ String "STR/13\|DEX/13" | ✅ Estrutura normalizada com AbilityID |
| **Validação de Prefixos** | ❌ `LANG_` (incorreto) | ✅ `PL_` (correto) |
| **ProficiencyDataTable** | ⚠️ Mistura tipos diferentes | ✅ Apenas proficiências gerais |
| **Type Safety** | ⚠️ Algumas referências por string | ✅ Todas via FDataTableRowHandle |
| **Estrutura JSON** | ✅ Maioria "flat" | ✅ 100% "flat" |

---

## 🎯 Prioridade de Implementação

1. **🔴 Crítico (Esta Semana):**
   - Corrigir `MulticlassRequirements` em `ClassDataTable.json`
   - Corrigir prefixo no validador

2. **🟡 Médio (Próximas 2 Semanas):**
   - Auditoria de `ProficiencyDataTable`
   - Verificar uso de `FDataTableRowHandle`
   - Verificar estrutura "flat"

3. **🟢 Baixo (Futuro):**
   - Profiling e otimizações de performance
   - Serialização binária para saves

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
