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
                        TSoftObjectPtr<UTexture2D> ValidRef = TSoftObjectPtr<UTexture2D>(FSoftObjectPath("/Engine/EngineResources/DefaultTexture"));

                        // Act
                        bool Result = SoftReferenceHelpers::IsSoftReferenceValid(ValidRef);

                        // Assert
                        // IsValid() verifica se o path é válido (não se o asset existe)
                        // Este teste verifica que a função retorna o resultado correto de IsValid()
                        TestTrue("Soft reference com path válido deve retornar true", Result);
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
                        UTexture2D* Result = SoftReferenceHelpers::LoadSoftReference(InvalidRef);

                        // Assert
                        TestNull("Deve retornar nullptr para referência inválida", Result);
                    });
             });
}

#pragma endregion SoftReferenceHelpers Tests
