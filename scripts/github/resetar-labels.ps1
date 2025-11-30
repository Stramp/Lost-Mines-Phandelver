# --- SCRIPT: Resetar Labels do GitHub ---
# Deleta todas as labels e cria as corretas com cores padronizadas
# Encoding UTF-8 para evitar problemas com caracteres especiais
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8

$meuRepo = "Stramp/Lost-Mines-Phandelver"
$ghPath = "C:\Program Files\GitHub CLI\gh.exe"

Write-Host "=== RESETANDO LABELS DO GITHUB ===" -ForegroundColor Cyan
Write-Host "Repositório: $meuRepo" -ForegroundColor Gray
Write-Host ""

# ===== FUNÇÃO: Obter cor do label =====
function Get-LabelColor {
    param([string]$labelName)

    $labelLower = $labelName.ToLower()

    # Prioridades P0-P3
    if ($labelLower -match "^p0:") { return "B60205" }
    if ($labelLower -match "^p1:") { return "D93F0B" }
    if ($labelLower -match "^p2:") { return "FBCA04" }
    if ($labelLower -match "^p3:") { return "0E8A16" }

    # Status
    if ($labelLower -match "^status:") {
        if ($labelLower -match "blocked") { return "000000" }
        return "FBCA04"
    }

    # Type
    if ($labelLower -match "^type:") {
        if ($labelLower -match "bug") { return "EE0701" }
        if ($labelLower -match "feature") { return "1D76DB" }
        return "1D76DB"
    }

    # Sys: (Sistemas)
    if ($labelLower -match "^sys:") {
        if ($labelLower -match "combat") { return "5319E7" }
        if ($labelLower -match "ai") { return "0052CC" }
        if ($labelLower -match "ui|ux") { return "C5DEF5" }
        if ($labelLower -match "save|load|persistencia") { return "BFD4F2" }
        if ($labelLower -match "character|personagem") { return "5319E7" }
        if ($labelLower -match "inventario|inventory") { return "0052CC" }
        return "5319E7"
    }

    # Quest: (Missões)
    if ($labelLower -match "^quest:") {
        if ($labelLower -match "main") { return "E11D21" }
        if ($labelLower -match "side") { return "F9D0C4" }
        return "E11D21"
    }

    # Writ: (Escrita)
    if ($labelLower -match "^writ:") {
        if ($labelLower -match "dialog") { return "D4C5F9" }
        if ($labelLower -match "scripting") { return "672688" }
        return "D4C5F9"
    }

    # Act: (Atos)
    if ($labelLower -match "^act:") {
        if ($labelLower -match "1") { return "C2E0C6" }
        if ($labelLower -match "2") { return "BFDADC" }
        if ($labelLower -match "3") { return "C2E0C6" }
        return "C2E0C6"
    }

    # Art: (Arte)
    if ($labelLower -match "^art:") {
        if ($labelLower -match "concept") { return "6A737D" }
        if ($labelLower -match "environment") { return "0E8A16" }
        if ($labelLower -match "character") { return "74C468" }
        if ($labelLower -match "animation") { return "94E09B" }
        if ($labelLower -match "vfx") { return "FFC25F" }
        return "0E8A16"
    }

    # Stage: (Estágios)
    if ($labelLower -match "^stage:") {
        if ($labelLower -match "blockout") { return "FEF2C0" }
        if ($labelLower -match "final") { return "006B75" }
        return "FEF2C0"
    }

    # Default
    return "0E8A16"
}

# ===== LABELS PADRONIZADAS DO PROJETO =====
$labelsPadronizadas = @(
    # Prioridades
    @{ Name = "P0: Critical"; Description = "Urgência máxima. Bloqueia o desenvolvimento." },
    @{ Name = "P1: High"; Description = "Alta prioridade. Necessário para a próxima build." },
    @{ Name = "P2: Medium"; Description = "Prioridade normal." },
    @{ Name = "P3: Low"; Description = "Baixa prioridade. Fazer se sobrar tempo." },

    # Status
    @{ Name = "Status: Blocked"; Description = "Tarefa impedida de avançar por dependência externa." },

    # Type
    @{ Name = "Type: Bug"; Description = "Erro de código ou comportamento inesperado." },
    @{ Name = "Type: Feature"; Description = "Nova funcionalidade ou mecânica." },

    # Sys: (Sistemas)
    @{ Name = "Sys: Combat"; Description = "Sistemas de dano, magias, turnos e armas." },
    @{ Name = "Sys: AI"; Description = "Comportamento de inimigos e NPCs." },
    @{ Name = "Sys: UI/UX"; Description = "Interfaces, menus e HUD." },
    @{ Name = "Sys: Save/Load"; Description = "Persistência de dados." },
    @{ Name = "Sys: Character"; Description = "Sistema de criação e gerenciamento de personagens." },
    @{ Name = "Sys: Inventory"; Description = "Sistema de inventário e itens." },

    # Quest: (Missões)
    @{ Name = "Quest: Main"; Description = "Caminho crítico da história principal." },
    @{ Name = "Quest: Side"; Description = "Conteúdo opcional e missões secundárias." },

    # Writ: (Escrita)
    @{ Name = "Writ: Dialog"; Description = "Escrita de falas, lore e textos." },
    @{ Name = "Writ: Scripting"; Description = "Lógica da quest (Blueprints/Triggers)." },

    # Act: (Atos)
    @{ Name = "Act: 1"; Description = "Conteúdo referente ao Ato 1." },
    @{ Name = "Act: 2"; Description = "Conteúdo referente ao Ato 2." },
    @{ Name = "Act: 3"; Description = "Conteúdo referente ao Ato 3." },

    # Art: (Arte)
    @{ Name = "Art: Concept"; Description = "Arte conceitual e referências." },
    @{ Name = "Art: Environment"; Description = "Cenários, props e vegetação." },
    @{ Name = "Art: Character"; Description = "Modelagem de personagens e monstros." },
    @{ Name = "Art: Animation"; Description = "Rigging e clips de animação." },
    @{ Name = "Art: VFX"; Description = "Efeitos visuais, partículas e shaders." },

    # Stage: (Estágios)
    @{ Name = "Stage: Blockout"; Description = "Fase de protótipo (Whitebox)." },
    @{ Name = "Stage: Final"; Description = "Asset finalizado e pronto para o jogo." }
)

# ===== PASSO 1: DELETAR TODAS AS LABELS =====
Write-Host "--- PASSO 1: DELETANDO LABELS EXISTENTES ---" -ForegroundColor Yellow
Write-Host ""

$labelsJson = & $ghPath api repos/$meuRepo/labels 2>&1

if ($LASTEXITCODE -eq 0 -and $labelsJson) {
    try {
        $labels = $labelsJson | ConvertFrom-Json -ErrorAction SilentlyContinue

        if (-not ($labels -is [array])) {
            if ($labels) {
                $labels = @($labels)
            } else {
                $labels = @()
            }
        }

        if ($labels.Count -gt 0) {
            Write-Host "Encontradas $($labels.Count) labels para deletar..." -ForegroundColor Gray
            $deletadas = 0
            $falhas = 0

            foreach ($label in $labels) {
                Write-Host "  Deletando: $($label.name)..." -NoNewline
                $result = & $ghPath api repos/$meuRepo/labels/$($label.name) --method DELETE 2>&1

                if ($LASTEXITCODE -eq 0) {
                    Write-Host " [OK]" -ForegroundColor Green
                    $deletadas++
                } else {
                    Write-Host " [ERRO]" -ForegroundColor Red
                    Write-Host "    Detalhe: $result" -ForegroundColor Yellow
                    $falhas++
                }
            }

            Write-Host ""
            Write-Host "Deletadas: $deletadas | Falhas: $falhas" -ForegroundColor $(if ($falhas -eq 0) { "Green" } else { "Yellow" })
        } else {
            Write-Host "Nenhuma label encontrada para deletar." -ForegroundColor Gray
        }
    } catch {
        Write-Host "ERRO ao processar labels para deleção: $_" -ForegroundColor Red
    }
} else {
    Write-Host "ERRO ao buscar labels: $labelsJson" -ForegroundColor Red
}

Write-Host ""
Write-Host "--- PASSO 2: CRIANDO LABELS PADRONIZADAS ---" -ForegroundColor Yellow
Write-Host ""

# ===== PASSO 2: CRIAR LABELS PADRONIZADAS =====
$criadas = 0
$falhas = 0

foreach ($labelInfo in $labelsPadronizadas) {
    $labelName = $labelInfo.Name
    $labelDescription = $labelInfo.Description
    $labelColor = Get-LabelColor -labelName $labelName

    Write-Host "  Criando/Atualizando: $labelName..." -NoNewline
    Write-Host " (cor: #$labelColor)" -ForegroundColor DarkGray -NoNewline

    # Verifica se label já existe
    $labelNameEncoded = [System.Web.HttpUtility]::UrlEncode($labelName)
    $checkResult = & $ghPath api repos/$meuRepo/labels/$labelNameEncoded 2>&1
    $labelExists = ($LASTEXITCODE -eq 0)

    if ($labelExists) {
        # Label existe, atualiza
        $result = & $ghPath api repos/$meuRepo/labels/$labelNameEncoded --method PATCH `
            --raw-field "color=$labelColor" `
            --raw-field "description=$labelDescription" 2>&1

        if ($LASTEXITCODE -eq 0) {
            Write-Host " [ATUALIZADA]" -ForegroundColor Yellow
            $criadas++
        } else {
            Write-Host " [ERRO ao atualizar]" -ForegroundColor Red
            Write-Host "    Detalhe: $result" -ForegroundColor Yellow
            $falhas++
        }
    } else {
        # Label não existe, cria
        $result = & $ghPath api repos/$meuRepo/labels --method POST `
            --raw-field "name=$labelName" `
            --raw-field "color=$labelColor" `
            --raw-field "description=$labelDescription" 2>&1

        if ($LASTEXITCODE -eq 0) {
            Write-Host " [CRIADA]" -ForegroundColor Green
            $criadas++
        } elseif ($result -match "already_exists") {
            # Se deu "already_exists" mesmo verificando antes, tenta atualizar
            $updateResult = & $ghPath api repos/$meuRepo/labels/$labelNameEncoded --method PATCH `
                --raw-field "color=$labelColor" `
                --raw-field "description=$labelDescription" 2>&1

            if ($LASTEXITCODE -eq 0) {
                Write-Host " [ATUALIZADA]" -ForegroundColor Yellow
                $criadas++
            } else {
                Write-Host " [ERRO ao atualizar]" -ForegroundColor Red
                Write-Host "    Detalhe: $updateResult" -ForegroundColor Yellow
                $falhas++
            }
        } else {
            Write-Host " [ERRO ao criar]" -ForegroundColor Red
            Write-Host "    Detalhe: $result" -ForegroundColor Yellow
            $falhas++
        }
    }
}

Write-Host ""
Write-Host "=== RESULTADO ===" -ForegroundColor Cyan
Write-Host "Labels criadas: $criadas" -ForegroundColor Green
Write-Host "Falhas: $falhas" -ForegroundColor $(if ($falhas -eq 0) { "Gray" } else { "Red" })
Write-Host "Total esperado: $($labelsPadronizadas.Count)" -ForegroundColor Gray

Write-Host ""
Write-Host "=== CONCLUÍDO ===" -ForegroundColor Cyan
