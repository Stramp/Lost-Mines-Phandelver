# Guia - Configurações Automáticas Implementadas

## ✅ Configurações Implementadas

### 1. EditorConfig (`.editorconfig`)
**Status:** ✅ Configurado

**O que faz:**
- Padroniza formatação entre editores (VS Code, Visual Studio, Cursor)
- Define tabs, espaços, encoding, etc.

**Como funciona:**
- Automático - editores que suportam EditorConfig aplicam automaticamente
- Não precisa fazer nada, apenas funciona

**Editores compatíveis:**
- ✅ VS Code (com extensão EditorConfig)
- ✅ Visual Studio 2017+
- ✅ Cursor (herda do VS Code)
- ✅ Rider
- ✅ Vim/Neovim (com plugin)

---

### 2. Pre-commit Hook (`.git/hooks/pre-commit`)
**Status:** ✅ Configurado

**O que faz:**
- Valida formatação de código antes de commitar
- Impede commits com código mal formatado
- Verifica arquivos C++ (.cpp, .h, .hpp)

**Como funciona:**
- Automático - roda antes de cada `git commit`
- Se código não estiver formatado, commit é bloqueado

**Como testar:**
```bash
# Fazer uma mudança em um arquivo .cpp
# Tentar commitar
git commit -m "teste"

# Se código não estiver formatado, verá erro
# Formate o código e tente novamente
```

**Desabilitar temporariamente:**
```bash
git commit --no-verify -m "mensagem"
# (não recomendado, mas possível)
```

---

### 3. Clang-Format Automático (`.vscode/settings.json`)
**Status:** ✅ Configurado

**O que faz:**
- Formata código automaticamente ao salvar arquivo
- Usa o arquivo `.clang-format` para regras

**Como funciona:**
- Ao salvar arquivo `.cpp` ou `.h`, formata automaticamente
- Não precisa fazer nada, apenas salvar

**Configuração aplicada:**
- `editor.formatOnSave: true` - Formata ao salvar
- `C_Cpp.clang_format_path` - Caminho do clang-format
- `C_Cpp.clang_format_style: "file"` - Usa `.clang-format`

**Verificar se está funcionando:**
1. Abra um arquivo `.cpp`
2. Desformate o código (remova espaços, quebre linhas)
3. Salve (Ctrl+S)
4. Código deve ser formatado automaticamente

---

## 🔧 Troubleshooting

### Pre-commit Hook não funciona

**Problema:** Hook não executa

**Solução:**
```bash
# Verificar se hook tem permissão de execução
chmod +x .git/hooks/pre-commit

# Testar manualmente
.git/hooks/pre-commit
```

### Clang-format não formata

**Problema:** Código não formata ao salvar

**Solução:**
1. Verifique se clang-format está instalado: `C:\Program Files\LLVM\bin\clang-format.exe`
2. Verifique se extensão C/C++ está instalada no Cursor/VS Code
3. Reinicie o Cursor
4. Verifique se `editor.formatOnSave` está `true` no settings.json

### EditorConfig não funciona

**Problema:** Formatação diferente entre editores

**Solução:**
1. Instale extensão EditorConfig no VS Code/Cursor
2. Reinicie o editor
3. EditorConfig aplica automaticamente

---

## 📝 Notas

- **Pre-commit hook** pode ser lento se validar compilação (desabilitado por padrão)
- **Clang-format** precisa do LLVM instalado
- **EditorConfig** precisa de extensão no editor (mas é padrão na maioria)

---

## ✅ Checklist

- [ ] EditorConfig criado (`.editorconfig`)
- [ ] Pre-commit hook criado (`.git/hooks/pre-commit`)
- [ ] Clang-format configurado no settings.json
- [ ] Hook tem permissão de execução
- [ ] Clang-format está instalado

---

**Todas as configurações estão ativas e funcionando automaticamente!**
