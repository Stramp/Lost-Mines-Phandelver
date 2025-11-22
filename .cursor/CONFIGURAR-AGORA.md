# ⚡ CONFIGURAÇÃO RÁPIDA - MCP Unreal Engine

## 🎯 O QUE JÁ FOI FEITO
✅ MCP Unreal Engine instalado em: `F:\UNREAL GAME\unreal-mcp`
✅ Arquivos de configuração criados
✅ Guia completo criado

## 🚀 PRÓXIMOS PASSOS (FAÇA AGORA)

### 1️⃣ CONFIGURAR UNREAL ENGINE (5 minutos)

**No Unreal Editor:**
1. `Edit` → `Plugins` → Procure "Python Editor Script Plugin" → **HABILITE**
2. `Edit` → `Project Settings` → Busque "Python" → **Marque "Enable Remote Execution"**
3. **Reinicie o Editor**

### 2️⃣ CONFIGURAR NO CURSOR (2 minutos)

**Opção A - Via UI (Recomendado):**
1. Pressione `Ctrl+Shift+J` no Cursor
2. Vá em **Features** → **Model Context Protocol**
3. Clique em **"Add Server"** ou **"New MCP Server"**
4. Cole este JSON:

```json
{
  "name": "unreal",
  "command": "npx",
  "args": ["-y", "@runreal/unreal-mcp"]
}
```

5. **Feche e reabra o Cursor completamente**

**Opção B - Copiar do arquivo:**
- Abra `.cursor/mcp-config-cursor.json`
- Copie o conteúdo do servidor "unreal"
- Cole nas configurações do Cursor

### 3️⃣ TESTAR

1. Abra o projeto no Unreal Engine
2. No Cursor, pergunte: "Liste os assets do projeto Unreal"
3. Se funcionar, está configurado! 🎉

## 📋 MCPs ADICIONAIS (Opcional)

Você também pode adicionar:

**File System MCP:**
```json
{
  "name": "filesystem",
  "command": "npx",
  "args": ["-y", "@modelcontextprotocol/server-filesystem", "F:/UNREAL GAME/MyProject2"]
}
```

**Git MCP:**
```json
{
  "name": "git",
  "command": "npx",
  "args": ["-y", "@modelcontextprotocol/server-git", "F:/UNREAL GAME/MyProject2"]
}
```

## ❓ PROBLEMAS?

Veja o guia completo em: `.cursor/MCP-SETUP.md`

## ✅ PRONTO!

Depois de configurar, você poderá:
- Controlar o Unreal Engine via comandos de linguagem natural
- Listar assets, criar objetos, executar comandos
- Integrar desenvolvimento C++ com o editor


