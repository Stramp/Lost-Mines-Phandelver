// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyProject2TestsTarget : TargetRules
{
	public MyProject2TestsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Test;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("MyProject2");
	}
}

