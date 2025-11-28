#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para migrar DJ_Proficiencie.json para nova estrutura com Tags.
Fase 2.6: Modificar DJ_Proficiencie.json (já tem ProficiencyID, só adicionar Tags)
"""

import json
import os
import sys


def get_proficiency_type_tags(proficiency_entry):
    """Determina TypeTags baseado no tipo de proficiência"""
    proficiency_id = proficiency_entry.get("ProficiencyID", "")
    proficiency_type = proficiency_entry.get("Type", "")

    type_tags = []

    # Tags baseado no ID
    if proficiency_id.startswith("PW_"):
        type_tags.append("Proficiency.Weapon")
        if "Simple" in proficiency_id:
            type_tags.append("Proficiency.Weapon.Simple")
        elif "Martial" in proficiency_id:
            type_tags.append("Proficiency.Weapon.Martial")
    elif proficiency_id.startswith("PA_"):
        type_tags.append("Proficiency.Armor")
        if "Light" in proficiency_id:
            type_tags.append("Proficiency.Armor.Light")
        elif "Medium" in proficiency_id:
            type_tags.append("Proficiency.Armor.Medium")
        elif "Heavy" in proficiency_id:
            type_tags.append("Proficiency.Armor.Heavy")
    elif proficiency_id.startswith("PS_"):
        type_tags.append("Proficiency.Shield")
    elif proficiency_id.startswith("PT_"):
        type_tags.append("Proficiency.Tool")
    elif proficiency_id.startswith("PL_"):
        type_tags.append("Proficiency.Language")
    elif proficiency_id.startswith("PSK_"):
        type_tags.append("Proficiency.Skill")

    # Tags baseado no Type
    if proficiency_type:
        type_tags.append(f"Proficiency.{proficiency_type}")

    return type_tags if type_tags else ["Proficiency.Unknown"]


def migrate_proficiency_entry(prof_entry):
    """Migra uma entrada de proficiência para nova estrutura"""
    new_entry = prof_entry.copy()
    new_entry["TypeTags"] = get_proficiency_type_tags(prof_entry)
    return new_entry


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    input_file = os.path.join(project_root, "Content", "Data", "JSON", "DJ_Proficiencie.json")
    output_file = os.path.join(project_root, "Content", "Data", "JSON", "ProficiencyDataTable.json")

    # Ler JSON original
    with open(input_file, 'r', encoding='utf-8') as f:
        proficiencies = json.load(f)

    # Migrar cada entrada
    migrated_proficiencies = [migrate_proficiency_entry(prof) for prof in proficiencies]

    # Salvar JSON migrado
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(migrated_proficiencies, f, indent=2, ensure_ascii=False)

    print(f"Migracao concluida: {len(migrated_proficiencies)} proficiencias migradas")
    print(f"Arquivo salvo em: {output_file}")


if __name__ == "__main__":
    main()
