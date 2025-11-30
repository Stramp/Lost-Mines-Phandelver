# 💡 Dicas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Boas Práticas</b></summary>

> **Quando escrever testes:**
>
> - ✅ Criar nova função helper em `Utils/`
> - ✅ Implementar lógica de cálculo complexa
> - ✅ Refatorar código crítico
> - ✅ Corrigir bug (adicionar teste que reproduz o bug)
>
> **Quando pular testes:**
>
> - ❌ Código muito simples (getter/setter)
> - ❌ Wrapper direto de Unreal API
> - ❌ Código temporário (mas lembre-se: não deveria ter código temporário!)

</details>

---

## 🚀 Próximos Passos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Checklist de Implementação</b></summary>

> **Status atual:**
>
> - [x] Configurar módulo de testes no `.Build.cs` (AutomationTest adicionado)
> - [x] Criar estrutura de pastas `Tests/` em cada módulo
> - [x] Implementar testes para helpers críticos:
> - [x] `CalculationHelpers` - ✅ 28 testes
> - [x] `ValidationHelpers` - ✅ 35 testes
> - [x] `CharacterSheetHelpers` - ✅ 36 testes
> - [x] `DataTableHelpers` - ✅ 13 testes
> - [x] `FormattingHelpers` - ✅ 10 testes
> - [x] `ChoiceHelpers` - ✅ 7 testes
> - [x] `FeatDataTable` - ✅ 6 testes
> - [x] `ComponentHelpers` - ✅ 3 testes
> - [x] Executar testes no Editor (Automation Tool)
> - [ ] Integrar testes no CI/CD (planejado)
>
> **Total:** 275+ testes implementados e funcionando

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](./index.md)
- [🎯 Regras de Teste](./regras-teste.md)
- [🧪 Testes de Integração](./integracao/testes-integracao.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
