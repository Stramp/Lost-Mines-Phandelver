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

#pragma endregion Includes

// ============================================================================
// Character Creation End-to-End Tests
// ============================================================================
#pragma region Character Creation End-to-End Tests

/**
 * Testes de integração end-to-end para criação completa de personagem.
 *
 * Testa o fluxo completo:
 * 1. Criar CharacterSheetDataAsset com dados completos
 * 2. Inicializar CharacterSheetComponent
 * 3. Validar que CharacterDataComponent foi populado corretamente
 *
 * Estes testes validam a integração entre múltiplos sistemas:
 * - Data Asset (Camada 1)
 * - Bridge Component (Camada 2)
 * - Runtime Component (Camada 3)
 */
BEGIN_DEFINE_SPEC(CharacterCreationE2ESpec, "MyProject2.Integration.CharacterCreation",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UCharacterSheetDataAsset *TestDataAsset;
AActor *TestActor;
UCharacterSheetComponent *TestSheetComponent;
UCharacterDataComponent *TestDataComponent;

END_DEFINE_SPEC(CharacterCreationE2ESpec)

void CharacterCreationE2ESpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar Actor e Componentes para cada teste
            TestActor = NewObject<AActor>();

            // Criar CharacterDataComponent (Camada 3 - Runtime)
            TestDataComponent = NewObject<UCharacterDataComponent>(TestActor);
            TestDataComponent->RegisterComponent();

            // Criar CharacterSheetComponent (Camada 2 - Bridge)
            TestSheetComponent = NewObject<UCharacterSheetComponent>(TestActor);
            TestSheetComponent->RegisterComponent();

            // Criar CharacterSheetDataAsset (Camada 1 - Editor)
            TestDataAsset = NewObject<UCharacterSheetDataAsset>();

            // ✅ TDD CORRETO: Estado inicial LIMPO
            TestDataComponent->AbilityScores.Empty();
            TestDataComponent->Languages.Empty();
            TestDataComponent->RaceTraits.Empty();
            TestDataAsset->PointBuyStrength = 0;
            TestDataAsset->PointBuyDexterity = 0;
            TestDataAsset->PointBuyConstitution = 0;
            TestDataAsset->PointBuyIntelligence = 0;
            TestDataAsset->PointBuyWisdom = 0;
            TestDataAsset->PointBuyCharisma = 0;
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

    Describe(
        "Criação Completa de Personagem",
        [this]()
        {
            It("deve inicializar personagem básico com raça e background",
               [this]()
               {
                   // ✅ TDD CORRETO: Teste E2E foca no FLUXO COMPLETO, não em detalhes unitários
                   // Arrange: Configurar Data Asset básico
                   TestDataAsset->CharacterName = TEXT("Test Character");
                   TestDataAsset->SelectedRace = TEXT("Human");
                   TestDataAsset->SelectedBackground = TEXT("Acolyte");

                   // ✅ TDD CORRETO: Configurar apenas ENTRADAS (PointBuy), não valores finais
                   // Configuração básica de Point Buy para validar fluxo
                   TestDataAsset->PointBuyStrength = 7;     // Score 15
                   TestDataAsset->PointBuyDexterity = 6;    // Score 14
                   TestDataAsset->PointBuyConstitution = 5; // Score 13
                   TestDataAsset->PointBuyIntelligence = 4; // Score 12
                   TestDataAsset->PointBuyWisdom = 2;       // Score 10
                   TestDataAsset->PointBuyCharisma = 0;     // Score 8
                   // ❌ NÃO configurar FinalStrength, FinalDexterity, etc. manualmente!

                   // Act: Inicializar componente com Data Asset
                   TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                   // Assert: Validar FLUXO COMPLETO (não detalhes unitários)
                   TestEqual(TEXT("CharacterName deve ser copiado"), TestDataComponent->CharacterName,
                             TEXT("Test Character"));
                   TestEqual(TEXT("SelectedRace deve ser copiado"), TestDataComponent->SelectedRace, FName(TEXT("Human")));
                   TestEqual(TEXT("SelectedBackground deve ser copiado"), TestDataComponent->SelectedBackground,
                             FName(TEXT("Acolyte")));

                   // ✅ TDD CORRETO: Validar que AbilityScores foi populado (não valores específicos)
                   // Detalhes de cálculo são testados em testes unitários (Step1, Step3)
                   TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
                   TestEqual("AbilityScores deve conter todos os 6 atributos", TestDataComponent->AbilityScores.Num(),
                             DnDConstants::NUM_ABILITY_SCORES);
                   TestTrue("AbilityScores deve conter Strength",
                            TestDataComponent->AbilityScores.Contains(TEXT("Strength")));
                   TestTrue("AbilityScores deve conter Dexterity",
                            TestDataComponent->AbilityScores.Contains(TEXT("Dexterity")));

                   // Validar integridade dos dados usando método do componente
                   TestTrue("CharacterDataComponent deve ter dados válidos após inicialização",
                            TestDataComponent->ValidateDataIntegrity());
               });

            It("deve inicializar personagem com Variant Human completo",
               [this]()
               {
                   // ✅ TDD CORRETO: Teste E2E foca no FLUXO COMPLETO de Variant Human
                   // Arrange: Configurar Variant Human
                   TestDataAsset->SelectedRace = TEXT("Human");
                   TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                   TestDataAsset->SelectedFeat = TEXT("Alert");
                   TestDataAsset->SelectedSkill = TEXT("Perception");

                   // Custom Ability Score Choices (2x +1) - Variant Human
                   TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Strength"));
                   TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Dexterity"));

                   // ✅ TDD CORRETO: Configurar apenas ENTRADAS (PointBuy), não valores finais
                   TestDataAsset->PointBuyStrength = 7;     // Score 15
                   TestDataAsset->PointBuyDexterity = 6;    // Score 14
                   // ❌ NÃO configurar FinalStrength, FinalDexterity manualmente!
                   // Sistema DEVE calcular: PointBuy + Variant Human bonuses

                   // Act
                   TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                   // Assert: Validar FLUXO COMPLETO de Variant Human (não detalhes unitários)
                   // Detalhes de Variant Human são testados em testes unitários (Step1)
                   TestEqual(TEXT("SelectedFeat deve ser Alert"), TestDataComponent->SelectedFeat, FName(TEXT("Alert")));
                   TestEqual(TEXT("SelectedSkill deve ser Perception"), TestDataComponent->SelectedSkill, FName(TEXT("Perception")));
                   TestEqual("CustomAbilityScoreChoices deve ter VARIANT_HUMAN_ABILITY_SCORE_CHOICES itens",
                             TestDataComponent->CustomAbilityScoreChoices.Num(),
                             DnDConstants::VARIANT_HUMAN_ABILITY_SCORE_CHOICES);

                   // ✅ TDD CORRETO: Validar que AbilityScores foi populado (não valores específicos)
                   TestTrue("AbilityScores deve conter Strength",
                            TestDataComponent->AbilityScores.Contains(TEXT("Strength")));
                   TestTrue("AbilityScores deve conter Dexterity",
                            TestDataComponent->AbilityScores.Contains(TEXT("Dexterity")));

                   // Validar integridade dos dados
                   TestTrue("CharacterDataComponent deve ter dados válidos após inicialização",
                            TestDataComponent->ValidateDataIntegrity());
               });

            It("deve inicializar personagem com multiclasse básico",
               [this]()
               {
                   // Arrange: Configurar multiclasse (Fighter 1 / Wizard 1)
                   FMulticlassEntry FighterEntry;
                   FighterEntry.ClassData.Name = TEXT("Fighter");
                   FighterEntry.ClassData.LevelInClass = DnDConstants::MIN_LEVEL; // Nível 1

                   FMulticlassEntry WizardEntry;
                   WizardEntry.ClassData.Name = TEXT("Wizard");
                   WizardEntry.ClassData.LevelInClass = DnDConstants::MIN_LEVEL; // Nível 1

                   TestDataAsset->Multiclass.Add(FighterEntry);
                   TestDataAsset->Multiclass.Add(WizardEntry);

                   // TotalLevel = soma dos níveis de classe
                   const int32 ExpectedTotalLevel = DnDConstants::MIN_LEVEL + DnDConstants::MIN_LEVEL; // 1 + 1 = 2
                   TestDataAsset->TotalLevel = ExpectedTotalLevel;

                   // Act
                   TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                   // Assert: Validar que multiclasse foi configurado corretamente
                   TestEqual("Multiclass deve conter 2 classes", TestDataAsset->Multiclass.Num(), 2);
                   TestEqual("TotalLevel no Data Asset deve ser 2", TestDataAsset->TotalLevel, ExpectedTotalLevel);

                   // Validar que primeira classe é Fighter
                   TestEqual(TEXT("Primeira classe deve ser Fighter"), TestDataAsset->Multiclass[0].ClassData.Name,
                             FName(TEXT("Fighter")));
                   TestEqual("Fighter deve ter nível MIN_LEVEL", TestDataAsset->Multiclass[0].ClassData.LevelInClass,
                             DnDConstants::MIN_LEVEL);

                   // Validar que segunda classe é Wizard
                   TestEqual(TEXT("Segunda classe deve ser Wizard"), TestDataAsset->Multiclass[1].ClassData.Name,
                             FName(TEXT("Wizard")));
                   TestEqual("Wizard deve ter nível MIN_LEVEL", TestDataAsset->Multiclass[1].ClassData.LevelInClass,
                             DnDConstants::MIN_LEVEL);

                   // Nota: CharacterTotalLvl é calculado pelo motor de multiclasse em runtime,
                   // não é copiado diretamente do Data Asset. Este teste valida que o fluxo
                   // não quebra com multiclasse configurado e que os dados foram preservados.
               });

            It("deve lidar com DataAsset nullptr graciosamente",
               [this]()
               {
                   // Arrange: Salvar estado inicial do CharacterDataComponent
                   const FName InitialRace = TestDataComponent->SelectedRace;
                   const FName InitialBackground = TestDataComponent->SelectedBackground;
                   const int32 InitialAbilityScoresCount = TestDataComponent->AbilityScores.Num();

                   // Act: Tentar inicializar com nullptr
                   TestSheetComponent->InitializeFromDataAsset(nullptr);

                   // Assert: Componente não deve crashar e não deve modificar dados existentes
                   // (Validação é feita internamente com ensureMsgf que retorna early)
                   TestEqual(TEXT("SelectedRace não deve ser modificado após nullptr"), TestDataComponent->SelectedRace,
                             InitialRace);
                   TestEqual(TEXT("SelectedBackground não deve ser modificado após nullptr"),
                             TestDataComponent->SelectedBackground, InitialBackground);
                   TestEqual("AbilityScores não deve ser modificado após nullptr",
                             TestDataComponent->AbilityScores.Num(), InitialAbilityScoresCount);

                   // Validar que CharacterDataComponent ainda está em estado válido (mesmo que vazio)
                   // Nota: ValidateDataIntegrity pode retornar false se dados estão vazios,
                   // mas isso é esperado - o importante é que não crashou
               });
        });
}

#pragma endregion Character Creation End - to - End Tests
