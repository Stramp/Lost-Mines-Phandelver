#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para migrar Background_All.json para nova estrutura com IDs, Tags e Handles.
Fase 2.3: Modificar Background_All.json
"""

import json
import os
import sys

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

# Mapeamento de FeatureName para TraitID (features de background são traits)
FEATURE_NAME_TO_TRAIT_ID = {
    "Shelter of the Faithful": "TR_ShelterOfTheFaithful",
    "Criminal Contact": "TR_CriminalContact",
    "Rustic Hospitality": "TR_RusticHospitality",
    "Position of Privilege": "TR_PositionOfPrivilege",
    "Researcher": "TR_Researcher",
    "Military Rank": "TR_MilitaryRank",
    "Discovery": "TR_Discovery",
    "By Popular Demand": "TR_ByPopularDemand",
    "False Identity": "TR_FalseIdentity",
    "Guild Membership": "TR_GuildMembership",
    "Wanderer": "TR_Wanderer"
}

# Mapeamento de BackgroundName para BackgroundID e Tags
BACKGROUND_NAME_TO_ID_AND_TAGS = {
    "Acolyte": ("BG_Acolyte", ["Background.Acolyte"]),
    "Criminal": ("BG_Criminal", ["Background.Criminal"]),
    "Folk Hero": ("BG_FolkHero", ["Background.FolkHero"]),
    "Noble": ("BG_Noble", ["Background.Noble"]),
    "Sage": ("BG_Sage", ["Background.Sage"]),
    "Soldier": ("BG_Soldier", ["Background.Soldier"]),
    "Hermit": ("BG_Hermit", ["Background.Hermit"]),
    "Entertainer": ("BG_Entertainer", ["Background.Entertainer"]),
    "Guild Artisan": ("BG_GuildArtisan", ["Background.GuildArtisan"]),
    "Outlander": ("BG_Outlander", ["Background.Outlander"])
}


def convert_skill_proficiencies_to_handles(skills):
    """Converte SkillProficiencies[] (strings) para SkillProficiencyHandles[] (FDataTableRowHandle)"""
    result = []
    for skill in skills:
        skill_id = SKILL_NAME_TO_ID.get(skill, f"PSK_{skill.replace(' ', '')}")
        result.append({
            "DataTable": "/Game/Data/SkillDataTable",
            "RowName": skill_id
        })
    return result


def convert_languages_to_handles(languages):
    """Converte Languages[] para LanguageHandles[]"""
    result = []
    for lang in languages:
        lang_id = f"PL_{lang}"
        result.append({
            "DataTable": "/Game/Data/LanguageDataTable",
            "RowName": lang_id
        })
    return result


def convert_feature_name_to_handle(feature_name):
    """Converte FeatureName (string) para FeatureHandle (FDataTableRowHandle)"""
    if not feature_name:
        return None

    trait_id = FEATURE_NAME_TO_TRAIT_ID.get(feature_name, f"TR_{feature_name.replace(' ', '')}")
    return {
        "DataTable": "/Game/Data/TraitDataTable",
        "RowName": trait_id
    }


def migrate_background_entry(bg_entry):
    """Migra uma entrada de background para nova estrutura"""
    bg_name = bg_entry.get("BackgroundName", bg_entry.get("Name", ""))
    bg_id, type_tags = BACKGROUND_NAME_TO_ID_AND_TAGS.get(bg_name, (f"BG_{bg_name.replace(' ', '')}", ["Background.Unknown"]))

    new_entry = {
        "BackgroundID": bg_id,
        "Name": bg_entry.get("Name", ""),
        "BackgroundName": bg_name,
        "Description": bg_entry.get("Description", ""),
        "TypeTags": type_tags,
        "SkillProficiencyHandles": convert_skill_proficiencies_to_handles(
            bg_entry.get("SkillProficiencies", [])
        ),
        "LanguageHandles": convert_languages_to_handles(
            bg_entry.get("Languages", [])
        ),
        "LanguageChoices": bg_entry.get("LanguageChoices", {"Count": 0}),
        "Equipment": bg_entry.get("Equipment", [])
    }

    # Converter FeatureName para FeatureHandle
    feature_name = bg_entry.get("FeatureName", "")
    if feature_name:
        new_entry["FeatureHandle"] = convert_feature_name_to_handle(feature_name)
        new_entry["FeatureDescription"] = bg_entry.get("FeatureDescription", "")
    else:
        new_entry["FeatureHandle"] = None
        new_entry["FeatureDescription"] = ""

    return new_entry


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    input_file = os.path.join(project_root, "Content", "Data", "JSON", "Background_All.json")
    output_file = os.path.join(project_root, "Content", "Data", "JSON", "BackgroundDataTable.json")

    # Ler JSON original
    with open(input_file, 'r', encoding='utf-8') as f:
        backgrounds = json.load(f)

    # Migrar cada entrada
    migrated_backgrounds = [migrate_background_entry(bg) for bg in backgrounds]

    # Salvar JSON migrado
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(migrated_backgrounds, f, indent=2, ensure_ascii=False)

    print(f"Migracao concluida: {len(migrated_backgrounds)} backgrounds migrados")
    print(f"Arquivo salvo em: {output_file}")

    # Estatísticas
    total_skill_handles = sum(len(bg.get("SkillProficiencyHandles", [])) for bg in migrated_backgrounds)
    total_language_handles = sum(len(bg.get("LanguageHandles", [])) for bg in migrated_backgrounds)
    total_features = sum(1 for bg in migrated_backgrounds if bg.get("FeatureHandle"))

    print(f"Estatisticas:")
    print(f"   - Total de SkillProficiencyHandles: {total_skill_handles}")
    print(f"   - Total de LanguageHandles: {total_language_handles}")
    print(f"   - Total de FeatureHandles: {total_features}")


if __name__ == "__main__":
    main()
