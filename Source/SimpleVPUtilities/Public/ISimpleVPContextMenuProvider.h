// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISimpleVPContextMenuProvider.generated.h"


class UVPContextMenu;


UINTERFACE(BlueprintType)
class USimpleVPContextMenuProvider : public UInterface
{
	GENERATED_BODY()
};


class ISimpleVPContextMenuProvider : public IInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Virtual Production")
    void OnCreateContextMenu();
};
