# Character Creation Steps - D&D 5e

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este documento define **duas ordens de criação de personagem**:
>
> 1. **Ordem Oficial D&D Beyond** - Para Widget/UI (jogador final)
> 2. **Ordem Técnica** - Para Data Asset (processamento interno)
>
> **Fonte:** [D&D Beyond - Step-By-Step Characters](https://www.dndbeyond.com/sources/dnd/basic-rules-2014/step-by-step-characters)

</details>

---

## 🎮 Ordem Oficial D&D Beyond (Widget/UI)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Passos para Jogador Final</b></summary>

> Esta é a ordem oficial do D&D Beyond, usada no **Widget de criação de personagem** para o jogador final.
>
> **Referência:** [D&D Beyond - Ch. 1: Step-By-Step Characters](https://www.dndbeyond.com/sources/dnd/basic-rules-2014/step-by-step-characters)
>
> 1. **Choose a Race** → Seleciona raça (unlocks subrace options)
> 2. **Choose a Class** → Seleciona classe (unlocks subclass options)
> 3. **Determine Ability Scores** → Point Buy, Standard Array, ou Roll
> 4. **Describe Your Character** → Background, Personality, Alignment, etc.
> 5. **Choose Equipment** → Starting equipment da classe e background
> 6. **Come Together** → Revisão final e preparação para jogo
> 7. **Beyond 1st Level** → Leveling up e progressão
>
> **Nota:** Esta ordem é para **experiência do usuário** no Widget. O sistema processa internamente usando a ordem técnica abaixo.

</details>

---

## 🔧 Ordem Técnica (Data Asset)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Processamento Interno</b></summary>

> Esta é a ordem de processamento interno usada no **CharacterSheetDataAsset**.
>
> **Uso:** Ordem técnica de processamento, não necessariamente a ordem que o usuário vê na UI.
>
> 1. **Choose Race** → unlocks Subrace options
> 2. **Choose Subrace** → adds bonuses
> 3. **Distribute Point Buy** → set base ability scores (8-15)
> 4. **Apply Racial Bonuses** → calculate final ability scores
> 5. **Choose Background** → adds skills, languages
> 6. **Choose Class** → unlocks Subclass options
> 7. **Choose Subclass** → adds features
> 8. **Calculate Features** → based on class levels
> 9. **Calculate Proficiencies** → from class + background
> 10. **Calculate HP** → based on class hit die + CON
>
> **Nota:** Esta ordem é otimizada para processamento técnico no Data Asset. O sistema sempre recalcula tudo corretamente independente da ordem de entrada.

</details>

---

## ✅ Validation Order

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔍 Ordem de Validação</b></summary>

> 1. Point Buy valid (27 points spent)
> 2. Subrace belongs to selected Race
> 3. Subclass belongs to selected Class
> 4. Total Level <= 20
> 5. All ability scores 8-17 (after bonuses, max 20 only with ASIs during level up)

</details>

---

## 📝 Notas Importantes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Diferenças entre as Ordens</b></summary>

> **Por que duas ordens?**
>
> - **Ordem Oficial (Widget):** Segue a experiência do jogador conforme D&D Beyond, mais intuitiva e familiar
> - **Ordem Técnica (Data Asset):** Otimizada para processamento interno, permite validações e cálculos mais eficientes
>
> **O sistema sempre funciona corretamente:**
>
> - O `RecalculateFinalScores()` sempre reseta e recalcula tudo, independente da ordem de entrada
> - Motores são independentes e podem ser aplicados em qualquer ordem
> - A ordem técnica é apenas uma otimização, não uma restrição
>
> **Quando usar cada ordem:**
>
> - **Widget/UI:** Use ordem oficial D&D Beyond (melhor UX)
> - **Data Asset:** Use ordem técnica (processamento otimizado)
> - **Testes:** Seguem ordem oficial D&D Beyond (consistência)

</details>

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentos Relacionados</b></summary>

> - **[Point Buy System](point-buy.md)** - Sistema de distribuição de pontos
> - **[Raças e Sub-raças](races.md)** - Seleção de raça
> - **[Multiclassing](multiclassing.md)** - Múltiplas classes
> - **[Guia Algorítmico Completo](../../technical/guides/algorithmic/character-creation.md)** - Algoritmos detalhados com Design Patterns
> - **[D&D Beyond - Step-By-Step Characters](https://www.dndbeyond.com/sources/dnd/basic-rules-2014/step-by-step-characters)** - Fonte oficial

</details>
