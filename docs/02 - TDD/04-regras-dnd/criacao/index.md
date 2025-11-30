# 4.1. Algoritmos de Criação de Personagem

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da seção de algoritmos de criação |

---

## 📊 Fluxo de Criação de Personagem

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Diagrama de Fluxo</b></summary>

> ```mermaid
> graph TD
>     Start([Início: Criar Personagem]) --> Step1[1. Escolher Raça]
>     Step1 --> Step2[2. Escolher Classe]
>     Step2 --> Step3[3. Alocar Ability Scores<br/>Point Buy]
>     Step3 --> ValidatePB{Point Buy<br/>Válido?}
>     ValidatePB -->|Não| Step3
>     ValidatePB -->|Sim| Step4[4. Descrever Personagem]
>     Step4 --> Step5[5. Escolher Equipamento]
>     Step5 --> Multiclass{Multiclass?}
>     Multiclass -->|Sim| ValidateMC{Pré-requisitos<br/>OK?}
>     ValidateMC -->|Não| Step2
>     ValidateMC -->|Sim| Step6[6. Aplicar Multiclass]
>     Multiclass -->|Não| Step7[7. Calcular Atributos Finais]
>     Step6 --> Step7
>     Step7 --> End([Personagem Criado])
>
>     style Start fill:#c8e6c9
>     style End fill:#c8e6c9
>     style ValidatePB fill:#fff3e0
>     style ValidateMC fill:#fff3e0
>     style Step3 fill:#e3f2fd
>     style Step6 fill:#f3e5f5
> ```
>
> **📖 [Ver algoritmo completo](character-creation-algorithm.md)**

</details>

---

## 📖 Algoritmos Disponíveis

- **[Character Creation Algorithm](character-creation-algorithm.md)** - Algoritmo completo passo a passo
- **[Point Buy Algorithm](point-buy-algorithm.md)** - Validação e cálculo de Point Buy
- **[Multiclass Algorithm](multiclass-algorithm.md)** - Validação e aplicação de multiclassing

---

**Navegação:** [← Voltar](../index.md) | [→ Próxima Seção: Combate](../combate/index.md)

**Última atualização:** 2024-12-27
