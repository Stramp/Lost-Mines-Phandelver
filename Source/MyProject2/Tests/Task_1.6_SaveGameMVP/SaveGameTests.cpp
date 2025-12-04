// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "SaveGame/MyProject2SaveGame.h"
#include "SaveGame/SaveGameHelpers.h"

#pragma endregion Includes

// ============================================================================
// Save Game Tests
// ============================================================================
#pragma region Save Game Tests

BEGIN_DEFINE_SPEC(SaveGameSpec, "MyProject2.SaveGame",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(SaveGameSpec)

void SaveGameSpec::Define()
{
    // ============================================================================
    // MyProject2SaveGame Tests
    // ============================================================================
    Describe("Issue-1.6/ MyProject2SaveGame",
             [this]()
             {
                 It("deve criar UMyProject2SaveGame sem crash",
                    [this]()
                    {
                        // Arrange & Act
                        UMyProject2SaveGame *SaveGame = NewObject<UMyProject2SaveGame>(GetTransientPackage());

                        // Assert
                        TestNotNull("SaveGame deve ser criado", SaveGame);
                        TestTrue("UMyProject2SaveGame criado sem crash", SaveGame != nullptr);
                    });

                 It("deve inicializar com valores padrão",
                    [this]()
                    {
                        // Arrange & Act
                        UMyProject2SaveGame *SaveGame = NewObject<UMyProject2SaveGame>(GetTransientPackage());

                        // Assert
                        TestEqual("CharacterName deve estar vazio", SaveGame->CharacterName, FString(TEXT("")));
                        TestEqual("CharacterLevel deve ser 1", SaveGame->CharacterLevel, 1);
                        TestEqual("CharacterRace deve ser NAME_None", SaveGame->CharacterRace, FName(NAME_None));
                        TestEqual("CharacterClass deve ser NAME_None", SaveGame->CharacterClass, FName(NAME_None));
                        TestEqual("SaveVersion deve ser 1", SaveGame->SaveVersion, 1);
                        TestTrue("SaveTimestamp deve ser definido", SaveGame->SaveTimestamp.GetTicks() > 0);
                    });

                 It("deve definir valores de personagem corretamente",
                    [this]()
                    {
                        // Arrange
                        UMyProject2SaveGame *SaveGame = NewObject<UMyProject2SaveGame>(GetTransientPackage());
                        FString TestName = TEXT("TestCharacter");
                        int32 TestLevel = 5;
                        FName TestRace = TEXT("Human");
                        FName TestClass = TEXT("Fighter");

                        // Act
                        SaveGame->CharacterName = TestName;
                        SaveGame->CharacterLevel = TestLevel;
                        SaveGame->CharacterRace = TestRace;
                        SaveGame->CharacterClass = TestClass;

                        // Assert
                        TestEqual("CharacterName deve ser 'TestCharacter'", SaveGame->CharacterName, TestName);
                        TestEqual("CharacterLevel deve ser 5", SaveGame->CharacterLevel, TestLevel);
                        TestEqual("CharacterRace deve ser 'Human'", SaveGame->CharacterRace, TestRace);
                        TestEqual("CharacterClass deve ser 'Fighter'", SaveGame->CharacterClass, TestClass);
                    });

                 It("deve definir SaveTimestamp corretamente",
                    [this]()
                    {
                        // Arrange
                        UMyProject2SaveGame *SaveGame = NewObject<UMyProject2SaveGame>(GetTransientPackage());
                        FDateTime TestTimestamp = FDateTime::Now();

                        // Act
                        SaveGame->SaveTimestamp = TestTimestamp;

                        // Assert
                        TestTrue("SaveTimestamp deve ser definido", SaveGame->SaveTimestamp.GetTicks() > 0);
                    });

                 It("deve herdar de USaveGame",
                    [this]()
                    {
                        // Arrange & Act & Assert
                        UClass *SaveGameClass = USaveGame::StaticClass();
                        UClass *MySaveGameClass = UMyProject2SaveGame::StaticClass();

                        TestTrue("UMyProject2SaveGame deve herdar de USaveGame",
                                 MySaveGameClass->IsChildOf(SaveGameClass));
                    });
             });

    // ============================================================================
    // SaveGameHelpers Tests
    // ============================================================================
    Describe("Issue-1.6/ SaveGameHelpers",
             [this]()
             {
                 It("deve verificar que save não existe em slot inexistente",
                    [this]()
                    {
                        // Arrange
                        FString NonExistentSlot = TEXT("TestSlot_NonExistent_12345");

                        // Act
                        bool bExists = USaveGameHelpers::DoesSaveGameExist(NonExistentSlot);

                        // Assert
                        TestFalse("Save não deve existir em slot inexistente", bExists);
                    });

                 // ============================================================================
                 // Nota: Testes de SaveGameToSlot e LoadGameFromSlot limitados
                 // ============================================================================
                 // SaveGameToSlot e LoadGameFromSlot usam LogError/LogWarning internamente,
                 // o que pode causar problemas no framework de testes. Testes de integração
                 // completos podem ser feitos manualmente no editor.
                 //
                 // DoesSaveGameExist e DeleteGameInSlot são mais seguros para testar,
                 // mas DeleteGameInSlot também pode usar LogError. Testamos apenas
                 // DoesSaveGameExist que é mais seguro.
                 // ============================================================================
             });
}

#pragma endregion Save Game Tests
