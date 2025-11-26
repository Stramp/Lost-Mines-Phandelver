# Troubleshooting

Guia de problemas comuns e suas soluções no sistema de fichas D&D 5e.

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚠️ Problemas no Editor</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Editor crash ao selecionar raça</summary>
>
> > **Sintomas:**
> > - Editor fecha inesperadamente ao selecionar uma raça no dropdown
> > - Erro de acesso de memória (`EXCEPTION_ACCESS_VIOLATION`)
> >
> > **Causa:**
> > - `PropertyHandlers` não estava inicializado quando o objeto era carregado do disco
> > - Uso de `std::function` com lambdas capturando `this` causava problemas de lifetime
> >
> > **Solução:**
> > - Implementado `PostLoad()` para inicializar `PropertyHandlers` quando objeto é carregado
> > - Substituído `std::function` por ponteiros de função estáticos (mais seguro)
> > - Adicionada verificação `PropertyHandlers.Num() == 0` antes de usar
> >
> > **Status:** ✅ Resolvido
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Categorias não aparecem no editor</summary>
>
> > **Sintomas:**
> > - Categorias da ficha (Basic Info, Race & Background, etc.) não aparecem
> > - Apenas categoria "Data Tables" está visível
> >
> > **Causa:**
> > - Nem todos os Data Tables foram atribuídos
> > - Sistema oculta categorias até que todos os Data Tables estejam configurados
> >
> > **Solução:**
> > 1. Atribua todos os Data Tables no `CharacterSheetDataAsset`:
> >    - Race Data Table
> >    - Class Data Table
> >    - Background Data Table
> >    - Feat Data Table
> > 2. Após atribuir todos, as categorias aparecerão automaticamente
> >
> > **Prevenção:**
> > - Sempre atribua todos os Data Tables antes de preencher a ficha
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Variant Human category não aparece/desaparece</summary>
>
> > **Sintomas:**
> > - Categoria "Variant Human" não aparece quando seleciona "Variant Human"
> > - Categoria não desaparece quando muda para outra raça
> >
> > **Causa:**
> > - `bIsVariantHuman` não estava sendo atualizado corretamente
> > - Editor não estava sendo notificado sobre mudanças na flag
> >
> > **Solução:**
> > - Implementado `UpdateVariantHumanFlag()` que verifica `SelectedSubrace == "Variant Human"`
> > - Adicionado `Modify()` e `PostEditChangeProperty()` para notificar editor
> > - Adicionado `EditConditionHides` nas propriedades de Variant Human
> >
> > **Status:** ✅ Resolvido
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Dropdowns vazios</summary>
>
> > **Sintomas:**
> > - Dropdowns de raça, classe, background estão vazios
> > - Não aparecem opções para selecionar
> >
> > **Causa:**
> > - Data Tables não foram atribuídos
> > - Data Tables estão vazios (sem dados)
> > - JSON não foi importado corretamente
> >
> > **Solução:**
> > 1. Verifique se Data Tables foram atribuídos no `CharacterSheetDataAsset`
> > 2. Verifique se Data Tables contêm dados:
> >    - Abra o Data Table no editor
> >    - Verifique se há linhas (rows)
> > 3. Se Data Table estiver vazio:
> >    - Importe JSON válido
> >    - Ou adicione linhas manualmente
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Problemas de Validação</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Validação falhando</summary>
>
> > **Sintomas:**
> > - `ValidateDataIntegrity()` retorna `false`
> > - Logs mostram erros de validação
> >
> > **Causas comuns:**
> >
> > <details>
> > <summary style="background-color: #c8c8c8; padding: 2px 4px; border-radius: 2px;">1. Ability Scores incompletos</summary>
> >
> > > **Erro:**
> > > ```
> > > CharacterDataComponent: Ability Score 'Strength' está faltando!
> > > ```
> > >
> > > **Solução:**
> > > - Verifique se todos os 6 atributos estão presentes:
> > >   - Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
> > > - Verifique se `CharacterSheetComponent::InitializeFromDataAsset()` foi chamado
> >
> > </details>
> >
> > <details>
> > <summary style="background-color: #c8c8c8; padding: 2px 4px; border-radius: 2px;">2. Raça não selecionada</summary>
> >
> > > **Erro:**
> > > ```
> > > CharacterDataComponent: Raça não foi selecionada!
> > > ```
> > >
> > > **Solução:**
> > > - Selecione uma raça no `CharacterSheetDataAsset`
> > > - Verifique se `SelectedRace != NAME_None`
> >
> > </details>
> >
> > <details>
> > <summary style="background-color: #c8c8c8; padding: 2px 4px; border-radius: 2px;">3. Background não selecionado</summary>
> >
> > > **Erro:**
> > > ```
> > > CharacterDataComponent: Background não foi selecionado!
> > > ```
> > >
> > > **Solução:**
> > > - Selecione um background no `CharacterSheetDataAsset`
> > > - Verifique se `SelectedBackground != NAME_None`
> >
> > </details>
> >
> > <details>
> > <summary style="background-color: #c8c8c8; padding: 2px 4px; border-radius: 2px;">4. Nível total inválido</summary>
> >
> > > **Erro:**
> > > ```
> > > CharacterDataComponent: Nível total inválido: 25 (deve ser 1-20)
> > > ```
> > >
> > > **Solução:**
> > > - Verifique se soma dos níveis de classes não excede 20
> > > - Sistema valida automaticamente, mas pode falhar se dados foram modificados manualmente
> >
> > </details>
> >
> > <details>
> > <summary style="background-color: #c8c8c8; padding: 2px 4px; border-radius: 2px;">5. Ability Score fora de range</summary>
> >
> > > **Erro:**
> > > ```
> > > CharacterDataComponent: Ability Score 'Strength' tem valor inválido: 35 (deve ser 1-30)
> > > ```
> > >
> > > **Solução:**
> > > - Verifique se ability scores estão entre 1 e 30
> > > - Em D&D 5e, scores acima de 30 são impossíveis sem magia
> >
> > </details>
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Point Buy validation falhando</summary>
>
> > **Sintomas:**
> > - `PointsRemaining` mostra valor negativo
> > - Sistema não permite ajustar ability scores
> >
> > **Causa:**
> > - Mais de 27 pontos foram gastos
> > - Ability scores estão fora do range 8-15
> >
> > **Solução:**
> > 1. Verifique cada ability score:
> >    - Deve estar entre 8 e 15
> >    - Custo: 8-13 = 1 ponto cada, 14 = 2 pontos, 15 = 3 pontos
> > 2. Ajuste scores para usar exatamente 27 pontos
> > 3. Sistema valida automaticamente, mas pode ser necessário resetar
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Variant Human validation falhando</summary>
>
> > **Sintomas:**
> > - Erro ao selecionar Variant Human
> > - Escolhas de Variant Human não são salvas
> >
> > **Causas:**
> >
> > <details>
> > <summary style="background-color: #c8c8c8; padding: 2px 4px; border-radius: 2px;">1. Menos de 2 atributos escolhidos</summary>
> >
> > > **Solução:**
> > > - Selecione exatamente 2 atributos em `CustomAbilityScoreChoices`
> > > - Sistema valida automaticamente
> >
> > </details>
> >
> > <details>
> > <summary style="background-color: #c8c8c8; padding: 2px 4px; border-radius: 2px;">2. Feat não disponível</summary>
> >
> > > **Solução:**
> > > - Verifique se feat não tem pré-requisitos de nível
> > > - Apenas feats sem pré-requisitos aparecem no nível 1
> > > - Verifique se `FeatDataTable` está atribuído
> >
> > </details>
> >
> > <details>
> > <summary style="background-color: #c8c8c8; padding: 2px 4px; border-radius: 2px;">3. Skill inválida</summary>
> >
> > > **Solução:**
> > > - Verifique se skill está na lista válida de skills
> > > - Lista atual: Acrobatics, Animal Handling, Arcana, Athletics, Deception, History, Insight, Intimidation, Investigation, Medicine, Nature, Perception, Performance, Persuasion, Religion, Sleight of Hand, Stealth, Survival
> >
> > </details>
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌐 Problemas de Replicação</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Dados não replicando em multiplayer</summary>
>
> > **Sintomas:**
> > - Dados do personagem não aparecem no cliente
> > - Ability scores, raça, background não sincronizam
> >
> > **Causa:**
> > - `GetLifetimeReplicatedProps()` não implementado corretamente
> > - Propriedades não têm `DOREPLIFETIME`
> > - Lógica executando no cliente ao invés do servidor
> >
> > **Solução:**
> > 1. Verifique `GetLifetimeReplicatedProps()`:
> > ```cpp
> > void UCharacterDataComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
> > {
> >     Super::GetLifetimeReplicatedProps(OutLifetimeProps);
> >     DOREPLIFETIME(UCharacterDataComponent, CharacterName);
> >     DOREPLIFETIME(UCharacterDataComponent, AbilityScores);
> >     // ... outras propriedades
> > }
> > ```
> >
> > 2. Verifique se propriedades têm `Replicated`:
> > ```cpp
> > UPROPERTY(Replicated, BlueprintReadOnly)
> > FName SelectedRace;
> > ```
> >
> > 3. Verifique autoridade:
> > ```cpp
> > if (GetLocalRole() == ROLE_Authority)
> > {
> >     // Lógica autoritária apenas no servidor
> > }
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Dados replicando mas não atualizando</summary>
>
> > **Sintomas:**
> > - Dados aparecem no cliente, mas não atualizam quando mudam
> > - Mudanças no servidor não refletem no cliente
> >
> > **Causa:**
> > - Falta `ReplicatedUsing` para callbacks
> > - `OnRep_*` functions não implementadas
> >
> > **Solução:**
> > 1. Adicione `ReplicatedUsing`:
> > ```cpp
> > UPROPERTY(Replicated, ReplicatedUsing = OnRep_Health)
> > float Health;
> >
> > UFUNCTION()
> > void OnRep_Health();
> > ```
> >
> > 2. Implemente callback:
> > ```cpp
> > void UCharacterDataComponent::OnRep_Health()
> > {
> >     // Atualizar UI, lógica, etc.
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔨 Problemas de Compilação</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Erro: "Non-type template argument is not a constant expression"</summary>
>
> > **Sintomas:**
> > - Erro de compilação em `ensureMsgf()` ou macros similares
> > - Erro ao usar `GetOwner()->GetName()` em macros
> >
> > **Causa:**
> > - Macros de assert não aceitam expressões complexas
> > - `GetOwner()` pode retornar nullptr
> >
> > **Solução:**
> > - Use guard clauses ao invés de macros:
> > ```cpp
> > // ❌ ERRADO
> > ensureMsgf(GetOwner(), TEXT("Owner is null: %s"), *GetOwner()->GetName());
> >
> > // ✅ CORRETO
> > AActor* Owner = GetOwner();
> > if (!Owner)
> > {
> >     UE_LOG(LogTemp, Error, TEXT("Owner is null"));
> >     return;
> > }
> > FString OwnerName = Owner->GetName();
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Erro: "UProperties should not be wrapped by WITH_EDITOR"</summary>
>
> > **Sintomas:**
> > - Warning sobre `UPROPERTY` dentro de `#if WITH_EDITOR`
> >
> > **Causa:**
> > - `UPROPERTY` não pode estar dentro de `WITH_EDITOR`
> > - Deve usar `WITH_EDITORONLY_DATA` para propriedades editor-only
> >
> > **Solução:**
> > ```cpp
> > // ❌ ERRADO
> > #if WITH_EDITOR
> > UPROPERTY()
> > bool bIsVariantHuman;
> > #endif
> >
> > // ✅ CORRETO
> > #if WITH_EDITORONLY_DATA
> > UPROPERTY()
> > bool bIsVariantHuman;
> > #endif
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Erro: "#include found after .generated.h file"</summary>
>
> > **Sintomas:**
> > - Erro de compilação sobre ordem de includes
> >
> > **Causa:**
> > - Includes devem vir antes de `.generated.h`
> > - `.generated.h` deve ser o último include
> >
> > **Solução:**
> > ```cpp
> > // ✅ CORRETO
> > #include "CoreMinimal.h"
> > #include <functional>  // Antes de .generated.h
> > #include "CharacterSheetDataAsset.generated.h"
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Problemas de Performance</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Editor lento ao modificar propriedades</summary>
>
> > **Sintomas:**
> > - Editor fica lento ao modificar ability scores ou outras propriedades
> > - Lag ao digitar valores
> >
> > **Causa:**
> > - `PostEditChangeProperty()` executando validações pesadas a cada mudança
> > - Múltiplas chamadas recursivas
> >
> > **Solução:**
> > - Sistema já implementa `bIsValidatingProperties` para evitar recursão
> > - Se problema persistir, verifique se handlers não estão fazendo operações pesadas
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 Como Reportar Problemas</b></summary>

> Se encontrar um problema não listado aqui:
>
> 1. **Verifique logs:**
>    - Output Log no editor
>    - Logs de compilação
>
> 2. **Colete informações:**
>    - Versão do Unreal Engine
>    - Plataforma (Windows, etc.)
>    - Passos para reproduzir
>    - Screenshots (se aplicável)
>
> 3. **Abra issue no GitHub:**
>    - Use template de bug report
>    - Inclua todas as informações coletadas

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛡️ Prevenção</b></summary>

> Para evitar problemas:
>
> 1. **Sempre valide dados:**
>    - Use `ValidateDataIntegrity()` antes de usar dados
>    - Verifique nullptr antes de acessar objetos
>
> 2. **Siga arquitetura:**
>    - Use Data Tables ao invés de hardcode
>    - Mantenha separação de responsabilidades
>
> 3. **Teste no editor:**
>    - Sempre teste mudanças no editor
>    - Verifique logs para warnings/erros
>
> 4. **Compile antes de commitar:**
>    - Sempre compile antes de fazer commit
>    - Resolva warnings antes de commitar

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Recursos Adicionais</b></summary>

> Para mais ajuda, consulte:
>
> - [getting-started.md](getting-started.md) - Guia de início
> - [API.md](../API.md) - Referência da API
> - [ARCHITECTURE.md](../../ARCHITECTURE.md) - Arquitetura do projeto

</details>
