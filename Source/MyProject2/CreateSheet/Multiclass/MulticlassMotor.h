// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
struct FCharacterSheetData;
class UDataTable;

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
     * @return Array com nomes de classes disponíveis (que atendem requisitos de atributo)
     */
    static TArray<FName> GetAvailableClasses(const UDataTable *ClassDataTable, int32 FinalStrength,
                                             int32 FinalDexterity, int32 FinalConstitution, int32 FinalIntelligence,
                                             int32 FinalWisdom, int32 FinalCharisma);

    /**
     * Valida requisitos de atributo para multiclasse.
     * Verifica se o personagem atende aos requisitos mínimos de atributo para pegar uma nova classe.
     *
     * @param Data Estrutura genérica com dados de classe e atributos finais
     * @param DesiredClassName Nome da classe desejada para multiclasse
     * @return true se requisitos atendidos, false caso contrário
     */
    static bool ValidateMulticlassRequirements(const FCharacterSheetData &Data, FName DesiredClassName);

    /**
     * Aplica regras de multiclasse.
     * Calcula e aplica todas as regras relacionadas a multiclasse (proficiências, features, etc.).
     *
     * @param Data Estrutura genérica com dados de classe e referências necessárias
     */
    static void ApplyMulticlassRules(FCharacterSheetData &Data);

    /**
     * Processa mudança de nível em uma classe específica.
     * Chamado quando LevelInClass é alterado no editor.
     * Busca informações da classe na tabela e loga features ganhas no nível.
     *
     * @param ClassName Nome da classe que teve o nível alterado
     * @param LevelInClass Novo nível na classe (1-20)
     * @param ClassDataTable Data Table de classes para buscar informações (pode ser nullptr)
     */
    static void ProcessLevelChange(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable);
};
