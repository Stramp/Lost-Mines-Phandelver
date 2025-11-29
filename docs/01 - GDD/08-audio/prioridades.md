# 8.3. Prioridades de Áudio

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Prioridades de Áudio</b></summary>

> Ordem de implementação e especificações técnicas.

</details>

---

## Ordem de Implementação

1. **SFX de combate** (crítico para feedback de ações)
2. **Música ambiente por área** (Phandalin, masmorras, etc.)
3. **SFX de interação** (portas, baús, diálogos)
4. **Vozes de NPCs** (opcional inicialmente, pode ser texto apenas)
5. **SFX ambientais** (vento, fogo, água - opcional inicialmente)

## Especificações Técnicas

- **Variação de Pitch:** Para passos e ataques (evitar repetição robótica)
- **Prioridade de Vozes:** Quais sons devem ser cortados se o limite de canais for atingido
- **Spatial Audio:** Sons 3D para imersão (passos, vozes, ambiente)

---

**Navegação:** [← Voltar ao Índice](index.md) | [→ Próxima Seção: Referências](../09-referencias/index.md)
