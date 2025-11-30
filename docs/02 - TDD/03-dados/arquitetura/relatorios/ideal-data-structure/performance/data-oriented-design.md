# Estrutura de Dados Orientada a Performance (Data-Oriented Design)

## Estrutura Atual (Array of Structures - AoS)

```cpp
// ❌ INEFICIENTE - Dados espalhados na memória
TArray<FRaceData> Races; // Cada objeto tem todos os campos juntos
```

## Estrutura Ideal (Structure of Arrays - SoA)

```cpp
// ✅ EFICIENTE - Dados contíguos, cache-friendly
struct FRaceDataSoA {
    TArray<FName> RaceIDs;           // Array contíguo de IDs
    TArray<FName> RaceNames;         // Array contíguo de nomes
    TArray<int32> BaseSpeeds;        // Array contíguo de speeds
    TArray<TArray<FName>> TraitIDs;  // Array de arrays de traits
    // ... permite SIMD, prefetching, cache hits
};
```

## Serialização Binária (Estilo LSF/Baldur's Gate 3)

- **Formato:** FlatBuffers ou Protobuf (não JSON para runtime)
- **Versionamento:** Schema registry para backward/forward compatibility
- **Diferencial:** Salvar apenas deltas, não estado completo

---

## 🔗 Navegação

- [📚 Relatório - Índice](../index.md)
- [✅ Checklist de Migração](../checklist-migracao.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de ideal-data-structure-report.md |
