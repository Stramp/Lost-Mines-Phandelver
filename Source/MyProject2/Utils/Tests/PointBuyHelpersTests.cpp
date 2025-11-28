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
    Describe("CalculatePointsRemaining",
             [this]()
             {
                 It("deve calcular pontos restantes corretamente para alocação válida",
                    [this]()
                    {
                        // Arrange: Alocação que gasta 20 pontos (restam 7)
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 5);     // Score 13 = 5 pontos
                        PointBuyMap.Add(TEXT("Dexterity"), 5);    // Score 13 = 5 pontos
                        PointBuyMap.Add(TEXT("Constitution"), 5); // Score 13 = 5 pontos
                        PointBuyMap.Add(TEXT("Intelligence"), 5); // Score 13 = 5 pontos
                        PointBuyMap.Add(TEXT("Wisdom"), 0);       // Score 8 = 0 pontos
                        PointBuyMap.Add(TEXT("Charisma"), 0);     // Score 8 = 0 pontos
                        // Total: 5 + 5 + 5 + 5 + 0 + 0 = 20 pontos (restam 7)

                        // Act
                        int32 Result =
                            PointBuyHelpers::CalculatePointsRemaining(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                        // Assert
                        TestEqual("Pontos restantes devem ser 7", Result, 7);
                    });

                 It("deve retornar negativo quando excede pontos máximos",
                    [this]()
                    {
                        // Arrange: Alocação que excede 27 pontos
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 7);     // Score 15 = 9 pontos
                        PointBuyMap.Add(TEXT("Dexterity"), 7);    // Score 15 = 9 pontos
                        PointBuyMap.Add(TEXT("Constitution"), 7); // Score 15 = 9 pontos
                        PointBuyMap.Add(TEXT("Intelligence"), 7); // Score 15 = 9 pontos
                        PointBuyMap.Add(TEXT("Wisdom"), 7);       // Score 15 = 9 pontos
                        PointBuyMap.Add(TEXT("Charisma"), 7);     // Score 15 = 9 pontos
                        // Total: 9 * 6 = 54 pontos (excede 27 por 27)

                        // Act
                        int32 Result =
                            PointBuyHelpers::CalculatePointsRemaining(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                        // Assert
                        TestTrue("Pontos restantes devem ser negativo", Result < 0);
                        TestEqual("Pontos restantes devem ser -27", Result, -27);
                    });

                 It("deve retornar 0 quando gasta exatamente pontos máximos",
                    [this]()
                    {
                        // Arrange: Alocação que gasta exatamente 27 pontos
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 7);     // Score 15 = 9 pontos
                        PointBuyMap.Add(TEXT("Dexterity"), 6);    // Score 14 = 7 pontos
                        PointBuyMap.Add(TEXT("Constitution"), 5); // Score 13 = 5 pontos
                        PointBuyMap.Add(TEXT("Intelligence"), 4); // Score 12 = 4 pontos
                        PointBuyMap.Add(TEXT("Wisdom"), 2);       // Score 10 = 2 pontos
                        PointBuyMap.Add(TEXT("Charisma"), 0);     // Score 8 = 0 pontos
                        // Total: 9 + 7 + 5 + 4 + 2 + 0 = 27 pontos

                        // Act
                        int32 Result =
                            PointBuyHelpers::CalculatePointsRemaining(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                        // Assert
                        TestEqual("Pontos restantes devem ser 0", Result, 0);
                    });
             });

    Describe(
        "AdjustPointBuyAllocation",
        [this]()
        {
            It("deve ajustar alocação que excede pontos máximos",
               [this]()
               {
                   // Arrange: Alocação que excede 27 pontos
                   TMap<FName, int32> PointBuyMap;
                   PointBuyMap.Add(TEXT("Strength"), 7);     // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Dexterity"), 7);    // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Constitution"), 7); // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Intelligence"), 7); // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Wisdom"), 7);       // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Charisma"), 7);     // Score 15 = 9 pontos
                   // Total: 9 * 6 = 54 pontos (excede 27)

                   // Act
                   FString Result =
                       PointBuyHelpers::AdjustPointBuyAllocation(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestTrue("Mensagem não deve estar vazia", !Result.IsEmpty());
                   // Verifica que reduziu (não precisa verificar valor exato, apenas que ajustou)
                   TMap<FName, int32> BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
                   int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
                   TestTrue("Custo total deve ser <= 27 após ajuste", TotalCost <= DnDConstants::MAX_POINT_BUY_POINTS);
               });

            It("deve retornar mensagem de sucesso quando ajusta completamente",
               [this]()
               {
                   // Arrange: Alocação que excede 27 pontos (mas pode ser ajustada)
                   TMap<FName, int32> PointBuyMap;
                   PointBuyMap.Add(TEXT("Strength"), 7);     // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Dexterity"), 7);    // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Constitution"), 7); // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Intelligence"), 7); // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Wisdom"), 7);       // Score 15 = 9 pontos
                   PointBuyMap.Add(TEXT("Charisma"), 7);     // Score 15 = 9 pontos

                   // Act
                   FString Result =
                       PointBuyHelpers::AdjustPointBuyAllocation(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestTrue("Mensagem deve mencionar ajuste", Result.Contains(TEXT("ajustada")));
               });

            It("deve manter alocação válida sem alterações",
               [this]()
               {
                   // Arrange: Alocação válida que não excede 27 pontos
                   TMap<FName, int32> PointBuyMap;
                   PointBuyMap.Add(TEXT("Strength"), 0);     // Score 8 = 0 pontos
                   PointBuyMap.Add(TEXT("Dexterity"), 0);    // Score 8 = 0 pontos
                   PointBuyMap.Add(TEXT("Constitution"), 0); // Score 8 = 0 pontos
                   PointBuyMap.Add(TEXT("Intelligence"), 0); // Score 8 = 0 pontos
                   PointBuyMap.Add(TEXT("Wisdom"), 0);       // Score 8 = 0 pontos
                   PointBuyMap.Add(TEXT("Charisma"), 0);     // Score 8 = 0 pontos
                   // Total: 0 pontos (não excede)

                   TMap<FName, int32> OriginalMap = PointBuyMap;

                   // Act
                   FString Result =
                       PointBuyHelpers::AdjustPointBuyAllocation(PointBuyMap, DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   // Verifica que não alterou (todos valores devem ser 0)
                   for (const auto &Pair : OriginalMap)
                   {
                       TestEqual(FString::Printf(TEXT("%s deve permanecer 0"), *Pair.Key.ToString()),
                                 PointBuyMap.FindRef(Pair.Key), 0);
                   }
               });
        });
}

#pragma endregion PointBuyHelpers Tests
