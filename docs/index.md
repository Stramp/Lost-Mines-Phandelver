# Documentação do Projeto - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Organização da Documentação</b></summary>

> Esta documentação segue uma estrutura hierárquica tipo **iceberg**, com explicações resumidas na superfície que linkam para documentos mais profundos e detalhados.
>
> **Níveis de Profundidade:**
>
> - **Nível 1 (Superfície):** Visão geral e resumos - `README.md` e `ARCHITECTURE.md` na raiz
> - **Nível 2 (Intermediário):** Documentos organizados por categoria - `docs/design/` e `docs/technical/`
> - **Nível 3 (Profundo):** Documentos específicos e detalhados - arquivos individuais dentro de cada categoria
> - **Nível 4+ (Muito Profundo):** Seções específicas dentro de documentos, exemplos de código, referências técnicas
>
> **Separação de Responsabilidades:**
>
> - **Design:** Regras de jogo, mecânicas D&D 5e, visão do produto final
> - **Técnico:** Arquitetura, API, implementação, guias de desenvolvimento
> - **Planejamento:** Roadmap completo, fases de desenvolvimento, decisões arquiteturais

</details>

---

## 📖 Estrutura de Documentação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎨 Design (docs/design/)</b></summary>

> Documentação relacionada ao design do jogo, regras D&D 5e e visão do produto final.
>
> **Documentos Principais:**
>
> - **[Game Design Document (GDD)](design/gdd.md)** - Visão completa do jogo final, objetivos, mecânicas principais
> - **[Adaptação D&D 5e + GAS](design/gas-dnd-adaptation.md)** - Como adaptar D&D 5e para Unreal Engine 5 com GAS
> - **[Regras D&D 5e](design/dnd-rules/)** - Documentação algorítmica das regras do D&D 5ª edição
>
> **📖 Para mais detalhes, veja [design/index.md](design/index.md)**

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Técnico (docs/technical/)</b></summary>

> Documentação relacionada à arquitetura técnica, implementação e desenvolvimento.
>
> **Documentos Principais:**
>
> - **[Arquitetura Técnica](technical/architecture.md)** - Arquitetura completa do projeto, princípios, camadas, motores
> - **[API Reference](technical/api.md)** - Referência completa da API das classes principais
> - **[Guias Práticos](technical/guides/)** - Guias passo a passo para desenvolvimento
>
> **📖 Para mais detalhes, veja [technical/index.md](technical/index.md)**

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Planejamento (docs/planning/)</b></summary>

> Documentação relacionada ao planejamento e roadmap do projeto.
>
> **Documentos Principais:**
>
> - **[Roadmap Completo](planning/roadmap.md)** - Roadmap completo e detalhado com todas as fases, prazos, dependências e decisões arquiteturais
>
> **📖 Para mais detalhes, veja [planning/index.md](planning/index.md)**

</details>

---

## 🗺️ Navegação Rápida

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚀 Por Onde Começar?</b></summary>

> **Novo no Projeto?**
>
> 1. Leia o **[README.md](../README.md)** na raiz do projeto (visão geral)
> 2. Leia o **[GDD](design/gdd.md)** para entender o jogo final
> 3. Leia a **[Arquitetura Técnica](technical/architecture.md)** para entender a estrutura
> 4. Siga o **[Guia de Início Rápido](technical/guides/getting-started.md)** para criar seu primeiro personagem
>
> **Quer Implementar uma Feature?**
>
> 1. Consulte as **[Regras D&D 5e](design/dnd-rules/)** para entender a mecânica
> 2. Veja a **[Arquitetura Técnica](technical/architecture.md)** para entender como implementar
> 3. Consulte a **[API Reference](technical/api.md)** para ver classes disponíveis
> 4. Siga os **[Guias Práticos](technical/guides/)** para exemplos
>
> **Problemas?**
>
> 1. Consulte o **[Troubleshooting](technical/guides/troubleshooting.md)**
> 2. Verifique a **[Arquitetura Técnica](technical/architecture.md)** para padrões
> 3. Veja os **[Guias Práticos](technical/guides/)** para exemplos

</details>

---

## 📋 Convenções de Documentação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 Padrões e Estilo</b></summary>

> **Organização:**
>
> - ✅ Todos os documentos seguem `.cursor/rules/markdown-organization.mdc`
> - ✅ Uso de colapsos (`<details>`) para hierarquia visual
> - ✅ Emojis descritivos nos títulos
> - ✅ Blocos de citação (`>`) para indentação visual
>
> **Níveis de Detalhamento:**
>
> - **Nível 1:** Resumos e visões gerais (README, ARCHITECTURE na raiz)
> - **Nível 2:** Documentos categorizados (design/, technical/)
> - **Nível 3:** Documentos específicos (gdd.md, architecture.md, etc.)
> - **Nível 4+:** Seções dentro de documentos, exemplos de código
>
> **Links e Referências:**
>
> - Sempre use links relativos para navegação
> - Documentos principais linkam para documentos relacionados
> - Cada pasta tem um `index.md` explicando seu conteúdo

</details>

---

## 🔄 Atualizações

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📅 Histórico de Reorganização</b></summary>

> **Última Atualização:** 2024-12-XX
>
> - ✅ Estrutura hierárquica tipo iceberg implementada
> - ✅ Separação clara entre design e técnico
> - ✅ GDD criado com visão do jogo final
> - ✅ Regras D&D 5e integradas em `docs/design/dnd-rules/`
> - ✅ Arquitetura técnica movida para `docs/technical/`
> - ✅ README e ARCHITECTURE na raiz atualizados (resumidos)
> - ✅ Documentação atualizada seguindo padrões de markdown-organization.mdc
> - ✅ **275+ testes automatizados implementados** (Unit + Integration)
>   - Testes Unitários: 271+ testes (CalculationHelpers, ValidationHelpers, CharacterSheetHelpers, DataTableHelpers, FormattingHelpers, ChoiceHelpers, FeatDataTable, ComponentHelpers, MulticlassHelpers, MulticlassMotor, CharacterSheetDataAssetLoaders, CharacterSheetDataAssetValidators, ProficiencyHelpers, ProficiencyDataTable, CharacterCreation Steps)
>   - Testes de Integração: 4+ testes (CharacterCreationE2E, CompleteCharacterCreationE2E)
> - ✅ Documentação de testes atualizada com todos os testes implementados
> - ✅ Guias de setup completos criados (setup.md, data-tables-setup.md)
> - ✅ Guia de workflows principais criado (workflows.md)
> - ✅ Sistema de logging com throttle implementado (LogWarningWithThrottledPopup, LogErrorWithThrottledPopup)
> - ✅ GetOptions filtrado por feature implementado (GetAvailableChoiceNamesForFeature)

</details>
