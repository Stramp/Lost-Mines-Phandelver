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
    static void LogPropertyChange(FName PropertyName);

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
     * Reseta classe com tag de requerimento para NAME_None.
     * Helper puro e testável para reset de classe com tag.
     *
     * @param Entry Entrada de multiclasse a verificar
     * @param Index Índice da entrada no array
     * @return true se resetou a classe, false caso contrário
     */
    static bool ResetClassWithRequirementTag(struct FMulticlassEntry &Entry, int32 Index);

    /**
     * Aplica correção ResetToNone para propriedade específica.
     * Helper puro e testável para aplicação de correções.
     *
     * @param Asset Asset do personagem
     * @param Correction Correção a ser aplicada
     */
    static void ApplyResetToNone(UCharacterSheetDataAsset *Asset, const struct FValidationCorrection &Correction);

    /**
     * Aplica correção ClearArray para propriedade específica.
     * Helper puro e testável para aplicação de correções.
     *
     * @param Asset Asset do personagem
     * @param Correction Correção a ser aplicada
     */
    static void ApplyClearArray(UCharacterSheetDataAsset *Asset, const struct FValidationCorrection &Correction);

    /**
     * Aplica correção AdjustValue para propriedade específica.
     * Helper puro e testável para aplicação de correções.
     *
     * @param Asset Asset do personagem
     * @param Correction Correção a ser aplicada
     */
    static void ApplyAdjustValue(UCharacterSheetDataAsset *Asset, const struct FValidationCorrection &Correction);
};
