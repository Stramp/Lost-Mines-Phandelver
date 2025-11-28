#!/usr/bin/env python3
"""
Script para adicionar campos de versionamento (SchemaVersion e DataVersion) aos arquivos JSON.

Adiciona campos de versão no início de cada arquivo JSON de Data Table para controle
de evolução e migração de dados.

Uso:
    python scripts/add_schema_versioning.py --dry-run
    python scripts/add_schema_versioning.py --backup
"""

import json
import sys
from pathlib import Path
from datetime import datetime
from typing import Dict, List

# Versão inicial do schema
SCHEMA_VERSION = "1.0.0"
DATA_VERSION = datetime.now().strftime("%Y-%m-%d")

# Arquivos JSON a processar
JSON_FILES = [
    "AbilityScoreDataTable.json",
    "TraitDataTable.json",
    "LanguageDataTable.json",
    "SkillDataTable.json",
    "SpellDataTable.json",
    "SpellSchoolDataTable.json",
    "DamageTypeDataTable.json",
    "ConditionDataTable.json",
    "ProficiencyDataTable.json",
    "RaceDataTable.json",
    "ClassDataTable.json",
    "BackgroundDataTable.json",
    "FeatDataTable.json",
    "FeatureDataTable.json",
    "ItemDataTable.json",
]


def load_json_file(file_path: Path) -> Dict:
    """Carrega um arquivo JSON."""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"[ERRO] Arquivo nao encontrado: {file_path}")
        return None
    except json.JSONDecodeError as e:
        print(f"[ERRO] JSON invalido em {file_path}: {e}")
        return None


def save_json_file(file_path: Path, data: List, backup: bool = False) -> bool:
    """Salva um arquivo JSON."""
    try:
        # Cria backup se solicitado
        if backup and file_path.exists():
            backup_path = file_path.with_suffix(file_path.suffix + '.backup')
            with open(backup_path, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=2, ensure_ascii=False)
            print(f"[OK] Backup criado: {backup_path}")

        # Salva arquivo
        with open(file_path, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        return True
    except Exception as e:
        print(f"[ERRO] Erro ao salvar {file_path}: {e}")
        return False


def add_versioning_to_entry(entry: Dict, schema_version: str, data_version: str) -> Dict:
    """Adiciona campos de versionamento a uma entrada JSON."""
    # Cria nova entrada com versionamento no início
    new_entry = {
        "SchemaVersion": schema_version,
        "DataVersion": data_version
    }

    # Adiciona campos existentes
    for key, value in entry.items():
        new_entry[key] = value

    return new_entry


def process_json_file(json_path: Path, schema_version: str, data_version: str,
                     dry_run: bool = False, backup: bool = False) -> bool:
    """Processa um arquivo JSON adicionando versionamento."""
    data = load_json_file(json_path)
    if data is None:
        return False

    # Verifica se já tem versionamento
    if isinstance(data, list) and len(data) > 0:
        first_entry = data[0]
        if "SchemaVersion" in first_entry and "DataVersion" in first_entry:
            print(f"[AVISO] {json_path.name} ja tem versionamento (SchemaVersion: {first_entry.get('SchemaVersion')}, DataVersion: {first_entry.get('DataVersion')})")
            return True

    # Adiciona versionamento a cada entrada
    if isinstance(data, list):
        updated_data = []
        for entry in data:
            updated_entry = add_versioning_to_entry(entry, schema_version, data_version)
            updated_data.append(updated_entry)

        if not dry_run:
            return save_json_file(json_path, updated_data, backup)
        else:
            print(f"[DRY RUN] Adicionaria versionamento a {len(updated_data)} entradas em {json_path.name}")
            return True
    else:
        print(f"[ERRO] {json_path.name} nao e um array JSON")
        return False


def main():
    import argparse

    parser = argparse.ArgumentParser(description='Adiciona campos de versionamento aos JSONs')
    parser.add_argument('--dry-run', action='store_true', help='Simula sem modificar arquivos')
    parser.add_argument('--backup', action='store_true', help='Cria backup antes de modificar')
    parser.add_argument('--schema-version', type=str, default=SCHEMA_VERSION,
                        help=f'Versao do schema (padrao: {SCHEMA_VERSION})')
    parser.add_argument('--data-version', type=str, default=DATA_VERSION,
                        help=f'Versao dos dados (padrao: {DATA_VERSION})')

    args = parser.parse_args()

    # Diretório de JSONs
    project_root = Path(__file__).parent.parent
    json_dir = project_root / 'Content' / 'Data' / 'JSON'

    if not json_dir.exists():
        print(f"[ERRO] Diretorio JSON nao encontrado: {json_dir}")
        sys.exit(1)

    print(f"Adicionando versionamento aos arquivos JSON...\n")
    print(f"SchemaVersion: {args.schema_version}")
    print(f"DataVersion: {args.data_version}\n")

    if args.dry_run:
        print("[DRY RUN] Nenhum arquivo sera modificado\n")

    success_count = 0
    total_count = len(JSON_FILES)

    for json_file in JSON_FILES:
        json_path = json_dir / json_file
        if json_path.exists():
            if process_json_file(json_path, args.schema_version, args.data_version,
                               args.dry_run, args.backup):
                success_count += 1
        else:
            print(f"[AVISO] Arquivo nao encontrado: {json_file}")

    if args.dry_run:
        print(f"\n[DRY RUN] {success_count}/{total_count} arquivos seriam processados")
    else:
        print(f"\n[OK] Processamento concluido: {success_count}/{total_count} arquivos processados")

    return 0 if success_count == total_count else 1


if __name__ == '__main__':
    sys.exit(main())

