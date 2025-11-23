// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

// Forward declarations
class UDataTable;

// Forward declaration para FClassLevelEntry (definida em CharacterSheetDataAsset.h)
struct FClassLevelEntry;

// Forward declarations para structs dos Data Tables
struct FRaceDataRow;
struct FClassDataRow;
struct FClassFeature;
struct FBackgroundDataRow;
struct FFeatDataRow;

/**
 * Funções helper para leitura, filtragem e validação de Data Tables de D&D 5e.
 * Funções puras e reutilizáveis seguindo princípios de Clean Code.
 *
 * Todas as funções são:
 * - Puras (sem efeitos colaterais)
 * - Parametrizadas (sem dependência de estado interno)
 * - Testáveis isoladamente
 * - < 50 linhas cada
 */
namespace CharacterSheetHelpers
{
    // ============================================================================
    // Race Data Table Helpers
    // ============================================================================

    /**
     * Retorna todos os nomes de raças disponíveis no Data Table.
     *
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Array com nomes de todas as raças, ou array vazio se Data Table inválido
     */
    TArray<FName> GetAllRaceNames(UDataTable *RaceDataTable);

    /**
     * Retorna todas as sub-raças disponíveis para uma raça específica.
     *
     * @param RaceName Nome da raça para buscar sub-raças
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Array com nomes das sub-raças, ou array vazio se não encontrado ou Data Table inválido
     */
    TArray<FName> GetAvailableSubraces(FName RaceName, UDataTable *RaceDataTable);

    // ============================================================================
    // Class Data Table Helpers
    // ============================================================================

    /**
     * Retorna todos os nomes de classes disponíveis no Data Table.
     *
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Array com nomes de todas as classes, ou array vazio se Data Table inválido
     */
    TArray<FName> GetAllClassNames(UDataTable *ClassDataTable);

    /**
     * Retorna todas as subclasses disponíveis para uma classe específica.
     *
     * @param ClassName Nome da classe para buscar subclasses
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Array com nomes das subclasses, ou array vazio se não encontrado ou Data Table inválido
     */
    TArray<FName> GetAvailableSubclasses(FName ClassName, UDataTable *ClassDataTable);

    /**
     * Verifica se o jogador pode selecionar uma subclasse para a classe especificada no nível dado.
     * Em D&D 5e, subclasses são geralmente escolhidas no nível 3.
     *
     * @param ClassName Nome da classe
     * @param ClassLevel Nível atual na classe
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return true se pode selecionar subclasse, false caso contrário
     */
    bool CanSelectSubclass(FName ClassName, int32 ClassLevel, UDataTable *ClassDataTable);

    /**
     * Retorna todas as features de uma classe que são desbloqueadas em um nível específico.
     *
     * @param ClassName Nome da classe
     * @param Level Nível para buscar features
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Array com features desbloqueadas no nível, ou array vazio se não encontrado ou Data Table inválido
     */
    TArray<FClassFeature> GetFeaturesAtLevel(FName ClassName, int32 Level, UDataTable *ClassDataTable);

    // ============================================================================
    // Background Data Table Helpers
    // ============================================================================

    /**
     * Retorna todos os nomes de backgrounds disponíveis no Data Table.
     *
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com nomes de todos os backgrounds, ou array vazio se Data Table inválido
     */
    TArray<FName> GetAllBackgroundNames(UDataTable *BackgroundDataTable);

    // ============================================================================
    // Feat Data Table Helpers
    // ============================================================================

    /**
     * Retorna todos os feats disponíveis para um personagem com base em nível total e ability scores.
     * Filtra feats que atendem aos pré-requisitos.
     *
     * @param TotalLevel Nível total do personagem
     * @param AbilityScores Map com ability scores do personagem (chave: FName do atributo, valor: score)
     * @param FeatDataTable Data Table de feats (pode ser nullptr)
     * @return Array com nomes dos feats disponíveis, ou array vazio se Data Table inválido
     */
    TArray<FName> GetAvailableFeats(int32 TotalLevel, const TMap<FName, int32> &AbilityScores,
                                    UDataTable *FeatDataTable);

    /**
     * Verifica se o personagem pode escolher um feat no nível especificado.
     * Em D&D 5e, feats podem ser escolhidos nos níveis 4, 8, 12, 16, 19 (ou ao invés de ASI).
     *
     * @param TotalLevel Nível total do personagem
     * @return true se pode escolher feat neste nível, false caso contrário
     */
    bool CanTakeFeatAtLevel(int32 TotalLevel);

    /**
     * Parseia e valida um pré-requisito de ability score.
     * Formato esperado: "AbilityName Score" (ex: "Strength 13", "Dexterity 15")
     *
     * @param Prerequisite String do pré-requisito
     * @param AbilityScores Map com ability scores do personagem
     * @return true se o pré-requisito é atendido, false caso contrário
     */
    bool ValidateAbilityScorePrerequisite(const FName &Prerequisite, const TMap<FName, int32> &AbilityScores);

    /**
     * Verifica se um personagem atende aos pré-requisitos de um feat.
     *
     * @param Row Row do feat no Data Table
     * @param AbilityScores Map com ability scores do personagem
     * @return true se todos os pré-requisitos são atendidos, false caso contrário
     */
    bool MeetsFeatPrerequisites(const FFeatDataRow *Row, const TMap<FName, int32> &AbilityScores);

    // ============================================================================
    // Ability Score Helpers
    // ============================================================================

    /**
     * Retorna array estático com os 6 nomes de ability scores padrão D&D 5e.
     * Ordem: Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
     *
     * @return Array com os 6 nomes de ability scores
     */
    TArray<FName> GetAbilityScoreNames();

    // ============================================================================
    // Point Buy System Helpers
    // ============================================================================

    /**
     * Calcula o custo em pontos do Point Buy para um ability score específico.
     * Segue tabela oficial D&D 5e:
     * - Score 8: 0 pontos
     * - Score 9-13: (score - 8) pontos
     * - Score 14: 7 pontos
     * - Score 15: 9 pontos
     *
     * @param Score Ability score (deve estar entre 8 e 15)
     * @return Custo em pontos, ou 0 se score inválido
     */
    int32 CalculatePointBuyCost(int32 Score);

    /**
     * Calcula o custo total do Point Buy para todos os ability scores.
     *
     * @param AbilityScores Map com ability scores (chave: FName do atributo, valor: score)
     * @return Custo total em pontos
     */
    int32 CalculateTotalPointBuyCost(const TMap<FName, int32> &AbilityScores);

    // ============================================================================
    // Level Calculation Helpers
    // ============================================================================

    /**
     * Calcula o nível total do personagem somando todos os níveis de classes.
     *
     * @param ClassLevels Array com entradas de nível por classe
     * @return Nível total do personagem
     */
    int32 CalculateTotalLevel(const TArray<FClassLevelEntry> &ClassLevels);
} // namespace CharacterSheetHelpers
