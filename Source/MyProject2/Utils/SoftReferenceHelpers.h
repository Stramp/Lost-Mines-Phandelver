// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/SoftObjectPtr.h"

/**
 * Funções helper para manipulação de Soft Object References.
 * Funções puras e reutilizáveis seguindo princípios de Clean Code.
 */
namespace SoftReferenceHelpers
{
    /**
     * Carrega um asset de uma Soft Reference de forma síncrona.
     *
     * @param SoftRef Soft Reference a carregar
     * @return Asset carregado, ou nullptr se falhar
     */
    template<typename AssetType>
    AssetType* LoadSoftReference(const TSoftObjectPtr<AssetType>& SoftRef)
    {
        if (!SoftRef.IsValid())
        {
            return nullptr;
        }
        return SoftRef.LoadSynchronous();
    }

    /**
     * Verifica se uma Soft Reference é válida (sem carregar).
     *
     * @param SoftRef Soft Reference a verificar
     * @return true se válida, false caso contrário
     */
    template<typename AssetType>
    bool IsSoftReferenceValid(const TSoftObjectPtr<AssetType>& SoftRef)
    {
        return SoftRef.IsValid();
    }
} // namespace SoftReferenceHelpers
