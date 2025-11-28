// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

// Forward declarations
class UDataTable;
struct FProficienciesEntry;
struct FMulticlassProficienciesEntry;
struct FClassDataRow;
struct FProgressEntry;
struct FFeatureDataRow;
struct FMulticlassClassFeature;
struct FDataTableRowHandle;

/**
 * Helpers para estrutura de dados de multiclasse.
 * Funções auxiliares para manipulação de arrays e estruturas de multiclasse.
 * Validação de atributos está em FMulticlassValidators.
 */
class MYPROJECT2_API FMulticlassHelpers
{
public:
    /**
     * Retorna classes disponíveis com tags de requisitos faltantes.
     * Classes que não atendem requisitos terão tag como "[INT +13]" indicando o requisito faltante.
     *
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param Attributes Array de atributos na ordem: [STR, DEX, CON, INT, WIS, CHA]
     * @return Array de FName com nomes das classes (com tags se não disponíveis)
     */
    static TArray<FName> GetAvailableClassWithTagRequirements(const UDataTable *ClassDataTable,
                                                              const TArray<int32> &Attributes);

    /**
     * Valida se é permitido processar Progression para uma entrada de multiclasse.
     * Regra: Progression só pode ser processada se há classe válida (Name != NAME_None) e nível > 0.
     * Função pura e testável, sem side effects.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe
     * @return true se é válido processar Progression, false caso contrário
     */
    static bool CanProcessProgression(FName ClassName, int32 LevelInClass);

    /**
     * Resolve array de handles de proficiências para nomes legíveis.
     * Helper puro e testável para resolução de handles de proficiências (estrutura flat).
     *
     * @param ProficiencyHandles Array de handles de proficiências (FDataTableRowHandle[])
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com nomes legíveis (ex: ["Simple Weapons"]) ou IDs originais se não encontrado
     */
    static TArray<FName> ResolveProficiencyHandlesToNames(const TArray<struct FDataTableRowHandle> &ProficiencyHandles,
                                                           const UDataTable *ProficiencyDataTable);

    /**
     * Resolve array de IDs de proficiências para nomes legíveis (legado - mantido para compatibilidade).
     * Helper puro e testável para resolução de IDs de proficiências.
     *
     * @param ProficiencyIDs Array de IDs de proficiências (ex: ["PW_Simple_Weapons"])
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com nomes legíveis (ex: ["Simple Weapons"]) ou IDs originais se não encontrado
     */
    static TArray<FName> ResolveProficiencyIDsToNames(const TArray<FName> &ProficiencyIDs,
                                                      const UDataTable *ProficiencyDataTable);

    /**
     * Converte FProficienciesEntry (tabela) para FMulticlassProficienciesEntry (Data Asset) retornando nomes legíveis.
     * Resolve IDs de proficiências (ex: "PW_Simple_Weapons") para nomes legíveis (ex: "Simple Weapons").
     * Helper puro e testável para conversão de estruturas de proficiências.
     *
     * @param SourceEntry Entry da tabela
     * @param ProficiencyDataTable Data Table de proficiências para resolver IDs (pode ser nullptr)
     * @return Entry convertida para Data Asset com nomes legíveis
     */
    static FMulticlassProficienciesEntry ConvertProficienciesEntry(const FProficienciesEntry &SourceEntry,
                                                                   const UDataTable *ProficiencyDataTable);

    /**
     * Valida parâmetros de entrada para carregamento de proficiências.
     * Proficiências são ganhas apenas no nível 1.
     * Função pura e testável, sem side effects.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe (deve ser 1)
     * @param ClassDataTable Data Table de classes
     * @return true se parâmetros são válidos, false caso contrário
     */
    static bool ValidateLoadProficienciesInputs(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable);

    /**
     * Constrói string formatada com lista de features.
     * Helper puro e testável para formatação de arrays de features.
     *
     * @param Features Array de nomes de features
     * @return String formatada (ex: "Feature1, Feature2" ou "Nenhum")
     */
    static FString BuildFeaturesString(const TArray<FName> &Features);

    /**
     * Valida parâmetros de entrada para ProcessLevelChange.
     * Função pura e testável, sem side effects.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe
     * @param ClassDataTable Data Table de classes
     * @return true se parâmetros são válidos, false caso contrário
     */
    static bool ValidateProcessLevelChangeInputs(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable);

    /**
     * Busca e valida dados da classe na tabela.
     * Função pura e testável, sem side effects.
     *
     * @param ClassName Nome da classe
     * @param ClassDataTable Data Table de classes
     * @return Row da classe encontrada, ou nullptr se não encontrada
     */
    static const struct FClassDataRow *FindAndValidateClassRow(FName ClassName, const UDataTable *ClassDataTable);

    /**
     * Extrai features do nível específico da progressão.
     * Função pura e testável, sem side effects.
     *
     * @param Progression Array de progressão da classe
     * @param LevelInClass Nível desejado (1-based)
     * @param OutLevelEntry [OUT] Entry do nível encontrado
     * @return true se nível foi encontrado, false caso contrário
     */
    static bool ExtractLevelFeatures(const TArray<struct FProgressEntry> &Progression, int32 LevelInClass,
                                     const struct FProgressEntry *&OutLevelEntry);

    /**
     * Converte FFeatureDataRow (tabela) para FMulticlassClassFeature (Data Asset).
     * Helper puro e testável para conversão de features.
     *
     * @param FeatureRow Row da feature da tabela
     * @param LevelUnlocked Nível em que a feature é desbloqueada
     * @return Feature convertida para Data Asset
     */
    static FMulticlassClassFeature ConvertFeatureRowToMulticlassFeature(const FFeatureDataRow &FeatureRow,
                                                                        int32 LevelUnlocked);

    /**
     * Carrega features de um nível específico e converte para FMulticlassClassFeature.
     * Busca features no ClassFeaturesDataTable usando os IDs do array Features.
     * Helper puro e testável, sem side effects.
     *
     * @param FeatureIDs Array de IDs de features (ex: ["FC_SecondWind", "FC_FightingStyle"])
     * @param FeatureDataTable Data Table de features (pode ser nullptr)
     * @param LevelUnlocked Nível em que as features são desbloqueadas
     * @param OutFeatures [OUT] Array de features convertidas
     * @return true se pelo menos uma feature foi carregada, false caso contrário
     */
    static bool LoadFeaturesForLevel(const TArray<FDataTableRowHandle> &FeatureHandles, const UDataTable *FeatureDataTable,
                                     int32 LevelUnlocked, TArray<FMulticlassClassFeature> &OutFeatures);

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
     * Verifica se uma feature tem escolhas disponíveis para o jogador.
     * Retorna true se FeatureType é "Choice" ou "SubclassSelection" E bHasAvailableChoices é true.
     * Helper puro e testável, sem side effects.
     * Usado para validações e verificações futuras.
     * Nota: A flag bHasAvailableChoices é calculada em ConvertFeatureRowToMulticlassFeature usando dados da tabela.
     *
     * @param Feature Feature a verificar
     * @return true se feature tem escolhas disponíveis, false caso contrário
     */
    static bool FeatureHasAvailableChoices(const FMulticlassClassFeature &Feature);

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
