// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SimpleVPBookmark.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleVPBookmarkBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS(meta=(ScriptName="VPBookmarkLibrary"))
class SIMPLEVPBOOKMARK_API USimpleVPBookmarkBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
    static USimpleVPBookmark* FindVPBookmark(const AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Bookmarks", meta = (WorldContext = "WorldContextObject"))
    static void GetAllVPBookmarkActors(const UObject* WorldContextObject, TArray<AActor*>& OutActors);

	UFUNCTION(BlueprintCallable, Category = "Bookmarks", meta = (WorldContext = "WorldContextObject"))
    static void GetAllVPBookmark(const UObject* WorldContextObject, TArray<USimpleVPBookmark*>& OutBookmarks);

	UFUNCTION(BlueprintCallable, Category = "Bookmarks")
    static bool CreateVPBookmarkName(AActor* Bookmark, const FString& FormatString, FString& GeneratedNumber, FString& GeneratedLetter);
};
