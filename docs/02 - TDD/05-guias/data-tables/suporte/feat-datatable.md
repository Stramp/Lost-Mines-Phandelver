# FeatDataTable

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⭐ FeatDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/FeatDataTable.h`
>
> **Struct:** `FFeatDataRow`

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `FeatName` | `FName` | Nome do feat (ex: "Alert", "Magic Initiate", "War Caster") |
> | `Description` | `FText` | Descrição textual do feat |
> | `Prerequisites` | `TArray<FName>` | Pré-requisitos para adquirir o feat |
> | `Benefits` | `TMap<FName, FString>` | Benefícios estruturados (dados programáticos) |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplos de JSON</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Alert</summary>
>
> > ```json
> > {
> >   "Name": "Alert",
> >   "FeatName": "Alert",
> >   "Description": "Always on the lookout for danger, you gain the following benefits.",
> >   "Prerequisites": [],
> >   "Benefits": {
> >     "InitiativeBonus": "5",
> >     "CannotBeSurprised": "true"
> >   }
> > }
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">War Caster (com pré-requisitos)</summary>
>
> > ```json
> > {
> >   "Name": "War Caster",
> >   "FeatName": "War Caster",
> >   "Description": "You have practiced casting spells in the midst of combat.",
> >   "Prerequisites": ["Ability to cast at least one spell"],
> >   "Benefits": {
> >     "AdvantageOnConcentration": "true",
> >     "CanCastSpellAsOpportunityAttack": "true"
> >   }
> > }
> > ```
>
> </details>

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

**Navegação:** [← Índice](../index.md) | [→ FeatureDataTable](feature-datatable.md)

**Última atualização:** 2024-12-27
