// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Utils/DataTableHelpers.h"
#include "CharacterSheetHelpers.generated.h"

// Forward declarations
class UDataTable;

/**
 * Struct para armazenar entrada de nível de classe (multi-classing).
 * Usado pelos helpers para cálculos internos.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassLevelEntry
{
    GENERATED_BODY()

    /** Nome da classe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FName ClassName;

    /** Nível nesta classe (1-20) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    int32 Level = 1;

    /** Nome da subclasse escolhida (se aplicável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FName SubclassName;

    /** Escolhas feitas pelo jogador nesta classe (ex: Fighting Style, Maneuvers) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FName> Choices;

    FClassLevelEntry() : ClassName(NAME_None), Level(1), SubclassName(NAME_None) {}

    FClassLevelEntry(const FName &InClassName, int32 InLevel)
        : ClassName(InClassName), Level(InLevel), SubclassName(NAME_None)
    {
    }
};

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

    // Removido: GetAllClassNames - não utilizado (dead code)

    /**
     * Verifica se o jogador pode selecionar uma subclasse para a classe especificada no nível dado.
     * Em D&D 5e, subclasses são geralmente escolhidas no nível 3.
     * Nota: Atualmente apenas verifica o nível mínimo. Verificação de subclasses disponíveis
     * será implementada quando necessário usando a estrutura flat de Progression com FeatureHandles.
     *
     * @param ClassName Nome da classe
     * @param ClassLevel Nível atual na classe
     * @param ClassDataTable Data Table de classes (pode ser nullptr, não usado atualmente)
     * @return true se pode selecionar subclasse (nível >= 3), false caso contrário
     */
    bool CanSelectSubclass(FName ClassName, int32 ClassLevel, UDataTable *ClassDataTable);

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
     * Retorna array com os nomes de ability scores e seus IDs.
     * Se AbilityScoreDataTable for fornecido, busca do Data Table (Data-Driven).
     * Caso contrário, retorna array hardcoded com os 6 ability scores padrão D&D 5e (fallback).
     * Sempre retorna Name + ID juntos (ID é a referência exata na Data Table).
     *
     * Ordem padrão: Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
     *
     * @param AbilityScoreDataTable Data Table de ability scores (pode ser nullptr para fallback hardcoded)
     * @return Array com Name + ID de ability scores (do Data Table ou hardcoded)
     */
    TArray<FNameWithID> GetAbilityScoreNames(UDataTable *AbilityScoreDataTable = nullptr);

    // ============================================================================
    // Skill Helpers
    // ============================================================================

    /**
     * Retorna array com os nomes de skills disponíveis e seus IDs.
     * Se ProficiencyDataTable for fornecido, busca skills do Data Table (Data-Driven).
     * Caso contrário, retorna array hardcoded com os 18 skills padrão D&D 5e (fallback).
     * Sempre retorna Name + ID juntos (ID é a referência exata na Data Table).
     *
     * Ordem alfabética: Acrobatics, Animal Handling, Arcana, Athletics, Deception,
     * History, Insight, Intimidation, Investigation, Medicine, Nature, Perception,
     * Performance, Persuasion, Religion, Sleight of Hand, Stealth, Survival
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr para fallback hardcoded)
     * @return Array com Name + ID de skills (do Data Table ou hardcoded)
     */
    TArray<FNameWithID> GetSkillNames(UDataTable *ProficiencyDataTable = nullptr);

    // ============================================================================
    // Language Helpers
    // ============================================================================

    /**
     * Retorna array com os nomes de idiomas disponíveis e seus IDs.
     * Se ProficiencyDataTable for fornecido, busca languages do Data Table (Data-Driven).
     * Caso contrário, retorna array hardcoded com os idiomas padrão D&D 5e (fallback).
     * Sempre retorna Name + ID juntos (ID é a referência exata na Data Table).
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr para fallback hardcoded)
     * @return Array com Name + ID de idiomas (do Data Table ou hardcoded)
     */
    TArray<FNameWithID> GetAvailableLanguageNames(UDataTable *ProficiencyDataTable = nullptr);

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
     * @param SelectedLanguages Array com idiomas já selecionados pelo jogador
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr para fallback hardcoded)
     * @return Array com idiomas disponíveis para escolha (excluindo já conhecidos)
     */
    TArray<FName> GetAvailableLanguagesForChoice(FName RaceName, FName SubraceName, FName BackgroundName,
                                                 const TArray<FName> &SelectedLanguages, UDataTable *RaceDataTable,
                                                 UDataTable *BackgroundDataTable,
                                                 UDataTable *ProficiencyDataTable = nullptr);

    // ============================================================================
    // Point Buy System Helpers
    // ============================================================================

    /**
     * Cria TMap de PointBuy a partir de valores individuais.
     * Helper puro para eliminar duplicação de código.
     *
     * @param PointBuyStrength Pontos alocados para Strength (0-7)
     * @param PointBuyDexterity Pontos alocados para Dexterity (0-7)
     * @param PointBuyConstitution Pontos alocados para Constitution (0-7)
     * @param PointBuyIntelligence Pontos alocados para Intelligence (0-7)
     * @param PointBuyWisdom Pontos alocados para Wisdom (0-7)
     * @param PointBuyCharisma Pontos alocados para Charisma (0-7)
     * @return Map com valores de Point Buy (chave: FName do atributo, valor: pontos de Point Buy)
     */
    TMap<FName, int32> CreatePointBuyMapFromData(int32 PointBuyStrength, int32 PointBuyDexterity,
                                                 int32 PointBuyConstitution, int32 PointBuyIntelligence,
                                                 int32 PointBuyWisdom, int32 PointBuyCharisma);

    /**
     * Cria TMap de BaseScores (BASE_ABILITY_SCORE + PointBuy) a partir de PointBuyMap.
     * Helper puro para eliminar duplicação de código.
     *
     * @param PointBuyMap Map com valores de Point Buy (chave: FName do atributo, valor: pontos de Point Buy)
     * @return Map com BaseScores calculados (BASE_ABILITY_SCORE + PointBuy para cada atributo)
     */
    TMap<FName, int32> CreateBaseScoresFromPointBuy(const TMap<FName, int32> &PointBuyMap);

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
