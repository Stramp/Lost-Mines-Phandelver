// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetValidators.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetValidationResult.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Utils/DnDConstants.h"
#include "Utils/CharacterSheetHelpers.h"

#pragma endregion Includes

// ============================================================================
// CharacterSheetDataAssetValidators Tests
// ============================================================================
#pragma region CharacterSheetDataAssetValidators Tests

BEGIN_DEFINE_SPEC(CharacterSheetDataAssetValidatorsSpec, "MyProject2.Characters.Data.Validators",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(CharacterSheetDataAssetValidatorsSpec)

void CharacterSheetDataAssetValidatorsSpec::Define()
{
    Describe("ValidateVariantHumanAbilityScoreChoices",
             [this]()
             {
                 It("deve detectar quando CustomAbilityScoreChoices excede máximo de 2 itens",
                    [this]()
                    {
                        AddInfo(TEXT("Testando validação: Variant Human não pode ter mais de 2 itens em CustomAbilityScoreChoices"));

                        // Arrange
                        UCharacterSheetDataAsset *Asset = NewObject<UCharacterSheetDataAsset>();
                        Asset->SelectedSubrace = TEXT("Variant Human");
                        Asset->SetIsVariantHuman(true);

                        // Configurar array com 3 itens (excede máximo de 2)
                        TArray<FName> AbilityScoreNames = CharacterSheetHelpers::GetAbilityScoreNames();
                        if (AbilityScoreNames.Num() >= 3)
                        {
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[0]); // STR
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[1]); // DEX
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[2]); // CON (excede máximo)

                            // Act
                            FValidationResult Result = FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(Asset);

                            // Assert
                            TestTrue("Validação deve detectar que excede máximo", Result.bNeedsCorrection);
                            TestTrue("Deve ter pelo menos uma correção", Result.Corrections.Num() > 0);

                            // Verifica se há correção do tipo ClearArray (ajusta para máximo de 2)
                            bool bHasClearArrayCorrection = false;
                            for (const FValidationCorrection &Correction : Result.Corrections)
                            {
                                if (Correction.CorrectionType == EValidationCorrectionType::ClearArray)
                                {
                                    bHasClearArrayCorrection = true;
                                    TestEqual("Correção deve ajustar para máximo de 2 itens", Correction.NewValue, 2);
                                    break;
                                }
                            }
                            TestTrue("Deve ter correção ClearArray para ajustar array", bHasClearArrayCorrection);

                            AddInfo(TEXT("✅ Teste passou: validação detecta exceder máximo de 2 itens"));
                        }
                        else
                        {
                            AddInfo(TEXT("⚠️ Teste pulado: não há ability scores suficientes para testar"));
                        }
                    });

                 It("deve aceitar exatamente 2 itens em CustomAbilityScoreChoices",
                    [this]()
                    {
                        AddInfo(TEXT("Testando validação: Variant Human pode ter exatamente 2 itens em CustomAbilityScoreChoices"));

                        // Arrange
                        UCharacterSheetDataAsset *Asset = NewObject<UCharacterSheetDataAsset>();
                        Asset->SelectedSubrace = TEXT("Variant Human");
                        Asset->SetIsVariantHuman(true);

                        // Configurar array com exatamente 2 itens (dentro do limite)
                        TArray<FName> AbilityScoreNames = CharacterSheetHelpers::GetAbilityScoreNames();
                        if (AbilityScoreNames.Num() >= 2)
                        {
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[0]); // STR
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[1]); // DEX

                            // Act
                            FValidationResult Result = FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(Asset);

                            // Assert
                            TestFalse("Validação deve aceitar 2 itens válidos", Result.bNeedsCorrection);
                            TestEqual("Não deve ter correções", Result.Corrections.Num(), 0);

                            AddInfo(TEXT("✅ Teste passou: validação aceita exatamente 2 itens"));
                        }
                        else
                        {
                            AddInfo(TEXT("⚠️ Teste pulado: não há ability scores suficientes para testar"));
                        }
                    });

                 It("deve aceitar menos de 2 itens em CustomAbilityScoreChoices",
                    [this]()
                    {
                        AddInfo(TEXT("Testando validação: Variant Human pode ter menos de 2 itens em CustomAbilityScoreChoices"));

                        // Arrange
                        UCharacterSheetDataAsset *Asset = NewObject<UCharacterSheetDataAsset>();
                        Asset->SelectedSubrace = TEXT("Variant Human");
                        Asset->SetIsVariantHuman(true);

                        // Configurar array com 1 item (dentro do limite)
                        TArray<FName> AbilityScoreNames = CharacterSheetHelpers::GetAbilityScoreNames();
                        if (AbilityScoreNames.Num() >= 1)
                        {
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[0]); // STR

                            // Act
                            FValidationResult Result = FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(Asset);

                            // Assert
                            TestFalse("Validação deve aceitar 1 item", Result.bNeedsCorrection);
                            TestEqual("Não deve ter correções", Result.Corrections.Num(), 0);

                            AddInfo(TEXT("✅ Teste passou: validação aceita menos de 2 itens"));
                        }
                        else
                        {
                            AddInfo(TEXT("⚠️ Teste pulado: não há ability scores suficientes para testar"));
                        }
                    });

                 It("deve aceitar array vazio em CustomAbilityScoreChoices",
                    [this]()
                    {
                        AddInfo(TEXT("Testando validação: Variant Human pode ter array vazio em CustomAbilityScoreChoices"));

                        // Arrange
                        UCharacterSheetDataAsset *Asset = NewObject<UCharacterSheetDataAsset>();
                        Asset->SelectedSubrace = TEXT("Variant Human");
                        Asset->SetIsVariantHuman(true);
                        Asset->CustomAbilityScoreChoices.Empty(); // Array vazio

                        // Act
                        FValidationResult Result = FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(Asset);

                        // Assert
                        TestFalse("Validação deve aceitar array vazio", Result.bNeedsCorrection);
                        TestEqual("Não deve ter correções", Result.Corrections.Num(), 0);

                        AddInfo(TEXT("✅ Teste passou: validação aceita array vazio"));
                    });

                 It("deve detectar duplicatas em CustomAbilityScoreChoices",
                    [this]()
                    {
                        AddInfo(TEXT("Testando validação: Variant Human não pode ter duplicatas em CustomAbilityScoreChoices"));

                        // Arrange
                        UCharacterSheetDataAsset *Asset = NewObject<UCharacterSheetDataAsset>();
                        Asset->SelectedSubrace = TEXT("Variant Human");
                        Asset->SetIsVariantHuman(true);

                        // Configurar array com duplicata (STR aparece duas vezes)
                        TArray<FName> AbilityScoreNames = CharacterSheetHelpers::GetAbilityScoreNames();
                        if (AbilityScoreNames.Num() >= 2)
                        {
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[0]); // STR
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[0]); // STR (duplicata)

                            // Act
                            FValidationResult Result = FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(Asset);

                            // Assert
                            TestTrue("Validação deve detectar duplicata", Result.bNeedsCorrection);
                            TestTrue("Deve ter pelo menos uma correção", Result.Corrections.Num() > 0);

                            AddInfo(TEXT("✅ Teste passou: validação detecta duplicata"));
                        }
                        else
                        {
                            AddInfo(TEXT("⚠️ Teste pulado: não há ability scores suficientes para testar"));
                        }
                    });

                 It("deve detectar elementos inválidos em CustomAbilityScoreChoices",
                    [this]()
                    {
                        AddInfo(TEXT("Testando validação: Variant Human não pode ter elementos inválidos em CustomAbilityScoreChoices"));

                        // Arrange
                        UCharacterSheetDataAsset *Asset = NewObject<UCharacterSheetDataAsset>();
                        Asset->SelectedSubrace = TEXT("Variant Human");
                        Asset->SetIsVariantHuman(true);

                        // Configurar array com elemento inválido
                        TArray<FName> AbilityScoreNames = CharacterSheetHelpers::GetAbilityScoreNames();
                        if (AbilityScoreNames.Num() >= 1)
                        {
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[0]); // STR (válido)
                            Asset->CustomAbilityScoreChoices.Add(TEXT("InvalidAbilityName")); // Nome inválido

                            // Act
                            FValidationResult Result = FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(Asset);

                            // Assert
                            TestTrue("Validação deve detectar elemento inválido", Result.bNeedsCorrection);
                            TestTrue("Deve ter pelo menos uma correção", Result.Corrections.Num() > 0);

                            // Verifica se há correção do tipo RemoveInvalid
                            bool bHasRemoveInvalidCorrection = false;
                            for (const FValidationCorrection &Correction : Result.Corrections)
                            {
                                if (Correction.CorrectionType == EValidationCorrectionType::RemoveInvalid)
                                {
                                    bHasRemoveInvalidCorrection = true;
                                    TestTrue("Correção deve ter índices inválidos", Correction.InvalidIndices.Num() > 0);
                                    break;
                                }
                            }
                            TestTrue("Deve ter correção RemoveInvalid para remover elemento inválido", bHasRemoveInvalidCorrection);

                            AddInfo(TEXT("✅ Teste passou: validação detecta elemento inválido"));
                        }
                        else
                        {
                            AddInfo(TEXT("⚠️ Teste pulado: não há ability scores suficientes para testar"));
                        }
                    });

                 It("deve detectar combinação de problemas (excede máximo + duplicata)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando validação: Variant Human com múltiplos problemas (excede máximo + duplicata)"));

                        // Arrange
                        UCharacterSheetDataAsset *Asset = NewObject<UCharacterSheetDataAsset>();
                        Asset->SelectedSubrace = TEXT("Variant Human");
                        Asset->SetIsVariantHuman(true);

                        // Configurar array com 3 itens (excede máximo) e duplicata
                        TArray<FName> AbilityScoreNames = CharacterSheetHelpers::GetAbilityScoreNames();
                        if (AbilityScoreNames.Num() >= 2)
                        {
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[0]); // STR
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[0]); // STR (duplicata)
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[1]); // DEX (excede máximo)

                            // Act
                            FValidationResult Result = FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(Asset);

                            // Assert
                            TestTrue("Validação deve detectar múltiplos problemas", Result.bNeedsCorrection);
                            TestTrue("Deve ter múltiplas correções", Result.Corrections.Num() > 1);

                            // Verifica se há correção ClearArray (excede máximo)
                            bool bHasClearArrayCorrection = false;
                            bool bHasRemoveInvalidCorrection = false;
                            for (const FValidationCorrection &Correction : Result.Corrections)
                            {
                                if (Correction.CorrectionType == EValidationCorrectionType::ClearArray)
                                {
                                    bHasClearArrayCorrection = true;
                                }
                                if (Correction.CorrectionType == EValidationCorrectionType::RemoveInvalid)
                                {
                                    bHasRemoveInvalidCorrection = true;
                                }
                            }
                            // Nota: Duplicatas não geram correção RemoveInvalid, apenas ClearArray quando excede máximo
                            TestTrue("Deve ter correção ClearArray para exceder máximo", bHasClearArrayCorrection);

                            AddInfo(TEXT("✅ Teste passou: validação detecta múltiplos problemas"));
                        }
                        else
                        {
                            AddInfo(TEXT("⚠️ Teste pulado: não há ability scores suficientes para testar"));
                        }
                    });

                 It("deve ignorar validação quando não é Variant Human",
                    [this]()
                    {
                        AddInfo(TEXT("Testando validação: deve ignorar quando não é Variant Human"));

                        // Arrange
                        UCharacterSheetDataAsset *Asset = NewObject<UCharacterSheetDataAsset>();
                        Asset->SelectedSubrace = TEXT("Human"); // Não é Variant Human
                        Asset->SetIsVariantHuman(false);

                        // Configurar array com 3 itens (seria inválido para Variant Human)
                        TArray<FName> AbilityScoreNames = CharacterSheetHelpers::GetAbilityScoreNames();
                        if (AbilityScoreNames.Num() >= 3)
                        {
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[0]); // STR
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[1]); // DEX
                            Asset->CustomAbilityScoreChoices.Add(AbilityScoreNames[2]); // CON

                            // Act
                            FValidationResult Result = FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(Asset);

                            // Assert
                            // Quando não é Variant Human, a função retorna early (linha 107-110)
                            // Então não deve ter correções
                            TestFalse("Validação deve ignorar quando não é Variant Human", Result.bNeedsCorrection);
                            TestEqual("Não deve ter correções", Result.Corrections.Num(), 0);

                            AddInfo(TEXT("✅ Teste passou: validação ignora quando não é Variant Human"));
                        }
                        else
                        {
                            AddInfo(TEXT("⚠️ Teste pulado: não há ability scores suficientes para testar"));
                        }
                    });

                 It("deve ignorar validação quando Asset é nullptr",
                    [this]()
                    {
                        AddInfo(TEXT("Testando validação: deve retornar resultado vazio quando Asset é nullptr"));

                        // Arrange
                        UCharacterSheetDataAsset *Asset = nullptr;

                        // Act
                        FValidationResult Result = FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(Asset);

                        // Assert
                        TestFalse("Validação deve retornar sem correções quando Asset é nullptr", Result.bNeedsCorrection);
                        TestEqual("Não deve ter correções", Result.Corrections.Num(), 0);

                        AddInfo(TEXT("✅ Teste passou: validação retorna vazio quando Asset é nullptr"));
                    });
             });
}

#pragma endregion CharacterSheetDataAssetValidators Tests
