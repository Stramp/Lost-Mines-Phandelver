# Guia de Início Rápido

Guia prático passo a passo para criar e configurar um personagem completo no sistema de fichas D&D 5e.

## Pré-requisitos

- Unreal Engine 5.7 instalado
- Projeto MyProject2 compilado e aberto no editor
- Data Tables configurados (Race, Class, Background, Feat)

## Passo 1: Configurar Data Tables

Antes de criar personagens, é necessário configurar os Data Tables no `CharacterSheetDataAsset`.

### 1.1 Criar CharacterSheetDataAsset

1. No Content Browser, navegue até a pasta desejada
2. Clique com botão direito → **Miscellaneous** → **Data Asset**
3. Selecione **Character Sheet Data Asset**
4. Nomeie o asset (ex: `DA_CharacterSheet_Elias`)

### 1.2 Atribuir Data Tables

No `CharacterSheetDataAsset` criado, na categoria **Data Tables**:

1. **Race Data Table:** Atribua o Data Table de raças
2. **Class Data Table:** Atribua o Data Table de classes
3. **Background Data Table:** Atribua o Data Table de backgrounds
4. **Feat Data Table:** Atribua o Data Table de feats

**Importante:** Após atribuir todos os Data Tables, todas as categorias da ficha ficarão visíveis automaticamente.

## Passo 2: Preencher Ficha do Personagem

### 2.1 Informações Básicas

Na categoria **Basic Info**:

- **Character Name:** Nome do personagem (ex: "Elias")
- **Character Description:** Descrição do personagem (ex: "Severino")

### 2.2 Raça e Background

Na categoria **Race & Background**:

1. **Selected Race:** Selecione a raça (ex: "Human")
2. **Selected Subrace:** Selecione sub-raça se aplicável (ex: "Variant Human")
3. **Selected Background:** Selecione background (ex: "Acolyte")

**Nota:** Os dropdowns são populados automaticamente pelos Data Tables.

### 2.3 Ability Scores (Point Buy)

Na categoria **Ability Scores**:

1. Ajuste cada ability score entre 8 e 15
2. O sistema Point Buy valida automaticamente:
   - Máximo 27 pontos gastos
   - Cada score entre 8 e 15
   - Points Remaining mostra pontos restantes

**Exemplo:**
- Strength: 10
- Dexterity: 12
- Constitution: 14
- Intelligence: 13
- Wisdom: 15
- Charisma: 11
- **Points Remaining:** 0 (todos os 27 pontos usados)

### 2.4 Variant Human (se aplicável)

Se selecionou "Variant Human" como sub-raça, a categoria **Variant Human** aparecerá:

1. **Custom Ability Score Choices:** Selecione 2 atributos para receber +1 cada
2. **Selected Feat:** Escolha um feat disponível
3. **Selected Skill:** Escolha uma skill

**Validação:** O sistema valida automaticamente que:
- Exatamente 2 atributos foram escolhidos
- Feat está disponível (sem pré-requisitos de nível)
- Skill é válida

### 2.5 Classes

Na categoria **Classes**:

1. Adicione entradas em **Class Levels**
2. Para cada entrada:
   - **Class Name:** Selecione a classe (ex: "Fighter")
   - **Level:** Defina o nível (1-20)
   - **Subclass Name:** Selecione subclasse se aplicável

**Multi-classing:** Você pode adicionar múltiplas classes. O sistema valida que o nível total não exceda 20.

## Passo 3: Configurar Actor no Mapa

### 3.1 Criar Actor

1. No Level Editor, adicione um Actor ao mapa (ou use um existente)
2. Selecione o Actor

### 3.2 Adicionar Componentes

No Details Panel do Actor:

1. Clique em **Add Component**
2. Adicione **Character Data Component**
3. Adicione **Character Sheet Component**

### 3.3 Configurar Character Sheet Component

No **Character Sheet Component**:

1. Em **Source Data Asset**, atribua o `CharacterSheetDataAsset` criado anteriormente

**Importante:** O sistema inicializará automaticamente no `BeginPlay()`.

## Passo 4: Testar e Validar

### 4.1 Executar no Editor

1. Pressione **Play** no editor
2. O sistema executará automaticamente:
   - `CharacterSheetComponent::BeginPlay()` inicializa dados
   - `CharacterDataComponent::BeginPlay()` valida e faz log

### 4.2 Verificar Log

No **Output Log**, você verá:

```
=== Character Sheet ===
Name: Elias
Description: Severino
Level Total: 1
Race: Human (Variant Human)
Background: Acolyte
--- Ability Scores ---
  Strength: 10
  Dexterity: 12
  Constitution: 14
  Intelligence: 13
  Wisdom: 15
  Charisma: 11
--- Proficiencies (4) ---
  Insight, Religion, Perception, Investigation
--- Data Integrity ---
  ✅ Todos os dados estão válidos e organizados corretamente
======================
```

### 4.3 Validar Integridade

O log mostra automaticamente se os dados estão válidos:

- ✅ **Verde:** Todos os dados válidos
- ❌ **Vermelho:** Dados inválidos ou incompletos (verifique erros acima)

## Exemplos de Código

### Acessar Ability Scores em C++

```cpp
// Em um componente que precisa dos dados do personagem
UCharacterDataComponent* DataComponent = GetCharacterDataComponent();
if (DataComponent && DataComponent->ValidateDataIntegrity())
{
    // Acessar ability score
    if (DataComponent->AbilityScores.Contains(TEXT("Strength")))
    {
        int32 Strength = DataComponent->AbilityScores[TEXT("Strength")];
        int32 Modifier = (Strength - 10) / 2; // Modifier = (Score - 10) / 2
        UE_LOG(LogTemp, Log, TEXT("Strength: %d (Modifier: %d)"), Strength, Modifier);
    }
}
```

### Validar Dados Antes de Usar

```cpp
void UMyCombatComponent::CalculateDamage()
{
    UCharacterDataComponent* DataComponent = GetCharacterDataComponent();

    // SEMPRE valide antes de usar dados
    if (!DataComponent || !DataComponent->ValidateDataIntegrity())
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot calculate damage: invalid character data"));
        return;
    }

    // Dados válidos, pode usar com segurança
    int32 Strength = DataComponent->AbilityScores[TEXT("Strength")];
    // ... calcular dano ...
}
```

### Criar Personagem Programaticamente

```cpp
void UMyCharacterCreator::CreateCharacterProgrammatically()
{
    // Criar ou obter CharacterSheetDataAsset
    UCharacterSheetDataAsset* DataAsset = NewObject<UCharacterSheetDataAsset>();

    // Configurar dados básicos
    DataAsset->CharacterName = TEXT("Elias");
    DataAsset->SelectedRace = TEXT("Human");
    DataAsset->SelectedSubrace = TEXT("Variant Human");
    DataAsset->SelectedBackground = TEXT("Acolyte");

    // Configurar ability scores
    DataAsset->AbilityScores[TEXT("Strength")].BaseScore = 10;
    DataAsset->AbilityScores[TEXT("Dexterity")].BaseScore = 12;
    // ... outros atributos ...

    // Adicionar classe
    FClassLevelEntry ClassEntry;
    ClassEntry.ClassName = TEXT("Fighter");
    ClassEntry.Level = 1;
    DataAsset->ClassLevels.Add(ClassEntry);

    // Inicializar no componente
    UCharacterSheetComponent* SheetComponent = GetCharacterSheetComponent();
    if (SheetComponent)
    {
        SheetComponent->InitializeFromDataAsset(DataAsset);
    }
}
```

### Integrar com Combat Components (Preparação)

```cpp
// Exemplo de como um CombatComponent futuro pode usar os dados
int32 UCombatComponent::GetAbilityModifier(FName AbilityName) const
{
    UCharacterDataComponent* DataComponent = GetCharacterDataComponent();
    if (!DataComponent)
    {
        return 0;
    }

    // Validar integridade antes de usar
    if (!DataComponent->ValidateDataIntegrity())
    {
        UE_LOG(LogTemp, Warning, TEXT("Character data invalid, returning 0 modifier"));
        return 0;
    }

    if (DataComponent->AbilityScores.Contains(AbilityName))
    {
        int32 Score = DataComponent->AbilityScores[AbilityName];
        return (Score - 10) / 2; // Modifier = (Score - 10) / 2
    }

    return 0;
}

bool UCombatComponent::HasProficiency(FName ProficiencyName) const
{
    UCharacterDataComponent* DataComponent = GetCharacterDataComponent();
    if (!DataComponent)
    {
        return false;
    }

    return DataComponent->Proficiencies.Contains(ProficiencyName);
}
```

## Troubleshooting Básico

### Problema: Categorias não aparecem no editor

**Solução:** Verifique se todos os Data Tables foram atribuídos. Quando todos estão atribuídos, todas as categorias ficam visíveis.

### Problema: Validação falhando

**Solução:**
1. Verifique se todos os 6 ability scores estão presentes
2. Verifique se raça e background foram selecionados
3. Verifique se nível total está entre 1 e 20
4. Veja o log para mensagens de erro específicas

### Problema: Dados não replicando em multiplayer

**Solução:**
1. Verifique se `GetLifetimeReplicatedProps()` está implementado
2. Verifique se todas as propriedades têm `DOREPLIFETIME`
3. Verifique se está executando no servidor (lógica autoritária)

### Problema: Ability scores não atualizando

**Solução:**
1. Verifique se os bônus raciais estão sendo aplicados corretamente
2. Verifique se o Data Table de raças está configurado
3. O sistema atualiza automaticamente quando raça/sub-raça muda

## Próximos Passos

Após criar o personagem básico:

1. **Combat Components:** Integrar ability scores e modifiers em sistema de combate
2. **GAS Migration:** Preparar para migração futura para Gameplay Ability System
3. **HP Calculation:** Implementar cálculo de HP baseado em Constitution
4. **Features:** Implementar features de classes (spells, abilities, etc.)

Veja [ARCHITECTURE.md](../../ARCHITECTURE.md) para mais detalhes sobre a arquitetura do sistema.
