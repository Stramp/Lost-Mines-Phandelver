#!/usr/bin/env python3
"""
Script para migrar ClassDataTable.json de estrutura aninhada para estrutura flat.

Transformações:
- Remove aninhamento FClass
- Move campos para nível raiz
- Converte Proficiencies[] para arrays de handles separados
- Mantém Progression no nível raiz (já estava)
"""

import json
import sys
from pathlib import Path

def convert_proficiencies_to_handles(proficiencies_entry):
    """Converte FProficienciesEntry para arrays de handles separados."""
    weapon_handles = []
    armor_handles = []
    saving_throw_handles = []
    skill_handles = []
    skill_choice_count = 0

    if not proficiencies_entry:
        return weapon_handles, armor_handles, saving_throw_handles, skill_handles, skill_choice_count

    # Pega primeiro elemento (geralmente só tem um)
    entry = proficiencies_entry[0] if isinstance(proficiencies_entry, list) and len(proficiencies_entry) > 0 else proficiencies_entry

    # Converte armas para handles
    if "armas" in entry:
        for weapon_id in entry["armas"]:
            weapon_handles.append({
                "DataTable": "/Game/Data/ProficiencyDataTable",
                "RowName": weapon_id
            })

    # Converte armaduras para handles
    if "armaduras" in entry:
        for armor_id in entry["armaduras"]:
            armor_handles.append({
                "DataTable": "/Game/Data/ProficiencyDataTable",
                "RowName": armor_id
            })

    # Converte SavingThrowIDs para handles
    if "SavingThrowIDs" in entry:
        for ability_id in entry["SavingThrowIDs"]:
            saving_throw_handles.append({
                "DataTable": "/Game/Data/AbilityScoreDataTable",
                "RowName": ability_id
            })

    # Converte FSkills para handles
    if "FSkills" in entry:
        fskills = entry["FSkills"]
        if "AvailableSkillHandles" in fskills:
            skill_handles = fskills["AvailableSkillHandles"]
        if "Count" in fskills:
            skill_choice_count = fskills["Count"]

    return weapon_handles, armor_handles, saving_throw_handles, skill_handles, skill_choice_count

def convert_progression_to_handles(progression):
    """Converte Progression para usar FeatureHandles."""
    if not progression:
        return []

    result = []
    for entry in progression:
        level_entry = {
            "Level": entry.get("Level", 1)
        }

        # Converte Features (FName[]) para FeatureHandles
        feature_handles = []
        if "Features" in entry:
            for feature_id in entry["Features"]:
                feature_handles.append({
                    "DataTable": "/Game/Data/FeatureDataTable",
                    "RowName": feature_id
                })

        level_entry["FeatureHandles"] = feature_handles
        result.append(level_entry)

    return result

def migrate_class_entry(class_entry):
    """Migra uma entrada de classe para estrutura flat."""
    if "FClass" not in class_entry:
        # Já está migrado ou estrutura inválida
        return class_entry

    fclass = class_entry["FClass"]

    # Cria nova estrutura flat
    new_entry = {
        "Name": class_entry.get("Name", ""),
        "ID": class_entry.get("ID", ""),
        "TypeTags": class_entry.get("TypeTags", []),
        "ClassName": fclass.get("Name", ""),
        "HitDie": fclass.get("HitDie", 6),
        "MulticlassRequirements": fclass.get("MulticlassRequirements", []),
    }

    # Converte Proficiencies para arrays de handles
    weapon_handles, armor_handles, saving_throw_handles, skill_handles, skill_choice_count = \
        convert_proficiencies_to_handles(fclass.get("Proficiencies", []))

    new_entry["WeaponProficiencyHandles"] = weapon_handles
    new_entry["ArmorProficiencyHandles"] = armor_handles
    new_entry["SavingThrowHandles"] = saving_throw_handles
    new_entry["AvailableSkillHandles"] = skill_handles
    new_entry["SkillChoiceCount"] = skill_choice_count

    # Converte Progression (já está no nível raiz, mas precisa converter Features para Handles)
    if "Progression" in class_entry:
        new_entry["Progression"] = convert_progression_to_handles(class_entry["Progression"])
    elif "Progression" in fclass:
        new_entry["Progression"] = convert_progression_to_handles(fclass["Progression"])
    else:
        new_entry["Progression"] = []

    # StartingEquipment e StartingGold (já estão no nível raiz ou em FClass)
    if "StartingEquipment" in class_entry:
        new_entry["StartingEquipment"] = class_entry["StartingEquipment"]
    elif "StartingEquipment" in fclass:
        new_entry["StartingEquipment"] = fclass["StartingEquipment"]
    else:
        new_entry["StartingEquipment"] = []

    if "StartingGold" in class_entry:
        new_entry["StartingGold"] = class_entry["StartingGold"]
    elif "StartingGold" in fclass:
        new_entry["StartingGold"] = fclass["StartingGold"]
    else:
        new_entry["StartingGold"] = 0

    return new_entry

def main():
    if len(sys.argv) < 3:
        print("Uso: python migrate_class_json_flat.py <input.json> <output.json>")
        sys.exit(1)

    input_path = Path(sys.argv[1])
    output_path = Path(sys.argv[2])

    if not input_path.exists():
        print(f"Erro: Arquivo de entrada não encontrado: {input_path}")
        sys.exit(1)

    # Lê JSON de entrada
    with open(input_path, 'r', encoding='utf-8') as f:
        data = json.load(f)

    # Migra cada entrada
    migrated_data = []
    for entry in data:
        migrated_entry = migrate_class_entry(entry)
        migrated_data.append(migrated_entry)

    # Salva JSON migrado
    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(migrated_data, f, indent=2, ensure_ascii=False)

    print(f"Migração concluída: {len(migrated_data)} classes migradas")
    print(f"Arquivo salvo em: {output_path}")

if __name__ == "__main__":
    main()
