# Data-Oriented Design e ECS

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 📊 Princípios de Performance e Arquitetura

O projeto segue princípios de **Data-Oriented Design (DOD)** e está preparado para evoluir para um padrão **Entity Component System (ECS)** quando necessário.

**Filosofia Fundamental:**

- **Composição sobre Herança**: Use composição de componentes ao invés de árvores de herança complexas
- **Separação Static/Dynamic**: Definições em Data Tables (o que o item "é"), estado em componentes runtime (o que o item "tem" agora)
- **Padrão "ID + Tags + Payload"**: Identificador único + metadados + dados específicos
- **Estrutura "Flat"**: JSONs planos e relacionais, não profundamente aninhados

**Benefícios:**

- ✅ Performance otimizada (layout de memória eficiente, cache-friendly)
- ✅ Flexibilidade através de composição
- ✅ Escalabilidade para sistemas complexos (estilo Baldur's Gate 3)
- ✅ Facilita migração futura para ECS completo

**Aplicação no Projeto:**

- Data Tables contêm apenas definições estáticas (raça, classe, traits)
- Componentes runtime contêm estado dinâmico (HP atual, buffs ativos, escolhas do jogador)
- Referências por ID, nunca por string/Name
- Estruturas JSON planas e relacionais

**📖 Para detalhes completos sobre DOD, ECS e arquiteturas de alta performance, veja:**

- [Relatório de Arquiteturas de Alta Performance](../../Estudos/high-performance-architectures-report.md)
- [Relatório de Estrutura de Dados Ideal](../../Estudos/ideal-data-structure-report.md)
- [Arquitetura de Carregamento Centralizado (Data Registry)](../../Estudos/data-registry-architecture.md) - Carregamento único e acesso O(1)

---

**Navegação:** [← CreateSheet](createsheet.md) | [→ GAS](gas-preparation.md)

**Última atualização:** 2024-12-27
