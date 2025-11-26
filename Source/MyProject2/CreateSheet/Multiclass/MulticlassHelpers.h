// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class UDataTable;
struct FProficienciesEntry;
struct FMulticlassProficienciesEntry;
struct FClassDataRow;
struct FProgressEntry;

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
     * Converte FProficienciesEntry (tabela) para FMulticlassProficienciesEntry (Data Asset).
     * Helper puro e testável para conversão de estruturas de proficiências.
     *
     * @param SourceEntry Entry da tabela
     * @return Entry convertida para Data Asset
     */
    static FMulticlassProficienciesEntry ConvertProficienciesEntry(const FProficienciesEntry &SourceEntry);

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
};
