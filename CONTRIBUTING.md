# Guia de Contribuição

Obrigado por considerar contribuir com o projeto MyProject2! Este documento fornece diretrizes para contribuir de forma eficiente e alinhada com os padrões do projeto.

## Código de Conduta

Este projeto segue princípios de Clean Code, Design Patterns e arquitetura bem definida. Ao contribuir, você está concordando em seguir esses princípios.

## Como Contribuir

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 Guia Passo a Passo</b></summary>

> ### 1. Fazer Fork e Clone
>
> ```bash
> # Fork o repositório no GitHub
> # Clone seu fork
> git clone https://github.com/seu-usuario/MyProject2.git
> cd MyProject2
> ```
>
> ### 2. Criar Branch
>
> ```bash
> # Crie uma branch para sua feature/correção
> git checkout -b feat/nome-da-feature
> # ou
> git checkout -b fix/nome-da-correcao
> ```
>
> **Convenção de nomes de branches:**
> - `feat/` - Novas funcionalidades
> - `fix/` - Correções de bugs
> - `refactor/` - Refatorações
> - `docs/` - Documentação
> - `test/` - Testes
>
> ### 3. Desenvolver
>
> Siga as regras críticas do projeto:
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Regras Obrigatórias</summary>
>
> > 1. **Clean Code e Design Patterns:**
> >    - Funções < 50 linhas
> >    - Sem código duplicado (DRY)
> >    - Funções helper reutilizáveis em `Utils/`
> >    - Single Responsibility Principle
> >
> > 2. **Arquitetura:**
> >    - Seguir `ARCHITECTURE.md`
> >    - Data-Driven (usar Data Tables/Assets)
> >    - Multiplayer-Ready (replicação correta)
> >    - Editor-Friendly (funciona no editor)
> >
> > 3. **Padrões Unreal Engine:**
> >    - Prefixos corretos (`A`, `U`, `F`, `E`, `I`)
> >    - `UPROPERTY()` e `UFUNCTION()` apropriados
> >    - Replicação com `DOREPLIFETIME`
> >    - Validação de RPCs com `WithValidation`
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✅ Checklist Antes de Commitar</summary>
>
> > - [ ] Código segue Clean Code e Design Patterns?
> > - [ ] Funções helper estão em `Utils/`?
> > - [ ] Compila sem erros ou warnings?
> > - [ ] Segue padrões de nomenclatura?
> > - [ ] Está documentado?
> > - [ ] Testado no editor?
> > - [ ] Validação de integridade implementada (se aplicável)?
> > - [ ] Replicação configurada (se aplicável)?
>
> </details>
>
> ### 4. Commits
>
> Use [Conventional Commits](https://www.conventionalcommits.org/):
>
> ```bash
> # Formato: <type>(<scope>): <description>
> git commit -m "feat(Characters): add CharacterTotalLvl to Data Asset"
> git commit -m "fix(Components): fix CharacterDataComponent search when Owner is nullptr"
> git commit -m "refactor(Utils): move FindCharacterDataComponent to ComponentHelpers"
> ```
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📌 Tipos e Scopes</summary>
>
> > **Tipos:**
> > - `feat` - Nova funcionalidade
> > - `fix` - Correção de bug
> > - `refactor` - Refatoração
> > - `docs` - Documentação
> > - `style` - Formatação
> > - `test` - Testes
> > - `chore` - Manutenção
> >
> > **Scopes sugeridos:**
> > - `Characters` - Personagens e componentes relacionados
> > - `Components` - Componentes genéricos
> > - `Data` - Data Assets e Data Tables
> > - `Utils` - Utilitários e helpers
> > - `Gameplay` - Mecânicas de jogo
> > - `Architecture` - Mudanças arquiteturais
> > - `Docs` - Documentação
>
> </details>
>
> ### 5. Testar
>
> Antes de fazer push:
>
> ```bash
> # Compilar o projeto
> # No Cursor/VS Code: Ctrl+Shift+P → Tasks: Run Task → Build
>
> # Testar no editor
> # Abrir projeto no Unreal Editor
> # Verificar que não há erros
> # Testar funcionalidade básica
> ```
>
> ### 6. Push e Pull Request
>
> ```bash
> # Push para seu fork
> git push origin feat/nome-da-feature
>
> # Criar Pull Request no GitHub
> # Preencher template de PR
> # Adicionar descrição clara das mudanças
> # Referenciar issues relacionadas (se houver)
> ```

</details>

## Padrões de Código

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Convenções e Estrutura</b></summary>

> ### Estrutura de Arquivos
>
> ```
> Source/MyProject2/
> ├── Characters/
> │   ├── Data/
> │   │   ├── Handlers/      # Handlers para PostEditChangeProperty
> │   │   ├── Validators/    # Validações
> │   │   ├── Updaters/      # Atualizações de campos calculados
> │   │   ├── Helpers/       # Funções auxiliares
> │   │   └── GetOptions/    # Lógica de dropdowns
> │   └── Components/
> ├── CreateSheet/            # Motores de criação de personagem
> │   ├── Core/               # Core genérico e CharacterSheetData
> │   ├── RaceBonus/          # Motor de bônus raciais
> │   └── PointBuy/           # Motor de Point Buy
> ├── Utils/                  # Helpers reutilizáveis
> └── ...
> ```
>
> ### Nomenclatura
>
> - **Classes:** Prefixos Unreal (`A`, `U`, `F`, `E`, `I`)
> - **Variáveis:** PascalCase (booleanos com `b` prefix)
> - **Funções:** PascalCase
> - **Constantes:** `const` + PascalCase
>
> ### Helpers e Utilitários
>
> **REGRA CRÍTICA:** Funções helper reutilizáveis DEVEM estar em `Utils/`:
>
> ```cpp
> // ✅ CORRETO
> #include "../../Utils/ComponentHelpers.h"
> UCharacterDataComponent* Component = ComponentHelpers::FindCharacterDataComponent(Owner);
>
> // ❌ ERRADO - função privada acoplada
> private:
>     UCharacterDataComponent* FindOrGetCharacterDataComponent();
> ```
>
> ### Arquitetura CreateSheet/
>
> **Ao criar novos motores de criação de personagem:**
>
> - ✅ **Seguir padrão de motores desacoplados:** Cada motor deve ser independente e não conhecer outros motores
> - ✅ **Usar `FCharacterSheetData`:** Estrutura genérica que permite reutilização em diferentes contextos
> - ✅ **Funções estáticas:** Motores devem ter métodos estáticos para facilitar testes
> - ✅ **Helpers puros:** Lógica de cálculo deve estar em helpers puros (sem side effects)
> - ✅ **Orquestração via Core:** `FCharacterSheetCore` é responsável por resetar e orquestrar motores
>
> **Exemplo de novo motor:**
>
> ```cpp
> // CreateSheet/LevelUp/LevelUpMotor.h
> class MYPROJECT2_API FLevelUpMotor
> {
> public:
>     static void ApplyLevelUpBonuses(FCharacterSheetData &Data);
> };
> ```
>
> **Referências:**
> - `FRaceBonusMotor` - Exemplo de motor de bônus
> - `FPointBuyMotor` - Exemplo de motor com validação e ajuste automático
> - `FCharacterSheetCore` - Orquestrador que coordena todos os motores
>
> ### Documentação
>
> - Documente funções públicas
> - Explique "por quê", não apenas "o quê"
> - Adicione comentários em código complexo
> - Atualize `ARCHITECTURE.md` se houver mudanças arquiteturais

</details>

## Processo de Revisão

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👀 Como Funciona a Revisão</b></summary>

> 1. **Revisão de Código:**
>    - Verificar se segue Clean Code
>    - Verificar se segue arquitetura
>    - Verificar se compila
>    - Verificar se está testado
>
> 2. **Feedback:**
>    - Feedback será fornecido via comentários no PR
>    - Resolva comentários antes de merge
>    - Faça perguntas se algo não estiver claro
>
> 3. **Aprovação:**
>    - PR precisa de aprovação antes de merge
>    - Mantenedores revisarão o código

</details>

## Reportar Bugs

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🐛 Como Reportar Problemas</b></summary>

> Use o template de issue do GitHub:
>
> 1. **Descrição:** O que aconteceu?
> 2. **Reprodução:** Passos para reproduzir
> 3. **Comportamento esperado:** O que deveria acontecer?
> 4. **Comportamento atual:** O que está acontecendo?
> 5. **Logs:** Logs relevantes (se houver)
> 6. **Ambiente:** Unreal Engine version, plataforma, etc.

</details>

## Sugerir Features

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Como Sugerir Novas Funcionalidades</b></summary>

> 1. Abra uma issue no GitHub
> 2. Use o template "Feature Request"
> 3. Descreva a feature proposta
> 4. Explique o caso de uso
> 5. Discuta implementação (se tiver ideias)

</details>

## Links Úteis

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação e Recursos</b></summary>

> Links úteis para contribuidores:
>
> - [ARCHITECTURE.md](ARCHITECTURE.md) - Arquitetura do projeto
> - [README.md](README.md) - Visão geral do projeto
> - [.cursor/rules/](.cursor/rules/) - Regras de código
> - [API.md](docs/API.md) - Referência da API
> - [getting-started.md](docs/GUIDES/getting-started.md) - Guia de início

</details>

## Dúvidas?

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>❓ Precisa de Ajuda?</b></summary>

> Se tiver dúvidas sobre como contribuir:
>
> 1. Verifique a documentação primeiro
> 2. Abra uma issue para discussão
> 3. Entre em contato com os mantenedores

</details>

---

**Obrigado por contribuir!** 🎉
