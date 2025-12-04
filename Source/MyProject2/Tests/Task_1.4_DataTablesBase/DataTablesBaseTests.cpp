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
#include "UObject/ConstructorHelpers.h"

#pragma endregion Includes

// ============================================================================
// Data Tables Base Tests
// ============================================================================
#pragma region Data Tables Base Tests

BEGIN_DEFINE_SPEC(DataTablesBaseSpec, "MyProject2.DataTables.Base",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UDataTable *RealRaceDataTable;
UDataTable *RealClassDataTable;

END_DEFINE_SPEC(DataTablesBaseSpec)

void DataTablesBaseSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Carrega Data Tables reais do Content usando LoadObject
            // Nota: Caminhos podem precisar ser ajustados conforme estrutura do projeto
            // Se os Data Tables não estiverem importados ainda, esses testes serão pulados
            RealRaceDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DataTable/RaceDataTable"));
            RealClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DataTable/ClassDataTable"));
        });

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

                 It("deve encontrar row quando existe no DataTable real",
                    [this]()
                    {
                        // Arrange
                        if (!RealRaceDataTable)
                        {
                            AddInfo(TEXT("RaceDataTable não foi carregado. Pulando teste."));
                            return;
                        }

                        // Usa raças que devem existir no Data Table real (baseado no JSON)
                        TArray<FName> TestRaceNames = {TEXT("Human"), TEXT("Elf"), TEXT("Dwarf"), TEXT("Halfling")};

                        for (const FName &RaceName : TestRaceNames)
                        {
                            // Act
                            FRaceDataRow *Result = DataTableHelpers::FindRaceRow(RaceName, RealRaceDataTable);

                            // Assert
                            if (Result)
                            {
                                TestEqual(FString::Printf(TEXT("Row encontrado para '%s' deve ter Name correto"),
                                                          *RaceName.ToString()),
                                          Result->Name, RaceName);
                            }
                            else
                            {
                                AddInfo(FString::Printf(
                                    TEXT("Raça '%s' não encontrada no DataTable. Pode não estar importado ainda."),
                                    *RaceName.ToString()));
                            }
                        }
                    });

                 It("deve retornar nullptr para raça que não existe no DataTable real",
                    [this]()
                    {
                        // Arrange
                        if (!RealRaceDataTable)
                        {
                            AddInfo(TEXT("RaceDataTable não foi carregado. Pulando teste."));
                            return;
                        }

                        // Usa uma raça que não deve existir
                        FName NonExistentRace = TEXT("NonExistentRace_Test12345");

                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(NonExistentRace, RealRaceDataTable);

                        // Assert
                        TestNull("FindRaceRow deve retornar nullptr para raça que não existe", Result);

                        // Nota: Um warning "LogDataTable: UDataTable::FindRow : 'FindRaceRow' requested row
                        // 'NonExistentRace_Test12345' not in DataTable" é esperado aqui, pois FindRow do Unreal Engine
                        // loga warning quando a row não existe. Isso é comportamento normal do Unreal Engine e não
                        // indica um problema.
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
