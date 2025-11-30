# 1. Arquitetura Técnica

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏗️ Arquitetura</b></summary>

> Esta seção contém a documentação completa da arquitetura técnica do projeto: princípios, sistemas e camadas.

</details>

---

## 📋 Índice da Documentação de Arquitetura

### 1. [Princípios de Design](principios/index.md)

Os 5 princípios fundamentais que guiam a arquitetura:

- **[Data-Driven](principios/data-driven.md)** - Todas as regras vêm de Data Tables/Assets
- **[Modularidade](principios/modularidade.md)** - Código organizado por domínio
- **[Editor-Friendly](principios/editor-friendly.md)** - Sistema funciona no editor
- **[Multiplayer-Ready](principios/multiplayer-ready.md)** - Preparado para multiplayer
- **[Separation of Concerns](principios/separation-of-concerns.md)** - Separação de responsabilidades

### 2. [Arquitetura em Camadas](camadas/index.md)

Arquitetura em 4 camadas distintas:

- **[Camada 1: Data Assets](camadas/layer-1-data-assets.md)** - Editor/Configuração
- **[Camada 2: Bridge Components](camadas/layer-2-bridge-components.md)** - Aplicação de Regras
- **[Camada 3: Runtime Data Components](camadas/layer-3-runtime-data.md)** - Dados Replicáveis
- **[Camada 4: Feature Components](camadas/layer-4-feature-components.md)** - Lógica Específica

### 3. [Fluxo de Dados](fluxo-dados.md)

Diagrama de fluxo de dados entre Editor, Servidor e Cliente.

### 4. [Arquitetura CreateSheet/](createsheet.md)

Motores desacoplados para criação de personagem.

### 5. [Data-Oriented Design e ECS](data-oriented-design.md)

Princípios de performance e arquitetura.

### 6. [Preparação para GAS](gas-preparation.md)

Arquitetura GAS - Preparação e Padrões.

### 7. [Regras de Implementação](regras-implementacao.md)

Guia de regras e padrões.

### 8. [Checklist de Arquitetura](checklist.md)

Checklist antes de criar novo código.

### 9. [Estrutura de Arquivos Recomendada](estrutura-arquivos.md)

Organização de diretórios e arquivos.

### 10. [Sistema de Logging](logging.md)

Sistema centralizado de logging.

### 11. [Referências](referencias.md)

Documentação do projeto e links externos.

### 12. [Sistemas](sistemas/index.md)

- **[Adaptação D&D 5e para GAS](sistemas/gas-dnd-adaptation/index.md)** - Adaptação completa de regras D&D 5e para Gameplay Ability System

---

**Navegação Principal:** [← Voltar ao Dashboard](dashboard-template.md) | [→ Próxima Seção: API](../02-api/index.md)

---

**Última atualização:** 2024-12-27
