#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Gera HTML estático com sidebar de navegação.
Rode uma vez: python generate_docs_html.py
Depois abra docs.html no navegador (sem servidor!)
"""

import os
from pathlib import Path

DOCS_DIR = Path(__file__).parent / "docs"
OUTPUT_FILE = Path(__file__).parent / "docs.html"

def get_markdown_files(root_dir):
    """Retorna estrutura de arquivos em formato de dicionário."""
    files = {}

    for root, dirs, filenames in os.walk(root_dir):
        # Ignora pastas especiais
        dirs[:] = [d for d in dirs if not d.startswith('.') and d != '__pycache__' and d != 'temp']

        # Pega caminho relativo
        rel_root = Path(root).relative_to(root_dir)

        current = files
        if rel_root != Path('.'):
            for part in rel_root.parts:
                if part not in current:
                    current[part] = {}
                current = current[part]

        for filename in sorted(filenames):
            if filename.endswith('.md'):
                rel_path = Path(root) / filename
                rel_path_str = str(rel_path.relative_to(DOCS_DIR.parent)).replace('\\', '/')
                current[filename] = rel_path_str

    return files

def build_sidebar_js(files, indent=0):
    """Gera JavaScript para estrutura de sidebar."""
    lines = []
    spaces = '  ' * indent

    lines.append(f'{spaces}{{')
    indent += 1
    spaces = '  ' * indent

    items = []
    for key, value in sorted(files.items()):
        if isinstance(value, dict):
            # É pasta
            items.append(f'{spaces}"{key}": {build_sidebar_js(value, indent)}')
        else:
            # É arquivo
            items.append(f'{spaces}"{key}": "{value}"')

    lines.append(',\n'.join(items))
    indent -= 1
    spaces = '  ' * indent
    lines.append(f'{spaces}}}')

    return '\n'.join(lines)

def main():
    if not DOCS_DIR.exists():
        print(f"ERRO: Pasta 'docs' não encontrada em {DOCS_DIR}")
        return

    print("Escaneando arquivos Markdown...")
    files = get_markdown_files(DOCS_DIR)

    print("Gerando HTML...")

    sidebar_js = build_sidebar_js(files)

    html = f'''<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Documentação MyProject2</title>
    <script src="https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script>
    <style>
        * {{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }}

        body {{
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
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

        .sidebar ul {{
            list-style: none;
        }}

        .sidebar li {{
            margin: 3px 0;
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
            content: "▼ ";
            display: inline-block;
            width: 15px;
            margin-right: 5px;
            font-size: 10px;
        }}

        .sidebar .folder-name.collapsed::before {{
            content: "▶ ";
        }}

        .sidebar .folder-name:hover {{
            background: #3d3d3d;
        }}

        .sidebar .folder-content {{
            margin-left: 20px;
            display: block;
            overflow: hidden;
            transition: max-height 0.3s ease-out, opacity 0.2s;
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
</head>
<body>
    <div class="sidebar">
        <h2>📚 Navegação</h2>
        <ul id="sidebar-nav"></ul>
    </div>
    <div class="content" id="content">
        <h1>Documentação MyProject2</h1>
        <p>Selecione um arquivo na sidebar para visualizar.</p>
    </div>

    <script>
        const files = {sidebar_js};

        function buildSidebar(files, parent = null, level = 0) {{
            let html = '';
            const indent = '  '.repeat(level);

            for (const [key, value] of Object.entries(files).sort()) {{
                if (typeof value === 'string') {{
                    const displayName = key.replace('.md', '');
                    html += `${{indent}}<li><a href="#" data-file="${{value}}">${{displayName}}</a></li>\\n`;
                }} else {{
                    html += `${{indent}}<li class="folder">\\n`;
                    html += `${{indent}}  <span class="folder-name">${{key}}</span>\\n`;
                    html += `${{indent}}  <ul class="folder-content">\\n`;
                    html += buildSidebar(value, key, level + 1);
                    html += `${{indent}}  </ul>\\n`;
                    html += `${{indent}}</li>\\n`;
                }}
            }}

            return html;
        }}

        function initCollapse() {{
            const folders = document.querySelectorAll('li.folder');

            folders.forEach(function(folder) {{
                const folderName = folder.querySelector('span.folder-name');
                const folderContent = folder.querySelector('ul.folder-content');

                if (folderName && folderContent) {{
                    folderName.classList.add('expanded');
                    folderName.style.cursor = 'pointer';
                    folderName.style.userSelect = 'none';

                    folderName.addEventListener('click', function(e) {{
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
                    }});
                }}
            }});
        }}

        async function loadMarkdown(filePath) {{
            try {{
                const response = await fetch(filePath);
                if (!response.ok) {{
                    throw new Error('Arquivo não encontrado');
                }}
                const text = await response.text();

                let content = text;
                if (content.startsWith('---')) {{
                    const parts = content.split('---', 3);
                    if (parts.length >= 3) {{
                        content = parts[2].trim();
                    }}
                }}

                const html = marked.parse(content);
                document.getElementById('content').innerHTML = html;

                document.querySelectorAll('.sidebar a').forEach(a => a.classList.remove('active'));
                document.querySelector(`.sidebar a[data-file="${{filePath}}"]`)?.classList.add('active');

                const activeLink = document.querySelector('.sidebar a.active');
                if (activeLink) {{
                    let parent = activeLink.closest('.folder-content');
                    while (parent) {{
                        parent.classList.remove('collapsed');
                        const folder = parent.closest('.folder');
                        if (folder) {{
                            const folderName = folder.querySelector('.folder-name');
                            if (folderName) {{
                                folderName.classList.remove('collapsed');
                                folderName.classList.add('expanded');
                            }}
                        }}
                        parent = parent.parentElement ? parent.parentElement.closest('.folder-content') : null;
                    }}
                }}
            }} catch (error) {{
                document.getElementById('content').innerHTML = `
                    <h1>Erro ao carregar arquivo</h1>
                    <p>Não foi possível carregar: ${{filePath}}</p>
                    <p><strong>Nota:</strong> Este HTML precisa ser aberto via servidor HTTP.</p>
                    <p>Use: <code>python docs_server.py</code> ou abra via servidor local</p>
                `;
            }}
        }}

        document.getElementById('sidebar-nav').innerHTML = buildSidebar(files);
        initCollapse();

        document.querySelectorAll('.sidebar a[data-file]').forEach(link => {{
            link.addEventListener('click', function(e) {{
                e.preventDefault();
                loadMarkdown(this.getAttribute('data-file'));
            }});
        }});

        if (files['index.md']) {{
            loadMarkdown(files['index.md']);
        }}
    </script>
</body>
</html>'''

    OUTPUT_FILE.write_text(html, encoding='utf-8')
    print(f"HTML gerado: {OUTPUT_FILE}")
    print(f"Abra no navegador: {OUTPUT_FILE}")
    print("\nNOTA: Para funcionar, abra via servidor HTTP (nao file://)")
    print("   Use: python docs_server.py e acesse http://localhost:8000/docs.html")

if __name__ == "__main__":
    main()
