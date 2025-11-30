# Boas Práticas - Data Tables

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Recomendações</b></summary>

> 1. **Nomes consistentes:** Use nomes consistentes entre Data Tables (ex: "Human" em RaceDataTable deve corresponder a "Human" em CharacterSheetDataAsset)
> 2. **Row Names:** Use o campo `Name` como Row Name (facilita busca com `FindRow`)
> 3. **Localização:** Use `FText` para descrições (suporta localização)
> 4. **Dados estruturados:** Use `TMap<FName, FString>` para dados programáticos quando necessário
> 5. **Validação:** Sempre valide JSON antes de importar (use validação JSON online)

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

**Navegação:** [← Índice](index.md) | [→ Troubleshooting](troubleshooting.md)

**Última atualização:** 2024-12-27
