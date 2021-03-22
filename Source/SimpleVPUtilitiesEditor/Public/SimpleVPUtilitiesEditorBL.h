// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SimpleVPTransientEdTickableBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleVPUtilitiesEditorBL.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEVPUTILITIESEDITOR_API USimpleVPUtilitiesEditorBL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* Spawn an editor-only virtual production tickable actor 
	* @note Actors based on the non-transient AVPEditorTickableActorBase will be saved in the level. 
	* @note Being non-transient also means that transactions happening on them will be replicated on other connected multi-user machines
	*/
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static ASimpleVPEditorTickableActorBase* SpawnVPEditorTickableActor(UObject* ContextObject, const TSubclassOf<ASimpleVPEditorTickableActorBase> ActorClass, const FVector Location, const FRotator Rotation);
		
	/**
	* Spawn an editor-only transient virtual production tickable actor
	* @note Actors based on the transient AVPTransientEditorTickableActorBase will NOT be saved in the level.
	* @note Being transient also means that transactions happening on them will NOT be replicated on other connected multi-user machines
	*/
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static ASimpleVPTransientEdTickableBase* SpawnVPTransientEditorTickableActor(UObject* ContextObject, const TSubclassOf<ASimpleVPTransientEdTickableBase> ActorClass, const FVector Location, const FRotator Rotation);

	
};
