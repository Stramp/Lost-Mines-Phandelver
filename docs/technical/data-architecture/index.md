# Data Architecture - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Esta seção contém documentação sobre **arquitetura de dados, organização de tabelas, banco de dados e estruturas de dados** para projetos de alta complexidade e escala.

</details>

---

## 📚 Documentos Principais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔬 Relatórios de Pesquisa</b></summary>

> **[high-performance-architectures-report.md](high-performance-architectures-report.md)** - Relatório completo sobre arquiteturas de alta performance:
>
> - Data-Oriented Design (DOD) vs OOP
> - Entity Component Systems (ECS)
> - Arquitetura de dados em Baldur's Gate 3 (Larian Studios)
> - Persistência e serialização de estado complexo
> - Arquiteturas de dados em escala planetária (Facebook TAO, Twitter/X)
> - Engenharia de banco de dados para atributos dinâmicos
> - Infraestrutura física e otimização de hardware
> - Governança, analytics e evolução de schema

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Estrutura de Dados Ideal</b></summary>

> **[ideal-data-structure-report.md](ideal-data-structure-report.md)** - Relatório completo sobre estrutura de dados ideal:
>
> - Análise completa dos JSONs existentes
> - Problemas críticos identificados
> - Estrutura ideal baseada em ECS + Data-Oriented Design
> - Tabelas de referência (Master Data)
> - Tabelas principais com IDs únicos
> - Padrão de nomenclatura de IDs
> - Checklist de migração completo
> - Comparação antes vs depois
> - Benefícios e prioridades de implementação

</details>

---

## 🎯 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Rápidos</b></summary>

> - **[Relatório de Arquiteturas de Alta Performance](high-performance-architectures-report.md)** - Pesquisa completa sobre sistemas de dados complexos
> - **[Estrutura de Dados Ideal](ideal-data-structure-report.md)** - Análise e recomendações para o projeto
> - **[Arquitetura Técnica](../architecture.md)** - Arquitetura completa do projeto
> - **[API Reference](../api.md)** - Referência de classes
> - **[Guias Práticos](../guides/)** - Guias passo a passo
> - **[Índice de Documentação Técnica](../index.md)** - Organização completa

</details>

---

## 📖 Resumo dos Conceitos Principais

### 🎯 Filosofia Fundamental: Composição sobre Herança

Para estruturas de dados perfeitas em Unreal Engine 5, siga:

- **Composição sobre Herança**: Use composição de componentes ao invés de árvores de herança complexas
- **Separação Static/Dynamic**: Definições em Data Tables (o que o item "é"), estado em componentes runtime (o que o item "tem" agora)
- **Padrão "ID + Tags + Payload"**: Identificador único + metadados + dados específicos
- **Estrutura "Flat"**: JSONs planos e relacionais, não profundamente aninhados

### Data-Oriented Design (DOD)

Organização de dados focada no layout físico na memória, priorizando cache hits e performance sobre modelagem orientada a objetos.

**Princípios:**
- **Array of Structures (AoS)** → **Structure of Arrays (SoA)**: Cada campo em seu próprio array contíguo
- **Cache-Friendly**: Dados organizados para maximizar cache hits da CPU
- **SIMD-Friendly**: Estrutura que permite processamento paralelo com instruções SIMD

### Entity Component System (ECS)

Padrão arquitetural que desacopla identidade (Entity), dados (Component) e lógica (System), permitindo composição dinâmica e escalabilidade.

**Estratégias de Armazenamento:**
- **Arquétipos (Archetypes)**: Agrupa entidades com mesma combinação de componentes - ideal para dados estáticos
- **Sparse Sets**: Arrays esparsos para flexibilidade dinâmica - ideal para estados efêmeros (buffs/debuffs)

### Normalização de Dados

Eliminação de redundância através de tabelas de referência (Master Data) e uso consistente de IDs únicos para todas as entidades.

### Serialização Binária

Uso de formatos binários (FlatBuffers, Protobuf) ao invés de JSON para persistência, reduzindo I/O e tamanho de arquivos.

**Serialização Diferencial**: Salvar apenas o "delta" (mudanças) em relação ao estado base, não o estado completo.

### Estrutura de Dados Ideal

- **Tabelas de Referência (Master Data):** Traits, Languages, Skills, Spells, etc.
- **Tabelas Principais:** Races, Classes, Backgrounds, etc.
- **IDs Únicos:** Padrão consistente de nomenclatura (ex: `TR_Darkvision`, `ABL_Strength`)
- **Referências por ID:** Nunca por string/Name
- **Estrutura "Flat"**: JSONs relacionais planos, não aninhados profundamente

---

## 🎓 Aplicação no Projeto

Os relatórios desta seção fornecem a base teórica e prática para:

1. **Organização de Data Tables** - Estrutura normalizada e escalável
2. **Performance** - Otimizações baseadas em Data-Oriented Design
3. **Escalabilidade** - Preparação para projetos AAA (estilo Baldur's Gate 3)
4. **Manutenção** - Estrutura que facilita evolução e mudanças
5. **Integridade** - Validação automática de referências

---

**Última atualização:** Baseado em análise completa dos JSONs existentes e pesquisa sobre arquiteturas de alta performance.
