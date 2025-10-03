#include "RemotePOVFunctionLibrary.h"
#include "RemotePOVCapture.h"
#include "RemoteCameraStateReplicator.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void URemotePOVFunctionLibrary::SpawnPOVCaptureFor(UObject* WorldContextObject, ARemoteCameraStateReplicator* TargetRep, ARemotePOVCapture*& OutCapture, int32 Width, int32 Height)
{
    OutCapture = nullptr;
    if (!WorldContextObject || !TargetRep) return;
    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    ARemotePOVCapture* Cap = World->SpawnActor<ARemotePOVCapture>(ARemotePOVCapture::StaticClass(), FTransform::Identity, Params);
    if (Cap)
    {
        Cap->TargetReplicator = TargetRep;
        Cap->RT_Width = Width;
        Cap->RT_Height = Height;
        OutCapture = Cap;
    }
}

ARemoteCameraStateReplicator* URemotePOVFunctionLibrary::FindOtherPlayersReplicator(UObject* WorldContextObject, APlayerController* LocalPC)
{
    if (!WorldContextObject) return nullptr;
    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return nullptr;

    TArray<AActor*> Found;
    UGameplayStatics::GetAllActorsOfClass(World, ARemoteCameraStateReplicator::StaticClass(), Found);
    for (AActor* A : Found)
    {
        if (A->GetOwner() != LocalPC)
        {
            return Cast<ARemoteCameraStateReplicator>(A);
        }
    }
    return nullptr;
}