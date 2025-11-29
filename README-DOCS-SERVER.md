# 📚 Servidor de Documentação Local

Servidor simples para visualizar documentação Markdown com **sidebar de navegação em árvore**.

## 🚀 Como Usar

### 1. Iniciar Servidor

```bash
python docs_server.py
```

### 2. Abrir no Navegador

Abra: **http://localhost:8000**

### 3. Navegar

- **Sidebar esquerda:** Navegação em árvore de todos os arquivos `.md`
- **Conteúdo direito:** Preview do arquivo selecionado
- **Links:** Funcionam automaticamente entre arquivos

## ✨ Características

- ✅ **Sidebar automática** - Gera árvore de navegação automaticamente
- ✅ **Não modifica MDs** - Apenas lê e exibe
- ✅ **Suporta Markdown completo** - Tabelas, código, listas, etc.
- ✅ **Links funcionam** - Navegação entre arquivos
- ✅ **Tema escuro na sidebar** - Fácil de ver
- ✅ **Responsivo** - Funciona bem em diferentes tamanhos

## 🛑 Parar Servidor

Pressione `Ctrl+C` no terminal

## 📝 Notas

- O servidor escaneia a pasta `docs/` recursivamente
- Ignora pastas `.git`, `__pycache__`, etc.
- Converte Markdown para HTML automaticamente
- Mantém estrutura de pastas na sidebar

## 🔧 Requisitos

- Python 3.x
- Biblioteca `markdown`: `pip install markdown`

---

**Criado para facilitar navegação na documentação do MyProject2**
