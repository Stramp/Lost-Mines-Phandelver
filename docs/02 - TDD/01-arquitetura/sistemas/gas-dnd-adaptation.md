# Adaptação D&D 5e para Unreal Engine 5 com GAS - Overview

> **Documento de Design:** Explica como adaptar as regras de D&D 5e para um jogo Action RPG no Unreal Engine 5 usando Gameplay Ability System (GAS).

**⚠️ Status do Projeto:**

**✅ Implementado Atualmente:**
- Sistema de fichas completo: `UCharacterSheetDataAsset`, `UCharacterSheetComponent`, `UCharacterDataComponent`
- Replicação multiplayer: `DOREPLIFETIME` em `UCharacterDataComponent` (13 propriedades replicáveis)
- Motores desacoplados: `FMulticlassMotor`, `FPointBuyMotor`, `FRaceBonusMotor`, `FCharacterSheetCore`
- Arquitetura em 4 camadas: Data Assets → Bridge Components → Runtime Data Components → Feature Components
- Sistema de cálculo: `FinalScore = BASE_ABILITY_SCORE (8) + RacialBonuses + PointBuyAllocation` (ordem de aplicação)
- Testes completos: 100% cobertura de testes para todos os motores críticos (TDD)

**🔮 Planejado (Futuro):**
- Migração para GAS (Gameplay Ability System) - este documento explica como será implementado
- Feature Components (Fase 5): `USpellcastingComponent`, `USecondWindComponent`, `UActionSurgeComponent`
- Motor de escolhas: `FChoiceMotor` (🔮 Planejado - escolhas atualmente gerenciadas por handlers/validators)

---

## 📖 Documentação Completa

Este documento foi dividido em seções menores para melhor navegação. Consulte a documentação completa em:

**[📁 gas-dnd-adaptation/](gas-dnd-adaptation/index.md)** - Documentação completa dividida em seções:

1. **[Visão Geral](gas-dnd-adaptation/visao-geral.md)** - RPG de Mesa vs Jogo Digital
2. **[Conceitos Fundamentais](gas-dnd-adaptation/conceitos-fundamentais.md)** - Os 3 Pilares do GAS
3. **[Fluxos Práticos](gas-dnd-adaptation/fluxos-praticos.md)** - Exemplos do RPG de Mesa para o Jogo
4. **[Adaptação de Regras](gas-dnd-adaptation/adaptacao-regras.md)** - Como adaptar regras D&D 5e
5. **[Action RPG Combate](gas-dnd-adaptation/action-rpg-combate.md)** - Colisão Real e Combate
6. **[Condições e Efeitos](gas-dnd-adaptation/condicoes-efeitos.md)** - Sistema de Condições D&D 5e
7. **[Magias e Habilidades](gas-dnd-adaptation/magias-habilidades.md)** - Spellcasting e Habilidades de Classe
8. **[Multiplayer](gas-dnd-adaptation/multiplayer.md)** - Sincronização e Autoridade

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Úteis</b></summary>

> ### **D&D 5e:**
>
> - [D&D Beyond Basic Rules](https://www.dndbeyond.com/sources/dnd/br-2024) - Regras oficiais de D&D 5e
> - [D&D 5e SRD](https://dnd.wizards.com/resources/systems-reference-document) - System Reference Document

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎮 Unreal Engine GAS</summary>

> - [GAS Documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine) - Documentação oficial do GAS
> - [GAS Community Wiki](https://github.com/tranek/GASDocumentation) - Documentação da comunidade

</details>

---

## ✅ Resumo: Do RPG de Mesa para o Jogo

> **🎯 Resultado Final:**
>
> Um jogo Action RPG multiplayer que mantém todas as regras de D&D 5e, executa tudo automaticamente em tempo real com colisão física real, e garante sincronização perfeita entre todos os jogadores.
>
> **📌 Nota Importante:**
>
> Este documento descreve a **arquitetura futura** usando GAS. O projeto atual usa:
>
> - ✅ `UCharacterDataComponent` com replicação (`DOREPLIFETIME`) para dados em runtime
> - 13 propriedades replicáveis: CharacterName, CharacterDescription, CharacterTotalLvl, SelectedRace, SelectedSubrace, SelectedBackground, Proficiencies, AvailableFeatures, SelectedFeat, SelectedSkill, CustomAbilityScoreChoices, RaceTraits, Languages
> - `AbilityScores` (TMap) não é replicável diretamente (limitação do Unreal Engine)
> - ✅ `UCharacterSheetComponent` como bridge component para aplicar regras
> - ✅ `UCharacterSheetDataAsset` para configuração no editor
> - 🔮 Migração futura para GAS manterá a mesma arquitetura de camadas, mas usando `AttributeSet`, `GameplayEffect` e `GameplayAbility`

---

**Navegação:** [← Voltar para Sistemas](index.md) | [→ Documentação Completa](gas-dnd-adaptation/index.md)

**Última atualização:** 2024-12-27
