# 🏗️ Estrutura de Testes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📁 Organização de Arquivos</b></summary>

> **Estrutura de diretórios:**
>
> ```
> Source/MyProject2/
> ├── Utils/
> │   ├── ComponentHelpers.h
> │   ├── ComponentHelpers.cpp
> │   └── Tests/
> │       └── ComponentHelpersTests.cpp
> ├── Data/Tables/
> │   ├── FeatDataTable.h
> │   ├── FeatDataTable.cpp
> │   └── Tests/
> │       └── FeatDataTableTests.cpp
> └── Tests/
> └── Integration/
> ├── CharacterCreationE2ETests.cpp
> └── README.md
> ```
>
> **Padrão:**
> - **Testes Unitários:** Cada módulo tem uma pasta `Tests/` com seus arquivos de teste (próximos ao código testado)
> - **Testes de Integração:** Centralizados em `Tests/Integration/` (testam fluxos completos entre múltiplos sistemas)

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](../index.md)
- [🎯 O Que Testar](./o-que-testar.md)
- [💻 Padrões de Teste](./padroes-teste.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
