---
title: "Next Steps Implementation"
category: technical
subcategory: reviews
tags: [next-steps, implementation, improvements]
last_updated: 2024-12-27
difficulty: intermediate
related: [implementation-summary.md, structural-improvements-checklist.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../../index.md) > [Técnico](../index.md) > Reviews > Next Steps

# Próximos Passos de Implementação - Melhorias Estruturais

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Status Atual</b></summary>

> **Data:** 2024-12-27
> **Versão:** 1.2
> **Progresso Geral:** ✅ **100% das Prioridades Críticas Concluídas**
>
> ### ✅ Concluído
>
> - ✅ **Prioridade 1:** JSON Schema Validation (100% - schemas, script, integração e CI/CD)
> - ✅ **Prioridade 2:** Normalizar MulticlassRequirements (100% - código completo, testes criados)
> - ✅ **Prioridade 3:** Versionamento de Schema (100% - completo)
> - ✅ **Prioridade 5:** Melhorias de Documentação (100% - todas as Data Tables documentadas, guia para designers criado)
>
> ### ⏳ Pendente (Opcional/Futuro)
>
> - ⏳ Executar migração de dados no ClassDataTable.json (quando necessário)
> - ⏳ Otimizações de Performance (Prioridade 4 - após profiling)

</details>

---

## 🎯 Próximos Passos Imediatos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ 1. Executar Migração de MulticlassRequirements (Opcional)</b></summary>

> **Status:** ✅ Código pronto, migração opcional quando necessário
>
> ### Objetivo
>
> Converter `ClassDataTable.json` do formato antigo (string) para nova estrutura normalizada.
>
> **Nota:** O código já suporta ambos os formatos (antigo e novo) para compatibilidade. A migração pode ser feita quando conveniente.
>
> ### Passos
>
> 1. **Fazer backup:**
>
>    ```bash
>    python scripts/migrate_multiclass_requirements.py --backup
>    ```
>
> 2. **Dry run (simular):**
>
>    ```bash
>    python scripts/migrate_multiclass_requirements.py --dry-run
>    ```
>
> 3. **Executar migração:**
>
>    ```bash
>    python scripts/migrate_multiclass_requirements.py
>    ```
>
> 4. **Validar JSON após migração:**
>
>    ```bash
>    python scripts/validate_json_schemas.py --file Content/Data/JSON/ClassDataTable.json
>    ```
>
> 5. **Testar no Unreal Engine:**
>    - Abrir projeto
>    - Verificar se Data Table carrega corretamente
>    - Testar validação de requisitos de multiclasse
>
> ### Resultado Esperado
>
> `ClassDataTable.json` terá campo `MulticlassRequirementGroups` com estrutura normalizada:
>
> ```json
> "MulticlassRequirementGroups": [
>   {
>     "Operator": "OR",
>     "Requirements": [
>       {"AbilityID": "ABL_Strength", "Value": 13},
>       {"AbilityID": "ABL_Dexterity", "Value": 13}
>     ]
>   }
> ]
> ```

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ 2. Adicionar AbilityScoreDataTable ao Contexto</b></summary>

> **Status:** ✅ Concluído
>
> ### Objetivo
>
> Garantir que `AbilityScoreDataTable` esteja disponível onde necessário para validação da nova estrutura.
>
> **Nota:** Já implementado. `AbilityScoreDataTable` foi adicionado ao `CharacterSheetDataAsset` e está sendo usado nas validações.
>
> ### Verificações Necessárias (Já Concluídas)
>
> 1. **Verificar se `CharacterSheetDataAsset` tem `AbilityScoreDataTable`:**
>    - Se não tiver, adicionar campo
>    - Configurar no editor
>
> 2. **Atualizar chamadas de `GetAvailableClassWithTagRequirements`:**
>    - Passar `AbilityScoreDataTable` quando disponível
>    - Manter compatibilidade com chamadas antigas
>
> 3. **Testar validação:**
>    - Verificar se nova estrutura funciona corretamente
>    - Comparar resultados com formato antigo
>
> ### Arquivos a Verificar
>
> - `Source/MyProject2/Characters/Data/CharacterSheetDataAsset.h`
> - `Source/MyProject2/CreateSheet/Multiclass/MulticlassMotor.cpp`
> - Locais onde `GetAvailableClassWithTagRequirements` é chamado

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ 3. Criar Testes para Nova Estrutura</b></summary>

> **Status:** ✅ Concluído
>
> ### Objetivo
>
> Garantir que nova estrutura de `MulticlassRequirements` funciona corretamente.
>
> **Nota:** Testes já criados em `MulticlassValidatorsTests.cpp`. Todos os casos de teste foram implementados.
>
> ### Testes Necessários (Já Implementados)
>
> 1. **Teste de Validação de Requisito Individual:**
>    - Requisito satisfeito
>    - Requisito não satisfeito
>    - AbilityID inválido
>
> 2. **Teste de Validação de Grupo (OR):**
>    - Pelo menos um requisito satisfeito
>    - Nenhum requisito satisfeito
>
> 3. **Teste de Validação de Grupo (AND):**
>    - Todos os requisitos satisfeitos
>    - Um requisito não satisfeito
>
> 4. **Teste de Validação de Múltiplos Grupos:**
>    - Todos os grupos satisfeitos (AND entre grupos)
>    - Um grupo não satisfeito
>
> 5. **Teste de Compatibilidade:**
>    - Formato antigo ainda funciona
>    - Fallback funciona corretamente
>
> ### Arquivo de Teste
>
> Criar: `Source/MyProject2/CreateSheet/Multiclass/Tests/MulticlassRequirementValidationTests.cpp`

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ 4. Integrar Validação com Unreal Engine</b></summary>

> **Status:** ✅ Concluído
>
> ### Objetivo
>
> Integrar validação de JSON Schemas com sistema de Data Validation do Unreal Engine.
>
> **Nota:** `FDataTableSchemaValidator` foi criado e integrado. Validação automática está funcionando.
>
> ### Passos (Já Concluídos)
>
> 1. **Criar classe de Data Validation:**
>    - Herdar de `UDataValidation`
>    - Implementar validação usando JSON Schemas
>
> 2. **Configurar no Editor:**
>    - Associar validators às Data Tables
>    - Configurar para rodar automaticamente
>
> 3. **Testar:**
>    - Modificar JSON intencionalmente para ter erro
>    - Verificar se validação detecta erro
>
> ### Referências
>
> - [Unreal Engine Data Validation](https://docs.unrealengine.com/5.7/en-US/data-validation-in-unreal-engine/)
> - Exemplos de validators existentes no projeto

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ 5. Adicionar Validação no CI/CD</b></summary>

> **Status:** ✅ Concluído
>
> ### Objetivo
>
> Validar JSONs automaticamente em cada commit/pull request.
>
> **Nota:** Workflow GitHub Actions criado em `.github/workflows/validate-json-schemas.yml`. Validação automática está ativa.
>
> ### Passos (Já Concluídos)
>
> 1. **Criar workflow GitHub Actions:**
>    - Instalar dependências Python (jsonschema)
>    - Executar script de validação
>    - Falhar build se JSONs inválidos
>
> 2. **Configurar:**
>    - Trigger em push e pull requests
>    - Validar todos os arquivos JSON
>    - Reportar erros claramente
>
> 3. **Testar:**
>    - Fazer commit com JSON inválido
>    - Verificar se CI/CD detecta erro
>
> ### Arquivo
>
> Criar: `.github/workflows/validate-json-schemas.yml`

</details>

---

## 📋 Checklist de Execução

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Checklist Completo</b></summary>

> ### Migração de Dados
>
> - [ ] Fazer backup do `ClassDataTable.json`
> - [ ] Executar dry-run do script de migração
> - [ ] Executar migração real
> - [ ] Validar JSON após migração
> - [ ] Testar no Unreal Engine
> - [ ] Verificar se validação funciona corretamente
>
> ### Integração de AbilityScoreDataTable
>
> - [ ] Verificar se `CharacterSheetDataAsset` tem `AbilityScoreDataTable`
> - [ ] Adicionar campo se necessário
> - [ ] Atualizar chamadas de `GetAvailableClassWithTagRequirements`
> - [ ] Testar validação com nova estrutura
>
> ### Testes
>
> - [ ] Criar arquivo de testes
> - [ ] Implementar teste de requisito individual
> - [ ] Implementar teste de grupo OR
> - [ ] Implementar teste de grupo AND
> - [ ] Implementar teste de múltiplos grupos
> - [ ] Implementar teste de compatibilidade
> - [ ] Executar todos os testes
>
> ### Integração Unreal Engine
>
> - [ ] Criar classe de Data Validation
> - [ ] Implementar validação usando JSON Schemas
> - [ ] Configurar no Editor
> - [ ] Testar validação automática
>
> ### CI/CD
>
> - [ ] Criar workflow GitHub Actions
> - [ ] Configurar validação automática
> - [ ] Testar com JSON inválido
> - [ ] Documentar processo

</details>

---

## 🎯 Status Atual

### ✅ Tarefas Concluídas

1. ✅ **Adicionar AbilityScoreDataTable ao contexto** - Concluído
2. ✅ **Criar testes para nova estrutura** - Concluído
3. ✅ **Integrar validação com Unreal Engine** - Concluído
4. ✅ **Adicionar validação no CI/CD** - Concluído

### ⏳ Tarefas Opcionais/Futuras

1. ⏳ **Executar migração de dados** - Opcional (código já suporta ambos os formatos)
2. ⏳ **Otimizações de Performance** - Após profiling (Prioridade 4)

---

**Última atualização:** 2024-12-27
**Versão:** 1.2
