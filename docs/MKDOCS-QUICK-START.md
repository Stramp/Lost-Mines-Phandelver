---
title: "MkDocs - Guia Rápido"
category: root
tags: [mkdocs, quick-start, guide]
last_updated: 2024-12-27
---

**Navegação:** [Home](../README.md) > [Documentação](index.md) > MkDocs Quick Start

# 🚀 MkDocs Material - Guia Rápido

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Início Rápido</b></summary>

> Este guia mostra como começar a usar a documentação do MyProject2 em menos de 2 minutos.

</details>

---

## 📦 Instalação (Uma Vez)

```bash
# Instalar dependências
pip install -r requirements-docs.txt
```

**Tempo estimado:** 1-2 minutos

---

## 🎯 Comandos Essenciais

### Desenvolvimento Local

```bash
# Servir localmente (com auto-reload)
mkdocs serve

# Acessar em: http://127.0.0.1:8000
```

**O que faz:** Inicia servidor local que atualiza automaticamente quando você edita arquivos.

### Build para Produção

```bash
# Gerar site estático
mkdocs build

# Site será gerado em: site/
```

**O que faz:** Gera HTML estático na pasta `site/` (não versionar no Git).

### Deploy para GitHub Pages

```bash
# Deploy automático
mkdocs gh-deploy
```

**O que faz:** Faz deploy automático para GitHub Pages na branch `gh-pages`.

---

## 📝 Editar Documentação

1. **Edite arquivos Markdown** em `docs/`
2. **Salve o arquivo**
3. **Visualize no navegador** - O servidor atualiza automaticamente!

**Exemplo:**
```bash
# Editar arquivo
code docs/index.md

# Servidor detecta mudança e atualiza automaticamente
# Navegador atualiza sozinho (ou pressione F5)
```

---

## 🎨 Recursos Disponíveis

### Admonitions (Caixas de Aviso)

```markdown
!!! note "Nota"
    Esta é uma nota importante.

!!! warning "Aviso"
    Cuidado com isso!
```

### Tabs (Abas)

```markdown
=== "C++"

    ```cpp
    void Function();
    ```

=== "Blueprint"

    ```cpp
    // Blueprint equivalent
    ```
```

### Fórmulas Matemáticas

```latex
$$
E = mc^2
$$
```

### Teclas de Atalho

++ctrl+shift+p++ - Abre command palette

### Destaque de Texto

==Texto destacado==

### Ícones

:material-github: GitHub

:fontawesome-brands-discord: Discord

---

## 🐛 Problemas Comuns

### "mkdocs: command not found"

**Solução:**
```bash
pip install -r requirements-docs.txt
```

### "ModuleNotFoundError"

**Solução:**
```bash
pip install -r requirements-docs.txt
```

### Site não atualiza

**Solução:**
- Verifique se `mkdocs serve` está rodando
- Pressione F5 no navegador
- Ou execute `mkdocs build --clean` e depois `mkdocs serve`

---

## 📚 Mais Informações

- **[Setup Completo](MKDOCS-SETUP-COMPLETE.md)** - Guia completo com todos os recursos
- **[Melhorias](MKDOCS-IMPROVEMENTS.md)** - Lista de melhorias implementadas
- **[README MkDocs](README-MKDOCS.md)** - Documentação detalhada

---

## ✅ Checklist Rápido

- [ ] Dependências instaladas (`pip install -r requirements-docs.txt`)
- [ ] Servidor local funcionando (`mkdocs serve`)
- [ ] Site carrega no navegador
- [ ] Edições aparecem automaticamente

---

**Pronto!** Você está pronto para editar a documentação! 🎉

---

**Última atualização:** 2024-12-27
