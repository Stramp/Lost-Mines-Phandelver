#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para migrar Item_All.json para nova estrutura com Tags e Soft References.
Fase 2.7: Modificar Item_All.json (já tem ItemID, adicionar Tags e Soft References)
"""

import json
import os
import sys


def get_item_type_tags(item_entry):
    """Determina TypeTags baseado no tipo de item"""
    item_id = item_entry.get("ItemID", "")
    item_type = item_entry.get("Type", "")

    type_tags = []

    # Tags baseado no ID
    if item_id.startswith("ITM_WPN_"):
        type_tags.append("Item.Weapon")
    elif item_id.startswith("ITM_ARM_"):
        type_tags.append("Item.Armor")
    elif item_id.startswith("ITM_CNM_"):
        type_tags.append("Item.Consumable")
    elif item_id.startswith("ITM_MAG_"):
        type_tags.append("Item.Magic")
    elif item_id.startswith("ITM_OTH_"):
        type_tags.append("Item.Other")
    elif item_id.startswith("ITM_TOL_"):
        type_tags.append("Item.Tool")
    elif item_id.startswith("ITM_GOLD_"):
        type_tags.append("Item.Currency")

    # Tags baseado no Type
    if item_type:
        type_tags.append(f"Item.{item_type}")

    return type_tags if type_tags else ["Item.Unknown"]


def migrate_item_entry(item_entry):
    """Migra uma entrada de item para nova estrutura"""
    new_entry = item_entry.copy()
    new_entry["TypeTags"] = get_item_type_tags(item_entry)

    # Adicionar campos opcionais para Soft References (vazios por padrão)
    if "IconTexture" not in new_entry:
        new_entry["IconTexture"] = None
    if "MeshReference" not in new_entry:
        new_entry["MeshReference"] = None
    if "SpellHandle" not in new_entry:
        new_entry["SpellHandle"] = None
    if "DamageTypeID" not in new_entry:
        new_entry["DamageTypeID"] = None

    return new_entry


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    input_file = os.path.join(project_root, "Content", "Data", "JSON", "Item_All.json")
    output_file = os.path.join(project_root, "Content", "Data", "JSON", "ItemDataTable.json")

    # Ler JSON original
    with open(input_file, 'r', encoding='utf-8') as f:
        items = json.load(f)

    # Migrar cada entrada
    migrated_items = [migrate_item_entry(item) for item in items]

    # Salvar JSON migrado
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(migrated_items, f, indent=2, ensure_ascii=False)

    print(f"Migracao concluida: {len(migrated_items)} itens migrados")
    print(f"Arquivo salvo em: {output_file}")


if __name__ == "__main__":
    main()
