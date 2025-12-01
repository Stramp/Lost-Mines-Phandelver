#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para verificar e corrigir links na documentação.
Todos os links devem seguir o padrão do sidebar: nome único sem path e sem extensão.
"""

import os
import re
from pathlib import Path
from typing import List, Tuple, Dict

# Caminho raiz da documentação
DOC_ROOT = Path(r"F:\UNREAL GAME\minasphandelver\Documentacao")

# Padrão para encontrar links markdown: [texto](link)
LINK_PATTERN = re.compile(r'\[([^\]]+)\]\(([^)]+)\)')

# Links externos (http, https, mailto, etc) devem ser ignorados
EXTERNAL_LINK_PATTERN = re.compile(r'^(https?|mailto|ftp|#)://', re.IGNORECASE)

# Links que começam com # são âncoras, devem ser ignorados
ANCHOR_PATTERN = re.compile(r'^#')

def get_all_md_files(root: Path) -> List[Path]:
    """Retorna lista de todos os arquivos .md na documentação."""
    md_files = []
    for file_path in root.rglob("*.md"):
        # Ignora arquivos em pastas especiais
        if any(part.startswith('.') for part in file_path.parts):
            continue
        md_files.append(file_path)
    return md_files

def get_file_name_without_extension(file_path: Path) -> str:
    """Retorna o nome do arquivo sem extensão."""
    return file_path.stem

def find_file_by_name(root: Path, name: str) -> Path:
    """Encontra arquivo pelo nome (sem extensão) em qualquer pasta."""
    for file_path in root.rglob("*.md"):
        if file_path.stem == name:
            return file_path
    return None

def is_valid_link(link: str, root: Path) -> Tuple[bool, str]:
    """
    Verifica se o link é válido.
    Retorna (é_válido, mensagem_erro).
    """
    # Ignora links externos
    if EXTERNAL_LINK_PATTERN.match(link):
        return True, ""

    # Ignora âncoras
    if ANCHOR_PATTERN.match(link):
        return True, ""

    # Remove extensão .md se houver
    link_clean = link.replace('.md', '')

    # Se o link contém path (barra), está errado
    if '/' in link_clean or '\\' in link_clean:
        # Verifica se o arquivo existe no path especificado
        link_path = root / link_clean
        if link_path.with_suffix('.md').exists():
            # Link funciona mas não segue o padrão (tem path)
            return False, f"Link com path: '{link}' (deveria ser apenas '{Path(link_clean).stem}')"
        else:
            # Link quebrado
            return False, f"Link quebrado: '{link}' (arquivo não encontrado)"

    # Link sem path - verifica se arquivo existe
    file_found = find_file_by_name(root, link_clean)
    if file_found:
        return True, ""
    else:
        return False, f"Link quebrado: '{link}' (arquivo '{link_clean}.md' não encontrado)"

def check_file_links(file_path: Path, root: Path) -> List[Tuple[int, str, str, str]]:
    """
    Verifica links em um arquivo.
    Retorna lista de (linha, link_texto, link_url, erro).
    """
    errors = []

    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except Exception as e:
        errors.append((0, "", "", f"Erro ao ler arquivo: {e}"))
        return errors

    for line_num, line in enumerate(lines, 1):
        matches = LINK_PATTERN.finditer(line)
        for match in matches:
            link_text = match.group(1)
            link_url = match.group(2)

            is_valid, error_msg = is_valid_link(link_url, root)
            if not is_valid:
                errors.append((line_num, link_text, link_url, error_msg))

    return errors

def main():
    """Função principal."""
    print("=== VERIFICAÇÃO DE LINKS NA DOCUMENTAÇÃO ===\n")

    all_files = get_all_md_files(DOC_ROOT)
    print(f"Arquivos encontrados: {len(all_files)}\n")

    all_errors = []
    files_with_errors = 0

    for file_path in all_files:
        errors = check_file_links(file_path, DOC_ROOT)
        if errors:
            files_with_errors += 1
            rel_path = file_path.relative_to(DOC_ROOT)
            all_errors.append((rel_path, errors))

    # Relatório
    print(f"=== RESULTADO ===\n")
    print(f"Arquivos verificados: {len(all_files)}")
    print(f"Arquivos com erros: {files_with_errors}\n")

    if all_errors:
        print("=== ERROS ENCONTRADOS ===\n")
        for rel_path, errors in all_errors:
            print(f"Arquivo: {rel_path}")
            for line_num, link_text, link_url, error_msg in errors:
                print(f"  Linha {line_num}: [{link_text}]({link_url})")
                print(f"    ERRO: {error_msg}")
            print()
    else:
        print("✅ Todos os links estão corretos!")

    print(f"\nTotal de erros: {sum(len(errors) for _, errors in all_errors)}")

if __name__ == "__main__":
    main()
