#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RemotePOVFunctionLibrary.generated.h"

class ARemoteCameraStateReplicator;
class ARemotePOVCapture;
class APlayerController;

/** Helper nodes to spawn capture actors and look up replicators. */
UCLASS()
class REMOTEPOV_API URemotePOVFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    /** Spawns a capture actor on the local client for a target (remote) replicator. */
    UFUNCTION(BlueprintCallable, Category="RemotePOV", meta=(WorldContext="WorldContextObject"))
    static void SpawnPOVCaptureFor(UObject* WorldContextObject, ARemoteCameraStateReplicator* TargetRep, ARemotePOVCapture*& OutCapture, int32 Width=1280, int32 Height=720);

    /** Find the first replicator whose owner is NOT the given PlayerController (i.e., the "other" player in a 2P session). */
    UFUNCTION(BlueprintCallable, Category="RemotePOV", meta=(WorldContext="WorldContextObject"))
    static ARemoteCameraStateReplicator* FindOtherPlayersReplicator(UObject* WorldContextObject, APlayerController* LocalPC);
};