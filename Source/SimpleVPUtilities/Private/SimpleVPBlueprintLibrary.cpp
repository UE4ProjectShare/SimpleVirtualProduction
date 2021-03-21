// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleVPBlueprintLibrary.h"

void USimpleVPBlueprintLibrary::SetGrabSpeed(const float Speed)
{
	IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("VI.DragScale"));
	CVar->Set(Speed);
}
