# Ferramentas e MCPs para Desenvolvimento Unreal Engine

## 🚀 MCPs Recomendados

### 1. Unreal Engine MCP
**Repositório**: https://github.com/flopperam/unreal-engine-mcp

Controla o Unreal Engine 5.5+ via comandos em linguagem natural.

**Instalação**:
```bash
# Clone o repositório
git clone https://github.com/flopperam/unreal-engine-mcp.git
cd unreal-engine-mcp

# Siga as instruções no README para instalação
```

**Configuração no Cursor**:
1. Localize o arquivo de configuração do Cursor (Settings > MCP)
2. Adicione a configuração do `mcp-config-example.json`
3. Ajuste os caminhos conforme seu ambiente

### 2. MCPs Úteis Gerais

#### File System MCP
```bash
npx -y @modelcontextprotocol/server-filesystem
```
- Navegação de arquivos
- Busca por padrões
- Operações em lote

#### Git MCP
```bash
npx -y @modelcontextprotocol/server-git
```
- Operações Git
- Commits, branches, merges
- Histórico e diffs

## 🛠️ Extensões VS Code/Cursor Recomendadas

### Essenciais para C++
- **C/C++** (Microsoft) - IntelliSense, debugging
- **C++ Intellisense** - Autocomplete melhorado
- **clangd** - Language server

### Unreal Engine
- **Unreal Engine 4 Snippets** - Snippets para UE4/UE5
- **UnrealScript** - Syntax highlighting

### Produtividade
- **GitLens** - Git avançado
- **Error Lens** - Erros inline
- **Todo Tree** - Gerenciamento de TODOs
- **Better Comments** - Comentários destacados

## 📚 Ferramentas de Desenvolvimento

### Visual Studio Tools para Unreal Engine
**Link**: https://learn.microsoft.com/pt-br/visualstudio/gamedev/unreal/get-started/vs-tools-unreal-install

**Funcionalidades**:
- Logs do Unreal Engine no Visual Studio
- Visualização de macros
- Adicionar classes, módulos e plugins
- Depuração de código C++ chamado por Blueprints
- Localização de referências aos Blueprints

### ReSharper C++ para Unreal Engine
**Link**: https://www.jetbrains.com/pt-br/lp/resharper-cpp-unreal-engine/

- Assistência de codificação inteligente
- Inspeções de código
- Suporte específico para Unreal Engine
- Integração com UnrealHeaderTool

## 🔧 Ferramentas de Build

### UnrealBuildTool (UBT)
- Já configurado no workspace
- Use `Ctrl+Shift+P > Tasks: Run Task` para builds
- Tasks disponíveis:
  - Debug, DebugGame, Development, Test, Shipping
  - Build, Rebuild, Clean

### Generate Project Files
- Task disponível no workspace
- Use após modificar `.Build.cs`

## 🐛 Ferramentas de Debugging

### Unreal Insights
- Profiling de performance
- Análise de frame time
- Memory profiling
- Network profiling

### Visual Studio Debugger
- Breakpoints
- Watch variables
- Call stack
- Memory inspection

## 📊 Ferramentas de Análise

### Static Analysis
- **PVS-Studio** - Análise estática
- **Cppcheck** - Detecção de bugs
- **Clang Static Analyzer** - Análise estática

### Code Formatting
- **ClangFormat** - Formatação automática
- Configure via `.clang-format`

## 🎮 Comandos Úteis do Unreal Engine

### Console Commands (Runtime)
```
stat fps              # Mostra FPS
stat unit            # Estatísticas de performance
stat memory          # Uso de memória
showdebug ai         # Debug de IA
showdebug collision  # Debug de colisão
```

### Editor Commands
- `Ctrl+Shift+P` - Command Palette
- `F5` - Compile (no editor)
- `Ctrl+Alt+F11` - Hot Reload

## 📖 Recursos de Aprendizado

### Documentação Oficial
- **Unreal Engine Docs**: https://docs.unrealengine.com/
- **API Reference**: https://docs.unrealengine.com/5.7/en-US/API/
- **C++ Programming**: https://docs.unrealengine.com/5.7/en-US/cpp-programming-in-unreal-engine/

### Comunidade
- **Unreal Engine Forums**: https://forums.unrealengine.com/
- **Unreal Engine Discord**
- **Stack Overflow** - Tag: `unreal-engine`

## ✅ Checklist de Configuração

- [ ] Instalar extensões VS Code/Cursor recomendadas
- [ ] Configurar Unreal Engine MCP (opcional)
- [ ] Configurar File System MCP (opcional)
- [ ] Configurar Git MCP (opcional)
- [ ] Instalar Visual Studio Tools para Unreal (opcional)
- [ ] Configurar ClangFormat (opcional)
- [ ] Testar tasks de build do workspace

## 💡 Dicas de Produtividade

1. Use **Blueprints** para prototipagem rápida
2. Use **C++** para performance crítica
3. **SEMPRE** teste builds antes de commitar
4. Use **Unreal Insights** para identificar gargalos
5. Mantenha **dependências mínimas** no `.Build.cs`
6. **Documente** código complexo
7. Use **static analysis** regularmente
8. **Profile** antes de otimizar

