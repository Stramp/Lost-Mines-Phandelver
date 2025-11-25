// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChoiceMotor.h"
#include "Data/Tables/ClassDataTable.h"
#include "Utils/DataTableHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/ChoiceHelpers.h"
#include "Logging/LogMacros.h"

TArray<FClassChoice> FChoiceMotor::CollectAvailableChoices(FName ClassName, int32 ClassLevel,
                                                           UDataTable *ClassDataTable)
{
    TArray<FClassChoice> AvailableChoices;

    if (!ClassDataTable || ClassName == NAME_None || ClassLevel < 1)
    {
        return AvailableChoices;
    }

    // Busca features até o nível atual
    TArray<FClassFeature> Features = CharacterSheetHelpers::GetFeaturesAtLevel(ClassName, ClassLevel, ClassDataTable);

    // Para cada feature, verifica se tem escolhas
    for (const FClassFeature &Feature : Features)
    {
        // Apenas features do tipo "Choice" ou "SubclassSelection" têm escolhas
        if (Feature.FeatureType != TEXT("Choice") && Feature.FeatureType != TEXT("SubclassSelection") &&
            Feature.FeatureType != TEXT("ASI"))
        {
            continue;
        }

        // Se a feature tem escolhas definidas no DataTable
        if (Feature.Choices.Num() > 0)
        {
            // Para cada escolha na feature, cria um FClassChoice
            for (const FClassFeatureChoice &FeatureChoice : Feature.Choices)
            {
                FClassChoice ClassChoice =
                    ConvertFeatureChoiceToClassChoice(FeatureChoice, Feature, Feature.LevelUnlocked);
                AvailableChoices.Add(ClassChoice);
            }
        }
        else
        {
            // Se não tem Choices definidas, cria uma escolha baseada no FeatureType
            if (Feature.FeatureType == TEXT("Choice"))
            {
                FClassChoice ChoiceChoice = CreateChoiceFromFeature(Feature, ClassName, ClassLevel, ClassDataTable);
                AvailableChoices.Add(ChoiceChoice);
            }
            else if (Feature.FeatureType == TEXT("ASI"))
            {
                FClassChoice ASIChoice;
                ASIChoice.ChoiceID = Feature.FeatureID;
                ASIChoice.ChoiceName = Feature.FeatureName;
                ASIChoice.ChoiceType = TEXT("ASI");
                ASIChoice.Level = Feature.LevelUnlocked;
                ASIChoice.AvailableSingleChoices = {TEXT("Strength+2"),
                                                    TEXT("Dexterity+2"),
                                                    TEXT("Constitution+2"),
                                                    TEXT("Intelligence+2"),
                                                    TEXT("Wisdom+2"),
                                                    TEXT("Charisma+2"),
                                                    TEXT("Feat")};
                AvailableChoices.Add(ASIChoice);
            }
            else if (Feature.FeatureType == TEXT("SubclassSelection"))
            {
                // SubclassSelection sem Choices definidas: busca SubclassNames do ClassDataRow
                FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, ClassDataTable);
                if (ClassRow && ClassRow->SubclassNames.Num() > 0)
                {
                    FClassChoice SubclassChoice;
                    SubclassChoice.ChoiceID = Feature.FeatureID;
                    SubclassChoice.ChoiceName = Feature.FeatureName;
                    SubclassChoice.ChoiceType = TEXT("SubclassSelection");
                    SubclassChoice.Level = Feature.LevelUnlocked;
                    SubclassChoice.AvailableSingleChoices = ClassRow->SubclassNames;
                    AvailableChoices.Add(SubclassChoice);
                }
            }
        }
    }

    return AvailableChoices;
}

bool FChoiceMotor::ValidateChoice(const FClassChoice &Choice, FName ClassName, UDataTable *ClassDataTable,
                                  FString &OutErrorMessage)
{
    if (Choice.ChoiceID == NAME_None)
    {
        OutErrorMessage = TEXT("ChoiceID não pode ser vazio");
        return false;
    }

    // Busca a feature correspondente no DataTable
    TArray<FClassFeature> Features = CharacterSheetHelpers::GetFeaturesAtLevel(ClassName, Choice.Level, ClassDataTable);
    FClassFeatureChoice *FoundFeatureChoice = nullptr;
    FClassFeature *FoundFeature = nullptr;

    for (FClassFeature &Feature : Features)
    {
        for (FClassFeatureChoice &FeatureChoice : Feature.Choices)
        {
            if (FeatureChoice.ChoiceID == Choice.ChoiceID)
            {
                FoundFeatureChoice = &FeatureChoice;
                FoundFeature = &Feature;
                break;
            }
        }
        if (FoundFeatureChoice)
        {
            break;
        }
    }

    // Se não encontrou no DataTable, pode ser uma escolha especial (ex: ASI)
    if (!FoundFeatureChoice)
    {
        // ASI e SubclassSelection podem não ter FeatureChoice definida
        if (Choice.ChoiceType == TEXT("ASI") || Choice.ChoiceType == TEXT("SubclassSelection"))
        {
            // Valida se há escolha feita (AvailableSingleChoices deve ter exatamente 1 item após escolha)
            if (Choice.AvailableSingleChoices.Num() != 1)
            {
                OutErrorMessage = FString::Printf(TEXT("ASI requer uma escolha, mas nenhuma foi fornecida"));
                return false;
            }
            return true;
        }

        OutErrorMessage =
            FString::Printf(TEXT("ChoiceID '%s' não encontrado no DataTable"), *Choice.ChoiceID.ToString());
        return false;
    }

    // Valida quantidade de escolhas baseado no tipo
    if (Choice.ChoiceType == TEXT("Simple") || Choice.ChoiceType == TEXT("SubclassSelection") ||
        Choice.ChoiceType == TEXT("ASI"))
    {
        // Escolhas simples: AvailableSingleChoices deve ter exatamente 1 item após escolha
        if (Choice.AvailableSingleChoices.Num() != 1)
        {
            OutErrorMessage = FString::Printf(TEXT("Escolha requer um valor, mas nenhum foi fornecido"));
            return false;
        }
        // Valida se a escolha está nas opções originais do DataTable
        if (!FoundFeatureChoice->AvailableOptions.Contains(Choice.AvailableSingleChoices[0]))
        {
            OutErrorMessage = FString::Printf(TEXT("Valor '%s' não está nas opções disponíveis"),
                                              *Choice.AvailableSingleChoices[0].ToString());
            return false;
        }
    }
    else if (Choice.ChoiceType == TEXT("Multiple"))
    {
        // Escolhas múltiplas: AvailableMultChoice deve ter a quantidade correta após escolhas
        if (Choice.AvailableMultChoice.Num() != FoundFeatureChoice->ChoicesAllowed)
        {
            OutErrorMessage = FString::Printf(TEXT("Escolha requer %d valor(es), mas %d foram fornecidos"),
                                              FoundFeatureChoice->ChoicesAllowed, Choice.AvailableMultChoice.Num());
            return false;
        }
        // Valida se todas as escolhas estão nas opções originais do DataTable
        for (const FName &SelectedValue : Choice.AvailableMultChoice)
        {
            if (!FoundFeatureChoice->AvailableOptions.Contains(SelectedValue))
            {
                OutErrorMessage =
                    FString::Printf(TEXT("Valor '%s' não está nas opções disponíveis"), *SelectedValue.ToString());
                return false;
            }
        }
    }

    return true;
}

TArray<FClassFeatureChoice> FChoiceMotor::ResolveDependencies(const TArray<FClassFeatureChoice> &AvailableChoices,
                                                              const TArray<FClassChoice> &MadeChoices)
{
    TArray<FClassFeatureChoice> ResolvedChoices;

    for (const FClassFeatureChoice &Choice : AvailableChoices)
    {
        // Se não tem dependência, adiciona diretamente
        if (Choice.DependsOnChoiceID == NAME_None)
        {
            ResolvedChoices.Add(Choice);
            continue;
        }

        // Busca a escolha dependente nas escolhas já feitas
        bool bDependencyMet = false;
        for (const FClassChoice &MadeChoice : MadeChoices)
        {
            if (MadeChoice.ChoiceID == Choice.DependsOnChoiceID)
            {
                // Verifica dependência nos arrays de escolhas
                bool bValueMatches = false;
                if (MadeChoice.ChoiceType == TEXT("Simple") || MadeChoice.ChoiceType == TEXT("SubclassSelection") ||
                    MadeChoice.ChoiceType == TEXT("ASI"))
                {
                    // Para escolhas simples, AvailableSingleChoices deve ter 1 item com o valor escolhido
                    bValueMatches = MadeChoice.AvailableSingleChoices.Num() > 0 &&
                                    MadeChoice.AvailableSingleChoices[0] == Choice.RequiredValue;
                }
                else if (MadeChoice.ChoiceType == TEXT("Multiple"))
                {
                    // Para escolhas múltiplas, AvailableMultChoice contém as escolhas feitas
                    bValueMatches = MadeChoice.AvailableMultChoice.Contains(Choice.RequiredValue);
                }

                if (bValueMatches)
                {
                    bDependencyMet = true;
                    break;
                }
            }
        }

        // Se dependência foi atendida, adiciona à lista
        if (bDependencyMet)
        {
            ResolvedChoices.Add(Choice);
        }
    }

    return ResolvedChoices;
}

FClassChoice FChoiceMotor::ConvertFeatureChoiceToClassChoice(const FClassFeatureChoice &FeatureChoice,
                                                             const FClassFeature &Feature, int32 ClassLevel)
{
    FClassChoice ClassChoice;
    ClassChoice.ChoiceID = FeatureChoice.ChoiceID;
    ClassChoice.ChoiceName = Feature.FeatureName;
    ClassChoice.ChoiceType = DetermineChoiceType(Feature, FeatureChoice);
    ClassChoice.Level = ClassLevel;

    // Preenche opções disponíveis baseado no tipo
    if (ClassChoice.ChoiceType == TEXT("Multiple"))
    {
        ClassChoice.AvailableMultChoice = FeatureChoice.AvailableOptions;
    }
    else
    {
        ClassChoice.AvailableSingleChoices = FeatureChoice.AvailableOptions;
    }

    return ClassChoice;
}

FName FChoiceMotor::DetermineChoiceType(const FClassFeature &Feature, const FClassFeatureChoice &FeatureChoice)
{
    // Se FeatureType é SubclassSelection, retorna SubclassSelection
    if (Feature.FeatureType == TEXT("SubclassSelection"))
    {
        return TEXT("SubclassSelection");
    }

    // Se FeatureType é ASI, retorna ASI
    if (Feature.FeatureType == TEXT("ASI"))
    {
        return TEXT("ASI");
    }

    // Se ChoicesAllowed > 1, é Multiple
    if (FeatureChoice.ChoicesAllowed > 1)
    {
        return TEXT("Multiple");
    }

    // Padrão: Simple
    return TEXT("Simple");
}

FClassChoice FChoiceMotor::CreateChoiceFromFeature(const FClassFeature &Feature, FName ClassName, int32 ClassLevel,
                                                   UDataTable *ClassDataTable)
{
    FClassChoice ChoiceChoice;

    // Gera ChoiceID único: ClassName_FeatureName_Level
    ChoiceChoice.ChoiceID = GenerateUniqueChoiceID(ClassName, Feature.FeatureName, Feature.LevelUnlocked);
    ChoiceChoice.ChoiceName = Feature.FeatureName;
    ChoiceChoice.ChoiceType = TEXT("Simple");
    ChoiceChoice.Level = Feature.LevelUnlocked;

    // Busca opções para esta feature
    TArray<FName> Options =
        FindOptionsForChoiceFeature(ChoiceChoice.ChoiceID, Feature.FeatureName, ClassName, ClassLevel, ClassDataTable);

    UE_LOG(LogTemp, Warning,
           TEXT("[ChoiceMotor] CreateChoiceFromFeature: ChoiceID=%s, FeatureName=%s, Options.Num()=%d"),
           *ChoiceChoice.ChoiceID.ToString(), *Feature.FeatureName.ToString(), Options.Num());

    // Preenche AvailableSingleChoices com opções encontradas
    if (Options.Num() > 0)
    {
        ChoiceChoice.AvailableSingleChoices = Options;
        UE_LOG(LogTemp, Warning, TEXT("[ChoiceMotor] AvailableSingleChoices preenchido: %d opções"), Options.Num());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[ChoiceMotor] NENHUMA opção encontrada para ChoiceID=%s"),
               *ChoiceChoice.ChoiceID.ToString());
    }

    return ChoiceChoice;
}

FName FChoiceMotor::GenerateUniqueChoiceID(FName ClassName, FName FeatureName, int32 Level)
{
    // Formato: ClassName_FeatureName_Level (ex: "Fighter_FightingStyle_1")
    // Remove espaços do FeatureName para evitar ChoiceIDs com espaços
    FString FeatureNameStr = FeatureName.ToString();
    FeatureNameStr.ReplaceInline(TEXT(" "), TEXT("")); // Remove espaços

    FString ChoiceIDString = FString::Printf(TEXT("%s_%s_%d"), *ClassName.ToString(), *FeatureNameStr, Level);
    return FName(*ChoiceIDString);
}

TArray<FName> FChoiceMotor::FindOptionsForChoiceFeature(FName ChoiceID, FName FeatureName, FName ClassName,
                                                        int32 ClassLevel, UDataTable *ClassDataTable)
{
    // Tenta buscar opções do DataTable primeiro
    TArray<FName> Options = CharacterSheetHelpers::GetChoiceOptions(ChoiceID, ClassName, ClassLevel, ClassDataTable);

    // Se não encontrou, tenta buscar usando FeatureName como ChoiceID (compatibilidade)
    if (Options.Num() == 0)
    {
        Options = CharacterSheetHelpers::GetChoiceOptions(FeatureName, ClassName, ClassLevel, ClassDataTable);
    }

    // Fallback hardcoded para casos conhecidos (Fighting Style)
    // Verifica tanto "Fighting Style" (com espaço) quanto "FightingStyle" (sem espaço)
    if (Options.Num() == 0)
    {
        FString FeatureNameStr = FeatureName.ToString();
        if (FeatureNameStr == TEXT("Fighting Style") || FeatureNameStr == TEXT("FightingStyle"))
        {
            Options = {TEXT("Archery"),    TEXT("Defense"),
                       TEXT("Dueling"),    TEXT("Great Weapon Fighting"),
                       TEXT("Protection"), TEXT("Two-Weapon Fighting")};
        }
    }

    return Options;
}
