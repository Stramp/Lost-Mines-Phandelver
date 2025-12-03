// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "CreateSheet/Multiclass/MulticlassValidators.h"
#include "Data/Structures/FMulticlassRequirement.h"
#include "Data/Tables/AbilityScoreDataTable.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// MulticlassValidators Tests - Normalized Structure
// ============================================================================
#pragma region MulticlassValidators Tests

BEGIN_DEFINE_SPEC(MulticlassValidatorsSpec, "MyProject2.CreateSheet.MulticlassValidators",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UDataTable *AbilityScoreDataTable;

END_DEFINE_SPEC(MulticlassValidatorsSpec)

void MulticlassValidatorsSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Cria Data Table mock de Ability Scores
            AbilityScoreDataTable = NewObject<UDataTable>();
            AbilityScoreDataTable->RowStruct = FAbilityScoreDataRow::StaticStruct();

            // Adiciona rows de teste
            FAbilityScoreDataRow *StrRow = new FAbilityScoreDataRow();
            StrRow->Name = TEXT("Strength");
            StrRow->ID = TEXT("ABL_Strength");
            StrRow->Abbreviation = TEXT("STR");
            AbilityScoreDataTable->AddRow(TEXT("ABL_Strength"), *StrRow);

            FAbilityScoreDataRow *DexRow = new FAbilityScoreDataRow();
            DexRow->Name = TEXT("Dexterity");
            DexRow->ID = TEXT("ABL_Dexterity");
            DexRow->Abbreviation = TEXT("DEX");
            AbilityScoreDataTable->AddRow(TEXT("ABL_Dexterity"), *DexRow);

            FAbilityScoreDataRow *IntRow = new FAbilityScoreDataRow();
            IntRow->Name = TEXT("Intelligence");
            IntRow->ID = TEXT("ABL_Intelligence");
            IntRow->Abbreviation = TEXT("INT");
            AbilityScoreDataTable->AddRow(TEXT("ABL_Intelligence"), *IntRow);
        });

    Describe("ValidateRequirement",
             [this]()
             {
                 It("deve validar requisito quando atributo atende valor mínimo (STR 13 com valor 15)",
                    [this]()
                    {
                        // Arrange
                        FMulticlassRequirement Requirement(TEXT("ABL_Strength"), 13);
                        TArray<int32> Attributes = {15, 12, 14, 10, 11, 13}; // [STR, DEX, CON, INT, WIS, CHA]
                        FString MissingTag;

                        // Act
                        bool Result = FMulticlassValidators::ValidateRequirement(Requirement, Attributes,
                                                                                 AbilityScoreDataTable, MissingTag);

                        // Assert
                        TestTrue("Requisito deve ser válido quando STR >= 13", Result);
                    });

                 It("deve rejeitar requisito quando atributo está abaixo do valor mínimo (STR 13 com valor 12)",
                    [this]()
                    {
                        // Arrange
                        FMulticlassRequirement Requirement(TEXT("ABL_Strength"), 13);
                        TArray<int32> Attributes = {12, 14, 14, 10, 11, 13}; // STR = 12 < 13
                        FString MissingTag;

                        // Act
                        bool Result = FMulticlassValidators::ValidateRequirement(Requirement, Attributes,
                                                                                 AbilityScoreDataTable, MissingTag);

                        // Assert
                        TestFalse("Requisito deve ser inválido quando STR < 13", Result);
                        TestTrue("MissingTag deve conter informação do requisito faltante",
                                 MissingTag.Contains(TEXT("STR")) || MissingTag.Contains(TEXT("+1")));
                    });

                 It("deve rejeitar quando AbilityID não existe no DataTable",
                    [this]()
                    {
                        // Arrange
                        FMulticlassRequirement Requirement(TEXT("ABL_Invalid"), 13);
                        TArray<int32> Attributes = {15, 12, 14, 10, 11, 13};
                        FString MissingTag;

                        // Act
                        bool Result = FMulticlassValidators::ValidateRequirement(Requirement, Attributes,
                                                                                 AbilityScoreDataTable, MissingTag);

                        // Assert
                        TestFalse("Requisito deve ser inválido quando AbilityID não existe", Result);
                    });

                 It("deve rejeitar quando AbilityScoreDataTable é nullptr",
                    [this]()
                    {
                        // Arrange
                        FMulticlassRequirement Requirement(TEXT("ABL_Strength"), 13);
                        TArray<int32> Attributes = {15, 12, 14, 10, 11, 13};
                        FString MissingTag;

                        // Act
                        bool Result =
                            FMulticlassValidators::ValidateRequirement(Requirement, Attributes, nullptr, MissingTag);

                        // Assert
                        TestFalse("Requisito deve ser inválido quando DataTable é nullptr", Result);
                    });
             });

    Describe("ValidateRequirementGroup - OR Operator",
             [this]()
             {
                 It("deve validar grupo OR quando pelo menos um requisito é satisfeito (STR 13 OU DEX 13)",
                    [this]()
                    {
                        // Arrange
                        FMulticlassRequirementGroup Group;
                        Group.Operator = TEXT("OR");
                        Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Strength"), 13));
                        Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Dexterity"), 13));

                        // STR = 15 (satisfaz), DEX = 12 (não satisfaz)
                        TArray<int32> Attributes = {15, 12, 14, 10, 11, 13};
                        FString MissingTag;

                        // Act
                        bool Result = FMulticlassValidators::ValidateRequirementGroup(
                            Group, Attributes, AbilityScoreDataTable, MissingTag);

                        // Assert
                        TestTrue("Grupo OR deve ser válido quando pelo menos um requisito é satisfeito", Result);
                    });

                 It("deve rejeitar grupo OR quando nenhum requisito é satisfeito",
                    [this]()
                    {
                        // Arrange
                        FMulticlassRequirementGroup Group;
                        Group.Operator = TEXT("OR");
                        Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Strength"), 13));
                        Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Dexterity"), 13));

                        // STR = 12, DEX = 12 (ambos abaixo de 13)
                        TArray<int32> Attributes = {12, 12, 14, 10, 11, 13};
                        FString MissingTag;

                        // Act
                        bool Result = FMulticlassValidators::ValidateRequirementGroup(
                            Group, Attributes, AbilityScoreDataTable, MissingTag);

                        // Assert
                        TestFalse("Grupo OR deve ser inválido quando nenhum requisito é satisfeito", Result);
                    });
             });

    Describe(
        "ValidateRequirementGroup - AND Operator",
        [this]()
        {
            It("deve validar grupo AND quando todos os requisitos são satisfeitos",
               [this]()
               {
                   // Arrange
                   FMulticlassRequirementGroup Group;
                   Group.Operator = TEXT("AND");
                   Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Strength"), 13));
                   Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Intelligence"), 13));

                   // STR = 15, INT = 15 (ambos >= 13)
                   TArray<int32> Attributes = {15, 12, 14, 15, 11, 13};
                   FString MissingTag;

                   // Act
                   bool Result = FMulticlassValidators::ValidateRequirementGroup(Group, Attributes,
                                                                                 AbilityScoreDataTable, MissingTag);

                   // Assert
                   TestTrue("Grupo AND deve ser válido quando todos os requisitos são satisfeitos", Result);
               });

            It("deve rejeitar grupo AND quando pelo menos um requisito não é satisfeito",
               [this]()
               {
                   // Arrange
                   FMulticlassRequirementGroup Group;
                   Group.Operator = TEXT("AND");
                   Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Strength"), 13));
                   Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Intelligence"), 13));

                   // STR = 15 (satisfaz), INT = 12 (não satisfaz)
                   TArray<int32> Attributes = {15, 12, 14, 12, 11, 13};
                   FString MissingTag;

                   // Act
                   bool Result = FMulticlassValidators::ValidateRequirementGroup(Group, Attributes,
                                                                                 AbilityScoreDataTable, MissingTag);

                   // Assert
                   TestFalse("Grupo AND deve ser inválido quando pelo menos um requisito não é satisfeito", Result);
               });
        });

    Describe("ValidateMulticlassRequirementGroups",
             [this]()
             {
                 It("deve validar múltiplos grupos quando todos são satisfeitos (lógica AND entre grupos)",
                    [this]()
                    {
                        // Arrange
                        TArray<FMulticlassRequirementGroup> Groups;

                        // Grupo 1: STR 13 OU DEX 13
                        FMulticlassRequirementGroup Group1;
                        Group1.Operator = TEXT("OR");
                        Group1.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Strength"), 13));
                        Group1.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Dexterity"), 13));
                        Groups.Add(Group1);

                        // Grupo 2: INT 13
                        FMulticlassRequirementGroup Group2;
                        Group2.Operator = TEXT("AND");
                        Group2.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Intelligence"), 13));
                        Groups.Add(Group2);

                        // STR = 15 (satisfaz Grupo 1), INT = 15 (satisfaz Grupo 2)
                        TArray<int32> Attributes = {15, 12, 14, 15, 11, 13};
                        FString MissingTag;

                        // Act
                        bool Result = FMulticlassValidators::ValidateMulticlassRequirementGroups(
                            Groups, Attributes, AbilityScoreDataTable, MissingTag);

                        // Assert
                        TestTrue("Todos os grupos devem ser válidos quando requisitos são satisfeitos", Result);
                    });

                 It("deve rejeitar quando pelo menos um grupo não é satisfeito",
                    [this]()
                    {
                        // Arrange
                        TArray<FMulticlassRequirementGroup> Groups;

                        // Grupo 1: STR 13 OU DEX 13
                        FMulticlassRequirementGroup Group1;
                        Group1.Operator = TEXT("OR");
                        Group1.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Strength"), 13));
                        Group1.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Dexterity"), 13));
                        Groups.Add(Group1);

                        // Grupo 2: INT 13
                        FMulticlassRequirementGroup Group2;
                        Group2.Operator = TEXT("AND");
                        Group2.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Intelligence"), 13));
                        Groups.Add(Group2);

                        // STR = 15 (satisfaz Grupo 1), INT = 12 (não satisfaz Grupo 2)
                        TArray<int32> Attributes = {15, 12, 14, 12, 11, 13};
                        FString MissingTag;

                        // Act
                        bool Result = FMulticlassValidators::ValidateMulticlassRequirementGroups(
                            Groups, Attributes, AbilityScoreDataTable, MissingTag);

                        // Assert
                        TestFalse("Deve rejeitar quando pelo menos um grupo não é satisfeito", Result);
                    });

                 It("deve validar grupo vazio como válido",
                    [this]()
                    {
                        // Arrange
                        TArray<FMulticlassRequirementGroup> Groups;
                        TArray<int32> Attributes = {15, 12, 14, 10, 11, 13};
                        FString MissingTag;

                        // Act
                        bool Result = FMulticlassValidators::ValidateMulticlassRequirementGroups(
                            Groups, Attributes, AbilityScoreDataTable, MissingTag);

                        // Assert
                        TestTrue("Grupos vazios devem ser válidos", Result);
                    });
             });
}

#pragma endregion MulticlassValidators Tests
