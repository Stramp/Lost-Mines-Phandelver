# Changelog

Todas as mudanças notáveis neste projeto serão documentadas neste arquivo.

O formato é baseado em [Keep a Changelog](https://keepachangelog.com/pt-BR/1.0.0/),
e este projeto adere ao [Semantic Versioning](https://semver.org/lang/pt-BR/).

<details open>
<summary>📋 Versões</summary>

- **[Unreleased](#unreleased)** - Mudanças em desenvolvimento
- **[0.2.0](#020---2024-12-xx)** - Refatoração modular e validação de integridade
- **[0.1.0](#010---2024-12-xx)** - Sistema básico de fichas de personagem

</details>

---

## Versões

<details>

<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>[Unreleased]</b></summary>

> 🔄 Mudanças em desenvolvimento
>
> Mudanças pendentes de release.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Novas Funcionalidades
> >
> > 1. Commit [`3c8c31c`] - Implementar sistema completo de raça e background com escolhas de idiomas
> >    - Corrigido `GetAllRaceNames()` para mostrar todas as raças base (Dragonborn, Half-Elf, Half-Orc, Tiefling)
> >    - Adicionada flag `bHasSubraces` para ocultar campo de sub-raça quando raça não tem sub-raças
> >    - Implementado `UpdateSubraceFlag()` seguindo padrão de `bIsVariantHuman`
> >    - Adicionado sistema de escolhas de idiomas com filtro automático
> >    - Filtro de idiomas disponíveis exclui idiomas já conhecidos automaticamente
> >    - Ajuste automático do array `SelectedLanguages` quando `MaxLanguageChoices` diminui
> >    - Adicionada propriedade `Languages` ao `CharacterDataComponent` (replicável)
> >    - Adicionada seção de idiomas no log da ficha (`LogCharacterSheet()`)
> >    - Todos os dados do personagem agora acessíveis em qualquer sistema/componente para GAS e replicação
> >
> > 2. Commit [`9a98032`] - Implementar sistema de escolhas de idiomas com filtro automático
> >    - Adicionado array `SelectedLanguages` com dropdown filtrado
> >    - Filtro exclui idiomas automáticos de raça/background
> >    - Adicionadas propriedades `MaxLanguageChoices` e `bHasLanguageChoices`
> >    - Implementado helper `GetAvailableLanguagesForChoice`
> >    - Adicionada validação e handlers para idiomas
> >    - Categoria "Language Choices" oculta quando não há escolhas disponíveis
> >
> > 3. Commit [`9fa0946`] - Implementar sistema de escolhas de idiomas
> >    - Refatorado `BackgroundDataTable` para separar idiomas automáticos de escolhas
> >    - Criado struct `FLanguageChoices` para escolhas de idiomas
> >    - Implementado `CalculateLanguages()` para compilar lista final de idiomas conhecidos
> >
> > 4. Commit [`f625bf6`] - Adicionar escolhas de Variant Human, race traits e melhorar log da ficha
> >    - Adicionado suporte para escolhas customizadas de Variant Human
> >    - Adicionado sistema de race traits
> >    - Melhorado sistema de logging da ficha do personagem
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Changed</summary>
>
> > Mudanças em Funcionalidades Existentes
> >
> > 1. Commit [`6c500f5`] - Refatoração do ValidateVariantHumanChoices
> >    - Dividida em 3 funções separadas seguindo Clean Code (Validators)
> >    - Reorganização de categorias no editor do CharacterSheetDataAsset
> >
> > 2. Commit [`e14a162`] - Extração de helpers reutilizáveis para Utils/
> >    - Movidos helpers para `Utils/` seguindo Clean Code
> >    - Funções puras e testáveis isoladas
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🐛 Fixed</summary>
>
> > Correções de Bugs
> >
> > 1. Commit [`3c8c31c`] - Remoção de logs de DEBUG
> >    - Removidos todos os logs temporários de DEBUG de handlers, updaters e calculation helpers
> >    - Mantido `LogCharacterSheet()` intacto conforme solicitado
> >
> > 2. Commit [`e2b34ec`] - Correção do cálculo de bônus para Variant Human
> >    - Corrigido cálculo de bônus raciais para Variant Human
> >    - Ajuste em CalculationHelpers para aplicar escolhas customizadas apenas uma vez
> >
> > 3. Commit [`a9ef548`] - Correção de arrays hardcoded e centralização de helpers
> >    - Removidos arrays hardcoded
> >    - Centralizados helpers em Utils/
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📚 Docs</summary>
>
> > Documentação
> >
> > 1. Commit [`275db60`] - Atualização do roadmap no README
> >    - Adicionado roadmap detalhado com 10 fases do Action RPG
> >    - Incluída seção de NPCs e Monsters
> >
> > 2. Commit [`6737271`] - Adição de seção Skill Helpers e documentação completa de helpers
> >    - Adicionada seção Skill Helpers na documentação da API
> >    - Documentação completa de todas as funções helper
> >
> > 3. Commit [`271f1f9`] - Correção de line endings e formatação da API
> >    - Normalização de line endings (LF vs CRLF)
> >    - Correção de formatação na documentação da API
> >
> > 4. Commit [`6369309`] - Adição de hash de commit para atualização do changelog
> >    - Adicionado hash de commit para rastreabilidade
> >
> > 5. Commit [`5d47179`] - Adição de hash de commit para atualização do changelog
> >    - Adicionado hash de commit para rastreabilidade
> >
> > 6. Commit [`7b5040e`] - Adição de hashes de commits em todas as entradas do CHANGELOG
> >    - Adicionados hashes de commits para rastreabilidade completa
> >
> > 7. Commit [`cf8ec7d`] - Aplicação de padrão de organização Markdown em guias
> >    - Aplicado padrão markdown-organization.mdc em `docs/GUIDES/`
> >
> > 8. Commit [`4d11ca4`] - Aplicação de padrão de organização Markdown em ARCHITECTURE.md
> >    - Aplicado padrão markdown-organization.mdc com seções colapsáveis
> >
> > 9. Commit [`d4d8a80`] - Adição de regra de honestidade e perguntas para IA
> >    - Adicionada regra honesty-and-questions.mdc
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>[0.2.0] - 2024-12-XX</b></summary>

> ✨ Refatoração modular e validação de integridade
>
> Esta versão introduz uma refatoração completa da arquitetura do `CharacterSheetDataAsset` para uma organização modular, implementa validação de integridade de dados e adiciona suporte completo para Variant Human.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Novas Funcionalidades
> >
> > 1. Commit [`c90d893`] - Sistema de validação de integridade de dados
> >    - Implementado `ValidateDataIntegrity()` em `CharacterDataComponent`
> >    - Sistema de logging completo da ficha do personagem (`LogCharacterSheet()`)
> >
> > 2. Commit [`8460879`] - Suporte completo para Variant Human
> >    - Atributos customizados, feat e skill
> >    - Visibilidade condicional de categorias baseada em seleção de Data Tables
> >
> > 3. Commit [`1cd52b3`] - Organização modular do CharacterSheetDataAsset
> >    - `Handlers/` - Processamento de mudanças de propriedades
> >
> > 4. Commit [`8899eed`] - Organização modular do CharacterSheetDataAsset
> >    - `Validators/` - Validação de dados
> >    - `Updaters/` - Atualização de campos calculados
> >
> > 5. Commit [`e899bf8`] - Organização modular do CharacterSheetDataAsset
> >    - `Helpers/` - Funções auxiliares reutilizáveis
> >
> > 6. Commit [`c20b354`] - Organização modular do CharacterSheetDataAsset
> >    - `GetOptions/` - Lógica para dropdowns no editor
> >
> > 7. Commit [`503e553`] - Padrão Map/Table-Driven com ponteiros de função estáticos
> >    - Implementado padrão Map/Table-Driven para handlers
> >
> > 8. Commit [`cf8ec7d`] - Documentação completa
> >    - `docs/GUIDES/getting-started.md` - Guia prático passo a passo
> >    - `docs/GUIDES/data-tables.md` - Documentação dos Data Tables
> >    - `docs/GUIDES/troubleshooting.md` - Problemas comuns e soluções
> >
> > 9. Commit [`886ca0f`] - CharacterSheetHelpers para operações com Data Tables D&D 5e
> >
> > 10. Commit [`47198fe`] - FeatDataTable para feats gerais D&D 5e
> >
> > 11. Commit [`80d152e`] - Expansão de ClassDataTable
> >     - Adicionado `FeatureType` e `SubclassNames`
> >
> > 12. Commit [`b526ff9`, `30a5b7a`] - Funções GetOptions para dropdowns no editor
> >     - Dropdowns para raças, classes, backgrounds, feats, skills
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Changed</summary>
>
> > Mudanças em Funcionalidades Existentes
> >
> > 1. Commit [`503e553`] - Refatoração completa do PostEditChangeProperty
> >    - Implementado padrão Map/Table-Driven com lookup table
> >
> > 2. Commit [`b00fad8`] - Substituição de std::function por ponteiros de função estáticos
> >    - Mais seguro e eficiente
> >
> > 3. Commit [`d3d87b1`] - Otimização de handlers
> >    - Handlers agora chamam apenas funções necessárias (não mais `ValidateAndUpdate` completo)
> >
> > 4. Commit [`c20b354`] - Movida lógica de GetOptions para módulo separado
> >    - Criado `FCharacterSheetDataAssetGetOptions`
> >
> > 5. Commit [`1cd52b3`] - Movidas funções wrapper de handlers para módulo Handlers
> >
> > 6. Commit [`e899bf8`] - Simplificado construtor de CharacterSheetDataAsset
> >    - Removidas inicializações redundantes de `PointsRemaining` e `TotalLevel`
> >    - Extraída inicialização de `AbilityScores` para helper
> >
> > 7. Commit [`8899eed`] - Melhorada organização de código
> >    - Separação de responsabilidades
> >    - `CharacterSheetDataAssetTypes.h` criado para evitar dependências circulares
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🐛 Fixed</summary>
>
> > Correções de Bugs
> >
> > 1. Commit [`b00fad8`] - Correção de crash do editor ao selecionar raça
> >    - Resolvido com implementação de `PostLoad()` para inicializar `PropertyHandlers`
> >    - Substituído `std::function` por ponteiros de função estáticos (resolve problemas de lifetime)
> >
> > 2. Commit [`8899eed`] - Correção de recursão infinita em PostEditChangeProperty
> >    - Resolvido com flag `bIsValidatingProperties` para evitar re-disparo de handlers
> >    - Handlers agora gerenciam a flag corretamente
> >
> > 3. Commit [`30a5b7a`] - Correção de validação de sub-raças
> >    - Agora valida corretamente se sub-raça pertence à raça selecionada
> >    - Reset automático de sub-raça quando raça muda
> >    - Filtro de raças base corrigido (apenas raças base aparecem no dropdown principal)
> >
> > 4. Commit [`6b8621f`] - Proteção de modificações de propriedades
> >    - Adicionado `Modify()` antes de modificar propriedades em `UpdateCalculatedFields`
> >
> > 5. Commit [`ff5d537`] - Evita validação redundante ao resetar sub-raça
> >
> > 6. Commit [`22c1991`] - Correção de range de validação de ability scores
> >    - Correção de range de validação de ability scores em criação de personagem
> >
> > 7. Commit [`a3ce3e7`] - Correção de tabela de custos Point Buy
> >    - Correção de tabela de custos Point Buy para corresponder às regras oficiais D&D 5e
> >
> > 8. Commit [`b81bab2`] - Remoção de replicação desnecessária
> >    - Removida replicação de `TMap` de `CharacterDataComponent` (não suportado nativamente)
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>[0.1.0] - 2024-12-XX</b></summary>

> 🎯 Sistema básico de fichas de personagem
>
> Versão inicial do sistema de fichas de personagem D&D 5e com funcionalidades básicas.
>
> > **Nota:** Esta versão representa os commits iniciais do projeto que estabeleceram a arquitetura base e funcionalidades fundamentais.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Funcionalidades Iniciais
> >
> > 1. Sistema básico de fichas de personagem D&D 5e
> >    - `UCharacterSheetDataAsset` - Data Asset para configuração no editor
> >    - `UCharacterDataComponent` - Componente de dados replicáveis em runtime
> >    - `UCharacterSheetComponent` - Bridge component para inicialização
> >
> > 2. Suporte para Point Buy system
> >    - 27 pontos, scores 8-15
> >
> > 3. Suporte para multi-classing
> >    - Múltiplas classes, nível total máximo 20
> >
> > 4. Data Tables para raças, classes, backgrounds e feats
> >
> > 5. Sistema de proficiências
> >    - Proficiências de raça + classe + background
> >
> > 6. Bônus raciais automáticos nos ability scores
> >
> > 7. Validação automática no editor
> >    - `PostEditChangeProperty`
> >
> > 8. Replicação completa para multiplayer
> >    - `DOREPLIFETIME`
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🏗️ Architecture</summary>
>
> > Arquitetura Inicial
> >
> > - Arquitetura em 4 camadas:
> >   - **Camada 1:** Data Assets (Editor/Configuração)
> >   - **Camada 2:** Bridge Components (Aplicação de Regras)
> >   - **Camada 3:** Runtime Data Components (Dados Replicáveis)
> >   - **Camada 4:** Feature Components (Lógica Específica)
> > - Preparação para migração futura para GAS
> > - Data-Driven design (todas as regras vêm de Data Tables)
> > - Editor-Friendly (configuração completa no editor)
>
> </details>

</details>

---

<details>
<summary>📚 Tipos de Mudanças</summary>

- **Added** - Novas funcionalidades
- **Changed** - Mudanças em funcionalidades existentes
- **Deprecated** - Funcionalidades que serão removidas
- **Removed** - Funcionalidades removidas
- **Fixed** - Correções de bugs
- **Security** - Correções de segurança

</details>
