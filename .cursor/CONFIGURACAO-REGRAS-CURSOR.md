# 🔧 Configuração para Garantir que o Cursor Leia as Regras

## 🚨 Problema

O Cursor às vezes ignora regras criadas em arquivos `.mdc` na pasta `.cursor/rules/`, mesmo quando marcadas como `alwaysApply: true` ou globais.

## ✅ Soluções Implementadas

### 1. Arquivo de Inicialização (000-cursor-rules-loader.mdc)

Criamos um arquivo `000-cursor-rules-loader.mdc` que força o Cursor a:

- ✅ Verificar e ler todas as regras no início de cada sessão
- ✅ Confirmar que as regras foram carregadas
- ✅ Aplicar regras em ordem de prioridade
- ✅ Detectar quando regras não estão sendo seguidas

**Este arquivo já está criado e deve funcionar automaticamente.**

### 2. Configuração no Campo "Regras para IA" do Cursor

**IMPORTANTE:** Configure o campo "Regras para IA" (ou "Regras do Usuário") nas configurações do Cursor com o seguinte texto:

```markdown
SEMPRE COMEÇAR POR:

1. VERIFICAR SE VOCÊ TEM acesso à pasta .cursor/rules/ e aos arquivos .mdc dentro dela.

- Se tiver, confirme isso para o usuário listando quantas regras foram encontradas.

- Se não tiver, SEMPRE AVISE O USUÁRIO. SEMPRE inclua o emoji de "sinal de aviso" ⚠️ e "AVISO" em CAIXA ALTA, pra garantir que o seu aviso seja notado pelo usuário.

2. Lendo TODAS as regras da pasta .cursor/rules/ ANTES de responder qualquer coisa.

3. Aplicando as regras em ordem de prioridade:
   - Máxima: clean-code-mandatory.mdc, execution-guard.mdc, project-architecture.mdc
   - Alta: teaching-role.mdc, test-driven-development.mdc, task-execution.mdc
   - Média: Todas as outras regras

4. Sempre confirmar no início da resposta que as regras foram carregadas com:
   "✅ REGRAS CARREGADAS: [número] regras encontradas e aplicadas"
```

**Como configurar:**

1. Abra o Cursor
2. Vá em **Settings** (Configurações)
3. Procure por **"Rules for AI"** ou **"User Rules"** ou **"Regras para IA"**
4. Cole o texto acima no campo
5. Salve

### 3. Configuração do VS Code para Arquivos .mdc

**IMPORTANTE:** Desative a UI especial do Cursor para arquivos `.mdc` para evitar problemas de autogeração e salvamento.

#### Opção 1: Via JSON (Recomendado)

1. Abra o Cursor
2. Pressione `Ctrl+Shift+P` (ou `Cmd+Shift+P` no macOS)
3. Digite e selecione **"Preferences: Open User Settings (JSON)"**
4. Adicione ou modifique a seguinte configuração:

```json
{
  "workbench.editorAssociations": {
    "*.mdc": "default"
  }
}
```

5. Salve o arquivo (`Ctrl+S` ou `Cmd+S`)

#### Opção 2: Via UI de Configurações

1. Abra o Cursor
2. Vá em **File > Preferences > Settings** (`Ctrl+,` ou `Cmd+,`)
3. Procure por `workbench.editorAssociations`
4. Clique em **"Edit in settings.json"**
5. Adicione a configuração:

```json
"workbench.editorAssociations": {
  "*.mdc": "default"
}
```

6. Salve e reinicie se necessário

### 4. Verificar Configuração de Globs

**IMPORTANTE:** Garanta que os arquivos `.mdc` tenham `globs: "**/*"` no frontmatter para serem globais.

**Baseado no repositório do bmadcode:**
- ✅ Regras com `alwaysApply: true` devem ter `globs: "**/*"` para funcionarem globalmente
- ✅ Regras específicas podem ter globs mais restritivos (ex: `["*.cpp", "*.h"]`)
- ✅ Regras sem globs podem não ser aplicadas corretamente

**Exemplo de frontmatter correto para regras globais:**

```yaml
---
description: Descrição da regra
alwaysApply: true
priority: 1
globs: "**/*"
---
```

**Exemplo de frontmatter para regras específicas:**

```yaml
---
description: Regra específica para arquivos C++
alwaysApply: false
globs: ["*.cpp", "*.h", "*.hpp"]
---
```

**✅ Status das Regras do Projeto:**
- Todas as regras com `alwaysApply: true` agora têm `globs: "**/*"` configurado
- Arquivo de configuração `.vscode/settings.json` criado com `workbench.editorAssociations`

## 🧪 Como Testar

### Teste 1: Verificação de Carregamento

1. Inicie um novo chat no Cursor
2. A primeira resposta do agente DEVE começar com:
   ```
   ✅ REGRAS CARREGADAS: [número] regras encontradas e aplicadas
   ```
3. Se não aparecer, as regras não estão sendo lidas

### Teste 2: Verificação de Aplicação

1. Peça algo que violaria Clean Code (ex: "crie uma função helper dentro de um Motor")
2. O agente DEVE parar e explicar por que não pode fazer isso
3. Se não parar, as regras não estão sendo aplicadas

### Teste 3: Verificação de Postura

1. Observe se o agente mantém postura de expert/teacher
2. Observe se responde em português brasileiro
3. Observe se explica o "porquê" das decisões

## 🔍 Troubleshooting

### Problema: Regras não são carregadas

**Soluções:**

1. ✅ Verifique se o arquivo `000-cursor-rules-loader.mdc` existe
2. ✅ Verifique se configurou o campo "Regras para IA"
3. ✅ Verifique se `workbench.editorAssociations` está configurado
4. ✅ Reinicie o Cursor
5. ✅ Inicie um novo chat (não continue um antigo)

### Problema: Regras são carregadas mas não aplicadas

**Soluções:**

1. ✅ Verifique se os arquivos `.mdc` têm `alwaysApply: true`
2. ✅ Verifique se os globs estão configurados como `"**/*"`
3. ✅ Verifique se não há conflitos entre regras
4. ✅ Use o comando `@rules` no chat para forçar leitura

### Problema: Cursor ignora regras específicas

**Soluções:**

1. ✅ Verifique a prioridade da regra (arquivos com `000-` têm prioridade)
2. ✅ Verifique se a regra não está conflitando com outras
3. ✅ Tente mover a regra para um arquivo com nome que comece com `000-`
4. ✅ Adicione a regra diretamente no campo "Regras para IA"

## 📚 Referências e Recursos

### Repositório de Regras Automáticas (bmadcode)

**Repositório GitHub:** [Regras Automáticas do Cursor - Fluxo Ágil](https://github.com/bmadcode/cursor-rules)

**Principais pontos:**
- ✅ Garante que os globs estejam configurados como globais (`globs: "**/*"`)
- ✅ Permite autogeração de regras pelo agente
- ✅ Resolve problemas de salvamento de regras

**Uso:**
- Depois de adicionar o arquivo `.mdc` na pasta `.cursor/rules/`, mande o agente escrever regras novas ou atualizar as existentes
- Não edite os arquivos manualmente - deixe o agente gerenciar

### Artigos e Discussões

- [Post do Reddit sobre o problema](https://www.reddit.com/r/cursor/comments/...)
- [Artigo Medium - Cursor Rules: Why Your AI Agent Is Ignoring You](https://sdrmike.medium.com/cursor-rules-why-your-ai-agent-is-ignoring-you-and-how-to-fix-it-5b4d2ac0b1b0)
- [Fórum do Cursor - Ultimate Rule Generator](https://forum.cursor.com/t/ultimate-rule-generator-no-more-failure-to-generate-and-private-rules/)

## ✅ Checklist de Configuração

Antes de considerar configurado:

- [x] Arquivo `000-cursor-rules-loader.mdc` existe em `.cursor/rules/` ✅
- [ ] Campo "Regras para IA" está configurado no Cursor (configuração manual necessária)
- [x] `workbench.editorAssociations` está configurado em `.vscode/settings.json` ✅
- [x] Todos os arquivos `.mdc` com `alwaysApply: true` têm `globs: "**/*"` configurado ✅
- [ ] Teste de carregamento passou (primeira resposta confirma regras)
- [ ] Teste de aplicação passou (agente para quando viola regras)
- [ ] Teste de postura passou (agente mantém comportamento esperado)

## 🚀 Autogeração de Regras (Baseado no Repositório bmadcode)

**IMPORTANTE:** Com a configuração correta, você pode pedir ao agente para criar ou atualizar regras automaticamente:

**Exemplos de comandos:**
- "Escrever uma regra nova para [tema]"
- "Atualizar a regra [nome-da-regra] com [mudanças]"
- "Criar regra para [funcionalidade específica]"

**O agente irá:**
1. ✅ Criar ou atualizar o arquivo `.mdc` na pasta `.cursor/rules/`
2. ✅ Configurar corretamente o frontmatter com `globs: "**/*"` se necessário
3. ✅ Garantir que a regra está formatada corretamente
4. ✅ Não é necessário editar manualmente os arquivos

## 🎯 Resultado Esperado

Após configurar tudo corretamente:

- ✅ Todas as regras são lidas no início de cada sessão
- ✅ Regras são aplicadas consistentemente
- ✅ Agente para quando algo viola regras
- ✅ Comportamento é previsível e confiável
- ✅ Você pode confiar que as regras estão sendo seguidas

---

**Lembre-se:** Se as regras ainda não estão funcionando após todas essas configurações, tente:

1. Reiniciar o Cursor completamente
2. Iniciar um novo chat (não continuar um antigo)
3. Verificar se há atualizações do Cursor disponíveis
4. Contatar suporte do Cursor se o problema persistir

