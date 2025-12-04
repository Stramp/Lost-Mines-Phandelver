// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/DataTableRowHandleHelpers.h"
#include "Engine/DataTable.h"
#include "Data/Tables/RaceDataTable.h"

#pragma endregion Includes

// ============================================================================
// DataTableRowHandleHelpers Tests
// ============================================================================
#pragma region DataTableRowHandleHelpers Tests

BEGIN_DEFINE_SPEC(DataTableRowHandleHelpersSpec, "MyProject2.Utils.DataTableRowHandleHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UDataTable* TestDataTable;
FName TestRowName;

END_DEFINE_SPEC(DataTableRowHandleHelpersSpec)

void DataTableRowHandleHelpersSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar DataTable de teste
            TestDataTable = NewObject<UDataTable>();
            TestDataTable->RowStruct = FRaceDataRow::StaticStruct();
            TestRowName = FName("TestRace");

            // Adicionar uma row de teste
            FRaceDataRow* TestRow = new FRaceDataRow();
            TestRow->Name = FName("Elf");
            TestDataTable->AddRow(TestRowName, *TestRow);
        });

    AfterEach(
        [this]()
        {
            // Cleanup
            if (TestDataTable)
            {
                TestDataTable->ConditionalBeginDestroy();
            }
        });

    Describe("ResolveHandle",
             [this]()
             {
                 It("deve retornar row quando handle é válido",
                    [this]()
                    {
                        // Arrange
                        FDataTableRowHandle Handle;
                        Handle.DataTable = TestDataTable;
                        Handle.RowName = TestRowName;

                        // Act
                        const FRaceDataRow* Result = DataTableRowHandleHelpers::ResolveHandle<FRaceDataRow>(Handle);

                        // Assert
                        TestNotNull("Result não deve ser nullptr", Result);
                        if (Result)
                        {
                            TestEqual("Name deve ser Elf", Result->Name, FName("Elf"));
                        }
                    });

                 It("deve retornar nullptr quando handle é inválido",
                    [this]()
                    {
                        // Arrange
                        FDataTableRowHandle InvalidHandle;

                        // Act
                        const FRaceDataRow* Result = DataTableRowHandleHelpers::ResolveHandle<FRaceDataRow>(InvalidHandle);

                        // Assert
                        TestNull("Result deve ser nullptr para handle inválido", Result);
                    });

                 It("deve retornar nullptr quando row não existe",
                    [this]()
                    {
                        // Arrange
                        FDataTableRowHandle Handle;
                        Handle.DataTable = TestDataTable;
                        Handle.RowName = FName("NonExistentRow");

                        // Act
                        const FRaceDataRow* Result = DataTableRowHandleHelpers::ResolveHandle<FRaceDataRow>(Handle);

                        // Assert
                        TestNull("Result deve ser nullptr quando row não existe", Result);
                    });
             });

    Describe("CreateHandle",
             [this]()
             {
                 It("deve criar handle válido quando row existe",
                    [this]()
                    {
                        // Act
                        FDataTableRowHandle Handle = DataTableRowHandleHelpers::CreateHandle(TestDataTable, TestRowName);

                        // Assert
                        TestTrue(TEXT("Handle deve ser válido"), DataTableRowHandleHelpers::IsHandleValid(Handle));
                        TestTrue(TEXT("Handle deve apontar para DataTable correto"), Handle.DataTable == TestDataTable);
                        TestEqual(TEXT("Handle deve apontar para RowName correto"), Handle.RowName, TestRowName);
                    });

                 It("deve criar handle inválido quando DataTable é nullptr",
                    [this]()
                    {
                        // Act
                        FDataTableRowHandle Handle = DataTableRowHandleHelpers::CreateHandle(nullptr, TestRowName);

                        // Assert
                        TestFalse("Handle deve ser inválido", DataTableRowHandleHelpers::IsHandleValid(Handle));
                    });

                 It("deve criar handle inválido quando RowName é NAME_None",
                    [this]()
                    {
                        // Act
                        FDataTableRowHandle Handle = DataTableRowHandleHelpers::CreateHandle(TestDataTable, NAME_None);

                        // Assert
                        TestFalse("Handle deve ser inválido", DataTableRowHandleHelpers::IsHandleValid(Handle));
                    });

                 It("deve criar handle inválido quando row não existe",
                    [this]()
                    {
                        // Act
                        FDataTableRowHandle Handle = DataTableRowHandleHelpers::CreateHandle(TestDataTable, FName("NonExistentRow"));

                        // Assert
                        TestFalse("Handle deve ser inválido quando row não existe", DataTableRowHandleHelpers::IsHandleValid(Handle));
                    });
             });

    Describe("IsHandleValid",
             [this]()
             {
                 It("deve retornar true quando handle é válido",
                    [this]()
                    {
                        // Arrange
                        FDataTableRowHandle Handle;
                        Handle.DataTable = TestDataTable;
                        Handle.RowName = TestRowName;

                        // Act
                        bool Result = DataTableRowHandleHelpers::IsHandleValid(Handle);

                        // Assert
                        TestTrue("Handle válido deve retornar true", Result);
                    });

                 It("deve retornar false quando handle é null",
                    [this]()
                    {
                        // Arrange
                        FDataTableRowHandle NullHandle;

                        // Act
                        bool Result = DataTableRowHandleHelpers::IsHandleValid(NullHandle);

                        // Assert
                        TestFalse("Handle null deve retornar false", Result);
                    });

                 It("deve retornar false quando DataTable é nullptr",
                    [this]()
                    {
                        // Arrange
                        FDataTableRowHandle Handle;
                        Handle.DataTable = nullptr;
                        Handle.RowName = TestRowName;

                        // Act
                        bool Result = DataTableRowHandleHelpers::IsHandleValid(Handle);

                        // Assert
                        TestFalse("Handle com DataTable nullptr deve retornar false", Result);
                    });

                 It("deve retornar false quando row não existe",
                    [this]()
                    {
                        // Arrange
                        FDataTableRowHandle Handle;
                        Handle.DataTable = TestDataTable;
                        Handle.RowName = FName("NonExistentRow");

                        // Act
                        bool Result = DataTableRowHandleHelpers::IsHandleValid(Handle);

                        // Assert
                        TestFalse("Handle com row inexistente deve retornar false", Result);
                    });
             });
}

#pragma endregion DataTableRowHandleHelpers Tests
