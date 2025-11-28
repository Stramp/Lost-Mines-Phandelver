#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para converter TypeTags de AbilityScoreDataTable.json
do formato array simples para o formato correto do Unreal Engine.

Formato ERRADO:
  "TypeTags": ["Ability.Physical"]

Formato CORRETO:
  "TypeTags": {
    "GameplayTags": [
      {
        "TagName": "Ability.Physical"
      }
    ]
  }
"""

import json
import os
import sys
from pathlib import Path

def convert_type_tags_format(data):
    """
    Converte TypeTags do formato array simples para formato Unreal Engine.

    Args:
        data: Lista de objetos (entradas da Data Table)

    Returns:
        Lista de objetos com TypeTags convertidos
    """
    converted = []

    for entry in data:
        if "TypeTags" in entry:
            type_tags = entry["TypeTags"]

            # Se já está no formato correto, não altera
            if isinstance(type_tags, dict) and "GameplayTags" in type_tags:
                converted.append(entry)
                continue

            # Se é array simples, converte
            if isinstance(type_tags, list):
                gameplay_tags = []
                for tag in type_tags:
                    if isinstance(tag, str):
                        gameplay_tags.append({"TagName": tag})
                    elif isinstance(tag, dict) and "TagName" in tag:
                        gameplay_tags.append(tag)
                    else:
                        print(f"AVISO: Tag invalida ignorada: {tag}")

                entry["TypeTags"] = {
                    "GameplayTags": gameplay_tags
                }

            # Se é string (formato antigo com parênteses), converte
            elif isinstance(type_tags, str):
                # Remove parênteses se existirem
                tag_name = type_tags.strip("()")
                entry["TypeTags"] = {
                    "GameplayTags": [
                        {"TagName": tag_name}
                    ]
                }

        converted.append(entry)

    return converted

def main():
    """Função principal do script."""
    # Caminho do arquivo JSON
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    json_file = project_root / "Content" / "Data" / "JSON" / "AbilityScoreDataTable.json"

    if not json_file.exists():
        print(f"ERRO: Arquivo nao encontrado: {json_file}")
        sys.exit(1)

    print(f"Lendo arquivo: {json_file}")

    # Lê o arquivo JSON
    try:
        with open(json_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        print(f"ERRO ao ler JSON: {e}")
        sys.exit(1)

    if not isinstance(data, list):
        print("ERRO: JSON deve ser um array")
        sys.exit(1)

    print(f"OK: {len(data)} entradas encontradas")

    # Converte TypeTags
    print("Convertendo TypeTags...")
    converted_data = convert_type_tags_format(data)

    # Conta quantas foram convertidas
    converted_count = 0
    for i, (original, converted) in enumerate(zip(data, converted_data)):
        if original.get("TypeTags") != converted.get("TypeTags"):
            converted_count += 1
            name = converted.get("Name", f"Entry {i}")
            print(f"  Convertido: {name}")

    if converted_count == 0:
        print("INFO: Nenhuma conversao necessaria (ja esta no formato correto)")
    else:
        print(f"OK: {converted_count} entradas convertidas")

    # Salva o arquivo
    print(f"Salvando arquivo: {json_file}")
    try:
        with open(json_file, 'w', encoding='utf-8') as f:
            json.dump(converted_data, f, indent=2, ensure_ascii=False)
        print("OK: Arquivo salvo com sucesso!")
    except Exception as e:
        print(f"ERRO ao salvar arquivo: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
