#!/usr/bin/env python3
"""
Script para gerar changelog de mudanças de schema.

Compara versões de schema entre commits ou arquivos e gera log de mudanças.

Uso:
    python scripts/schema_changelog.py --compare-file Content/Data/JSON/RaceDataTable.json.backup
    python scripts/schema_changelog.py --list-versions
"""

import json
import sys
from pathlib import Path
from typing import Dict, List, Set, Tuple
from datetime import datetime

# Diretório de JSONs
JSON_DIR = Path(__file__).parent.parent / 'Content' / 'Data' / 'JSON'


def load_json_file(file_path: Path) -> List:
    """Carrega um arquivo JSON."""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            return json.load(f)
    except FileNotFoundError:
        return None
    except json.JSONDecodeError:
        return None


def extract_versions(data: List) -> Dict[str, Set[str]]:
    """Extrai versões de schema e dados de um arquivo JSON."""
    schema_versions = set()
    data_versions = set()

    for entry in data:
        if isinstance(entry, dict):
            if "SchemaVersion" in entry:
                schema_versions.add(entry["SchemaVersion"])
            if "DataVersion" in entry:
                data_versions.add(entry["DataVersion"])

    return {
        "schema_versions": schema_versions,
        "data_versions": data_versions
    }


def compare_entries(old_entry: Dict, new_entry: Dict) -> List[str]:
    """Compara duas entradas e retorna lista de mudanças."""
    changes = []

    # Compara SchemaVersion
    old_schema = old_entry.get("SchemaVersion", "N/A")
    new_schema = new_entry.get("SchemaVersion", "N/A")
    if old_schema != new_schema:
        changes.append(f"SchemaVersion: {old_schema} -> {new_schema}")

    # Compara DataVersion
    old_data = old_entry.get("DataVersion", "N/A")
    new_data = new_entry.get("DataVersion", "N/A")
    if old_data != new_data:
        changes.append(f"DataVersion: {old_data} -> {new_data}")

    # Compara campos principais
    for key in ["Name", "ID"]:
        if old_entry.get(key) != new_entry.get(key):
            changes.append(f"{key}: {old_entry.get(key)} -> {new_entry.get(key)}")

    return changes


def list_versions(json_path: Path) -> None:
    """Lista versões de schema e dados de um arquivo JSON."""
    data = load_json_file(json_path)
    if data is None:
        print(f"[ERRO] Nao foi possivel carregar {json_path.name}")
        return

    versions = extract_versions(data)

    print(f"\n{json_path.name}:")
    print(f"  Schema Versions: {sorted(versions['schema_versions'])}")
    print(f"  Data Versions: {sorted(versions['data_versions'])}")


def compare_files(old_path: Path, new_path: Path) -> None:
    """Compara dois arquivos JSON e mostra mudanças."""
    old_data = load_json_file(old_path)
    new_data = load_json_file(new_path)

    if old_data is None or new_data is None:
        print(f"[ERRO] Nao foi possivel carregar arquivos para comparacao")
        return

    # Cria mapas por ID para comparação
    old_map = {entry.get("ID"): entry for entry in old_data if isinstance(entry, dict) and "ID" in entry}
    new_map = {entry.get("ID"): entry for entry in new_data if isinstance(entry, dict) and "ID" in entry}

    print(f"\nComparando {old_path.name} e {new_path.name}:")

    # Entradas removidas
    removed = set(old_map.keys()) - set(new_map.keys())
    if removed:
        print(f"\n  Removidas ({len(removed)}):")
        for id in sorted(removed):
            print(f"    - {id}")

    # Entradas adicionadas
    added = set(new_map.keys()) - set(old_map.keys())
    if added:
        print(f"\n  Adicionadas ({len(added)}):")
        for id in sorted(added):
            print(f"    - {id}")

    # Entradas modificadas
    modified = []
    for id in set(old_map.keys()) & set(new_map.keys()):
        changes = compare_entries(old_map[id], new_map[id])
        if changes:
            modified.append((id, changes))

    if modified:
        print(f"\n  Modificadas ({len(modified)}):")
        for id, changes in modified:
            print(f"    - {id}:")
            for change in changes:
                print(f"      {change}")


def main():
    import argparse

    parser = argparse.ArgumentParser(description='Gera changelog de mudanças de schema')
    parser.add_argument('--compare-file', type=str, help='Arquivo para comparar (ex: backup)')
    parser.add_argument('--list-versions', action='store_true', help='Lista versões de todos os arquivos')
    parser.add_argument('--file', type=str, help='Arquivo específico para processar')

    args = parser.parse_args()

    if args.list_versions:
        # Lista versões de todos os arquivos
        json_files = sorted(JSON_DIR.glob("*.json"))
        json_files = [f for f in json_files if not f.name.startswith(".") and "backup" not in f.name]

        print("Versoes de Schema e Dados:\n")
        for json_file in json_files:
            list_versions(json_file)

    elif args.compare_file:
        # Compara arquivo específico
        compare_path = Path(args.compare_file)
        if not compare_path.is_absolute():
            compare_path = JSON_DIR / compare_path.name

        if args.file:
            current_path = JSON_DIR / args.file
        else:
            # Tenta encontrar arquivo correspondente
            current_path = JSON_DIR / compare_path.stem.replace(".backup", "") / compare_path.suffix

        if not current_path.exists():
            # Tenta sem extensão .backup
            current_path = JSON_DIR / compare_path.name.replace(".backup", "")

        if current_path.exists():
            compare_files(compare_path, current_path)
        else:
            print(f"[ERRO] Arquivo atual nao encontrado: {current_path}")
            sys.exit(1)

    else:
        parser.print_help()
        sys.exit(1)

    return 0


if __name__ == '__main__':
    sys.exit(main())
