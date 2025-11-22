Plano 1: Expansão do ClassDataTable
Objetivo: adicionar campos necessários para subclasses e tipos de features.
Escopo:
Expandir FClassFeature (adicionar FeatureType)
Adicionar SubclassNames em FClassDataRow
Ajustar comentários/documentação
Arquivos:
Source/MyProject2/Data/Tables/ClassDataTable.h
Dependências: nenhuma (estrutura independente)
Risco: baixo (apenas expansão de struct)
Plano 2: Criação do FeatDataTable
Objetivo: criar estrutura completa para feats gerais.
Escopo:
Criar FeatDataTable.h com FFeatDataRow
Estrutura completa (FeatName, Description, Prerequisites, Benefits)
Seguir padrão de RaceDataTable/ClassDataTable
Arquivos:
Source/MyProject2/Data/Tables/FeatDataTable.h (novo)
Dependências: nenhuma (estrutura independente)
Risco: baixo (novo arquivo, sem impacto em código existente)
Plano 3: Helpers para Data Tables
Objetivo: criar funções reutilizáveis para ler e validar Data Tables.
Escopo:
Criar Utils/CharacterSheetHelpers.h/cpp
Funções: leitura de Data Tables, filtragem, validação
Seguir padrão de ComponentHelpers (namespace, funções puras)
Arquivos:
Source/MyProject2/Utils/CharacterSheetHelpers.h (novo)
Source/MyProject2/Utils/CharacterSheetHelpers.cpp (novo)
Dependências:
ClassDataTable expandido (Plano 1)
FeatDataTable criado (Plano 2)
Risco: médio (precisa seguir Clean Code rigorosamente)
Plano 4: Interface do Editor (CharacterSheetDataAsset)
Objetivo: expandir interface do editor com multi-classing, Point Buy, validações.
Escopo:
Criar structs FClassLevelEntry e FAbilityScoreEntry
Expandir CharacterSheetDataAsset com novos campos
Implementar PostEditChangeProperty() com validações
Usar helpers do Plano 3
Arquivos:
Source/MyProject2/Characters/Data/CharacterSheetDataAsset.h
Source/MyProject2/Characters/Data/CharacterSheetDataAsset.cpp
Dependências:
Plano 1 (ClassDataTable expandido)
Plano 3 (Helpers prontos)
Risco: alto (interface complexa, pode violar arquitetura se mal feita)
Ordem de execução recomendada
Plano 1 (ClassDataTable)     ↓Plano 2 (FeatDataTable)    ↓Plano 3 (Helpers) ────┐    ↓                  │Plano 4 (Interface) ←──┘
Por quê:
Estruturas primeiro (Planos 1 e 2): base para tudo
Helpers depois (Plano 3): usa as estruturas
Interface por último (Plano 4): usa helpers e estruturas
Vantagens da divisão
Foco: cada plano tem responsabilidade única
Testabilidade: cada plano pode ser testado isoladamente
Reversibilidade: se um plano falhar, não quebra os outros
Alinhamento: cada plano pode ser revisado contra Clean Code/Arquitetura separadamente
Progresso incremental: pode executar e testar cada plano antes do próximo
Observação sobre JSONs
Os JSONs não precisam de um plano separado porque:
São dados, não código
Podem ser criados manualmente no editor do Unreal
Ou criados em paralelo enquanto os planos de código executam
Se quiser automatizar a criação dos JSONs, pode ser um Plano 5 opcional (scripts/templates).
