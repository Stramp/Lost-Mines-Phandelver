// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "SaveGame/SaveGameHelpers.h"
#include "SaveGame/MyProject2SaveGame.h"
#include "Kismet/GameplayStatics.h"

#pragma endregion Includes

// ============================================================================
// SaveGameHelpers Tests
// ============================================================================
#pragma region SaveGameHelpers Tests

BEGIN_DEFINE_SPEC(SaveGameHelpersSpec, "MyProject2.SaveGame.SaveGameHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UMyProject2SaveGame *TestSaveGame;
FString TestSlotName;
int32 TestUserIndex;

END_DEFINE_SPEC(SaveGameHelpersSpec)

void SaveGameHelpersSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar SaveGame e configurar slot único para cada teste
            TestSaveGame = NewObject<UMyProject2SaveGame>();
            TestSlotName = FString::Printf(TEXT("TestSlot_%lld"), FDateTime::Now().ToUnixTimestamp());
            TestUserIndex = 0;

            // Limpar qualquer save existente no slot de teste
            USaveGameHelpers::DeleteGameInSlot(TestSlotName, TestUserIndex);
        });

    AfterEach(
        [this]()
        {
            // Cleanup: Deletar save de teste após cada teste
            if (!TestSlotName.IsEmpty())
            {
                USaveGameHelpers::DeleteGameInSlot(TestSlotName, TestUserIndex);
            }

            if (TestSaveGame)
            {
                TestSaveGame = nullptr;
            }
        });

    // ========================================================================
    // SaveGameToSlot Tests
    // ========================================================================
#pragma region SaveGameToSlot Tests

    Describe("SaveGameToSlot",
             [this]()
             {
                 It("deve salvar com sucesso quando SaveGameObject é válido",
                    [this]()
                    {
                        // Arrange
                        TestSaveGame->CharacterName = TEXT("TestCharacter");
                        TestSaveGame->CharacterLevel = 5;
                        TestSaveGame->CharacterRace = FName(TEXT("Human"));
                        TestSaveGame->CharacterClass = FName(TEXT("Fighter"));

                        // Act
                        bool bResult = USaveGameHelpers::SaveGameToSlot(TestSaveGame, TestSlotName, TestUserIndex);

                        // Assert
                        TestTrue("SaveGameToSlot deve retornar true quando SaveGameObject é válido", bResult);
                        TestTrue("Save deve existir após salvar",
                                 USaveGameHelpers::DoesSaveGameExist(TestSlotName, TestUserIndex));
                    });

                 It("deve retornar false quando SaveGameObject é nullptr",
                    [this]()
                    {
                        // Arrange
                        UMyProject2SaveGame *NullSaveGame = nullptr;

                        // Act
                        bool bResult = USaveGameHelpers::SaveGameToSlot(NullSaveGame, TestSlotName, TestUserIndex);

                        // Assert
                        TestFalse("SaveGameToSlot deve retornar false quando SaveGameObject é nullptr", bResult);
                    });

                 It("deve usar DefaultSaveSlotName quando SlotName é vazio",
                    [this]()
                    {
                        // Arrange
                        TestSaveGame->CharacterName = TEXT("TestCharacter");

                        // Act
                        bool bResult = USaveGameHelpers::SaveGameToSlot(TestSaveGame, TEXT(""), TestUserIndex);

                        // Assert
                        TestTrue("SaveGameToSlot deve retornar true", bResult);
                        TestTrue("Save deve existir no slot padrão",
                                 USaveGameHelpers::DoesSaveGameExist(TEXT(""), TestUserIndex));
                    });

                 It("deve usar DefaultUserIndex quando UserIndex é -1",
                    [this]()
                    {
                        // Arrange
                        TestSaveGame->CharacterName = TEXT("TestCharacter");

                        // Act
                        bool bResult = USaveGameHelpers::SaveGameToSlot(TestSaveGame, TestSlotName, -1);

                        // Assert
                        TestTrue("SaveGameToSlot deve retornar true", bResult);
                        TestTrue("Save deve existir no UserIndex padrão",
                                 USaveGameHelpers::DoesSaveGameExist(TestSlotName, -1));
                    });
             });

#pragma endregion SaveGameToSlot Tests

    // ========================================================================
    // LoadGameFromSlot Tests
    // ========================================================================
#pragma region LoadGameFromSlot Tests

    Describe(
        "LoadGameFromSlot",
        [this]()
        {
            It("deve carregar save existente corretamente",
               [this]()
               {
                   // Arrange: Salvar primeiro
                   TestSaveGame->CharacterName = TEXT("LoadedCharacter");
                   TestSaveGame->CharacterLevel = 10;
                   TestSaveGame->CharacterRace = FName(TEXT("Elf"));
                   TestSaveGame->CharacterClass = FName(TEXT("Wizard"));
                   USaveGameHelpers::SaveGameToSlot(TestSaveGame, TestSlotName, TestUserIndex);

                   // Act
                   UMyProject2SaveGame *LoadedSave = USaveGameHelpers::LoadGameFromSlot(TestSlotName, TestUserIndex);

                   // Assert
                   TestNotNull("LoadGameFromSlot deve retornar objeto válido quando save existe", LoadedSave);
                   if (LoadedSave)
                   {
                       TestEqual("CharacterName deve ser preservado", LoadedSave->CharacterName,
                                 TEXT("LoadedCharacter"));
                       TestEqual("CharacterLevel deve ser preservado", LoadedSave->CharacterLevel, 10);
                       TestEqual("CharacterRace deve ser preservado", LoadedSave->CharacterRace, FName(TEXT("Elf")));
                       TestEqual("CharacterClass deve ser preservado", LoadedSave->CharacterClass,
                                 FName(TEXT("Wizard")));
                   }
               });

            It("deve retornar nullptr quando save não existe",
               [this]()
               {
                   // Arrange: Não salvar nada, usar slot que não existe
                   FString NonExistentSlot = TEXT("NonExistentSlot_12345");

                   // Act
                   UMyProject2SaveGame *LoadedSave = USaveGameHelpers::LoadGameFromSlot(NonExistentSlot, TestUserIndex);

                   // Assert
                   TestNull("LoadGameFromSlot deve retornar nullptr quando save não existe", LoadedSave);
               });

            It("deve usar DefaultSaveSlotName quando SlotName é vazio",
               [this]()
               {
                   // Arrange: Salvar no slot padrão
                   TestSaveGame->CharacterName = TEXT("DefaultSlotCharacter");
                   USaveGameHelpers::SaveGameToSlot(TestSaveGame, TEXT(""), TestUserIndex);

                   // Act
                   UMyProject2SaveGame *LoadedSave = USaveGameHelpers::LoadGameFromSlot(TEXT(""), TestUserIndex);

                   // Assert
                   TestNotNull("LoadGameFromSlot deve carregar do slot padrão", LoadedSave);
                   if (LoadedSave)
                   {
                       TestEqual("CharacterName deve ser preservado", LoadedSave->CharacterName,
                                 TEXT("DefaultSlotCharacter"));
                   }
               });
        });

#pragma endregion LoadGameFromSlot Tests

    // ========================================================================
    // DoesSaveGameExist Tests
    // ========================================================================
#pragma region DoesSaveGameExist Tests

    Describe("DoesSaveGameExist",
             [this]()
             {
                 It("deve retornar true quando save existe",
                    [this]()
                    {
                        // Arrange: Salvar primeiro
                        TestSaveGame->CharacterName = TEXT("TestCharacter");
                        USaveGameHelpers::SaveGameToSlot(TestSaveGame, TestSlotName, TestUserIndex);

                        // Act
                        bool bResult = USaveGameHelpers::DoesSaveGameExist(TestSlotName, TestUserIndex);

                        // Assert
                        TestTrue("DoesSaveGameExist deve retornar true quando save existe", bResult);
                    });

                 It("deve retornar false quando save não existe",
                    [this]()
                    {
                        // Arrange: Não salvar nada, usar slot que não existe
                        FString NonExistentSlot = TEXT("NonExistentSlot_67890");

                        // Act
                        bool bResult = USaveGameHelpers::DoesSaveGameExist(NonExistentSlot, TestUserIndex);

                        // Assert
                        TestFalse("DoesSaveGameExist deve retornar false quando save não existe", bResult);
                    });

                 It("deve usar DefaultSaveSlotName quando SlotName é vazio",
                    [this]()
                    {
                        // Arrange: Salvar no slot padrão
                        TestSaveGame->CharacterName = TEXT("TestCharacter");
                        USaveGameHelpers::SaveGameToSlot(TestSaveGame, TEXT(""), TestUserIndex);

                        // Act
                        bool bResult = USaveGameHelpers::DoesSaveGameExist(TEXT(""), TestUserIndex);

                        // Assert
                        TestTrue("DoesSaveGameExist deve retornar true para slot padrão quando save existe", bResult);
                    });
             });

#pragma endregion DoesSaveGameExist Tests

    // ========================================================================
    // DeleteGameInSlot Tests
    // ========================================================================
#pragma region DeleteGameInSlot Tests

    Describe("DeleteGameInSlot",
             [this]()
             {
                 It("deve deletar save existente com sucesso",
                    [this]()
                    {
                        // Arrange: Salvar primeiro
                        TestSaveGame->CharacterName = TEXT("TestCharacter");
                        USaveGameHelpers::SaveGameToSlot(TestSaveGame, TestSlotName, TestUserIndex);
                        TestTrue("Save deve existir antes de deletar",
                                 USaveGameHelpers::DoesSaveGameExist(TestSlotName, TestUserIndex));

                        // Act
                        bool bResult = USaveGameHelpers::DeleteGameInSlot(TestSlotName, TestUserIndex);

                        // Assert
                        TestTrue("DeleteGameInSlot deve retornar true quando save existe", bResult);
                        TestFalse("Save não deve existir após deletar",
                                  USaveGameHelpers::DoesSaveGameExist(TestSlotName, TestUserIndex));
                    });

                 It("deve retornar false quando save não existe",
                    [this]()
                    {
                        // Arrange: Não salvar nada, usar slot que não existe
                        FString NonExistentSlot = TEXT("NonExistentSlot_11111");

                        // Act
                        bool bResult = USaveGameHelpers::DeleteGameInSlot(NonExistentSlot, TestUserIndex);

                        // Assert
                        TestFalse("DeleteGameInSlot deve retornar false quando save não existe", bResult);
                    });

                 It("deve usar DefaultSaveSlotName quando SlotName é vazio",
                    [this]()
                    {
                        // Arrange: Salvar no slot padrão
                        TestSaveGame->CharacterName = TEXT("TestCharacter");
                        USaveGameHelpers::SaveGameToSlot(TestSaveGame, TEXT(""), TestUserIndex);

                        // Act
                        bool bResult = USaveGameHelpers::DeleteGameInSlot(TEXT(""), TestUserIndex);

                        // Assert
                        TestTrue("DeleteGameInSlot deve retornar true para slot padrão quando save existe", bResult);
                        TestFalse("Save não deve existir após deletar",
                                  USaveGameHelpers::DoesSaveGameExist(TEXT(""), TestUserIndex));
                    });
             });

#pragma endregion DeleteGameInSlot Tests

    // ========================================================================
    // Integration Tests (Save -> Load -> Verify)
    // ========================================================================
#pragma region Integration Tests

    Describe(
        "Save and Load Integration",
        [this]()
        {
            It("deve preservar todos os dados após salvar e carregar",
               [this]()
               {
                   // Arrange: Criar SaveGame com dados completos
                   TestSaveGame->CharacterName = TEXT("IntegrationTestCharacter");
                   TestSaveGame->CharacterLevel = 15;
                   TestSaveGame->CharacterRace = FName(TEXT("Dwarf"));
                   TestSaveGame->CharacterClass = FName(TEXT("Paladin"));
                   TestSaveGame->SaveVersion = 1;

                   // Act: Salvar e depois carregar
                   bool bSaveResult = USaveGameHelpers::SaveGameToSlot(TestSaveGame, TestSlotName, TestUserIndex);
                   UMyProject2SaveGame *LoadedSave = USaveGameHelpers::LoadGameFromSlot(TestSlotName, TestUserIndex);

                   // Assert
                   TestTrue("Save deve ser bem-sucedido", bSaveResult);
                   TestNotNull("LoadedSave não deve ser nullptr", LoadedSave);
                   if (LoadedSave)
                   {
                       TestEqual("CharacterName deve ser preservado", LoadedSave->CharacterName,
                                 TEXT("IntegrationTestCharacter"));
                       TestEqual("CharacterLevel deve ser preservado", LoadedSave->CharacterLevel, 15);
                       TestEqual("CharacterRace deve ser preservado", LoadedSave->CharacterRace, FName(TEXT("Dwarf")));
                       TestEqual("CharacterClass deve ser preservado", LoadedSave->CharacterClass,
                                 FName(TEXT("Paladin")));
                       TestEqual("SaveVersion deve ser preservado", LoadedSave->SaveVersion, 1);
                   }
               });

            It("deve atualizar SaveTimestamp ao salvar",
               [this]()
               {
                   // Arrange
                   TestSaveGame->CharacterName = TEXT("TimestampTest");
                   FDateTime BeforeSave = FDateTime::Now();

                   // Act
                   USaveGameHelpers::SaveGameToSlot(TestSaveGame, TestSlotName, TestUserIndex);
                   FDateTime AfterSave = FDateTime::Now();
                   UMyProject2SaveGame *LoadedSave = USaveGameHelpers::LoadGameFromSlot(TestSlotName, TestUserIndex);

                   // Assert
                   TestNotNull("LoadedSave não deve ser nullptr", LoadedSave);
                   if (LoadedSave)
                   {
                       // Timestamp deve estar entre BeforeSave e AfterSave (com margem de erro)
                       TestTrue("SaveTimestamp deve ser atualizado",
                                LoadedSave->SaveTimestamp >= BeforeSave && LoadedSave->SaveTimestamp <= AfterSave);
                   }
               });
        });

#pragma endregion Integration Tests
}

#pragma endregion SaveGameHelpers Tests
