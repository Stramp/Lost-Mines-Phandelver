# 🎯 File System MCP e Git MCP - Exemplos Práticos

## 📁 File System MCP - O que faz e exemplos

### O que é:
Permite que a IA navegue, leia, escreva e busque arquivos no seu projeto **sem você precisar abrir manualmente**.

### Exemplos Práticos:

#### 1. **Buscar arquivos rapidamente**
**Você pergunta:**
> "Encontre todos os arquivos .h que contêm a palavra 'Character'"

**A IA faz:**
- Busca em todo o projeto
- Lista os arquivos encontrados
- Mostra onde está a palavra

**Sem MCP:** Você teria que abrir cada arquivo manualmente ou usar busca do Windows

#### 2. **Organizar estrutura do projeto**
**Você pergunta:**
> "Crie uma pasta Components/ e mova todos os arquivos de componentes para lá"

**A IA faz:**
- Cria a pasta
- Move os arquivos automaticamente
- Atualiza referências se necessário

**Sem MCP:** Você teria que fazer tudo manualmente, arquivo por arquivo

#### 3. **Ler múltiplos arquivos de uma vez**
**Você pergunta:**
> "Mostre todos os arquivos .Build.cs do projeto e compare as dependências"

**A IA faz:**
- Lê todos os arquivos .Build.cs
- Compara as dependências
- Mostra diferenças e sugestões

**Sem MCP:** Você teria que abrir cada arquivo manualmente

#### 4. **Buscar padrões em código**
**Você pergunta:**
> "Encontre todos os lugares onde usamos UPROPERTY(BlueprintReadWrite)"

**A IA faz:**
- Busca em todos os arquivos .h e .cpp
- Lista todas as ocorrências
- Mostra contexto de cada uso

**Sem MCP:** Você usaria Ctrl+Shift+F, mas a IA não conseguiria processar os resultados

#### 5. **Criar estrutura de pastas**
**Você pergunta:**
> "Crie a estrutura de pastas para um sistema de inventário: Inventory/ com subpastas Items/, UI/, Components/"

**A IA faz:**
- Cria todas as pastas de uma vez
- Organiza a estrutura
- Pronto para você começar a codificar

**Sem MCP:** Você criaria pasta por pasta manualmente

---

## 🔀 Git MCP - O que faz e exemplos

### O que é:
Permite que a IA faça operações Git **sem você precisar abrir terminal ou interface Git**.

### Exemplos Práticos:

#### 1. **Ver o que mudou**
**Você pergunta:**
> "O que mudou desde o último commit?"

**A IA faz:**
- Executa `git status` e `git diff`
- Mostra arquivos modificados
- Mostra as mudanças linha por linha
- Explica o que foi alterado

**Sem MCP:** Você abriria terminal, digitaria comandos, interpretaria a saída

#### 2. **Fazer commit inteligente**
**Você pergunta:**
> "Faça commit das mudanças com uma mensagem descrevendo o que foi feito"

**A IA faz:**
- Analisa as mudanças
- Cria mensagem de commit descritiva
- Faz o commit automaticamente
- Exemplo: "Adiciona sistema de inventário com classes Item e InventoryComponent"

**Sem MCP:** Você escreveria a mensagem manualmente, podendo esquecer detalhes

#### 3. **Criar branch para feature**
**Você pergunta:**
> "Crie uma branch chamada 'feature/inventory-system' e mude para ela"

**A IA faz:**
- Cria a branch
- Muda para ela
- Confirma a operação

**Sem MCP:** Você digitaria: `git checkout -b feature/inventory-system`

#### 4. **Ver histórico de um arquivo**
**Você pergunta:**
> "Mostre o histórico de mudanças do arquivo MyCharacter.h"

**A IA faz:**
- Executa `git log` para aquele arquivo
- Mostra commits, autores, datas
- Pode mostrar diffs de commits específicos

**Sem MCP:** Você usaria `git log -- MyCharacter.h` e interpretaria a saída

#### 5. **Reverter mudanças**
**Você pergunta:**
> "Desfaça as mudanças no arquivo MyProject2.Build.cs"

**A IA faz:**
- Executa `git checkout -- MyProject2.Build.cs`
- Confirma que foi revertido
- Mostra o estado anterior

**Sem MCP:** Você precisaria saber o comando exato e executá-lo

#### 6. **Ver diferenças entre branches**
**Você pergunta:**
> "Compare a branch main com a branch feature/inventory-system"

**A IA faz:**
- Executa `git diff main..feature/inventory-system`
- Mostra todas as diferenças
- Explica o que foi adicionado/removido

**Sem MCP:** Você executaria o comando e interpretaria a saída manualmente

#### 7. **Ver quem modificou uma linha**
**Você pergunta:**
> "Quem escreveu essa função BeginPlay() e quando?"

**A IA faz:**
- Usa `git blame` ou `git log -p`
- Mostra autor, data, commit
- Pode mostrar o contexto do commit

**Sem MCP:** Você usaria `git blame` e interpretaria a saída

---

## 💡 Exemplos Combinados (File System + Git)

### Cenário Real: Adicionar nova feature

**Você pergunta:**
> "Crie um sistema de inventário. Crie as pastas, arquivos base, e faça commit inicial"

**A IA faz (com ambos MCPs):**
1. **File System MCP:**
   - Cria estrutura: `Source/MyProject2/Inventory/`
   - Cria arquivos: `Item.h`, `Item.cpp`, `InventoryComponent.h`, etc.
   - Escreve código base seguindo padrões Unreal

2. **Git MCP:**
   - Cria branch: `feature/inventory-system`
   - Faz commit: "Adiciona sistema de inventário base"
   - Mostra status do que foi criado

**Sem MCPs:** Você faria tudo manualmente, passo a passo

---

## 🎮 Exemplos Específicos para Unreal Engine

### File System MCP + Unreal:

**Exemplo 1:**
> "Encontre todos os Blueprints que herdam de Character e liste os arquivos"

**A IA faz:**
- Busca arquivos `.uasset` na pasta Content/
- Identifica quais são Characters
- Lista os caminhos

**Exemplo 2:**
> "Crie uma nova classe Actor chamada PickupItem seguindo o padrão do projeto"

**A IA faz:**
- Lê exemplos de Actors existentes
- Cria `PickupItem.h` e `PickupItem.cpp` seguindo padrões
- Coloca nos diretórios corretos

### Git MCP + Unreal:

**Exemplo 1:**
> "O que mudou no código C++ desde ontem?"

**A IA faz:**
- Filtra commits de ontem
- Mostra apenas mudanças em `.cpp` e `.h`
- Explica o impacto das mudanças

**Exemplo 2:**
> "Crie uma branch para testar uma nova mecânica de combate"

**A IA faz:**
- Cria branch: `feature/combat-system`
- Muda para ela
- Pronto para você desenvolver

---

## ✅ Resumo: Por que são úteis?

### File System MCP:
- ✅ **Busca rápida** - Encontra arquivos sem você procurar
- ✅ **Organização** - Cria estrutura automaticamente
- ✅ **Análise** - Lê múltiplos arquivos de uma vez
- ✅ **Automação** - Faz tarefas repetitivas

### Git MCP:
- ✅ **Sem terminal** - Operações Git via chat
- ✅ **Commits inteligentes** - Mensagens descritivas automáticas
- ✅ **Histórico fácil** - Ver mudanças rapidamente
- ✅ **Workflow fluido** - Não precisa sair do Cursor

---

## 🚀 Quer configurar agora?

São simples de configurar e funcionam bem! Quer que eu configure os dois agora?

