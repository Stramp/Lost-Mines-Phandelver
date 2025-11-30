# FeatureDataTable

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ FeatureDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/FeatureDataTable.h`
>
> **Struct:** `FFeatureDataRow`

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome da feature (ex: "Second Wind", "Fighting Style") |
> | `ID` | `FName` | ID único da feature (ex: "FC_SecondWind", "FC_FightingStyle") |
> | `FeatureID` | `FName` | Alias de ID (mantido para compatibilidade) |
> | `Description` | `FText` | Descrição textual da feature (localizável) |
> | `LevelUnlocked` | `int32` | Nível em que a feature é desbloqueada |
> | `FeatureType` | `FName` | Tipo: "Automatic", "Choice", "SubclassSelection", "ASI", "FeatSelection" |
> | `FeatureData` | `TMap<FName, FString>` | Dados estruturados opcionais (ex: UsesPerRest, Type) |
> | `AvailableChoices` | `TArray<FFeatureChoice>` | Escolhas disponíveis para features do tipo "Choice" |
> | `bAllowMultipleChoices` | `bool` | Permite múltiplas escolhas (padrão: false) |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Tipos de Features</b></summary>

> - **"Automatic"**: Feature aplicada automaticamente (ex: Second Wind, Action Surge)
> - **"Choice"**: Jogador escolhe entre opções (ex: Fighting Style)
> - **"SubclassSelection"**: Jogador escolhe subclasse (ex: Martial Archetype)
> - **"ASI"**: Ability Score Improvement
> - **"FeatSelection"**: Jogador pode escolher um Feat ao invés de ASI

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplos de JSON</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Second Wind</summary>
>
> > ```json
> > {
> >   "Name": "Second Wind",
> >   "ID": "FC_SecondWind",
> >   "FeatureID": "FC_SecondWind",
> >   "Description": "You have a limited well of stamina that you can draw on to protect yourself from harm.",
> >   "LevelUnlocked": 1,
> >   "FeatureType": "Automatic",
> >   "FeatureData": {
> >     "UsesPerRest": "1",
> >     "Type": "BonusAction"
> >   },
> >   "AvailableChoices": [],
> >   "bAllowMultipleChoices": false
> > }
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Fighting Style (Choice)</summary>
>
> > ```json
> > {
> >   "Name": "Fighting Style",
> >   "ID": "FC_FightingStyle",
> >   "FeatureID": "FC_FightingStyle",
> >   "Description": "You adopt a particular style of fighting as your specialty.",
> >   "LevelUnlocked": 1,
> >   "FeatureType": "Choice",
> >   "FeatureData": {},
> >   "AvailableChoices": [
> >     { "ID": "FC_Archery", "Name": "Archery" },
> >     { "ID": "FC_Defense", "Name": "Defense" },
> >     { "ID": "FC_Dueling", "Name": "Dueling" }
> >   ],
> >   "bAllowMultipleChoices": false
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

**Navegação:** [← Índice](../index.md) | [← FeatDataTable](feat-datatable.md)

**Última atualização:** 2024-12-27
