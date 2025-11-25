// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MulticlassingResult.h"

// Forward declarations
class UDataTable;
struct FClassDataRow;
struct FClassLevelEntry;
struct FClassFeature;

/**
 * Motor de multiclassing para criação de personagem D&D 5e.
 * Responsável por calcular TotalLevel, ProficiencyBonus, coletar features disponíveis
 * e fornecer interface desacoplada para SpellSystem futuro.
 *
 * Motor independente: não conhece SpellSystem, apenas fornece dados brutos.
 * Genérico: recebe dados puros, não objetos concretos.
 *
 * Responsabilidades:
 * - Calcular nível total (soma de todos os níveis de classe)
 * - Calcular bônus de proficiência baseado no TotalLevel
 * - Coletar features disponíveis considerando níveis e escolhas
 * - Coletar informações de spellcasting (dados brutos para SpellSystem)
 * - Responder queries sobre classes e níveis
 */
class MYPROJECT2_API FMulticlassingMotor
{
public:
    /**
     * Calcula resultado completo de multiclassing.
     *
     * @param ClassLevels Array de níveis de classe do personagem
     * @param ClassDataTable Data Table de classes
     * @return Resultado com TotalLevel, ProficiencyBonus, Features, SpellcastingInfo
     */
    static FMulticlassingResult CalculateMulticlassing(const TArray<FClassLevelEntry> &ClassLevels,
                                                       UDataTable *ClassDataTable);

    /**
     * Query: Retorna informações sobre classes e níveis.
     * Usado por SpellSystem para saber quais classes o personagem tem.
     *
     * @param ClassLevels Array de níveis de classe
     * @return Map de ClassName -> ClassLevel
     */
    static TMap<FName, int32> GetClassLevelsInfo(const TArray<FClassLevelEntry> &ClassLevels);

    /**
     * Retorna todas as classes disponíveis com informação de disponibilidade.
     * Verifica requisitos de atributo para multiclassing D&D 5e.
     * Retorna TODAS as classes, mas marca como não disponível (bIsAvailable = false)
     * as que não atendem aos requisitos.
     *
     * @param ClassDataTable Data Table de classes
     * @param FinalStrength Final Strength score
     * @param FinalDexterity Final Dexterity score
     * @param FinalConstitution Final Constitution score
     * @param FinalIntelligence Final Intelligence score
     * @param FinalWisdom Final Wisdom score
     * @param FinalCharisma Final Charisma score
     * @return Array de FClassOption com todas as classes e sua disponibilidade
     */
    static TArray<FClassOption> GetAvailableClasses(UDataTable *ClassDataTable, int32 FinalStrength,
                                                    int32 FinalDexterity, int32 FinalConstitution,
                                                    int32 FinalIntelligence, int32 FinalWisdom, int32 FinalCharisma);

private:
    // NOTA: CalculateTotalLevel e CalculateProficiencyBonus são reutilizados de helpers existentes
    // - CharacterSheetHelpers::CalculateTotalLevel
    // - CalculationHelpers::CalculateProficiencyBonus

    /**
     * Coleta todas as features disponíveis considerando níveis e escolhas.
     */
    static TArray<FClassFeature> CollectAvailableFeatures(const TArray<FClassLevelEntry> &ClassLevels,
                                                          UDataTable *ClassDataTable);

    /**
     * Resolve escolhas do jogador em features.
     * Filtra features baseado em escolhas feitas (ex: subclass, fighting style).
     */
    static void ResolveFeatureChoices(TArray<FClassFeature> &Features, const TArray<FClassLevelEntry> &ClassLevels,
                                      UDataTable *ClassDataTable);

    /**
     * Coleta informações de spellcasting de todas as classes.
     * Retorna dados brutos para SpellSystem processar.
     */
    static TArray<FClassSpellcastingInfo> CollectSpellcastingInfo(const TArray<FClassLevelEntry> &ClassLevels,
                                                                  UDataTable *ClassDataTable);

    /**
     * Retorna features disponíveis para um nível específico de uma classe.
     */
    static TArray<FClassFeature> GetFeaturesForClassLevel(FName ClassName, int32 ClassLevel,
                                                          UDataTable *ClassDataTable);
};
