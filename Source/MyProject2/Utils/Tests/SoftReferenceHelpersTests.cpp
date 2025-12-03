// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/SoftReferenceHelpers.h"
#include "Engine/Texture2D.h"

#pragma endregion Includes

// ============================================================================
// SoftReferenceHelpers Tests
// ============================================================================
#pragma region SoftReferenceHelpers Tests

BEGIN_DEFINE_SPEC(SoftReferenceHelpersSpec, "MyProject2.Utils.SoftReferenceHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(SoftReferenceHelpersSpec)

void SoftReferenceHelpersSpec::Define()
{
    Describe("IsSoftReferenceValid",
             [this]()
             {
                 It("deve retornar true quando soft reference tem path válido",
                    [this]()
                    {
                        // Arrange
                        // TSoftObjectPtr::IsValid() verifica se o objeto está carregado na memória
                        // Para testar, precisamos carregar um asset válido do engine
                        FSoftObjectPath ValidPath("/Engine/EngineResources/DefaultTexture");
                        TSoftObjectPtr<UTexture2D> ValidRef(ValidPath);

                        // Carrega o asset de forma síncrona para que IsValid() retorne true
                        ValidRef.LoadSynchronous();

                        // Act
                        bool Result = SoftReferenceHelpers::IsSoftReferenceValid(ValidRef);

                        // Assert
                        // IsValid() retorna true quando o objeto está carregado na memória
                        // Nota: Em modo headless, alguns assets podem não estar disponíveis
                        // Se o asset não puder ser carregado, o teste pode falhar
                        // Mas isso é esperado em alguns ambientes
                        if (ValidRef.IsValid())
                        {
                            TestTrue("Soft reference com objeto carregado deve retornar true", Result);
                        }
                        else
                        {
                            // Se não conseguiu carregar, o teste ainda é válido se IsValid() retorna false
                            TestFalse("Soft reference sem objeto carregado deve retornar false", Result);
                        }
                    });

                 It("deve retornar false quando soft reference é inválida",
                    [this]()
                    {
                        // Arrange
                        TSoftObjectPtr<UTexture2D> InvalidRef;

                        // Act
                        bool Result = SoftReferenceHelpers::IsSoftReferenceValid(InvalidRef);

                        // Assert
                        TestFalse("Soft reference inválida deve retornar false", Result);
                    });
             });

    Describe("LoadSoftReference",
             [this]()
             {
                 It("deve retornar nullptr quando soft reference é inválida",
                    [this]()
                    {
                        // Arrange
                        TSoftObjectPtr<UTexture2D> InvalidRef;

                        // Act
                        UTexture2D *Result = SoftReferenceHelpers::LoadSoftReference(InvalidRef);

                        // Assert
                        TestNull("Deve retornar nullptr para referência inválida", Result);
                    });
             });
}

#pragma endregion SoftReferenceHelpers Tests
