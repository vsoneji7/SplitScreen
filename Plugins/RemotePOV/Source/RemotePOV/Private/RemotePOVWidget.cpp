#include "RemotePOVWidget.h"
#include "Components/Image.h"
#include "RemotePOVCapture.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Slate/SlateBrushAsset.h"

UTextureRenderTarget2D* URemotePOVWidget::GetRemoteRenderTarget() const
{
    return (CaptureActor) ? CaptureActor->RenderTarget : nullptr;
}

void URemotePOVWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (RemoteViewImage && CaptureActor && CaptureActor->RenderTarget)
    {
        FSlateBrush Brush; Brush.SetResourceObject(CaptureActor->RenderTarget);
        if (CaptureActor->RenderTarget)
        {
            Brush.ImageSize = FVector2D(CaptureActor->RenderTarget->SizeX, CaptureActor->RenderTarget->SizeY);
        }
        RemoteViewImage->SetBrush(Brush);
    }
}