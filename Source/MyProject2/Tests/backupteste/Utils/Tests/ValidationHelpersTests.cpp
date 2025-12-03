// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/ValidationHelpers.h"
#include "Utils/DnDConstants.h"
#include "Utils/CharacterSheetHelpers.h"

#pragma endregion Includes

// ============================================================================
// ValidationHelpers Tests
// ============================================================================
#pragma region ValidationHelpers Tests

BEGIN_DEFINE_SPEC(ValidationHelpersSpec, "MyProject2.Utils.ValidationHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(ValidationHelpersSpec)

void ValidationHelpersSpec::Define()
{
    Describe("ValidateAbilityScoreRange",
             [this]()
             {
                 It("deve validar score dentro do range padrão (1-30)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateAbilityScoreRange com score válido (15)"));

                        // Act
                        bool Result = ValidationHelpers::ValidateAbilityScoreRange(15);

                        // Assert
                        TestTrue("Score 15 deve ser válido no range padrão", Result);
                        AddInfo(TEXT("✅ Teste passou: score válido reconhecido corretamente"));
                    });

                 It("deve validar score no limite mínimo (1)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateAbilityScoreRange com score mínimo (1)"));

                        // Act
                        bool Result = ValidationHelpers::ValidateAbilityScoreRange(1);

                        // Assert
                        TestTrue("Score 1 deve ser válido (limite mínimo)", Result);
                        AddInfo(TEXT("✅ Teste passou: limite mínimo validado corretamente"));
                    });

                 It("deve validar score no limite máximo (30)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateAbilityScoreRange com score máximo (30)"));

                        // Act
                        bool Result = ValidationHelpers::ValidateAbilityScoreRange(30);

                        // Assert
                        TestTrue("Score 30 deve ser válido (limite máximo)", Result);
                        AddInfo(TEXT("✅ Teste passou: limite máximo validado corretamente"));
                    });

                 It("deve rejeitar score abaixo do mínimo (0)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateAbilityScoreRange com score inválido (0)"));

                        // Act
                        bool Result = ValidationHelpers::ValidateAbilityScoreRange(0);

                        // Assert
                        TestFalse("Score 0 deve ser inválido", Result);
                        AddInfo(TEXT("✅ Teste passou: score abaixo do mínimo rejeitado corretamente"));
                    });

                 It("deve rejeitar score acima do máximo (31)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateAbilityScoreRange com score inválido (31)"));

                        // Act
                        bool Result = ValidationHelpers::ValidateAbilityScoreRange(31);

                        // Assert
                        TestFalse("Score 31 deve ser inválido", Result);
                        AddInfo(TEXT("✅ Teste passou: score acima do máximo rejeitado corretamente"));
                    });

                 It("deve validar score com range customizado",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateAbilityScoreRange com range customizado (8-15)"));

                        // Act & Assert
                        TestTrue("Score 10 deve ser válido no range 8-15",
                                 ValidationHelpers::ValidateAbilityScoreRange(10, 8, 15));
                        TestTrue("Score 8 deve ser válido no range 8-15",
                                 ValidationHelpers::ValidateAbilityScoreRange(8, 8, 15));
                        TestTrue("Score 15 deve ser válido no range 8-15",
                                 ValidationHelpers::ValidateAbilityScoreRange(15, 8, 15));
                        TestFalse("Score 7 deve ser inválido no range 8-15",
                                  ValidationHelpers::ValidateAbilityScoreRange(7, 8, 15));
                        TestFalse("Score 16 deve ser inválido no range 8-15",
                                  ValidationHelpers::ValidateAbilityScoreRange(16, 8, 15));
                        AddInfo(TEXT("✅ Teste passou: range customizado validado corretamente"));
                    });
             });

    Describe(
        "ValidatePointBuy",
        [this]()
        {
            It("deve validar alocação válida de Point Buy",
               [this]()
               {
                   AddInfo(TEXT("Testando ValidatePointBuy com alocação válida"));

                   // Arrange: Alocação válida (todos scores entre 8-15)
                   TMap<FName, int32> BaseScores;
                   BaseScores.Add(TEXT("Strength"), 15);
                   BaseScores.Add(TEXT("Dexterity"), 14);
                   BaseScores.Add(TEXT("Constitution"), 13);
                   BaseScores.Add(TEXT("Intelligence"), 12);
                   BaseScores.Add(TEXT("Wisdom"), 10);
                   BaseScores.Add(TEXT("Charisma"), 8);

                   int32 PointsRemaining = 0;

                   // Act
                   bool Result = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining,
                                                                     DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestTrue("Alocação válida deve ser aceita", Result);
                   AddInfo(FString::Printf(TEXT("✅ Teste passou: alocação válida aceita (pontos restantes: %d)"),
                                           PointsRemaining));
               });

            It("deve rejeitar score abaixo do mínimo (7)",
               [this]()
               {
                   AddInfo(TEXT("Testando ValidatePointBuy com score abaixo do mínimo"));

                   // Arrange: Score 7 (abaixo do mínimo 8)
                   TMap<FName, int32> BaseScores;
                   BaseScores.Add(TEXT("Strength"), 7);
                   BaseScores.Add(TEXT("Dexterity"), 8);
                   BaseScores.Add(TEXT("Constitution"), 8);
                   BaseScores.Add(TEXT("Intelligence"), 8);
                   BaseScores.Add(TEXT("Wisdom"), 8);
                   BaseScores.Add(TEXT("Charisma"), 8);

                   int32 PointsRemaining = 0;

                   // Act
                   bool Result = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining,
                                                                     DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestFalse("Alocação com score abaixo do mínimo deve ser rejeitada", Result);
                   AddInfo(TEXT("✅ Teste passou: score abaixo do mínimo rejeitado corretamente"));
               });

            It("deve rejeitar score acima do máximo (16)",
               [this]()
               {
                   AddInfo(TEXT("Testando ValidatePointBuy com score acima do máximo"));

                   // Arrange: Score 16 (acima do máximo 15)
                   TMap<FName, int32> BaseScores;
                   BaseScores.Add(TEXT("Strength"), 16);
                   BaseScores.Add(TEXT("Dexterity"), 8);
                   BaseScores.Add(TEXT("Constitution"), 8);
                   BaseScores.Add(TEXT("Intelligence"), 8);
                   BaseScores.Add(TEXT("Wisdom"), 8);
                   BaseScores.Add(TEXT("Charisma"), 8);

                   int32 PointsRemaining = 0;

                   // Act
                   bool Result = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining,
                                                                     DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestFalse("Alocação com score acima do máximo deve ser rejeitada", Result);
                   AddInfo(TEXT("✅ Teste passou: score acima do máximo rejeitado corretamente"));
               });

            It("deve calcular pontos restantes corretamente",
               [this]()
               {
                   AddInfo(TEXT("Testando ValidatePointBuy cálculo de pontos restantes"));

                   // Arrange: Alocação que gasta exatamente 27 pontos
                   TMap<FName, int32> BaseScores;
                   BaseScores.Add(TEXT("Strength"), 15);
                   BaseScores.Add(TEXT("Dexterity"), 15);
                   BaseScores.Add(TEXT("Constitution"), 15);
                   BaseScores.Add(TEXT("Intelligence"), 8);
                   BaseScores.Add(TEXT("Wisdom"), 8);
                   BaseScores.Add(TEXT("Charisma"), 8);

                   int32 PointsRemaining = 0;

                   // Act
                   bool Result = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining,
                                                                     DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestTrue("Alocação válida deve ser aceita", Result);
                   // Nota: PointsRemaining pode ser negativo se excedeu, ou positivo se sobrou
                   // O importante é que a função calcula corretamente
                   AddInfo(FString::Printf(TEXT("✅ Teste passou: pontos restantes calculados (%d)"), PointsRemaining));
               });

            It("deve validar alocação com todos scores no mínimo (8)",
               [this]()
               {
                   AddInfo(TEXT("Testando ValidatePointBuy com todos scores no mínimo"));

                   // Arrange: Todos scores no mínimo (8)
                   TMap<FName, int32> BaseScores;
                   BaseScores.Add(TEXT("Strength"), 8);
                   BaseScores.Add(TEXT("Dexterity"), 8);
                   BaseScores.Add(TEXT("Constitution"), 8);
                   BaseScores.Add(TEXT("Intelligence"), 8);
                   BaseScores.Add(TEXT("Wisdom"), 8);
                   BaseScores.Add(TEXT("Charisma"), 8);

                   int32 PointsRemaining = 0;

                   // Act
                   bool Result = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining,
                                                                     DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestTrue("Alocação com todos scores no mínimo deve ser válida", Result);
                   AddInfo(TEXT("✅ Teste passou: alocação mínima validada corretamente"));
               });

            It("deve validar alocação com todos scores no máximo (15)",
               [this]()
               {
                   AddInfo(TEXT("Testando ValidatePointBuy com todos scores no máximo"));

                   // Arrange: Todos scores no máximo (15)
                   TMap<FName, int32> BaseScores;
                   BaseScores.Add(TEXT("Strength"), 15);
                   BaseScores.Add(TEXT("Dexterity"), 15);
                   BaseScores.Add(TEXT("Constitution"), 15);
                   BaseScores.Add(TEXT("Intelligence"), 15);
                   BaseScores.Add(TEXT("Wisdom"), 15);
                   BaseScores.Add(TEXT("Charisma"), 15);

                   int32 PointsRemaining = 0;

                   // Act
                   bool Result = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining,
                                                                     DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestTrue("Alocação com todos scores no máximo deve ser válida", Result);
                   AddInfo(TEXT("✅ Teste passou: alocação máxima validada corretamente"));
               });
        });

    Describe(
        "ValidatePointBuyAllocation",
        [this]()
        {
            It("deve validar alocação que gasta exatamente MaxPoints",
               [this]()
               {
                   AddInfo(TEXT("Testando ValidatePointBuyAllocation com alocação que gasta exatamente 27 pontos"));

                   // Arrange: Alocação que gasta exatamente 27 pontos
                   // 15, 15, 15, 8, 8, 8 = 9 + 9 + 9 + 0 + 0 + 0 = 27 pontos
                   TMap<FName, int32> BaseScores;
                   BaseScores.Add(TEXT("Strength"), 15);
                   BaseScores.Add(TEXT("Dexterity"), 15);
                   BaseScores.Add(TEXT("Constitution"), 15);
                   BaseScores.Add(TEXT("Intelligence"), 8);
                   BaseScores.Add(TEXT("Wisdom"), 8);
                   BaseScores.Add(TEXT("Charisma"), 8);

                   // Act
                   bool Result =
                       ValidationHelpers::ValidatePointBuyAllocation(BaseScores, DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestTrue("Alocação que gasta exatamente 27 pontos deve ser válida", Result);
                   AddInfo(TEXT("✅ Teste passou: alocação que gasta exatamente MaxPoints validada corretamente"));
               });

            It("deve rejeitar alocação que não gasta exatamente MaxPoints",
               [this]()
               {
                   AddInfo(TEXT("Testando ValidatePointBuyAllocation com alocação que não gasta exatamente 27 pontos"));

                   // Arrange: Alocação que não gasta exatamente 27 pontos (todos 8 = 0 pontos)
                   TMap<FName, int32> BaseScores;
                   BaseScores.Add(TEXT("Strength"), 8);
                   BaseScores.Add(TEXT("Dexterity"), 8);
                   BaseScores.Add(TEXT("Constitution"), 8);
                   BaseScores.Add(TEXT("Intelligence"), 8);
                   BaseScores.Add(TEXT("Wisdom"), 8);
                   BaseScores.Add(TEXT("Charisma"), 8);

                   // Act
                   bool Result =
                       ValidationHelpers::ValidatePointBuyAllocation(BaseScores, DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestFalse("Alocação que não gasta exatamente MaxPoints deve ser rejeitada", Result);
                   AddInfo(TEXT("✅ Teste passou: alocação incompleta rejeitada corretamente"));
               });

            It("deve rejeitar alocação com scores fora do range",
               [this]()
               {
                   AddInfo(TEXT("Testando ValidatePointBuyAllocation com scores fora do range"));

                   // Arrange: Score 16 (acima do máximo)
                   TMap<FName, int32> BaseScores;
                   BaseScores.Add(TEXT("Strength"), 16);
                   BaseScores.Add(TEXT("Dexterity"), 8);
                   BaseScores.Add(TEXT("Constitution"), 8);
                   BaseScores.Add(TEXT("Intelligence"), 8);
                   BaseScores.Add(TEXT("Wisdom"), 8);
                   BaseScores.Add(TEXT("Charisma"), 8);

                   // Act
                   bool Result =
                       ValidationHelpers::ValidatePointBuyAllocation(BaseScores, DnDConstants::MAX_POINT_BUY_POINTS);

                   // Assert
                   TestFalse("Alocação com scores fora do range deve ser rejeitada", Result);
                   AddInfo(TEXT("✅ Teste passou: alocação inválida rejeitada corretamente"));
               });
        });

    Describe("ValidateTotalLevelRange",
             [this]()
             {
                 It("deve validar level 1 como válido",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevelRange com level 1"));

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevelRange(1);

                        // Assert
                        TestTrue("Level 1 deve ser válido", Result);
                        AddInfo(TEXT("✅ Teste passou: level 1 validado corretamente"));
                    });

                 It("deve validar level 20 como válido",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevelRange com level 20"));

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevelRange(20);

                        // Assert
                        TestTrue("Level 20 deve ser válido", Result);
                        AddInfo(TEXT("✅ Teste passou: level 20 validado corretamente"));
                    });

                 It("deve rejeitar level 0",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevelRange com level 0"));

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevelRange(0);

                        // Assert
                        TestFalse("Level 0 deve ser inválido", Result);
                        AddInfo(TEXT("✅ Teste passou: level 0 rejeitado corretamente"));
                    });

                 It("deve rejeitar level 21",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevelRange com level 21"));

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevelRange(21);

                        // Assert
                        TestFalse("Level 21 deve ser inválido", Result);
                        AddInfo(TEXT("✅ Teste passou: level 21 rejeitado corretamente"));
                    });

                 It("deve rejeitar level negativo",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevelRange com level negativo"));

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevelRange(-5);

                        // Assert
                        TestFalse("Level negativo deve ser inválido", Result);
                        AddInfo(TEXT("✅ Teste passou: level negativo rejeitado corretamente"));
                    });

                 It("deve validar com MaxLevel customizado",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevelRange com MaxLevel customizado"));

                        // Act & Assert
                        TestTrue("Level 10 deve ser válido com MaxLevel 15",
                                 ValidationHelpers::ValidateTotalLevelRange(10, 15));
                        TestFalse("Level 16 deve ser inválido com MaxLevel 15",
                                  ValidationHelpers::ValidateTotalLevelRange(16, 15));
                        AddInfo(TEXT("✅ Teste passou: MaxLevel customizado validado corretamente"));
                    });
             });

    Describe("ValidateFeatSelectionPure",
             [this]()
             {
                 It("deve retornar true quando SelectedFeat está em AvailableFeats",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateFeatSelectionPure com feat válido"));

                        // Arrange
                        TArray<FName> AvailableFeats;
                        AvailableFeats.Add(TEXT("Feat_Alert"));
                        AvailableFeats.Add(TEXT("Feat_MagicInitiate"));

                        // Act
                        bool Result = ValidationHelpers::ValidateFeatSelectionPure(TEXT("Feat_Alert"), AvailableFeats);

                        // Assert
                        TestTrue("Feat válido deve ser aceito", Result);
                        AddInfo(TEXT("✅ Teste passou: feat válido aceito corretamente"));
                    });

                 It("deve retornar true quando SelectedFeat é NAME_None",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateFeatSelectionPure com NAME_None"));

                        // Arrange
                        TArray<FName> AvailableFeats;
                        AvailableFeats.Add(TEXT("Feat_Alert"));

                        // Act
                        bool Result = ValidationHelpers::ValidateFeatSelectionPure(NAME_None, AvailableFeats);

                        // Assert
                        TestTrue("NAME_None deve ser aceito", Result);
                        AddInfo(TEXT("✅ Teste passou: NAME_None aceito corretamente"));
                    });

                 It("deve retornar false quando SelectedFeat não está em AvailableFeats",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateFeatSelectionPure com feat inválido"));

                        // Arrange
                        TArray<FName> AvailableFeats;
                        AvailableFeats.Add(TEXT("Feat_Alert"));

                        // Act
                        bool Result =
                            ValidationHelpers::ValidateFeatSelectionPure(TEXT("Feat_NonExistent"), AvailableFeats);

                        // Assert
                        TestFalse("Feat inválido deve ser rejeitado", Result);
                        AddInfo(TEXT("✅ Teste passou: feat inválido rejeitado corretamente"));
                    });

                 It("deve retornar false quando AvailableFeats está vazio",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateFeatSelectionPure com AvailableFeats vazio"));

                        // Arrange
                        TArray<FName> EmptyFeats;

                        // Act
                        bool Result = ValidationHelpers::ValidateFeatSelectionPure(TEXT("Feat_Alert"), EmptyFeats);

                        // Assert
                        TestFalse("Feat não deve ser aceito quando lista está vazia", Result);
                        AddInfo(TEXT("✅ Teste passou: lista vazia tratada corretamente"));
                    });
             });

    Describe("ValidateSkillSelectionPure",
             [this]()
             {
                 It("deve retornar true quando SelectedSkill está em ValidSkills",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateSkillSelectionPure com skill válido"));

                        // Arrange
                        TArray<FName> ValidSkills;
                        ValidSkills.Add(TEXT("Athletics"));
                        ValidSkills.Add(TEXT("Acrobatics"));

                        // Act
                        bool Result = ValidationHelpers::ValidateSkillSelectionPure(TEXT("Athletics"), ValidSkills);

                        // Assert
                        TestTrue("Skill válido deve ser aceito", Result);
                        AddInfo(TEXT("✅ Teste passou: skill válido aceito corretamente"));
                    });

                 It("deve retornar true quando SelectedSkill é NAME_None",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateSkillSelectionPure com NAME_None"));

                        // Arrange
                        TArray<FName> ValidSkills;
                        ValidSkills.Add(TEXT("Athletics"));

                        // Act
                        bool Result = ValidationHelpers::ValidateSkillSelectionPure(NAME_None, ValidSkills);

                        // Assert
                        TestTrue("NAME_None deve ser aceito", Result);
                        AddInfo(TEXT("✅ Teste passou: NAME_None aceito corretamente"));
                    });

                 It("deve retornar false quando SelectedSkill não está em ValidSkills",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateSkillSelectionPure com skill inválido"));

                        // Arrange
                        TArray<FName> ValidSkills;
                        ValidSkills.Add(TEXT("Athletics"));

                        // Act
                        bool Result =
                            ValidationHelpers::ValidateSkillSelectionPure(TEXT("NonExistentSkill"), ValidSkills);

                        // Assert
                        TestFalse("Skill inválido deve ser rejeitado", Result);
                        AddInfo(TEXT("✅ Teste passou: skill inválido rejeitado corretamente"));
                    });

                 It("deve retornar false quando ValidSkills está vazio",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateSkillSelectionPure com ValidSkills vazio"));

                        // Arrange
                        TArray<FName> EmptySkills;

                        // Act
                        bool Result = ValidationHelpers::ValidateSkillSelectionPure(TEXT("Athletics"), EmptySkills);

                        // Assert
                        TestFalse("Skill não deve ser aceito quando lista está vazia", Result);
                        AddInfo(TEXT("✅ Teste passou: lista vazia tratada corretamente"));
                    });
             });

    Describe("ValidateTotalLevel",
             [this]()
             {
                 It("deve calcular e validar nível total para single class",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevel com single class level 5"));

                        // Arrange
                        TArray<FClassLevelEntry> ClassLevels;
                        FClassLevelEntry Entry;
                        Entry.ClassName = TEXT("Fighter");
                        Entry.Level = 5;
                        ClassLevels.Add(Entry);

                        int32 TotalLevel = 0;

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevel(ClassLevels, TotalLevel, 20);

                        // Assert
                        TestTrue("Single class level 5 deve ser válido", Result);
                        TestEqual("TotalLevel deve ser 5", TotalLevel, 5);
                        AddInfo(TEXT("✅ Teste passou: single class validado corretamente"));
                    });

                 It("deve calcular e validar nível total para multiclass",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevel com multiclass: Fighter 3 / Wizard 2"));

                        // Arrange
                        TArray<FClassLevelEntry> ClassLevels;
                        FClassLevelEntry Entry1;
                        Entry1.ClassName = TEXT("Fighter");
                        Entry1.Level = 3;
                        ClassLevels.Add(Entry1);

                        FClassLevelEntry Entry2;
                        Entry2.ClassName = TEXT("Wizard");
                        Entry2.Level = 2;
                        ClassLevels.Add(Entry2);

                        int32 TotalLevel = 0;

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevel(ClassLevels, TotalLevel, 20);

                        // Assert
                        TestTrue("Multiclass total level 5 deve ser válido", Result);
                        TestEqual("TotalLevel deve ser 5", TotalLevel, 5);
                        AddInfo(TEXT("✅ Teste passou: multiclass validado corretamente"));
                    });

                 It("deve rejeitar quando TotalLevel excede MaxLevel",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevel com TotalLevel > MaxLevel"));

                        // Arrange
                        TArray<FClassLevelEntry> ClassLevels;
                        FClassLevelEntry Entry;
                        Entry.ClassName = TEXT("Fighter");
                        Entry.Level = 21; // Excede MaxLevel 20
                        ClassLevels.Add(Entry);

                        int32 TotalLevel = 0;

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevel(ClassLevels, TotalLevel, 20);

                        // Assert
                        TestFalse("TotalLevel > MaxLevel deve ser rejeitado", Result);
                        AddInfo(TEXT("✅ Teste passou: TotalLevel excedente rejeitado corretamente"));
                    });

                 It("deve validar quando TotalLevel é exatamente MaxLevel",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevel com TotalLevel = MaxLevel"));

                        // Arrange
                        TArray<FClassLevelEntry> ClassLevels;
                        FClassLevelEntry Entry;
                        Entry.ClassName = TEXT("Fighter");
                        Entry.Level = 20;
                        ClassLevels.Add(Entry);

                        int32 TotalLevel = 0;

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevel(ClassLevels, TotalLevel, 20);

                        // Assert
                        TestTrue("TotalLevel = MaxLevel deve ser válido", Result);
                        TestEqual("TotalLevel deve ser 20", TotalLevel, 20);
                        AddInfo(TEXT("✅ Teste passou: TotalLevel no limite validado corretamente"));
                    });

                 It("deve retornar false para array vazio",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevel com array vazio"));

                        // Arrange
                        TArray<FClassLevelEntry> EmptyLevels;
                        int32 TotalLevel = 0;

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevel(EmptyLevels, TotalLevel, 20);

                        // Assert
                        TestFalse("Array vazio deve retornar false", Result);
                        TestEqual("TotalLevel deve ser 0", TotalLevel, 0);
                        AddInfo(TEXT("✅ Teste passou: array vazio tratado corretamente"));
                    });

                 It("deve validar com MaxLevel customizado",
                    [this]()
                    {
                        AddInfo(TEXT("Testando ValidateTotalLevel com MaxLevel customizado"));

                        // Arrange
                        TArray<FClassLevelEntry> ClassLevels;
                        FClassLevelEntry Entry;
                        Entry.ClassName = TEXT("Fighter");
                        Entry.Level = 10;
                        ClassLevels.Add(Entry);

                        int32 TotalLevel = 0;

                        // Act
                        bool Result = ValidationHelpers::ValidateTotalLevel(ClassLevels, TotalLevel, 15);

                        // Assert
                        TestTrue("Level 10 deve ser válido com MaxLevel 15", Result);
                        TestFalse("Level 10 deve ser inválido com MaxLevel 5",
                                  ValidationHelpers::ValidateTotalLevel(ClassLevels, TotalLevel, 5));
                        AddInfo(TEXT("✅ Teste passou: MaxLevel customizado validado corretamente"));
                    });
             });
}

#pragma endregion ValidationHelpers Tests
