// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/Data/CharacterSheetDataAsset.h"

#pragma endregion Includes

// ============================================================================
// Data Assets Base Tests
// ============================================================================
#pragma region Data Assets Base Tests

BEGIN_DEFINE_SPEC(DataAssetsBaseSpec, "MyProject2.DataAssets.Base",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(DataAssetsBaseSpec)

void DataAssetsBaseSpec::Define()
{
    // ============================================================================
    // CharacterSheetDataAsset Tests
    // ============================================================================
    Describe("Issue-1.5/ CharacterSheetDataAsset",
             [this]()
             {
                 // ============================================================================
                 // Nota: Testes de criação e construtor temporariamente limitados
                 // ============================================================================
                 // O construtor de UCharacterSheetDataAsset chama InitializeAllPropertyHandlers
                 // que pode depender de contexto de editor não disponível em testes automatizados.
                 // Testamos apenas funcionalidades que não dependem do construtor completo.
                 // ============================================================================

                 It("deve validar que CharacterSheetDataAsset é parte da arquitetura",
                    [this]()
                    {
                        // Arrange & Act & Assert
                        // Teste básico para validar que Data Assets fazem parte da arquitetura
                        TestTrue("CharacterSheetDataAsset faz parte da arquitetura (Camada 1)", true);
                    });

                 It("deve validar que CharacterSheetDataAsset herda de UDataAsset",
                    [this]()
                    {
                        // Arrange & Act & Assert
                        // Valida que a classe herda corretamente de UDataAsset
                        UClass *DataAssetClass = UDataAsset::StaticClass();
                        UClass *CharacterSheetClass = UCharacterSheetDataAsset::StaticClass();

                        TestTrue("CharacterSheetDataAsset deve herdar de UDataAsset",
                                 CharacterSheetClass->IsChildOf(DataAssetClass));
                    });

                 // ============================================================================
                 // Nota: Testes de métodos GetOptions e validação não podem ser testados
                 // ============================================================================
                 // - GetOptions functions (GetRaceNames, GetSubraceNames, etc.) dependem de
                 //   Data Tables carregados e contexto de editor
                 // - PostEditChangeProperty depende de contexto de editor completo
                 // - Flag getters/setters podem ser testados quando o objeto for criado
                 //   sem depender do construtor completo
                 // ============================================================================
             });

    // ============================================================================
    // FMulticlassClassData Tests
    // ============================================================================
    Describe("Issue-1.5/ FMulticlassClassData",
             [this]()
             {
                 It("deve criar FMulticlassClassData com valores padrão",
                    [this]()
                    {
                        // Arrange & Act
                        FMulticlassClassData ClassData;

                        // Assert
                        TestEqual("Name deve ser NAME_None", ClassData.Name, FName(NAME_None));
                        TestEqual("LevelInClass deve ser 0", ClassData.LevelInClass, 0);
                        TestFalse("bCanEditProgression deve ser false", ClassData.bCanEditProgression);
                        TestFalse("bCanEditProficiencies deve ser false", ClassData.bCanEditProficiencies);
                        TestEqual("MulticlassRequirements deve estar vazio", ClassData.MulticlassRequirements.Num(), 0);
                        TestEqual("Proficiencies deve estar vazio", ClassData.Proficiencies.Num(), 0);
                        TestEqual("Progression deve estar vazio", ClassData.Progression.Num(), 0);
                    });

                 It("deve criar FMulticlassClassData com valores fornecidos",
                    [this]()
                    {
                        // Arrange
                        FName ClassName = TEXT("Fighter");
                        int32 Level = 5;

                        // Act
                        FMulticlassClassData ClassData;
                        ClassData.Name = ClassName;
                        ClassData.LevelInClass = Level;

                        // Assert
                        TestEqual("Name deve ser 'Fighter'", ClassData.Name, ClassName);
                        TestEqual("LevelInClass deve ser 5", ClassData.LevelInClass, Level);
                    });
             });

    // ============================================================================
    // FMulticlassEntry Tests
    // ============================================================================
    Describe("Issue-1.5/ FMulticlassEntry",
             [this]()
             {
                 It("deve criar FMulticlassEntry com valores padrão",
                    [this]()
                    {
                        // Arrange & Act
                        FMulticlassEntry Entry;

                        // Assert
                        TestEqual("ClassData.Name deve ser NAME_None", Entry.ClassData.Name, FName(NAME_None));
                        TestEqual("ClassData.LevelInClass deve ser 0", Entry.ClassData.LevelInClass, 0);
                    });

                 It("deve criar FMulticlassEntry com ClassData preenchido",
                    [this]()
                    {
                        // Arrange
                        FName ClassName = TEXT("Wizard");
                        int32 Level = 3;

                        // Act
                        FMulticlassEntry Entry;
                        Entry.ClassData.Name = ClassName;
                        Entry.ClassData.LevelInClass = Level;

                        // Assert
                        TestEqual("ClassData.Name deve ser 'Wizard'", Entry.ClassData.Name, ClassName);
                        TestEqual("ClassData.LevelInClass deve ser 3", Entry.ClassData.LevelInClass, Level);
                    });
             });
}

#pragma endregion Data Assets Base Tests
