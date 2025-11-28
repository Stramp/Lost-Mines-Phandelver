#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para corrigir TODOS os JSONs para seguir padrão Name/ID.
Remove campos duplicados e padroniza nomenclatura.
"""

import json
import sys
from pathlib import Path
from collections import OrderedDict

def fix_feat_json(input_path, output_path):
    """Corrige FeatDataTable.json: FC_ID/FeatID → ID, remove duplicados"""
    with open(input_path, 'r', encoding='utf-8') as f:
        data = json.load(f)

    fixed_count = 0
    for entry in data:
        # Substitui FC_ID por ID
        if "FC_ID" in entry:
            if "ID" not in entry:
                entry["ID"] = entry.pop("FC_ID")
                fixed_count += 1
            else:
                # Se já tem ID, remove FC_ID
                entry.pop("FC_ID")
                fixed_count += 1

        # Remove FeatID (redundante, ID já existe)
        if "FeatID" in entry:
            entry.pop("FeatID")
            fixed_count += 1

        # Reordena: Name, ID primeiro
        if "Name" in entry and "ID" in entry:
            ordered_entry = OrderedDict()
            ordered_entry["Name"] = entry.pop("Name")
            ordered_entry["ID"] = entry.pop("ID")
            # Adiciona resto dos campos
            for key, value in entry.items():
                ordered_entry[key] = value
            # Substitui entry
            entry.clear()
            entry.update(ordered_entry)

    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)

    print(f"FeatDataTable.json corrigido: {len(data)} entradas, {fixed_count} correcoes")

def fix_feature_json(input_path, output_path):
    """Corrige FeatureDataTable.json: FC_ID/FeatureID → ID, remove duplicados"""
    with open(input_path, 'r', encoding='utf-8') as f:
        data = json.load(f)

    fixed_count = 0
    for entry in data:
        # Substitui FC_ID por ID
        if "FC_ID" in entry:
            if "ID" not in entry:
                entry["ID"] = entry.pop("FC_ID")
                fixed_count += 1
            else:
                # Se já tem ID, remove FC_ID
                entry.pop("FC_ID")
                fixed_count += 1

        # Remove FeatureID (redundante, ID já existe)
        if "FeatureID" in entry:
            entry.pop("FeatureID")
            fixed_count += 1

        # Reordena: Name, ID primeiro
        if "Name" in entry and "ID" in entry:
            ordered_entry = OrderedDict()
            ordered_entry["Name"] = entry.pop("Name")
            ordered_entry["ID"] = entry.pop("ID")
            # Adiciona resto dos campos
            for key, value in entry.items():
                ordered_entry[key] = value
            # Substitui entry
            entry.clear()
            entry.update(ordered_entry)

    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)

    print(f"FeatureDataTable.json corrigido: {len(data)} entradas, {fixed_count} correcoes")

def fix_proficiency_json(input_path, output_path):
    """Corrige ProficiencyDataTable.json: ProficiencyID → ID"""
    with open(input_path, 'r', encoding='utf-8') as f:
        data = json.load(f)

    fixed_count = 0
    for entry in data:
        # Substitui ProficiencyID por ID
        if "ProficiencyID" in entry:
            if "ID" not in entry:
                entry["ID"] = entry.pop("ProficiencyID")
                fixed_count += 1
            else:
                # Se já tem ID, remove ProficiencyID
                entry.pop("ProficiencyID")
                fixed_count += 1

        # Reordena: Name, ID primeiro
        if "Name" in entry and "ID" in entry:
            ordered_entry = OrderedDict()
            ordered_entry["Name"] = entry.pop("Name")
            ordered_entry["ID"] = entry.pop("ID")
            # Adiciona resto dos campos
            for key, value in entry.items():
                ordered_entry[key] = value
            # Substitui entry
            entry.clear()
            entry.update(ordered_entry)

    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)

    print(f"ProficiencyDataTable.json corrigido: {len(data)} entradas, {fixed_count} correcoes")

def main():
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    json_dir = project_root / "Content" / "Data" / "JSON"

    files_to_fix = [
        ("FeatDataTable.json", fix_feat_json),
        ("FeatureDataTable.json", fix_feature_json),
        ("ProficiencyDataTable.json", fix_proficiency_json),
    ]

    for filename, fix_func in files_to_fix:
        input_path = json_dir / filename

        if not input_path.exists():
            print(f"Arquivo nao encontrado: {input_path}")
            continue

        # Backup
        import shutil
        backup_path = json_dir / f"{filename}.backup2"
        shutil.copy2(input_path, backup_path)
        print(f"Backup criado: {backup_path}")

        # Correção
        fix_func(input_path, input_path)

    print("\nTodos os JSONs foram corrigidos!")

if __name__ == "__main__":
    main()
