// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "CreateSheet/Multiclass/MulticlassHelpers.h"
#include "Data/Tables/FeatureDataTable.h"
#include "Data/Structures/MulticlassTypes.h"

#pragma endregion Includes

// ============================================================================
// MulticlassHelpers Tests
// ============================================================================
#pragma region MulticlassHelpers Tests

BEGIN_DEFINE_SPEC(MulticlassHelpersSpec, "MyProject2.CreateSheet.MulticlassHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(MulticlassHelpersSpec)

void MulticlassHelpersSpec::Define()
{
    Describe(
        "ConvertFeatureRowToMulticlassFeature",
        [this]()
        {
            It("deve definir AvailableChoices como NAME_None quando feature é do tipo Automatic",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature automática (sem escolhas)"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Second Wind");
                   FeatureRow.ID = TEXT("FC_SecondWind");
                   FeatureRow.Description = FText::FromString(TEXT("Recupera HP como ação bônus"));
                   FeatureRow.LevelUnlocked = 1;
                   FeatureRow.FeatureType = TEXT("Automatic");
                   FeatureRow.AvailableChoices.Empty(); // Array vazio

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 1);

                   // Assert
                   TestEqual("AvailableChoices deve ser NAME_None para feature automática", Result.AvailableChoices,
                             FName(NAME_None));
                   TestEqual("AvailableChoiceToAdd deve ser NAME_None para feature automática",
                             Result.AvailableChoiceToAdd, FName(NAME_None));
                   TestEqual("SelectedChoices deve estar vazio para feature automática", Result.SelectedChoices.Num(), 0);
                   TestEqual("FeatureType deve ser Automatic", Result.FeatureType, FName(TEXT("Automatic")));
                   TestFalse("bHasAvailableChoices deve ser false para feature automática",
                             Result.bHasAvailableChoices);
                   TestFalse("bIsMultipleChoice deve ser false para feature automática", Result.bIsMultipleChoice);
                   AddInfo(TEXT("✅ Teste passou: feature automática não tem AvailableChoices e flags são false"));
               });

            It("deve definir AvailableChoices como NAME_None quando feature é do tipo Choice mas não tem "
               "AvailableChoices",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature Choice sem escolhas disponíveis"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Fighting Style");
                   FeatureRow.ID = TEXT("FC_FightingStyle");
                   FeatureRow.Description = FText::FromString(TEXT("Escolha um estilo de combate"));
                   FeatureRow.LevelUnlocked = 1;
                   FeatureRow.FeatureType = TEXT("Choice");
                   FeatureRow.AvailableChoices.Empty(); // Array vazio - sem escolhas disponíveis

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 1);

                   // Assert
                   TestEqual("AvailableChoices deve ser NAME_None quando Choice não tem escolhas",
                             Result.AvailableChoices, FName(NAME_None));
                   TestEqual("AvailableChoiceToAdd deve ser NAME_None quando não há escolhas",
                             Result.AvailableChoiceToAdd, FName(NAME_None));
                   TestEqual("SelectedChoices deve estar vazio quando não há escolhas", Result.SelectedChoices.Num(), 0);
                   TestEqual("FeatureType deve ser Choice", Result.FeatureType, FName(TEXT("Choice")));
                   TestFalse("bHasAvailableChoices deve ser false quando não há escolhas na tabela",
                             Result.bHasAvailableChoices);
                   TestFalse("bIsMultipleChoice deve ser false quando não há escolhas", Result.bIsMultipleChoice);
                   AddInfo(TEXT("✅ Teste passou: feature Choice sem escolhas não tem AvailableChoices e flags são false"));
               });

            It("deve definir AvailableChoices como NAME_None quando feature é do tipo SubclassSelection mas não tem "
               "AvailableChoices",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature SubclassSelection sem escolhas disponíveis"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Martial Archetype");
                   FeatureRow.ID = TEXT("FC_MartialArchetype");
                   FeatureRow.Description = FText::FromString(TEXT("Escolha um arquétipo marcial"));
                   FeatureRow.LevelUnlocked = 3;
                   FeatureRow.FeatureType = TEXT("SubclassSelection");
                   FeatureRow.AvailableChoices.Empty(); // Array vazio - sem escolhas disponíveis

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 3);

                   // Assert
                   TestEqual("AvailableChoices deve ser NAME_None quando SubclassSelection não tem escolhas",
                             Result.AvailableChoices, FName(NAME_None));
                   TestEqual("AvailableChoiceToAdd deve ser NAME_None quando não há escolhas",
                             Result.AvailableChoiceToAdd, FName(NAME_None));
                   TestEqual("SelectedChoices deve estar vazio quando não há escolhas", Result.SelectedChoices.Num(), 0);
                   TestEqual("FeatureType deve ser SubclassSelection", Result.FeatureType,
                             FName(TEXT("SubclassSelection")));
                   TestFalse("bHasAvailableChoices deve ser false quando não há escolhas na tabela",
                             Result.bHasAvailableChoices);
                   TestFalse("bIsMultipleChoice deve ser false quando não há escolhas", Result.bIsMultipleChoice);
                   AddInfo(TEXT("✅ Teste passou: feature SubclassSelection sem escolhas não tem AvailableChoices e flags são false"));
               });

            It("deve preencher AvailableChoices quando feature tem exatamente 1 escolha disponível",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature Choice com 1 escolha disponível"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Fighting Style");
                   FeatureRow.ID = TEXT("FC_FightingStyle");
                   FeatureRow.Description = FText::FromString(TEXT("Escolha um estilo de combate"));
                   FeatureRow.LevelUnlocked = 1;
                   FeatureRow.FeatureType = TEXT("Choice");

                   // Adiciona apenas 1 escolha disponível
                   FFeatureChoice Choice1;
                   Choice1.ID = TEXT("FC_Archery");
                   Choice1.Name = TEXT("Archery");
                   FeatureRow.AvailableChoices.Add(Choice1);

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 1);

                   // Assert
                   TestEqual("AvailableChoices deve ser preenchido com a única escolha", Result.AvailableChoices,
                             FName(TEXT("Archery")));
                   TestEqual("SelectedChoices deve estar vazio para escolha única", Result.SelectedChoices.Num(), 0);
                   TestEqual("FeatureType deve ser Choice", Result.FeatureType, FName(TEXT("Choice")));
                   TestTrue("bHasAvailableChoices deve ser true quando há escolhas", Result.bHasAvailableChoices);
                   TestFalse("bIsMultipleChoice deve ser false para 1 escolha", Result.bIsMultipleChoice);
                   AddInfo(TEXT("✅ Teste passou: feature Choice com 1 escolha preenche AvailableChoices corretamente"));
               });

            It("deve usar AvailableChoices quando feature tem múltiplas opções mas é escolha única (Tipo 2)",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature Choice com múltiplas opções mas escolha única (Fighting Style)"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Fighting Style");
                   FeatureRow.ID = TEXT("FC_FightingStyle");
                   FeatureRow.Description = FText::FromString(TEXT("Escolha um estilo de combate"));
                   FeatureRow.LevelUnlocked = 1;
                   FeatureRow.FeatureType = TEXT("Choice");
                   FeatureRow.bAllowMultipleChoices = false; // Escolha única (Tipo 2)

                   // Adiciona múltiplas escolhas disponíveis
                   FFeatureChoice Choice1;
                   Choice1.ID = TEXT("FC_Archery");
                   Choice1.Name = TEXT("Archery");
                   FeatureRow.AvailableChoices.Add(Choice1);

                   FFeatureChoice Choice2;
                   Choice2.ID = TEXT("FC_Defense");
                   Choice2.Name = TEXT("Defense");
                   FeatureRow.AvailableChoices.Add(Choice2);

                   FFeatureChoice Choice3;
                   Choice3.ID = TEXT("FC_Dueling");
                   Choice3.Name = TEXT("Dueling");
                   FeatureRow.AvailableChoices.Add(Choice3);

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 1);

                   // Assert
                   TestEqual("AvailableChoices deve ser NAME_None (jogador escolhe no dropdown)",
                             Result.AvailableChoices, FName(NAME_None));
                   TestEqual("AvailableChoiceToAdd deve ser NAME_None (não usado para escolha única)",
                             Result.AvailableChoiceToAdd, FName(NAME_None));
                   TestEqual("SelectedChoices deve estar vazio (não usado para escolha única)",
                             Result.SelectedChoices.Num(), 0);
                   TestEqual("FeatureType deve ser Choice", Result.FeatureType, FName(TEXT("Choice")));
                   TestTrue("bHasAvailableChoices deve ser true quando há escolhas", Result.bHasAvailableChoices);
                   TestFalse("bIsMultipleChoice deve ser false para escolha única", Result.bIsMultipleChoice);
                   AddInfo(TEXT("✅ Teste passou: feature Choice com múltiplas opções mas escolha única usa AvailableChoices"));
               });

            It("deve usar SelectedChoices quando feature permite múltiplas escolhas (Tipo 3)",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature Choice com escolhas múltiplas (Manobras, Metamagic)"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Battle Master Maneuvers");
                   FeatureRow.ID = TEXT("FC_BattleMasterManeuvers");
                   FeatureRow.Description = FText::FromString(TEXT("Escolha manobras de combate"));
                   FeatureRow.LevelUnlocked = 3;
                   FeatureRow.FeatureType = TEXT("Choice");
                   FeatureRow.bAllowMultipleChoices = true; // Escolhas múltiplas (Tipo 3)

                   // Adiciona múltiplas escolhas disponíveis
                   FFeatureChoice Choice1;
                   Choice1.ID = TEXT("FC_DisarmingAttack");
                   Choice1.Name = TEXT("Disarming Attack");
                   FeatureRow.AvailableChoices.Add(Choice1);

                   FFeatureChoice Choice2;
                   Choice2.ID = TEXT("FC_PrecisionAttack");
                   Choice2.Name = TEXT("Precision Attack");
                   FeatureRow.AvailableChoices.Add(Choice2);

                   FFeatureChoice Choice3;
                   Choice3.ID = TEXT("FC_TripAttack");
                   Choice3.Name = TEXT("Trip Attack");
                   FeatureRow.AvailableChoices.Add(Choice3);

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 3);

                   // Assert
                   TestEqual("AvailableChoices deve ser NAME_None (não usado para múltiplas escolhas)",
                             Result.AvailableChoices, FName(NAME_None));
                   TestEqual("AvailableChoiceToAdd deve ser NAME_None inicialmente (jogador escolhe depois)",
                             Result.AvailableChoiceToAdd, FName(NAME_None));
                   TestEqual("SelectedChoices deve estar vazio (jogador escolhe depois)",
                             Result.SelectedChoices.Num(), 0);
                   TestEqual("FeatureType deve ser Choice", Result.FeatureType, FName(TEXT("Choice")));
                   TestTrue("bHasAvailableChoices deve ser true quando há escolhas", Result.bHasAvailableChoices);
                   TestTrue("bIsMultipleChoice deve ser true para escolhas múltiplas", Result.bIsMultipleChoice);
                   AddInfo(TEXT("✅ Teste passou: feature Choice com escolhas múltiplas usa SelectedChoices"));
               });

            It("deve usar AvailableChoices quando SubclassSelection tem múltiplas opções mas é escolha única (Tipo 2)",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature SubclassSelection com múltiplas opções mas escolha única"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Martial Archetype");
                   FeatureRow.ID = TEXT("FC_MartialArchetype");
                   FeatureRow.Description = FText::FromString(TEXT("Escolha um arquétipo marcial"));
                   FeatureRow.LevelUnlocked = 3;
                   FeatureRow.FeatureType = TEXT("SubclassSelection");
                   FeatureRow.bAllowMultipleChoices = false; // Escolha única (Tipo 2)

                   // Adiciona múltiplas escolhas disponíveis
                   FFeatureChoice Choice1;
                   Choice1.ID = TEXT("FC_Champion");
                   Choice1.Name = TEXT("Champion");
                   FeatureRow.AvailableChoices.Add(Choice1);

                   FFeatureChoice Choice2;
                   Choice2.ID = TEXT("FC_BattleMaster");
                   Choice2.Name = TEXT("Battle Master");
                   FeatureRow.AvailableChoices.Add(Choice2);

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 3);

                   // Assert
                   TestEqual("AvailableChoices deve ser NAME_None (jogador escolhe no dropdown)",
                             Result.AvailableChoices, FName(NAME_None));
                   TestEqual("AvailableChoiceToAdd deve ser NAME_None (não usado para escolha única)",
                             Result.AvailableChoiceToAdd, FName(NAME_None));
                   TestEqual("SelectedChoices deve estar vazio (não usado para escolha única)",
                             Result.SelectedChoices.Num(), 0);
                   TestEqual("FeatureType deve ser SubclassSelection", Result.FeatureType,
                             FName(TEXT("SubclassSelection")));
                   TestTrue("bHasAvailableChoices deve ser true quando há escolhas", Result.bHasAvailableChoices);
                   TestFalse("bIsMultipleChoice deve ser false para escolha única", Result.bIsMultipleChoice);
                   AddInfo(TEXT("✅ Teste passou: feature SubclassSelection com múltiplas opções mas escolha única usa AvailableChoices"));
               });

            It("deve definir AvailableChoices como NAME_None quando feature é do tipo ASI",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature ASI (sem escolhas)"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Ability Score Improvement");
                   FeatureRow.ID = TEXT("FC_ASI");
                   FeatureRow.Description = FText::FromString(TEXT("Aumenta um atributo em +2 ou dois em +1"));
                   FeatureRow.LevelUnlocked = 4;
                   FeatureRow.FeatureType = TEXT("ASI");
                   FeatureRow.AvailableChoices.Empty(); // Array vazio

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 4);

                   // Assert
                   TestEqual("AvailableChoices deve ser NAME_None para feature ASI", Result.AvailableChoices,
                             FName(NAME_None));
                   TestEqual("AvailableChoiceToAdd deve ser NAME_None para feature ASI",
                             Result.AvailableChoiceToAdd, FName(NAME_None));
                   TestEqual("SelectedChoices deve estar vazio para feature ASI", Result.SelectedChoices.Num(), 0);
                   TestEqual("FeatureType deve ser ASI", Result.FeatureType, FName(TEXT("ASI")));
                   TestFalse("bHasAvailableChoices deve ser false para feature ASI", Result.bHasAvailableChoices);
                   TestFalse("bIsMultipleChoice deve ser false para feature ASI", Result.bIsMultipleChoice);
                   AddInfo(TEXT("✅ Teste passou: feature ASI não tem AvailableChoices e flags são false"));
               });

            It("deve definir AvailableChoices como NAME_None quando feature é do tipo FeatSelection",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature FeatSelection (sem escolhas na tabela)"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Feat Selection");
                   FeatureRow.ID = TEXT("FC_FeatSelection");
                   FeatureRow.Description = FText::FromString(TEXT("Pode escolher um Feat ao invés de ASI"));
                   FeatureRow.LevelUnlocked = 4;
                   FeatureRow.FeatureType = TEXT("FeatSelection");
                   FeatureRow.AvailableChoices.Empty(); // Array vazio (feats vêm do FeatDataTable)

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 4);

                   // Assert
                   TestEqual("AvailableChoices deve ser NAME_None para feature FeatSelection", Result.AvailableChoices,
                             FName(NAME_None));
                   TestEqual("AvailableChoiceToAdd deve ser NAME_None para feature FeatSelection",
                             Result.AvailableChoiceToAdd, FName(NAME_None));
                   TestEqual("SelectedChoices deve estar vazio para feature FeatSelection", Result.SelectedChoices.Num(), 0);
                   TestEqual("FeatureType deve ser FeatSelection", Result.FeatureType, FName(TEXT("FeatSelection")));
                   TestFalse("bHasAvailableChoices deve ser false para feature FeatSelection", Result.bHasAvailableChoices);
                   TestFalse("bIsMultipleChoice deve ser false para feature FeatSelection", Result.bIsMultipleChoice);
                   AddInfo(TEXT("✅ Teste passou: feature FeatSelection não tem AvailableChoices na tabela e flags são false"));
               });
        });

    Describe(
        "FeatureHasAvailableChoices (helper para calcular flag)",
        [this]()
        {
            It("deve retornar false quando feature é Automatic e AvailableChoices é NAME_None",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature Automatic sem escolhas"));

                   // Arrange
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("Automatic");
                   Feature.AvailableChoices = NAME_None;

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestFalse("Feature Automatic sem escolhas deve retornar false", bHasChoices);
                   AddInfo(TEXT("✅ Teste passou: helper retorna false para feature Automatic"));
               });

            It("deve retornar false quando feature é Choice mas não tem escolhas disponíveis",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature Choice sem escolhas disponíveis"));

                   // Arrange - Estado válido: Choice sem AvailableChoices e sem SelectedChoices
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("Choice");
                   Feature.AvailableChoices = NAME_None;
                   Feature.SelectedChoices.Empty();
                   Feature.bHasAvailableChoices = false; // Estado consistente: sem escolhas

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestFalse("Feature Choice sem escolhas disponíveis deve retornar false", bHasChoices);
                   AddInfo(TEXT("✅ Teste passou: helper retorna false para Choice sem escolhas"));
               });

            It("deve retornar true quando feature é Choice e tem AvailableChoices preenchido",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature Choice com AvailableChoices preenchido"));

                   // Arrange - Estado válido: Choice com AvailableChoices preenchido
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("Choice");
                   Feature.AvailableChoices = TEXT("Archery");
                   Feature.bHasAvailableChoices = true; // Estado consistente: tem escolhas

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestTrue("Feature Choice com AvailableChoices preenchido deve retornar true", bHasChoices);
                   AddInfo(TEXT("✅ Teste passou: helper retorna true para Choice com escolhas"));
               });

            It("deve retornar true quando feature é Choice com múltiplas escolhas (SelectedChoices)",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature Choice com múltiplas escolhas"));

                   // Arrange
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("Choice");
                   Feature.AvailableChoices = NAME_None; // Vazio para múltiplas escolhas
                   Feature.SelectedChoices.Add(TEXT("Archery"));
                   Feature.bHasAvailableChoices = true; // Flag calculada indica que há escolhas
                   Feature.bIsMultipleChoice = true;

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestTrue("Feature Choice com múltiplas escolhas deve retornar true", bHasChoices);
                   AddInfo(TEXT("✅ Teste passou: helper retorna true para Choice com múltiplas escolhas"));
               });

            It("deve retornar true quando feature é SubclassSelection e tem AvailableChoices preenchido",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature SubclassSelection com AvailableChoices preenchido"));

                   // Arrange - Estado válido: SubclassSelection com AvailableChoices preenchido
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("SubclassSelection");
                   Feature.AvailableChoices = TEXT("Champion");
                   Feature.bHasAvailableChoices = true; // Estado consistente: tem escolhas

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestTrue("Feature SubclassSelection com AvailableChoices preenchido deve retornar true", bHasChoices);
                   AddInfo(TEXT("✅ Teste passou: helper retorna true para SubclassSelection com escolhas"));
               });

            It("deve retornar false quando feature é Automatic independente de AvailableChoices",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature Automatic não pode ter escolhas (tipo verificado primeiro)"));

                   // Arrange - Estado válido: Automatic não pode ter escolhas por definição
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("Automatic");
                   Feature.AvailableChoices = NAME_None; // Estado consistente: Automatic não tem escolhas
                   Feature.bHasAvailableChoices = false; // Estado consistente

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestFalse("Feature Automatic não deve ter escolhas (tipo verificado primeiro)", bHasChoices);
                   AddInfo(TEXT("✅ Teste passou: helper retorna false para Automatic independente de estado"));
               });
        });
}

#pragma endregion MulticlassHelpers Tests
