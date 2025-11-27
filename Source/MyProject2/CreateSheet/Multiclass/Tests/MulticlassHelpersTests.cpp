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
                   FeatureRow.FC_ID = TEXT("FC_SecondWind");
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
                   TestEqual("FeatureType deve ser Automatic", Result.FeatureType, FName(TEXT("Automatic")));
                   TestFalse("bHasAvailableChoices deve ser false para feature automática",
                             Result.bHasAvailableChoices);
                   AddInfo(TEXT("✅ Teste passou: feature automática não tem AvailableChoices e flag é false"));
               });

            It("deve definir AvailableChoices como NAME_None quando feature é do tipo Choice mas não tem "
               "AvailableChoices",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature Choice sem escolhas disponíveis"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Fighting Style");
                   FeatureRow.FC_ID = TEXT("FC_FightingStyle");
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
                   TestEqual("FeatureType deve ser Choice", Result.FeatureType, FName(TEXT("Choice")));
                   AddInfo(TEXT("✅ Teste passou: feature Choice sem escolhas não tem AvailableChoices"));
               });

            It("deve definir AvailableChoices como NAME_None quando feature é do tipo SubclassSelection mas não tem "
               "AvailableChoices",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature SubclassSelection sem escolhas disponíveis"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Martial Archetype");
                   FeatureRow.FC_ID = TEXT("FC_MartialArchetype");
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
                   TestEqual("FeatureType deve ser SubclassSelection", Result.FeatureType,
                             FName(TEXT("SubclassSelection")));
                   AddInfo(TEXT("✅ Teste passou: feature SubclassSelection sem escolhas não tem AvailableChoices"));
               });

            It("deve preencher AvailableChoices quando feature é do tipo Choice e tem escolhas disponíveis",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature Choice com escolhas disponíveis"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Fighting Style");
                   FeatureRow.FC_ID = TEXT("FC_FightingStyle");
                   FeatureRow.Description = FText::FromString(TEXT("Escolha um estilo de combate"));
                   FeatureRow.LevelUnlocked = 1;
                   FeatureRow.FeatureType = TEXT("Choice");

                   // Adiciona escolhas disponíveis
                   FFeatureChoice Choice1;
                   Choice1.ID = TEXT("FC_Archery");
                   Choice1.Name = TEXT("Archery");
                   FeatureRow.AvailableChoices.Add(Choice1);

                   FFeatureChoice Choice2;
                   Choice2.ID = TEXT("FC_Defense");
                   Choice2.Name = TEXT("Defense");
                   FeatureRow.AvailableChoices.Add(Choice2);

                   // Act
                   FMulticlassClassFeature Result =
                       FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(FeatureRow, 1);

                   // Assert
                   TestNotEqual("AvailableChoices não deve ser NAME_None quando há escolhas disponíveis",
                                Result.AvailableChoices, FName(NAME_None));
                   TestEqual("AvailableChoices deve ser o primeiro nome (Archery)", Result.AvailableChoices,
                             FName(TEXT("Archery")));
                   TestEqual("FeatureType deve ser Choice", Result.FeatureType, FName(TEXT("Choice")));
                   TestTrue("bHasAvailableChoices deve ser true quando há escolhas", Result.bHasAvailableChoices);
                   AddInfo(TEXT(
                       "✅ Teste passou: feature Choice com escolhas preenche AvailableChoices e flag corretamente"));
               });

            It("deve preencher AvailableChoices quando feature é do tipo SubclassSelection e tem escolhas disponíveis",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature SubclassSelection com escolhas disponíveis"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Martial Archetype");
                   FeatureRow.FC_ID = TEXT("FC_MartialArchetype");
                   FeatureRow.Description = FText::FromString(TEXT("Escolha um arquétipo marcial"));
                   FeatureRow.LevelUnlocked = 3;
                   FeatureRow.FeatureType = TEXT("SubclassSelection");

                   // Adiciona escolhas disponíveis
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
                   TestNotEqual("AvailableChoices não deve ser NAME_None quando há escolhas disponíveis",
                                Result.AvailableChoices, FName(NAME_None));
                   TestEqual("AvailableChoices deve ser o primeiro nome (Champion)", Result.AvailableChoices,
                             FName(TEXT("Champion")));
                   TestEqual("FeatureType deve ser SubclassSelection", Result.FeatureType,
                             FName(TEXT("SubclassSelection")));
                   TestTrue("bHasAvailableChoices deve ser true quando há escolhas", Result.bHasAvailableChoices);
                   AddInfo(TEXT("✅ Teste passou: feature SubclassSelection com escolhas preenche AvailableChoices e "
                                "flag corretamente"));
               });

            It("deve definir AvailableChoices como NAME_None quando feature é do tipo ASI",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature ASI (sem escolhas)"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Ability Score Improvement");
                   FeatureRow.FC_ID = TEXT("FC_ASI");
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
                   TestEqual("FeatureType deve ser ASI", Result.FeatureType, FName(TEXT("ASI")));
                   AddInfo(TEXT("✅ Teste passou: feature ASI não tem AvailableChoices"));
               });

            It("deve definir AvailableChoices como NAME_None quando feature é do tipo FeatSelection",
               [this]()
               {
                   AddInfo(TEXT("Testando conversão de feature FeatSelection (sem escolhas na tabela)"));

                   // Arrange
                   FFeatureDataRow FeatureRow;
                   FeatureRow.Name = TEXT("Feat Selection");
                   FeatureRow.FC_ID = TEXT("FC_FeatSelection");
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
                   TestEqual("FeatureType deve ser FeatSelection", Result.FeatureType, FName(TEXT("FeatSelection")));
                   AddInfo(TEXT("✅ Teste passou: feature FeatSelection não tem AvailableChoices na tabela"));
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

            It("deve retornar false quando feature é Choice mas AvailableChoices é NAME_None",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature Choice sem escolhas"));

                   // Arrange
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("Choice");
                   Feature.AvailableChoices = NAME_None;

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestFalse("Feature Choice sem escolhas deve retornar false", bHasChoices);
                   AddInfo(TEXT("✅ Teste passou: helper retorna false para Choice sem escolhas"));
               });

            It("deve retornar true quando feature é Choice e AvailableChoices não é NAME_None",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature Choice com escolhas"));

                   // Arrange
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("Choice");
                   Feature.AvailableChoices = TEXT("Archery");

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestTrue("Feature Choice com escolhas deve retornar true", bHasChoices);
                   AddInfo(TEXT("✅ Teste passou: helper retorna true para Choice com escolhas"));
               });

            It("deve retornar true quando feature é SubclassSelection e AvailableChoices não é NAME_None",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature SubclassSelection com escolhas"));

                   // Arrange
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("SubclassSelection");
                   Feature.AvailableChoices = TEXT("Champion");

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestTrue("Feature SubclassSelection com escolhas deve retornar true", bHasChoices);
                   AddInfo(TEXT("✅ Teste passou: helper retorna true para SubclassSelection com escolhas"));
               });

            It("deve retornar false quando feature é Automatic mesmo com AvailableChoices preenchido",
               [this]()
               {
                   AddInfo(TEXT("Testando helper: feature Automatic não deve ter escolhas mesmo se AvailableChoices "
                                "preenchido"));

                   // Arrange
                   FMulticlassClassFeature Feature;
                   Feature.FeatureType = TEXT("Automatic");
                   Feature.AvailableChoices = TEXT("Archery"); // Preenchido mas não deve contar

                   // Act
                   bool bHasChoices = FMulticlassHelpers::FeatureHasAvailableChoices(Feature);

                   // Assert
                   TestFalse("Feature Automatic não deve ter escolhas mesmo com AvailableChoices preenchido",
                             bHasChoices);
                   AddInfo(TEXT(
                       "✅ Teste passou: helper retorna false para Automatic mesmo com AvailableChoices preenchido"));
               });
        });
}

#pragma endregion MulticlassHelpers Tests
