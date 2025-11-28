#!/usr/bin/env python3
"""
Script para atualizar todos os schemas JSON para incluir campos de versionamento.

Adiciona SchemaVersion e DataVersion aos schemas existentes.

Uso:
    python scripts/update_all_schemas_versioning.py
"""

import json
import sys
from pathlib import Path
from typing import Dict

# Diretório de schemas
SCHEMA_DIR = Path(__file__).parent.parent / 'Content' / 'Data' / 'JSON' / 'Schemas'

# Lista de schemas para atualizar
SCHEMA_FILES = [
    "AbilityScoreDataTable.schema.json",
    "TraitDataTable.schema.json",
    "LanguageDataTable.schema.json",
    "SkillDataTable.schema.json",
    "SpellDataTable.schema.json",
    "SpellSchoolDataTable.schema.json",
    "DamageTypeDataTable.schema.json",
    "ConditionDataTable.schema.json",
    "ProficiencyDataTable.schema.json",
    "RaceDataTable.schema.json",
    "ClassDataTable.schema.json",
    "BackgroundDataTable.schema.json",
    "FeatDataTable.schema.json",
    "FeatureDataTable.schema.json",
    "ItemDataTable.schema.json",
]


def update_schema(schema_path: Path) -> bool:
    """Atualiza um schema para incluir campos de versionamento."""
    try:
        with open(schema_path, 'r', encoding='utf-8') as f:
            schema = json.load(f)
    except FileNotFoundError:
        print(f"[ERRO] Schema nao encontrado: {schema_path}")
        return False
    except json.JSONDecodeError as e:
        print(f"[ERRO] JSON invalido em {schema_path}: {e}")
        return False

    # Verifica se já tem campos de versionamento
    if 'items' in schema and 'properties' in schema['items']:
        if 'SchemaVersion' in schema['items']['properties']:
            print(f"[AVISO] {schema_path.name} ja tem campos de versionamento")
            return True

        # Adiciona campos de versionamento
        required = schema['items'].get('required', [])
        if 'SchemaVersion' not in required:
            required.insert(0, 'DataVersion')
            required.insert(0, 'SchemaVersion')
            schema['items']['required'] = required

        properties = schema['items']['properties']

        # Cria novo dicionário com versionamento primeiro
        new_properties = {
            "SchemaVersion": {
                "type": "string",
                "pattern": "^\\d+\\.\\d+\\.\\d+$",
                "description": "Versão do schema (formato: MAJOR.MINOR.PATCH, ex: 1.0.0)"
            },
            "DataVersion": {
                "type": "string",
                "pattern": "^\\d{4}-\\d{2}-\\d{2}$",
                "description": "Versão dos dados (formato: YYYY-MM-DD, ex: 2024-12-27)"
            }
        }

        # Adiciona propriedades existentes
        for key, value in properties.items():
            new_properties[key] = value

        schema['items']['properties'] = new_properties

        # Salva schema atualizado
        try:
            with open(schema_path, 'w', encoding='utf-8') as f:
                json.dump(schema, f, indent=2, ensure_ascii=False)
            print(f"[OK] Schema atualizado: {schema_path.name}")
            return True
        except Exception as e:
            print(f"[ERRO] Erro ao salvar {schema_path}: {e}")
            return False

    return False


def main():
    if not SCHEMA_DIR.exists():
        print(f"[ERRO] Diretorio de schemas nao encontrado: {SCHEMA_DIR}")
        sys.exit(1)

    print("Atualizando schemas para incluir campos de versionamento...\n")

    success_count = 0
    total_count = len(SCHEMA_FILES)

    for schema_file in SCHEMA_FILES:
        schema_path = SCHEMA_DIR / schema_file
        if schema_path.exists():
            if update_schema(schema_path):
                success_count += 1
        else:
            print(f"[AVISO] Schema nao encontrado: {schema_file}")

    print(f"\n[OK] Processamento concluido: {success_count}/{total_count} schemas atualizados")
    return 0 if success_count == total_count else 1


if __name__ == '__main__':
    sys.exit(main())

