// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/Tables/ClassDataTable.h"
#include "Characters/Data/CharacterSheetDataAsset.h"

// Forward declarations
class UDataTable;
struct FClassFeature;
struct FClassFeatureChoice;

/**
 * Motor para processar escolhas de classe.
 * Responsável por coletar, validar e resolver escolhas baseadas em FClassFeatureChoice do DataTable.
 */
class MYPROJECT2_API FChoiceMotor
{
public:
    /**
     * Coleta todas as escolhas disponíveis para uma classe até um determinado nível.
     * Busca features do tipo "Choice" ou "SubclassSelection" no DataTable e cria FClassChoice.
     *
     * @param ClassName Nome da classe
     * @param ClassLevel Nível atual da classe
     * @param ClassDataTable Data Table de classes
     * @return Array de FClassChoice disponíveis (com todas as opções em AvailableSingleChoices/AvailableMultChoice)
     */
    static TArray<FClassChoice> CollectAvailableChoices(FName ClassName, int32 ClassLevel, UDataTable *ClassDataTable);

    /**
     * Valida uma escolha contra as regras do DataTable.
     * Verifica se as escolhas feitas (AvailableSingleChoices/AvailableMultChoice) estão dentro das opções originais e
     * se quantidade está correta.
     *
     * @param Choice Escolha a ser validada
     * @param ClassName Nome da classe
     * @param ClassDataTable Data Table de classes
     * @param OutErrorMessage Mensagem de erro se inválida
     * @return true se válida, false caso contrário
     */
    static bool ValidateChoice(const FClassChoice &Choice, FName ClassName, UDataTable *ClassDataTable,
                               FString &OutErrorMessage);

    // TODO: Reimplementar usando nova estrutura FClassData.FProgress
    // Estrutura antiga (FClassFeatureChoice) não existe mais
    // static TArray<FClassFeatureChoice> ResolveDependencies(const TArray<FClassFeatureChoice> &AvailableChoices,
    //                                                          const TArray<FClassChoice> &MadeChoices);

private:
    /**
     * Converte FClassFeatureChoice (do DataTable) para FClassChoice (do Data Asset).
     */
    static FClassChoice ConvertFeatureChoiceToClassChoice(const FClassFeatureChoice &FeatureChoice,
                                                          const FClassFeature &Feature, int32 ClassLevel);

    /**
     * Determina o ChoiceType baseado na feature e na escolha.
     */
    static FName DetermineChoiceType(const FClassFeature &Feature, const FClassFeatureChoice &FeatureChoice);

    /**
     * Cria FClassChoice a partir de uma Feature do tipo "Choice" sem Choices definidas no JSON.
     * Gera ChoiceID único no formato: ClassName_FeatureName_Level
     *
     * @param Feature Feature do tipo "Choice"
     * @param ClassName Nome da classe
     * @param ClassLevel Nível da classe
     * @param ClassDataTable Data Table de classes
     * @return FClassChoice criada com ChoiceID único e opções preenchidas
     */
    static FClassChoice CreateChoiceFromFeature(const FClassFeature &Feature, FName ClassName, int32 ClassLevel,
                                                UDataTable *ClassDataTable);

    /**
     * Gera ChoiceID único no formato: ClassName_FeatureName_Level
     *
     * @param ClassName Nome da classe
     * @param FeatureName Nome da feature
     * @param Level Nível da feature
     * @return ChoiceID único
     */
    static FName GenerateUniqueChoiceID(FName ClassName, FName FeatureName, int32 Level);

    /**
     * Busca opções para uma feature do tipo "Choice" sem Choices definidas.
     * Tenta buscar do DataTable primeiro, depois usa fallback hardcoded para casos conhecidos.
     *
     * @param ChoiceID ChoiceID da escolha
     * @param FeatureName Nome da feature
     * @param ClassName Nome da classe
     * @param ClassLevel Nível da classe
     * @param ClassDataTable Data Table de classes
     * @return Array de opções disponíveis
     */
    static TArray<FName> FindOptionsForChoiceFeature(FName ChoiceID, FName FeatureName, FName ClassName,
                                                     int32 ClassLevel, UDataTable *ClassDataTable);
};
