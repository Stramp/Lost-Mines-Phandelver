// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// Forward declarations
class UDataTable;
struct FClassDataRow;
struct FProgressEntry;
struct FMulticlassClassFeature;
struct FDataTableRowHandle;

/**
 * Helpers de carregamento de dados para multiclasse.
 * Funções auxiliares para buscar e carregar dados de classes, features e progressão.
 */
class MYPROJECT2_API FMulticlassDataLoadingHelpers
{
public:
    /**
     * Retorna classes disponíveis com tags de requisitos faltantes.
     * Classes que não atendem requisitos terão tag como "[INT +13]" indicando o requisito faltante.
     * Tenta usar nova estrutura normalizada primeiro, com fallback para formato antigo.
     *
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param Attributes Array de atributos na ordem: [STR, DEX, CON, INT, WIS, CHA]
     * @param AbilityScoreDataTable Data Table de Ability Scores (opcional, necessário para nova estrutura)
     * @return Array de FName com nomes das classes (com tags se não disponíveis)
     */
    static TArray<FName> GetAvailableClassWithTagRequirements(const UDataTable *ClassDataTable,
                                                              const TArray<int32> &Attributes,
                                                              const UDataTable *AbilityScoreDataTable = nullptr);

    /**
     * Busca e valida classe na tabela, logando erro se não encontrada.
     * Helper puro e testável para evitar duplicação de código de busca e log.
     *
     * @param ClassName Nome da classe
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param FunctionName Nome da função chamadora para contexto de log
     * @return Row da classe encontrada, ou nullptr se não encontrada
     */
    static const FClassDataRow *FindClassRowWithErrorLogging(FName ClassName, const UDataTable *ClassDataTable,
                                                             const FString &FunctionName);

    /**
     * Carrega informações básicas da classe (MulticlassRequirements) do ClassDataTable.
     * Helper puro e testável para carregar dados automáticos da classe.
     *
     * @param ClassName Nome da classe
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param OutMulticlassRequirements [OUT] Requisitos de multiclasse carregados
     * @return true se informações foram carregadas com sucesso, false caso contrário
     */
    static bool LoadClassBasicInfo(FName ClassName, const UDataTable *ClassDataTable,
                                   TArray<FString> &OutMulticlassRequirements);

    /**
     * Extrai features do nível específico da progressão.
     * Função pura e testável, sem side effects.
     *
     * @param Progression Array de progressão da classe
     * @param LevelInClass Nível desejado (1-based)
     * @param OutLevelEntry [OUT] Entry do nível encontrado
     * @return true se nível foi encontrado, false caso contrário
     */
    static bool ExtractLevelFeatures(const TArray<FProgressEntry> &Progression, int32 LevelInClass,
                                     const FProgressEntry *&OutLevelEntry);

    /**
     * Carrega features de um nível específico e converte para FMulticlassClassFeature.
     * Busca features no ClassFeaturesDataTable usando os IDs do array Features.
     * Helper puro e testável, sem side effects.
     *
     * @param FeatureHandles Array de handles de features (FDataTableRowHandle[])
     * @param FeatureDataTable Data Table de features (pode ser nullptr)
     * @param LevelUnlocked Nível em que as features são desbloqueadas
     * @param OutFeatures [OUT] Array de features convertidas
     * @return true se pelo menos uma feature foi carregada, false caso contrário
     */
    static bool LoadFeaturesForLevel(const TArray<FDataTableRowHandle> &FeatureHandles,
                                     const UDataTable *FeatureDataTable, int32 LevelUnlocked,
                                     TArray<FMulticlassClassFeature> &OutFeatures);

    /**
     * Loga features ganhas em um nível específico de uma classe.
     * Busca informações da classe na tabela e registra no log quais features foram ganhas no nível.
     * Apenas loga informações, não carrega nem processa dados.
     * Helper de logging para multiclasse.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe (1-20)
     * @param ClassDataTable Data Table de classes para buscar informações (pode ser nullptr)
     */
    static void LogLevelChangeFeatures(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable);
};
