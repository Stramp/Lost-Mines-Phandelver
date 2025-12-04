// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// ProficiencyDataTable Tests
// ============================================================================
#pragma region ProficiencyDataTable Tests

BEGIN_DEFINE_SPEC(ProficiencyDataTableSpec, "MyProject2.Data.Tables.ProficiencyDataTable",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UDataTable* TestProficiencyDataTable;

END_DEFINE_SPEC(ProficiencyDataTableSpec)

void ProficiencyDataTableSpec::Define()
{
    BeforeEach([this]()
    {
        TestProficiencyDataTable = NewObject<UDataTable>();
        TestProficiencyDataTable->RowStruct = FProficiencyDataRow::StaticStruct();
    });

    AfterEach([this]()
    {
        if (TestProficiencyDataTable)
        {
            TestProficiencyDataTable->ConditionalBeginDestroy();
        }
    });

    Describe("FProficiencyDataRow Structure", [this]()
    {
        It("deve ter campos básicos: Name, ID, Type, Description", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.Name = TEXT("Simple Weapons");
            Row.ID = TEXT("PW_Simple_Weapons");
            Row.Type = TEXT("Weapon");
            Row.Description = FText::FromString(TEXT("Proficiência com armas simples"));

            // Assert
            TestEqual(TEXT("Name deve ser Simple Weapons"), Row.Name, FName(TEXT("Simple Weapons")));
            TestEqual(TEXT("ID deve ser PW_Simple_Weapons"), Row.ID, FName(TEXT("PW_Simple_Weapons")));
            TestEqual(TEXT("Type deve ser Weapon"), Row.Type, FName(TEXT("Weapon")));
            TestTrue("Description não deve estar vazio", !Row.Description.IsEmpty());
        });

        It("deve ter ProficiencyData vazio por padrão (backward compatible)", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;

            // Assert
            TestEqual("ProficiencyData deve estar vazio por padrão", Row.ProficiencyData.Num(), 0);
        });

        It("deve permitir adicionar dados em ProficiencyData", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("Damage"), TEXT("1d4"));
            Row.ProficiencyData.Add(TEXT("DamageType"), TEXT("Bludgeoning"));

            // Assert
            TestEqual("ProficiencyData deve ter 2 entradas", Row.ProficiencyData.Num(), 2);
            TestTrue("ProficiencyData deve conter Damage", Row.ProficiencyData.Contains(TEXT("Damage")));
            TestEqual("Damage deve ser 1d4", Row.ProficiencyData[TEXT("Damage")], TEXT("1d4"));
        });
    });

    Describe("ProficiencyDataTable Integration", [this]()
    {
        It("deve carregar proficiência com ProficiencyData do Data Table", [this]()
        {
            // Arrange
            FProficiencyDataRow* WeaponRow = new FProficiencyDataRow();
            WeaponRow->Name = TEXT("Shortsword");
            WeaponRow->ID = TEXT("PW_Shortsword");
            WeaponRow->Type = TEXT("Weapon");
            WeaponRow->Description = FText::FromString(TEXT("Espada curta"));
            WeaponRow->ProficiencyData.Add(TEXT("Damage"), TEXT("1d6"));
            WeaponRow->ProficiencyData.Add(TEXT("DamageType"), TEXT("Piercing"));
            WeaponRow->ProficiencyData.Add(TEXT("Properties"), TEXT("Finesse,Light"));

            TestProficiencyDataTable->AddRow(TEXT("PW_Shortsword"), *WeaponRow);

            // Act
            const FProficiencyDataRow* FoundRow = TestProficiencyDataTable->FindRow<FProficiencyDataRow>(
                TEXT("PW_Shortsword"), TEXT("Test"));

            // Assert
            TestNotNull("Row deve ser encontrada", FoundRow);
            TestEqual("ProficiencyData deve ter 3 entradas", FoundRow->ProficiencyData.Num(), 3);
            TestTrue("ProficiencyData deve conter Damage", FoundRow->ProficiencyData.Contains(TEXT("Damage")));
            TestEqual("Damage deve ser 1d6", FoundRow->ProficiencyData[TEXT("Damage")], TEXT("1d6"));

            // Cleanup
            delete WeaponRow;
        });
    });
}

#pragma endregion ProficiencyDataTable Tests
