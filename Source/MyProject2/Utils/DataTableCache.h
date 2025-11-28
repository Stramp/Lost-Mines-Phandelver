// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Data Table Cache
// ============================================================================
#pragma region Data Table Cache

/**
 * Cache de lookup para Data Tables (performance).
 *
 * Responsabilidade:
 * - Cachear resoluções frequentes de FDataTableRowHandle
 * - Reduzir overhead de lookup em loops
 * - Limpar cache quando necessário (ex: reload de Data Tables)
 *
 * Princípio: Data-Oriented Design - reduzir indireção
 * - Cachea resoluções frequentes para evitar lookups repetidos
 * - Melhora performance em loops grandes
 * - Alinhado com planos5.md (cache de lookups)
 *
 * Uso:
 * ```cpp
 * const FRaceDataRow* RaceRow = FDataTableCache::GetCachedRow<FRaceDataRow>(Handle);
 * ```
 */
class MYPROJECT2_API FDataTableCache
{
public:
    /**
     * Obtém row do cache ou resolve e cacheia se não estiver em cache.
     *
     * @param Handle Handle a resolver
     * @return Row encontrado, ou nullptr se inválido
     */
    template<typename RowType>
    static const RowType* GetCachedRow(const FDataTableRowHandle& Handle)
    {
        if (Handle.IsNull() || !Handle.DataTable)
        {
            return nullptr;
        }

        // Verificar cache
        FHandleKey CacheKey;
        CacheKey.DataTable = Handle.DataTable;
        CacheKey.RowName = Handle.RowName;
        if (const void** CachedPtr = GetCache().Find(CacheKey))
        {
            return static_cast<const RowType*>(*CachedPtr);
        }

        // Resolver e cachear
        const RowType* Row = Handle.DataTable->FindRow<RowType>(Handle.RowName, TEXT("FDataTableCache::GetCachedRow"));
        if (Row)
        {
            GetCache().Add(CacheKey, Row);
        }

        return Row;
    }

    /**
     * Limpa o cache.
     * Deve ser chamado quando Data Tables são recarregados.
     */
    static void ClearCache()
    {
        GetCache().Empty();
    }

    /**
     * Obtém estatísticas do cache (para debugging).
     *
     * @return Número de entradas em cache
     */
    static int32 GetCacheSize()
    {
        return GetCache().Num();
    }

private:
    /**
     * Chave para o cache (DataTable + RowName).
     */
    struct FHandleKey
    {
        UDataTable* DataTable;
        FName RowName;

        FHandleKey()
            : DataTable(nullptr)
            , RowName(NAME_None)
        {
        }

        FHandleKey(UDataTable* InDataTable, const FName& InRowName)
            : DataTable(InDataTable)
            , RowName(InRowName)
        {
        }

        bool operator==(const FHandleKey& Other) const
        {
            return DataTable == Other.DataTable && RowName == Other.RowName;
        }

        friend uint32 GetTypeHash(const FHandleKey& Key)
        {
            return HashCombine(GetTypeHash(Key.DataTable), GetTypeHash(Key.RowName));
        }
    };

    /**
     * Obtém o cache estático (thread-safe para uso em game thread).
     *
     * @return Referência ao cache
     */
    static TMap<FHandleKey, const void*>& GetCache()
    {
        static TMap<FHandleKey, const void*> Cache;
        return Cache;
    }
};

#pragma endregion Data Table Cache
