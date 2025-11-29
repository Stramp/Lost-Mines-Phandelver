---
title: "Guia de Validação JSON Schema"
category: technical
subcategory: guides
tags: [json-schema, validation, data-tables, ci-cd]
last_updated: 2024-12-27
difficulty: intermediate
related: [../data-architecture/json-schema.md, ../reviews/structural-review-report.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../index.md) > [Técnico](../technical/index.md) > [Guias](guides/index.md) > JSON Schema Validation Guide

# Guia de Validação JSON Schema

> **Objetivo:** Documentar como usar o sistema de validação JSON Schema no projeto MyProject2.
>
> **Público-alvo:** Desenvolvedores e designers que trabalham com Data Tables JSON.

---

## 📋 Visão Geral

O projeto MyProject2 implementa validação de JSON Schema em três níveis:

1. **Validação Local (Python Script)** - Validação completa antes de importar no Unreal Engine
2. **Validação no Editor (C)** - Validação automática quando Data Tables são alteradas
3. **Validação no CI/CD (GitHub Actions)** - Validação automática em cada commit/PR

---

## 🔧 Validação Local com Python

### Pré-requisitos

```bash
pip install jsonschema
```

### Uso Básico

Validar todos os arquivos JSON:

```bash
python scripts/validate_json_schemas.py
```

Validar um arquivo específico:

```bash
python scripts/validate_json_schemas.py --file Content/Data/JSON/RaceDataTable.json
```

Modo verbose (mostra detalhes):

```bash
python scripts/validate_json_schemas.py --verbose
```

### Saída Esperada

**Sucesso:**
```
[OK] Content\Data\JSON\RaceDataTable.json: Valido
[OK] Content\Data\JSON\ClassDataTable.json: Valido
...

Resumo: 15/15 arquivos validos
```

**Erro:**
```
[ERRO] Content\Data\JSON\RaceDataTable.json: Invalido
  - Erro de validacao: 'ID' is a required property
  - Erro de validacao: 'TypeTags' is a required property

Resumo: 14/15 arquivos validos
```

### Integração com Editor

O script pode ser executado manualmente antes de importar JSONs no Unreal Engine, garantindo que os dados estão corretos antes da importação.

---

## 🎮 Validação no Editor (Unreal Engine)

### Validação Automática

Quando uma Data Table é alterada no editor, o sistema automaticamente valida:

1. **Estrutura básica** (Name, ID, TypeTags obrigatórios)
2. **Padrões de nomenclatura** (prefixos de ID e TypeTags)
3. **Tipos de dados** (validação básica em C)

### Como Funciona

A validação é integrada em `HandleDataTableChange` e executa automaticamente quando:

- Uma Data Table é atribuída ao `CharacterSheetDataAsset`
- Uma Data Table é modificada no editor

### Exemplo de Uso em C++

```cpp
// Validação básica (sempre disponível)
FDataTableSchemaValidationResult Result =
    FDataTableSchemaValidator::ValidateBasicStructure(DataTable, TEXT("RaceDataTable"));

if (!Result.bIsValid)
{
    for (const FString& Error : Result.Errors)
    {
        UE_LOG(LogTemp, Warning, TEXT("Schema Error: %s"), *Error);
    }
}

// Validação completa com Python (opcional, requer Python instalado)
FDataTableSchemaValidationResult FullResult =
    FDataTableSchemaValidator::ValidateDataTableSchema(DataTable, TEXT("RaceDataTable"), true);
```

### Logs no Editor

Erros de validação aparecem no Output Log do Unreal Engine:

```
LogTemp: Warning: RaceDataTable Schema Error: Row 'Elf' na DataTable 'RaceDataTable' não tem ID
LogTemp: Warning: RaceDataTable Schema Error: Row 'Dwarf' na DataTable 'RaceDataTable' não tem TypeTags
```

---

## 🚀 Validação no CI/CD (GitHub Actions)

### Workflow Automático

O projeto inclui dois workflows GitHub Actions:

1. **`.github/workflows/validate-json-schemas.yml`** - Workflow dedicado para validação
2. **`.github/workflows/build.yml`** - Workflow de build que inclui validação

### Quando Executa

- **Push** para branches `master`, `main`, `develop`
- **Pull Request** para branches `master`, `main`, `develop`
- **Apenas quando** arquivos JSON ou schemas são modificados (workflow dedicado)

### O Que Valida

1. Instala Python 3.11
2. Instala biblioteca `jsonschema`
3. Executa `scripts/validate_json_schemas.py`
4. Falha o build se houver erros de validação

### Badges de Status

Badges no README mostram status dos workflows:

```markdown
[![JSON Schema Validation](https://github.com/your-username/MyProject2/workflows/Validate%20JSON%20Schemas/badge.svg)](https://github.com/your-username/MyProject2/actions/workflows/validate-json-schemas.yml)
```

---

## 📝 Estrutura de MulticlassRequirements

### Formato Antigo (Deprecated)

```json
{
  "MulticlassRequirements": [
    "STR/13|DEX/13"
  ]
}
```

### Formato Novo (Normalizado)

```json
{
  "MulticlassRequirementGroups": [
    {
      "Operator": "OR",
      "Requirements": [
        {
          "AbilityID": "ABL_Strength",
          "Value": 13
        },
        {
          "AbilityID": "ABL_Dexterity",
          "Value": 13
        }
      ]
    }
  ]
}
```

### Migração

Use o script de migração para converter formato antigo para novo:

```bash
python scripts/migrate_multiclass_requirements.py --backup
```

O script:
- Cria backup automático do arquivo original
- Converte todas as classes para o novo formato
- Mantém formato antigo para compatibilidade durante transição

### Validação de AbilityIDs

Valide referências AbilityID:

```bash
python scripts/validate_ability_ids.py
```

Verifica se todos os `AbilityID` referenciados existem no `AbilityScoreDataTable.json`.

---

## 🛠️ Troubleshooting

### Erro: "Biblioteca 'jsonschema' não encontrada"

**Solução:**
```bash
pip install jsonschema
```

### Erro: "Arquivo JSON não encontrado"

**Solução:**
- Verifique se o arquivo está em `Content/Data/JSON/`
- Verifique se o nome do arquivo corresponde ao schema (ex: `RaceDataTable.json` → `RaceDataTable.schema.json`)

### Erro: "Schema não encontrado"

**Solução:**
- Verifique se o schema existe em `Content/Data/JSON/Schemas/`
- Verifique se o nome do schema corresponde ao JSON (ex: `RaceDataTable.json` → `RaceDataTable.schema.json`)

### Validação no Editor não funciona

**Solução:**
- Verifique se `FDataTableSchemaValidator` está sendo chamado
- Verifique logs do Unreal Engine (Window → Developer Tools → Output Log)
- Validação Python requer Python instalado e acessível via PATH

---

## 📚 Referências

- [JSON Schema Documentation](../data-architecture/json-schema.md) - Estrutura completa dos schemas
- [Structural Review Report](../reviews/structural-review-report.md) - Análise completa da estrutura
- [DataTableSchemaValidator.h](../../../Source/MyProject2/Utils/DataTableSchemaValidator.h) - Código fonte do validador
- [validate_json_schemas.py](../../../scripts/validate_json_schemas.py) - Script Python de validação

---

## ✅ Checklist de Validação

Antes de commitar mudanças em JSONs:

- [ ] Executar `python scripts/validate_json_schemas.py` localmente
- [ ] Verificar que todos os arquivos passam na validação
- [ ] Verificar que AbilityIDs são válidos (se usar MulticlassRequirements)
- [ ] Commitar mudanças
- [ ] Verificar que CI/CD passa (GitHub Actions)

---

**Última atualização:** 2024-12-27
