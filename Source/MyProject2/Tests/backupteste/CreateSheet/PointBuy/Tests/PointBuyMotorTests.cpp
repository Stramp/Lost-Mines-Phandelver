// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "CreateSheet/PointBuy/PointBuyOrchestrator.h"
#include "Data/Structures/FCharacterSheetData.h"
#include "Utils/DnDConstants.h"

#pragma endregion Includes

// ============================================================================
// PointBuyMotor Tests
// ============================================================================
#pragma region PointBuyMotor Tests

BEGIN_DEFINE_SPEC(PointBuyMotorSpec, "MyProject2.CreateSheet.PointBuy.PointBuyMotor",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

int32 TestFinalStrength;
int32 TestFinalDexterity;
int32 TestFinalConstitution;
int32 TestFinalIntelligence;
int32 TestFinalWisdom;
int32 TestFinalCharisma;

END_DEFINE_SPEC(PointBuyMotorSpec)

void PointBuyMotorSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Inicializar Final Scores com valores base
            TestFinalStrength = DnDConstants::BASE_ABILITY_SCORE;
            TestFinalDexterity = DnDConstants::BASE_ABILITY_SCORE;
            TestFinalConstitution = DnDConstants::BASE_ABILITY_SCORE;
            TestFinalIntelligence = DnDConstants::BASE_ABILITY_SCORE;
            TestFinalWisdom = DnDConstants::BASE_ABILITY_SCORE;
            TestFinalCharisma = DnDConstants::BASE_ABILITY_SCORE;
        });

    Describe("ApplyPointBuy",
             [this]()
             {
                 It("deve aplicar Point Buy válido sem ajuste (exatamente 27 pontos)",
                    [this]()
                    {
                        // Arrange: Alocação válida que gasta exatamente 27 pontos
                        FCharacterSheetData Data;
                        Data.PointBuyStrength = 7;     // Score 15 = 9 pontos
                        Data.PointBuyDexterity = 6;    // Score 14 = 7 pontos
                        Data.PointBuyConstitution = 5; // Score 13 = 5 pontos
                        Data.PointBuyIntelligence = 4; // Score 12 = 4 pontos
                        Data.PointBuyWisdom = 2;       // Score 10 = 2 pontos
                        Data.PointBuyCharisma = 0;     // Score 8 = 0 pontos
                        // Total: 9 + 7 + 5 + 4 + 2 + 0 = 27 pontos

                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FPointBuyResult Result = FPointBuyOrchestrator::ProcessPointBuy(Data);

                        // Assert: Valores hardcoded conhecidos
                        TestTrue("Resultado deve ser válido", Result.bIsValid);
                        TestFalse("Não deve ter sido ajustado", Result.bWasAutoAdjusted);
                        TestEqual("Pontos restantes devem ser 0", Result.PointsRemaining, 0);
                        TestEqual("Final Strength deve ser 15", TestFinalStrength, 15);
                        TestEqual("Final Dexterity deve ser 14", TestFinalDexterity, 14);
                        TestEqual("Final Constitution deve ser 13", TestFinalConstitution, 13);
                        TestEqual("Final Intelligence deve ser 12", TestFinalIntelligence, 12);
                        TestEqual("Final Wisdom deve ser 10", TestFinalWisdom, 10);
                        TestEqual("Final Charisma deve ser 8", TestFinalCharisma, 8);
                    });

                 It("deve ajustar automaticamente quando excede 27 pontos",
                    [this]()
                    {
                        // Arrange: Alocação que excede 27 pontos
                        FCharacterSheetData Data;
                        Data.PointBuyStrength = 7;     // Score 15 = 9 pontos
                        Data.PointBuyDexterity = 7;    // Score 15 = 9 pontos
                        Data.PointBuyConstitution = 7; // Score 15 = 9 pontos
                        Data.PointBuyIntelligence = 7; // Score 15 = 9 pontos
                        Data.PointBuyWisdom = 7;       // Score 15 = 9 pontos
                        Data.PointBuyCharisma = 7;     // Score 15 = 9 pontos
                        // Total: 9 * 6 = 54 pontos (excede 27)

                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FPointBuyResult Result = FPointBuyOrchestrator::ProcessPointBuy(Data);

                        // Assert
                        TestTrue("Resultado deve ser válido", Result.bIsValid);
                        TestTrue("Deve ter sido ajustado", Result.bWasAutoAdjusted);
                        TestEqual("Pontos restantes devem ser 0 após ajuste", Result.PointsRemaining, 0);
                        TestTrue("FeedbackMessage não deve estar vazio", !Result.FeedbackMessage.IsEmpty());
                    });

                 It("deve retornar resultado vazio quando referências são inválidas",
                    [this]()
                    {
                        // Arrange: Referências nulas
                        FCharacterSheetData Data;
                        Data.PointBuyStrength = 3;
                        Data.FinalStrength = nullptr; // Inválido

                        // Act
                        FPointBuyResult Result = FPointBuyOrchestrator::ProcessPointBuy(Data);

                        // Assert
                        TestFalse("Resultado não deve ser válido (referências inválidas)", Result.bIsValid);
                        TestFalse("Não deve ter sido ajustado", Result.bWasAutoAdjusted);
                        TestEqual("Pontos restantes devem ser 0", Result.PointsRemaining, 0);
                    });

                 It("deve calcular pontos restantes quando não gasta todos os pontos",
                    [this]()
                    {
                        // Arrange: Alocação que gasta menos de 27 pontos
                        FCharacterSheetData Data;
                        Data.PointBuyStrength = 0;     // Score 8 = 0 pontos
                        Data.PointBuyDexterity = 0;    // Score 8 = 0 pontos
                        Data.PointBuyConstitution = 0; // Score 8 = 0 pontos
                        Data.PointBuyIntelligence = 0; // Score 8 = 0 pontos
                        Data.PointBuyWisdom = 0;       // Score 8 = 0 pontos
                        Data.PointBuyCharisma = 0;     // Score 8 = 0 pontos
                        // Total: 0 pontos (restam 27)

                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FPointBuyResult Result = FPointBuyOrchestrator::ProcessPointBuy(Data);

                        // Assert
                        TestTrue("Resultado deve ser válido", Result.bIsValid);
                        TestFalse("Não deve ter sido ajustado", Result.bWasAutoAdjusted);
                        TestEqual("Pontos restantes devem ser 27", Result.PointsRemaining, 27);
                        TestTrue("FeedbackMessage deve mencionar pontos restantes",
                                 Result.FeedbackMessage.Contains(TEXT("Pontos restantes")));
                    });
             });
}

#pragma endregion PointBuyMotor Tests
