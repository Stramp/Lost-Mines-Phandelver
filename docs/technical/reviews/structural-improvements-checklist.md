# Checklist de Melhorias Estruturais - Padrão AAA

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Checklist Rápido</b></summary>

> Este checklist resume as melhorias prioritárias identificadas no [Relatório de Revisão Estrutural](./structural-review-report.md).
>
> **Status:** 🔴 Crítico | 🟡 Médio | 🟢 Baixo

</details>

---

## 🔴 Crítico - Prioridade 1: JSON Schema Validation

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Implementar Validação de Schema</b></summary>

> **Objetivo:** Validar estrutura e tipos de dados antes de importar no Unreal Engine.
>
> ### Tarefas
>
> - [ ] Criar diretório `Content/Data/JSON/Schemas/`
> - [ ] Criar JSON Schema para `RaceDataTable.json`
> - [ ] Criar JSON Schema para `ClassDataTable.json`
> - [ ] Criar JSON Schema para `BackgroundDataTable.json`
> - [ ] Criar JSON Schema para `FeatDataTable.json`
> - [ ] Criar JSON Schema para `FeatureDataTable.json`
> - [ ] Criar JSON Schema para `ProficiencyDataTable.json`
> - [ ] Criar JSON Schema para `ItemDataTable.json`
> - [ ] Criar JSON Schema para `TraitDataTable.json`
> - [ ] Criar JSON Schema para `LanguageDataTable.json`
> - [ ] Criar JSON Schema para `SkillDataTable.json`
> - [ ] Criar JSON Schema para `SpellDataTable.json`
> - [ ] Criar JSON Schema para `SpellSchoolDataTable.json`
> - [ ] Criar JSON Schema para `DamageTypeDataTable.json`
> - [ ] Criar JSON Schema para `ConditionDataTable.json`
> - [ ] Criar JSON Schema para `AbilityScoreDataTable.json`
> - [ ] Criar script Python de validação (`scripts/validate_json_schemas.py`)
> - [ ] Integrar validação com Unreal Engine Data Validation
> - [ ] Adicionar validação no CI/CD (GitHub Actions)
> - [ ] Documentar uso dos schemas
>
> **Estimativa:** 2-3 semanas
> **Referência:** [Relatório Completo](./structural-review-report.md#41-implementar-json-schema-validation--crítico)

</details>

---

## 🔴 Crítico - Prioridade 2: Normalizar MulticlassRequirements

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Normalizar Estrutura de MulticlassRequirements</b></summary>

> **Objetivo:** Converter formato string para estrutura normalizada usando `AbilityID`.
>
> ### Tarefas
>
> - [ ] Criar struct `FMulticlassRequirement` em C++
> - [ ] Criar struct `FMulticlassRequirementGroup` em C++
> - [ ] Atualizar `ClassDataTable.h` com novas estruturas
> - [ ] Criar script de migração (`scripts/migrate_multiclass_requirements.py`)
> - [ ] Migrar `ClassDataTable.json` (formato antigo → novo)
> - [ ] Atualizar código que processa `MulticlassRequirements`
> - [ ] Atualizar `MulticlassValidators.cpp` para nova estrutura
> - [ ] Atualizar `MulticlassMotor.cpp` para nova estrutura
> - [ ] Criar testes para nova estrutura
> - [ ] Validar todas as referências `AbilityID`
> - [ ] Atualizar documentação
>
> **Estimativa:** 1 semana
> **Referência:** [Relatório Completo](./structural-review-report.md#42-normalizar-multiclassrequirements--crítico)

</details>

---

## 🟡 Médio - Prioridade 3: Versionamento de Schema

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Adicionar Versionamento de Schema</b></summary>

> **Objetivo:** Adicionar campos de versão para controle de evolução e migração.
>
> ### Tarefas
>
> - [ ] Adicionar campo `SchemaVersion` em todos os JSONs
> - [ ] Adicionar campo `DataVersion` em todos os JSONs
> - [ ] Criar sistema de migração entre versões
> - [ ] Implementar validação de compatibilidade
> - [ ] Criar logs de mudanças
> - [ ] Documentar processo de versionamento
>
> **Estimativa:** 1-2 semanas
> **Referência:** [Relatório Completo](./structural-review-report.md#43-adicionar-versionamento-de-schema--médio)

</details>

---

## 🟡 Médio - Prioridade 4: Otimizações de Performance (Futuro)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⏳ Considerar SoA para Hot-Paths</b></summary>

> **Objetivo:** Considerar Structure of Arrays (SoA) para hot-paths quando necessário.
>
> ### Tarefas
>
> - [ ] Fazer profiling de performance atual
> - [ ] Identificar hot-paths que se beneficiariam de SoA
> - [ ] Avaliar trade-off legibilidade vs performance
> - [ ] Implementar SoA apenas se necessário (após profiling)
>
> **Estimativa:** TBD (após profiling)
> **Referência:** [Relatório Completo](./structural-review-report.md#44-otimizar-estrutura-de-progression--médio---futuro)

</details>

---

## 🟢 Baixo - Prioridade 5: Melhorias de Documentação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Melhorar Documentação</b></summary>

> **Objetivo:** Criar documentação clara para cada Data Table.
>
> ### Tarefas
>
> - [ ] Documentar `RaceDataTable` (campos, exemplos, uso)
> - [ ] Documentar `ClassDataTable` (campos, exemplos, uso)
> - [ ] Documentar `BackgroundDataTable` (campos, exemplos, uso)
> - [ ] Documentar `FeatDataTable` (campos, exemplos, uso)
> - [ ] Documentar `FeatureDataTable` (campos, exemplos, uso)
> - [ ] Documentar `ProficiencyDataTable` (campos, exemplos, uso)
> - [ ] Documentar `ItemDataTable` (campos, exemplos, uso)
> - [ ] Criar guia para designers
> - [ ] Adicionar exemplos de uso
>
> **Estimativa:** Contínuo
> **Referência:** [Relatório Completo](./structural-review-report.md#45-melhorar-documentação--baixo)

</details>

---

## 📊 Progresso Geral

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Status de Implementação</b></summary>

> ### Prioridade 1: JSON Schema Validation
> - **Status:** ⏳ Não Iniciado
> - **Progresso:** 0/20 tarefas (0%)
>
> ### Prioridade 2: Normalizar MulticlassRequirements
> - **Status:** ⏳ Não Iniciado
> - **Progresso:** 0/11 tarefas (0%)
>
> ### Prioridade 3: Versionamento de Schema
> - **Status:** ⏳ Não Iniciado
> - **Progresso:** 0/6 tarefas (0%)
>
> ### Prioridade 4: Otimizações de Performance
> - **Status:** ⏳ Futuro (após profiling)
> - **Progresso:** 0/4 tarefas (0%)
>
> ### Prioridade 5: Melhorias de Documentação
> - **Status:** ⏳ Contínuo
> - **Progresso:** 0/9 tarefas (0%)
>
> **Total:** 0/50 tarefas (0%)

</details>

---

## 🎯 Próximos Passos Imediatos

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚀 Ações Imediatas</b></summary>

> 1. **Esta Semana:**
>    - [ ] Iniciar implementação de JSON Schema validation (Prioridade 1)
>    - [ ] Criar primeiro schema de exemplo (`RaceDataTable.schema.json`)
>
> 2. **Próxima Semana:**
>    - [ ] Completar todos os JSON Schemas
>    - [ ] Implementar script de validação Python
>    - [ ] Iniciar normalização de MulticlassRequirements (Prioridade 2)
>
> 3. **Próximas 2-3 Semanas:**
>    - [ ] Completar normalização de MulticlassRequirements
>    - [ ] Adicionar versionamento de schema (Prioridade 3)
>    - [ ] Melhorar documentação (Prioridade 5)

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
**Referência Completa:** [Relatório de Revisão Estrutural](./structural-review-report.md)
