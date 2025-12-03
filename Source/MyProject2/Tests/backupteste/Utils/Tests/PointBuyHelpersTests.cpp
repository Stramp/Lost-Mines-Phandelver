// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/PointBuyHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DnDConstants.h"

#pragma endregion Includes

// ============================================================================
// PointBuyHelpers Tests
// ============================================================================
#pragma region PointBuyHelpers Tests

BEGIN_DEFINE_SPEC(PointBuyHelpersSpec, "MyProject2.Utils.PointBuyHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(PointBuyHelpersSpec)

void PointBuyHelpersSpec::Define()
{
    Describe("CalculatePointBuyCost",
             [this]()
             {
                 It("deve retornar 0 para score 8 (0 pontos)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 8;
                        int32 ExpectedCost = 0; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculatePointBuyCost(Score);

                        // Assert
                        TestEqual("Score 8 deve custar 0 pontos", Result, ExpectedCost);
                    });

                 It("deve retornar custo correto para score 9 (1 ponto)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 9;
                        int32 ExpectedCost = 1; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculatePointBuyCost(Score);

                        // Assert
                        TestEqual("Score 9 deve custar 1 ponto", Result, ExpectedCost);
                    });

                 It("deve retornar custo correto para score 10 (2 pontos)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 10;
                        int32 ExpectedCost = 2; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculatePointBuyCost(Score);

                        // Assert
                        TestEqual("Score 10 deve custar 2 pontos", Result, ExpectedCost);
                    });

                 It("deve retornar custo correto para score 13 (5 pontos)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 13;
                        int32 ExpectedCost = 5; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculatePointBuyCost(Score);

                        // Assert
                        TestEqual("Score 13 deve custar 5 pontos", Result, ExpectedCost);
                    });

                 It("deve retornar 7 para score 14 (7 pontos)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 14;
                        int32 ExpectedCost = 7; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculatePointBuyCost(Score);

                        // Assert
                        TestEqual("Score 14 deve custar 7 pontos", Result, ExpectedCost);
                    });

                 It("deve retornar 9 para score 15 (9 pontos)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 15;
                        int32 ExpectedCost = 9; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculatePointBuyCost(Score);

                        // Assert
                        TestEqual("Score 15 deve custar 9 pontos", Result, ExpectedCost);
                    });

                 It("deve retornar 0 para score inválido (< 8)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 7;
                        int32 ExpectedCost = 0; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculatePointBuyCost(Score);

                        // Assert
                        TestEqual("Score inválido (< 8) deve retornar 0", Result, ExpectedCost);
                    });

                 It("deve retornar 0 para score inválido (> 15)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 16;
                        int32 ExpectedCost = 0; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculatePointBuyCost(Score);

                        // Assert
                        TestEqual("Score inválido (> 15) deve retornar 0", Result, ExpectedCost);
                    });
             });

    Describe("CalculateTotalPointBuyCost",
             [this]()
             {
                 It("deve calcular custo total correto para ability scores válidos (27 pontos)",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> AbilityScores;
                        AbilityScores.Add(TEXT("Strength"), 15);
                        AbilityScores.Add(TEXT("Dexterity"), 14);
                        AbilityScores.Add(TEXT("Constitution"), 13);
                        AbilityScores.Add(TEXT("Intelligence"), 12);
                        AbilityScores.Add(TEXT("Wisdom"), 10);
                        AbilityScores.Add(TEXT("Charisma"), 8);
                        int32 ExpectedTotalCost = 27; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculateTotalPointBuyCost(AbilityScores);

                        // Assert
                        TestEqual("Custo total deve ser 27 pontos", Result, ExpectedTotalCost);
                    });

                 It("deve retornar 0 para map vazio",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> EmptyScores;
                        int32 ExpectedTotalCost = 0; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculateTotalPointBuyCost(EmptyScores);

                        // Assert
                        TestEqual("Map vazio deve retornar 0", Result, ExpectedTotalCost);
                    });

                 It("deve ignorar scores inválidos no cálculo (retorna 0 para inválidos)",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> AbilityScores;
                        AbilityScores.Add(TEXT("Strength"), 15);
                        AbilityScores.Add(TEXT("Dexterity"), 7); // Inválido, retorna 0
                        AbilityScores.Add(TEXT("Constitution"), 8);
                        int32 ExpectedTotalCost = 9; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculateTotalPointBuyCost(AbilityScores);

                        // Assert
                        TestEqual("Scores inválidos devem ser ignorados (retornar 0)", Result, ExpectedTotalCost);
                    });

                 It("deve calcular custo para todos os scores mínimos (8) = 0 pontos",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> AbilityScores;
                        AbilityScores.Add(TEXT("Strength"), 8);
                        AbilityScores.Add(TEXT("Dexterity"), 8);
                        AbilityScores.Add(TEXT("Constitution"), 8);
                        AbilityScores.Add(TEXT("Intelligence"), 8);
                        AbilityScores.Add(TEXT("Wisdom"), 8);
                        AbilityScores.Add(TEXT("Charisma"), 8);
                        int32 ExpectedTotalCost = 0; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculateTotalPointBuyCost(AbilityScores);

                        // Assert
                        TestEqual("Todos os scores mínimos (8) devem custar 0 pontos", Result, ExpectedTotalCost);
                    });

                 It("deve calcular custo para todos os scores máximos (15) = 54 pontos",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> AbilityScores;
                        AbilityScores.Add(TEXT("Strength"), 15);
                        AbilityScores.Add(TEXT("Dexterity"), 15);
                        AbilityScores.Add(TEXT("Constitution"), 15);
                        AbilityScores.Add(TEXT("Intelligence"), 15);
                        AbilityScores.Add(TEXT("Wisdom"), 15);
                        AbilityScores.Add(TEXT("Charisma"), 15);
                        int32 ExpectedTotalCost = 54; // Valor hardcoded conhecido

                        // Act
                        int32 Result = PointBuyHelpers::CalculateTotalPointBuyCost(AbilityScores);

                        // Assert
                        TestEqual("Todos os scores máximos (15) devem custar 54 pontos", Result, ExpectedTotalCost);
                    });
             });

    Describe("CalculatePointsRemaining",
             [this]()
             {
                 It("deve calcular pontos restantes corretamente para alocação válida",
                    [this]()
                    {
                        // Arrange: Alocação que gasta 20 pontos
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 5);
                        PointBuyMap.Add(TEXT("Dexterity"), 5);
                        PointBuyMap.Add(TEXT("Constitution"), 5);
                        PointBuyMap.Add(TEXT("Intelligence"), 5);
                        PointBuyMap.Add(TEXT("Wisdom"), 0);
                        PointBuyMap.Add(TEXT("Charisma"), 0);
                        int32 ExpectedPointsRemaining = 7; // Valor hardcoded conhecido

                        // Act
                        int32 Result =
                            PointBuyHelpers::CalculatePointsRemaining(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                        // Assert
                        TestEqual("Pontos restantes devem ser 7", Result, ExpectedPointsRemaining);
                    });

                 It("deve retornar negativo quando excede pontos máximos",
                    [this]()
                    {
                        // Arrange: Alocação que excede 27 pontos
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 7);
                        PointBuyMap.Add(TEXT("Dexterity"), 7);
                        PointBuyMap.Add(TEXT("Constitution"), 7);
                        PointBuyMap.Add(TEXT("Intelligence"), 7);
                        PointBuyMap.Add(TEXT("Wisdom"), 7);
                        PointBuyMap.Add(TEXT("Charisma"), 7);
                        int32 ExpectedPointsRemaining = -27; // Valor hardcoded conhecido

                        // Act
                        int32 Result =
                            PointBuyHelpers::CalculatePointsRemaining(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                        // Assert
                        TestTrue("Pontos restantes devem ser negativo", Result < 0);
                        TestEqual("Pontos restantes devem ser -27", Result, ExpectedPointsRemaining);
                    });

                 It("deve retornar 0 quando gasta exatamente pontos máximos",
                    [this]()
                    {
                        // Arrange: Alocação que gasta exatamente 27 pontos
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 7);
                        PointBuyMap.Add(TEXT("Dexterity"), 6);
                        PointBuyMap.Add(TEXT("Constitution"), 5);
                        PointBuyMap.Add(TEXT("Intelligence"), 4);
                        PointBuyMap.Add(TEXT("Wisdom"), 2);
                        PointBuyMap.Add(TEXT("Charisma"), 0);
                        int32 ExpectedPointsRemaining = 0; // Valor hardcoded conhecido

                        // Act
                        int32 Result =
                            PointBuyHelpers::CalculatePointsRemaining(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                        // Assert
                        TestEqual("Pontos restantes devem ser 0", Result, ExpectedPointsRemaining);
                    });
             });

    Describe("AdjustPointBuyAllocation",
             [this]()
             {
                 It("deve ajustar alocação que excede pontos máximos",
                    [this]()
                    {
                        // Arrange: Alocação que excede 27 pontos
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 7);
                        PointBuyMap.Add(TEXT("Dexterity"), 7);
                        PointBuyMap.Add(TEXT("Constitution"), 7);
                        PointBuyMap.Add(TEXT("Intelligence"), 7);
                        PointBuyMap.Add(TEXT("Wisdom"), 7);
                        PointBuyMap.Add(TEXT("Charisma"), 7);

                        // Act
                        FString Result =
                            PointBuyHelpers::AdjustPointBuyAllocation(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                        // Assert
                        TestTrue("Mensagem não deve estar vazia", !Result.IsEmpty());
                        TMap<FName, int32> BaseScores =
                            CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
                        int32 TotalCost = PointBuyHelpers::CalculateTotalPointBuyCost(BaseScores);
                        const int32 MaxPoints = DnDConstants::MAX_POINT_BUY_POINTS;
                        TestTrue("Custo total deve ser <= 27 após ajuste", TotalCost <= MaxPoints);
                    });

                 It("deve retornar mensagem de sucesso quando ajusta completamente",
                    [this]()
                    {
                        // Arrange: Alocação que excede 27 pontos (mas pode ser ajustada)
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 7);
                        PointBuyMap.Add(TEXT("Dexterity"), 7);
                        PointBuyMap.Add(TEXT("Constitution"), 7);
                        PointBuyMap.Add(TEXT("Intelligence"), 7);
                        PointBuyMap.Add(TEXT("Wisdom"), 7);
                        PointBuyMap.Add(TEXT("Charisma"), 7);
                        const FString ExpectedKeyword = TEXT("ajustada");

                        // Act
                        FString Result =
                            PointBuyHelpers::AdjustPointBuyAllocation(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                        // Assert
                        TestTrue("Mensagem deve mencionar ajuste", Result.Contains(ExpectedKeyword));
                    });

                 It("deve manter alocação válida sem alterações",
                    [this]()
                    {
                        // Arrange: Alocação válida que não excede 27 pontos
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 0);
                        PointBuyMap.Add(TEXT("Dexterity"), 0);
                        PointBuyMap.Add(TEXT("Constitution"), 0);
                        PointBuyMap.Add(TEXT("Intelligence"), 0);
                        PointBuyMap.Add(TEXT("Wisdom"), 0);
                        PointBuyMap.Add(TEXT("Charisma"), 0);
                        const int32 ExpectedValue = 0;
                        TMap<FName, int32> OriginalMap = PointBuyMap;

                        // Act
                        FString Result =
                            PointBuyHelpers::AdjustPointBuyAllocation(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                        // Assert
                        for (const auto &Pair : OriginalMap)
                        {
                            TestEqual(FString::Printf(TEXT("%s deve permanecer 0"), *Pair.Key.ToString()),
                                      PointBuyMap.FindRef(Pair.Key), ExpectedValue);
                        }
                    });
             });
}

#pragma endregion PointBuyHelpers Tests
