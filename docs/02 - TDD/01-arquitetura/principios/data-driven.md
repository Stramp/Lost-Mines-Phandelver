# Princípio: Data-Driven

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 📊 Data-Driven

**Conceito:** Todas as regras vêm de Data Tables ou Data Assets, não de código hardcoded.

**Benefícios:**

- ✅ Designers podem modificar regras sem programadores
- ✅ Fácil adicionar novo conteúdo
- ✅ Suporte a localização
- ✅ Validação automática

**Implementação:**

- Use `UDataTable` para dados tabulares (raças, classes, itens)
- Use `UDataAsset` para configurações complexas (fichas de personagem)
- Valide dados no editor com `PostEditChangeProperty()`
- Use `FTableRowBase` para estruturas de dados

**Exemplo:**

```cpp
// ✅ CORRETO - Data-Driven
UPROPERTY(EditDefaultsOnly, Category = "Data")
UDataTable* RaceDataTable;

// ❌ ERRADO - Hardcoded
const float DwarfConstitutionBonus = 2.0f;
```

---

**Navegação:** [← Voltar para Princípios](index.md) | [→ Modularidade](modularidade.md)

**Última atualização:** 2024-12-27
