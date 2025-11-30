# Princípio: Multiplayer-Ready

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 🌐 Preparação para Multiplayer

**Conceito:** Sistema preparado para multiplayer desde o início, não precisa refatorar depois.

**Benefícios:**

- ✅ Não precisa refatorar depois
- ✅ Lógica autoritária correta desde o início
- ✅ Sincronização automática
- ✅ Escalável para servidor dedicado

**Implementação:**

- **SEMPRE** use `DOREPLIFETIME` para propriedades replicáveis
- **SEMPRE** valide RPCs com `WithValidation`
- **SEMPRE** execute lógica autoritária no servidor
- **SEMPRE** use `GetLocalRole()` para verificar autoridade
- **NUNCA** confie em dados do cliente sem validação

**Exemplo:**

```cpp
// ✅ CORRETO - Replicação
void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMyCharacter, CharacterData);
}

// ✅ CORRETO - RPC com validação
UFUNCTION(Server, Reliable, WithValidation)
void ServerTakeDamage(float DamageAmount);

bool ServerTakeDamage_Validate(float DamageAmount)
{
    return DamageAmount >= 0.0f && DamageAmount <= 1000.0f;
}

void ServerTakeDamage_Implementation(float DamageAmount)
{
    // Lógica autoritária apenas no servidor
    if (GetLocalRole() == ROLE_Authority)
    {
        Health -= DamageAmount;
    }
}
```

---

**Navegação:** [← Editor-Friendly](editor-friendly.md) | [→ Separation of Concerns](separation-of-concerns.md)

**Última atualização:** 2024-12-27
