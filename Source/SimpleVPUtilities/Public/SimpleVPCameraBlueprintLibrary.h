// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleVPCameraBlueprintLibrary.generated.h"


class ACameraRig_Rail;
UENUM(BlueprintType)
enum class ESimpleVPCameraRigSpawnLinearApproximationMode : uint8
{
	None			UMETA(Display = "No Approximation"),	// We won't do linear approximation, instead using the Spline as constructed initially.
    Density,												// LinearApproximationParam will be used as a density value 
    IntegrationStep,										// LinearApproximationParam will be used as the Integration step in Unreal Units.
};

/** Parameters used to custom the CameraRig that's created. */
USTRUCT(BlueprintType)
struct FSimpleVPCameraRigSpawnParams
{
	GENERATED_BODY();

	FSimpleVPCameraRigSpawnParams();

public:
	/** Use world space (as opposed to local space) for points. */
	UPROPERTY(Transient, BlueprintReadWrite, Category="Camera Rig")
	bool bUseWorldSpace;

	/**
	* Use the first vector of input as the spawn transform.
	* Causes RigTransform to be completely ignored.
	*/
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Camera Rig")
	bool bUseFirstPointAsSpawnLocation;

	/**
	* Causes a linear approximation of the spline points to be generated instead
	* of relying purely on the passed in points / curves.
	*/
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Camera Rig")
	ESimpleVPCameraRigSpawnLinearApproximationMode LinearApproximationMode;

	/**
	* This is only used if LinearApproximationMode is not None.
	* When mode is Density:
	* See FSplinePositionLinearApproximation::Build.
	*
	* When mode is IntegrationStep:
	* Integration step (in CM) between approximation points. Decreasing this value will
	* increase the number of spline points and will therefore increase the accuracy
	* (at the cost of increased complexity).
	*/
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Camera Rig")
	float LinearApproximationParam;
};

/**
 * 
 */
UCLASS()
class SIMPLEVPUTILITIES_API USimpleVPCameraBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static ACameraRig_Rail* SpawnDollyTrackFromPoints(UObject* WorldContextObject, UPARAM(ref) const TArray<FTransform>& Points, ESplinePointType::Type InterpType = ESplinePointType::Linear);

	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static ACameraRig_Rail* SpawnDollyTrackFromPointsSmooth(UObject* WorldContextObject, UPARAM(ref) const TArray<FTransform>& Points, ESplinePointType::Type InterpType = ESplinePointType::Linear);

	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static ACameraRig_Rail* SpawnCameraRigFromActors(UObject* WorldContextObject, const FTransform& RigTransform, const TArray<AActor*>& Actors, const FSimpleVPCameraRigSpawnParams& Params);

	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static ACameraRig_Rail* SpawnCameraRigFromPoints(UObject* WorldContextObject, const FTransform& RigTransform, const TArray<FVector>& Points, const FSimpleVPCameraRigSpawnParams& Params);

	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static ACameraRig_Rail* SpawnCameraRigFromSelectedActors(UObject* WorldContextObject, const FTransform& RigTransform, const FSimpleVPCameraRigSpawnParams& Params);
};
