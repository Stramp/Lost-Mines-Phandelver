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
    Describe("LoadClassProgression - Atualização de flags de escolhas",
             [this]()
             {
                 It("deve carregar progressão e features sem escolhas devem ter flag false",
                    [this]()
                    {
                        AddInfo(TEXT("Testando Data Asset: features sem escolhas após carregar progressão"));

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
                        // TestTrue("Deve ter progressão carregada", Asset->Multiclass[0].ClassData.Progression.Num() >
                        // 0); if (Asset->Multiclass[0].ClassData.Progression.Num() > 0)
                        // {
                        //     TArray<FMulticlassClassFeature> Features =
                        //     Asset->Multiclass[0].ClassData.Progression[0].Features; if (Features.Num() > 0)
                        //     {
                        //         FMulticlassClassFeature FirstFeature = Features[0];
                        //         // TODO: Verificar se flag foi atualizada (quando implementar)
                        //         // bool bHasChoices = FirstFeature.bHasAvailableChoices; // ou helper
                        //         // TestFalse("Feature sem escolhas deve ter flag false", bHasChoices);
                        //         TestEqual("Feature Automatic deve ter AvailableChoices = NAME_None",
                        //                  FirstFeature.AvailableChoices, NAME_None);
                        //     }
                        // }
                        AddInfo(TEXT("⚠️ Teste pendente: criar mocks e implementar flag/helper"));
                    });

                 It("deve carregar progressão e features com escolhas devem ter flag true",
                    [this]()
                    {
                        AddInfo(TEXT("Testando Data Asset: features com escolhas após carregar progressão"));

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
                        // TestTrue("Deve ter progressão carregada", Asset->Multiclass[0].ClassData.Progression.Num() >
                        // 0); if (Asset->Multiclass[0].ClassData.Progression.Num() > 0)
                        // {
                        //     TArray<FMulticlassClassFeature> Features =
                        //     Asset->Multiclass[0].ClassData.Progression[0].Features; if (Features.Num() > 0)
                        //     {
                        //         FMulticlassClassFeature FirstFeature = Features[0];
                        //         // TODO: Verificar se flag foi atualizada (quando implementar)
                        //         // bool bHasChoices = FirstFeature.bHasAvailableChoices; // ou helper
                        //         // TestTrue("Feature com escolhas deve ter flag true", bHasChoices);
                        //         TestNotEqual("Feature Choice deve ter AvailableChoices preenchido",
                        //                     FirstFeature.AvailableChoices, NAME_None);
                        //     }
                        // }
                        AddInfo(TEXT("⚠️ Teste pendente: criar mocks e implementar flag/helper"));
                    });

                 It("deve atualizar flags corretamente quando progressão é recarregada",
                    [this]()
                    {
                        AddInfo(TEXT("Testando Data Asset: flags devem ser atualizadas ao recarregar progressão"));

                        // Arrange
                        // TODO: Criar CharacterSheetDataAsset mock
                        // UCharacterSheetDataAsset* Asset = NewObject<UCharacterSheetDataAsset>();
                        // Asset->ClassDataTable = CreateMockClassDataTable();
                        // Asset->ClassFeaturesDataTable = CreateMockFeatureDataTable_ChoiceWithChoices();
                        // Asset->Multiclass.AddDefaulted();
                        // Asset->Multiclass[0].ClassData.Name = TEXT("Fighter");
                        // Asset->Multiclass[0].ClassData.LevelInClass = 1;

                        // Act - Carrega primeira vez
                        // bool bLoaded1 = FCharacterSheetDataAssetLoaders::LoadClassProgression(Asset, 0);

                        // Muda para feature sem escolhas
                        // Asset->ClassFeaturesDataTable = CreateMockFeatureDataTable_Automatic();

                        // Act - Recarrega
                        // bool bLoaded2 = FCharacterSheetDataAssetLoaders::LoadClassProgression(Asset, 0);

                        // Assert
                        // TestTrue("Primeira carga deve funcionar", bLoaded1);
                        // TestTrue("Segunda carga deve funcionar", bLoaded2);
                        // if (Asset->Multiclass[0].ClassData.Progression.Num() > 0)
                        // {
                        //     TArray<FMulticlassClassFeature> Features =
                        //     Asset->Multiclass[0].ClassData.Progression[0].Features; if (Features.Num() > 0)
                        //     {
                        //         FMulticlassClassFeature FirstFeature = Features[0];
                        //         // TODO: Verificar se flag foi atualizada corretamente
                        //         // bool bHasChoices = FirstFeature.bHasAvailableChoices; // ou helper
                        //         // TestFalse("Após recarregar com feature sem escolhas, flag deve ser false",
                        //         bHasChoices); TestEqual("Feature Automatic deve ter AvailableChoices = NAME_None",
                        //                  FirstFeature.AvailableChoices, NAME_None);
                        //     }
                        // }
                        AddInfo(TEXT("⚠️ Teste pendente: criar mocks e implementar flag/helper"));
                    });
             });
}

#pragma endregion CharacterSheetDataAssetLoaders Tests
