// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleVPViewportTickableBase.h"

ASimpleVPViewportTickableBase::ASimpleVPViewportTickableBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SetActorTickEnabled(true);
	//we don't want virtual production objects to be visible by cameras
	SetActorHiddenInGame(true);
}

void ASimpleVPViewportTickableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
