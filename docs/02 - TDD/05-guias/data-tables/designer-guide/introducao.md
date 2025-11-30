# 📋 Introdução - Guia para Designers

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Visão Geral</b></summary>

> Este guia é destinado a **designers e game designers** que precisam criar ou editar dados de D&D 5e no projeto. Você não precisa saber programação, apenas entender a estrutura JSON e seguir os exemplos.
>
> **Objetivo:** Permitir que designers modifiquem regras, adicionem novas raças, classes, itens, etc. sem precisar alterar código C++.

</details>

---

## 🎯 O Que São Data Tables?

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Conceito</b></summary>

> **Data Tables** são tabelas de dados que armazenam informações do jogo (raças, classes, itens, magias, etc.) em formato JSON.
>
> **Por que usar Data Tables?**
>
> - ✅ Permite modificar regras sem recompilar código
> - ✅ Facilita balanceamento e iteração rápida
> - ✅ Designers podem trabalhar independentemente de programadores
> - ✅ Dados podem ser versionados e compartilhados facilmente
>
> **Onde ficam os arquivos?**
>
> - Arquivos JSON: `Content/Data/JSON/`
> - Schemas de validação: `Content/Data/JSON/Schemas/`
> - Importados no Unreal Editor como Data Tables

</details>

---

## 📝 Formato JSON Básico

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔤 Estrutura Básica</b></summary>

> **Formato geral:**
>
> ```json
> [
> {
> "Name": "Nome da Entrada",
> "ID": "ID_Unico",
> "Campo1": "Valor1",
> "Campo2": 123,
> "Campo3": ["Item1", "Item2"]
> },
> {
> "Name": "Outra Entrada",
> ...
> }
> ]
> ```
>
> **Regras importantes:**
>
> 1. **Sempre comece com `[` e termine com `]`** (array de objetos)
> 2. **Cada entrada é um objeto dentro de `{}`**
> 3. **Use vírgulas entre campos**, mas **não após o último campo**
> 4. **Strings sempre entre aspas duplas `"`**
> 5. **Números sem aspas**
> 6. **Arrays entre `[]`**
>
> **Exemplo prático:**
>
> ```json
> [
> {
> "Name": "Human",
> "ID": "RACE_Human",
> "Description": "Humans are adaptable."
> },
> {
> "Name": "Elf",
> "ID": "RACE_Elf",
> "Description": "Elves are graceful."
> }
> ]
> ```

</details>

---

## 🔗 Navegação

- [📚 Guia para Designers - Índice](./index.md)
- [🛠️ Ferramentas Recomendadas](./ferramentas.md)
- [📖 Guia Rápido por Data Table](./guia-rapido.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables-designer-guide.md |
