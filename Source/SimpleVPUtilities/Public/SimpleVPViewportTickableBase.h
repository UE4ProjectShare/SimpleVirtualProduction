// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleVPViewportTickableBase.generated.h"

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ESimpleVPViewportTickableFlags : uint8
{
	Editor			= 1 << 0,
    Game			= 1 << 1,
    EditorPreview	= 1 << 2,
    GamePreview		= 1 << 3,
};
ENUM_CLASS_FLAGS(ESimpleVPViewportTickableFlags)

UCLASS(Abstract)
class SIMPLEVPUTILITIES_API ASimpleVPViewportTickableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleVPViewportTickableBase(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Tick")
	void EditorTick(float DeltaSeconds);

	UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Utilities")
	void EditorDestroyed();
	
	/** Sets the LockLocation variable to disable movement from the translation gizmo */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Editor")
    void EditorLockLocation(bool bSetLockLocation);

	/**
	* Where the actor should be ticked.
	* Editor = Tick in the editor viewport. Use the event EditorTick.
	* Game = Tick in game even if we are only ticking the viewport. Use the event Tick.
	* Preview = Tick if the actor is present in any editing tool like Blueprint or Material graph. Use EditorTick.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Actor Tick", meta = (Bitmask, BitmaskEnum = EVPViewportTickableType))
	ESimpleVPViewportTickableFlags ViewportTickType;

	/** If true, actor is ticked even if TickType==LEVELTICK_ViewportsOnly */
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

};
