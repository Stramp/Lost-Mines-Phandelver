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
> Nenhuma mudança pendente no momento.

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
> > - Sistema de validação de integridade de dados (`ValidateDataIntegrity()`) em `CharacterDataComponent`
> > - Suporte completo para Variant Human (atributos customizados, feat e skill)
> > - Organização modular do `CharacterSheetDataAsset`:
> >   - `Handlers/` - Processamento de mudanças de propriedades
> >   - `Validators/` - Validação de dados
> >   - `Updaters/` - Atualização de campos calculados
> >   - `Helpers/` - Funções auxiliares reutilizáveis
> >   - `GetOptions/` - Lógica para dropdowns no editor
> > - Padrão Map/Table-Driven com ponteiros de função estáticos para handlers
> > - Sistema de logging completo da ficha do personagem (`LogCharacterSheet()`)
> > - Documentação completa:
> >   - `docs/API.md` - Referência completa da API
> >   - `docs/GUIDES/getting-started.md` - Guia prático passo a passo
> >   - `docs/GUIDES/data-tables.md` - Documentação dos Data Tables
> >   - `docs/GUIDES/troubleshooting.md` - Problemas comuns e soluções
> >   - `CHANGELOG.md` - Histórico de mudanças
> >   - `CONTRIBUTING.md` - Guia para contribuidores
> > - `CharacterSheetHelpers` para operações com Data Tables D&D 5e
> > - `FeatDataTable` para feats gerais D&D 5e
> > - Expansão de `ClassDataTable` com `FeatureType` e `SubclassNames`
> > - Funções `GetOptions` para dropdowns no editor (raças, classes, backgrounds, feats, skills)
> > - Visibilidade condicional de categorias baseada em seleção de Data Tables
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Changed</summary>
>
> > Mudanças em Funcionalidades Existentes
> >
> > - Refatoração completa do `PostEditChangeProperty`:
> >   - Implementado padrão Map/Table-Driven com lookup table
> >   - Substituído `std::function` por ponteiros de função estáticos (mais seguro)
> >   - Handlers agora chamam apenas funções necessárias (não mais `ValidateAndUpdate` completo)
> > - Movida lógica de `GetOptions` para módulo separado (`FCharacterSheetDataAssetGetOptions`)
> > - Movidas funções wrapper de handlers para módulo `Handlers`
> > - Simplificado construtor de `CharacterSheetDataAsset`:
> >   - Removidas inicializações redundantes de `PointsRemaining` e `TotalLevel`
> >   - Extraída inicialização de `AbilityScores` para helper
> > - Melhorada organização de código com separação de responsabilidades
> > - `CharacterSheetDataAssetTypes.h` criado para evitar dependências circulares
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🐛 Fixed</summary>
>
> > Correções de Bugs
> >
> > - **Editor crash ao selecionar raça:**
> >   - Resolvido com implementação de `PostLoad()` para inicializar `PropertyHandlers`
> >   - Substituído `std::function` por ponteiros de função estáticos (resolve problemas de lifetime)
> > - **Recursão infinita em `PostEditChangeProperty`:**
> >   - Resolvido com flag `bIsValidatingProperties` para evitar re-disparo de handlers
> >   - Handlers agora gerenciam a flag corretamente
> > - **Validação de sub-raças:**
> >   - Agora valida corretamente se sub-raça pertence à raça selecionada
> >   - Reset automático de sub-raça quando raça muda
> > - **Filtro de raças base:**
> >   - Agora filtra corretamente sub-raças do dropdown de raças
> >   - Apenas raças base aparecem no dropdown principal
> > - **Proteção de modificações de propriedades:**
> >   - Adicionado `Modify()` antes de modificar propriedades em `UpdateCalculatedFields`
> >   - Evita validação redundante ao resetar sub-raça
> > - **Correção de múltiplos bugs críticos:**
> >   - Correção de range de validação de ability scores em criação de personagem
> >   - Correção de tabela de custos Point Buy para corresponder às regras oficiais D&D 5e
> > - **Remoção de replicação desnecessária:**
> >   - Removida replicação de `TMap` de `CharacterDataComponent` (não suportado nativamente)
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
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Funcionalidades Iniciais
> >
> > - Sistema básico de fichas de personagem D&D 5e
> > - `UCharacterSheetDataAsset` - Data Asset para configuração no editor
> > - `UCharacterDataComponent` - Componente de dados replicáveis em runtime
> > - `UCharacterSheetComponent` - Bridge component para inicialização
> > - Suporte para Point Buy system (27 pontos, scores 8-15)
> > - Suporte para multi-classing (múltiplas classes, nível total máximo 20)
> > - Data Tables para raças, classes, backgrounds e feats
> > - Sistema de proficiências (raça + classe + background)
> > - Bônus raciais automáticos nos ability scores
> > - Validação automática no editor (`PostEditChangeProperty`)
> > - Replicação completa para multiplayer (`DOREPLIFETIME`)
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
