# Scripts GitHub

Scripts PowerShell para gerenciar issues, milestones, labels e projetos no GitHub.

## Scripts Disponíveis

### `criar-projeto-github.ps1`

Script principal para criar/atualizar issues do GitHub a partir dos arquivos Markdown na pasta `ciclos/`.

**Funcionalidades:**
- Cria ou atualiza issues automaticamente (idempotente)
- Cria milestones e labels se não existirem
- Classifica issues em 3 projetos diferentes:
  - **Core Engineering** (Sistemas e Código)
  - **Narrative & Quest Design** (História e Missões)
  - **Art & World Building** (Visual e Mapas)
- Cria relacionamentos entre issues (dependências)
- Mapeia labels para formato padronizado
- Adiciona issues aos projetos corretos

**Uso:**
```powershell
cd "F:\UNREAL GAME\MyProject2\scripts\github"
powershell -ExecutionPolicy Bypass -File "criar-projeto-github.ps1"
```

### `teste-single-task.ps1`

Script de teste para processar uma única task antes de rodar o script completo.

**Uso:**
```powershell
cd "F:\UNREAL GAME\MyProject2\scripts\github"
powershell -ExecutionPolicy Bypass -File "teste-single-task.ps1"
```

**Nota:** Por padrão, testa a task `02-04-skill-datatable`. Para testar outra, edite a última linha do script.

### `deletar-todas-issues.ps1`

Script para deletar **TODAS** as issues do repositório permanentemente.

**⚠️ ATENÇÃO: Operação irreversível!**

**Uso:**
```powershell
cd "F:\UNREAL GAME\MyProject2\scripts\github"
powershell -ExecutionPolicy Bypass -File "deletar-todas-issues.ps1"
```

**Funcionalidades:**
- Lista todas as issues (abertas e fechadas)
- Deleta uma por uma com barra de progresso
- Mostra estatísticas ao final

## Estrutura de Pastas

```
F:\UNREAL GAME\
├── MyProject2/
│   └── scripts/
│       └── github/          ← Scripts estão aqui
│           ├── criar-projeto-github.ps1
│           ├── teste-single-task.ps1
│           ├── deletar-todas-issues.ps1
│           └── README.md
└── minasphandelver/
    └── Documentacao/
        └── 04-Planning/
            └── ciclos/      ← Arquivos .md das tasks estão aqui
                ├── fase-1/
                ├── fase-2/
                └── fase-3/
```

## Requisitos

- **GitHub CLI** (`gh`) instalado e autenticado
- **PowerShell** 5.1 ou superior
- Acesso ao repositório `Stramp/Lost-Mines-Phandelver`

## Configuração

Os scripts usam caminhos relativos para encontrar a pasta `ciclos/` na documentação do wiki (`minasphandelver/Documentacao/04-Planning/ciclos/`). Os caminhos são calculados automaticamente a partir da localização do script em `MyProject2/scripts/github/`.
