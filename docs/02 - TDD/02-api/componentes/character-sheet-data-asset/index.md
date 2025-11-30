# CharacterSheetDataAsset

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de api.md para arquivo dedicado |

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 CharacterSheetDataAsset - Data Assets</b></summary>

> **Caminho:** `Source/MyProject2/Characters/Data/CharacterSheetDataAsset.h`
>
> **Camada:** 1 - Data Assets
>
> **Responsabilidade:** Armazenar configuração estática editável no editor.

</details>

### Propriedades Principais

#### CharacterName
```cpp
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
FName CharacterName = NAME_None;
```
- **Tipo:** `FName`
- **Editável:** Apenas em defaults
- **Descrição:** Nome do personagem

#### SelectedRace
```cpp
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background",
          meta = (GetOptions = "GetRaceNames"))
FName SelectedRace = NAME_None;
```
- **Tipo:** `FName`
- **GetOptions:** `GetRaceNames()` - Dropdown com raças disponíveis
- **Descrição:** Raça selecionada

#### AbilityScores
```cpp
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Scores")
TMap<FName, FAbilityScoreEntry> AbilityScores;
```
- **Tipo:** `TMap<FName, FAbilityScoreEntry>`
- **Descrição:** Ability scores do personagem (chave: nome do atributo, valor: entrada com base/racial/final)
- **Estrutura:** Cada entrada contém `BaseScore`, `RacialBonus`, `FinalScore`

### Métodos GetOptions

Funções `UFUNCTION(CallInEditor)` para popular dropdowns no editor:

- `GetRaceNames()` - Retorna nomes de raças
- `GetSubraceNames()` - Retorna sub-raças para raça selecionada
- `GetBackgroundNames()` - Retorna nomes de backgrounds
- `GetClassNames()` - Retorna nomes de classes
- `GetSubclassNames(FName ClassName)` - Retorna subclasses para classe
- `GetAbilityScoreNames()` - Retorna nomes dos 6 atributos
- `GetAvailableFeatNames()` - Retorna feats disponíveis
- `GetSkillNames()` - Retorna nomes de skills
- `GetAvailableChoiceNames()` - Retorna todas as escolhas disponíveis de todas as features
- `GetAvailableChoiceNamesForFeature(FName FeatureFC_ID)` - Retorna escolhas filtradas por FC_ID de feature específica

**Nota:** A lógica de implementação está em `FCharacterSheetDataAssetGetOptions`, mas as funções devem permanecer na classe para o sistema `GetOptions` do Unreal funcionar.

**Filtro por Feature:**
- `GetAvailableChoiceNamesForFeature()` filtra escolhas por `FC_ID` da feature
- Usado em `FMulticlassClassFeature.AvailableChoices` para mostrar apenas escolhas da feature específica (ex: Fighting Style mostra apenas estilos de luta)
- Meta tag: `GetOptionsFunctionParams = "FC_ID"` passa o FC_ID automaticamente

### Validação no Editor

O `CharacterSheetDataAsset` valida dados automaticamente no editor via `PostEditChangeProperty()`:

- **Validação de Tipo de Data Tables:** Verifica se cada Data Table atribuída tem o RowStruct correto (ex: RaceDataTable deve ter `FRaceDataRow`). Exibe popup de erro com throttle se tipo incorreto for detectado.
- Valida Point Buy (27 pontos, scores 8-15)
- Valida nível total (máximo 20)
- Valida escolhas de Variant Human
- Atualiza bônus raciais automaticamente
- Atualiza campos calculados (proficiências, features)

**Validação de Tipo de Data Tables:**

Quando o usuário atribui uma Data Table no editor, o sistema valida automaticamente se o tipo está correto:

- **RaceDataTable** → Deve ter RowStruct `FRaceDataRow`
- **ClassDataTable** → Deve ter RowStruct `FClassDataRow`
- **BackgroundDataTable** → Deve ter RowStruct `FBackgroundDataRow`
- **FeatDataTable** → Deve ter RowStruct `FFeatDataRow`
- **ClassFeaturesDataTable** → Deve ter RowStruct `FFeatureDataRow`
- **ClassProficienciesDataTable** → Deve ter RowStruct `FProficiencyDataRow`
- **ProficiencyDataTable** → Deve ter RowStruct `FProficiencyDataRow`

**Comportamento:**
- Validação ocorre em `HandleDataTableChange()` quando Data Table é atribuída
- Validação também ocorre em `ValidateDataTables()` para todas as tabelas já atribuídas
- Popup de erro é exibido com throttle (0.5s) para evitar poluição visual
- Lógica de visibilidade (`UpdateSheetVisibility`) **não é afetada** - apenas verifica se tabelas são `!= nullptr`

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[CharacterSheetComponent](../character-sheet-component/index.md)** - Bridge Component que usa este Data Asset
> - **[CharacterDataComponent](../character-data-component/index.md)** - Runtime Component que recebe os dados
> - **[Estruturas Relacionadas](../estruturas-relacionadas/index.md)** - Structs auxiliares
> - **[Motores](../../motores/index.md)** - Motores de criação de personagem
> - **[Helpers](../../helpers/index.md)** - Funções helper para trabalhar com este Data Asset
> - **[Índice de Componentes](../index.md)** - Lista de todos os componentes

</details>
