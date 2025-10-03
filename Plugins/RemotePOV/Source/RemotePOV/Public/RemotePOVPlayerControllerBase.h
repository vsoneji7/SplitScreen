#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RemoteCameraStateReplicator.h"
#include "RemotePOVPlayerControllerBase.generated.h"

/**
 * Base PlayerController that auto-ensures a camera replicator exists for this player.
 * You can set your GameMode's PlayerControllerClass to this (or BP subclass it).
 */
UCLASS(BlueprintType)
class REMOTEPOV_API ARemotePOVPlayerControllerBase : public APlayerController
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    /** Server: ensure a replicator actor exists owned by this controller. */
    UFUNCTION(Server, Reliable)
    void ServerEnsureReplicator();

    /** Returns the replicator owned by this controller on the local machine (if present). */
    UFUNCTION(BlueprintCallable, Category="RemotePOV")
    ARemoteCameraStateReplicator* GetMyReplicator() const { return MyReplicator; }

protected:
    /** How often (Hz) to send camera updates from client to server. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RemotePOV")
    float CameraUpdateHz = 30.f;

private:
    UPROPERTY()
    ARemoteCameraStateReplicator* MyReplicator = nullptr;

    float Accum = 0.f;
    void UpdateCameraIfNeeded(float DeltaSeconds);
    void FindMyReplicator();
    void SpawnReplicator_Server();
};