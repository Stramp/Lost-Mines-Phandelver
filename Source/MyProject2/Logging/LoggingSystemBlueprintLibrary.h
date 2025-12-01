// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoggingSystem.h"
#include "LoggingSystemBlueprintLibrary.generated.h"

#pragma endregion Includes

// ============================================================================
// Logging System Blueprint Library
// ============================================================================
#pragma region Logging System Blueprint Library

/**
 * Blueprint Function Library para expor FLoggingSystem ao Blueprint.
 *
 * Fornece funções simplificadas e completas para logging no Blueprint.
 *
 * Princípios:
 * - Versões simplificadas: apenas Module + Message (para uso rápido)
 * - Versões completas: Module + Function + Message + AssetName (para rastreamento detalhado)
 * - BlueprintCallable: funções disponíveis no Blueprint para uso em qualquer momento
 */
UCLASS()
class MYPROJECT2_API ULoggingSystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // ========================================================================
    // Simplified Log Functions (Module + Message only)
    // ========================================================================
#pragma region Simplified Log Functions

    /**
     * Log Debug simplificado (apenas Module + Message).
     * Versão simplificada para uso rápido no Blueprint.
     *
     * @param Module Módulo/sistema que gerou o log (ex: "Test", "MySystem")
     * @param Message Mensagem do log
     */
    UFUNCTION(BlueprintCallable, Category = "Logging|Simplified",
              meta = (ToolTip = "Log Debug simplificado (Module + Message apenas)"))
    static void LogDebug_Simple(const FString &Module, const FString &Message);

    /**
     * Log Info simplificado (apenas Module + Message).
     * Versão simplificada para uso rápido no Blueprint.
     *
     * @param Module Módulo/sistema que gerou o log (ex: "Test", "MySystem")
     * @param Message Mensagem do log
     */
    UFUNCTION(BlueprintCallable, Category = "Logging|Simplified",
              meta = (ToolTip = "Log Info simplificado (Module + Message apenas)"))
    static void LogInfo_Simple(const FString &Module, const FString &Message);

    /**
     * Log Warning simplificado (apenas Module + Message).
     * Versão simplificada para uso rápido no Blueprint.
     *
     * @param Module Módulo/sistema que gerou o log (ex: "Test", "MySystem")
     * @param Message Mensagem do log
     */
    UFUNCTION(BlueprintCallable, Category = "Logging|Simplified",
              meta = (ToolTip = "Log Warning simplificado (Module + Message apenas)"))
    static void LogWarning_Simple(const FString &Module, const FString &Message);

    /**
     * Log Error simplificado (apenas Module + Message).
     * Versão simplificada para uso rápido no Blueprint.
     *
     * @param Module Módulo/sistema que gerou o log (ex: "Test", "MySystem")
     * @param Message Mensagem do log
     */
    UFUNCTION(BlueprintCallable, Category = "Logging|Simplified",
              meta = (ToolTip = "Log Error simplificado (Module + Message apenas)"))
    static void LogError_Simple(const FString &Module, const FString &Message);

#pragma endregion Simplified Log Functions

    // ========================================================================
    // Complete Log Functions (Module + Function + Message + AssetName)
    // ========================================================================
#pragma region Complete Log Functions

    /**
     * Log Debug completo (Module + Function + Message + AssetName opcional).
     * Versão completa para rastreamento detalhado no Blueprint.
     *
     * @param Module Módulo/sistema que gerou o log (ex: "DataTable", "Validation")
     * @param Function Função/componente que gerou o log (ex: "LoadData", "Validate")
     * @param Message Mensagem do log
     * @param AssetName Nome do asset relacionado (opcional, pode ser vazio)
     */
    UFUNCTION(BlueprintCallable, Category = "Logging|Complete",
              meta = (ToolTip = "Log Debug completo (Module + Function + Message + AssetName opcional)"))
    static void LogDebug_Complete(const FString &Module, const FString &Function, const FString &Message,
                                  const FString &AssetName = TEXT(""));

    /**
     * Log Info completo (Module + Function + Message + AssetName opcional).
     * Versão completa para rastreamento detalhado no Blueprint.
     *
     * @param Module Módulo/sistema que gerou o log (ex: "DataTable", "Validation")
     * @param Function Função/componente que gerou o log (ex: "LoadData", "Validate")
     * @param Message Mensagem do log
     * @param AssetName Nome do asset relacionado (opcional, pode ser vazio)
     */
    UFUNCTION(BlueprintCallable, Category = "Logging|Complete",
              meta = (ToolTip = "Log Info completo (Module + Function + Message + AssetName opcional)"))
    static void LogInfo_Complete(const FString &Module, const FString &Function, const FString &Message,
                                 const FString &AssetName = TEXT(""));

    /**
     * Log Warning completo (Module + Function + Message + AssetName opcional).
     * Versão completa para rastreamento detalhado no Blueprint.
     *
     * @param Module Módulo/sistema que gerou o log (ex: "DataTable", "Validation")
     * @param Function Função/componente que gerou o log (ex: "LoadData", "Validate")
     * @param Message Mensagem do log
     * @param AssetName Nome do asset relacionado (opcional, pode ser vazio)
     */
    UFUNCTION(BlueprintCallable, Category = "Logging|Complete",
              meta = (ToolTip = "Log Warning completo (Module + Function + Message + AssetName opcional)"))
    static void LogWarning_Complete(const FString &Module, const FString &Function, const FString &Message,
                                    const FString &AssetName = TEXT(""));

    /**
     * Log Error completo (Module + Function + Message + AssetName opcional).
     * Versão completa para rastreamento detalhado no Blueprint.
     *
     * @param Module Módulo/sistema que gerou o log (ex: "DataTable", "Validation")
     * @param Function Função/componente que gerou o log (ex: "LoadData", "Validate")
     * @param Message Mensagem do log
     * @param AssetName Nome do asset relacionado (opcional, pode ser vazio)
     */
    UFUNCTION(BlueprintCallable, Category = "Logging|Complete",
              meta = (ToolTip = "Log Error completo (Module + Function + Message + AssetName opcional)"))
    static void LogError_Complete(const FString &Module, const FString &Function, const FString &Message,
                                  const FString &AssetName = TEXT(""));

#pragma endregion Complete Log Functions
};

#pragma endregion Logging System Blueprint Library
