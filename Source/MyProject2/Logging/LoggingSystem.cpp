// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "LoggingSystem.h"

// Engine includes
#include "Engine/Engine.h"

#if WITH_EDITOR
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "EditorStyleSet.h"
#endif

#pragma endregion Includes

// ============================================================================
// Log Categories Definition
// ============================================================================
#pragma region Log Categories Definition

// Categorias já definidas no header com DEFINE_LOG_CATEGORY_STATIC

#pragma endregion Log Categories Definition

// ============================================================================
// Log Message Formatting
// ============================================================================
#pragma region Log Message Formatting

FString FLoggingSystem::FormatLogMessage(const FLogContext &Context, const FString &Message)
{
    FString FormattedMessage;

    // Adiciona módulo e função
    FormattedMessage = FString::Printf(TEXT("[%s::%s]"), *Context.Module, *Context.Function);

    // Adiciona asset se disponível
    if (!Context.AssetName.IsEmpty())
    {
        FormattedMessage += FString::Printf(TEXT(" [Asset: %s]"), *Context.AssetName);
    }

    // Adiciona mensagem
    FormattedMessage += FString::Printf(TEXT(" %s"), *Message);

    return FormattedMessage;
}

#pragma endregion Log Message Formatting

// ============================================================================
// Log Category Selection
// ============================================================================
#pragma region Log Category Selection

const FLogCategoryBase &FLoggingSystem::GetLogCategory(const FString &Module)
{
    // Mapeia módulo para categoria de log apropriada
    if (Module.Contains(TEXT("DataTable")) || Module.Contains(TEXT("Table")))
    {
        return LogMyProject2DataTable;
    }
    else if (Module.Contains(TEXT("Validation")) || Module.Contains(TEXT("Validator")))
    {
        return LogMyProject2Validation;
    }
    else if (Module.Contains(TEXT("Multiclass")))
    {
        return LogMyProject2Multiclass;
    }

    // Fallback: usa categoria geral
    return LogMyProject2DataTable;
}

#pragma endregion Log Category Selection

// ============================================================================
// Public Log Functions
// ============================================================================
#pragma region Public Log Functions

void FLoggingSystem::LogDebug(const FLogContext &Context, const FString &Message)
{
    const FString FormattedMessage = FormatLogMessage(Context, Message);
    const FLogCategoryBase &LogCategory = GetLogCategory(Context.Module);

    UE_LOG(LogMyProject2DataTable, Verbose, TEXT("%s"), *FormattedMessage);
}

void FLoggingSystem::LogInfo(const FLogContext &Context, const FString &Message)
{
    const FString FormattedMessage = FormatLogMessage(Context, Message);
    const FLogCategoryBase &LogCategory = GetLogCategory(Context.Module);

    UE_LOG(LogMyProject2DataTable, Log, TEXT("%s"), *FormattedMessage);
}

void FLoggingSystem::LogWarning(const FLogContext &Context, const FString &Message, bool bRequiresAction)
{
    const FString FormattedMessage = FormatLogMessage(Context, Message);
    const FLogCategoryBase &LogCategory = GetLogCategory(Context.Module);

    FString FullMessage = FormattedMessage;
    if (bRequiresAction)
    {
        FullMessage += TEXT(" [REQUIRES ACTION]");
    }

    UE_LOG(LogMyProject2DataTable, Warning, TEXT("%s"), *FullMessage);

#if WITH_EDITOR
    if (bRequiresAction)
    {
        ShowEditorFeedback(Context, Message, ELogSeverity::Warning);
    }
#endif
}

void FLoggingSystem::LogError(const FLogContext &Context, const FString &Message, bool bShowInEditor)
{
    const FString FormattedMessage = FormatLogMessage(Context, Message);
    const FLogCategoryBase &LogCategory = GetLogCategory(Context.Module);

    UE_LOG(LogMyProject2DataTable, Error, TEXT("%s"), *FormattedMessage);

#if WITH_EDITOR
    if (bShowInEditor)
    {
        ShowEditorFeedback(Context, Message, ELogSeverity::Error);
    }
#endif
}

void FLoggingSystem::LogFatal(const FLogContext &Context, const FString &Message)
{
    const FString FormattedMessage = FormatLogMessage(Context, Message);
    const FLogCategoryBase &LogCategory = GetLogCategory(Context.Module);

    UE_LOG(LogMyProject2DataTable, Fatal, TEXT("%s"), *FormattedMessage);

#if WITH_EDITOR
    ShowEditorFeedback(Context, Message, ELogSeverity::Fatal);
#endif
}

#pragma endregion Public Log Functions

// ============================================================================
// Specialized Log Functions
// ============================================================================
#pragma region Specialized Log Functions

void FLoggingSystem::LogDataTableError(const FLogContext &Context, const FString &TableName, const FString &RowName,
                                       const FString &PropertyName, const FString &ErrorMessage)
{
    FString FullMessage = FString::Printf(TEXT("Data Table Error - Table: '%s'"), *TableName);

    if (!RowName.IsEmpty())
    {
        FullMessage += FString::Printf(TEXT(", Row: '%s'"), *RowName);
    }

    if (!PropertyName.IsEmpty())
    {
        FullMessage += FString::Printf(TEXT(", Property: '%s'"), *PropertyName);
    }

    FullMessage += FString::Printf(TEXT(" - %s"), *ErrorMessage);

    LogError(Context, FullMessage, true);
}

void FLoggingSystem::LogDataTableWarning(const FLogContext &Context, const FString &TableName, const FString &RowName,
                                         const FString &WarningMessage)
{
    FString FullMessage = FString::Printf(TEXT("Data Table Warning - Table: '%s'"), *TableName);

    if (!RowName.IsEmpty())
    {
        FullMessage += FString::Printf(TEXT(", Row: '%s'"), *RowName);
    }

    FullMessage += FString::Printf(TEXT(" - %s"), *WarningMessage);

    LogWarning(Context, FullMessage, true);
}

#pragma endregion Specialized Log Functions

// ============================================================================
// Editor Feedback
// ============================================================================
#pragma region Editor Feedback

#if WITH_EDITOR

void FLoggingSystem::ShowEditorFeedback(const FLogContext &Context, const FString &Message, ELogSeverity Severity)
{
    // Cria notificação no editor
    FNotificationInfo NotificationInfo(FText::FromString(Message));
    NotificationInfo.bFireAndForget = false;
    NotificationInfo.bUseLargeFont = (Severity == ELogSeverity::Error || Severity == ELogSeverity::Fatal);
    NotificationInfo.ExpireDuration =
        (Severity == ELogSeverity::Error || Severity == ELogSeverity::Fatal) ? 10.0f : 5.0f;

    // Define cor baseada na severidade
    // Nota: Imagens podem ser adicionadas depois se necessário
    // Por enquanto, o texto e duração já indicam a severidade

    // Adiciona detalhes do contexto
    FString DetailText = FString::Printf(TEXT("Module: %s\nFunction: %s"), *Context.Module, *Context.Function);
    if (!Context.AssetName.IsEmpty())
    {
        DetailText += FString::Printf(TEXT("\nAsset: %s"), *Context.AssetName);
    }
    NotificationInfo.HyperlinkText = FText::FromString(DetailText);

    // Mostra notificação
    FSlateNotificationManager::Get().AddNotification(NotificationInfo);
}

#endif // WITH_EDITOR

#pragma endregion Editor Feedback
