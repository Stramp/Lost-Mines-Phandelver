# Ciclo 4.2: Personagem Controlável MVP

**Fase:** 1 - Começo  
**Categoria:** 4. Vertical Slice - Cragmaw Hideout  
**Status:** ⏳ Pendente  
**Prioridade:** 🔴 Crítica
**Milestone:** Fase 1: Começo
**Label:** Sys: Character, P0: Critical

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> **Objetivo:** Criar personagem controlável com movimento e animações básicas.
>
> **Critério de Sucesso:** Personagem se move com WASD, rotaciona com mouse e tem animações básicas.
>
> **Tempo Estimado:** 6-8 horas (soma das micro-tarefas: 7h)
>
> **WIP:** Máximo 1-2 tarefas simultâneas
>
> **Dependências:** 
> - Ciclo 1.7 (Sistema de Input MVP)
> - Ciclo 1.9 (Sistema de Física MVP)
> - Ciclo 4.1 (Mapa Básico MVP)

>___
</details>

---

## 🎯 MVP: Personagem Controlável Funcional

### Micro-Tarefas

- [ ] **4.2.1** Criar Character Blueprint base (2h)
  - Criar Character Blueprint
  - Configurar mesh básico
  - Adicionar componentes necessários
  - Verificar Blueprint

- [ ] **4.2.2** Configurar movimento WASD (1h)
  - Integrar com Input System
  - Configurar CharacterMovementComponent
  - Testar movimento
  - Verificar movimento

- [ ] **4.2.3** Implementar rotação (Mouse) (1h)
  - Integrar rotação com mouse
  - Configurar sensibilidade
  - Testar rotação
  - Verificar rotação

- [ ] **4.2.4** Adicionar animação básica (idle, walk) (2h)
  - Criar animações básicas
  - Configurar Animation Blueprint
  - Integrar animações
  - Testar animações

- [ ] **4.2.5** Testar controle (1h)
  - Testar movimento completo
  - Testar rotação
  - Testar animações
  - Verificar que tudo funciona

---

## ✅ Definition of Done

**Ciclo não está "pronto" até que:**

- [ ] Código implementado e testado
- [ ] Personagem controlável funcional
- [ ] Documentação GDD/TDD atualizada (se aplicável)
- [ ] CHANGELOG.md atualizado (se mudança significativa)

**Documentação Correspondente:**

Este ciclo atualiza:
- [GDD: Controles e Inputs](01-GDD/02-mecanicas/controles-inputs) - Mapeamento de controles
- [TDD: Input System](02-TDD/05-guias/setup) - Sistema de input
- [GDD: UI/UX](01-GDD/07-ui-ux) - Feedback visual (se aplicável)

**Ação:** Atualizar documentos acima ao completar este ciclo.

---

## 📝 Modelo Objeto-Ação-Reação (Alinhado com Compêndio)

**Movimento WASD - Descrição Técnica:**

- **Objeto:** Personagem (PlayerCharacter) com CharacterMovementComponent
- **Estado Inicial:** Personagem em posição inicial, movimento desabilitado
- **Ação do Jogador:** Pressionar tecla W/A/S/D (ou setas direcionais)
- **Reação do Sistema:**
  1. Ler input do InputAction "Move"
  2. Calcular direção do movimento baseado na rotação da câmera
  3. Aplicar força ao CharacterMovementComponent
  4. Atualizar animação: `IF Velocity > 0 THEN PlayAnimation("Walk") ELSE PlayAnimation("Idle")`
  5. Atualizar posição do personagem no mundo

**Rotação com Mouse - Descrição Técnica:**

- **Objeto:** Câmera (CameraComponent) e Personagem (PlayerCharacter)
- **Estado Inicial:** Câmera fixa, personagem com rotação inicial
- **Ação do Jogador:** Mover mouse horizontalmente (DeltaX)
- **Reação do Sistema:**
  1. Ler DeltaX do mouse
  2. Calcular rotação: `RotationYaw += DeltaX * MouseSensitivity`
  3. Aplicar rotação ao Personagem: `SetActorRotation(RotationYaw)`
  4. Rotacionar câmera junto com personagem (ou manter câmera fixa, dependendo do estilo)

---

## ✅ Critério de Sucesso

**Ciclo completo quando:**

- [ ] Character Blueprint criado
- [ ] Movimento WASD funciona
- [ ] Rotação com mouse funciona
- [ ] Animações básicas funcionam
- [ ] Testes passam

**Validação:** Personagem deve se mover suavemente, rotacionar com mouse e ter animações básicas funcionando.

---

## 🔄 Expansões Futuras

Após MVP funcionar:

- **Expansão 1:** Adicionar mais animações (correr, atacar, morrer)
- **Expansão 2:** Adicionar sistema de estados (idle, walk, run, combat)
- **Expansão 3:** Adicionar feedback visual de movimento (partículas, poeira)
- **Expansão 4:** Adicionar sons de passos

---

## 🔄 Próximos Ciclos

Após completar este ciclo:

- **Ciclo 4.3:** Sistema de Combate Básico MVP
- **Ciclo 4.4:** Inimigo Goblin MVP

---

**Última atualização:** 2024-12-27

