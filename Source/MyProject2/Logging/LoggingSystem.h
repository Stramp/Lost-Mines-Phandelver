// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"

// Engine includes
#include "Engine/Engine.h"

#include "LoggingSystem.generated.h"

#pragma endregion Includes

// ============================================================================
// Log Categories
// ============================================================================
#pragma region Log Categories

/**
 * Categorias de log para organização.
 * Cada categoria representa um módulo/sistema do projeto.
 */
DEFINE_LOG_CATEGORY_STATIC(LogMyProject2DataTable, Log, All);
DEFINE_LOG_CATEGORY_STATIC(LogMyProject2Validation, Log, All);
DEFINE_LOG_CATEGORY_STATIC(LogMyProject2Multiclass, Log, All);

#pragma endregion Log Categories

// ============================================================================
// Log Severity Enum
// ============================================================================
#pragma region Log Severity Enum

/**
 * Níveis de severidade para logs.
 * Define a importância e persistência do log.
 */
UENUM(BlueprintType)
enum class ELogSeverity : uint8
{
    /** Log temporário para debug (não persiste) */
    Debug,

    /** Informação geral (não persiste) */
    Info,

    /** Aviso sobre configuração incorreta (persiste até correção) */
    Warning,

    /** Erro crítico que requer ação humana (persiste permanentemente) */
    Error,

    /** Erro fatal que impede funcionamento (persiste permanentemente) */
    Fatal
};

#pragma endregion Log Severity Enum

// ============================================================================
// Log Context Struct
// ============================================================================
#pragma region Log Context Struct

/**
 * Contexto do log para rastreamento e feedback.
 * Contém informações sobre onde e por que o log foi gerado.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FLogContext
{
    GENERATED_BODY()

    /** Módulo/sistema que gerou o log (ex: "DataTable", "Validation") */
    UPROPERTY(BlueprintReadOnly, Category = "Log Context")
    FString Module;

    /** Função/componente que gerou o log */
    UPROPERTY(BlueprintReadOnly, Category = "Log Context")
    FString Function;

    /** Asset/objeto relacionado ao log (pode ser vazio) */
    UPROPERTY(BlueprintReadOnly, Category = "Log Context")
    FString AssetName;

    /** Linha do código (para debug) */
    UPROPERTY(BlueprintReadOnly, Category = "Log Context")
    int32 LineNumber;

    FLogContext() : Module(TEXT("Unknown")), Function(TEXT("Unknown")), AssetName(TEXT("")), LineNumber(0) {}

    FLogContext(const FString &InModule, const FString &InFunction, const FString &InAssetName = TEXT(""),
                int32 InLineNumber = 0)
        : Module(InModule), Function(InFunction), AssetName(InAssetName), LineNumber(InLineNumber)
    {
    }
};

#pragma endregion Log Context Struct

// ============================================================================
// Logging System
// ============================================================================
#pragma region Logging System

/**
 * Sistema de logging centralizado para MyProject2.
 * Fornece logs temporários (debug) e permanentes (erros críticos).
 * Editor-Friendly: fornece feedback visual quando possível.
 *
 * Princípios:
 * - Funções puras e reutilizáveis
 * - Single Responsibility: cada função uma responsabilidade
 * - Modular: pode ser usado em qualquer parte do projeto
 * - Testável: funções isoladas e parameterizadas
 */
class MYPROJECT2_API FLoggingSystem
{
public:
    /**
     * Log temporário para debug (não persiste).
     * Usado durante desenvolvimento para rastreamento.
     *
     * @param Context Contexto do log (módulo, função, etc.)
     * @param Message Mensagem do log
     */
    static void LogDebug(const FLogContext &Context, const FString &Message);

    /**
     * Log de informação geral (não persiste).
     * Usado para eventos normais do sistema.
     *
     * @param Context Contexto do log
     * @param Message Mensagem do log
     */
    static void LogInfo(const FLogContext &Context, const FString &Message);

    /**
     * Log de aviso sobre configuração incorreta (persiste até correção).
     * Usado quando há problema de configuração que requer atenção.
     *
     * @param Context Contexto do log
     * @param Message Mensagem do log
     * @param bRequiresAction Se true, indica que ação humana é necessária
     */
    static void LogWarning(const FLogContext &Context, const FString &Message, bool bRequiresAction = true);

    /**
     * Log de erro crítico que requer ação humana (persiste permanentemente).
     * Usado para erros de configuração que impedem funcionamento correto.
     *
     * @param Context Contexto do log
     * @param Message Mensagem do log
     * @param bShowInEditor Se true, mostra feedback visual no editor
     */
    static void LogError(const FLogContext &Context, const FString &Message, bool bShowInEditor = true);

    /**
     * Log de erro fatal que impede funcionamento (persiste permanentemente).
     * Usado para erros que impedem completamente o funcionamento.
     *
     * @param Context Contexto do log
     * @param Message Mensagem do log
     */
    static void LogFatal(const FLogContext &Context, const FString &Message);

    /**
     * Log de erro de Data Table (especializado para tabelas).
     * Fornece feedback específico sobre problemas de configuração de tabelas.
     *
     * @param Context Contexto do log
     * @param TableName Nome da tabela com problema
     * @param RowName Nome da row com problema (pode ser vazio)
     * @param PropertyName Nome da propriedade com problema (pode ser vazio)
     * @param ErrorMessage Mensagem de erro específica
     */
    static void LogDataTableError(const FLogContext &Context, const FString &TableName, const FString &RowName,
                                  const FString &PropertyName, const FString &ErrorMessage);

    /**
     * Log de aviso de Data Table (especializado para tabelas).
     * Fornece feedback sobre problemas não críticos de configuração de tabelas.
     *
     * @param Context Contexto do log
     * @param TableName Nome da tabela com problema
     * @param RowName Nome da row com problema (pode ser vazio)
     * @param WarningMessage Mensagem de aviso específica
     */
    static void LogDataTableWarning(const FLogContext &Context, const FString &TableName, const FString &RowName,
                                    const FString &WarningMessage);

private:
    /**
     * Helper interno: formata mensagem completa com contexto.
     * Função pura e testável.
     *
     * @param Context Contexto do log
     * @param Message Mensagem do log
     * @return Mensagem formatada
     */
    static FString FormatLogMessage(const FLogContext &Context, const FString &Message);

    /**
     * Helper interno: obtém categoria de log baseada no módulo.
     * Função pura e testável.
     *
     * @param Module Nome do módulo
     * @return Categoria de log apropriada
     */
    static const FLogCategoryBase &GetLogCategory(const FString &Module);

#if WITH_EDITOR
    /**
     * Helper interno: mostra feedback visual no editor.
     * Apenas compilado em builds com editor.
     *
     * @param Context Contexto do log
     * @param Message Mensagem do log
     * @param Severity Severidade do log
     */
    static void ShowEditorFeedback(const FLogContext &Context, const FString &Message, ELogSeverity Severity);
#endif
};

#pragma endregion Logging System
