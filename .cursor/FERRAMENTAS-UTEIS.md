# 🛠️ Ferramentas e MCPs Úteis para Desenvolvimento

## 🎯 MCPs Recomendados (que funcionam bem)

### 1. **GitHub MCP** ⭐ MUITO ÚTIL
**O que faz:**
- Acessa repositórios GitHub diretamente
- Cria issues, PRs, comentários
- Busca código em repositórios
- Visualiza histórico de commits

**Por que é útil:**
- Acessar exemplos de código Unreal Engine
- Ver documentação de plugins
- Buscar soluções em projetos open-source

**Como instalar:**
- Settings → Tools & MCP → Add Custom MCP
- Ou use o botão "Add to Cursor" na documentação do GitHub MCP

### 2. **File System MCP** ⭐ ESSENCIAL
**O que faz:**
- Navega arquivos do projeto
- Busca por padrões
- Lê/escreve arquivos
- Operações em lote

**Por que é útil:**
- Organizar estrutura do projeto
- Buscar arquivos rapidamente
- Gerenciar assets

**Configuração:**
```json
{
  "name": "filesystem",
  "command": "npx",
  "args": ["-y", "@modelcontextprotocol/server-filesystem", "F:/UNREAL GAME/MyProject2"]
}
```

### 3. **Git MCP** ⭐ ESSENCIAL
**O que faz:**
- Operações Git integradas
- Commits, branches, merges
- Histórico e diffs
- Status do repositório

**Por que é útil:**
- Gerenciar versões sem sair do Cursor
- Ver mudanças rapidamente
- Criar branches para features

**Configuração:**
```json
{
  "name": "git",
  "command": "npx",
  "args": ["-y", "@modelcontextprotocol/server-git", "F:/UNREAL GAME/MyProject2"]
}
```

### 4. **Notion MCP** (se você usa Notion)
**O que faz:**
- Acessa documentos do Notion
- Cria/atualiza páginas
- Busca informações
- Integra documentação

**Por que é útil:**
- Manter documentação do projeto
- Acessar requisitos e design docs
- Gerenciar tarefas

### 5. **Figma MCP** (se você usa Figma)
**O que faz:**
- Acessa designs do Figma
- Exporta assets
- Visualiza componentes

**Por que é útil:**
- Verificar designs durante desenvolvimento
- Exportar assets diretamente

## 🔧 Ferramentas de Desenvolvimento (não MCP)

### 1. **Unreal Engine Tools** (já configurado)
- ✅ Tasks de build no workspace
- ✅ Launch configurations
- ✅ IntelliSense configurado

### 2. **Extensões VS Code/Cursor Essenciais**

#### C++ Development
- **C/C++** (Microsoft) - IntelliSense, debugging
- **C++ Intellisense** - Autocomplete melhorado
- **clangd** - Language server (já configurado com .clangd)

#### Unreal Engine
- **Unreal Engine 4 Snippets** - Snippets para UE
- **UnrealScript** - Syntax highlighting

#### Produtividade
- **GitLens** - Git avançado
- **Error Lens** - Erros inline
- **Todo Tree** - Gerenciamento de TODOs
- **Better Comments** - Comentários destacados
- **Code Spell Checker** - Verificação ortográfica

### 3. **Ferramentas Externas**

#### Visual Studio Tools para Unreal Engine
- Logs do Unreal no VS
- Visualização de macros
- Depuração avançada
- Link: https://learn.microsoft.com/pt-br/visualstudio/gamedev/unreal/get-started/vs-tools-unreal-install

#### ReSharper C++ para Unreal Engine
- Assistência de codificação inteligente
- Inspeções de código
- Suporte específico para UE
- Link: https://www.jetbrains.com/pt-br/lp/resharper-cpp-unreal-engine/

#### Unreal Insights
- Profiling de performance
- Análise de frame time
- Memory profiling
- Network profiling
- Já vem com o Unreal Engine

## 📚 Recursos de Aprendizado

### Documentação
- **Unreal Engine Docs**: https://docs.unrealengine.com/
- **API Reference**: https://docs.unrealengine.com/5.7/en-US/API/
- **C++ Programming**: https://docs.unrealengine.com/5.7/en-US/cpp-programming-in-unreal-engine/

### Comunidade
- **Unreal Engine Forums**: https://forums.unrealengine.com/
- **Unreal Engine Discord**
- **Stack Overflow** - Tag: `unreal-engine`
- **Reddit** - r/unrealengine

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
- `Ctrl+Shift+P` - Command Palette (Cursor)
- `F5` - Compile (no editor)
- `Ctrl+Alt+F11` - Hot Reload

## 💡 Dicas de Produtividade

1. **Use snippets** - Configure snippets personalizados para código comum
2. **Use tasks** - Configure tasks para builds frequentes
3. **Use Git** - Commite frequentemente, use branches
4. **Use Blueprints** - Para prototipagem rápida
5. **Use C++** - Para performance crítica
6. **Profile antes de otimizar** - Use Unreal Insights
7. **Documente** - Comente código complexo
8. **Use versionamento** - Git para código, Perforce/Plastic para assets grandes

## 🚀 Próximos Passos Recomendados

1. **Instale File System e Git MCPs** (são simples e funcionam bem)
2. **Configure GitHub MCP** (se usar GitHub)
3. **Instale extensões essenciais** do Cursor
4. **Explore Unreal Insights** para profiling
5. **Configure snippets** para código comum

