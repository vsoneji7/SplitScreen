#include "RemotePOVCapture.h"
#include "Components/SceneCaptureComponent2D.h"

ARemotePOVCapture::ARemotePOVCapture()
{
    PrimaryActorTick.bCanEverTick = true;
    Capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));
    RootComponent = Capture;
}

void ARemotePOVCapture::BeginPlay()
{
    Super::BeginPlay();

    if (!RenderTarget)
    {
        RenderTarget = NewObject<UTextureRenderTarget2D>(this);
        RenderTarget->InitAutoFormat(RT_Width, RT_Height);
        RenderTarget->ClearColor = FLinearColor::Black;
    }
    Capture->TextureTarget = RenderTarget;

    Capture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
    Capture->ShowFlags.SetMotionBlur(false);
    Capture->bCaptureEveryFrame = bCaptureEveryFrame;
    Capture->bAlwaysPersistRenderingState = false;

    // Lighten the capture cost by default (teams can re-enable as needed)
    Capture->ShowFlags.SetScreenSpaceReflections(false);
    Capture->ShowFlags.SetAmbientOcclusion(false);
    Capture->ShowFlags.SetContactShadows(false);
}

void ARemotePOVCapture::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!TargetReplicator) return;

    const FNetCameraState& S = TargetReplicator->CameraState;
    SetActorLocationAndRotation(S.Location, S.Rotation);
    Capture->FOVAngle = S.FOV;

    if (!bCaptureEveryFrame)
    {
        if (++FrameCounter % FMath::Max(1, CaptureEveryNFrames) == 0)
        {
            Capture->CaptureScene();
        }
    }
}