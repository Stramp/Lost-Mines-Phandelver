// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Data/Structures/MulticlassTypes.h"
#include "Engine/DataTable.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"
#include "Data/Tables/FeatDataTable.h"
#include "Data/Tables/FeatureDataTable.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Data/Tables/ItemDataTable.h"
#include "Utils/DataTableHelpers.h"

#pragma endregion Includes

// ============================================================================
// CharacterSheetDataAssetHelpers Tests
// ============================================================================
#pragma region CharacterSheetDataAssetHelpers Tests

BEGIN_DEFINE_SPEC(CharacterSheetDataAssetHelpersSpec, "MyProject2.CharacterSheetDataAssetHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UCharacterSheetDataAsset *TestAsset;
UDataTable *TestRaceDataTable;
UDataTable *TestClassDataTable;

END_DEFINE_SPEC(CharacterSheetDataAssetHelpersSpec)

void CharacterSheetDataAssetHelpersSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar Asset e Data Tables de teste
            TestAsset = NewObject<UCharacterSheetDataAsset>();
            TestRaceDataTable = NewObject<UDataTable>();
            TestRaceDataTable->RowStruct = FRaceDataRow::StaticStruct();
            TestClassDataTable = NewObject<UDataTable>();
            TestClassDataTable->RowStruct = FClassDataRow::StaticStruct();
        });

    AfterEach(
        [this]()
        {
            // Cleanup
            if (TestAsset)
            {
                TestAsset->ConditionalBeginDestroy();
            }
            if (TestRaceDataTable)
            {
                TestRaceDataTable->ConditionalBeginDestroy();
            }
            if (TestClassDataTable)
            {
                TestClassDataTable->ConditionalBeginDestroy();
            }
        });

    // ============================================================================
    // Data Table Type Validation Tests
    // ============================================================================
    Describe(
        "ValidateDataTableType",
        [this]()
        {
            It("deve retornar true quando DataTable é nullptr",
               [this]()
               {
                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::ValidateDataTableType(
                       TestAsset, nullptr, TEXT("RaceDataTable"), TEXT("FRaceDataRow"),
                       DataTableHelpers::IsRaceDataTable);

                   // Assert
                   TestTrue("ValidateDataTableType deve retornar true para nullptr", Result);
               });

            It("deve retornar true quando DataTable tem tipo correto",
               [this]()
               {
                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::ValidateDataTableType(
                       TestAsset, TestRaceDataTable, TEXT("RaceDataTable"), TEXT("FRaceDataRow"),
                       DataTableHelpers::IsRaceDataTable);

                   // Assert
                   TestTrue("ValidateDataTableType deve retornar true para tipo correto", Result);
               });

            It("deve retornar false quando DataTable tem tipo incorreto",
               [this]()
               {
                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::ValidateDataTableType(
                       TestAsset, TestClassDataTable, TEXT("RaceDataTable"), TEXT("FRaceDataRow"),
                       DataTableHelpers::IsRaceDataTable);

                   // Assert
                   TestFalse("ValidateDataTableType deve retornar false para tipo incorreto", Result);
               });
        });

    // ============================================================================
    // Multiple Choice Feature Helpers Tests
    // ============================================================================
    Describe(
        "GetMaxChoicesLimit",
        [this]()
        {
            It("deve retornar -1 quando MaxChoices não está definido",
               [this]()
               {
                   // Arrange
                   FMulticlassClassFeature Feature;
                   Feature.FeatureData.Empty(); // Sem MaxChoices

                   // Act
                   int32 Result = FCharacterSheetDataAssetHelpers::GetMaxChoicesLimit(Feature);

                   // Assert
                   TestEqual("GetMaxChoicesLimit deve retornar -1 quando não há limite", Result, -1);
               });

            It("deve retornar limite correto quando MaxChoices está definido",
               [this]()
               {
                   // Arrange
                   FMulticlassClassFeature Feature;
                   Feature.FeatureData.Add(TEXT("MaxChoices"), TEXT("3"));

                   // Act
                   int32 Result = FCharacterSheetDataAssetHelpers::GetMaxChoicesLimit(Feature);

                   // Assert
                   TestEqual("GetMaxChoicesLimit deve retornar 3 quando MaxChoices é 3", Result, 3);
               });

            It("deve retornar -1 quando MaxChoices é inválido (0 ou negativo)",
               [this]()
               {
                   // Arrange
                   FMulticlassClassFeature Feature;
                   Feature.FeatureData.Add(TEXT("MaxChoices"), TEXT("0"));

                   // Act
                   int32 Result = FCharacterSheetDataAssetHelpers::GetMaxChoicesLimit(Feature);

                   // Assert
                   TestEqual("GetMaxChoicesLimit deve retornar -1 quando MaxChoices é 0", Result, -1);
               });
        });

    Describe(
        "CanAddChoice",
        [this]()
        {
            It("deve retornar true quando escolha é válida e não é duplicata",
               [this]()
               {
                   // Arrange
                   FName Choice = TEXT("Archery");
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};
                   TArray<FName> SelectedChoices;
                   int32 MaxChoices = -1; // Sem limite

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CanAddChoice(Choice, ValidChoices, SelectedChoices,
                                                                                MaxChoices);

                   // Assert
                   TestTrue("CanAddChoice deve retornar true para escolha válida", Result);
               });

            It("deve retornar false quando escolha não está em ValidChoices",
               [this]()
               {
                   // Arrange
                   FName Choice = TEXT("InvalidChoice");
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};
                   TArray<FName> SelectedChoices;
                   int32 MaxChoices = -1;

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CanAddChoice(Choice, ValidChoices, SelectedChoices,
                                                                                MaxChoices);

                   // Assert
                   TestFalse("CanAddChoice deve retornar false para escolha inválida", Result);
               });

            It("deve retornar false quando escolha já está em SelectedChoices (duplicata)",
               [this]()
               {
                   // Arrange
                   FName Choice = TEXT("Archery");
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};
                   TArray<FName> SelectedChoices = {TEXT("Archery")};
                   int32 MaxChoices = -1;

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CanAddChoice(Choice, ValidChoices, SelectedChoices,
                                                                                MaxChoices);

                   // Assert
                   TestFalse("CanAddChoice deve retornar false para escolha duplicata", Result);
               });

            It("deve retornar false quando limite máximo foi atingido",
               [this]()
               {
                   // Arrange
                   FName Choice = TEXT("Defense");
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};
                   TArray<FName> SelectedChoices = {TEXT("Archery")};
                   int32 MaxChoices = 1; // Limite de 1 escolha

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CanAddChoice(Choice, ValidChoices, SelectedChoices,
                                                                                MaxChoices);

                   // Assert
                   TestFalse("CanAddChoice deve retornar false quando limite foi atingido", Result);
               });

            It("deve retornar true quando limite não foi atingido",
               [this]()
               {
                   // Arrange
                   FName Choice = TEXT("Defense");
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};
                   TArray<FName> SelectedChoices = {TEXT("Archery")};
                   int32 MaxChoices = 3; // Limite de 3 escolhas

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CanAddChoice(Choice, ValidChoices, SelectedChoices,
                                                                                MaxChoices);

                   // Assert
                   TestTrue("CanAddChoice deve retornar true quando limite não foi atingido", Result);
               });
        });

    Describe(
        "CleanInvalidAndDuplicateChoices",
        [this]()
        {
            It("deve retornar false quando não há mudanças (todas escolhas são válidas e únicas)",
               [this]()
               {
                   // Arrange
                   TArray<FName> SelectedChoices = {TEXT("Archery"), TEXT("Defense")};
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(SelectedChoices,
                                                                                                  ValidChoices);

                   // Assert
                   TestFalse("CleanInvalidAndDuplicateChoices deve retornar false quando não há mudanças", Result);
                   TestEqual("SelectedChoices deve manter 2 escolhas", SelectedChoices.Num(), 2);
               });

            It("deve remover escolhas inválidas",
               [this]()
               {
                   // Arrange
                   TArray<FName> SelectedChoices = {TEXT("Archery"), TEXT("InvalidChoice"), TEXT("Defense")};
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(SelectedChoices,
                                                                                                  ValidChoices);

                   // Assert
                   TestTrue("CleanInvalidAndDuplicateChoices deve retornar true quando remove escolhas inválidas",
                            Result);
                   TestEqual("SelectedChoices deve ter 2 escolhas após limpeza", SelectedChoices.Num(), 2);
                   TestTrue("SelectedChoices deve conter Archery", SelectedChoices.Contains(TEXT("Archery")));
                   TestTrue("SelectedChoices deve conter Defense", SelectedChoices.Contains(TEXT("Defense")));
                   TestFalse("SelectedChoices não deve conter InvalidChoice",
                             SelectedChoices.Contains(TEXT("InvalidChoice")));
               });

            It("deve remover duplicatas",
               [this]()
               {
                   // Arrange
                   TArray<FName> SelectedChoices = {TEXT("Archery"), TEXT("Defense"), TEXT("Archery")};
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(SelectedChoices,
                                                                                                  ValidChoices);

                   // Assert
                   TestTrue("CleanInvalidAndDuplicateChoices deve retornar true quando remove duplicatas", Result);
                   TestEqual("SelectedChoices deve ter 2 escolhas após remoção de duplicatas",
                             SelectedChoices.Num(), 2);
                   // Verifica que não há duplicatas
                   TSet<FName> UniqueSet(SelectedChoices);
                   TestEqual("SelectedChoices deve ter 2 escolhas únicas", UniqueSet.Num(), 2);
               });

            It("deve remover escolhas inválidas e duplicatas simultaneamente",
               [this]()
               {
                   // Arrange
                   TArray<FName> SelectedChoices = {TEXT("Archery"), TEXT("InvalidChoice"), TEXT("Archery"),
                                                     TEXT("Defense")};
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(SelectedChoices,
                                                                                                  ValidChoices);

                   // Assert
                   TestTrue("CleanInvalidAndDuplicateChoices deve retornar true quando remove inválidas e duplicatas",
                            Result);
                   TestEqual("SelectedChoices deve ter 2 escolhas após limpeza", SelectedChoices.Num(), 2);
                   TestTrue("SelectedChoices deve conter Archery", SelectedChoices.Contains(TEXT("Archery")));
                   TestTrue("SelectedChoices deve conter Defense", SelectedChoices.Contains(TEXT("Defense")));
               });

            It("deve retornar false quando array está vazio",
               [this]()
               {
                   // Arrange
                   TArray<FName> SelectedChoices;
                   TArray<FName> ValidChoices = {TEXT("Archery"), TEXT("Defense")};

                   // Act
                   bool Result = FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(SelectedChoices,
                                                                                                  ValidChoices);

                   // Assert
                   TestFalse("CleanInvalidAndDuplicateChoices deve retornar false quando array está vazio", Result);
                   TestEqual("SelectedChoices deve permanecer vazio", SelectedChoices.Num(), 0);
               });
        });
}

#pragma endregion CharacterSheetDataAssetHelpers Tests
