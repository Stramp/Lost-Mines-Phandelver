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
struct FClassFeatureChoice;
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

    // TODO: Reimplementar usando nova estrutura FClassData.FProgress
    // Estrutura antiga (FClassFeature, FClassFeatureChoice) não existe mais
    // Funções comentadas:
    // - GetFeaturesAtLevel
    // - GetAvailableChoicesForClassLevel

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
     * Retorna todos os feats disponíveis para Variant Human (nível 1).
     * Variant Human é uma exceção especial que permite escolher feat no nível 1,
     * bypassando a verificação normal de nível (4, 8, 12, 16, 19).
     * Ainda valida pré-requisitos de ability scores.
     *
     * @param AbilityScores Map com ability scores do personagem (chave: FName do atributo, valor: score)
     * @param FeatDataTable Data Table de feats (pode ser nullptr)
     * @return Array com nomes dos feats disponíveis, ou array vazio se Data Table inválido
     */
    TArray<FName> GetAvailableFeatsForVariantHuman(const TMap<FName, int32> &AbilityScores, UDataTable *FeatDataTable);

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
    // Skill Helpers
    // ============================================================================

    /**
     * Retorna array estático com os 18 nomes de skills padrão D&D 5e.
     * Ordem alfabética: Acrobatics, Animal Handling, Arcana, Athletics, Deception,
     * History, Insight, Intimidation, Investigation, Medicine, Nature, Perception,
     * Performance, Persuasion, Religion, Sleight of Hand, Stealth, Survival
     *
     * NOTA: Futuramente pode ser migrado para SkillDataTable seguindo o princípio
     * Data-Driven completo. Por enquanto, hardcoded porque são constantes do sistema
     * D&D 5e (assim como Ability Scores são hardcoded).
     *
     * @return Array com os 18 nomes de skills
     */
    TArray<FName> GetSkillNames();

    // ============================================================================
    // Language Helpers
    // ============================================================================

    /**
     * Retorna array estático com os nomes de idiomas padrão D&D 5e.
     * NOTA: Futuramente pode ser migrado para LanguageDataTable para permitir customização.
     * Por enquanto, hardcoded porque são constantes do sistema D&D 5e.
     * @return Array com nomes de idiomas disponíveis
     */
    TArray<FName> GetAvailableLanguageNames();

    /**
     * Detecta se raça/sub-raça permite escolha de idiomas via TraitData.
     *
     * @param RaceName Nome da raça (pode ser NAME_None)
     * @param SubraceName Nome da sub-raça (pode ser NAME_None)
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @param OutCount [OUT] Quantidade de idiomas que podem ser escolhidos (1, 2, etc.)
     * @return true se há escolha de idiomas, false caso contrário
     */
    bool HasLanguageChoiceFromRace(FName RaceName, FName SubraceName, UDataTable *RaceDataTable, int32 &OutCount);

    /**
     * Detecta se background permite escolha de idiomas.
     *
     * @param BackgroundName Nome do background (pode ser NAME_None)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @param OutCount [OUT] Quantidade de idiomas que podem ser escolhidos (1, 2, etc.)
     * @return true se há escolha de idiomas, false caso contrário
     */
    bool HasLanguageChoiceFromBackground(FName BackgroundName, UDataTable *BackgroundDataTable, int32 &OutCount);

    /**
     * Calcula idiomas automáticos que o personagem já fala (raça + sub-raça + background automáticos).
     * NÃO inclui idiomas escolhidos pelo jogador (apenas automáticos).
     * Usado para filtrar dropdown de escolhas de idiomas.
     *
     * @param RaceName Nome da raça selecionada (pode ser NAME_None)
     * @param SubraceName Nome da sub-raça selecionada (pode ser NAME_None)
     * @param BackgroundName Nome do background selecionado (pode ser NAME_None)
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com idiomas automáticos já conhecidos
     */
    TArray<FName> GetAutomaticLanguages(FName RaceName, FName SubraceName, FName BackgroundName,
                                        UDataTable *RaceDataTable, UDataTable *BackgroundDataTable);

    /**
     * Retorna idiomas disponíveis para escolha, EXCLUINDO idiomas já conhecidos automaticamente.
     * Filtra o array completo de idiomas removendo os que o personagem já fala (raça + sub-raça + background
     * automáticos). Usado no dropdown de escolhas de idiomas para evitar que o jogador escolha idiomas que já possui.
     *
     * @param RaceName Nome da raça selecionada (pode ser NAME_None)
     * @param SubraceName Nome da sub-raça selecionada (pode ser NAME_None)
     * @param BackgroundName Nome do background selecionado (pode ser NAME_None)
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com idiomas disponíveis para escolha (excluindo já conhecidos)
     */
    TArray<FName> GetAvailableLanguagesForChoice(FName RaceName, FName SubraceName, FName BackgroundName,
                                                 const TArray<FName> &SelectedLanguages, UDataTable *RaceDataTable,
                                                 UDataTable *BackgroundDataTable);

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

    // ============================================================================
    // Multiclassing Helpers
    // ============================================================================

    /**
     * Retorna opções disponíveis para uma escolha específica.
     * Usado pela UI para popular dropdowns dinâmicos.
     *
     * @param ChoiceID ID único da escolha (ex: "Fighter_FightingStyle_1")
     * @param ClassName Nome da classe
     * @param ClassLevel Nível da classe
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Array com opções disponíveis, ou array vazio se não encontrado
     */
    TArray<FName> GetChoiceOptions(FName ChoiceID, FName ClassName, int32 ClassLevel, UDataTable *ClassDataTable);

    /**
     * Verifica se uma escolha é válida baseado em dependências.
     *
     * @param ChoiceID ID único da escolha
     * @param SelectedValues Valores escolhidos pelo jogador
     * @param ClassLevels Array com níveis de classe do personagem
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return true se a escolha é válida, false caso contrário
     */
    bool IsChoiceValid(FName ChoiceID, const TArray<FName> &SelectedValues, const TArray<FClassLevelEntry> &ClassLevels,
                       UDataTable *ClassDataTable);
} // namespace CharacterSheetHelpers
