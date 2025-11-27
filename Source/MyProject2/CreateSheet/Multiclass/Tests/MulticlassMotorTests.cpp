// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "CreateSheet/Multiclass/MulticlassMotor.h"
#include "CreateSheet/Multiclass/MulticlassHelpers.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/FeatureDataTable.h"
#include "Data/Structures/MulticlassTypes.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// MulticlassMotor Tests
// ============================================================================
#pragma region MulticlassMotor Tests

BEGIN_DEFINE_SPEC(MulticlassMotorSpec, "MyProject2.CreateSheet.MulticlassMotor",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(MulticlassMotorSpec)

void MulticlassMotorSpec::Define()
{
    Describe(
        "LoadClassProgression - Features com/sem escolhas",
        [this]()
        {
            It("deve retornar features com AvailableChoices NAME_None quando feature é Automatic",
               [this]()
               {
                   AddInfo(TEXT("Testando motor: feature Automatic deve ter AvailableChoices = NAME_None"));

                   // Arrange
                   // TODO: Criar DataTable mock com feature Automatic
                   // UDataTable* ClassDataTable = CreateMockClassDataTable();
                   // UDataTable* FeatureDataTable = CreateMockFeatureDataTable_Automatic();
                   // FName ClassName = TEXT("Fighter");
                   // int32 LevelInClass = 1;

                   // Act
                   // TArray<FMulticlassProgressEntry> Progression;
                   // bool bLoaded = FMulticlassMotor::LoadClassProgression(ClassName, LevelInClass,
                   //                                                    ClassDataTable, FeatureDataTable, Progression);

                   // Assert
                   // TestTrue("Motor deve carregar progressão", bLoaded);
                   // TestTrue("Deve ter pelo menos 1 nível", Progression.Num() > 0);
                   // if (Progression.Num() > 0 && Progression[0].Features.Num() > 0)
                   // {
                   //     FMulticlassClassFeature FirstFeature = Progression[0].Features[0];
                   //     TestEqual("Feature Automatic deve ter AvailableChoices = NAME_None",
                   //              FirstFeature.AvailableChoices, NAME_None);
                   //     // TODO: Testar helper FeatureHasAvailableChoices
                   //     // bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(FirstFeature);
                   //     // TestFalse("Feature Automatic não deve ter escolhas disponíveis", bHasChoices);
                   // }
                   AddInfo(TEXT("⚠️ Teste pendente: criar DataTable mocks para testar motor"));
               });

            It("deve retornar features com AvailableChoices preenchido quando feature é Choice com escolhas",
               [this]()
               {
                   AddInfo(TEXT("Testando motor: feature Choice com escolhas deve ter AvailableChoices preenchido"));

                   // Arrange
                   // TODO: Criar DataTable mock com feature Choice que tem escolhas
                   // UDataTable* ClassDataTable = CreateMockClassDataTable();
                   // UDataTable* FeatureDataTable = CreateMockFeatureDataTable_ChoiceWithChoices();
                   // FName ClassName = TEXT("Fighter");
                   // int32 LevelInClass = 1;

                   // Act
                   // TArray<FMulticlassProgressEntry> Progression;
                   // bool bLoaded = FMulticlassMotor::LoadClassProgression(ClassName, LevelInClass,
                   //                                                    ClassDataTable, FeatureDataTable, Progression);

                   // Assert
                   // TestTrue("Motor deve carregar progressão", bLoaded);
                   // TestTrue("Deve ter pelo menos 1 nível", Progression.Num() > 0);
                   // if (Progression.Num() > 0 && Progression[0].Features.Num() > 0)
                   // {
                   //     FMulticlassClassFeature FirstFeature = Progression[0].Features[0];
                   //     TestNotEqual("Feature Choice deve ter AvailableChoices preenchido",
                   //                  FirstFeature.AvailableChoices, NAME_None);
                   //     // TODO: Testar helper FeatureHasAvailableChoices
                   //     // bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(FirstFeature);
                   //     // TestTrue("Feature Choice com escolhas deve retornar true", bHasChoices);
                   // }
                   AddInfo(TEXT("⚠️ Teste pendente: criar DataTable mocks para testar motor"));
               });

            It("deve retornar features com AvailableChoices NAME_None quando feature é Choice mas sem escolhas na "
               "tabela",
               [this]()
               {
                   AddInfo(TEXT(
                       "Testando motor: feature Choice sem escolhas na tabela deve ter AvailableChoices = NAME_None"));

                   // Arrange
                   // TODO: Criar DataTable mock com feature Choice mas sem AvailableChoices
                   // UDataTable* ClassDataTable = CreateMockClassDataTable();
                   // UDataTable* FeatureDataTable = CreateMockFeatureDataTable_ChoiceWithoutChoices();
                   // FName ClassName = TEXT("Fighter");
                   // int32 LevelInClass = 1;

                   // Act
                   // TArray<FMulticlassProgressEntry> Progression;
                   // bool bLoaded = FMulticlassMotor::LoadClassProgression(ClassName, LevelInClass,
                   //                                                    ClassDataTable, FeatureDataTable, Progression);

                   // Assert
                   // TestTrue("Motor deve carregar progressão", bLoaded);
                   // TestTrue("Deve ter pelo menos 1 nível", Progression.Num() > 0);
                   // if (Progression.Num() > 0 && Progression[0].Features.Num() > 0)
                   // {
                   //     FMulticlassClassFeature FirstFeature = Progression[0].Features[0];
                   //     TestEqual("Feature Choice sem escolhas deve ter AvailableChoices = NAME_None",
                   //              FirstFeature.AvailableChoices, NAME_None);
                   //     // TODO: Testar helper FeatureHasAvailableChoices
                   //     // bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(FirstFeature);
                   //     // TestFalse("Feature Choice sem escolhas não deve retornar true", bHasChoices);
                   // }
                   AddInfo(TEXT("⚠️ Teste pendente: criar DataTable mocks para testar motor"));
               });
        });
}

#pragma endregion MulticlassMotor Tests
