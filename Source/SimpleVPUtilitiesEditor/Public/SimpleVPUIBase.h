// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "SimpleVPUIBase.generated.h"

class USimpleVPBookmark;

/**
 * 
 */
UCLASS()
class SIMPLEVPUTILITIESEDITOR_API USimpleVPUIBase : public UEditorUtilityWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Virtual Production")
	void OnBookmarkCreated(USimpleVPBookmark* Created);

	UFUNCTION(BlueprintImplementableEvent, Category = "Virtual Production")
    void OnBookmarkDestroyed(USimpleVPBookmark* Destroyed);

	UFUNCTION(BlueprintImplementableEvent, Category = "Virtual Production")
	void OnBookmarkCleared(USimpleVPBookmark* Cleared);
	
};
