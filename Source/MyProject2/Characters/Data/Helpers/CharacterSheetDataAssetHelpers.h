// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "UObject/NameTypes.h"

// Forward declarations
class UCharacterSheetDataAsset;
struct FMulticlassEntry;
struct FValidationCorrection;

/**
 * Helpers for CharacterSheetDataAsset.
 * Utility functions for resetting and managing character sheet data.
 */
class MYPROJECT2_API FCharacterSheetDataAssetHelpers
{
public:
    /**
     * Resets Variant Human choices when race changes.
     * Clears CustomAbilityScoreChoices, SelectedFeat, and SelectedSkill.
     */
    static void ResetVariantHumanChoices(UCharacterSheetDataAsset *Asset);

    /**
     * Creates a map of ability scores from final attribute values.
     * Used for feat validation and other ability score-based operations.
     *
     * @param FinalStrength Final Strength score
     * @param FinalDexterity Final Dexterity score
     * @param FinalConstitution Final Constitution score
     * @param FinalIntelligence Final Intelligence score
     * @param FinalWisdom Final Wisdom score
     * @param FinalCharisma Final Charisma score
     * @return Map of ability score names to their final values
     */
    static TMap<FName, int32> CreateAbilityScoresMap(int32 FinalStrength, int32 FinalDexterity, int32 FinalConstitution,
                                                     int32 FinalIntelligence, int32 FinalWisdom, int32 FinalCharisma);

    /**
     * Creates array of attributes in order [STR, DEX, CON, INT, WIS, CHA].
     * Helper puro e testável para conversão de atributos individuais para array.
     *
     * @param FinalStrength Final Strength score
     * @param FinalDexterity Final Dexterity score
     * @param FinalConstitution Final Constitution score
     * @param FinalIntelligence Final Intelligence score
     * @param FinalWisdom Final Wisdom score
     * @param FinalCharisma Final Charisma score
     * @return Array of attributes in standard order [STR, DEX, CON, INT, WIS, CHA]
     */
    static TArray<int32> CreateAttributesArray(int32 FinalStrength, int32 FinalDexterity, int32 FinalConstitution,
                                               int32 FinalIntelligence, int32 FinalWisdom, int32 FinalCharisma);

    /**
     * Updates Point Buy allocation values from adjusted allocation map.
     * Uses GetAbilityScoreNames() to ensure data-driven approach.
     *
     * @param Asset Character Sheet Data Asset to update
     * @param AdjustedAllocation Map of ability score names to adjusted values
     */
    static void UpdatePointBuyFromAdjustedAllocation(UCharacterSheetDataAsset *Asset,
                                                     const TMap<FName, int32> &AdjustedAllocation);

    /**
     * Verifica se a propriedade é calculada (não deve disparar handlers).
     * Propriedades calculadas são atualizadas automaticamente e não devem
     * disparar PostEditChangeProperty para evitar recursão.
     *
     * @param PropertyName Nome da propriedade a verificar
     * @return true se a propriedade é calculada, false caso contrário
     */
    static bool IsCalculatedProperty(FName PropertyName);

    /**
     * Loga que PostEditChangeProperty chamou o handler para uma propriedade específica.
     * Helper puro e testável para logging de mudanças de propriedade.
     *
     * @param PropertyName Nome da propriedade que mudou
     */

    /**
     * Valida se Asset é válido e retorna false se não for.
     * Helper puro e testável para validação de Asset.
     *
     * @param Asset Asset a validar
     * @return true se Asset é válido, false caso contrário
     */
    static bool ValidateAsset(UCharacterSheetDataAsset *Asset);

    /**
     * Reseta sub-raça quando raça principal muda.
     * Helper puro e testável para reset de sub-raça.
     *
     * @param Asset Asset do personagem
     * @param PropertyName Nome da propriedade que mudou
     */
    static void ResetSubraceIfRaceChanged(UCharacterSheetDataAsset *Asset, FName PropertyName);

    /**
     * Loga informações sobre status dos Data Tables.
     * Helper puro e testável para logging de status de Data Tables.
     *
     * @param Asset Asset do personagem
     */
    static void LogDataTableStatus(UCharacterSheetDataAsset *Asset);

    /**
     * Obtém nome da classe formatado para log (ou "Unknown" se vazio).
     * Helper puro e testável para formatação de nomes de classe.
     *
     * @param ClassName Nome da classe original
     * @return Nome formatado para exibição
     */
    static FString GetFormattedClassName(const FString &ClassName);

    /**
     * Extrai tag de requerimento do nome da classe.
     * Exemplo: "[INT +3] Wizard" -> "[INT +3]"
     *
     * @param ClassName Nome completo da classe (pode conter tag)
     * @param OutTag [OUT] Tag extraída (ex: "[INT +3]")
     * @return true se encontrou tag, false caso contrário
     */
    static bool ExtractRequirementTag(const FString &ClassName, FString &OutTag);

    /**
     * Parseia tag de requerimento para obter atributo e valor faltante.
     * Exemplo: "[INT +3]" -> "INT", 3
     *
     * @param Tag Tag de requerimento (ex: "[INT +3]")
     * @param OutAttributeAbbr [OUT] Abreviação do atributo (ex: "INT")
     * @param OutMissingValue [OUT] Valor faltante (ex: 3)
     * @return true se parseou com sucesso, false caso contrário
     */
    static bool ParseRequirementTag(const FString &Tag, FString &OutAttributeAbbr, int32 &OutMissingValue);

    /**
     * Obtém nome completo do atributo a partir da abreviação.
     * Exemplo: "INT" -> "Intelligence"
     *
     * @param AttributeAbbr Abreviação do atributo (ex: "INT")
     * @return Nome completo do atributo (ex: "Intelligence") ou vazio se não encontrado
     */
    static FString GetFullAttributeName(const FString &AttributeAbbr);

    /**
     * Verifica se o nome da classe contém tag de requerimento.
     * Exemplo: "[INT +3] Wizard" -> true, "Wizard" -> false
     *
     * @param ClassName Nome da classe (FName)
     * @return true se contém tag de requerimento, false caso contrário
     */
    static bool HasRequirementTag(FName ClassName);

    /**
     * Verifica se a classe é válida sem tag de requerimento.
     * Classe válida = não é NAME_None e não tem tag de requerimento.
     *
     * @param ClassName Nome da classe (FName)
     * @return true se é classe válida sem tag, false caso contrário
     */
    static bool IsValidClassWithoutTag(FName ClassName);

    /**
     * Ajusta array de Progression manualmente como fallback quando LoadClassProgression falha.
     * Helper puro e testável para ajuste de Progression.
     *
     * @param Progression Array de Progression a ajustar
     * @param LevelInClass Nível na classe (1-20)
     */
    static void AdjustProgressionFallback(TArray<struct FMulticlassProgressEntry> *Progression, int32 LevelInClass);

    /**
     * Detecta se a propriedade mudada é uma propriedade aninhada dentro do array Multiclass.
     * Helper puro e testável para detecção de propriedades aninhadas.
     *
     * @param PropertyChangedEvent Evento de mudança de propriedade
     * @param HandlerPropertyName [OUT] Nome da propriedade do handler (pode ser diferente de PropertyName)
     * @return true se é propriedade aninhada que precisa de handler específico, false caso contrário
     */
    static bool DetectNestedMulticlassProperty(const struct FPropertyChangedEvent &PropertyChangedEvent,
                                               FName &HandlerPropertyName);

    /**
     * Detecta se correções alteraram LevelInClass.
     * Função pura e testável, sem side effects.
     * Usado para determinar se dados devem ser recarregados após correções.
     *
     * @param ValidationResult Resultado da validação a analisar
     * @return true se LevelInClass foi ajustado, false caso contrário
     */
    static bool DetectLevelInClassCorrections(const struct FValidationResult &ValidationResult);

    // ============================================================================
    // Data Table Type Validation Helpers
    // ============================================================================

    /**
     * Valida tipo de Data Table específica e exibe popup de erro se tipo incorreto.
     * Helper reutilizável para validação de tipo de Data Tables.
     *
     * @param Asset Data Asset
     * @param DataTable Data Table a validar (pode ser nullptr)
     * @param PropertyName Nome da propriedade (para mensagem de erro)
     * @param ExpectedTypeName Nome do tipo esperado (ex: "FRaceDataRow")
     * @param ValidationFunction Função de validação (ex: DataTableHelpers::IsRaceDataTable)
     * @return true se tipo é válido ou DataTable é nullptr, false se tipo incorreto
     */
    static bool ValidateDataTableType(UCharacterSheetDataAsset *Asset, class UDataTable *DataTable,
                                      const FName &PropertyName, const FString &ExpectedTypeName,
                                      bool (*ValidationFunction)(class UDataTable *));

    // ============================================================================
    // Multiple Choice Feature Helpers
    // ============================================================================

    /**
     * Itera por todas as features de múltiplas escolhas (Tipo 3) em todas as entradas de multiclasse.
     * Helper reutilizável para evitar duplicação de código (DRY).
     * Executa callback para cada feature que atende aos critérios.
     *
     * @param Asset Data Asset
     * @param Callback Função a ser executada para cada feature (recebe Feature e ValidChoices)
     */
    static void ForEachMultipleChoiceFeature(
        UCharacterSheetDataAsset *Asset,
        TFunctionRef<void(struct FMulticlassClassFeature &Feature, const TArray<FName> &ValidChoices)> Callback);

    /**
     * Obtém limite máximo de escolhas para uma feature (MaxChoices).
     * Busca em FeatureData["MaxChoices"] ou retorna -1 se não definido (sem limite).
     * Helper puro e testável para obtenção de limites.
     *
     * @param Feature Feature a verificar
     * @return Limite máximo de escolhas, ou -1 se não há limite definido
     */
    static int32 GetMaxChoicesLimit(const struct FMulticlassClassFeature &Feature);

    /**
     * Valida se uma escolha pode ser adicionada (não excede limite, não é duplicata).
     * Helper puro e testável para validação de escolhas.
     *
     * @param Choice Escolha a validar
     * @param ValidChoices Lista de escolhas válidas para a feature
     * @param SelectedChoices Lista de escolhas já selecionadas
     * @param MaxChoices Limite máximo de escolhas (-1 = sem limite)
     * @return true se pode adicionar, false caso contrário
     */
    static bool CanAddChoice(FName Choice, const TArray<FName> &ValidChoices,
                             const TArray<FName> &SelectedChoices, int32 MaxChoices);

    /**
     * Remove escolhas inválidas e duplicatas de SelectedChoices.
     * Helper puro e testável para limpeza de array de escolhas.
     * Retorna true se houve mudanças.
     *
     * @param SelectedChoices [IN/OUT] Array de escolhas (será modificado)
     * @param ValidChoices Lista de escolhas válidas para a feature
     * @return true se houve mudanças (escolhas removidas), false caso contrário
     */
    static bool CleanInvalidAndDuplicateChoices(TArray<FName> &SelectedChoices, const TArray<FName> &ValidChoices);
};
