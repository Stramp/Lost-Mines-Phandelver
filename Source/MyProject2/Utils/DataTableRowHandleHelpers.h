// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

/**
 * Funções helper para manipulação de FDataTableRowHandle.
 * Funções puras e reutilizáveis seguindo princípios de Clean Code.
 */
namespace DataTableRowHandleHelpers
{
    /**
     * Resolve um FDataTableRowHandle para o row correspondente.
     *
     * @param Handle Handle a resolver
     * @return Row encontrado, ou nullptr se inválido
     */
    template<typename RowType>
    const RowType* ResolveHandle(const FDataTableRowHandle& Handle)
    {
        if (!Handle.IsNull() && Handle.DataTable)
        {
            return Handle.DataTable->FindRow<RowType>(Handle.RowName, TEXT("ResolveHandle"));
        }
        return nullptr;
    }

    /**
     * Cria um FDataTableRowHandle a partir de um DataTable e RowName.
     *
     * @param DataTable Data Table de referência
     * @param RowName Nome da row
     * @return Handle criado, ou Handle inválido se não encontrado
     */
    FDataTableRowHandle CreateHandle(UDataTable* DataTable, const FName& RowName);

    /**
     * Valida se um Handle aponta para um row válido.
     *
     * @param Handle Handle a validar
     * @return true se válido, false caso contrário
     */
    bool IsHandleValid(const FDataTableRowHandle& Handle);
} // namespace DataTableRowHandleHelpers
