// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleVPBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEVPUTILITIES_API USimpleVPBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Set the VR grab speed cvar */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void SetGrabSpeed(const float Speed);

	/** Trigger an UnrealEd Duplicate */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static bool EditorDuplicate();
	
};
