#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/SceneCapture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "RemoteCameraStateReplicator.h"
#include "RemotePOVCapture.generated.h"

/**
 * Local-only actor that mirrors a remote player's camera using a SceneCapture2D and renders into a UTextureRenderTarget2D.
 */
UCLASS(BlueprintType)
class REMOTEPOV_API ARemotePOVCapture : public AActor
{
    GENERATED_BODY()
public:
    ARemotePOVCapture();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneCaptureComponent2D* Capture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTextureRenderTarget2D* RenderTarget;

    /** Replicator to follow (set on each client). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ARemoteCameraStateReplicator* TargetReplicator = nullptr;

    /** Performance controls */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCaptureEveryFrame = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CaptureEveryNFrames = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RT_Width = 1280;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RT_Height = 720;

private:
    int32 FrameCounter = 0;
};