#!/usr/bin/env python3
"""
Script para validar referências AbilityID no ClassDataTable.json.
Verifica se todos os AbilityIDs referenciados existem no AbilityScoreDataTable.json.
"""

import json
import sys
from pathlib import Path

def load_json_file(file_path):
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

def extract_ability_ids_from_class_table(class_data):
    """Extrai todos os AbilityIDs referenciados no ClassDataTable."""
    ability_ids = set()

    for entry in class_data:
        for group in entry.get('MulticlassRequirementGroups', []):
            for req in group.get('Requirements', []):
                ability_id = req.get('AbilityID')
                if ability_id:
                    ability_ids.add(ability_id)

    return ability_ids

def extract_ability_ids_from_ability_table(ability_data):
    """Extrai todos os AbilityIDs válidos do AbilityScoreDataTable."""
    ability_ids = set()

    for entry in ability_data:
        ability_id = entry.get('ID')
        if ability_id:
            ability_ids.add(ability_id)

    return ability_ids

def main():
    # Caminhos dos arquivos
    project_root = Path(__file__).parent.parent
    class_table_path = project_root / 'Content' / 'Data' / 'JSON' / 'ClassDataTable.json'
    ability_table_path = project_root / 'Content' / 'Data' / 'JSON' / 'AbilityScoreDataTable.json'

    # Carrega JSONs
    class_data = load_json_file(class_table_path)
    ability_data = load_json_file(ability_table_path)

    if not class_data or not ability_data:
        sys.exit(1)

    # Extrai AbilityIDs
    referenced_ids = extract_ability_ids_from_class_table(class_data)
    valid_ids = extract_ability_ids_from_ability_table(ability_data)

    # Valida referências
    invalid_ids = referenced_ids - valid_ids

    print(f"Validando referencias AbilityID...\n")
    print(f"AbilityIDs referenciados: {len(referenced_ids)}")
    print(f"AbilityIDs validos: {len(valid_ids)}")
    print(f"Referencias invalidas: {len(invalid_ids)}\n")

    if invalid_ids:
        print("[ERRO] Referencias invalidas encontradas:")
        for invalid_id in sorted(invalid_ids):
            print(f"  - {invalid_id}")
        print(f"\nAbilityIDs validos disponiveis:")
        for valid_id in sorted(valid_ids):
            print(f"  - {valid_id}")
        sys.exit(1)
    else:
        print("[OK] Todas as referencias AbilityID sao validas!")
        print(f"\nAbilityIDs referenciados:")
        for ref_id in sorted(referenced_ids):
            print(f"  - {ref_id}")
        return 0

if __name__ == '__main__':
    sys.exit(main())
