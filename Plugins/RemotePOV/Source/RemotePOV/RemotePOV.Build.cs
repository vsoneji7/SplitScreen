using UnrealBuildTool;

public class RemotePOV : ModuleRules
{
    public RemotePOV(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Slate", "SlateCore"
        });

        PublicIncludePaths.AddRange(new string[] { "RemotePOV/Public" });
        PrivateIncludePaths.AddRange(new string[] { "RemotePOV/Private" });
    }
}