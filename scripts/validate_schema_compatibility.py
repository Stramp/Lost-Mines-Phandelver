#!/usr/bin/env python3
"""
Script para validar compatibilidade de versões de schema.

Verifica se versões de schema são compatíveis e detecta mudanças incompatíveis.

Uso:
    python scripts/validate_schema_compatibility.py
    python scripts/validate_schema_compatibility.py --min-version 1.0.0
"""

import json
import sys
from pathlib import Path
from typing import Dict, List, Tuple, Optional
from packaging import version

# Versão mínima suportada
MIN_SCHEMA_VERSION = "1.0.0"


def parse_version(version_str: str) -> Optional[version.Version]:
    """Converte string de versão para objeto Version."""
    try:
        return version.parse(version_str)
    except version.InvalidVersion:
        return None


def load_json_file(file_path: Path) -> List:
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


def validate_schema_version(entry: Dict, file_name: str, min_version: str) -> Tuple[bool, List[str]]:
    """Valida versão de schema de uma entrada."""
    errors = []

    # Verifica se tem SchemaVersion
    if "SchemaVersion" not in entry:
        errors.append(f"Entrada sem SchemaVersion em {file_name}")
        return False, errors

    schema_version_str = entry.get("SchemaVersion", "")
    schema_version = parse_version(schema_version_str)

    if schema_version is None:
        errors.append(f"SchemaVersion invalido em {file_name}: {schema_version_str}")
        return False, errors

    min_ver = parse_version(min_version)
    if min_ver and schema_version < min_ver:
        errors.append(f"SchemaVersion {schema_version_str} abaixo da versao minima {min_version} em {file_name}")
        return False, errors

    # Verifica se tem DataVersion
    if "DataVersion" not in entry:
        errors.append(f"Entrada sem DataVersion em {file_name}")
        return False, errors

    data_version = entry.get("DataVersion", "")
    if not data_version or len(data_version) != 10:  # YYYY-MM-DD
        errors.append(f"DataVersion invalido em {file_name}: {data_version}")
        return False, errors

    return True, errors


def validate_file_compatibility(json_path: Path, min_version: str) -> Tuple[bool, List[str]]:
    """Valida compatibilidade de versões em um arquivo JSON."""
    data = load_json_file(json_path)
    if data is None:
        return False, [f"Erro ao carregar {json_path.name}"]

    if not isinstance(data, list):
        return False, [f"{json_path.name} nao e um array JSON"]

    all_errors = []
    schema_versions = set()
    data_versions = set()

    for i, entry in enumerate(data):
        is_valid, errors = validate_schema_version(entry, f"{json_path.name}[{i}]", min_version)
        if not is_valid:
            all_errors.extend(errors)
        else:
            schema_versions.add(entry.get("SchemaVersion"))
            data_versions.add(entry.get("DataVersion"))

    # Verifica consistência de versões
    if len(schema_versions) > 1:
        all_errors.append(f"{json_path.name} tem multiplas versoes de schema: {schema_versions}")

    if len(data_versions) > 1:
        all_errors.append(f"{json_path.name} tem multiplas versoes de dados: {data_versions}")

    return len(all_errors) == 0, all_errors


def main():
    import argparse

    parser = argparse.ArgumentParser(description='Valida compatibilidade de versões de schema')
    parser.add_argument('--min-version', type=str, default=MIN_SCHEMA_VERSION,
                        help=f'Versao minima suportada (padrao: {MIN_SCHEMA_VERSION})')
    parser.add_argument('--file', type=str, help='Validar apenas um arquivo JSON específico')

    args = parser.parse_args()

    # Diretório de JSONs
    project_root = Path(__file__).parent.parent
    json_dir = project_root / 'Content' / 'Data' / 'JSON'

    if not json_dir.exists():
        print(f"[ERRO] Diretorio JSON nao encontrado: {json_dir}")
        sys.exit(1)

    print(f"Validando compatibilidade de versoes de schema...\n")
    print(f"Versao minima: {args.min_version}\n")

    if args.file:
        # Valida arquivo único
        json_path = json_dir / args.file
        if not json_path.exists():
            print(f"[ERRO] Arquivo nao encontrado: {json_path}")
            sys.exit(1)

        is_valid, errors = validate_file_compatibility(json_path, args.min_version)
        if is_valid:
            print(f"[OK] {json_path.name}: Compativel")
        else:
            print(f"[ERRO] {json_path.name}: Incompativel")
            for error in errors:
                print(f"  - {error}")
            sys.exit(1)
    else:
        # Valida todos os arquivos
        json_files = sorted(json_dir.glob("*.json"))
        json_files = [f for f in json_files if f.name != "Schemas"]  # Exclui diretório Schemas

        valid_count = 0
        total_count = len(json_files)
        all_errors = []

        for json_path in json_files:
            is_valid, errors = validate_file_compatibility(json_path, args.min_version)
            if is_valid:
                print(f"[OK] {json_path.name}: Compativel")
                valid_count += 1
            else:
                print(f"[ERRO] {json_path.name}: Incompativel")
                for error in errors:
                    print(f"  - {error}")
                    all_errors.append(f"{json_path.name}: {error}")

        print(f"\nResumo: {valid_count}/{total_count} arquivos compativeis")

        if all_errors:
            print(f"\nTotal de erros: {len(all_errors)}")
            sys.exit(1)

    return 0


if __name__ == '__main__':
    try:
        from packaging import version
    except ImportError:
        print("ERRO: Biblioteca 'packaging' nao encontrada.")
        print("Instale com: pip install packaging")
        sys.exit(1)

    sys.exit(main())
