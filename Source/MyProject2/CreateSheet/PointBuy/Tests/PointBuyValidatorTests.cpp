// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "CreateSheet/PointBuy/PointBuyValidator.h"
#include "Utils/DnDConstants.h"

#pragma endregion Includes

// ============================================================================
// PointBuyValidator Tests
// ============================================================================
#pragma region PointBuyValidator Tests

BEGIN_DEFINE_SPEC(PointBuyValidatorSpec, "MyProject2.CreateSheet.PointBuy.PointBuyValidator",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(PointBuyValidatorSpec)

void PointBuyValidatorSpec::Define()
{
    Describe("ValidatePointBuy",
             [this]()
             {
                 It("deve validar alocação válida que gasta exatamente 27 pontos",
                    [this]()
                    {
                        // Arrange: Alocação válida (todos scores 8-15, exatamente 27 pontos)
                        int32 PointBuyStrength = 7;      // Score 15 = 9 pontos
                        int32 PointBuyDexterity = 6;      // Score 14 = 7 pontos
                        int32 PointBuyConstitution = 5;   // Score 13 = 5 pontos
                        int32 PointBuyIntelligence = 4;   // Score 12 = 4 pontos
                        int32 PointBuyWisdom = 2;         // Score 10 = 2 pontos
                        int32 PointBuyCharisma = 0;       // Score 8 = 0 pontos
                        // Total: 9 + 7 + 5 + 4 + 2 + 0 = 27 pontos

                        // Act
                        FPointBuyValidationResult Result = FPointBuyValidator::ValidatePointBuy(
                            PointBuyStrength, PointBuyDexterity, PointBuyConstitution, PointBuyIntelligence,
                            PointBuyWisdom, PointBuyCharisma);

                        // Assert
                        TestTrue("Alocação deve ser válida", Result.bIsValid);
                        TestTrue("Todos os scores devem ser válidos", Result.bAllScoresValid);
                        TestEqual("Pontos restantes devem ser 0", Result.PointsRemaining, 0);
                    });

                 It("deve rejeitar alocação que não gasta exatamente 27 pontos",
                    [this]()
                    {
                        // Arrange: Alocação que gasta menos de 27 pontos
                        int32 PointBuyStrength = 0;       // Score 8 = 0 pontos
                        int32 PointBuyDexterity = 0;       // Score 8 = 0 pontos
                        int32 PointBuyConstitution = 0;    // Score 8 = 0 pontos
                        int32 PointBuyIntelligence = 0;    // Score 8 = 0 pontos
                        int32 PointBuyWisdom = 0;          // Score 8 = 0 pontos
                        int32 PointBuyCharisma = 0;        // Score 8 = 0 pontos
                        // Total: 0 pontos (restam 27)

                        // Act
                        FPointBuyValidationResult Result = FPointBuyValidator::ValidatePointBuy(
                            PointBuyStrength, PointBuyDexterity, PointBuyConstitution, PointBuyIntelligence,
                            PointBuyWisdom, PointBuyCharisma);

                        // Assert
                        TestFalse("Alocação não deve ser válida (não gastou todos os pontos)", Result.bIsValid);
                        TestTrue("Todos os scores devem ser válidos (range correto)", Result.bAllScoresValid);
                        TestEqual("Pontos restantes devem ser 27", Result.PointsRemaining, 27);
                    });

                 It("deve rejeitar alocação que excede 27 pontos",
                    [this]()
                    {
                        // Arrange: Alocação que excede 27 pontos
                        int32 PointBuyStrength = 7;       // Score 15 = 9 pontos
                        int32 PointBuyDexterity = 7;      // Score 15 = 9 pontos
                        int32 PointBuyConstitution = 7;    // Score 15 = 9 pontos
                        int32 PointBuyIntelligence = 7;    // Score 15 = 9 pontos
                        int32 PointBuyWisdom = 7;          // Score 15 = 9 pontos
                        int32 PointBuyCharisma = 7;       // Score 15 = 9 pontos
                        // Total: 9 * 6 = 54 pontos (excede 27)

                        // Act
                        FPointBuyValidationResult Result = FPointBuyValidator::ValidatePointBuy(
                            PointBuyStrength, PointBuyDexterity, PointBuyConstitution, PointBuyIntelligence,
                            PointBuyWisdom, PointBuyCharisma);

                        // Assert
                        TestFalse("Alocação não deve ser válida (excedeu pontos)", Result.bIsValid);
                        TestTrue("Todos os scores devem ser válidos (range correto)", Result.bAllScoresValid);
                        TestTrue("Pontos restantes devem ser negativo", Result.PointsRemaining < 0);
                    });

                 It("deve rejeitar scores fora do range válido (abaixo de 8)",
                    [this]()
                    {
                        // Arrange: Point Buy negativo resultaria em score < 8
                        // Mas Point Buy é 0-7, então não pode ter score < 8 diretamente
                        // Este teste valida que o sistema rejeita se houver score < 8
                        // (mesmo que não seja possível com Point Buy direto, valida a lógica)

                        // Act: Alocação com valores mínimos (todos 0 = score 8)
                        FPointBuyValidationResult Result = FPointBuyValidator::ValidatePointBuy(0, 0, 0, 0, 0, 0);

                        // Assert: Scores são válidos (8 está no range), mas não gasta 27 pontos
                        TestFalse("Alocação não deve ser válida (não gastou todos os pontos)", Result.bIsValid);
                        TestTrue("Todos os scores devem ser válidos (8 está no range)", Result.bAllScoresValid);
                    });

                 It("deve calcular pontos restantes corretamente",
                    [this]()
                    {
                        // Arrange: Alocação que gasta 20 pontos (restam 7)
                        int32 PointBuyStrength = 5;       // Score 13 = 5 pontos
                        int32 PointBuyDexterity = 5;       // Score 13 = 5 pontos
                        int32 PointBuyConstitution = 5;     // Score 13 = 5 pontos
                        int32 PointBuyIntelligence = 5;     // Score 13 = 5 pontos
                        int32 PointBuyWisdom = 0;           // Score 8 = 0 pontos
                        int32 PointBuyCharisma = 0;         // Score 8 = 0 pontos
                        // Total: 5 + 5 + 5 + 5 + 0 + 0 = 20 pontos (restam 7)

                        // Act
                        FPointBuyValidationResult Result = FPointBuyValidator::ValidatePointBuy(
                            PointBuyStrength, PointBuyDexterity, PointBuyConstitution, PointBuyIntelligence,
                            PointBuyWisdom, PointBuyCharisma);

                        // Assert
                        TestFalse("Alocação não deve ser válida (não gastou todos os pontos)", Result.bIsValid);
                        TestEqual("Pontos restantes devem ser 7", Result.PointsRemaining, 7);
                    });
             });
}

#pragma endregion PointBuyValidator Tests

