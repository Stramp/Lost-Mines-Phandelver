#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para migrar DJ_FeaturesClass.json para nova estrutura com IDs e Tags.
Fase 2.5: Modificar DJ_FeaturesClass.json
"""

import json
import os
import sys


def migrate_feature_entry(feature_entry):
    """Migra uma entrada de feature para nova estrutura"""
    fc_id = feature_entry.get("FC_ID", "")
    feature_name = feature_entry.get("Name", "")
    feature_type = feature_entry.get("FeatureType", "Automatic")

    # FeatureID é alias do FC_ID
    feature_id = fc_id

    # TypeTags baseado no nome e tipo da feature
    type_tags = [f"Feature.{feature_name.replace(' ', '')}"]

    # Adicionar tags baseado no tipo
    if feature_type == "Combat":
        type_tags.append("Feature.Combat")
    elif feature_type == "Spellcasting":
        type_tags.append("Feature.Spellcasting")
    elif "Spell" in feature_name or "Magic" in feature_name:
        type_tags.append("Feature.Spellcasting")
    elif "Attack" in feature_name or "Fighting" in feature_name or "Weapon" in feature_name:
        type_tags.append("Feature.Combat")

    new_entry = feature_entry.copy()
    new_entry["FeatureID"] = feature_id
    new_entry["TypeTags"] = type_tags

    return new_entry


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    input_file = os.path.join(project_root, "Content", "Data", "JSON", "DJ_FeaturesClass.json")
    output_file = os.path.join(project_root, "Content", "Data", "JSON", "FeatureDataTable.json")

    # Ler JSON original
    with open(input_file, 'r', encoding='utf-8') as f:
        features = json.load(f)

    # Migrar cada entrada
    migrated_features = [migrate_feature_entry(feat) for feat in features]

    # Salvar JSON migrado
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(migrated_features, f, indent=2, ensure_ascii=False)

    print(f"Migracao concluida: {len(migrated_features)} features migradas")
    print(f"Arquivo salvo em: {output_file}")


if __name__ == "__main__":
    main()
