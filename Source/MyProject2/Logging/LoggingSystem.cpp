// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "LoggingSystem.h"

// Engine includes
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"

#if WITH_EDITOR
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "EditorStyleSet.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/CoreStyle.h"
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
// Throttled Log Functions
// ============================================================================
#pragma region Throttled Log Functions

void FLoggingSystem::LogWarningWithThrottledPopup(const FLogContext &Context, const FString &Message,
                                                  float ThrottleDelay)
{
    // Log imediato (UE_LOG) - sempre executa
    const FString FormattedMessage = FormatLogMessage(Context, Message);
    const FLogCategoryBase &LogCategory = GetLogCategory(Context.Module);

    FString FullMessage = FormattedMessage;
    FullMessage += TEXT(" [REQUIRES ACTION]");

    UE_LOG(LogMyProject2DataTable, Warning, TEXT("%s"), *FullMessage);

#if WITH_EDITOR
    // Popup throttled - agenda para depois do delay
    ShowEditorFeedbackWithThrottle(Context, Message, ELogSeverity::Warning, ThrottleDelay);
#endif
}

void FLoggingSystem::LogErrorWithThrottledPopup(const FLogContext &Context, const FString &Message, float ThrottleDelay)
{
    // Log imediato (UE_LOG) - sempre executa
    const FString FormattedMessage = FormatLogMessage(Context, Message);
    const FLogCategoryBase &LogCategory = GetLogCategory(Context.Module);

    UE_LOG(LogMyProject2DataTable, Error, TEXT("%s"), *FormattedMessage);

#if WITH_EDITOR
    // Popup throttled - agenda para depois do delay
    ShowEditorFeedbackWithThrottle(Context, Message, ELogSeverity::Error, ThrottleDelay);
#endif
}

#pragma endregion Throttled Log Functions

// ============================================================================
// Editor Feedback
// ============================================================================
#pragma region Editor Feedback

#if WITH_EDITOR

void FLoggingSystem::ShowEditorFeedback(const FLogContext &Context, const FString &Message, ELogSeverity Severity)
{
    // Cria notificação no editor
    FNotificationInfo NotificationInfo(FText::FromString(Message));

    // Para Warning e Error, não fecha automaticamente (usuário precisa ver)
    if (Severity == ELogSeverity::Warning || Severity == ELogSeverity::Error || Severity == ELogSeverity::Fatal)
    {
        NotificationInfo.bFireAndForget = false;
        NotificationInfo.bUseThrobber = false;
        NotificationInfo.bUseSuccessFailIcons = true;
    }
    else
    {
        // Info fecha automaticamente após 3 segundos
        NotificationInfo.bFireAndForget = true;
        NotificationInfo.ExpireDuration = 3.0f;
    }

    // Configurações visuais baseadas na severidade
    NotificationInfo.bUseLargeFont = (Severity == ELogSeverity::Error || Severity == ELogSeverity::Fatal);

    // Define imagem baseada na severidade
    if (Severity == ELogSeverity::Warning)
    {
        NotificationInfo.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Warning"));
    }
    else if (Severity == ELogSeverity::Error || Severity == ELogSeverity::Fatal)
    {
        NotificationInfo.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.Error"));
    }

    // Adiciona detalhes do contexto
    FString DetailText = FString::Printf(TEXT("Module: %s\nFunction: %s"), *Context.Module, *Context.Function);
    if (!Context.AssetName.IsEmpty())
    {
        DetailText += FString::Printf(TEXT("\nAsset: %s"), *Context.AssetName);
    }
    NotificationInfo.HyperlinkText = FText::FromString(DetailText);

    // Cria weak pointer compartilhado que será atualizado após AddNotification
    // Usa TSharedPtr para gerenciar o weak pointer de forma segura
    struct FNotificationWeakPtrWrapper
    {
        TWeakPtr<SNotificationItem> WeakPtr;
    };
    TSharedPtr<FNotificationWeakPtrWrapper> WeakPtrWrapper = MakeShareable(new FNotificationWeakPtrWrapper());

    // Adiciona botão de fechar usando weak pointer para evitar referência circular
    NotificationInfo.ButtonDetails.Add(
        FNotificationButtonInfo(FText::FromString(TEXT("Fechar")), FText::FromString(TEXT("Fecha esta notificação")),
                                FSimpleDelegate::CreateLambda(
                                    [WeakPtrWrapper]()
                                    {
                                        if (TSharedPtr<SNotificationItem> PinnedPtr = WeakPtrWrapper->WeakPtr.Pin())
                                        {
                                            PinnedPtr->ExpireAndFadeout();
                                        }
                                    })));

    // Mostra notificação e captura o ponteiro real
    TSharedPtr<SNotificationItem> NotificationPtr = FSlateNotificationManager::Get().AddNotification(NotificationInfo);

    // Atualiza o weak pointer com o ponteiro real
    WeakPtrWrapper->WeakPtr = NotificationPtr;

    // Para Warning/Error, força exibição imediata e não fecha automaticamente
    if (NotificationPtr.IsValid() &&
        (Severity == ELogSeverity::Warning || Severity == ELogSeverity::Error || Severity == ELogSeverity::Fatal))
    {
        NotificationPtr->SetCompletionState(SNotificationItem::CS_Pending);
        // Garante que notificação permanece visível até usuário fechar
        NotificationPtr->SetExpireDuration(0.0f);
    }

    // Debug: Log que notificação foi criada
    UE_LOG(LogMyProject2DataTable, Log, TEXT("[ShowEditorFeedback] Notificação criada: %s (Severity: %d)"), *Message,
           (int32)Severity);
}

void FLoggingSystem::ShowEditorFeedbackWithThrottle(const FLogContext &Context, const FString &Message,
                                                    ELogSeverity Severity, float ThrottleDelay)
{
    // Obtém World para acessar TimerManager
    UWorld *World = nullptr;
    if (GEngine && GEngine->GetWorldContexts().Num() > 0)
    {
        World = GEngine->GetWorldContexts()[0].World();
    }

    if (!World)
    {
        // Se não há World disponível, mostra feedback imediatamente (fallback)
        ShowEditorFeedback(Context, Message, Severity);
        return;
    }

    // Timer handle estático para throttle (compartilhado entre todas as chamadas)
    static FTimerHandle ThrottleTimerHandle;

    // Cancela timer anterior se existir (throttle: apenas o último popup será mostrado)
    if (ThrottleTimerHandle.IsValid())
    {
        World->GetTimerManager().ClearTimer(ThrottleTimerHandle);
    }

    // Cria cópias dos parâmetros para o lambda (captura por valor)
    FLogContext ContextCopy = Context;
    FString MessageCopy = Message;
    ELogSeverity SeverityCopy = Severity;

    // Agenda popup para depois do delay
    World->GetTimerManager().SetTimer(
        ThrottleTimerHandle,
        [ContextCopy, MessageCopy, SeverityCopy]()
        {
            // Mostra feedback após delay
            ShowEditorFeedback(ContextCopy, MessageCopy, SeverityCopy);
        },
        ThrottleDelay,
        false // não repetir
    );
}

#endif // WITH_EDITOR

#pragma endregion Editor Feedback
