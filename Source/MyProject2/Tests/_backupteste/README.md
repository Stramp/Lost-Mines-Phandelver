# Backup de Testes - Antes da Reorganização

**NOTA:** Esta pasta foi renomeada para `_backupteste` (com underscore) para que o Unreal Engine não reconheça como pasta de testes e não compile esses arquivos.

Este diretório contém um backup completo de todos os testes do projeto antes da reorganização por issue executada.

## Data do Backup
2025-12-03

## Motivo
Reorganização dos testes por issue executada, começando da issue 1.1.

## Estrutura

O backup mantém a estrutura original dos testes:

```
backupteste/
├── CharacterCreation/          # Testes de criação de personagem (já existiam)
├── Characters/                 # Testes de personagens
│   ├── Components/
│   ├── Data/
│   ├── Helpers/
│   └── Tests/
├── CreateSheet/                # Testes de criação de ficha
│   ├── Core/
│   ├── Multiclass/
│   ├── PointBuy/
│   └── RaceBonus/
├── Data/                       # Testes de tabelas de dados
│   └── Tables/
├── Integration/                # Testes de integração (já existiam)
├── SaveGame/                   # Testes de save/load
└── Utils/                      # Testes de utilitários
```

## Total de Arquivos

- **29 arquivos de teste** copiados do projeto
- **7 arquivos** já existiam no backup (CharacterCreation e Integration)

## Arquivos Copiados

### Characters (6 arquivos)
- `Characters/Components/Input/Tests/InputActionManagerComponentTests.cpp`
- `Characters/Data/Tests/CharacterSheetDataAssetHelpersTests.cpp`
- `Characters/Data/Tests/CharacterSheetDataAssetLoadersTests.cpp`
- `Characters/Data/Tests/CharacterSheetDataAssetValidatorsTests.cpp`
- `Characters/Helpers/Tests/MovementHelpersTests.cpp`
- `Characters/Tests/MyCharacterIntegrationTests.cpp`

### CreateSheet (7 arquivos)
- `CreateSheet/Core/Tests/CharacterSheetCoreTests.cpp`
- `CreateSheet/Multiclass/Tests/MulticlassHelpersTests.cpp`
- `CreateSheet/Multiclass/Tests/MulticlassMotorTests.cpp`
- `CreateSheet/Multiclass/Tests/MulticlassValidatorsTests.cpp`
- `CreateSheet/PointBuy/Tests/PointBuyMotorTests.cpp`
- `CreateSheet/PointBuy/Tests/PointBuyValidatorTests.cpp`
- `CreateSheet/RaceBonus/Tests/RaceBonusHelpersTests.cpp`
- `CreateSheet/RaceBonus/Tests/RaceBonusMotorTests.cpp`

### Data (2 arquivos)
- `Data/Tables/Tests/FeatDataTableTests.cpp`
- `Data/Tables/Tests/ProficiencyDataTableTests.cpp`

### SaveGame (1 arquivo)
- `SaveGame/Tests/SaveGameHelpersTests.cpp`

### Utils (10 arquivos)
- `Utils/Tests/CalculationHelpersTests.cpp`
- `Utils/Tests/CharacterSheetHelpersTests.cpp`
- `Utils/Tests/ChoiceHelpersTests.cpp`
- `Utils/Tests/ComponentHelpersTests.cpp`
- `Utils/Tests/DataTableHelpersTests.cpp`
- `Utils/Tests/DataTableRowHandleHelpersTests.cpp`
- `Utils/Tests/FormattingHelpersTests.cpp`
- `Utils/Tests/GameplayTagHelpersTests.cpp`
- `Utils/Tests/PointBuyHelpersTests.cpp`
- `Utils/Tests/ProficiencyHelpersTests.cpp`
- `Utils/Tests/SoftReferenceHelpersTests.cpp`
- `Utils/Tests/ValidationHelpersTests.cpp`

## Próximos Passos

Após a reorganização por issue, os testes serão reorganizados seguindo a estrutura:

```
Tests/
├── Issue-1.1/
├── Issue-1.2/
├── Issue-2.1/
└── ...
```

Cada pasta de issue conterá os testes relacionados àquela issue específica.

