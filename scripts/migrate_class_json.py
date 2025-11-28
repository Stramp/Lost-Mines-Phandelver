#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para migrar DJ_Class.json para nova estrutura com IDs, Tags e Handles.
Fase 2.2: Modificar DJ_Class.json
"""

import json
import os
import sys

# Mapeamento de AbilityName para AbilityID
ABILITY_NAME_TO_ID = {
    "Strength": "ABL_Strength",
    "Dexterity": "ABL_Dexterity",
    "Constitution": "ABL_Constitution",
    "Intelligence": "ABL_Intelligence",
    "Wisdom": "ABL_Wisdom",
    "Charisma": "ABL_Charisma"
}

# Mapeamento de SkillName para SkillID
SKILL_NAME_TO_ID = {
    "Acrobatics": "PSK_Acrobatics",
    "Animal Handling": "PSK_AnimalHandling",
    "Arcana": "PSK_Arcana",
    "Athletics": "PSK_Athletics",
    "Deception": "PSK_Deception",
    "History": "PSK_History",
    "Insight": "PSK_Insight",
    "Intimidation": "PSK_Intimidation",
    "Investigation": "PSK_Investigation",
    "Medicine": "PSK_Medicine",
    "Nature": "PSK_Nature",
    "Perception": "PSK_Perception",
    "Performance": "PSK_Performance",
    "Persuasion": "PSK_Persuasion",
    "Religion": "PSK_Religion",
    "Sleight of Hand": "PSK_SleightOfHand",
    "Stealth": "PSK_Stealth",
    "Survival": "PSK_Survival"
}

# Mapeamento de ClassName para ClassID e Tags
CLASS_NAME_TO_ID_AND_TAGS = {
    "Fighter": ("CLASS_Fighter", ["Class.Fighter", "Class.Martial"]),
    "Wizard": ("CLASS_Wizard", ["Class.Wizard", "Class.Spellcaster"]),
    "Barbarian": ("CLASS_Barbarian", ["Class.Barbarian", "Class.Martial"]),
    "Bard": ("CLASS_Bard", ["Class.Bard", "Class.Spellcaster"]),
    "Cleric": ("CLASS_Cleric", ["Class.Cleric", "Class.Spellcaster"]),
    "Druid": ("CLASS_Druid", ["Class.Druid", "Class.Spellcaster"]),
    "Monk": ("CLASS_Monk", ["Class.Monk", "Class.Martial"]),
    "Paladin": ("CLASS_Paladin", ["Class.Paladin", "Class.Martial", "Class.Spellcaster"]),
    "Ranger": ("CLASS_Ranger", ["Class.Ranger", "Class.Martial", "Class.Spellcaster"]),
    "Rogue": ("CLASS_Rogue", ["Class.Rogue", "Class.Martial"]),
    "Sorcerer": ("CLASS_Sorcerer", ["Class.Sorcerer", "Class.Spellcaster"]),
    "Warlock": ("CLASS_Warlock", ["Class.Warlock", "Class.Spellcaster"])
}


def convert_saving_throws_to_ids(saving_throws):
    """Converte savingThrows[] (strings) para SavingThrowIDs[] (IDs)"""
    result = []
    for st in saving_throws:
        ability_id = ABILITY_NAME_TO_ID.get(st, f"ABL_{st}")
        result.append(ability_id)
    return result


def convert_skills_to_handles(skills):
    """Converte FSkills.available[] (strings) para AvailableSkillHandles[] (FDataTableRowHandle)"""
    result = []
    for skill in skills:
        skill_id = SKILL_NAME_TO_ID.get(skill, f"PSK_{skill.replace(' ', '')}")
        result.append({
            "DataTable": "/Game/Data/SkillDataTable",
            "RowName": skill_id
        })
    return result


def migrate_class_entry(class_entry):
    """Migra uma entrada de classe para nova estrutura"""
    class_name_key = class_entry.get("Name", "").replace("Class_", "")
    fclass = class_entry.get("FClass", {})
    class_name = fclass.get("Name", class_name_key)

    class_id, type_tags = CLASS_NAME_TO_ID_AND_TAGS.get(class_name, (f"CLASS_{class_name}", ["Class.Unknown"]))

    new_entry = {
        "Name": class_entry.get("Name", ""),
        "ClassID": class_id,
        "TypeTags": type_tags,
        "FClass": {
            "Name": class_name,
            "HitDie": fclass.get("HitDie", 6),
            "MulticlassRequirements": fclass.get("MulticlassRequirements", []),
            "Proficiencies": []
        },
        "Progression": fclass.get("Progression", []),
        "StartingEquipment": fclass.get("StartingEquipment", []),
        "StartingGold": fclass.get("StartingGold", 0)
    }

    # Migrar Proficiencies
    proficiencies = fclass.get("Proficiencies", [])
    if proficiencies:
        prof_entry = proficiencies[0]
        new_prof_entry = {
            "armas": prof_entry.get("armas", []),
            "armaduras": prof_entry.get("armaduras", []),
            "SavingThrowIDs": convert_saving_throws_to_ids(prof_entry.get("savingThrows", []))
        }

        # Migrar FSkills
        fskills = prof_entry.get("FSkills", {})
        if fskills:
            available_skills = fskills.get("available", [])
            new_prof_entry["FSkills"] = {
                "AvailableSkillHandles": convert_skills_to_handles(available_skills),
                "Count": fskills.get("qtdAvailable", 0)
            }
        else:
            new_prof_entry["FSkills"] = {
                "AvailableSkillHandles": [],
                "Count": 0
            }

        new_entry["FClass"]["Proficiencies"] = [new_prof_entry]

    return new_entry


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    input_file = os.path.join(project_root, "Content", "Data", "JSON", "DJ_Class.json")
    output_file = os.path.join(project_root, "Content", "Data", "JSON", "ClassDataTable.json")

    # Ler JSON original
    with open(input_file, 'r', encoding='utf-8') as f:
        classes = json.load(f)

    # Migrar cada entrada
    migrated_classes = [migrate_class_entry(cls) for cls in classes]

    # Salvar JSON migrado
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(migrated_classes, f, indent=2, ensure_ascii=False)

    print(f"Migracao concluida: {len(migrated_classes)} classes migradas")
    print(f"Arquivo salvo em: {output_file}")

    # Estatísticas
    total_saving_throws = sum(
        len(p.get("SavingThrowIDs", []))
        for cls in migrated_classes
        for p in cls.get("FClass", {}).get("Proficiencies", [])
    )
    total_skill_handles = sum(
        len(fs.get("AvailableSkillHandles", []))
        for cls in migrated_classes
        for p in cls.get("FClass", {}).get("Proficiencies", [])
        for fs in [p.get("FSkills", {})]
    )

    print(f"Estatisticas:")
    print(f"   - Total de SavingThrowIDs: {total_saving_throws}")
    print(f"   - Total de AvailableSkillHandles: {total_skill_handles}")


if __name__ == "__main__":
    main()
