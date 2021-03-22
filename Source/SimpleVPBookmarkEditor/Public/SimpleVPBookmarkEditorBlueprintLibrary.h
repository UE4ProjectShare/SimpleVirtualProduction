// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleVPBookmarkContext.h"
#include "SimpleVPBookmarkEditorBlueprintLibrary.generated.h"


class USimpleVPBookmark;


UCLASS()
class SIMPLEVPBOOKMARKEDITOR_API USimpleVPBookmarkEditorBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
    static bool JumpToBookmarkInLevelEditor(const USimpleVPBookmark* Bookmark);

	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
    static bool JumpToBookmarkInLevelEditorByIndex(const int32 BookmarkIndex);

	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
    static AActor* AddBookmarkAtCurrentLevelEditorPosition(const TSubclassOf<AActor> ActorClass, const FSimpleVPBookmarkCreationContext CreationContext, const FVector Offset, const bool bFlattenRotation = true);

	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
    static void GetAllActorsClassThamImplementsVPBookmarkInterface(TArray<TSubclassOf<AActor>>& OutActorClasses);
};
