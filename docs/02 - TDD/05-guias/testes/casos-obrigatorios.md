# ✅ Casos de Teste Obrigatórios

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Para Helper Functions</b></summary>

> **ALWAYS test:**
>
> 1. **Valid case/happy path**
>    - Função funciona com entrada válida
>
> 2. **Nullptr/null input**
>    - Função lida corretamente com nullptr
>
> 3. **Not found case**
>    - Função retorna valor apropriado quando não encontra
>
> **Exemplo para `FindFeatRow()`:**
>
> - ✅ Com FeatName válido → retorna row
> - ✅ Com FeatName nullptr → retorna nullptr
> - ✅ Com FeatName inexistente → retorna nullptr
> - ✅ Com FeatDataTable nullptr → retorna nullptr

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Para Funções de Cálculo</b></summary>

> **ALWAYS test:**
>
> 1. **Valores normais**
>    - Função funciona com valores típicos
>
> 2. **Valores extremos**
>    - 0, máximo, negativo (se aplicável)
>
> 3. **Valores inválidos**
>    - nullptr, valores fora de range
>
> **Exemplo para `GetPrerequisites()`:**
>
> - ✅ Com string única → retorna array com 1 item
> - ✅ Com múltiplas strings (vírgula) → retorna array com N itens
> - ✅ Com string vazia → retorna array vazio
> - ✅ Sem chave "Prerequisites" → retorna array vazio

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](./index.md)
- [🎯 Padrão AAA](./padrao-aaa.md)
- [🎯 Regras de Teste](./regras-teste.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
