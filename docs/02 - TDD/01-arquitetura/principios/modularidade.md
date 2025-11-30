# Princípio: Modularidade

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 🧩 Modularidade

**Conceito:** Código organizado por domínio, cada parte com responsabilidade única e clara. Baseado em **Composição sobre Herança** e **Data-Oriented Design**.

**Benefícios:**

- ✅ Fácil manutenção
- ✅ Fácil expansão
- ✅ Código limpo e organizado
- ✅ Reutilização de componentes
- ✅ Performance otimizada (layout de memória eficiente)
- ✅ Flexibilidade através de composição

**Filosofia:**

- **Composição sobre Herança**: Use composição de componentes ao invés de árvores de herança complexas
- **Separação Static/Dynamic**: Definições em Data Tables (static), estado em componentes runtime (dynamic)
- **Data-Oriented Design**: Organize dados por layout de memória, não por hierarquia de classes

**Estrutura de Diretórios:**

```
Source/MyProject2/
├── Characters/          # Personagens e raças
│   ├── Data/           # Data Assets de personagens
│   └── Components/      # Componentes de personagem
├── Components/          # Componentes reutilizáveis
│   ├── Data/           # Componentes de dados
│   ├── Features/        # Componentes de features
│   └── UI/             # Componentes de UI
├── Data/               # Data Assets e Data Tables
│   ├── Tables/         # Data Tables
│   └── Assets/         # Data Assets
├── Gameplay/           # Mecânicas de jogo
│   ├── Abilities/      # Habilidades
│   └── Systems/        # Sistemas de jogo
└── Utils/              # Utilitários
```

---

**Navegação:** [← Data-Driven](data-driven.md) | [→ Editor-Friendly](editor-friendly.md)

**Última atualização:** 2024-12-27
