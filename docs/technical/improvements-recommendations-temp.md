# Recomendações de Melhorias - Arquitetura de Dados

> **Arquivo Temporário:** Este documento contém todas as recomendações de melhorias identificadas na revisão completa do projeto.
>
> **Data:** 2024-12-XX
> **Status:** Em implementação

---

## 📋 Resumo Executivo

Este documento lista todas as melhorias sugeridas para a arquitetura de dados do projeto, baseadas em:
- `planos5.md` - Arquitetura ideal de banco de dados
- `architecture.md` - Princípios arquiteturais do projeto
- `database-architecture.md` - Arquitetura de banco de dados normalizada
- Revisão completa dos JSONs e estruturas C++

---

## 🎯 Melhorias Identificadas

### 🔴 Alta Prioridade

#### 1. Serialização Diferencial para Save Games

**Problema:**
- `CharacterDataComponent` não implementa serialização diferencial (salva apenas delta)
- Save games podem ficar grandes salvando dados completos ao invés de apenas mudanças

**Solução:**
- Criar structs de runtime instance leves para save games
- Salvar apenas IDs de referência e estado mutável (HP atual, escolhas do jogador)
- Não salvar definições completas (vêm de Data Tables)

**Arquivos a Criar:**
- `Source/MyProject2/Characters/Data/RuntimeInstanceData.h`
- `Source/MyProject2/Characters/Data/RuntimeInstanceData.cpp`

**Benefícios:**
- Save games menores (apenas delta)
- Carregamento mais rápido
- Alinhado com planos5.md (serialização diferencial)

---

#### 2. Remover Duplicação: ClassDataTable_flat.json

**Problema:**
- `ClassDataTable_flat.json` parece duplicado de `ClassDataTable.json`
- Pode causar confusão sobre qual arquivo usar

**Solução:**
- Verificar se são idênticos
- Se sim, remover `ClassDataTable_flat.json`
- Se diferentes, documentar a diferença

**Arquivos a Modificar:**
- `Content/Data/JSON/ClassDataTable_flat.json` (remover se duplicado)

---

#### 3. Validação de Integridade Referencial

**Problema:**
- Não há validação automática de referências quebradas entre Data Tables
- Pode causar crashes em runtime se referências forem inválidas

**Solução:**
- Criar validator para verificar integridade referencial
- Validar todas as referências FDataTableRowHandle
- Verificar se todos os IDs referenciados existem
- Detectar referências circulares problemáticas

**Arquivos a Criar:**
- `Source/MyProject2/Utils/DataTableIntegrityValidator.h`
- `Source/MyProject2/Utils/DataTableIntegrityValidator.cpp`
- `Source/MyProject2/Utils/Tests/DataTableIntegrityValidatorTests.cpp` (TDD)

**Benefícios:**
- Detecção precoce de problemas
- Validação no editor antes de runtime
- Alinhado com planos5.md (Fase 4: Validação e Integridade)

---

### 🟡 Média Prioridade

#### 4. Cache de Lookup para Performance

**Problema:**
- Resolução de `FDataTableRowHandle` pode ser custosa em loops
- Lookups repetidos da mesma referência são ineficientes

**Solução:**
- Implementar cache de lookup (conforme planos5.md)
- Cachear resoluções frequentes para evitar lookups repetidos
- Limpar cache quando necessário (ex: reload de Data Tables)

**Arquivos a Criar:**
- `Source/MyProject2/Utils/DataTableCache.h`
- `Source/MyProject2/Utils/DataTableCache.cpp`
- `Source/MyProject2/Utils/Tests/DataTableCacheTests.cpp` (TDD)

**Benefícios:**
- Performance melhorada em loops
- Redução de overhead de lookup
- Alinhado com planos5.md (cache de lookups)

---

#### 5. Documentação de Padrões JSON

**Problema:**
- Falta documentação sobre formato esperado dos JSONs
- Designers podem não saber como estruturar dados corretamente

**Solução:**
- Criar documentação completa de schema JSON
- Documentar estrutura obrigatória (Name, ID, TypeTags)
- Documentar padrões de referências (FDataTableRowHandle)
- Documentar padrão de Payload (TMap<FName, FString>)

**Arquivos a Criar:**
- `docs/technical/data-architecture/json-schema.md`

**Benefícios:**
- Onboarding mais fácil para designers
- Consistência na estrutura de dados
- Redução de erros

---

#### 6. Separação Definition vs Instance para Skills

**Problema:**
- `FMulticlassSkills` mistura dados de definição (InitialAvailable) com runtime (Selected)
- Pode causar confusão sobre o que é master data vs instance data

**Solução:**
- Separar claramente em duas structs:
  - `FMulticlassSkillsDefinition` - dados de definição (master data)
  - `FMulticlassSkillsInstance` - dados de instância (runtime)

**Arquivos a Modificar:**
- `Source/MyProject2/Data/Structures/MulticlassTypes.h`

**Benefícios:**
- Separação clara de responsabilidades
- Facilita serialização diferencial
- Alinhado com arquitetura (Separação Static/Dynamic)

---

### 🟢 Baixa Prioridade

#### 7. Otimização: Structure of Arrays (SoA) para Performance Crítica

**Problema:**
- Arrays de structs completas podem ser ineficientes em loops grandes
- Para 1000+ NPCs, pode ser necessário otimização

**Solução:**
- Considerar SoA apenas para hotspots críticos
- Manter AoS atual para casos normais
- Implementar apenas se houver necessidade comprovada

**Nota:** Aplicar apenas se houver necessidade comprovada de performance (ex: 1000+ NPCs simultâneos).

---

#### 8. Melhorar Estrutura de Armas/Armaduras (Payload)

**Problema:**
- `ItemDataTable.json` mistura armas, armaduras e itens genéricos
- Falta estrutura para stats de combate

**Solução:**
- Usar Payload estruturado em `ItemData` (TMap<FName, FString>)
- Documentar estrutura esperada para cada tipo de item
- Facilitar extensão sem alterar struct

**Arquivos a Modificar:**
- `Content/Data/JSON/ItemDataTable.json` (melhorar exemplos)
- `docs/technical/data-architecture/json-schema.md` (documentar)

**Benefícios:**
- Payload estruturado facilita extensão
- Alinhado com padrão "ID + Tags + Payload"
- Facilita migração futura para GAS

---

## 📊 Checklist de Implementação

### Alta Prioridade

- [ ] 1. Serialização Diferencial para Save Games
  - [ ] Criar `RuntimeInstanceData.h`
  - [ ] Criar `RuntimeInstanceData.cpp`
  - [ ] Implementar structs de instância leves
  - [ ] Testes TDD

- [ ] 2. Remover Duplicação: ClassDataTable_flat.json
  - [ ] Verificar se são idênticos
  - [ ] Remover se duplicado
  - [ ] Documentar se diferentes

- [ ] 3. Validação de Integridade Referencial
  - [ ] Criar `DataTableIntegrityValidator.h`
  - [ ] Criar `DataTableIntegrityValidator.cpp`
  - [ ] Testes TDD
  - [ ] Integrar validação no editor

### Média Prioridade

- [ ] 4. Cache de Lookup para Performance
  - [ ] Criar `DataTableCache.h`
  - [ ] Criar `DataTableCache.cpp`
  - [ ] Testes TDD

- [ ] 5. Documentação de Padrões JSON
  - [ ] Criar `json-schema.md`
  - [ ] Documentar estrutura obrigatória
  - [ ] Documentar padrões de referências
  - [ ] Documentar padrão de Payload

- [ ] 6. Separação Definition vs Instance para Skills
  - [ ] Modificar `MulticlassTypes.h`
  - [ ] Separar em duas structs
  - [ ] Atualizar código que usa

### Baixa Prioridade

- [ ] 7. Otimização: SoA (apenas se necessário)
  - [ ] Profiling para identificar necessidade
  - [ ] Implementar apenas se comprovado necessário

- [ ] 8. Melhorar Estrutura de Armas/Armaduras
  - [ ] Melhorar exemplos em `ItemDataTable.json`
  - [ ] Documentar em `json-schema.md`

---

## 📚 Referências

- `memorias/planos5.md` - Arquitetura ideal de banco de dados
- `docs/technical/architecture.md` - Princípios arquiteturais
- `docs/technical/data-architecture/database-architecture.md` - Arquitetura de banco de dados normalizada
- `.cursor/rules/test-driven-development.mdc` - TDD obrigatório
- `.cursor/rules/clean-code-mandatory.mdc` - Clean Code obrigatório

---

## ✅ Status de Implementação

**Data de Início:** 2024-12-XX
**Status Atual:** Em implementação

**Progresso:**
- [ ] Alta Prioridade: 0/3 (0%)
- [ ] Média Prioridade: 0/3 (0%)
- [ ] Baixa Prioridade: 0/2 (0%)
- [ ] **Total:** 0/8 (0%)
