// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ChatX : ModuleRules
{
    public ChatX(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput" ,
            "UMG",
            "Slate",
            "SlateCore",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] { "ChatX" });

        /*
         네가 말한 #include "ChatX/Game/CXGameModeBase.h" 
        이게 가능한 이유는 바로 Build.cs에서 PublicIncludePaths에 
        "ChatX" 경로를 추가했기 때문이야.


         */



        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
