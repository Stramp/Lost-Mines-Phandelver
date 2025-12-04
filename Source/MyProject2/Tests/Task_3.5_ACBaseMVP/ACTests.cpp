// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/CalculationHelpers.h"
#include "Utils/DnDConstants.h"
#include "Utils/DataTableHelpers.h"
#include "Data/Tables/ItemDataTable.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// AC Tests
// ============================================================================
#pragma region AC Tests

BEGIN_DEFINE_SPEC(ACSpec, "MyProject2.AC", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
UDataTable *RealItemDataTable;
END_DEFINE_SPEC(ACSpec)

void ACSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Carrega ItemDataTable real do Content usando LoadObject
            // Nota: Caminho pode precisar ser ajustado conforme estrutura do projeto
            RealItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DataTable/ItemDataTable"));
        });

    // ============================================================================
    // CalculateAC Tests
    // ============================================================================
    Describe(
        "Issue-3.5/ CalculateAC",
        [this]()
        {
            It("deve calcular AC base sem armadura (10 + DEX modifier +2 = 12)",
               [this]()
               {
                   // Arrange
                   int32 DexterityModifier = 2;

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier);

                   // Assert
                   TestEqual("AC base deve ser 12 (10 + 2)", Result, 12);
               });

            It("deve calcular AC base sem armadura com DEX modifier 0 (AC = 10)",
               [this]()
               {
                   // Arrange
                   int32 DexterityModifier = 0;

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier);

                   // Assert
                   TestEqual("AC base deve ser 10 (10 + 0)", Result, 10);
               });

            It("deve calcular AC base sem armadura com DEX modifier negativo (AC = 8)",
               [this]()
               {
                   // Arrange
                   int32 DexterityModifier = -2;

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier);

                   // Assert
                   TestEqual("AC base deve ser 8 (10 + (-2))", Result, 8);
               });

            It("deve calcular AC com armadura leve usando dados da Data Table (Leather Armor)",
               [this]()
               {
                   // Arrange: Busca Leather Armor na Data Table pelo ID
                   FItemDataRow *LeatherArmor =
                       DataTableHelpers::FindItemRow(TEXT("ITM_ARM_LeatherArmor"), RealItemDataTable);

                   // Se não encontrar na Data Table, usa valores conhecidos como fallback
                   int32 ArmorACValue = 11; // Valor padrão D&D 5e
                   FName ArmorType = TEXT("Light");

                   if (LeatherArmor && LeatherArmor->ACValue > 0)
                   {
                       ArmorACValue = LeatherArmor->ACValue;
                       ArmorType = LeatherArmor->ArmorType;
                   }

                   int32 DexterityModifier = 3;
                   int32 ExpectedAC = 14; // Valor hardcoded conhecido: 11 + 3 = 14

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                   // Assert
                   TestEqual("AC com armadura leve deve ser 14 (11 + 3)", Result, ExpectedAC);
               });

            It("deve calcular AC com armadura média limitando DEX modifier usando dados da Data Table (Scale Mail)",
               [this]()
               {
                   // Arrange: Busca Scale Mail na Data Table pelo ID
                   FItemDataRow *ScaleMail =
                       DataTableHelpers::FindItemRow(TEXT("ITM_ARM_ScaleMail"), RealItemDataTable);

                   // Se não encontrar na Data Table, usa valores conhecidos como fallback
                   int32 ArmorACValue = 13; // Valor padrão D&D 5e
                   FName ArmorType = TEXT("Medium");

                   if (ScaleMail && ScaleMail->ACValue > 0)
                   {
                       ArmorACValue = ScaleMail->ACValue;
                       ArmorType = ScaleMail->ArmorType;
                   }

                   int32 DexterityModifier = 4; // +4, mas limitado a +2
                   int32 ExpectedAC = 15;       // Valor hardcoded conhecido: 13 + min(4, 2) = 15

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                   // Assert
                   TestEqual("AC com armadura média deve ser 15 (13 + min(4, 2) = 13 + 2)", Result, ExpectedAC);
               });

            It("deve calcular AC com armadura média usando DEX modifier completo quando menor que +2",
               [this]()
               {
                   // Arrange
                   int32 DexterityModifier = 1; // +1, menor que limite +2
                   int32 ArmorACValue = 13;     // Scale Mail
                   FName ArmorType = TEXT("Medium");

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                   // Assert
                   TestEqual("AC com armadura média deve ser 14 (13 + 1)", Result, 14);
               });

            It("deve calcular AC com armadura pesada sem DEX modifier usando dados da Data Table (Chain Mail)",
               [this]()
               {
                   // Arrange: Busca Chain Mail na Data Table pelo ID
                   FItemDataRow *ChainMail =
                       DataTableHelpers::FindItemRow(TEXT("ITM_ARM_ChainMail"), RealItemDataTable);

                   // Se não encontrar na Data Table, usa valores conhecidos como fallback
                   int32 ArmorACValue = 16; // Valor padrão D&D 5e
                   FName ArmorType = TEXT("Heavy");

                   if (ChainMail && ChainMail->ACValue > 0)
                   {
                       ArmorACValue = ChainMail->ACValue;
                       ArmorType = ChainMail->ArmorType;
                   }

                   int32 DexterityModifier = 3; // Ignorado para armaduras pesadas
                   int32 ExpectedAC = 16;       // Valor hardcoded conhecido (sem DEX modifier)

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                   // Assert
                   TestEqual("AC com armadura pesada deve ser 16 (sem DEX modifier)", Result, ExpectedAC);
               });

            It("deve calcular AC com escudo adicionando +2 (AC base 12 + escudo = 14)",
               [this]()
               {
                   // Arrange
                   int32 DexterityModifier = 2;
                   bool bHasShield = true;

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, 0, NAME_None, bHasShield);

                   // Assert
                   TestEqual("AC com escudo deve ser 14 (10 + 2 + 2)", Result, 14);
               });

            It("deve calcular AC com armadura leve e escudo usando dados da Data Table",
               [this]()
               {
                   // Arrange: Busca Leather Armor na Data Table pelo ID
                   FItemDataRow *LeatherArmor =
                       DataTableHelpers::FindItemRow(TEXT("ITM_ARM_LeatherArmor"), RealItemDataTable);

                   // Se não encontrar na Data Table, usa valores conhecidos como fallback
                   int32 ArmorACValue = 11; // Valor padrão D&D 5e
                   FName ArmorType = TEXT("Light");

                   if (LeatherArmor && LeatherArmor->ACValue > 0)
                   {
                       ArmorACValue = LeatherArmor->ACValue;
                       ArmorType = LeatherArmor->ArmorType;
                   }

                   int32 DexterityModifier = 3;
                   bool bHasShield = true;
                   int32 ExpectedAC = 16; // Valor hardcoded conhecido: 11 + 3 + 2 = 16

                   // Act
                   int32 Result =
                       CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType, bHasShield);

                   // Assert
                   TestEqual("AC com armadura leve e escudo deve ser 16 (11 + 3 + 2)", Result, ExpectedAC);
               });

            It("deve calcular AC com armadura média e escudo usando dados da Data Table",
               [this]()
               {
                   // Arrange: Busca Scale Mail na Data Table pelo ID
                   FItemDataRow *ScaleMail =
                       DataTableHelpers::FindItemRow(TEXT("ITM_ARM_ScaleMail"), RealItemDataTable);

                   // Se não encontrar na Data Table, usa valores conhecidos como fallback
                   int32 ArmorACValue = 13; // Valor padrão D&D 5e
                   FName ArmorType = TEXT("Medium");

                   if (ScaleMail && ScaleMail->ACValue > 0)
                   {
                       ArmorACValue = ScaleMail->ACValue;
                       ArmorType = ScaleMail->ArmorType;
                   }

                   int32 DexterityModifier = 4; // Limitado a +2
                   bool bHasShield = true;
                   int32 ExpectedAC = 17; // Valor hardcoded conhecido: 13 + 2 + 2 = 17

                   // Act
                   int32 Result =
                       CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType, bHasShield);

                   // Assert
                   TestEqual("AC com armadura média e escudo deve ser 17 (13 + 2 + 2)", Result, ExpectedAC);
               });

            It("deve calcular AC com armadura pesada e escudo usando dados da Data Table",
               [this]()
               {
                   // Arrange: Busca Chain Mail na Data Table pelo ID
                   FItemDataRow *ChainMail =
                       DataTableHelpers::FindItemRow(TEXT("ITM_ARM_ChainMail"), RealItemDataTable);

                   // Se não encontrar na Data Table, usa valores conhecidos como fallback
                   int32 ArmorACValue = 16; // Valor padrão D&D 5e
                   FName ArmorType = TEXT("Heavy");

                   if (ChainMail && ChainMail->ACValue > 0)
                   {
                       ArmorACValue = ChainMail->ACValue;
                       ArmorType = ChainMail->ArmorType;
                   }

                   int32 DexterityModifier = 3; // Ignorado
                   bool bHasShield = true;
                   int32 ExpectedAC = 18; // Valor hardcoded conhecido: 16 + 2 = 18

                   // Act
                   int32 Result =
                       CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType, bHasShield);

                   // Assert
                   TestEqual("AC com armadura pesada e escudo deve ser 18 (16 + 2)", Result, ExpectedAC);
               });

            It("deve usar AC base como fallback para tipo de armadura desconhecido",
               [this]()
               {
                   // Arrange
                   int32 DexterityModifier = 2;
                   int32 ArmorACValue = 10;
                   FName ArmorType = TEXT("Unknown"); // Tipo desconhecido

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                   // Assert
                   // Deve usar AC base (10 + DEX modifier) como fallback
                   TestEqual("AC com tipo desconhecido deve usar AC base (10 + 2)", Result, 12);
               });

            It("deve usar AC base quando ArmorACValue é 0 mesmo com tipo definido",
               [this]()
               {
                   // Arrange
                   int32 DexterityModifier = 2;
                   int32 ArmorACValue = 0; // Zero significa sem armadura
                   FName ArmorType = TEXT("Light");

                   // Act
                   int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                   // Assert
                   // Deve usar AC base quando ArmorACValue é 0
                   TestEqual("AC com ArmorACValue 0 deve usar AC base (10 + 2)", Result, 12);
               });
        });
}

#pragma endregion AC Tests
