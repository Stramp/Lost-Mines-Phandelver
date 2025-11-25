// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class UDataTable;
struct FClassLevelEntry;

/**
 * Validator para sistema de multiclassing D&D 5e.
 * Responsável por validar pré-requisitos e escolhas de multiclassing.
 */
class MYPROJECT2_API FMulticlassingValidator
{
public:
    /**
     * Valida pré-requisitos de multiclassing D&D 5e.
     * Regra: precisa ter 13+ no atributo principal de ambas as classes.
     *
     * @param ClassLevels Array de níveis de classe do personagem
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param FinalStrength Final Strength score
     * @param FinalDexterity Final Dexterity score
     * @param FinalConstitution Final Constitution score
     * @param FinalIntelligence Final Intelligence score
     * @param FinalWisdom Final Wisdom score
     * @param FinalCharisma Final Charisma score
     * @param OutErrorMessage [OUT] Mensagem de erro se validação falhar
     * @return true se pré-requisitos são atendidos, false caso contrário
     */
    static bool ValidateMulticlassingPrerequisites(const TArray<FClassLevelEntry> &ClassLevels,
                                                   UDataTable *ClassDataTable, int32 FinalStrength,
                                                   int32 FinalDexterity, int32 FinalConstitution,
                                                   int32 FinalIntelligence, int32 FinalWisdom, int32 FinalCharisma,
                                                   FString &OutErrorMessage);

    /**
     * Valida escolhas do jogador (quantidade, dependências).
     *
     * @param ClassEntry Entrada de nível de classe com escolhas
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param OutErrorMessage [OUT] Mensagem de erro se validação falhar
     * @return true se escolhas são válidas, false caso contrário
     */
    static bool ValidateChoices(const FClassLevelEntry &ClassEntry, UDataTable *ClassDataTable,
                                FString &OutErrorMessage);
};
