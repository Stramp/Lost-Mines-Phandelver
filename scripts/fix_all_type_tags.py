#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para converter TypeTags de TODOS os arquivos JSON em Content/Data/JSON
do formato array simples ou string para o formato correto do Unreal Engine.

Formato ERRADO:
  "TypeTags": ["Ability.Physical"]
  "TypeTags": "(Ability.Physical)"

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
from typing import List, Dict, Any

def convert_type_tags_format(data: List[Dict[str, Any]]) -> tuple[List[Dict[str, Any]], int, int]:
    """
    Converte TypeTags do formato array simples ou string para formato Unreal Engine.
    Remove SchemaVersion e DataVersion.
    Adiciona ParentTags em TypeTags.

    Args:
        data: Lista de objetos (entradas da Data Table)

    Returns:
        Tupla (lista convertida, quantidade de TypeTags convertidos, quantidade de versões removidas)
    """
    converted = []
    converted_count = 0
    versions_removed = 0

    for entry in data:
        # Remove SchemaVersion e DataVersion
        if "SchemaVersion" in entry:
            del entry["SchemaVersion"]
            versions_removed += 1

        if "DataVersion" in entry:
            del entry["DataVersion"]
            versions_removed += 1

        # Processa TypeTags
        if "TypeTags" in entry:
            type_tags = entry["TypeTags"]
            needs_conversion = False

            # Se já está no formato correto, apenas adiciona ParentTags se não existir
            if isinstance(type_tags, dict) and "GameplayTags" in type_tags:
                if "ParentTags" not in type_tags:
                    type_tags["ParentTags"] = []
                    converted_count += 1
            else:
                needs_conversion = True

            # Se é array simples, converte
            if isinstance(type_tags, list):
                gameplay_tags = []
                for tag in type_tags:
                    if isinstance(tag, str):
                        gameplay_tags.append({"TagName": tag})
                    elif isinstance(tag, dict) and "TagName" in tag:
                        gameplay_tags.append(tag)
                    else:
                        print(f"    AVISO: Tag invalida ignorada: {tag}")

                entry["TypeTags"] = {
                    "GameplayTags": gameplay_tags,
                    "ParentTags": []
                }
                converted_count += 1

            # Se é string (formato antigo com parênteses), converte
            elif isinstance(type_tags, str):
                # Remove parênteses se existirem
                tag_name = type_tags.strip("()")
                entry["TypeTags"] = {
                    "GameplayTags": [
                        {"TagName": tag_name}
                    ],
                    "ParentTags": []
                }
                converted_count += 1

        converted.append(entry)

    return converted, converted_count, versions_removed

def process_json_file(json_file: Path) -> tuple[bool, int, int]:
    """
    Processa um arquivo JSON e converte TypeTags se necessário.
    Remove SchemaVersion e DataVersion.

    Args:
        json_file: Caminho do arquivo JSON

    Returns:
        Tupla (sucesso, quantidade de TypeTags convertidos, quantidade de versões removidas)
    """
    try:
        # Lê o arquivo JSON
        with open(json_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        print(f"    ERRO ao ler JSON: {e}")
        return False, 0, 0
    except Exception as e:
        print(f"    ERRO ao abrir arquivo: {e}")
        return False, 0, 0

    if not isinstance(data, list):
        print(f"    AVISO: JSON nao e um array, pulando...")
        return False, 0, 0

    # Converte TypeTags e remove versões
    converted_data, converted_count, versions_removed = convert_type_tags_format(data)

    # Sempre salva se houve alguma alteração
    if converted_count > 0 or versions_removed > 0:
        try:
            with open(json_file, 'w', encoding='utf-8') as f:
                json.dump(converted_data, f, indent=2, ensure_ascii=False)
            return True, converted_count, versions_removed
        except Exception as e:
            print(f"    ERRO ao salvar arquivo: {e}")
            return False, converted_count, versions_removed

    return True, 0, 0

def main():
    """Função principal do script."""
    # Caminho da pasta JSON
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    json_dir = project_root / "Content" / "Data" / "JSON"

    if not json_dir.exists():
        print(f"ERRO: Pasta nao encontrada: {json_dir}")
        sys.exit(1)

    print(f"Processando arquivos JSON em: {json_dir}")
    print("-" * 60)

    # Lista todos os arquivos JSON (exceto schemas)
    json_files = [f for f in json_dir.glob("*.json") if f.name != "AbilityScoreDataTable.schema.json"]

    if not json_files:
        print("Nenhum arquivo JSON encontrado")
        sys.exit(0)

    print(f"Encontrados {len(json_files)} arquivos JSON\n")

    total_converted = 0
    total_versions_removed = 0
    total_files_processed = 0
    total_files_skipped = 0

    # Processa cada arquivo
    for json_file in sorted(json_files):
        print(f"Processando: {json_file.name}")

        try:
            # Lê para contar entradas
            with open(json_file, 'r', encoding='utf-8') as f:
                data = json.load(f)

            if not isinstance(data, list):
                print(f"  AVISO: Nao e um array, pulando...\n")
                total_files_skipped += 1
                continue

            entry_count = len(data)
            print(f"  {entry_count} entradas encontradas")

            # Processa o arquivo
            success, converted_count, versions_removed = process_json_file(json_file)

            if success:
                changes = []
                if converted_count > 0:
                    changes.append(f"{converted_count} TypeTags convertidos")
                if versions_removed > 0:
                    changes.append(f"{versions_removed} versoes removidas")

                if changes:
                    print(f"  OK: {', '.join(changes)}")
                    total_converted += converted_count
                    total_versions_removed += versions_removed
                    total_files_processed += 1
                else:
                    print(f"  OK: Ja esta no formato correto")
                    total_files_processed += 1
            else:
                print(f"  ERRO: Falha ao processar arquivo")
                total_files_skipped += 1

        except Exception as e:
            print(f"  ERRO: {e}")
            total_files_skipped += 1

        print()

    # Resumo
    print("-" * 60)
    print(f"RESUMO:")
    print(f"  Arquivos processados: {total_files_processed}")
    print(f"  Arquivos pulados: {total_files_skipped}")
    print(f"  Total de TypeTags convertidos: {total_converted}")
    print(f"  Total de versoes removidas: {total_versions_removed}")

    if total_converted > 0 or total_versions_removed > 0:
        print(f"\nOK: Conversao concluida com sucesso!")
    else:
        print(f"\nINFO: Nenhuma conversao necessaria (todos ja estao no formato correto)")

if __name__ == "__main__":
    main()
