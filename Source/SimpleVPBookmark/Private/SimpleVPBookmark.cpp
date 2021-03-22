// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleVPBookmark.h"


FSimpleVPBookmarkViewportData::FSimpleVPBookmarkViewportData()
	: JumpToOffsetLocation(FVector::ZeroVector)
	, LookRotation(FRotator::ZeroRotator)
	, OrthoZoom(0.f)
	, bFlattenRotation(false)
{
}

int32 USimpleVPBookmark::GetBookmarkIndex() const
{
	int32 Result = INDEX_NONE;
	if (UWorld* World = GetWorld())
	{
		if (AWorldSettings* WorldSettings = World->GetWorldSettings())
		{
			const TArray<UBookmarkBase*>& Bookmarks = WorldSettings->GetBookmarks();
			Bookmarks.Find(const_cast<USimpleVPBookmark*>(this), Result);
		}
	}
	return Result;
}

AActor* USimpleVPBookmark::GetAssociatedBookmarkActor() const
{
	return OwnedActor.Get();
}
