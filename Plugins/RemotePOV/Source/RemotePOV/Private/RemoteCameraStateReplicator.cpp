#include "RemoteCameraStateReplicator.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerController.h"

ARemoteCameraStateReplicator::ARemoteCameraStateReplicator()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
    bAlwaysRelevant = true;     // ensure all clients receive it
    SetReplicateMovement(false);
}

void ARemoteCameraStateReplicator::ServerUpdateCamera_Implementation(const FNetCameraState& NewState)
{
    CameraState = NewState; // replicated to everyone (owner and non-owners)
}

void ARemoteCameraStateReplicator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ARemoteCameraStateReplicator, CameraState);
}