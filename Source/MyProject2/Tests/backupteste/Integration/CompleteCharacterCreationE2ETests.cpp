// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Characters/Components/CharacterSheetComponent.h"
#include "Characters/Components/CharacterDataComponent.h"
#include "GameFramework/Actor.h"
#include "Utils/DnDConstants.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Data/Structures/MulticlassTypes.h"

#pragma endregion Includes

// ============================================================================
// Complete Character Creation End-to-End Tests
// ============================================================================
#pragma region Complete Character Creation End-to-End Tests

/**
 * Teste de integração completo para processo de criação de ficha D&D 5e.
 *
 * Valida todos os 6 passos do processo de criação:
 * 1. Choose a Race
 * 2. Choose a Class
 * 3. Determine Ability Scores
 * 4. Describe Your Character
 * 5. Choose Equipment
 * 6. Finalize Character
 *
 * Este teste garante que o sistema completo funciona corretamente seguindo
 * as regras do D&D 5e conforme documentação oficial.
 */
BEGIN_DEFINE_SPEC(CompleteCharacterCreationE2ESpec, "MyProject2.Integration.CompleteCharacterCreation",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UCharacterSheetDataAsset* TestDataAsset;
AActor* TestActor;
UCharacterSheetComponent* TestSheetComponent;
UCharacterDataComponent* TestDataComponent;

END_DEFINE_SPEC(CompleteCharacterCreationE2ESpec)

void CompleteCharacterCreationE2ESpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar Actor e Componentes para cada teste
            TestActor = NewObject<AActor>();

            // Criar CharacterDataComponent (Camada 3 - Runtime)
            TestDataComponent = NewObject<UCharacterDataComponent>(TestActor);
            TestDataComponent->RegisterComponent();

            // ✅ TDD CORRETO: Estado inicial LIMPO
            TestDataComponent->AbilityScores.Empty();
            TestDataComponent->Languages.Empty();
            TestDataComponent->RaceTraits.Empty();
            TestDataComponent->CharacterTotalLvl = 0;
            TestDataComponent->SelectedRace = NAME_None;
            TestDataComponent->SelectedSubrace = NAME_None;
            TestDataComponent->SelectedBackground = NAME_None;

            // Criar CharacterSheetComponent (Camada 2 - Bridge)
            TestSheetComponent = NewObject<UCharacterSheetComponent>(TestActor);
            TestSheetComponent->RegisterComponent();

            // Criar CharacterSheetDataAsset (Camada 1 - Editor)
            TestDataAsset = NewObject<UCharacterSheetDataAsset>();

            // ✅ TDD CORRETO: Estado inicial LIMPO no DataAsset
            TestDataAsset->PointBuyStrength = 0;
            TestDataAsset->PointBuyDexterity = 0;
            TestDataAsset->PointBuyConstitution = 0;
            TestDataAsset->PointBuyIntelligence = 0;
            TestDataAsset->PointBuyWisdom = 0;
            TestDataAsset->PointBuyCharisma = 0;
            TestDataAsset->FinalStrength = 0;
            TestDataAsset->FinalDexterity = 0;
            TestDataAsset->FinalConstitution = 0;
            TestDataAsset->FinalIntelligence = 0;
            TestDataAsset->FinalWisdom = 0;
            TestDataAsset->FinalCharisma = 0;
            TestDataAsset->SelectedRace = NAME_None;
            TestDataAsset->SelectedSubrace = NAME_None;
            TestDataAsset->SelectedBackground = NAME_None;
            TestDataAsset->Multiclass.Empty();
            TestDataAsset->TotalLevel = 0;
            TestDataAsset->ProficiencyBonus = 0;
        });

    AfterEach(
        [this]()
        {
            // Cleanup completo de todos os objetos (RAII pattern)
            if (TestSheetComponent)
            {
                TestSheetComponent->ConditionalBeginDestroy();
                TestSheetComponent = nullptr;
            }
            if (TestDataComponent)
            {
                TestDataComponent->ConditionalBeginDestroy();
                TestDataComponent = nullptr;
            }
            if (TestActor)
            {
                TestActor->ConditionalBeginDestroy();
                TestActor = nullptr;
            }
            if (TestDataAsset)
            {
                TestDataAsset->ConditionalBeginDestroy();
                TestDataAsset = nullptr;
            }
        });

    Describe("Criação Completa de Personagem - Todos os 6 Passos D&D 5e",
             [this]()
             {
                 It("deve criar personagem completo seguindo todos os 6 passos do D&D 5e",
                    [this]()
                    {
                        AddInfo(TEXT("Testando: processo completo de criação de personagem (6 passos D&D 5e)"));

                        // ========================================================================
                        // STEP 1: Choose a Race
                        // ========================================================================
                        TestDataAsset->CharacterName = TEXT("Test Character");
                        TestDataAsset->SelectedRace = TEXT("Elf");
                        TestDataAsset->SelectedSubrace = TEXT("High Elf");
                        // High Elf: +2 DEX (Elf), +1 INT (High Elf)

                        // ========================================================================
                        // STEP 2: Choose a Class
                        // ========================================================================
                        FMulticlassEntry WizardEntry;
                        WizardEntry.ClassData.Name = TEXT("Wizard");
                        WizardEntry.ClassData.LevelInClass = 1;
                        TestDataAsset->Multiclass.Add(WizardEntry);
                        TestDataAsset->TotalLevel = 1;

                        // ========================================================================
                        // STEP 3: Determine Ability Scores (Point Buy)
                        // ========================================================================
                        // ✅ TDD CORRETO: Configurar apenas ENTRADAS (PointBuy), não valores finais
                        // Alocação Point Buy válida (27 pontos):
                        // STR 8 (0), DEX 8 (0), CON 13 (5), INT 15 (9), WIS 12 (4), CHA 15 (9)
                        // Total: 0 + 0 + 5 + 9 + 4 + 9 = 27 ✓
                        TestDataAsset->PointBuyStrength = 0;      // Score 8 (0 pontos)
                        TestDataAsset->PointBuyDexterity = 0;     // Score 8 (0 pontos)
                        TestDataAsset->PointBuyConstitution = 5;  // Score 13 (5 pontos)
                        TestDataAsset->PointBuyIntelligence = 7;  // Score 15 (9 pontos)
                        TestDataAsset->PointBuyWisdom = 4;        // Score 12 (4 pontos)
                        TestDataAsset->PointBuyCharisma = 7;      // Score 15 (9 pontos)
                        // ❌ NÃO configurar FinalStrength, FinalDexterity, etc. manualmente!
                        // Sistema DEVE calcular: PointBuy + racial bonuses

                        // ========================================================================
                        // STEP 4: Describe Your Character
                        // ========================================================================
                        // Background (parte do Step 4 conforme D&D 5e oficial)
                        TestDataAsset->SelectedBackground = TEXT("Acolyte");

                        // Personality Traits, Ideals, Bonds, Flaws (NÃO IMPLEMENTADO)
                        // NOTA: Estes serão validados quando implementados
                        // Este passo será validado como "não implementado" no teste

                        // ========================================================================
                        // STEP 5: Choose Equipment (NÃO IMPLEMENTADO)
                        // ========================================================================
                        // NOTA: Starting Equipment não está implementado
                        // Este passo será validado como "não implementado" no teste

                        // ========================================================================
                        // STEP 6: Come Together (Revisão Final)
                        // ========================================================================
                        // Revisão final, validações, cálculos derivados
                        // NOTA: Este passo não adiciona dados, apenas valida e calcula

                        // Act: Inicializar componente com Data Asset
                        TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                        // ========================================================================
                        // ASSERT: Validar todos os passos
                        // ========================================================================

                        // STEP 1: Validar Race
                        TestEqual("STEP 1: Race deve ser Elf",
                                  TestDataComponent->SelectedRace, FName(TEXT("Elf")));
                        TestEqual("STEP 1: Subrace deve ser High Elf",
                                  TestDataComponent->SelectedSubrace, FName(TEXT("High Elf")));
                        TestTrue("STEP 1: RaceTraits deve conter traits",
                                 TestDataComponent->RaceTraits.Num() > 0);

                        // STEP 2: Validar Class
                        TestEqual("STEP 2: Classe deve ser Wizard",
                                  TestDataAsset->Multiclass[0].ClassData.Name, FName(TEXT("Wizard")));
                        TestEqual("STEP 2: Level deve ser 1",
                                  TestDataAsset->Multiclass[0].ClassData.LevelInClass, 1);
                        TestEqual("STEP 2: TotalLevel deve ser 1",
                                  TestDataAsset->TotalLevel, 1);

                        // STEP 3: Validar Ability Scores (após racial bonuses)
                        // ✅ TDD CORRETO: Verificar se sistema CALCULOU, não apenas copiou
                        // ⚠️ TDD RED: Estes testes devem FALHAR até InitializeFromDataAsset chamar RecalculateFinalScores()
                        TestTrue("STEP 3: Sistema DEVE calcular AbilityScores (não apenas copiar)",
                                 TestDataComponent->AbilityScores.Contains(TEXT("Strength")));
                        // Se não calcular, AbilityScores estará vazio ou com valores errados
                        // Esperado após cálculo: STR 8 (PointBuy 0), DEX 10 (PointBuy 0 + 2 Elf), INT 16 (PointBuy 7 + 1 High Elf)
                        TestEqual("STEP 3: Sistema DEVE calcular Strength = 8 (PointBuy 0)",
                                  TestDataComponent->AbilityScores[TEXT("Strength")], 8);

                        TestTrue("STEP 3: Sistema DEVE calcular Dexterity",
                                 TestDataComponent->AbilityScores.Contains(TEXT("Dexterity")));
                        TestEqual("STEP 3: Sistema DEVE calcular Dexterity = 10 (PointBuy 0 + 2 Elf)",
                                  TestDataComponent->AbilityScores[TEXT("Dexterity")], 10);

                        TestTrue("STEP 3: Sistema DEVE calcular Intelligence",
                                 TestDataComponent->AbilityScores.Contains(TEXT("Intelligence")));
                        TestEqual("STEP 3: Sistema DEVE calcular Intelligence = 16 (PointBuy 7 + 1 High Elf)",
                                  TestDataComponent->AbilityScores[TEXT("Intelligence")], 16);

                        // STEP 6: Validar cálculos derivados
                        // ✅ TDD CORRETO: Verificar se sistema CALCULOU proficiency bonus
                        // D&D 5e: Níveis 1-4 têm proficiency bonus +2
                        // Fórmula correta: 2 + floor((Level - 1) / 4)
                        // ⚠️ TDD RED: Este teste deve FALHAR até sistema calcular proficiency bonus
                        TestEqual("STEP 6: Sistema DEVE calcular ProficiencyBonus = +2 para nível 1",
                                  TestDataAsset->ProficiencyBonus, 2);
                        // NOTA: MaxHealth não está implementado ainda no CharacterDataComponent
                        // Este teste deve FALHAR até que HP seja implementado
                        AddInfo(TEXT("⚠️ STEP 6 (HP inicial) não implementado - será validado quando implementado"));
                        TestTrue("HP inicial deve estar implementado", false);

                        // STEP 4: Validar Background e Describe Your Character
                        TestEqual("STEP 4: Background deve ser Acolyte",
                                  TestDataComponent->SelectedBackground, FName(TEXT("Acolyte")));
                        // Personality Traits, Ideals, Bonds, Flaws (NÃO IMPLEMENTADO)
                        AddInfo(TEXT("⚠️ STEP 4 (Personality/Ideals/Bonds/Flaws) não implementado - será validado quando implementado"));

                        // STEP 5: Validar Equipment (NÃO IMPLEMENTADO)
                        AddInfo(TEXT("⚠️ STEP 5 (Starting Equipment) não implementado - será validado quando implementado"));

                        // Validação final
                        TestTrue("CharacterDataComponent deve ter dados válidos após inicialização completa",
                                 TestDataComponent->ValidateDataIntegrity());
                    });

                 It("deve criar personagem Variant Human completo seguindo todos os 6 passos",
                    [this]()
                    {
                        AddInfo(TEXT("Testando: processo completo com Variant Human (6 passos D&D 5e)"));

                        // STEP 1: Variant Human
                        TestDataAsset->SelectedRace = TEXT("Human");
                        TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                        TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Strength"));
                        TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Dexterity"));
                        TestDataAsset->SelectedFeat = TEXT("Alert");
                        TestDataAsset->SelectedSkill = TEXT("Perception");

                        // STEP 2: Class
                        FMulticlassEntry FighterEntry;
                        FighterEntry.ClassData.Name = TEXT("Fighter");
                        FighterEntry.ClassData.LevelInClass = 1;
                        TestDataAsset->Multiclass.Add(FighterEntry);
                        TestDataAsset->TotalLevel = 1;

                        // STEP 3: Point Buy
                        // ✅ TDD CORRETO: Configurar apenas ENTRADAS (PointBuy), não valores finais
                        // Alocação Point Buy válida (27 pontos):
                        // STR 15 (9), DEX 14 (7), CON 13 (5), INT 12 (4), WIS 10 (2), CHA 8 (0)
                        // Total: 9 + 7 + 5 + 4 + 2 + 0 = 27 ✓
                        TestDataAsset->PointBuyStrength = 7;     // Score 15 (9 pontos)
                        TestDataAsset->PointBuyDexterity = 6;    // Score 14 (7 pontos)
                        TestDataAsset->PointBuyConstitution = 5; // Score 13 (5 pontos)
                        TestDataAsset->PointBuyIntelligence = 4; // Score 12 (4 pontos)
                        TestDataAsset->PointBuyWisdom = 2;       // Score 10 (2 pontos)
                        TestDataAsset->PointBuyCharisma = 0;     // Score 8 (0 pontos)
                        // ❌ NÃO configurar FinalStrength, FinalDexterity, etc. manualmente!
                        // Sistema DEVE calcular: PointBuy + Variant Human bonuses (+1 STR, +1 DEX)

                        // STEP 4: Describe Your Character
                        // Background (parte do Step 4 conforme D&D 5e oficial)
                        TestDataAsset->SelectedBackground = TEXT("Acolyte");
                        // Personality Traits, Ideals, Bonds, Flaws (NÃO IMPLEMENTADO)

                        // STEP 5: Choose Equipment (NÃO IMPLEMENTADO)

                        // Act
                        TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                        // Assert
                        // STEP 1: Validar Variant Human
                        TestEqual("Variant Human: SelectedFeat deve ser Alert",
                                  TestDataComponent->SelectedFeat, FName(TEXT("Alert")));
                        TestEqual("Variant Human: SelectedSkill deve ser Perception",
                                  TestDataComponent->SelectedSkill, FName(TEXT("Perception")));
                        TestEqual("Variant Human: CustomAbilityScoreChoices deve ter 2 itens",
                                  TestDataComponent->CustomAbilityScoreChoices.Num(), 2);

                        // STEP 4: Validar Background
                        TestEqual("Variant Human: Background deve ser Acolyte",
                                  TestDataComponent->SelectedBackground, FName(TEXT("Acolyte")));
                        // ✅ TDD CORRETO: Verificar se sistema CALCULOU, não apenas copiou
                        // ⚠️ TDD RED: Estes testes devem FALHAR até sistema calcular Variant Human bonuses
                        TestTrue("Variant Human: Sistema DEVE calcular Strength",
                                 TestDataComponent->AbilityScores.Contains(TEXT("Strength")));
                        TestEqual("Variant Human: Sistema DEVE calcular Strength = 16 (PointBuy 7 + 1 Variant Human)",
                                  TestDataComponent->AbilityScores[TEXT("Strength")], 16);
                        TestTrue("Variant Human: Sistema DEVE calcular Dexterity",
                                 TestDataComponent->AbilityScores.Contains(TEXT("Dexterity")));
                        TestEqual("Variant Human: Sistema DEVE calcular Dexterity = 15 (PointBuy 6 + 1 Variant Human)",
                                  TestDataComponent->AbilityScores[TEXT("Dexterity")], 15);
                    });
             });
}

#pragma endregion Complete Character Creation End-to-End Tests
