// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/ProficiencyHelpers.h"
#include "Data/Tables/ProficiencyDataTable.h"

#pragma endregion Includes

// ============================================================================
// ProficiencyHelpers Tests
// ============================================================================
#pragma region ProficiencyHelpers Tests

BEGIN_DEFINE_SPEC(ProficiencyHelpersSpec, "MyProject2.Utils.ProficiencyHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(ProficiencyHelpersSpec)

void ProficiencyHelpersSpec::Define()
{
    Describe("GetProficiencyDataValue", [this]()
    {
        It("deve retornar valor quando chave existe", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("Damage"), TEXT("1d4"));

            // Act
            FString Result = ProficiencyHelpers::GetProficiencyDataValue(Row, TEXT("Damage"));

            // Assert
            TestEqual("Deve retornar 1d4", Result, TEXT("1d4"));
        });

        It("deve retornar string vazia quando chave não existe", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;

            // Act
            FString Result = ProficiencyHelpers::GetProficiencyDataValue(Row, TEXT("Damage"));

            // Assert
            TestTrue("Deve retornar string vazia", Result.IsEmpty());
        });
    });

    Describe("HasProficiencyData", [this]()
    {
        It("deve retornar true quando ProficiencyData não está vazio", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("Damage"), TEXT("1d4"));

            // Act
            bool Result = ProficiencyHelpers::HasProficiencyData(Row);

            // Assert
            TestTrue("Deve retornar true", Result);
        });

        It("deve retornar false quando ProficiencyData está vazio", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;

            // Act
            bool Result = ProficiencyHelpers::HasProficiencyData(Row);

            // Assert
            TestFalse("Deve retornar false", Result);
        });
    });

    Describe("GetProficiencyDataAsInt", [this]()
    {
        It("deve converter string numérica para int32", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("AC"), TEXT("15"));

            // Act
            int32 Result = ProficiencyHelpers::GetProficiencyDataAsInt(Row, TEXT("AC"), -1);

            // Assert
            TestEqual("Deve retornar 15", Result, 15);
        });

        It("deve retornar default quando chave não existe", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;

            // Act
            int32 Result = ProficiencyHelpers::GetProficiencyDataAsInt(Row, TEXT("AC"), -1);

            // Assert
            TestEqual("Deve retornar -1 (default)", Result, -1);
        });

        It("deve retornar default quando valor não é numérico", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("AC"), TEXT("invalid"));

            // Act
            int32 Result = ProficiencyHelpers::GetProficiencyDataAsInt(Row, TEXT("AC"), -1);

            // Assert
            TestEqual("Deve retornar -1 (default)", Result, -1);
        });
    });

    Describe("GetProficiencyDataAsFloat", [this]()
    {
        It("deve converter string numérica para float", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("Weight"), TEXT("3.5"));

            // Act
            float Result = ProficiencyHelpers::GetProficiencyDataAsFloat(Row, TEXT("Weight"), 0.0f);

            // Assert
            TestEqual("Deve retornar 3.5", Result, 3.5f, 0.001f);
        });

        It("deve retornar default quando chave não existe", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;

            // Act
            float Result = ProficiencyHelpers::GetProficiencyDataAsFloat(Row, TEXT("Weight"), 0.0f);

            // Assert
            TestEqual("Deve retornar 0.0 (default)", Result, 0.0f);
        });
    });

    Describe("GetProficiencyDataAsBool", [this]()
    {
        It("deve converter 'true' para bool true", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("StealthDisadvantage"), TEXT("true"));

            // Act
            bool Result = ProficiencyHelpers::GetProficiencyDataAsBool(Row, TEXT("StealthDisadvantage"), false);

            // Assert
            TestTrue("Deve retornar true", Result);
        });

        It("deve converter '1' para bool true", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("StealthDisadvantage"), TEXT("1"));

            // Act
            bool Result = ProficiencyHelpers::GetProficiencyDataAsBool(Row, TEXT("StealthDisadvantage"), false);

            // Assert
            TestTrue("Deve retornar true", Result);
        });

        It("deve converter 'false' para bool false", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("StealthDisadvantage"), TEXT("false"));

            // Act
            bool Result = ProficiencyHelpers::GetProficiencyDataAsBool(Row, TEXT("StealthDisadvantage"), true);

            // Assert
            TestFalse("Deve retornar false", Result);
        });

        It("deve converter '0' para bool false", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("StealthDisadvantage"), TEXT("0"));

            // Act
            bool Result = ProficiencyHelpers::GetProficiencyDataAsBool(Row, TEXT("StealthDisadvantage"), true);

            // Assert
            TestFalse("Deve retornar false", Result);
        });

        It("deve retornar default quando valor é inválido", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;
            Row.ProficiencyData.Add(TEXT("StealthDisadvantage"), TEXT("invalid"));

            // Act
            bool Result = ProficiencyHelpers::GetProficiencyDataAsBool(Row, TEXT("StealthDisadvantage"), false);

            // Assert
            TestFalse("Deve retornar false (default para valor inválido)", Result);
        });

        It("deve retornar default quando chave não existe", [this]()
        {
            // Arrange
            FProficiencyDataRow Row;

            // Act
            bool Result = ProficiencyHelpers::GetProficiencyDataAsBool(Row, TEXT("StealthDisadvantage"), false);

            // Assert
            TestFalse("Deve retornar false (default)", Result);
        });
    });
}

#pragma endregion ProficiencyHelpers Tests
