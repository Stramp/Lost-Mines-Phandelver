# 📚 MkDocs Material - Guia de Uso

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 O que é MkDocs Material?</b></summary>

> **MkDocs Material** é um gerador de sites de documentação que transforma seus arquivos Markdown em um site HTML bonito e navegável, com busca integrada, navegação lateral e tema Material Design.

</details>

---

## 🚀 Instalação Rápida

### 1. Instalar Dependências

```bash
pip install -r requirements-docs.txt
```

### 2. Servir Localmente (Desenvolvimento)

```bash
mkdocs serve
```

Acesse: `http://127.0.0.1:8000`

### 3. Gerar Site Estático

```bash
mkdocs build
```

O site será gerado na pasta `site/` (não versionar no Git).

---

## 📋 Comandos Úteis

### Desenvolvimento

```bash
# Servir com auto-reload (detecta mudanças)
mkdocs serve

# Servir em porta específica
mkdocs serve --dev-addr=127.0.0.1:8080
```

### Build

```bash
# Build para produção
mkdocs build

# Build limpo (remove site/ antes)
mkdocs build --clean
```

### Deploy (GitHub Pages)

```bash
# Deploy automático para GitHub Pages
mkdocs gh-deploy

# Deploy com mensagem customizada
mkdocs gh-deploy -m "Update documentation"
```

---

## 🎨 Recursos do MkDocs Material

### ✅ Recursos Implementados

#### Navegação
- ✅ **Busca Integrada Multilíngue** - Busca full-text em pt-BR e en
- ✅ **Navegação Instantânea** - Carregamento rápido entre páginas
- ✅ **Navegação Lateral** - Menu colapsável com hierarquia
- ✅ **Path Breadcrumbs** - Mostra caminho completo
- ✅ **Header Autohide** - Header esconde ao rolar
- ✅ **Tabs Sticky** - Tabs fixas no topo

#### Busca
- ✅ **Busca com Highlight** - Destaca termos encontrados
- ✅ **Sugestões** - Autocompletar na busca
- ✅ **Boost de Resultados** - Prioriza resultados importantes
- ✅ **Compartilhamento** - Compartilha links com busca

#### Código
- ✅ **Syntax Highlighting** - Destaque de código C++/JSON
- ✅ **Cópia de Código** - Botão para copiar código
- ✅ **Anotações de Código** - Adiciona notas em blocos
- ✅ **Seleção de Código** - Seleção facilitada
- ✅ **Mermaid Diagrams** - Diagramas renderizados automaticamente
- ✅ **Fórmulas Matemáticas** - Suporte a LaTeX/MathJax

#### Conteúdo
- ✅ **Tabs** - Organização de conteúdo em abas
- ✅ **Admonitions com Ícones** - Caixas com ícones customizados
- ✅ **Emojis e Ícones** - Suporte a emojis e ícones Material/FontAwesome
- ✅ **Tooltips** - Tooltips em elementos
- ✅ **Tabelas Melhoradas** - Renderização aprimorada
- ✅ **Teclas de Atalho** - Exibe atalhos de teclado

#### Internacionalização
- ✅ **Idioma Português (pt-BR)** - Interface em português
- ✅ **Datas Localizadas** - Datas em português brasileiro
- ✅ **Textos Traduzidos** - Interface traduzida

#### Social e Integração
- ✅ **Git Integration** - Data de última modificação automática
- ✅ **Social Links** - Links para GitHub, Discord
- ✅ **Dark Mode** - Alternância automática claro/escuro
- ✅ **Consent para Cookies** - Preparado para GDPR

### 📖 Documentação Completa

Para ver todas as melhorias implementadas, consulte: **[MkDocs Improvements](MKDOCS-IMPROVEMENTS.md)**

---

## 📁 Estrutura de Arquivos

```
MyProject2/
├── docs/                    # Documentação Markdown (source)
│   ├── index.md
│   ├── NAVIGATION.md
│   ├── GLOSSARY.md
│   ├── design/
│   ├── technical/
│   └── planning/
├── mkdocs.yml               # Configuração do MkDocs
├── requirements-docs.txt    # Dependências Python
└── site/                    # Site gerado (não versionar)
```

---

## 🔧 Configuração

### Personalizar Tema

Edite `mkdocs.yml`:

```yaml
theme:
  palette:
    - scheme: default
      primary: indigo  # Cor primária
      accent: indigo   # Cor de destaque
```

### Adicionar Plugins

Edite `mkdocs.yml`:

```yaml
plugins:
  - search
  - git-revision-date-localized
  # Adicione mais plugins aqui
```

### Modificar Navegação

Edite a seção `nav:` em `mkdocs.yml` para reorganizar o menu lateral.

---

## 📝 Frontmatter YAML

Todos os documentos devem ter frontmatter YAML no topo:

```yaml
---
title: "Título do Documento"
category: technical
subcategory: guides
tags: [tag1, tag2, tag3]
last_updated: 2024-12-27
difficulty: intermediate
related: [related-doc.md]
---
```

**Campos:**
- `title`: Título exibido no site
- `category`: Categoria principal (root, design, technical, planning)
- `subcategory`: Subcategoria quando aplicável
- `tags`: Tags para busca e categorização
- `last_updated`: Data de última atualização
- `difficulty`: Nível (beginner, intermediate, advanced)
- `related`: Links para documentos relacionados

---

## 🐛 Troubleshooting

### Erro: "mkdocs: command not found"

**Solução:** Instale as dependências:
```bash
pip install -r requirements-docs.txt
```

### Erro: "ModuleNotFoundError: No module named 'mkdocs'"

**Solução:** Use ambiente virtual:
```bash
python -m venv venv
source venv/bin/activate  # Linux/Mac
venv\Scripts\activate      # Windows
pip install -r requirements-docs.txt
```

### Site não atualiza após mudanças

**Solução:** Use `mkdocs serve` com auto-reload (padrão) ou force rebuild:
```bash
mkdocs build --clean
```

---

## 📚 Referências

- [MkDocs Documentation](https://www.mkdocs.org/)
- [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/)
- [MkDocs Plugins](https://github.com/mkdocs/mkdocs/wiki/MkDocs-Plugins)

---

## ✅ Checklist de Uso

Antes de fazer deploy:

- [ ] Todos os documentos têm frontmatter YAML?
- [ ] Navegação em `mkdocs.yml` está atualizada?
- [ ] Site builda sem erros (`mkdocs build`)?
- [ ] Links internos funcionam?
- [ ] Busca funciona corretamente?
- [ ] Tema está configurado corretamente?

---

**Última atualização:** 2024-12-27
