#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para migrar Race_All.json para nova estrutura com IDs, Tags e Handles.
Fase 2.1: Modificar Race_All.json
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
    "Charisma": "ABL_Charisma",
    "Custom": "ABL_Custom"  # Para Variant Human
}

# Mapeamento de TraitName para TraitID
TRAIT_NAME_TO_ID = {
    "Darkvision": "TR_Darkvision",
    "Dwarven Resilience": "TR_DwarvenResilience",
    "Stonecunning": "TR_Stonecunning",
    "Dwarven Toughness": "TR_DwarvenToughness",
    "Dwarven Armor Training": "TR_DwarvenArmorTraining",
    "Fey Ancestry": "TR_FeyAncestry",
    "Trance": "TR_Trance",
    "Elf Weapon Training": "TR_ElfWeaponTraining",
    "Cantrip": "TR_Cantrip",
    "Extra Language": "TR_ExtraLanguage",
    "Fleet of Foot": "TR_FleetOfFoot",
    "Mask of the Wild": "TR_MaskOfTheWild",
    "Superior Darkvision": "TR_SuperiorDarkvision",
    "Sunlight Sensitivity": "TR_SunlightSensitivity",
    "Drow Magic": "TR_DrowMagic",
    "Lucky": "TR_Lucky",
    "Brave": "TR_Brave",
    "Halfling Nimbleness": "TR_HalflingNimbleness",
    "Naturally Stealthy": "TR_NaturallyStealthy",
    "Stout Resilience": "TR_StoutResilience",
    "Skill Proficiency": "TR_SkillProficiency",
    "Feat": "TR_Feat",
    "Draconic Ancestry": "TR_DraconicAncestry",
    "Breath Weapon": "TR_BreathWeapon",
    "Damage Resistance": "TR_DamageResistance",
    "Gnome Cunning": "TR_GnomeCunning",
    "Natural Illusionist": "TR_NaturalIllusionist",
    "Speak with Small Beasts": "TR_SpeakWithSmallBeasts",
    "Artificer's Lore": "TR_ArtificersLore",
    "Tinker": "TR_Tinker",
    "Skill Versatility": "TR_SkillVersatility",
    "Menacing": "TR_Menacing",
    "Relentless Endurance": "TR_RelentlessEndurance",
    "Savage Attacks": "TR_SavageAttacks",
    "Hellish Resistance": "TR_HellishResistance",
    "Infernal Legacy": "TR_InfernalLegacy"
}

# Mapeamento de LanguageName para LanguageID
LANGUAGE_NAME_TO_ID = {
    "Common": "PL_Common",
    "Dwarvish": "PL_Dwarvish",
    "Elvish": "PL_Elvish",
    "Halfling": "PL_Halfling",
    "Orc": "PL_Orc",
    "Gnomish": "PL_Gnomish",
    "Draconic": "PL_Draconic",
    "Infernal": "PL_Infernal"
}

# Mapeamento de RaceName para RaceID
RACE_NAME_TO_ID = {
    "Dwarf": "RACE_Dwarf",
    "Hill Dwarf": "RACE_HillDwarf",
    "Mountain Dwarf": "RACE_MountainDwarf",
    "Elf": "RACE_Elf",
    "High Elf": "RACE_HighElf",
    "Wood Elf": "RACE_WoodElf",
    "Drow": "RACE_Drow",
    "Halfling": "RACE_Halfling",
    "Lightfoot": "RACE_Lightfoot",
    "Stout": "RACE_Stout",
    "Human": "RACE_Human",
    "Standard Human": "RACE_StandardHuman",
    "Variant Human": "RACE_VariantHuman",
    "Dragonborn": "RACE_Dragonborn",
    "Gnome": "RACE_Gnome",
    "Forest Gnome": "RACE_ForestGnome",
    "Rock Gnome": "RACE_RockGnome",
    "Half-Elf": "RACE_HalfElf",
    "Half-Orc": "RACE_HalfOrc",
    "Tiefling": "RACE_Tiefling"
}

# Mapeamento de RaceName para TypeTags
RACE_NAME_TO_TAGS = {
    "Dwarf": ["Race.Dwarf"],
    "Hill Dwarf": ["Race.Dwarf", "Race.Subrace.HillDwarf"],
    "Mountain Dwarf": ["Race.Dwarf", "Race.Subrace.MountainDwarf"],
    "Elf": ["Race.Elf"],
    "High Elf": ["Race.Elf", "Race.Subrace.HighElf"],
    "Wood Elf": ["Race.Elf", "Race.Subrace.WoodElf"],
    "Drow": ["Race.Elf", "Race.Subrace.Drow"],
    "Halfling": ["Race.Halfling"],
    "Lightfoot": ["Race.Halfling", "Race.Subrace.Lightfoot"],
    "Stout": ["Race.Halfling", "Race.Subrace.Stout"],
    "Human": ["Race.Human"],
    "Standard Human": ["Race.Human", "Race.Subrace.StandardHuman"],
    "Variant Human": ["Race.Human", "Race.Subrace.VariantHuman"],
    "Dragonborn": ["Race.Dragonborn"],
    "Gnome": ["Race.Gnome"],
    "Forest Gnome": ["Race.Gnome", "Race.Subrace.ForestGnome"],
    "Rock Gnome": ["Race.Gnome", "Race.Subrace.RockGnome"],
    "Half-Elf": ["Race.HalfElf"],
    "Half-Orc": ["Race.HalfOrc"],
    "Tiefling": ["Race.Tiefling"]
}


def convert_ability_score_improvements(improvements):
    """Converte AbilityName para AbilityID"""
    result = []
    for imp in improvements:
        ability_name = imp.get("AbilityName", "")
        ability_id = ABILITY_NAME_TO_ID.get(ability_name, f"ABL_{ability_name}")
        result.append({
            "AbilityID": ability_id,
            "Bonus": imp.get("Bonus", 0)
        })
    return result


def convert_traits_to_handles(traits):
    """Converte Traits[] para TraitHandles[]"""
    result = []
    for trait in traits:
        trait_name = trait.get("TraitName", "")
        trait_id = TRAIT_NAME_TO_ID.get(trait_name, f"TR_{trait_name.replace(' ', '')}")
        result.append({
            "DataTable": "/Game/Data/TraitDataTable",
            "RowName": trait_id
        })
    return result


def convert_languages_to_handles(languages):
    """Converte Languages[] para LanguageHandles[]"""
    result = []
    for lang in languages:
        lang_id = LANGUAGE_NAME_TO_ID.get(lang, f"PL_{lang}")
        result.append({
            "DataTable": "/Game/Data/LanguageDataTable",
            "RowName": lang_id
        })
    return result


def convert_subrace_names_to_handles(subrace_names):
    """Converte SubraceNames[] para SubraceHandles[]"""
    result = []
    for subrace_name in subrace_names:
        subrace_id = RACE_NAME_TO_ID.get(subrace_name, f"RACE_{subrace_name.replace(' ', '')}")
        result.append({
            "DataTable": "/Game/Data/RaceDataTable",
            "RowName": subrace_id
        })
    return result


def migrate_race_entry(race_entry):
    """Migra uma entrada de raça para nova estrutura"""
    race_name = race_entry.get("RaceName", race_entry.get("Name", ""))
    race_id = RACE_NAME_TO_ID.get(race_name, f"RACE_{race_name.replace(' ', '')}")
    type_tags = RACE_NAME_TO_TAGS.get(race_name, ["Race.Unknown"])

    new_entry = {
        "RaceID": race_id,
        "Name": race_entry.get("Name", ""),
        "RaceName": race_name,
        "Description": race_entry.get("Description", ""),
        "TypeTags": type_tags,
        "AbilityScoreImprovements": convert_ability_score_improvements(
            race_entry.get("AbilityScoreImprovements", [])
        ),
        "Size": race_entry.get("Size", "Medium"),
        "BaseSpeed": race_entry.get("BaseSpeed", 30)
    }

    # Converter Traits para TraitHandles
    if "Traits" in race_entry and race_entry["Traits"]:
        new_entry["TraitHandles"] = convert_traits_to_handles(race_entry["Traits"])
    else:
        new_entry["TraitHandles"] = []

    # Converter Languages para LanguageHandles
    if "Languages" in race_entry and race_entry["Languages"]:
        new_entry["LanguageHandles"] = convert_languages_to_handles(race_entry["Languages"])
    else:
        new_entry["LanguageHandles"] = []

    # Converter SubraceNames para SubraceHandles
    if "SubraceNames" in race_entry and race_entry["SubraceNames"]:
        new_entry["SubraceHandles"] = convert_subrace_names_to_handles(race_entry["SubraceNames"])
    else:
        new_entry["SubraceHandles"] = []

    return new_entry


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    input_file = os.path.join(project_root, "Content", "Data", "JSON", "Race_All.json")
    output_file = os.path.join(project_root, "Content", "Data", "JSON", "RaceDataTable.json")

    # Ler JSON original
    with open(input_file, 'r', encoding='utf-8') as f:
        races = json.load(f)

    # Migrar cada entrada
    migrated_races = [migrate_race_entry(race) for race in races]

    # Salvar JSON migrado
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(migrated_races, f, indent=2, ensure_ascii=False)

    print(f"Migracao concluida: {len(migrated_races)} racas migradas")
    print(f"Arquivo salvo em: {output_file}")

    # Estatísticas
    total_traits = sum(len(r.get("TraitHandles", [])) for r in migrated_races)
    total_languages = sum(len(r.get("LanguageHandles", [])) for r in migrated_races)
    total_subraces = sum(len(r.get("SubraceHandles", [])) for r in migrated_races)

    print(f"Estatisticas:")
    print(f"   - Total de TraitHandles: {total_traits}")
    print(f"   - Total de LanguageHandles: {total_languages}")
    print(f"   - Total de SubraceHandles: {total_subraces}")


if __name__ == "__main__":
    main()
