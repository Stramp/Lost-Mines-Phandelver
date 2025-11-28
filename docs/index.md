---
title: "Documentação do Projeto"
category: root
tags: [documentation, index, overview]
last_updated: 2024-12-27
---

# Documentação do Projeto

!!! abstract "Bem-vindo à Documentação do MyProject2"
    Esta documentação segue uma estrutura hierárquica tipo **iceberg**, com explicações resumidas na superfície que linkam para documentos mais profundos e detalhados.

    **Níveis de Profundidade:**

    - **Nível 1 (Superfície):** Visão geral e resumos - `README.md` e `ARCHITECTURE.md` na raiz
    - **Nível 2 (Intermediário):** Documentos organizados por categoria - `docs/design/` e `docs/technical/`
    - **Nível 3 (Profundo):** Documentos específicos e detalhados - arquivos individuais dentro de cada categoria
    - **Nível 4+ (Muito Profundo):** Seções específicas dentro de documentos, exemplos de código, referências técnicas

    **Separação de Responsabilidades:**

    - **Design:** Regras de jogo, mecânicas D&D 5e, visão do produto final
    - **Técnico:** Arquitetura, API, implementação, guias de desenvolvimento
    - **Planejamento:** Roadmap completo, fases de desenvolvimento, decisões arquiteturais

---

## Estrutura de Documentação

=== "🎨 Design"

    **Documentação relacionada ao design do jogo, regras D&D 5e e visão do produto final.**

    **Documentos Principais:**

    - [:material-file-document: Game Design Document (GDD)](design/gdd.md) - Visão completa do jogo final, objetivos, mecânicas principais
    - [:material-auto-fix: Adaptação D&D 5e + GAS](design/gas-dnd-adaptation.md) - Como adaptar D&D 5e para Unreal Engine 5 com GAS
    - [:material-dice-multiple: Regras D&D 5e](design/dnd-rules/) - Documentação algorítmica das regras do D&D 5ª edição

    [:octicons-arrow-right-24: Ver documentação de design completa](design/index.md)

=== "🔧 Técnico"

    **Documentação relacionada à arquitetura técnica, implementação e desenvolvimento.**

    **Documentos Principais:**

    - [:material-architecture: Arquitetura Técnica](technical/architecture.md) - Arquitetura completa do projeto, princípios, camadas, motores, Data-Oriented Design e ECS
    - [:material-api: API Reference](technical/api.md) - Referência completa da API das classes principais
    - [:material-database: Arquitetura de Dados](technical/data-architecture/) - Organização de dados, DOD, ECS, estrutura ideal (estilo Baldur's Gate 3)
    - [:material-book-open-variant: Guias Práticos](technical/guides/) - Guias passo a passo para desenvolvimento

    [:octicons-arrow-right-24: Ver documentação técnica completa](technical/index.md)

=== "📋 Planejamento"

    **Documentação relacionada ao planejamento e roadmap do projeto.**

    **Documentos Principais:**

    - [:material-calendar: Roadmap Completo](planning/roadmap.md) - Roadmap completo e detalhado com todas as fases, prazos, dependências e decisões arquiteturais

    [:octicons-arrow-right-24: Ver documentação de planejamento completa](planning/index.md)

---

## Navegação Rápida

!!! tip "Por Onde Começar?"
    **Novo no Projeto?**

    1. Leia o [:material-home: README.md](../README.md) na raiz do projeto (visão geral)
    2. Leia o [:material-file-document: GDD](design/gdd.md) para entender o jogo final
    3. Leia a [:material-architecture: Arquitetura Técnica](technical/architecture.md) para entender a estrutura
    4. Siga o [:material-rocket-launch: Guia de Início Rápido](technical/guides/getting-started.md) para criar seu primeiro personagem

    **Quer Implementar uma Feature?**

    1. Consulte as [:material-dice-multiple: Regras D&D 5e](design/dnd-rules/) para entender a mecânica
    2. Veja a [:material-architecture: Arquitetura Técnica](technical/architecture.md) para entender como implementar
    3. Consulte a [:material-api: API Reference](technical/api.md) para ver classes disponíveis
    4. Siga os [:material-book-open-variant: Guias Práticos](technical/guides/) para exemplos

    **Problemas?**

    1. Consulte o [:material-bug: Troubleshooting](technical/guides/troubleshooting.md)
    2. Verifique a [:material-architecture: Arquitetura Técnica](technical/architecture.md) para padrões
    3. Veja os [:material-book-open-variant: Guias Práticos](technical/guides/) para exemplos

---

## Convenções de Documentação

!!! info "Padrões e Estilo"
    **Organização:**

    - ✅ Todos os documentos seguem `.cursor/rules/markdown-organization.mdc`
    - ✅ Uso de Admonitions do Material for MkDocs para hierarquia visual
    - ✅ Emojis descritivos nos títulos
    - ✅ Ícones Material Design para melhor visualização

    **Níveis de Detalhamento:**

    - **Nível 1:** Resumos e visões gerais (README, ARCHITECTURE na raiz)
    - **Nível 2:** Documentos categorizados (design/, technical/)
    - **Nível 3:** Documentos específicos (gdd.md, architecture.md, etc.)
    - **Nível 4+:** Seções dentro de documentos, exemplos de código

    **Links e Referências:**

    - Sempre use links relativos para navegação
    - Documentos principais linkam para documentos relacionados
    - Cada pasta tem um `index.md` explicando seu conteúdo

---

## Atualizações Recentes

!!! success "Histórico de Reorganização"
    **Última Atualização:** 2024-12-27

    - ✅ Estrutura hierárquica tipo iceberg implementada
    - ✅ Separação clara entre design e técnico
    - ✅ GDD criado com visão do jogo final
    - ✅ Regras D&D 5e integradas em `docs/design/dnd-rules/`
    - ✅ Arquitetura técnica movida para `docs/technical/`
    - ✅ README e ARCHITECTURE na raiz atualizados (resumidos)
    - ✅ Documentação atualizada seguindo padrões de markdown-organization.mdc
    - ✅ **275+ testes automatizados implementados** (Unit + Integration)
    - ✅ Documentação de testes atualizada com todos os testes implementados
    - ✅ Guias de setup completos criados (setup.md, data-tables-setup.md)
    - ✅ Guia de workflows principais criado (workflows.md)
    - ✅ Sistema de logging com throttle implementado
    - ✅ GetOptions filtrado por feature implementado
    - ✅ **Padronização Name + ID completa** - Todas as 15 Data Tables seguem padrão consistente
    - ✅ **Documentação de arquitetura de dados atualizada** - Reflete estrutura atual
    - ✅ **Material for MkDocs implementado** - Documentação moderna e profissional
