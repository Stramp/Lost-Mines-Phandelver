#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Servidor local simples para visualizar documentação Markdown com sidebar de navegação.
Não modifica os arquivos MD originais.
"""

import os
import http.server
import socketserver
from pathlib import Path
from urllib.parse import unquote, urlparse
import markdown
from markdown.extensions.toc import TocExtension
import re

# Configuração
DOCS_DIR = Path(__file__).parent / "docs"
PORT = 8000

def get_markdown_files(root_dir):
    """Retorna lista de todos os arquivos .md recursivamente."""
    md_files = []
    for root, dirs, files in os.walk(root_dir):
        # Ignora pastas temp e outras
        dirs[:] = [d for d in dirs if not d.startswith('.') and d != '__pycache__']
        for file in files:
            if file.endswith('.md'):
                full_path = Path(root) / file
                rel_path = full_path.relative_to(root_dir)
                md_files.append(rel_path)
    return sorted(md_files)

def build_sidebar_tree(md_files, current_file=None):
    """Constrói HTML da sidebar em formato de árvore."""
    tree = {}

    # Organiza arquivos em estrutura de árvore
    for file_path in md_files:
        parts = file_path.parts
        current = tree
        for i, part in enumerate(parts):
            if part not in current:
                current[part] = {}
            current = current[part]

    def render_tree(node, path="", level=0):
        """Renderiza árvore recursivamente."""
        html = []
        indent = "  " * level

        for key, value in sorted(node.items()):
            current_path = f"{path}/{key}" if path else key
            is_file = not value or (len(value) == 0)

            if is_file:
                # É um arquivo
                file_url = f"/{current_path.replace(chr(92), '/')}"
                active = 'class="active"' if current_file and str(current_file) == current_path.replace(chr(92), '/') else ''
                display_name = key.replace('.md', '')
                html.append(f'{indent}<li><a href="{file_url}" {active}>{display_name}</a></li>')
            else:
                # É uma pasta
                folder_name = key
                html.append(f'{indent}<li class="folder">')
                html.append(f'{indent}  <span class="folder-name" data-folder="{folder_name}">{folder_name}</span>')
                html.append(f'{indent}  <ul class="folder-content">')
                html.extend(render_tree(value, current_path, level + 1))
                html.append(f'{indent}  </ul>')
                html.append(f'{indent}</li>')

        return html

    tree_html = render_tree(tree)
    return '\n'.join(tree_html)

def markdown_to_html(md_content, base_path=""):
    """Converte Markdown para HTML."""
    # Remove front matter se existir
    if md_content.startswith('---'):
        parts = md_content.split('---', 2)
        if len(parts) >= 3:
            md_content = parts[2].strip()

    # Configura extensões do markdown
    md = markdown.Markdown(
        extensions=[
            'fenced_code',
            'tables',
            'toc',
            'codehilite',
            'nl2br',
            'sane_lists',
        ],
        extension_configs={
            'toc': {
                'permalink': True,
                'toc_depth': 6
            }
        }
    )

    html = md.convert(md_content)

    # Processa links relativos (mantém como está, será processado pelo servidor)

    return html

def get_html_template(sidebar_html, content_html, title="Documentação"):
    """Retorna HTML completo com sidebar e conteúdo."""
    return f"""<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{title} - MyProject2</title>
    <style>
        * {{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }}

        body {{
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, sans-serif;
            display: flex;
            height: 100vh;
            overflow: hidden;
        }}

        .sidebar {{
            width: 300px;
            background: #2d2d2d;
            color: #e0e0e0;
            overflow-y: auto;
            padding: 20px;
            border-right: 1px solid #444;
        }}

        .sidebar h2 {{
            color: #fff;
            margin-bottom: 15px;
            font-size: 18px;
            padding-bottom: 10px;
            border-bottom: 2px solid #555;
        }}

        .sidebar h2::before {{
            content: "📚 ";
        }}

        .sidebar ul {{
            list-style: none;
        }}

        .sidebar li {{
            margin: 5px 0;
        }}

        .sidebar a {{
            color: #b0b0b0;
            text-decoration: none;
            display: block;
            padding: 5px 10px;
            border-radius: 4px;
            transition: all 0.2s;
        }}

        .sidebar a:hover {{
            background: #3d3d3d;
            color: #fff;
        }}

        .sidebar a.active {{
            background: #0066cc;
            color: #fff;
        }}

        .sidebar .folder {{
            margin: 3px 0;
        }}

        .sidebar .folder-name {{
            color: #fff;
            font-weight: bold;
            display: block;
            padding: 5px 10px;
            cursor: pointer;
            user-select: none;
            position: relative;
        }}

        .sidebar .folder-name::before {{
            content: "▶ ";
            display: inline-block;
            width: 15px;
            transition: transform 0.2s;
            font-size: 10px;
        }}

        .sidebar .folder-name.collapsed::before {{
            transform: rotate(0deg);
        }}

        .sidebar .folder-name.expanded::before {{
            transform: rotate(90deg);
        }}

        .sidebar .folder-name:hover {{
            background: #3d3d3d;
        }}

        .sidebar .folder-content {{
            margin-left: 20px;
            display: block;
            overflow: hidden;
            transition: max-height 0.3s ease-out, opacity 0.2s, margin 0.3s, padding 0.3s;
            max-height: 5000px;
            opacity: 1;
        }}

        .sidebar .folder-content.collapsed {{
            max-height: 0 !important;
            opacity: 0 !important;
            margin: 0 !important;
            padding: 0 !important;
            overflow: hidden !important;
        }}

        .content {{
            flex: 1;
            overflow-y: auto;
            padding: 40px;
            background: #fff;
            color: #333;
            line-height: 1.6;
        }}

        .content h1 {{
            color: #2d2d2d;
            margin-bottom: 20px;
            padding-bottom: 10px;
            border-bottom: 2px solid #e0e0e0;
        }}

        .content h2 {{
            color: #333;
            margin-top: 30px;
            margin-bottom: 15px;
        }}

        .content h3 {{
            color: #555;
            margin-top: 20px;
            margin-bottom: 10px;
        }}

        .content code {{
            background: #f5f5f5;
            padding: 2px 6px;
            border-radius: 3px;
            font-family: 'Courier New', monospace;
            font-size: 0.9em;
        }}

        .content pre {{
            background: #2d2d2d;
            color: #e0e0e0;
            padding: 15px;
            border-radius: 5px;
            overflow-x: auto;
            margin: 15px 0;
        }}

        .content pre code {{
            background: none;
            padding: 0;
            color: inherit;
        }}

        .content table {{
            border-collapse: collapse;
            width: 100%;
            margin: 20px 0;
        }}

        .content table th,
        .content table td {{
            border: 1px solid #ddd;
            padding: 10px;
            text-align: left;
        }}

        .content table th {{
            background: #f5f5f5;
            font-weight: bold;
        }}

        .content blockquote {{
            border-left: 4px solid #0066cc;
            padding-left: 20px;
            margin: 20px 0;
            color: #666;
        }}

        .content details {{
            margin: 15px 0;
            padding: 10px;
            background: #f9f9f9;
            border-radius: 5px;
        }}

        .content summary {{
            cursor: pointer;
            font-weight: bold;
            margin-bottom: 10px;
        }}
    </style>
    <script>
        window.addEventListener('load', function() {{
            var folders = document.querySelectorAll('.folder');

            folders.forEach(function(folder) {{
                var folderName = folder.querySelector('.folder-name');
                var folderContent = folder.querySelector('.folder-content');

                if (folderName && folderContent) {{
                    folderName.classList.add('expanded');
                    folderName.style.cursor = 'pointer';

                    folderName.onclick = function(e) {{
                        e.preventDefault();
                        e.stopPropagation();

                        if (folderName.classList.contains('expanded')) {{
                            folderName.classList.remove('expanded');
                            folderName.classList.add('collapsed');
                            folderContent.classList.add('collapsed');
                        }} else {{
                            folderName.classList.remove('collapsed');
                            folderName.classList.add('expanded');
                            folderContent.classList.remove('collapsed');
                        }}
                    }};
                }}
            }});

            // Expande pasta do arquivo ativo
            var activeLink = document.querySelector('.sidebar a.active');
            if (activeLink) {{
                var parent = activeLink.closest('.folder-content');
                while (parent) {{
                    parent.classList.remove('collapsed');
                    var folder = parent.closest('.folder');
                    if (folder) {{
                        var folderName = folder.querySelector('.folder-name');
                        if (folderName) {{
                            folderName.classList.remove('collapsed');
                            folderName.classList.add('expanded');
                        }}
                    }}
                    parent = parent.parentElement ? parent.parentElement.closest('.folder-content') : null;
                }}
            }}
        }});
    </script>
</head>
<body>
    <div class="sidebar">
        <h2>📚 Navegação</h2>
        <ul>
            {sidebar_html}
        </ul>
    </div>
    <div class="content">
        {content_html}
    </div>
</body>
</html>"""

class DocsHandler(http.server.SimpleHTTPRequestHandler):
    """Handler customizado para servir documentação."""

    def do_GET(self):
        """Processa requisições GET."""
        parsed_path = urlparse(self.path)
        path = unquote(parsed_path.path)

        # Página inicial
        if path == '/' or path == '/index.html':
            self.send_index()
            return

        # Arquivo Markdown
        if path.endswith('.md') or not path.endswith(('.html', '.css', '.js', '.png', '.jpg', '.gif')):
            if path.endswith('.md'):
                file_path = DOCS_DIR / path[1:]  # Remove /
            else:
                # Tenta encontrar arquivo .md
                file_path = DOCS_DIR / path[1:] / "index.md"
                if not file_path.exists():
                    file_path = DOCS_DIR / (path[1:] + ".md")

            if file_path.exists() and file_path.suffix == '.md':
                self.send_markdown(file_path)
                return

        # Arquivos estáticos (CSS, JS, etc.)
        super().do_GET()

    def send_index(self):
        """Envia página inicial."""
        md_files = get_markdown_files(DOCS_DIR)
        sidebar_html = build_sidebar_tree(md_files)

        # Tenta carregar index.md
        index_path = DOCS_DIR / "index.md"
        if index_path.exists():
            with open(index_path, 'r', encoding='utf-8') as f:
                content = f.read()
            content_html = markdown_to_html(content)
        else:
            content_html = "<h1>Documentação MyProject2</h1><p>Bem-vindo à documentação do projeto.</p>"

        html = get_html_template(sidebar_html, content_html, "Home")
        self.send_response(200)
        self.send_header('Content-type', 'text/html; charset=utf-8')
        self.end_headers()
        self.wfile.write(html.encode('utf-8'))

    def send_markdown(self, file_path):
        """Envia arquivo Markdown convertido para HTML."""
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                md_content = f.read()

            # Converte para HTML
            content_html = markdown_to_html(md_content, str(file_path.relative_to(DOCS_DIR)))

            # Extrai título
            title_match = re.search(r'^#\s+(.+)$', md_content, re.MULTILINE)
            title = title_match.group(1) if title_match else file_path.stem

            # Gera sidebar
            md_files = get_markdown_files(DOCS_DIR)
            current_file = str(file_path.relative_to(DOCS_DIR))
            sidebar_html = build_sidebar_tree(md_files, current_file)

            # Gera HTML completo
            html = get_html_template(sidebar_html, content_html, title)

            self.send_response(200)
            self.send_header('Content-type', 'text/html; charset=utf-8')
            self.end_headers()
            self.wfile.write(html.encode('utf-8'))

        except Exception as e:
            self.send_error(500, f"Erro ao processar arquivo: {str(e)}")

    def log_message(self, format, *args):
        """Suprime logs desnecessários."""
        pass

def main():
    """Inicia servidor."""
    if not DOCS_DIR.exists():
        print(f"ERRO: Pasta 'docs' nao encontrada em {DOCS_DIR}")
        return

    print("Iniciando servidor de documentacao...")
    print(f"Pasta: {DOCS_DIR}")
    print(f"URL: http://localhost:{PORT}")
    print("Pressione Ctrl+C para parar\n")

    os.chdir(DOCS_DIR.parent)

    with socketserver.TCPServer(("", PORT), DocsHandler) as httpd:
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\n\nServidor encerrado.")

if __name__ == "__main__":
    main()
