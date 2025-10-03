#include "RemotePOVPlayerControllerBase.h"
#include "EngineUtils.h"
#include "RemotePOVPlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"

void ARemotePOVPlayerControllerBase::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalController())
    {
        ServerEnsureReplicator();
    }
}

void ARemotePOVPlayerControllerBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!IsLocalController()) return;

    if (!MyReplicator) FindMyReplicator();
    UpdateCameraIfNeeded(DeltaSeconds);
}

void ARemotePOVPlayerControllerBase::ServerEnsureReplicator_Implementation()
{
    SpawnReplicator_Server();
}

void ARemotePOVPlayerControllerBase::SpawnReplicator_Server()
{
    // If one already exists with this owner, reuse it
    UWorld* World = GetWorld();
    if (!World) return;

    for (TActorIterator<ARemoteCameraStateReplicator> It(World); It; ++It)
    {
        if (It->GetOwner() == this)
        {
            MyReplicator = *It;
            return;
        }
    }

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.Instigator = GetPawn();
    ARemoteCameraStateReplicator* Rep = World->SpawnActor<ARemoteCameraStateReplicator>(ARemoteCameraStateReplicator::StaticClass(), FTransform::Identity, Params);
    if (Rep)
    {
        Rep->OwningPC = this;
        MyReplicator = Rep;
    }
}

void ARemotePOVPlayerControllerBase::FindMyReplicator()
{
    UWorld* World = GetWorld();
    if (!World) return;

    for (TActorIterator<ARemoteCameraStateReplicator> It(World); It; ++It)
    {
        if (It->GetOwner() == this)
        {
            MyReplicator = *It;
            return;
        }
    }
}

void ARemotePOVPlayerControllerBase::UpdateCameraIfNeeded(float DeltaSeconds)
{
    Accum += DeltaSeconds;
    const float Interval = (CameraUpdateHz > 0.f) ? (1.f / CameraUpdateHz) : (1.f / 30.f);
    if (Accum < Interval) return;
    Accum = 0.f;

    if (!MyReplicator || !PlayerCameraManager) return;

    FVector Loc; FRotator Rot; float FOV = 90.f;
    PlayerCameraManager->GetCameraViewPoint(Loc, Rot);
    FOV = PlayerCameraManager->GetFOVAngle();

    FNetCameraState S; S.Location = Loc; S.Rotation = Rot; S.FOV = FOV;
    MyReplicator->ServerUpdateCamera(S);
}