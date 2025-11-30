# Adaptação D&D 5e para GAS - Índice

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Índice criado após divisão de gas-dnd-adaptation.md |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> **Documento de Design:** Explica como adaptar as regras de D&D 5e para um jogo Action RPG no Unreal Engine 5 usando Gameplay Ability System (GAS).
>
> **⚠️ Status do Projeto:**
>
> **✅ Implementado Atualmente:**
> - Sistema de fichas completo: `UCharacterSheetDataAsset`, `UCharacterSheetComponent`, `UCharacterDataComponent`
> - Replicação multiplayer: `DOREPLIFETIME` em `UCharacterDataComponent` (13 propriedades replicáveis)
> - Motores desacoplados: `FMulticlassMotor`, `FPointBuyMotor`, `FRaceBonusMotor`, `FCharacterSheetCore`
> - Arquitetura em 4 camadas: Data Assets → Bridge Components → Runtime Data Components → Feature Components
>
> **🔮 Planejado (Futuro):**
> - Migração para GAS (Gameplay Ability System) - este documento explica como será implementado
> - Feature Components (Fase 5): `USpellcastingComponent`, `USecondWindComponent`, `UActionSurgeComponent`

</details>

---

## 📖 Documentação

- **[Visão Geral](visao-geral.md)** - RPG de Mesa vs Jogo Digital
- **[Conceitos Fundamentais](conceitos-fundamentais.md)** - Os 3 Pilares do GAS
- **[Fluxos Práticos](fluxos-praticos.md)** - Exemplos do RPG de Mesa para o Jogo
- **[Adaptação de Regras](adaptacao-regras.md)** - Como adaptar regras D&D 5e
- **[Action RPG Combate](action-rpg-combate.md)** - Colisão Real e Combate
- **[Condições e Efeitos](condicoes-efeitos.md)** - Sistema de Condições D&D 5e
- **[Magias e Habilidades](magias-habilidades.md)** - Spellcasting e Habilidades de Classe
- **[Multiplayer](multiplayer.md)** - Sincronização e Autoridade

---

**Navegação:** [← Voltar para Sistemas](../index.md) | [→ Visão Geral](visao-geral.md)

**Última atualização:** 2024-12-27
