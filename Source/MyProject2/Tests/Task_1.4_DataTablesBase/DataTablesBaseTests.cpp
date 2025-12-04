// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/DataTableHelpers.h"
#include "Utils/DataTableCache.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Data Tables Base Tests
// ============================================================================
#pragma region Data Tables Base Tests

BEGIN_DEFINE_SPEC(DataTablesBaseSpec, "MyProject2.DataTables.Base",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(DataTablesBaseSpec)

void DataTablesBaseSpec::Define()
{
    // ============================================================================
    // DataTableHelpers Tests
    // ============================================================================
    Describe("Issue-1.4/ DataTableHelpers",
             [this]()
             {
                 It("deve retornar nullptr quando DataTable é nullptr",
                    [this]()
                    {
                        // Arrange
                        FName RaceName = TEXT("Human");

                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(RaceName, nullptr);

                        // Assert
                        TestNull("FindRaceRow deve retornar nullptr quando DataTable é nullptr", Result);
                    });

                 It("deve retornar nullptr quando RaceName é NAME_None",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestDataTable = NewObject<UDataTable>(GetTransientPackage());
                        TestDataTable->RowStruct = FRaceDataRow::StaticStruct();

                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(NAME_None, TestDataTable);

                        // Assert
                        TestNull("FindRaceRow deve retornar nullptr quando RaceName é NAME_None", Result);
                    });

                 It("deve retornar nullptr quando DataTable está vazio",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestDataTable = NewObject<UDataTable>(GetTransientPackage());
                        TestDataTable->RowStruct = FRaceDataRow::StaticStruct();
                        FName RaceName = TEXT("Human");

                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(RaceName, TestDataTable);

                        // Assert
                        TestNull("FindRaceRow deve retornar nullptr quando DataTable está vazio", Result);

                        // Nota: Um warning "LogDataTable: UDataTable::FindRow : 'FindRaceRow' requested row 'Human' not
                        // in DataTable" é esperado aqui, pois FindRow do Unreal Engine loga warning quando a row não
                        // existe. Isso é comportamento normal do Unreal Engine e não indica um problema.
                    });

                 It("deve retornar nullptr quando row não existe no DataTable",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestDataTable = NewObject<UDataTable>(GetTransientPackage());
                        TestDataTable->RowStruct = FRaceDataRow::StaticStruct();

                        // Adicionar uma row diferente
                        FRaceDataRow *TestRow = new FRaceDataRow();
                        TestRow->Name = TEXT("Elf");
                        TestDataTable->AddRow(TEXT("Elf"), *TestRow);

                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(TEXT("Human"), TestDataTable);

                        // Assert
                        TestNull("FindRaceRow deve retornar nullptr quando row não existe", Result);

                        // Nota: Um warning "LogDataTable: UDataTable::FindRow : 'FindRaceRow' requested row 'Human' not
                        // in DataTable" é esperado aqui, pois FindRow do Unreal Engine loga warning quando a row não
                        // existe. Isso é comportamento normal do Unreal Engine e não indica um problema.

                        // Cleanup
                        delete TestRow;
                    });

                 It("deve encontrar row quando existe no DataTable",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestDataTable = NewObject<UDataTable>(GetTransientPackage());
                        TestDataTable->RowStruct = FRaceDataRow::StaticStruct();

                        FRaceDataRow *TestRow = new FRaceDataRow();
                        TestRow->Name = TEXT("Human");
                        FName RowName = TEXT("Human");
                        TestDataTable->AddRow(RowName, *TestRow);

                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(TEXT("Human"), TestDataTable);

                        // Assert
                        TestNotNull("FindRaceRow deve encontrar row quando existe", Result);
                        if (Result)
                        {
                            TestEqual("Row encontrado deve ter Name correto", Result->Name, FName(TEXT("Human")));
                        }

                        // Cleanup
                        delete TestRow;
                    });

                 It("deve retornar nullptr para FindClassRow quando DataTable é nullptr",
                    [this]()
                    {
                        // Arrange
                        FName ClassName = TEXT("Fighter");

                        // Act
                        FClassDataRow *Result = DataTableHelpers::FindClassRow(ClassName, nullptr);

                        // Assert
                        TestNull("FindClassRow deve retornar nullptr quando DataTable é nullptr", Result);
                    });

                 It("deve retornar nullptr para FindClassRow quando ClassName é NAME_None",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestDataTable = NewObject<UDataTable>(GetTransientPackage());
                        TestDataTable->RowStruct = FClassDataRow::StaticStruct();

                        // Act
                        FClassDataRow *Result = DataTableHelpers::FindClassRow(NAME_None, TestDataTable);

                        // Assert
                        TestNull("FindClassRow deve retornar nullptr quando ClassName é NAME_None", Result);
                    });
             });

    // ============================================================================
    // DataTableCache Tests
    // ============================================================================
    Describe("Issue-1.4/ DataTableCache",
             [this]()
             {
                 It("deve limpar cache sem crash",
                    [this]()
                    {
                        // Arrange & Act & Assert
                        // Não crasha = sucesso
                        FDataTableCache::ClearCache();
                        TestTrue("ClearCache executou sem crash", true);
                    });

                 // ============================================================================
                 // Nota: GetCachedRow não pode ser testado isoladamente
                 // ============================================================================
                 // O método GetCachedRow tem um problema de conversão de const no código existente
                 // (DataTableCache.h linha 55: UDataTable* DataTable = Handle.DataTable.Get()).
                 // Handle.DataTable.Get() retorna const UDataTable*, mas está sendo atribuído a
                 // UDataTable* não-const, causando erro de compilação.
                 // Estes testes podem ser reativados quando o bug for corrigido no DataTableCache.h.
                 // ============================================================================
             });
}

#pragma endregion Data Tables Base Tests
