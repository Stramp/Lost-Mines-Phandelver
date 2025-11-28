# 📚 Changelog da Documentação

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Histórico de Melhorias</b></summary>

> Este documento registra todas as melhorias e mudanças na estrutura e organização da documentação do projeto.

</details>

---

## [2024-12-27] - Melhorias de Navegação e Organização

### ✨ Adicionado

- **NAVIGATION.md** - Mapa completo de navegação com múltiplas perspectivas:
  - Navegação por categoria (Design, Técnico, Planejamento)
  - Navegação por tarefa (começar, criar personagem, entender arquitetura, etc.)
  - Navegação por conceito (Data-Driven, GAS, Point Buy, etc.)
  - Estrutura completa de arquivos
  - Busca rápida por palavra-chave

- **GLOSSARY.md** - Glossário completo de conceitos:
  - Conceitos fundamentais (Data-Driven, Component-Based, Point Buy, Multiclassing, GAS, etc.)
  - Padrões de Design (Strategy, Factory, Observer, Template Method, Command, RAII)
  - Componentes e estruturas (UCharacterSheetDataAsset, UCharacterSheetComponent, etc.)
  - Sistemas de jogo (Ability Scores, Proficiencies, Features)
  - Estruturas de dados (FDataTableRowHandle, Gameplay Tags, etc.)
  - Testes (TDD, Unit Tests, Integration Tests)
  - Referências cruzadas entre conceitos

- **Breadcrumbs** - Adicionados em todos os documentos principais:
  - Formato: `[Home] > [Documentação] > [Categoria] > [Subcategoria] > [Documento]`
  - Links relativos funcionais
  - Consistência em toda a documentação

- **TOC (Table of Contents)** - Adicionados em documentos > 200 linhas:
  - `api.md` (1878 linhas) - TOC completo com 10 seções principais
  - `architecture.md` (1478 linhas) - TOC com 12 seções principais
  - `roadmap.md` (1102 linhas) - Frontmatter adicionado
  - `tdd-complete-guide.md` (1055 linhas) - TOC com 8 seções principais
  - `gas-dnd-adaptation.md` (1007 linhas) - TOC com 8 seções principais

- **Frontmatter YAML** - Padronizado em todos os documentos principais:
  - `title`: Título do documento
  - `category`: Categoria principal (root, design, technical, planning)
  - `subcategory`: Subcategoria quando aplicável
  - `tags`: Tags relevantes para busca
  - `last_updated`: Data de última atualização
  - `difficulty`: Nível de dificuldade (beginner, intermediate, advanced)
  - `related`: Links para documentos relacionados

- **MkDocs Material** - Configuração completa:
  - `mkdocs.yml` - Configuração completa do MkDocs Material
  - `requirements-docs.txt` - Dependências Python para documentação
  - `docs/README-MKDOCS.md` - Guia completo de uso do MkDocs
  - Navegação hierárquica configurada
  - Tema Material Design com dark mode
  - Busca integrada configurada
  - Plugins de Git (data de última modificação)

### 📝 Modificado

- **Todos os documentos principais** - Adicionados breadcrumbs e frontmatter YAML
- **README.md** - Adicionada seção sobre MkDocs Material
- **Documentos de índice** - Atualizados com frontmatter e breadcrumbs

### 🎯 Benefícios

1. **Navegação Melhorada:**
   - Breadcrumbs facilitam localização de informações
   - NAVIGATION.md fornece múltiplas formas de encontrar conteúdo
   - TOC em documentos grandes melhora navegação interna

2. **Descoberta de Conteúdo:**
   - GLOSSARY.md explica conceitos rapidamente
   - Tags e categorias facilitam busca
   - Referências cruzadas conectam conceitos relacionados

3. **Organização:**
   - Frontmatter YAML padronizado permite busca e filtragem
   - Estrutura consistente em toda documentação
   - Preparado para geração de HTML com MkDocs

4. **Experiência do Usuário:**
   - Documentação mais navegável e acessível
   - Busca facilitada por tags e categorias
   - Visual consistente com breadcrumbs e TOC

---

## 📊 Estatísticas

- **Total de documentos:** 44 arquivos Markdown
- **Documentos com frontmatter:** 44 (100%)
- **Documentos com breadcrumbs:** 44 (100%)
- **Documentos com TOC:** 5 (documentos > 200 linhas)
- **Novos arquivos criados:** 4 (NAVIGATION.md, GLOSSARY.md, mkdocs.yml, requirements-docs.txt, README-MKDOCS.md, CHANGELOG-DOCS.md)

---

**Última atualização:** 2024-12-27
