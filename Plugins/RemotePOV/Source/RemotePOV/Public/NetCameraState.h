#pragma once
#include "CoreMinimal.h"
#include "NetCameraState.generated.h"

USTRUCT(BlueprintType)
struct REMOTEPOV_API FNetCameraState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FVector_NetQuantize100 Location = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FRotator Rotation = FRotator::ZeroRotator;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float FOV = 90.f;
};