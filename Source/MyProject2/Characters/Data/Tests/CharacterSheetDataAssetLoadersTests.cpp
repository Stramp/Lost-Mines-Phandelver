// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/Data/Loaders/CharacterSheetDataAssetLoaders.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "CreateSheet/Multiclass/MulticlassHelpers.h"
#include "Data/Structures/MulticlassTypes.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// CharacterSheetDataAssetLoaders Tests
// ============================================================================
#pragma region CharacterSheetDataAssetLoaders Tests

BEGIN_DEFINE_SPEC(CharacterSheetDataAssetLoadersSpec, "MyProject2.Characters.Data.Loaders",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(CharacterSheetDataAssetLoadersSpec)

void CharacterSheetDataAssetLoadersSpec::Define()
{
    Describe("LoadClassProgression",
             [this]()
             {
                 It("deve carregar progressão de classe corretamente",
                    [this]()
                    {
                        AddInfo(TEXT("Testando Data Asset: carregamento de progressão de classe"));

                        // Arrange
                        // TODO: Criar CharacterSheetDataAsset mock com DataTables
                        // UCharacterSheetDataAsset* Asset = NewObject<UCharacterSheetDataAsset>();
                        // Asset->ClassDataTable = CreateMockClassDataTable();
                        // Asset->ClassFeaturesDataTable = CreateMockFeatureDataTable_Automatic();
                        // Asset->Multiclass.AddDefaulted();
                        // Asset->Multiclass[0].ClassData.Name = TEXT("Fighter");
                        // Asset->Multiclass[0].ClassData.LevelInClass = 1;

                        // Act
                        // bool bLoaded = FCharacterSheetDataAssetLoaders::LoadClassProgression(Asset, 0);

                        // Assert
                        // TestTrue("Loader deve carregar progressão", bLoaded);
                        // TestTrue("Deve ter progressão carregada", Asset->Multiclass[0].ClassData.Progression.Num() > 0);
                        AddInfo(TEXT("⚠️ Teste pendente: criar mocks para testar carregamento"));
                    });
             });

    Describe("LoadClassProgression - Features sem escolhas",
             [this]()
             {
                 It("deve definir AvailableChoices como NAME_None quando feature não tem escolhas",
                    [this]()
                    {
                        AddInfo(TEXT("Testando Data Asset: features sem escolhas devem ter AvailableChoices = NAME_None"));

                        // Arrange
                        // TODO: Criar CharacterSheetDataAsset mock com DataTables
                        // UCharacterSheetDataAsset* Asset = NewObject<UCharacterSheetDataAsset>();
                        // Asset->ClassDataTable = CreateMockClassDataTable();
                        // Asset->ClassFeaturesDataTable = CreateMockFeatureDataTable_Automatic();
                        // Asset->Multiclass.AddDefaulted();
                        // Asset->Multiclass[0].ClassData.Name = TEXT("Fighter");
                        // Asset->Multiclass[0].ClassData.LevelInClass = 1;

                        // Act
                        // bool bLoaded = FCharacterSheetDataAssetLoaders::LoadClassProgression(Asset, 0);

                        // Assert
                        // TestTrue("Loader deve carregar progressão", bLoaded);
                        // if (Asset->Multiclass[0].ClassData.Progression.Num() > 0)
                        // {
                        //     TArray<FMulticlassClassFeature> Features = Asset->Multiclass[0].ClassData.Progression[0].Features;
                        //     if (Features.Num() > 0)
                        //     {
                        //         FMulticlassClassFeature FirstFeature = Features[0];
                        //         TestEqual("Feature sem escolhas deve ter AvailableChoices = NAME_None",
                        //                  FirstFeature.AvailableChoices, NAME_None);
                        //     }
                        // }
                        AddInfo(TEXT("⚠️ Teste pendente: criar mocks para testar comportamento"));
                    });
             });

    Describe("LoadClassProgression - Features com escolhas",
             [this]()
             {
                 It("deve preencher AvailableChoices quando feature tem escolhas disponíveis",
                    [this]()
                    {
                        AddInfo(TEXT("Testando Data Asset: features com escolhas devem ter AvailableChoices preenchido"));

                        // Arrange
                        // TODO: Criar CharacterSheetDataAsset mock com DataTables
                        // UCharacterSheetDataAsset* Asset = NewObject<UCharacterSheetDataAsset>();
                        // Asset->ClassDataTable = CreateMockClassDataTable();
                        // Asset->ClassFeaturesDataTable = CreateMockFeatureDataTable_ChoiceWithChoices();
                        // Asset->Multiclass.AddDefaulted();
                        // Asset->Multiclass[0].ClassData.Name = TEXT("Fighter");
                        // Asset->Multiclass[0].ClassData.LevelInClass = 1;

                        // Act
                        // bool bLoaded = FCharacterSheetDataAssetLoaders::LoadClassProgression(Asset, 0);

                        // Assert
                        // TestTrue("Loader deve carregar progressão", bLoaded);
                        // if (Asset->Multiclass[0].ClassData.Progression.Num() > 0)
                        // {
                        //     TArray<FMulticlassClassFeature> Features = Asset->Multiclass[0].ClassData.Progression[0].Features;
                        //     if (Features.Num() > 0)
                        //     {
                        //         FMulticlassClassFeature FirstFeature = Features[0];
                        //         TestNotEqual("Feature com escolhas deve ter AvailableChoices preenchido",
                        //                     FirstFeature.AvailableChoices, NAME_None);
                        //     }
                        // }
                        AddInfo(TEXT("⚠️ Teste pendente: criar mocks para testar comportamento"));
                    });
             });

    Describe("LoadClassProficiencies", [this]()
    {
        It("deve IMPEDIR adição manual de proficiências no array da classe", [this]()
        {
            AddInfo(TEXT("Testando: sistema deve IMPEDIR adição manual de proficiências (TDD - deve falhar até implementação)"));

            // Arrange
            UCharacterSheetDataAsset* Asset = NewObject<UCharacterSheetDataAsset>();
            Asset->Multiclass.AddDefaulted();
            FMulticlassClassData& ClassData = Asset->Multiclass[0].ClassData;

            // Configura classe válida
            ClassData.Name = TEXT("Fighter");
            ClassData.LevelInClass = 1;

            // Verifica que array está vazio inicialmente
            TestEqual("Array de proficiências deve estar vazio inicialmente",
                      ClassData.Proficiencies.Num(), 0);

            // Act - Tenta adicionar proficiência manualmente (deve ser bloqueado)
            FMulticlassProficienciesEntry NewProficiency;
            NewProficiency.armas.Add(TEXT("PW_Simple_Weapons"));
            NewProficiency.armaduras.Add(TEXT("PA_Light_Armor"));
            NewProficiency.savingThrows.Add(TEXT("STR"));
            NewProficiency.savingThrows.Add(TEXT("CON"));

            // NOTA: Sistema deve impedir adição manual - apenas LoadClassProficiencies pode adicionar
            // Por enquanto, este teste deve FALHAR até implementarmos proteção
            ClassData.Proficiencies.Add(NewProficiency);

            // Assert - Sistema deve manter array vazio ou limpar adições manuais
            // Este teste deve FALHAR até implementarmos validação que impede adições manuais
            TestEqual("Array deve permanecer vazio após tentativa de adição manual (sistema deve bloquear)",
                      ClassData.Proficiencies.Num(), 0);
        });

        It("deve IMPEDIR adição manual de múltiplas proficiências no array", [this]()
        {
            AddInfo(TEXT("Testando: sistema deve IMPEDIR adição manual de múltiplas proficiências (TDD - deve falhar até implementação)"));

            // Arrange
            UCharacterSheetDataAsset* Asset = NewObject<UCharacterSheetDataAsset>();
            Asset->Multiclass.AddDefaulted();
            FMulticlassClassData& ClassData = Asset->Multiclass[0].ClassData;
            ClassData.Name = TEXT("Fighter");
            ClassData.LevelInClass = 1;

            // Act - Tenta adicionar proficiências manualmente (deve ser bloqueado)
            FMulticlassProficienciesEntry Proficiency1;
            Proficiency1.armas.Add(TEXT("PW_Simple_Weapons"));
            ClassData.Proficiencies.Add(Proficiency1);

            FMulticlassProficienciesEntry Proficiency2;
            Proficiency2.armaduras.Add(TEXT("PA_Medium_Armor"));
            ClassData.Proficiencies.Add(Proficiency2);

            // Assert - Sistema deve manter array vazio ou limpar adições manuais
            // Este teste deve FALHAR até implementarmos validação que impede adições manuais
            TestEqual("Array deve permanecer vazio após tentativas de adição manual (sistema deve bloquear)",
                      ClassData.Proficiencies.Num(), 0);
        });

        It("deve IMPEDIR adição manual de proficiências com skills", [this]()
        {
            AddInfo(TEXT("Testando: sistema deve IMPEDIR adição manual de proficiências com FSkills (TDD - deve falhar até implementação)"));

            // Arrange
            UCharacterSheetDataAsset* Asset = NewObject<UCharacterSheetDataAsset>();
            Asset->Multiclass.AddDefaulted();
            FMulticlassClassData& ClassData = Asset->Multiclass[0].ClassData;
            ClassData.Name = TEXT("Rogue");
            ClassData.LevelInClass = 1;

            // Act - Tenta adicionar proficiência com skills manualmente (deve ser bloqueado)
            FMulticlassProficienciesEntry Proficiency;
            Proficiency.FSkills.InitialAvailable.Add(TEXT("Acrobatics"));
            Proficiency.FSkills.InitialAvailable.Add(TEXT("Stealth"));
            Proficiency.FSkills.InitialQtdAvailable = 4;
            ClassData.Proficiencies.Add(Proficiency);

            // Assert - Sistema deve manter array vazio ou limpar adições manuais
            // Este teste deve FALHAR até implementarmos validação que impede adições manuais
            TestEqual("Array deve permanecer vazio após tentativa de adição manual com skills (sistema deve bloquear)",
                      ClassData.Proficiencies.Num(), 0);
        });

        It("deve carregar proficiências apenas via LoadClassProficiencies", [this]()
        {
            AddInfo(TEXT("Testando: proficiências devem ser carregadas apenas via LoadClassProficiencies (TDD - deve falhar até implementação)"));

            // Arrange
            UCharacterSheetDataAsset* Asset = NewObject<UCharacterSheetDataAsset>();
            Asset->Multiclass.AddDefaulted();
            FMulticlassClassData& ClassData = Asset->Multiclass[0].ClassData;
            ClassData.Name = TEXT("Fighter");
            ClassData.LevelInClass = 1;

            // Act - Carrega proficiências via loader (método correto)
            // NOTA: Este teste requer DataTables configurados, por enquanto deve falhar
            bool bLoaded = FCharacterSheetDataAssetLoaders::LoadClassProficiencies(Asset, 0);

            // Assert - Loader deve carregar proficiências corretamente
            // Este teste deve FALHAR até implementarmos LoadClassProficiencies completo
            TestTrue("LoadClassProficiencies deve carregar proficiências", bLoaded);
            TestTrue("Array deve ter proficiências após LoadClassProficiencies",
                     ClassData.Proficiencies.Num() > 0);
        });
    });
}


#pragma endregion CharacterSheetDataAssetLoaders Tests
