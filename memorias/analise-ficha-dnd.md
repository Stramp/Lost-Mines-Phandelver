# Análise: Ficha D&D 5e

## Situação Atual

**Já existe:**
- Data Tables: RaceDataTable, ClassDataTable, BackgroundDataTable
- CharacterSheetDataAsset básico (Nome, Descrição, Level)
- CharacterSheetComponent e CharacterDataComponent

**Precisa implementar:**
- Point Buy System (27 pontos)
- Dropdowns dependentes (Raça → Sub-raça, Classe → Sub-classe)
- Multi-classing (níveis por classe)
- Level up system (features por nível)

## Estrutura de Dados Necessária

```
CharacterSheetDataAsset
├── Basic: Nome, Descrição
├── Race: SelectedRace, SelectedSubrace
├── Class: ClassLevels (TMap<ClassName, Level>), ClassSubclasses
├── Background: SelectedBackground
├── Point Buy: AvailablePoints (27), BaseAbilityScores (TMap<Ability, Score>)
└── Calculated: TotalLevel, FinalAbilityScores
```

## Próximos Passos

1. Expandir CharacterSheetDataAsset com campos acima
2. Implementar Point Buy validation
3. Criar helpers para dropdowns dependentes
4. Implementar multi-classing calculation
