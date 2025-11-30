# Regras de Implementação

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 📋 Guia de Regras e Padrões

### Ao Criar Novos Componentes

1. ✅ **SEMPRE** defina responsabilidade única
2. ✅ **SEMPRE** use `UPROPERTY()` apropriado (EditAnywhere, Replicated, etc.)
3. ✅ **SEMPRE** implemente `GetLifetimeReplicatedProps()` se tiver dados replicáveis
4. ✅ **SEMPRE** valide dados no editor quando possível
5. ❌ **NUNCA** misture lógica de diferentes camadas

### Ao Criar Data Assets

1. ✅ **SEMPRE** herde de `UDataAsset`
2. ✅ **SEMPRE** use `UPROPERTY(EditDefaultsOnly)`
3. ❌ **NUNCA** adicione lógica, apenas dados
4. ✅ **SEMPRE** valide dados no editor

### Ao Criar Features

1. ✅ **SEMPRE** crie componente separado para cada feature
2. ✅ **SEMPRE** use interfaces para comunicação
3. ✅ **SEMPRE** prepare para migração futura para GAS
4. ❌ **NUNCA** acople features diretamente

### Ao Implementar Multiplayer

1. ✅ **SEMPRE** use `DOREPLIFETIME` para propriedades replicáveis
2. ✅ **SEMPRE** valide RPCs com `WithValidation`
3. ✅ **SEMPRE** execute lógica autoritária no servidor
4. ✅ **SEMPRE** use `GetLocalRole() == ROLE_Authority` para verificar autoridade
5. ❌ **NUNCA** confie em dados do cliente sem validação

---

**Navegação:** [← GAS Preparation](gas-preparation.md) | [→ Checklist](checklist.md)

**Última atualização:** 2024-12-27
