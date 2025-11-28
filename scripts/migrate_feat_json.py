#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para migrar DJ_FeatsGerais.json para nova estrutura com IDs e Tags.
Fase 2.4: Modificar DJ_FeatsGerais.json
"""

import json
import os
import sys


def migrate_feat_entry(feat_entry):
    """Migra uma entrada de feat para nova estrutura"""
    fc_id = feat_entry.get("FC_ID", "")
    feat_name = feat_entry.get("Name", "")

    # Extrair FeatID do FC_ID (ex: "Feat_Alert" -> "FEAT_Alert")
    if fc_id.startswith("Feat_"):
        feat_id = f"FEAT_{fc_id[5:]}"  # Remove "Feat_" e adiciona "FEAT_"
    else:
        feat_id = f"FEAT_{feat_name.replace(' ', '')}"

    # TypeTags baseado no nome do feat
    type_tags = [f"Feat.{feat_name.replace(' ', '')}"]

    # Adicionar tags adicionais baseado em FeatureData
    feature_data = feat_entry.get("FeatureData", {})
    if "InitiativeBonus" in feature_data or "CannotBeSurprised" in feature_data:
        type_tags.append("Feat.Combat")
    if "DeceptionAdvantage" in feature_data or "PerformanceAdvantage" in feature_data:
        type_tags.append("Feat.Social")

    new_entry = feat_entry.copy()
    new_entry["FeatID"] = feat_id
    new_entry["TypeTags"] = type_tags

    return new_entry


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    input_file = os.path.join(project_root, "Content", "Data", "JSON", "DJ_FeatsGerais.json")
    output_file = os.path.join(project_root, "Content", "Data", "JSON", "FeatDataTable.json")

    # Ler JSON original
    with open(input_file, 'r', encoding='utf-8') as f:
        feats = json.load(f)

    # Migrar cada entrada
    migrated_feats = [migrate_feat_entry(feat) for feat in feats]

    # Salvar JSON migrado
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(migrated_feats, f, indent=2, ensure_ascii=False)

    print(f"Migracao concluida: {len(migrated_feats)} feats migrados")
    print(f"Arquivo salvo em: {output_file}")


if __name__ == "__main__":
    main()
