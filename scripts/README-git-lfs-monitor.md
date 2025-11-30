# Git LFS Usage Monitor

Scripts para monitorar o uso do Git LFS no GitHub com alertas visuais e porcentagens.

## 📋 Requisitos

### Python Script
```bash
pip install requests colorama
pip install win10toast  # Optional: for Windows toast notifications
```

### PowerShell Script
- PowerShell 5.1+ (já incluído no Windows 10+)
- Nenhuma dependência adicional

## 🔧 Configuração

1. **Obter Token do GitHub:**
   - Acesse: https://github.com/settings/tokens
   - Clique em "Generate new token (classic)"
   - Dê um nome (ex: "Git LFS Monitor")
   - Marque a permissão: `read:org` (ou `admin:org` se tiver acesso)
   - Clique em "Generate token"
   - **Copie o token** (você só verá ele uma vez!)

2. **Configurar o Script:**
   - Edite `scripts/git-lfs-config.json`
   - Adicione seu token e username:
   ```json
   {
     "github_token": "seu_token_aqui",
     "github_username": "seu_username"
   }
   ```

## 🚀 Uso

### Python (Multiplataforma)
```bash
python scripts/check-git-lfs-usage.py
```

### PowerShell (Windows)
```powershell
.\scripts\check-git-lfs-usage.ps1
```

## 📊 O que o Script Mostra

- **Storage Usage**: Uso de armazenamento LFS (GB usado / GB limite)
- **Bandwidth Usage**: Uso de bandwidth mensal (GB usado / GB limite)
- **Barras de Progresso**: Visual com cores (verde/amarelo/vermelho)
- **Alertas**: Quando uso > 80% (configurável)
- **Avisos**: Quando uso > 60% (configurável)
- **Recomendações**: Dicas para economizar quando uso > 50%
- **Notificações Windows**: Toast notification automática quando alerta (opcional, requer `win10toast`)

## ⚙️ Personalização

Edite `scripts/git-lfs-config.json` para ajustar:

- `alert_threshold_storage`: Porcentagem para alerta de storage (padrão: 80)
- `alert_threshold_bandwidth`: Porcentagem para alerta de bandwidth (padrão: 80)
- `warning_threshold_storage`: Porcentagem para aviso de storage (padrão: 60)
- `warning_threshold_bandwidth`: Porcentagem para aviso de bandwidth (padrão: 60)
- `free_plan_storage_gb`: Limite de storage do plano (padrão: 1.0 GB)
- `free_plan_bandwidth_gb`: Limite de bandwidth do plano (padrão: 1.0 GB)

## 🔄 Automação

### Windows Task Scheduler
1. Abra "Agendador de Tarefas"
2. Crie nova tarefa
3. Ação: Executar `powershell.exe`
4. Argumentos: `-File "F:\UNREAL GAME\MyProject2\scripts\check-git-lfs-usage.ps1"`
5. Configure para executar diariamente/semanalmente

### Cron (Linux/Mac)
```bash
# Executar diariamente às 9h
0 9 * * * cd /path/to/project && python scripts/check-git-lfs-usage.py
```

## 🔒 Segurança

⚠️ **IMPORTANTE**: O arquivo `git-lfs-config.json` contém seu token do GitHub.

- **NÃO** commite este arquivo no Git!
- Adicione ao `.gitignore`:
  ```
  scripts/git-lfs-config.json
  ```
- Mantenha o token seguro e não compartilhe

## 📝 Exemplo de Saída

```
============================================================
Git LFS Usage Monitor
============================================================

GitHub User: seu_username

Storage Usage:
  Used: 0.45 GB / 1.00 GB
  [████████████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░] 45.0%

Bandwidth Usage (This Month):
  Used: 0.23 GB / 1.00 GB
  [██████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░] 23.0%

============================================================

✓ All usage levels are within safe limits.
```

## 🐛 Troubleshooting

### Erro: "Invalid token"
- Verifique se o token está correto no `git-lfs-config.json`
- Certifique-se que o token tem permissão `read:org`

### Erro: "Token doesn't have billing access"
- O token precisa ter escopo `read:org` ou `admin:org`
- Gere um novo token com essas permissões

### Script não mostra cores (PowerShell)
- Certifique-se que está usando PowerShell (não CMD)
- Cores funcionam melhor no PowerShell 5.1+

## 📚 Referências

- [GitHub API - Billing](https://docs.github.com/en/rest/billing)
- [Git LFS Documentation](https://git-lfs.github.com/)
- [GitHub Personal Access Tokens](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token)
