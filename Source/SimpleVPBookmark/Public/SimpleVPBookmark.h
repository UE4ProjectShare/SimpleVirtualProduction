// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "SimpleVPBookmarkContext.h"
#include "Engine/BookmarkBase.h"


#include "SimpleVPBookmark.generated.h"


USTRUCT(BlueprintType)
struct SIMPLEVPBOOKMARK_API FSimpleVPBookmarkViewportData
{
	GENERATED_BODY()

	public:
	FSimpleVPBookmarkViewportData();

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FVector JumpToOffsetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FRotator LookRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	float OrthoZoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmarks")
	bool bFlattenRotation;
};

UCLASS(BlueprintType, Category = Bookmark)
class SIMPLEVPBOOKMARK_API USimpleVPBookmark : public UBookmarkBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TLazyObjectPtr<AActor> OwnedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmarks")
	FSimpleVPBookmarkCreationContext CreationContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmarks")
	FSimpleVPBookmarkViewportData CachedViewportData;

	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
	int32 GetBookmarkIndex() const;

	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
	AActor* GetAssociatedBookmarkActor() const;
};
