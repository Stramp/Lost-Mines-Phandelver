# 🎯 Filosofia Fundamental: Composição sobre Herança

Para iniciar uma "estrutura perfeita" no Unreal Engine 5 (UE5) para um jogo complexo como Baldur's Gate 3, você deve seguir o princípio da **Composição sobre Herança** e a **Separação entre Definição (Static) e Estado (Dynamic)**.

## ⚠️ O Erro Mais Comum

O erro mais comum é tentar criar uma única Struct gigante com todos os campos possíveis (Dano, Cura, Armadura, Texto de Lore, etc.). Isso cria dados "sujos" e pesados.

## ✅ A Arquitetura Ideal

Abaixo apresento a arquitetura de dados ideal. Você terá:

- **Tabelas de Definição (Static)**: O que o item "é" - dados imutáveis armazenados em Data Tables
- **Estruturas de Instância (Dynamic)**: O que o item "tem" agora - dados mutáveis em runtime

## 📋 O Padrão "Name + ID + Tags + Payload"

No Unreal Engine, JSON é apenas o meio de transporte. A estrutura real na engine deve usar:

- **Data Tables** para dados estáticos (definições)
- **Structs leves** para dados dinâmicos (estado em runtime)

**Filosofia:**
- **Name**: Nome de exibição (Key Field do Unreal Engine) - usado como chave primária na Data Table
- **ID**: Identificador único interno (ex: `RACE_Elf`, `CLASS_Fighter`, `ITM_Longsword`)
- **Tags**: Metadados e categorização via Gameplay Tags (ex: `TypeTags: ["Race.Elf", "Race.Fey"]`)
- **Payload**: Dados específicos do item (ex: `TraitData`, `FeatureData`, `TraitHandles`, `LanguageHandles`)

## 📐 Estrutura JSON "Flat" (Plana)

Ao invés de um JSON profundo e aninhado (que o importador do Unreal odeia e quebra frequentemente), use uma estrutura relacional **"flat" (plana)**.

**Exemplo:** `DT_MasterItemDatabase.json` - Esta é a tabela mestra. Ela não contém stats de combate, apenas identidade e visual.

---

## 🔗 Navegação

- [📚 Relatório - Índice](./index.md)
- [📊 Análise dos JSONs Existentes](./analise-jsons-existentes.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de ideal-data-structure-report.md |
