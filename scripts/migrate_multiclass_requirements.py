#!/usr/bin/env python3
"""
Script de migração para normalizar MulticlassRequirements em ClassDataTable.json.

Converte formato antigo (string) para estrutura normalizada:
- Antigo: ["STR/13|DEX/13"] (OR) ou ["STR/13", "DEX/13"] (AND)
- Novo: [{"Operator": "OR", "Requirements": [{"AbilityID": "ABL_Strength", "Value": 13}, ...]}]

Uso:
    python scripts/migrate_multiclass_requirements.py
    python scripts/migrate_multiclass_requirements.py --backup
    python scripts/migrate_multiclass_requirements.py --dry-run
"""

import json
import os
import re
import sys
from pathlib import Path
from typing import Dict, List, Tuple, Optional

# Mapeamento de abreviações para IDs completos
ABILITY_ABBR_TO_ID = {
    "STR": "ABL_Strength",
    "DEX": "ABL_Dexterity",
    "CON": "ABL_Constitution",
    "INT": "ABL_Intelligence",
    "WIS": "ABL_Wisdom",
    "CHA": "ABL_Charisma",
}


def parse_requirement_string(requirement_str: str) -> List[Tuple[str, int]]:
    """
    Parseia uma string de requisito no formato "STR/13|DEX/13" ou "STR/13".

    Retorna lista de tuplas (AbilityID, Value).
    """
    requirements = []

    # Divide por | (OR) ou & (AND)
    parts = re.split(r'[|&]', requirement_str)

    for part in parts:
        part = part.strip()
        # Formato: "STR/13"
        match = re.match(r'^([A-Z]{3})/(\d+)$', part)
        if match:
            abbr = match.group(1)
            value = int(match.group(2))

            # Converte abreviação para ID completo
            ability_id = ABILITY_ABBR_TO_ID.get(abbr)
            if ability_id:
                requirements.append((ability_id, value))
            else:
                print(f"[AVISO] Abreviacao desconhecida: {abbr}")

    return requirements


def determine_operator(requirement_str: str) -> str:
    """
    Determina o operador lógico baseado na string de requisito.
    - Se contém "|" → OR
    - Se contém "&" → AND
    - Se não contém nenhum → AND (requisito único)
    """
    if "|" in requirement_str:
        return "OR"
    elif "&" in requirement_str:
        return "AND"
    else:
        # Requisito único é tratado como AND
        return "AND"


def convert_multiclass_requirements(old_requirements: List[str]) -> List[Dict]:
    """
    Converte array de strings antigas para nova estrutura normalizada.

    Lógica:
    - Cada string no array antigo vira um grupo (AND entre grupos)
    - Dentro de cada string, | significa OR, & significa AND
    """
    new_groups = []

    for req_str in old_requirements:
        # Parseia requisitos da string
        requirements = parse_requirement_string(req_str)

        if not requirements:
            print(f"[AVISO] Nenhum requisito valido encontrado em: {req_str}")
            continue

        # Determina operador
        operator = determine_operator(req_str)

        # Cria grupo
        group = {
            "Operator": operator,
            "Requirements": [
                {"AbilityID": ability_id, "Value": value}
                for ability_id, value in requirements
            ]
        }

        new_groups.append(group)

    return new_groups


def migrate_class_data_table(json_path: Path, backup: bool = False, dry_run: bool = False) -> bool:
    """
    Migra ClassDataTable.json convertendo MulticlassRequirements.

    Retorna True se migração foi bem-sucedida, False caso contrário.
    """
    if not json_path.exists():
        print(f"❌ ERRO: Arquivo não encontrado: {json_path}")
        return False

    # Carrega JSON
    try:
        with open(json_path, "r", encoding="utf-8") as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        print(f"[ERRO] JSON invalido: {e}")
        return False

    # Backup
    if backup and not dry_run:
        backup_path = json_path.with_suffix(".json.backup")
        with open(backup_path, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        print(f"[OK] Backup criado: {backup_path}")

    # Migra cada entrada
    migrated_count = 0
    for entry in data:
        if "MulticlassRequirements" not in entry:
            continue

        old_requirements = entry.get("MulticlassRequirements", [])
        if not old_requirements:
            continue

        # Converte
        new_groups = convert_multiclass_requirements(old_requirements)

        if new_groups:
            # Adiciona novo campo
            entry["MulticlassRequirementGroups"] = new_groups

            # Mantém campo antigo para compatibilidade (comentado ou removido)
            # entry["MulticlassRequirements"] = old_requirements  # Mantido para referência

            migrated_count += 1
            print(f"[OK] Migrado: {entry.get('Name', 'Unknown')} - {len(new_groups)} grupo(s)")

    # Salva JSON
    if not dry_run:
        with open(json_path, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        print(f"\n[OK] Migracao concluida: {migrated_count} classe(s) migrada(s)")
    else:
        print(f"\n[DRY RUN] {migrated_count} classe(s) seriam migrada(s)")

    return True


def main():
    """Função principal."""
    import argparse

    parser = argparse.ArgumentParser(
        description="Migra MulticlassRequirements para estrutura normalizada"
    )
    parser.add_argument(
        "--file",
        type=str,
        default="Content/Data/JSON/ClassDataTable.json",
        help="Caminho para ClassDataTable.json (padrão: Content/Data/JSON/ClassDataTable.json)",
    )
    parser.add_argument(
        "--backup",
        action="store_true",
        help="Cria backup do arquivo antes de migrar",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Apenas simula migração sem modificar arquivo",
    )

    args = parser.parse_args()

    json_path = Path(args.file)

    if not json_path.exists():
        print(f"❌ ERRO: Arquivo não encontrado: {json_path}")
        sys.exit(1)

    print(f"Migrando: {json_path}\n")

    success = migrate_class_data_table(json_path, backup=args.backup, dry_run=args.dry_run)

    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()
