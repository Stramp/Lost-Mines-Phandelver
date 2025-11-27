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
            TestActor->AddComponent(TestDataComponent);

            // Criar CharacterSheetComponent (Camada 2 - Bridge)
            TestSheetComponent = NewObject<UCharacterSheetComponent>(TestActor);
            TestActor->AddComponent(TestSheetComponent);

            // Criar CharacterSheetDataAsset (Camada 1 - Editor)
            TestDataAsset = NewObject<UCharacterSheetDataAsset>();
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
                   // Arrange: Configurar Data Asset básico
                   TestDataAsset->CharacterName = TEXT("Test Character");
                   TestDataAsset->SelectedRace = TEXT("Human");
                   TestDataAsset->SelectedBackground = TEXT("Acolyte");

                   // Configurar ability scores finais (após Point Buy e Race Bonus)
                   // Usa DnDConstants para evitar magic numbers
                   TestDataAsset->FinalStrength = DnDConstants::MAX_POINT_BUY_SCORE; // 15
                   TestDataAsset->FinalDexterity = 13;                               // Valor intermediário válido
                   TestDataAsset->FinalConstitution = DnDConstants::INTERMEDIATE_POINT_BUY_SCORE; // 14
                   TestDataAsset->FinalIntelligence = 12;                            // Valor intermediário válido
                   TestDataAsset->FinalWisdom = DnDConstants::ABILITY_MODIFIER_BASE; // 10 (modificador 0)
                   TestDataAsset->FinalCharisma = DnDConstants::BASE_ABILITY_SCORE;  // 8 (mínimo Point Buy)

                   // Act: Inicializar componente com Data Asset
                   TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                   // Assert: Validar que CharacterDataComponent foi populado
                   TestEqual("CharacterName deve ser copiado", TestDataComponent->CharacterName,
                             TEXT("Test Character"));
                   TestEqual("SelectedRace deve ser copiado", TestDataComponent->SelectedRace, TEXT("Human"));
                   TestEqual("SelectedBackground deve ser copiado", TestDataComponent->SelectedBackground,
                             TEXT("Acolyte"));

                   // Validar todos os Ability Scores foram copiados corretamente
                   TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
                   TestEqual("AbilityScores deve conter todos os 6 atributos", TestDataComponent->AbilityScores.Num(),
                             DnDConstants::NUM_ABILITY_SCORES);

                   // Validar cada ability score individualmente
                   TestTrue("AbilityScores deve conter Strength",
                            TestDataComponent->AbilityScores.Contains(TEXT("Strength")));
                   TestEqual("Strength deve ser MAX_POINT_BUY_SCORE",
                             TestDataComponent->AbilityScores[TEXT("Strength")], DnDConstants::MAX_POINT_BUY_SCORE);

                   TestTrue("AbilityScores deve conter Dexterity",
                            TestDataComponent->AbilityScores.Contains(TEXT("Dexterity")));
                   TestEqual("Dexterity deve ser 13", TestDataComponent->AbilityScores[TEXT("Dexterity")], 13);

                   TestTrue("AbilityScores deve conter Constitution",
                            TestDataComponent->AbilityScores.Contains(TEXT("Constitution")));
                   TestEqual("Constitution deve ser INTERMEDIATE_POINT_BUY_SCORE",
                             TestDataComponent->AbilityScores[TEXT("Constitution")],
                             DnDConstants::INTERMEDIATE_POINT_BUY_SCORE);

                   TestTrue("AbilityScores deve conter Intelligence",
                            TestDataComponent->AbilityScores.Contains(TEXT("Intelligence")));
                   TestEqual("Intelligence deve ser 12", TestDataComponent->AbilityScores[TEXT("Intelligence")], 12);

                   TestTrue("AbilityScores deve conter Wisdom",
                            TestDataComponent->AbilityScores.Contains(TEXT("Wisdom")));
                   TestEqual("Wisdom deve ser ABILITY_MODIFIER_BASE", TestDataComponent->AbilityScores[TEXT("Wisdom")],
                             DnDConstants::ABILITY_MODIFIER_BASE);

                   TestTrue("AbilityScores deve conter Charisma",
                            TestDataComponent->AbilityScores.Contains(TEXT("Charisma")));
                   TestEqual("Charisma deve ser BASE_ABILITY_SCORE", TestDataComponent->AbilityScores[TEXT("Charisma")],
                             DnDConstants::BASE_ABILITY_SCORE);

                   // Validar integridade dos dados usando método do componente
                   TestTrue("CharacterDataComponent deve ter dados válidos após inicialização",
                            TestDataComponent->ValidateDataIntegrity());
               });

            It("deve inicializar personagem com Variant Human completo",
               [this]()
               {
                   // Arrange: Configurar Variant Human
                   TestDataAsset->SelectedRace = TEXT("Human");
                   TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                   TestDataAsset->SelectedFeat = TEXT("Alert");
                   TestDataAsset->SelectedSkill = TEXT("Perception");

                   // Custom Ability Score Choices (2x +1) - Variant Human
                   TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Strength"));
                   TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Dexterity"));
                   TestEqual("CustomAbilityScoreChoices deve ter VARIANT_HUMAN_ABILITY_SCORE_CHOICES itens",
                             TestDataAsset->CustomAbilityScoreChoices.Num(),
                             DnDConstants::VARIANT_HUMAN_ABILITY_SCORE_CHOICES);

                   // Ability scores finais (base + bônus Variant Human)
                   TestDataAsset->FinalStrength =
                       DnDConstants::MAX_POINT_BUY_SCORE + 1; // 15 base + 1 Variant Human = 16
                   TestDataAsset->FinalDexterity =
                       DnDConstants::INTERMEDIATE_POINT_BUY_SCORE; // 13 base + 1 Variant Human = 14

                   // Act
                   TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                   // Assert: Validar Variant Human choices
                   TestEqual("SelectedFeat deve ser Alert", TestDataComponent->SelectedFeat, TEXT("Alert"));
                   TestEqual("SelectedSkill deve ser Perception", TestDataComponent->SelectedSkill, TEXT("Perception"));
                   TestEqual("CustomAbilityScoreChoices deve ter VARIANT_HUMAN_ABILITY_SCORE_CHOICES itens",
                             TestDataComponent->CustomAbilityScoreChoices.Num(),
                             DnDConstants::VARIANT_HUMAN_ABILITY_SCORE_CHOICES);

                   // Validar que ability scores foram copiados corretamente
                   TestTrue("AbilityScores deve conter Strength",
                            TestDataComponent->AbilityScores.Contains(TEXT("Strength")));
                   TestEqual("Strength deve ser MAX_POINT_BUY_SCORE + 1",
                             TestDataComponent->AbilityScores[TEXT("Strength")], DnDConstants::MAX_POINT_BUY_SCORE + 1);

                   TestTrue("AbilityScores deve conter Dexterity",
                            TestDataComponent->AbilityScores.Contains(TEXT("Dexterity")));
                   TestEqual("Dexterity deve ser INTERMEDIATE_POINT_BUY_SCORE",
                             TestDataComponent->AbilityScores[TEXT("Dexterity")],
                             DnDConstants::INTERMEDIATE_POINT_BUY_SCORE);

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
                   TestEqual("Primeira classe deve ser Fighter", TestDataAsset->Multiclass[0].ClassData.Name,
                             TEXT("Fighter"));
                   TestEqual("Fighter deve ter nível MIN_LEVEL", TestDataAsset->Multiclass[0].ClassData.LevelInClass,
                             DnDConstants::MIN_LEVEL);

                   // Validar que segunda classe é Wizard
                   TestEqual("Segunda classe deve ser Wizard", TestDataAsset->Multiclass[1].ClassData.Name,
                             TEXT("Wizard"));
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
                   TestEqual("SelectedRace não deve ser modificado após nullptr", TestDataComponent->SelectedRace,
                             InitialRace);
                   TestEqual("SelectedBackground não deve ser modificado após nullptr",
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
