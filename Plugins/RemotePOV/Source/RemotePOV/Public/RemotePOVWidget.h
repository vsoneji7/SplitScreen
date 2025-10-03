#pragma once
#include "Blueprint/UserWidget.h"
#include "RemotePOVWidget.generated.h"

class ARemotePOVCapture;
class UImage;
class UTextureRenderTarget2D;

/** Simple widget that displays a capture's render target on screen. */
UCLASS()
class REMOTEPOV_API URemotePOVWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(meta=(BindWidgetOptional))
    UImage* RemoteViewImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ARemotePOVCapture* CaptureActor;

    UFUNCTION(BlueprintCallable)
    UTextureRenderTarget2D* GetRemoteRenderTarget() const;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};