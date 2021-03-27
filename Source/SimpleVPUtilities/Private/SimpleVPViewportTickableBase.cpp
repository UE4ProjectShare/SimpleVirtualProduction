// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleVPViewportTickableBase.h"

ASimpleVPViewportTickableBase::ASimpleVPViewportTickableBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ViewportTickType(ESimpleVPViewportTickableFlags::Game | ESimpleVPViewportTickableFlags::Editor)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SetActorTickEnabled(true);
	//we don't want virtual production objects to be visible by cameras
	SetActorHiddenInGame(true);
}

void ASimpleVPViewportTickableBase::EditorLockLocation(bool bSetLockLocation)
{
#if WITH_EDITOR
	bLockLocation = bSetLockLocation;
#endif
}

void ASimpleVPViewportTickableBase::EditorDestroyed_Implementation()
{
}

void ASimpleVPViewportTickableBase::EditorTick_Implementation(float DeltaSeconds)
{
}

bool ASimpleVPViewportTickableBase::ShouldTickIfViewportsOnly() const
{
	if (UWorld* World = GetWorld())
	{
		switch (World->WorldType)
		{
		case EWorldType::Game:
        case EWorldType::GameRPC:
        case EWorldType::PIE:
            return static_cast<uint8>(ViewportTickType & ESimpleVPViewportTickableFlags::Game) != 0;
		case EWorldType::Editor:
			return static_cast<uint8>(ViewportTickType & ESimpleVPViewportTickableFlags::Editor) != 0;
		case EWorldType::EditorPreview:
			return static_cast<uint8>(ViewportTickType & ESimpleVPViewportTickableFlags::EditorPreview) != 0;
		case EWorldType::GamePreview:
			return static_cast<uint8>(ViewportTickType & ESimpleVPViewportTickableFlags::GamePreview) != 0;
		}
	}
	return false;
}

void ASimpleVPViewportTickableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if WITH_EDITOR
	if (GIsEditor)
	{
		FEditorScriptExecutionGuard ScriptGuard;
		EditorTick(DeltaTime);
	}
#endif
}

void ASimpleVPViewportTickableBase::Destroyed()
{
#if WITH_EDITOR
	if (GIsEditor)
	{
		FEditorScriptExecutionGuard ScriptGuard;
		EditorDestroyed();
	}
#endif

	Super::Destroyed();
}
