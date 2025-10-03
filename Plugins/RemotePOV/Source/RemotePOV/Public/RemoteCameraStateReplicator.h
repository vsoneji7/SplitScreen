#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetCameraState.h"
#include "RemoteCameraStateReplicator.generated.h"

/**
 * An always-relevant replicated actor that carries a player's camera state (Location/Rotation/FOV) to other clients.
 * The owning client updates the server via ServerUpdateCamera(); the replicated variable then reaches everyone.
 */
UCLASS(BlueprintType)
class REMOTEPOV_API ARemoteCameraStateReplicator : public AActor
{
    GENERATED_BODY()
public:
    ARemoteCameraStateReplicator();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /** Latest camera state for this player (replicated to all clients). */
    UPROPERTY(ReplicatedUsing=OnRep_CameraState, BlueprintReadOnly)
    FNetCameraState CameraState;

    /** Server RPC: set by the owning client's PlayerController at ~20-30 Hz. */
    UFUNCTION(Server, Unreliable)
    void ServerUpdateCamera(const FNetCameraState& NewState);

    UFUNCTION()
    void OnRep_CameraState() {}

    /** Convenience: the PlayerController that owns this camera (not replicated). */
    UPROPERTY(BlueprintReadOnly)
    APlayerController* OwningPC = nullptr;
};