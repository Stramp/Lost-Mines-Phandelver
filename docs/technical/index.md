# Documentação Técnica - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Visão Geral</b></summary>

> Esta seção contém toda a documentação relacionada à **arquitetura técnica, implementação e desenvolvimento** do projeto.

</details>

---

## 📚 Documentos Principais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏗️ Arquitetura Técnica</b></summary>

> **[architecture.md](architecture.md)** - Documentação completa da arquitetura:
>
> - Princípios de design (Data-Driven, Modularidade, Editor-Friendly, Multiplayer-Ready)
> - Data-Oriented Design e ECS (Composição sobre Herança, Separação Static/Dynamic)
> - Arquitetura em 4 camadas
> - Motores desacoplados (CreateSheet/)
> - Preparação para GAS
> - Regras de implementação
> - Estrutura de arquivos

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 API Reference</b></summary>

> **[api.md](api.md)** - Referência completa da API:
>
> - CharacterDataComponent
> - CharacterSheetComponent
> - CharacterSheetDataAsset
> - CreateSheet - Motores de Criação
> - Helpers e Utilitários

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Arquitetura de Dados</b></summary>

> **[data-architecture/](data-architecture/)** - Documentação sobre organização de dados:
>
> - Relatório de Arquiteturas de Alta Performance (DOD, ECS, Baldur's Gate 3)
> - Estrutura de Dados Ideal para Projetos AAA (Padrão "ID + Tags + Payload")
> - Filosofia: Composição sobre Herança, Separação Static/Dynamic
> - Estrutura "Flat" (JSONs planos e relacionais)
> - Normalização e Tabelas de Referência
> - Serialização e Persistência (Serialização Diferencial, Formatos Binários)
>
> **📖 Para mais detalhes, veja [data-architecture/index.md](data-architecture/index.md)**

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Guias Práticos</b></summary>

> **[guides/](guides/)** - Guias passo a passo:
>
> **Setup e Configuração:**
> - Setup Completo - Configurar ambiente do zero
> - Data Tables Setup - Criar e configurar Data Tables
>
> **Uso:**
> - Getting Started - Criar primeiro personagem
> - Workflows - Fluxos principais do sistema
> - Data Tables - Estrutura e uso
>
> **Técnico:**
> - Testes Automatizados - Implementação e execução de testes
> - TDD Complete Guide - Guia completo de Test-Driven Development
> - Troubleshooting - Problemas comuns
>
> **📖 Para mais detalhes, veja [guides/index.md](guides/index.md)**

</details>

---

## 🎯 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Rápidos</b></summary>

> - **[Arquitetura](architecture.md)** - Arquitetura completa
> - **[API Reference](api.md)** - Referência de classes
> - **[Arquitetura de Dados](data-architecture/)** - Organização de dados e tabelas
> - **[Guias Práticos](guides/)** - Guias passo a passo
> - **[Documentação de Design](../design/)** - Regras D&D 5e e GDD
> - **[README Principal](../../README.md)** - Visão geral do projeto
> - **[ARCHITECTURE.md](../../ARCHITECTURE.md)** - Resumo da arquitetura
> - **[CHANGELOG.md](../../CHANGELOG.md)** - Histórico de mudanças
> - **[Índice de Documentação](../index.md)** - Organização completa

</details>
