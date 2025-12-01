#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para corrigir links na documentação.
Converte links com path para nome único sem path (padrão do sidebar).
"""

import os
import re
from pathlib import Path
from typing import List, Tuple, Dict

# Caminho raiz da documentação
DOC_ROOT = Path(r"F:\UNREAL GAME\minasphandelver\Documentacao")

# Padrão para encontrar links markdown: [texto](link)
LINK_PATTERN = re.compile(r'(\[[^\]]+\])(\()([^)]+)(\))')

# Links externos (http, https, mailto, etc) devem ser ignorados
EXTERNAL_LINK_PATTERN = re.compile(r'^(https?|mailto|ftp)://', re.IGNORECASE)

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

def find_file_by_name(root: Path, name: str) -> Path:
    """Encontra arquivo pelo nome (sem extensão) em qualquer pasta."""
    for file_path in root.rglob("*.md"):
        if file_path.stem == name:
            return file_path
    return None

def get_correct_link_name(link: str, root: Path) -> Tuple[str, bool]:
    """
    Retorna o nome único correto para o link.
    Retorna (nome_correto, precisa_corrigir).
    """
    # Ignora links externos
    if EXTERNAL_LINK_PATTERN.match(link):
        return link, False

    # Ignora âncoras
    if ANCHOR_PATTERN.match(link):
        return link, False

    # Remove extensão .md se houver
    link_clean = link.replace('.md', '')

    # Se o link contém path (barra), precisa corrigir
    if '/' in link_clean or '\\' in link_clean:
        # Remove âncoras (#) para buscar o arquivo
        link_without_anchor = link_clean.split('#')[0]

        # Tenta encontrar o arquivo pelo path completo
        link_path = root / link_without_anchor
        if link_path.with_suffix('.md').exists():
            # Arquivo existe, retorna apenas o nome único
            file_name = link_path.stem
            # Se tinha âncora, adiciona de volta
            if '#' in link_clean:
                anchor = '#' + link_clean.split('#', 1)[1]
                return file_name + anchor, True
            return file_name, True

        # Tenta encontrar pelo nome do arquivo final
        file_name_from_path = Path(link_without_anchor).stem
        file_found = find_file_by_name(root, file_name_from_path)
        if file_found:
            # Se tinha âncora, adiciona de volta
            if '#' in link_clean:
                anchor = '#' + link_clean.split('#', 1)[1]
                return file_name_from_path + anchor, True
            return file_name_from_path, True

        # Arquivo não encontrado, retorna como está (será reportado)
        return link, False

    # Link já está no formato correto (sem path)
    return link, False

def fix_file_links(file_path: Path, root: Path, dry_run: bool = True) -> Tuple[int, List[str]]:
    """
    Corrige links em um arquivo.
    Retorna (links_corrigidos, mensagens).
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        return 0, [f"Erro ao ler arquivo: {e}"]

    messages = []
    links_fixed = 0
    new_content = content

    def replace_link(match):
        nonlocal links_fixed
        link_text = match.group(1)  # [texto]
        opening = match.group(2)     # (
        link_url = match.group(3)    # link
        closing = match.group(4)      # )

        correct_link, needs_fix = get_correct_link_name(link_url, root)

        if needs_fix:
            links_fixed += 1
            messages.append(f"  Linha ~{content[:match.start()].count(chr(10)) + 1}: {link_text}{opening}{link_url}{closing} -> {link_text}{opening}{correct_link}{closing}")
            return link_text + opening + correct_link + closing
        return match.group(0)

    new_content = LINK_PATTERN.sub(replace_link, content)

    if links_fixed > 0 and not dry_run:
        try:
            with open(file_path, 'w', encoding='utf-8') as f:
                f.write(new_content)
        except Exception as e:
            messages.append(f"Erro ao salvar arquivo: {e}")

    return links_fixed, messages

def main():
    """Função principal."""
    import sys
    import io

    # Configura encoding UTF-8 para output
    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

    dry_run = '--fix' not in sys.argv

    if dry_run:
        print("=== VERIFICACAO DE LINKS (DRY RUN) ===\n")
        print("Execute com --fix para corrigir os links.\n")
    else:
        print("=== CORRIGINDO LINKS ===\n")

    all_files = get_all_md_files(DOC_ROOT)
    print(f"Arquivos encontrados: {len(all_files)}\n")

    total_fixed = 0
    files_with_fixes = 0

    for file_path in all_files:
        links_fixed, messages = fix_file_links(file_path, DOC_ROOT, dry_run)
        if links_fixed > 0:
            files_with_fixes += 1
            rel_path = file_path.relative_to(DOC_ROOT)
            print(f"Arquivo: {rel_path}")
            print(f"Links corrigidos: {links_fixed}")
            for msg in messages:
                print(msg)
            print()
            total_fixed += links_fixed

    print(f"=== RESULTADO ===")
    print(f"Arquivos verificados: {len(all_files)}")
    print(f"Arquivos com correções: {files_with_fixes}")
    print(f"Total de links corrigidos: {total_fixed}")

    if dry_run and total_fixed > 0:
        print(f"\nExecute com --fix para aplicar as correções.")

if __name__ == "__main__":
    main()
