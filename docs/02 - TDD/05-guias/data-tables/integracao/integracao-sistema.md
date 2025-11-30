# Integração com Sistema - Data Tables

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Como Criar/Editar Data Tables no Editor</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1. Criar Data Table</summary>
>
> > 1. No Content Browser, navegue até a pasta desejada
> > 2. Clique com botão direito → **Miscellaneous** → **Data Table**
> > 3. Selecione o struct apropriado:
> >    - `Race Data Row` para raças
> >    - `Class Data Row` para classes
> >    - `Background Data Row` para backgrounds
> >    - `Feat Data Row` para feats
> >    - `Feature Data Row` para features
> >    - `Proficiency Data Row` para proficiências
> >    - `Skill Data Row` para skills
> >    - `Language Data Row` para idiomas
> >    - `Spell Data Row` para magias
> >    - `Spell School Data Row` para escolas de magia
> >    - `Damage Type Data Row` para tipos de dano
> >    - `Condition Data Row` para condições
> >    - `Ability Score Data Row` para atributos
> >    - `Trait Data Row` para traits
> >    - `Item Data Row` para itens
> > 4. Nomeie o Data Table (ex: `DT_Races`, `DT_Classes`, `DT_Features`)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">2. Importar JSON</summary>
>
> > 1. Selecione o Data Table criado
> > 2. No Details Panel, clique em **Import**
> > 3. Selecione o arquivo JSON
> > 4. O sistema importará automaticamente os dados
> >
> > **Formato JSON esperado:**
> > - Array de objetos
> > - Cada objeto representa uma linha
> > - Campo `Name` é usado como Row Name no Data Table
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">3. Editar Manualmente</summary>
>
> > 1. Selecione o Data Table
> > 2. No Details Panel, clique em **Add Row** para adicionar nova entrada
> > 3. Preencha os campos conforme necessário
> > 4. Use **Remove Row** para remover entradas
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Validações Aplicadas</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">RaceDataTable</summary>
>
> > - **Custom ASI:** Variant Human com `AbilityName = "Custom"` é tratado especialmente
> > - **Traits:** Traits `FeatChoice` e `SkillChoice` habilitam escolhas do jogador
> > - **Bônus Raciais:** Calculados automaticamente por `FRaceBonusMotor` que processa bônus de raça base, sub-raça e Variant Human
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">ClassDataTable</summary>
>
> > - **Features por nível:** Sistema coleta features baseado no nível do personagem
> > - **Subclasses:** Sistema valida que subclasse pertence à classe selecionada
> > - **Proficiências:** Sistema agrega proficiências de todas as classes do personagem
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">BackgroundDataTable</summary>
>
> > - **Proficiências:** Sistema agrega skill proficiencies ao personagem
> > - **Features:** Features de background são adicionadas automaticamente
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FeatDataTable</summary>
>
> > - **Pré-requisitos:** Sistema valida pré-requisitos antes de permitir seleção
> > - **Disponibilidade:** Apenas feats sem pré-requisitos de nível aparecem no nível 1
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Point Buy System</summary>
>
> > - **Validação:** Point Buy é validado por `FPointBuyValidator` que verifica se não excede 27 pontos e se todos os scores estão no range [8, 15]
> > - **Aplicação:** Point Buy é aplicado por `FPointBuyMotor` que ajusta automaticamente se exceder 27 pontos
> > - **Cálculo Final:** Ability scores finais são calculados via `FCharacterSheetCore` que orquestra `FRaceBonusMotor` e `FPointBuyMotor` sequencialmente
>
> </details>

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

**Navegação:** [← Índice](../index.md) | [→ Exemplos](../exemplos/exemplos-json.md)

**Última atualização:** 2024-12-27
