// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
struct FCharacterSheetData;
class UDataTable;
struct FMulticlassProficienciesEntry;
struct FMulticlassProgressEntry;

/**
 * Motor de Multiclasse para criação de personagem.
 * Responsável por validar e aplicar regras de multiclasse D&D 5e.
 *
 * Motor independente: não conhece outros motores, apenas aplica regras de multiclasse.
 * Genérico: recebe FCharacterSheetData (dados puros), não objetos concretos.
 */
class MYPROJECT2_API FMulticlassMotor
{
public:
    /**
     * Retorna todas as classes disponíveis com validação de requisitos de atributo.
     * Filtra classes que o personagem pode pegar baseado nos atributos finais.
     *
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param FinalStrength Strength final do personagem
     * @param FinalDexterity Dexterity final do personagem
     * @param FinalConstitution Constitution final do personagem
     * @param FinalIntelligence Intelligence final do personagem
     * @param FinalWisdom Wisdom final do personagem
     * @param FinalCharisma Charisma final do personagem
     * @param AbilityScoreDataTable Data Table de Ability Scores (opcional, necessário para nova estrutura normalizada)
     * @return Array com nomes de classes disponíveis (que atendem requisitos de atributo)
     */
    static TArray<FName> GetAvailableClasses(const UDataTable *ClassDataTable, int32 FinalStrength,
                                             int32 FinalDexterity, int32 FinalConstitution, int32 FinalIntelligence,
                                             int32 FinalWisdom, int32 FinalCharisma,
                                             const UDataTable *AbilityScoreDataTable = nullptr);

    /**
     * Carrega proficiências de uma classe para multiclasse retornando nomes legíveis.
     * Proficiências são ganhas apenas no nível 1 da classe.
     * Resolve IDs de proficiências (ex: "PW_Simple_Weapons") para nomes legíveis (ex: "Simple Weapons").
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe (deve ser 1 para carregar proficiências)
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param ProficiencyDataTable Data Table de proficiências para resolver IDs (pode ser nullptr)
     * @param OutProficiencies [OUT] Array de proficiências carregadas com nomes legíveis
     * @return true se proficiências foram carregadas com sucesso, false caso contrário
     */
    static bool LoadClassProficiencies(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable,
                                       const UDataTable *ProficiencyDataTable,
                                       TArray<FMulticlassProficienciesEntry> &OutProficiencies);

    /**
     * Carrega progressão de features de uma classe para multiclasse.
     * Popula array Progression com features detalhadas do ClassFeaturesDataTable.
     * Para cada nível de 1 até LevelInClass, busca features do ClassDataTable e converte para FMulticlassClassFeature.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe (1-20)
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param FeatureDataTable Data Table de features (pode ser nullptr)
     * @param OutProgression [OUT] Array de progressão populada com features detalhadas
     * @return true se progressão foi carregada com sucesso, false caso contrário
     */
    static bool LoadClassProgression(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable,
                                     const UDataTable *FeatureDataTable,
                                     TArray<FMulticlassProgressEntry> &OutProgression);
};
