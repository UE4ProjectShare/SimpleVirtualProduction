// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleVPUtilitiesEditorBL.h"
#include "SimpleVPUtilitiesEditorModule.h"

ASimpleVPEditorTickableActorBase* USimpleVPUtilitiesEditorBL::SpawnVPEditorTickableActor(UObject* ContextObject,
	const TSubclassOf<ASimpleVPEditorTickableActorBase> ActorClass, const FVector Location, const FRotator Rotation)
{
	if (ActorClass.Get() == nullptr)
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("SimpleVPUtilitiesEditorBlueprintLibrary::SpawnVPEditorTickableActor - The ActorClass is invalid"));
		return nullptr;
	}

	UWorld* World = ContextObject ? ContextObject->GetWorld() : nullptr;
	if (World == nullptr)
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("SimpleVPUtilitiesEditorBlueprintLibrary::SpawnVPEditorTickableActor - The ContextObject is invalid."));
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ASimpleVPEditorTickableActorBase* NewActor = World->SpawnActor<ASimpleVPEditorTickableActorBase>(ActorClass.Get(), Location, Rotation, SpawnParams);
	return NewActor;
}

ASimpleVPTransientEdTickableBase* USimpleVPUtilitiesEditorBL::SpawnVPTransientEditorTickableActor(
	UObject* ContextObject, const TSubclassOf<ASimpleVPTransientEdTickableBase> ActorClass, const FVector Location,
	const FRotator Rotation)
{
	if (ActorClass.Get() == nullptr)
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("SimpleVPUtilitiesEditorBlueprintLibrary::SpawnSimpleVPTransientEditorTickableActor - The ActorClass is invalid"));
		return nullptr;
	}

	UWorld* World = ContextObject ? ContextObject->GetWorld() : nullptr;
	if (World == nullptr)
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("SimpleVPUtilitiesEditorBlueprintLibrary::SpawnSimpleVPTransientEditorTickableActor - The ContextObject is invalid."));
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ASimpleVPTransientEdTickableBase* NewActor = World->SpawnActor<ASimpleVPTransientEdTickableBase>(ActorClass.Get(), Location, Rotation, SpawnParams);
	return NewActor;
}
