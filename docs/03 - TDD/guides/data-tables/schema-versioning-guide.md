---
title: "Guia de Versionamento de Schema"
category: technical
subcategory: guides
tags: [schema-versioning, data-migration, compatibility]
last_updated: 2024-12-27
difficulty: intermediate
related: [../data-architecture/json-schema.md, ../reviews/structural-review-report.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../index.md) > [Técnico](../technical/index.md) > [Guias](guides/index.md) > Schema Versioning Guide

# Guia de Versionamento de Schema

> **Objetivo:** Documentar o sistema de versionamento de schema e como gerenciar evolução de dados.
>
> **Público-alvo:** Desenvolvedores que precisam evoluir estruturas de dados mantendo compatibilidade.

---

## 📋 Visão Geral

O projeto MyProject2 implementa versionamento de schema para:

1. **Controle de Evolução** - Rastrear mudanças na estrutura de dados
2. **Migração de Dados** - Facilitar migrações entre versões
3. **Compatibilidade** - Validar compatibilidade entre versões
4. **Rastreamento** - Manter histórico de mudanças

---

## 🔢 Campos de Versionamento

Cada entrada JSON possui dois campos de versão:

## SchemaVersion

**Formato:** `MAJOR.MINOR.PATCH` (ex: `1.0.0`)

**Semântica:**
- **MAJOR:** Mudanças incompatíveis (estrutura quebrada)
- **MINOR:** Novos campos opcionais (compatível para frente)
- **PATCH:** Correções de bugs, ajustes (compatível)

**Exemplo:**
```json
{
  "SchemaVersion": "1.0.0",
  "DataVersion": "2024-12-27",
  "Name": "Elf",
  "ID": "RACE_Elf",
  ...
}
```

### DataVersion

**Formato:** `YYYY-MM-DD` (ex: `2024-12-27`)

**Semântica:**
- Data da última modificação dos dados
- Usado para rastreamento e auditoria
- Não afeta compatibilidade

---

## 🛠️ Ferramentas

### 1. Adicionar Versionamento

Adiciona campos de versionamento a todos os JSONs:

```bash
python scripts/add_schema_versioning.py --backup
```

**Opções:**
- `--dry-run` - Simula sem modificar arquivos
- `--backup` - Cria backup antes de modificar
- `--schema-version` - Define versão do schema (padrão: 1.0.0)
- `--data-version` - Define versão dos dados (padrão: data atual)

### 2. Validar Compatibilidade

Valida compatibilidade de versões:

```bash
python scripts/validate_schema_compatibility.py
python scripts/validate_schema_compatibility.py --min-version 1.0.0
python scripts/validate_schema_compatibility.py --file RaceDataTable.json
```

**O que valida:**
- Presença de `SchemaVersion` e `DataVersion`
- Formato correto das versões
- Versão mínima suportada
- Consistência de versões dentro do arquivo

### 3. Gerar Changelog

Gera log de mudanças entre versões:

```bash
# Lista versões de todos os arquivos
python scripts/schema_changelog.py --list-versions

# Compara arquivo com backup
python scripts/schema_changelog.py --compare-file Content/Data/JSON/RaceDataTable.json.backup
```

---

## 📝 Processo de Versionamento

### Quando Atualizar SchemaVersion

**MAJOR (2.0.0):**
- Remover campos obrigatórios
- Mudar tipos de campos obrigatórios
- Mudar estrutura de arrays/objetos obrigatórios

**MINOR (1.1.0):**
- Adicionar novos campos opcionais
- Adicionar novos valores a enums
- Expandir estrutura sem quebrar compatibilidade

**PATCH (1.0.1):**
- Corrigir bugs em validação
- Ajustar padrões de regex
- Melhorar documentação em schemas

### Exemplo de Evolução

**Versão 1.0.0:**
```json
{
  "SchemaVersion": "1.0.0",
  "Name": "Elf",
  "ID": "RACE_Elf"
}
```

**Versão 1.1.0 (MINOR - adiciona campo opcional):**
```json
{
  "SchemaVersion": "1.1.0",
  "Name": "Elf",
  "ID": "RACE_Elf",
  "SubraceHandles": []  // Novo campo opcional
}
```

**Versão 2.0.0 (MAJOR - remove campo obrigatório):**
```json
{
  "SchemaVersion": "2.0.0",
  "Name": "Elf",
  "ID": "RACE_Elf"
  // "Description" removido (era obrigatório em 1.x)
}
```

---

## 🔄 Migração de Dados

### Script de Migração

Quando houver mudança MAJOR, criar script de migração:

```python
# scripts/migrate_schema_v1_to_v2.py
def migrate_entry_v1_to_v2(entry_v1: Dict) -> Dict:
    """Migra entrada da versão 1.0.0 para 2.0.0."""
    entry_v2 = {
        "SchemaVersion": "2.0.0",
        "DataVersion": datetime.now().strftime("%Y-%m-%d"),
        "Name": entry_v1["Name"],
        "ID": entry_v1["ID"],
        # Migra campos...
    }
    return entry_v2
```

## Processo de Migração

1. **Backup** - Sempre criar backup antes de migrar
2. **Validar** - Validar dados antes da migração
3. **Migrar** - Executar script de migração
4. **Validar** - Validar dados após migração
5. **Testar** - Testar no Unreal Engine

---

## ✅ Checklist de Versionamento

Antes de atualizar schema:

- [ ] Identificar tipo de mudança (MAJOR/MINOR/PATCH)
- [ ] Atualizar `SchemaVersion` apropriadamente
- [ ] Atualizar `DataVersion` para data atual
- [ ] Atualizar schema JSON correspondente
- [ ] Criar script de migração (se MAJOR)
- [ ] Validar compatibilidade
- [ ] Testar no Unreal Engine
- [ ] Documentar mudanças no CHANGELOG.md

---

## 📚 Referências

- [JSON Schema Documentation](../data-architecture/json-schema.md) - Estrutura completa dos schemas
- [Structural Review Report](../reviews/structural-review-report.md) - Análise completa da estrutura
- [Semantic Versioning](https://semver.org/) - Especificação de versionamento semântico

---

**Última atualização:** 2024-12-27
