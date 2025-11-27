// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * Constantes do sistema D&D 5e.
 * Centraliza todos os valores mágicos do sistema para melhor manutenibilidade.
 *
 * Princípio: Data-Driven - valores que são regras do sistema D&D 5e.
 * Se um valor pode mudar por configuração, deve estar em Data Table.
 * Se é uma constante do sistema, deve estar aqui.
 */
namespace DnDConstants
{
    // ============================================================================
    // Ability Scores
    // ============================================================================

    /** Valor mínimo de Ability Score (1) */
    constexpr int32 MIN_ABILITY_SCORE = 1;

    /** Valor máximo de Ability Score (30) */
    constexpr int32 MAX_ABILITY_SCORE = 30;

    /** Valor base de Ability Score para Point Buy (8) */
    constexpr int32 BASE_ABILITY_SCORE = 8;

    /** Valor máximo de Ability Score no Point Buy (15) */
    constexpr int32 MAX_POINT_BUY_SCORE = 15;

    /** Valor mínimo de Ability Score no Point Buy (8) */
    constexpr int32 MIN_POINT_BUY_SCORE = 8;

    /** Número de Ability Scores (6: STR, DEX, CON, INT, WIS, CHA) */
    constexpr int32 NUM_ABILITY_SCORES = 6;

    // ============================================================================
    // Point Buy System
    // ============================================================================

    /** Pontos máximos disponíveis no Point Buy (27) */
    constexpr int32 MAX_POINT_BUY_POINTS = 27;

    // ============================================================================
    // Levels
    // ============================================================================

    /** Nível mínimo de personagem (1) */
    constexpr int32 MIN_LEVEL = 1;

    /** Nível máximo de personagem (20) */
    constexpr int32 MAX_LEVEL = 20;

    /** Nível em que subclasses são escolhidas (3) */
    constexpr int32 SUBCLASS_SELECTION_LEVEL = 3;

    // ============================================================================
    // Feats
    // ============================================================================

    /** Níveis em que feats são ganhos (4, 8, 12, 16, 19) */
    constexpr int32 FEAT_LEVELS[] = {4, 8, 12, 16, 19};

    /** Número de níveis que concedem feats (5) */
    constexpr int32 NUM_FEAT_LEVELS = 5;

    // ============================================================================
    // Skills
    // ============================================================================

    /** Número de skills em D&D 5e (18) */
    constexpr int32 NUM_SKILLS = 18;

    // ============================================================================
    // Hit Dice
    // ============================================================================

    /** Hit Die mínimo (d6 - Wizard, Sorcerer) */
    constexpr int32 MIN_HIT_DIE = 6;

    /** Hit Die máximo (d12 - Barbarian) */
    constexpr int32 MAX_HIT_DIE = 12;

    // ============================================================================
    // Variant Human
    // ============================================================================

    /** Número de Ability Scores que Variant Human pode escolher (2) */
    constexpr int32 VARIANT_HUMAN_ABILITY_SCORE_CHOICES = 2;

    /** Número de skills que Variant Human pode escolher (1) */
    constexpr int32 VARIANT_HUMAN_SKILL_CHOICES = 1;

    /** Número de feats que Variant Human pode escolher (1) */
    constexpr int32 VARIANT_HUMAN_FEAT_CHOICES = 1;
} // namespace DnDConstants
