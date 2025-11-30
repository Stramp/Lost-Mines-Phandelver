# Princípio: Editor-Friendly

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 🛠️ Editor-Friendly

**Conceito:** Sistema funciona perfeitamente no editor, permitindo configuração rápida sem rodar o jogo.

**Benefícios:**

- ✅ Designers podem trabalhar sem rodar o jogo
- ✅ Testes rápidos
- ✅ Iteração rápida
- ✅ Validação em tempo real

**Implementação:**

- Use `WITH_EDITOR` para código específico do editor
- Valide dados em `PostEditChangeProperty()`
- Use `UPROPERTY(EditAnywhere)` para propriedades editáveis
- Forneça feedback visual no editor quando possível

**Exemplo:**

```cpp
#if WITH_EDITOR
void UCharacterSheetDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    ValidateData();
}
#endif
```

---

**Navegação:** [← Modularidade](modularidade.md) | [→ Multiplayer-Ready](multiplayer-ready.md)

**Última atualização:** 2024-12-27
