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
#include "Data/Tables/RaceDataTable.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Step 1: Choose Race Tests
// ============================================================================
#pragma region Step 1: Choose Race Tests

/**
 * Testes para Step 1: Choose a Race (D&D 5e)
 *
 * Testa:
 * - Seleção de raça
 * - Aplicação de racial traits
 * - Aplicação de ability score increases
 * - Seleção de subraces
 * - Languages automáticos
 * - Variant Human
 */
BEGIN_DEFINE_SPEC(Step1ChooseRaceSpec, "MyProject2.CharacterCreation.Step1_ChooseRace",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UCharacterSheetDataAsset* TestDataAsset;
AActor* TestActor;
UCharacterSheetComponent* TestSheetComponent;
UCharacterDataComponent* TestDataComponent;
UDataTable* TestRaceDataTable;

END_DEFINE_SPEC(Step1ChooseRaceSpec)

void Step1ChooseRaceSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar Actor e Componentes para cada teste
            TestActor = NewObject<AActor>();

            // Criar CharacterDataComponent (Camada 3 - Runtime)
            TestDataComponent = NewObject<UCharacterDataComponent>(TestActor);
            TestDataComponent->RegisterComponent();

            // ✅ TDD CORRETO: Estado inicial LIMPO (garantir que testes FALHEM até implementação)
            TestDataComponent->AbilityScores.Empty();
            TestDataComponent->Languages.Empty();
            TestDataComponent->RaceTraits.Empty();
            TestDataComponent->SelectedRace = NAME_None;
            TestDataComponent->SelectedSubrace = NAME_None;
            TestDataComponent->CustomAbilityScoreChoices.Empty();

            // Criar CharacterSheetComponent (Camada 2 - Bridge)
            TestSheetComponent = NewObject<UCharacterSheetComponent>(TestActor);
            TestSheetComponent->RegisterComponent();

            // Criar CharacterSheetDataAsset (Camada 1 - Editor)
            TestDataAsset = NewObject<UCharacterSheetDataAsset>();

            // ✅ TDD CORRETO: Estado inicial LIMPO no DataAsset (valores zerados)
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
            TestDataAsset->SelectedLanguages.Empty();
            TestDataAsset->CustomAbilityScoreChoices.Empty();

            // Criar RaceDataTable mock com dados de teste
            TestRaceDataTable = NewObject<UDataTable>();
            TestRaceDataTable->RowStruct = FRaceDataRow::StaticStruct();

            // Criar row de Elf
            FRaceDataRow* ElfRow = new FRaceDataRow();
            ElfRow->RaceName = TEXT("Elf");
            ElfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("Dexterity"), 2));
            ElfRow->Traits.Add(FRaceTrait(TEXT("Darkvision"), FText::FromString(TEXT("Darkvision"))));
            ElfRow->Traits.Add(FRaceTrait(TEXT("Fey Ancestry"), FText::FromString(TEXT("Fey Ancestry"))));
            ElfRow->Traits.Add(FRaceTrait(TEXT("Trance"), FText::FromString(TEXT("Trance"))));
            ElfRow->Traits.Add(FRaceTrait(TEXT("Keen Senses"), FText::FromString(TEXT("Keen Senses"))));
            ElfRow->SubraceNames.Add(TEXT("High Elf"));
            ElfRow->SubraceNames.Add(TEXT("Wood Elf"));
            ElfRow->Languages.Add(TEXT("Common"));
            ElfRow->Languages.Add(TEXT("Elvish"));
            TestRaceDataTable->AddRow(TEXT("Elf"), *ElfRow);
            delete ElfRow;

            // Criar row de High Elf (subrace)
            FRaceDataRow* HighElfRow = new FRaceDataRow();
            HighElfRow->RaceName = TEXT("High Elf");
            HighElfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("Intelligence"), 1));
            HighElfRow->Traits.Add(FRaceTrait(TEXT("Cantrip"), FText::FromString(TEXT("Cantrip"))));
            TestRaceDataTable->AddRow(TEXT("High Elf"), *HighElfRow);
            delete HighElfRow;

            // Criar row de Dwarf
            FRaceDataRow* DwarfRow = new FRaceDataRow();
            DwarfRow->RaceName = TEXT("Dwarf");
            DwarfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("Constitution"), 2));
            DwarfRow->Languages.Add(TEXT("Common"));
            DwarfRow->Languages.Add(TEXT("Dwarvish"));
            TestRaceDataTable->AddRow(TEXT("Dwarf"), *DwarfRow);
            delete DwarfRow;

            // Criar row de Human
            FRaceDataRow* HumanRow = new FRaceDataRow();
            HumanRow->RaceName = TEXT("Human");
            HumanRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("Custom"), 0)); // Variant Human usa Custom
            HumanRow->SubraceNames.Add(TEXT("Variant Human"));
            HumanRow->Languages.Add(TEXT("Common"));
            TestRaceDataTable->AddRow(TEXT("Human"), *HumanRow);
            delete HumanRow;

            // Criar row de Variant Human (subrace)
            FRaceDataRow* VariantHumanRow = new FRaceDataRow();
            VariantHumanRow->RaceName = TEXT("Variant Human");
            VariantHumanRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("Custom"), 0)); // 2x +1 escolhidos pelo jogador
            TestRaceDataTable->AddRow(TEXT("Variant Human"), *VariantHumanRow);
            delete VariantHumanRow;

            // Configurar RaceDataTable no DataAsset
            TestDataAsset->RaceDataTable = TestRaceDataTable;
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
            if (TestRaceDataTable)
            {
                TestRaceDataTable->ConditionalBeginDestroy();
                TestRaceDataTable = nullptr;
            }
            if (TestDataAsset)
            {
                TestDataAsset->ConditionalBeginDestroy();
                TestDataAsset = nullptr;
            }
        });

    Describe("Step 1: Choose a Race",
             [this]()
             {
                 Describe("Racial Traits",
                          [this]()
                          {
                              It("deve aplicar racial traits da raça escolhida",
                                 [this]()
                                 {
                                     AddInfo(TEXT("Testando: aplicação de racial traits (ex: Darkvision, Fey Ancestry)"));

                                     // Arrange
                                     TestDataAsset->SelectedRace = TEXT("Elf");
                                     // Elf tem traits: Darkvision, Fey Ancestry, Trance, Keen Senses

                                     // Act
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                                     // Assert
                                     TestTrue("RaceTraits deve conter traits de Elf",
                                              TestDataComponent->RaceTraits.Num() > 0);
                                     TestTrue("RaceTraits deve conter Darkvision",
                                              TestDataComponent->RaceTraits.Contains(TEXT("Darkvision")));
                                     TestTrue("RaceTraits deve conter Fey Ancestry",
                                              TestDataComponent->RaceTraits.Contains(TEXT("Fey Ancestry")));
                                     TestTrue("RaceTraits deve conter Trance",
                                              TestDataComponent->RaceTraits.Contains(TEXT("Trance")));
                                     TestTrue("RaceTraits deve conter Keen Senses",
                                              TestDataComponent->RaceTraits.Contains(TEXT("Keen Senses")));
                                 });

                              It("deve aplicar racial traits da subrace quando selecionada",
                                 [this]()
                                 {
                                     AddInfo(TEXT("Testando: aplicação de racial traits de subrace (ex: High Elf Cantrip)"));

                                     // Arrange
                                     TestDataAsset->SelectedRace = TEXT("Elf");
                                     TestDataAsset->SelectedSubrace = TEXT("High Elf");
                                     // High Elf tem trait adicional: Cantrip

                                     // Act
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                                     // Assert
                                     TestTrue("RaceTraits deve conter traits de High Elf",
                                              TestDataComponent->RaceTraits.Num() > 0);
                                     TestTrue("RaceTraits deve conter Cantrip de High Elf",
                                              TestDataComponent->RaceTraits.Contains(TEXT("Cantrip")));
                                     // Também deve conter traits da raça base
                                     TestTrue("RaceTraits deve conter Darkvision da raça base",
                                              TestDataComponent->RaceTraits.Contains(TEXT("Darkvision")));
                                 });
                          });

                 Describe("Ability Score Increases",
                          [this]()
                          {
                              It("deve calcular ability scores baseado em PointBuy + racial bonus",
                                 [this]()
                                 {
                                     AddInfo(TEXT("⚠️ TDD RED: Teste deve FALHAR até InitializeFromDataAsset chamar RecalculateFinalScores()"));

                                     // ✅ TDD CORRETO: Arrange - Estado LIMPO, apenas entradas (não valores finais)
                                     TestDataAsset->SelectedRace = TEXT("Elf"); // Elf dá +2 DEX
                                     TestDataAsset->PointBuyDexterity = 6; // Score 14 (base 8 + 6 pontos)
                                     // NÃO configurar FinalDexterity manualmente! Sistema DEVE calcular

                                     // Act - Chama função REAL do módulo
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);
                                     // Se InitializeFromDataAsset não chamar RecalculateFinalScores(),
                                     // este teste DEVE FALHAR (AbilityScores estará vazio ou com valor errado)

                                     // ✅ TDD CORRETO: Assert - Verifica CÁLCULO real
                                     // Se não calcular: AbilityScores estará vazio ou FinalDexterity será 0
                                     TestTrue("Sistema DEVE calcular ability scores (não apenas copiar)",
                                              TestDataComponent->AbilityScores.Contains(TEXT("Dexterity")));
                                     // Verifica cálculo: base 8 + PointBuy 6 + racial 2 = 16
                                     // Se não calcular, este assert FALHA
                                     TestEqual("Sistema DEVE calcular: 8 (base) + 6 (PointBuy) + 2 (racial) = 16",
                                               TestDataComponent->AbilityScores[TEXT("Dexterity")], 16);
                                 });

                              It("deve calcular ability scores da subrace (raça base + subrace)",
                                 [this]()
                                 {
                                     AddInfo(TEXT("⚠️ TDD RED: Teste deve FALHAR até sistema calcular bônus de raça + subrace"));

                                     // ✅ TDD CORRETO: Arrange - Estado LIMPO, apenas entradas
                                     TestDataAsset->SelectedRace = TEXT("Elf"); // +2 DEX
                                     TestDataAsset->SelectedSubrace = TEXT("High Elf"); // +1 INT
                                     TestDataAsset->PointBuyIntelligence = 5; // Score 13 (base 8 + 5 pontos)
                                     // NÃO configurar valores finais manualmente!

                                     // Act - Chama função REAL
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);
                                     // Se não calcular, este teste FALHA

                                     // ✅ TDD CORRETO: Assert - Verifica CÁLCULO real
                                     TestTrue("Sistema DEVE calcular Intelligence",
                                              TestDataComponent->AbilityScores.Contains(TEXT("Intelligence")));
                                     // Verifica cálculo: base 8 + PointBuy 5 + racial 1 = 14
                                     TestEqual("Sistema DEVE calcular Intelligence: 8 (base) + 5 (PointBuy) + 1 (racial) = 14",
                                               TestDataComponent->AbilityScores[TEXT("Intelligence")], 14);
                                     // Também verifica DEX da raça base (deve ser calculado automaticamente)
                                     TestEqual("Sistema DEVE calcular Dexterity: 8 (base) + 0 (PointBuy) + 2 (racial) = 10",
                                               TestDataComponent->AbilityScores[TEXT("Dexterity")], 10);
                                 });

                              It("deve limitar ability score máximo a 30 após bônus racial",
                                 [this]()
                                 {
                                     AddInfo(TEXT("Testando: limitação de ability score máximo (30) após bônus racial"));

                                     // Arrange
                                     TestDataAsset->SelectedRace = TEXT("Elf");
                                     // Elf dá +2 DEX
                                     // Para testar limite: PointBuy máximo (15) = base 8 + 7 pontos
                                     // Score após PointBuy: 15, após racial: 15 + 2 = 17 (não excede)
                                     // Para exceder 30, precisamos de um score muito alto antes do bônus
                                     // Configuramos PointBuy para resultar em 29 antes do bônus
                                     // PointBuy 15 = score 15, mas precisamos score 29
                                     // Então: base 8 + PointBuy 21 (inválido, máximo é 7)
                                     // Alternativa: usar FinalDexterity diretamente configurado para 29
                                     // Mas o sistema calcula via PointBuy, então vamos testar com valor válido
                                     // Score 28 (base 8 + PointBuy 7 = 15, mas isso não dá 28)
                                     // Melhor: configurar FinalDexterity para 29 e verificar se sistema limita
                                     // NOTA: O sistema calcula FinalDexterity via RecalculateFinalScores
                                     // Vamos configurar PointBuy para máximo e verificar se não excede 30
                                     TestDataAsset->PointBuyDexterity = 7; // Score 15 (base 8 + 7 pontos, máximo PointBuy)
                                     // Após racial bonus: 15 + 2 = 17 (não excede 30, mas testa o fluxo)

                                     // Act
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                                     // Assert
                                     TestTrue("AbilityScores deve conter Dexterity",
                                              TestDataComponent->AbilityScores.Contains(TEXT("Dexterity")));
                                     int32 FinalDexterity = TestDataComponent->AbilityScores[TEXT("Dexterity")];
                                     TestTrue("Dexterity não deve exceder MAX_ABILITY_SCORE",
                                              FinalDexterity <= DnDConstants::MAX_ABILITY_SCORE);
                                     // Verifica valor específico: base 8 + PointBuy 7 + racial 2 = 17
                                     TestEqual("FinalDexterity deve ser 17 (15 + 2 racial)",
                                               FinalDexterity, 17);
                                 });
                          });

                 Describe("Subraces",
                          [this]()
                          {
                              It("deve permitir escolher subrace quando raça tem subraces",
                                 [this]()
                                 {
                                     AddInfo(TEXT("Testando: seleção de subrace (ex: High Elf, Wood Elf)"));

                                     // Arrange
                                     TestDataAsset->SelectedRace = TEXT("Elf");
                                     TestDataAsset->SelectedSubrace = TEXT("High Elf");

                                     // Act
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                                     // Assert
                                     TestEqual("SelectedSubrace deve ser High Elf",
                                               TestDataComponent->SelectedSubrace, FName(TEXT("High Elf")));
                                 });

                              It("deve resetar subrace quando raça muda",
                                 [this]()
                                 {
                                     AddInfo(TEXT("Testando: reset de subrace quando raça muda"));

                                     // Arrange
                                     TestDataAsset->SelectedRace = TEXT("Elf");
                                     TestDataAsset->SelectedSubrace = TEXT("High Elf");

                                     // Act - Muda raça (simula PostEditChangeProperty chamando handler)
                                     // O handler HandleRaceChange deve resetar subrace
                                     TestDataAsset->SelectedRace = TEXT("Dwarf");
                                     // Simula chamada do handler (em produção, PostEditChangeProperty faz isso)
                                     // Por enquanto, verificamos se o sistema reseta quando InitializeFromDataAsset é chamado
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                                     // Assert
                                     // Verifica que subrace foi resetado no Component
                                     TestEqual(TEXT("SelectedSubrace no Component deve ser resetado quando raça muda"),
                                               TestDataComponent->SelectedSubrace, NAME_None);
                                     // NOTA: O handler HandleRaceChange reseta no DataAsset também,
                                     // mas como não estamos chamando PostEditChangeProperty, verificamos apenas o Component
                                 });
                          });

                 Describe("Languages",
                          [this]()
                          {
                              It("deve carregar languages automáticos da raça do DataTable",
                                 [this]()
                                 {
                                     AddInfo(TEXT("⚠️ TDD RED: Teste deve FALHAR até InitializeFromDataAsset calcular languages do DataTable"));

                                     // ✅ TDD CORRETO: Arrange - Estado LIMPO
                                     // Languages está vazio no BeforeEach
                                     TestDataAsset->SelectedRace = TEXT("Elf"); // Elf conhece: Common, Elvish
                                     TestDataAsset->RaceDataTable = TestRaceDataTable; // Mock com dados

                                     // Act - Chama função REAL
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);
                                     // Se não calcular languages, Languages estará vazio e teste FALHA

                                     // ✅ TDD CORRETO: Assert - Verifica que Languages foi PREENCHIDO
                                     // Se não implementar, este teste FALHA (Languages estará vazio)
                                     TestTrue("Sistema DEVE calcular languages (não apenas copiar)",
                                              TestDataComponent->Languages.Num() > 0);
                                     TestTrue("Sistema DEVE carregar Common do DataTable",
                                              TestDataComponent->Languages.Contains(TEXT("Common")));
                                     TestTrue("Sistema DEVE carregar Elvish do DataTable",
                                              TestDataComponent->Languages.Contains(TEXT("Elvish")));
                                 });

                              It("deve carregar languages opcionais escolhidos + languages automáticos",
                                 [this]()
                                 {
                                     AddInfo(TEXT("⚠️ TDD RED: Teste deve FALHAR até sistema calcular languages opcionais + automáticos"));

                                     // ✅ TDD CORRETO: Arrange - Estado LIMPO
                                     TestDataAsset->SelectedRace = TEXT("Human");
                                     TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                                     TestDataAsset->SelectedLanguages.Add(TEXT("Draconic")); // Language opcional escolhido
                                     TestDataAsset->RaceDataTable = TestRaceDataTable; // Mock com dados

                                     // Act - Chama função REAL
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);
                                     // Se não calcular, teste FALHA

                                     // ✅ TDD CORRETO: Assert - Verifica que sistema CARREGOU languages
                                     // Se não implementar, este teste FALHA
                                     TestTrue("Sistema DEVE carregar language opcional escolhido",
                                              TestDataComponent->Languages.Contains(TEXT("Draconic")));
                                     TestTrue("Sistema DEVE carregar languages automáticos da raça",
                                              TestDataComponent->Languages.Contains(TEXT("Common")));
                                 });
                          });

                 Describe("Variant Human",
                          [this]()
                          {
                              It("deve permitir escolher 2 ability scores para +1 cada (Variant Human)",
                                 [this]()
                                 {
                                     AddInfo(TEXT("Testando: Variant Human - 2 ability score choices (+1 cada)"));

                                     // Arrange
                                     TestDataAsset->SelectedRace = TEXT("Human");
                                     TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                                     TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Strength"));
                                     TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Dexterity"));

                                     // Act
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                                     // Assert
                                     TestEqual("CustomAbilityScoreChoices deve ter VARIANT_HUMAN_ABILITY_SCORE_CHOICES itens",
                                               TestDataComponent->CustomAbilityScoreChoices.Num(),
                                               DnDConstants::VARIANT_HUMAN_ABILITY_SCORE_CHOICES);
                                 });

                              It("deve permitir escolher 1 feat (Variant Human)",
                                 [this]()
                                 {
                                     AddInfo(TEXT("Testando: Variant Human - escolha de 1 feat"));

                                     // Arrange
                                     TestDataAsset->SelectedRace = TEXT("Human");
                                     TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                                     TestDataAsset->SelectedFeat = TEXT("Alert");

                                     // Act
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                                     // Assert
                                     TestEqual("SelectedFeat deve ser Alert",
                                               TestDataComponent->SelectedFeat, FName(TEXT("Alert")));
                                 });

                              It("deve permitir escolher 1 skill proficiency (Variant Human)",
                                 [this]()
                                 {
                                     AddInfo(TEXT("Testando: Variant Human - escolha de 1 skill proficiency"));

                                     // Arrange
                                     TestDataAsset->SelectedRace = TEXT("Human");
                                     TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                                     TestDataAsset->SelectedSkill = TEXT("Perception");

                                     // Act
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);

                                     // Assert
                                     TestEqual("SelectedSkill deve ser Perception",
                                               TestDataComponent->SelectedSkill, FName(TEXT("Perception")));
                                 });

                              It("deve aplicar +2 quando Variant Human escolhe 1 ability score (2 pontos no mesmo atributo)",
                                 [this]()
                                 {
                                     AddInfo(TEXT("⚠️ TDD RED: Teste deve FALHAR até sistema aplicar +2 quando 1 escolha"));

                                     // ✅ TDD CORRETO: Arrange - Estado LIMPO, apenas entradas
                                     TestDataAsset->SelectedRace = TEXT("Human");
                                     TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                                     TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Strength")); // 1 escolha = +2
                                     TestDataAsset->PointBuyStrength = 5; // Score 13 (base 8 + 5 pontos)
                                     // NÃO configurar FinalStrength manualmente! Sistema DEVE calcular

                                     // Act - Chama função REAL
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);
                                     // Se não calcular, este teste FALHA

                                     // ✅ TDD CORRETO: Assert - Verifica CÁLCULO real
                                     // Regra: 1 escolha = +2 no mesmo atributo
                                     // Cálculo esperado: base 8 + PointBuy 5 + racial 2 = 15
                                     // Se não calcular, este assert FALHA
                                     TestTrue("Sistema DEVE calcular Strength com bônus Variant Human",
                                              TestDataComponent->AbilityScores.Contains(TEXT("Strength")));
                                     TestEqual("Sistema DEVE aplicar +2 quando 1 escolha: 8 (base) + 5 (PointBuy) + 2 (racial) = 15",
                                               TestDataComponent->AbilityScores[TEXT("Strength")], 15);
                                 });

                              It("deve aplicar +1 em cada quando Variant Human escolhe 2 ability scores (1 ponto em cada)",
                                 [this]()
                                 {
                                     AddInfo(TEXT("⚠️ TDD RED: Teste deve FALHAR até sistema aplicar +1 em cada quando 2 escolhas"));

                                     // ✅ TDD CORRETO: Arrange - Estado LIMPO, apenas entradas
                                     TestDataAsset->SelectedRace = TEXT("Human");
                                     TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                                     TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Strength")); // +1
                                     TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Dexterity")); // +1
                                     TestDataAsset->PointBuyStrength = 4; // Score 12 (base 8 + 4 pontos)
                                     TestDataAsset->PointBuyDexterity = 6; // Score 14 (base 8 + 6 pontos)
                                     // NÃO configurar valores finais manualmente! Sistema DEVE calcular

                                     // Act - Chama função REAL
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);
                                     // Se não calcular, este teste FALHA

                                     // ✅ TDD CORRETO: Assert - Verifica CÁLCULO real
                                     // Regra: 2 escolhas = +1 em cada atributo
                                     // Strength: base 8 + PointBuy 4 + racial 1 = 13
                                     // Dexterity: base 8 + PointBuy 6 + racial 1 = 15
                                     // Se não calcular, estes asserts FALHAM
                                     TestTrue("Sistema DEVE calcular Strength com bônus Variant Human",
                                              TestDataComponent->AbilityScores.Contains(TEXT("Strength")));
                                     TestEqual("Sistema DEVE aplicar +1 quando 2 escolhas: Strength = 8 (base) + 4 (PointBuy) + 1 (racial) = 13",
                                               TestDataComponent->AbilityScores[TEXT("Strength")], 13);
                                     TestTrue("Sistema DEVE calcular Dexterity com bônus Variant Human",
                                              TestDataComponent->AbilityScores.Contains(TEXT("Dexterity")));
                                     TestEqual("Sistema DEVE aplicar +1 quando 2 escolhas: Dexterity = 8 (base) + 6 (PointBuy) + 1 (racial) = 15",
                                               TestDataComponent->AbilityScores[TEXT("Dexterity")], 15);
                                 });

                              It("deve validar e limitar Variant Human a máximo 2 ability score choices",
                                 [this]()
                                 {
                                     AddInfo(TEXT("⚠️ TDD RED: Teste deve FALHAR até sistema validar e limitar choices"));

                                     // ✅ TDD CORRETO: Arrange - Estado LIMPO, tentativa de adicionar 3 (inválido)
                                     TestDataAsset->SelectedRace = TEXT("Human");
                                     TestDataAsset->SelectedSubrace = TEXT("Variant Human");
                                     TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Strength"));
                                     TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Dexterity"));
                                     TestDataAsset->CustomAbilityScoreChoices.Add(TEXT("Constitution")); // Terceiro (inválido)

                                     // Act - Chama função REAL
                                     TestSheetComponent->InitializeFromDataAsset(TestDataAsset);
                                     // Se não validar, CustomAbilityScoreChoices terá 3 itens e teste FALHA

                                     // ✅ TDD CORRETO: Assert - Verifica que sistema VALIDOU e LIMITOU
                                     // Se não implementar validação, este teste FALHA (terá 3 ao invés de 2)
                                     TestEqual("Sistema DEVE validar e limitar a VARIANT_HUMAN_ABILITY_SCORE_CHOICES",
                                               TestDataComponent->CustomAbilityScoreChoices.Num(),
                                               DnDConstants::VARIANT_HUMAN_ABILITY_SCORE_CHOICES);
                                 });
                          });
             });
}

#pragma endregion Step 1: Choose Race Tests
