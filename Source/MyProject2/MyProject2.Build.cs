// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject2 : ModuleRules
{
	public MyProject2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Automation Test Framework para testes unitários
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "AutomationTest" });
		}

		// Adiciona raiz do módulo como include path para evitar includes relativos (../../)
		// Permite usar: #include "Utils/CharacterSheetHelpers.h" ao invés de #include "../../Utils/CharacterSheetHelpers.h"
		PublicIncludePaths.Add(ModuleDirectory);

		// Slate UI para notificações no editor
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "EditorStyle" });
		}

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
