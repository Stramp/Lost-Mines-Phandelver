# 🧪 Testes de Integração End-to-End

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Diferença: Unit Tests vs Integration Tests</b></summary>

> **Testes Unitários** (em `Utils/Tests/`, `Data/Tables/Tests/`, etc.):
>
> - Testam **funções isoladas**
> - Exemplo: `CalculateAbilityModifier(15)` retorna `+2`
> - Rápidos (< 1 segundo cada)
> - Não dependem de outros sistemas
>
> **Testes de Integração** (em `Tests/Integration/`):
>
> - Testam **fluxos completos** do sistema
> - Exemplo: Criar personagem completo → Validar tudo funcionou
> - Testam interação entre múltiplos componentes
> - Mais lentos (testam sistemas completos)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Testes de Integração Implementados</b></summary>

> **CharacterCreationE2ETests.cpp** - Testa o fluxo completo de criação de personagem:
>
> 1. **Personagem Básico** - Raça, background, ability scores
> 2. **Variant Human Completo** - Feat, skill, custom ability scores
> 3. **Multiclasse Básico** - Múltiplas classes
> 4. **Tratamento de Erros** - DataAsset nullptr
>
> **Executar Testes de Integração:**
>
> ```bash
> # Todos os testes de integração
> run_tests.bat MyProject2.Integration
>
> # Teste específico
> run_tests.bat MyProject2.Integration.CharacterCreation
> ```
>
> **📖 Para mais detalhes, veja [Tests/Integration/README.md](../../../Source/MyProject2/Tests/Integration/README.md)**

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](../index.md)
- [💡 Dicas](../dicas.md)
- [📖 Benefícios](../beneficios.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
