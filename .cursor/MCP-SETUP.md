# 🚀 Configuração do MCP Unreal Engine - GUIA COMPLETO

## ✅ Passo 1: Configurar o Unreal Engine (FAÇA ISSO PRIMEIRO!)

### 1.1 Habilitar Python Editor Script Plugin
1. Abra seu projeto no Unreal Engine 5.7
2. Vá em `Edit` → `Plugins`
3. Procure por **"Python Editor Script Plugin"**
4. **Marque a opção para habilitar**
5. Clique em **"Restart Now"** se solicitado

### 1.2 Habilitar Remote Execution
1. No Unreal Editor, vá em `Edit` → `Project Settings`
2. Procure por **"Python"** na barra de busca
3. Encontre a opção **"Enable Remote Execution"**
4. **Marque essa opção**
5. Feche e salve

## ✅ Passo 2: Configurar no Cursor

### 2.1 Abrir Configurações MCP
1. No Cursor, pressione `Ctrl+Shift+J` (ou `Cmd+Shift+J` no Mac)
2. Vá em **Features** → **Model Context Protocol**
3. Clique em **"Add Server"** ou **"New MCP Server"**

### 2.2 Adicionar Unreal Engine MCP
Cole esta configuração:

```json
{
  "name": "unreal",
  "command": "npx",
  "args": [
    "-y",
    "@runreal/unreal-mcp"
  ]
}
```

**OU** se preferir usar o servidor local instalado:

```json
{
  "name": "unreal",
  "command": "node",
  "args": [
    "F:/UNREAL GAME/unreal-mcp/server/bin.ts"
  ]
}
```

### 2.3 Reiniciar o Cursor
- Feche completamente o Cursor (`File` → `Exit`)
- Abra novamente

## ✅ Passo 3: Verificar se Funcionou

1. Abra o projeto no Unreal Engine
2. No Cursor, tente usar comandos como:
   - "Liste os assets do projeto"
   - "Mostre informações do projeto"
   - "Execute um comando de console no Unreal"

## 🛠️ Ferramentas Disponíveis

O MCP oferece estas ferramentas:

- `editor_list_assets` - Lista todos os assets
- `editor_get_project_info` - Informações do projeto
- `editor_console_command` - Executa comandos de console
- `editor_create_object` - Cria objetos no mundo
- `editor_get_world_outliner` - Lista todos os atores
- `editor_take_screenshot` - Tira screenshot do editor
- E muito mais!

## ⚠️ Troubleshooting

### Erro: "MCP Unreal: Unexpected token 'C', Connection..."
**Solução:**
1. Verifique se o Python Editor Script Plugin está habilitado
2. Verifique se "Enable Remote Execution" está marcado
3. Reinicie o Unreal Editor completamente
4. Feche e abra o Cursor completamente
5. Verifique processos Node.js em execução e encerre qualquer processo zombie do unreal-mcp

### MCP não conecta
1. Certifique-se de que o Unreal Editor está aberto
2. Verifique se o projeto está carregado
3. Tente mudar o bind address de `127.0.0.1` para `0.0.0.0` (nas configurações do Unreal)

## 📝 Notas Importantes

- ⚠️ Seus agentes de IA terão acesso completo ao Editor
- ⚠️ Revise todas as mudanças sugeridas antes de aprovar
- ✅ Este MCP não requer plugins C++ adicionais
- ✅ Usa o Python Remote Execution nativo do Unreal


