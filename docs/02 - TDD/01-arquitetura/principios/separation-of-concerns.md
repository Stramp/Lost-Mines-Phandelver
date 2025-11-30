# Princípio: Separation of Concerns

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 🔧 Separação de Responsabilidades (Component-Based Architecture)

**Conceito:** Cada camada tem responsabilidade única e bem definida.

**Benefícios:**

- ✅ Separação clara entre configuração (Editor) e execução (Runtime)
- ✅ Fácil testar cada camada independentemente
- ✅ Preparado para GAS (dados em Component, lógica em Abilities)
- ✅ Replicação eficiente (apenas dados necessários)

**Arquitetura em 4 Camadas:**

1. **Camada 1: Data Assets** (Editor/Configuração) - Armazena configuração estática
2. **Camada 2: Bridge Components** (Aplicação de Regras) - Ponte entre Data Asset e Runtime
3. **Camada 3: Runtime Data Components** (Dados Replicáveis) - Armazena dados em runtime
4. **Camada 4: Feature Components** (Lógica Específica) - Gerencia features específicas

**📖 Para detalhes completos sobre as camadas, veja [Arquitetura em Camadas](../camadas/index.md)**

---

**Navegação:** [← Multiplayer-Ready](multiplayer-ready.md) | [→ Voltar para Princípios](index.md)

**Última atualização:** 2024-12-27
