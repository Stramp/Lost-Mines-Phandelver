// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/GameplayTagHelpers.h"
#include "GameplayTagContainer.h"

#pragma endregion Includes

// ============================================================================
// GameplayTagHelpers Tests
// ============================================================================
#pragma region GameplayTagHelpers Tests

BEGIN_DEFINE_SPEC(GameplayTagHelpersSpec, "MyProject2.Utils.GameplayTagHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(GameplayTagHelpersSpec)

void GameplayTagHelpersSpec::Define()
{
    Describe("HasTag",
             [this]()
             {
                 It("deve retornar true quando container contém a tag",
                    [this]()
                    {
                        // Arrange
                        FGameplayTagContainer Container;
                        FGameplayTag Tag = FGameplayTag::RequestGameplayTag(FName("Race.Elf"));
                        if (Tag.IsValid())
                        {
                            Container.AddTag(Tag);
                        }

                        // Act
                        bool Result = GameplayTagHelpers::HasTag(Container, Tag);

                        // Assert
                        TestTrue("Container deve conter a tag", Result);
                    });

                 It("deve retornar false quando container não contém a tag",
                    [this]()
                    {
                        // Arrange
                        FGameplayTagContainer Container;
                        FGameplayTag Tag = FGameplayTag::RequestGameplayTag(FName("Race.Elf"));
                        FGameplayTag OtherTag = FGameplayTag::RequestGameplayTag(FName("Race.Dwarf"));
                        if (Tag.IsValid())
                        {
                            Container.AddTag(Tag);
                        }

                        // Act
                        bool Result = GameplayTagHelpers::HasTag(Container, OtherTag);

                        // Assert
                        TestFalse("Container não deve conter a tag diferente", Result);
                    });

                 It("deve retornar false quando tag é inválida",
                    [this]()
                    {
                        // Arrange
                        FGameplayTagContainer Container;
                        FGameplayTag InvalidTag;

                        // Act
                        bool Result = GameplayTagHelpers::HasTag(Container, InvalidTag);

                        // Assert
                        TestFalse("Deve retornar false para tag inválida", Result);
                    });
             });

    Describe("HasAnyTagInGroup",
             [this]()
             {
                 It("deve retornar true quando container contém tag do grupo",
                    [this]()
                    {
                        // Arrange
                        FGameplayTagContainer Container;
                        FGameplayTag RaceTag = FGameplayTag::RequestGameplayTag(FName("Race.Elf"));
                        FGameplayTag RaceGroup = FGameplayTag::RequestGameplayTag(FName("Race"));
                        if (RaceTag.IsValid())
                        {
                            Container.AddTag(RaceTag);
                        }

                        // Act
                        bool Result = GameplayTagHelpers::HasAnyTagInGroup(Container, RaceGroup);

                        // Assert
                        TestTrue("Container deve conter tag do grupo Race", Result);
                    });

                 It("deve retornar false quando container não contém tag do grupo",
                    [this]()
                    {
                        // Arrange
                        FGameplayTagContainer Container;
                        FGameplayTag ItemTag = FGameplayTag::RequestGameplayTag(FName("Item.Weapon"));
                        FGameplayTag RaceGroup = FGameplayTag::RequestGameplayTag(FName("Race"));
                        if (ItemTag.IsValid())
                        {
                            Container.AddTag(ItemTag);
                        }

                        // Act
                        bool Result = GameplayTagHelpers::HasAnyTagInGroup(Container, RaceGroup);

                        // Assert
                        TestFalse("Container não deve conter tag do grupo Race", Result);
                    });
             });

    Describe("NameToTag",
             [this]()
             {
                 It("deve converter FName válido para FGameplayTag válida",
                    [this]()
                    {
                        // Arrange
                        FName TagName = FName("Race.Elf");

                        // Act
                        FGameplayTag Result = GameplayTagHelpers::NameToTag(TagName);

                        // Assert
                        TestTrue("Tag deve ser válida", Result.IsValid());
                        TestEqual("Tag deve ter o nome correto", Result.GetTagName(), TagName);
                    });

                 It("deve retornar tag inválida quando FName é NAME_None",
                    [this]()
                    {
                        // Arrange
                        FName TagName = NAME_None;

                        // Act
                        FGameplayTag Result = GameplayTagHelpers::NameToTag(TagName);

                        // Assert
                        TestFalse("Tag deve ser inválida", Result.IsValid());
                    });
             });

    Describe("TagToName",
             [this]()
             {
                 It("deve converter FGameplayTag válida para FName",
                    [this]()
                    {
                        // Arrange
                        FGameplayTag Tag = FGameplayTag::RequestGameplayTag(FName("Race.Elf"));

                        // Act
                        FName Result = GameplayTagHelpers::TagToName(Tag);

                        // Assert
                        TestNotEqual(TEXT("Nome não deve ser NAME_None"), Result, NAME_None);
                        if (Tag.IsValid())
                        {
                            TestEqual("Nome deve corresponder à tag", Result, Tag.GetTagName());
                        }
                    });

                 It("deve retornar NAME_None quando tag é inválida",
                    [this]()
                    {
                        // Arrange
                        FGameplayTag InvalidTag;

                        // Act
                        FName Result = GameplayTagHelpers::TagToName(InvalidTag);

                        // Assert
                        TestEqual(TEXT("Nome deve ser NAME_None para tag inválida"), Result, NAME_None);
                    });
             });
}

#pragma endregion GameplayTagHelpers Tests
