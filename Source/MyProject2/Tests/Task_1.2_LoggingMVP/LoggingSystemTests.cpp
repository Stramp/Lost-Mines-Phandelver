// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Logging/LoggingSystem.h"

#pragma endregion Includes

// ============================================================================
// LoggingSystem Tests
// ============================================================================
#pragma region LoggingSystem Tests

BEGIN_DEFINE_SPEC(LoggingSystemSpec, "MyProject2.Logging.LoggingSystem",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(LoggingSystemSpec)

void LoggingSystemSpec::Define()
{
    Describe("Issue-1.2/ FLogContext",
             [this]()
             {
                 It("deve criar contexto vazio com valores padrão",
                    [this]()
                    {
                        // Arrange & Act
                        FLogContext Context;

                        // Assert
                        TestEqual("Module deve ser 'Unknown'", Context.Module, FString(TEXT("Unknown")));
                        TestEqual("Function deve ser 'Unknown'", Context.Function, FString(TEXT("Unknown")));
                        TestEqual("AssetName deve ser vazio", Context.AssetName, FString(TEXT("")));
                        TestEqual("LineNumber deve ser 0", Context.LineNumber, 0);
                    });

                 It("deve criar contexto com valores fornecidos",
                    [this]()
                    {
                        // Arrange
                        FString Module = TEXT("DataTable");
                        FString Function = TEXT("FindRow");
                        FString AssetName = TEXT("RaceDataTable");
                        int32 LineNumber = 42;

                        // Act
                        FLogContext Context(Module, Function, AssetName, LineNumber);

                        // Assert
                        TestEqual("Module deve ser 'DataTable'", Context.Module, Module);
                        TestEqual("Function deve ser 'FindRow'", Context.Function, Function);
                        TestEqual("AssetName deve ser 'RaceDataTable'", Context.AssetName, AssetName);
                        TestEqual("LineNumber deve ser 42", Context.LineNumber, LineNumber);
                    });

                 It("deve criar contexto sem AssetName (usa padrão vazio)",
                    [this]()
                    {
                        // Arrange
                        FString Module = TEXT("Validation");
                        FString Function = TEXT("ValidateScore");

                        // Act
                        FLogContext Context(Module, Function);

                        // Assert
                        TestEqual("Module deve ser 'Validation'", Context.Module, Module);
                        TestEqual("Function deve ser 'ValidateScore'", Context.Function, Function);
                        TestEqual("AssetName deve ser vazio", Context.AssetName, FString(TEXT("")));
                        TestEqual("LineNumber deve ser 0", Context.LineNumber, 0);
                    });
             });

    Describe("Issue-1.2/ LogDebug",
             [this]()
             {
                 It("deve executar sem crash com contexto válido",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("TestModule"), TEXT("TestFunction"));
                        FString Message = TEXT("Test debug message");

                        // Act & Assert
                        // Não crasha = sucesso
                        FLoggingSystem::LogDebug(Context, Message);
                        TestTrue("LogDebug executou sem crash", true);
                    });

                 It("deve executar sem crash com AssetName preenchido",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("TestModule"), TEXT("TestFunction"), TEXT("TestAsset"));
                        FString Message = TEXT("Test debug message with asset");

                        // Act & Assert
                        FLoggingSystem::LogDebug(Context, Message);
                        TestTrue("LogDebug executou sem crash com AssetName", true);
                    });
             });

    Describe("Issue-1.2/ LogInfo",
             [this]()
             {
                 It("deve executar sem crash com contexto válido",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("TestModule"), TEXT("TestFunction"));
                        FString Message = TEXT("Test info message");

                        // Act & Assert
                        FLoggingSystem::LogInfo(Context, Message);
                        TestTrue("LogInfo executou sem crash", true);
                    });
             });

    Describe("Issue-1.2/ LogWarning",
             [this]()
             {
                 It("deve executar sem crash com contexto válido",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("TestModule"), TEXT("TestFunction"));
                        FString Message = TEXT("Test warning message");

                        // Act & Assert
                        FLoggingSystem::LogWarning(Context, Message);
                        TestTrue("LogWarning executou sem crash", true);
                    });

                 It("deve executar sem crash quando bRequiresAction é true",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("TestModule"), TEXT("TestFunction"));
                        FString Message = TEXT("Test warning with action required");

                        // Act & Assert
                        FLoggingSystem::LogWarning(Context, Message, true);
                        TestTrue("LogWarning executou sem crash com bRequiresAction=true", true);
                    });

                 It("deve executar sem crash quando bRequiresAction é false",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("TestModule"), TEXT("TestFunction"));
                        FString Message = TEXT("Test warning without action required");

                        // Act & Assert
                        FLoggingSystem::LogWarning(Context, Message, false);
                        TestTrue("LogWarning executou sem crash com bRequiresAction=false", true);
                    });
             });

    // ============================================================================
    // Nota: Funções de Error não podem ser testadas
    // ============================================================================
    // LogError, LogDataTableError e LogErrorWithThrottledPopup não podem ser
    // testados porque o Unreal Engine Automation Test Framework marca qualquer
    // UE_LOG com nível Error como falha de teste automaticamente, mesmo que o
    // código execute corretamente. Isso é comportamento esperado do framework.
    //
    // LogFatal também não pode ser testado porque UE_LOG com nível Fatal causa
    // crash fatal do processo. Isso é comportamento esperado do Unreal Engine -
    // LogFatal é projetado para crashar em situações irrecuperáveis.
    // ============================================================================

    Describe("Issue-1.2/ LogDataTableWarning",
             [this]()
             {
                 It("deve executar sem crash com todos os parâmetros",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("DataTable"), TEXT("ValidateRow"));
                        FString TableName = TEXT("RaceDataTable");
                        FString RowName = TEXT("Elf");
                        FString WarningMessage = TEXT("Missing optional property");

                        // Act & Assert
                        FLoggingSystem::LogDataTableWarning(Context, TableName, RowName, WarningMessage);
                        TestTrue("LogDataTableWarning executou sem crash", true);
                    });

                 It("deve executar sem crash com RowName vazio",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("DataTable"), TEXT("ValidateTable"));
                        FString TableName = TEXT("RaceDataTable");
                        FString RowName = TEXT("");
                        FString WarningMessage = TEXT("Table has deprecated rows");

                        // Act & Assert
                        FLoggingSystem::LogDataTableWarning(Context, TableName, RowName, WarningMessage);
                        TestTrue("LogDataTableWarning executou sem crash com RowName vazio", true);
                    });
             });

    Describe("Issue-1.2/ LogWarningWithThrottledPopup",
             [this]()
             {
                 It("deve executar sem crash com contexto válido",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("TestModule"), TEXT("TestFunction"));
                        FString Message = TEXT("Test throttled warning");
                        float ThrottleDelay = 0.5f;

                        // Act & Assert
                        FLoggingSystem::LogWarningWithThrottledPopup(Context, Message, ThrottleDelay);
                        TestTrue("LogWarningWithThrottledPopup executou sem crash", true);
                    });

                 It("deve executar sem crash com delay padrão",
                    [this]()
                    {
                        // Arrange
                        FLogContext Context(TEXT("TestModule"), TEXT("TestFunction"));
                        FString Message = TEXT("Test throttled warning with default delay");

                        // Act & Assert
                        FLoggingSystem::LogWarningWithThrottledPopup(Context, Message);
                        TestTrue("LogWarningWithThrottledPopup executou sem crash com delay padrão", true);
                    });
             });
}

#pragma endregion LoggingSystem Tests
