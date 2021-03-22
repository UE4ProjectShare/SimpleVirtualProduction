// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISimpleVPBookmarkProvider.generated.h"

class USimpleVPBookmark;
// This class does not need to be modified.
UINTERFACE(BlueprintType)//todo:MinimalAPI
class SIMPLEVPBOOKMARK_API USimpleVPBookmarkProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLEVPBOOKMARK_API ISimpleVPBookmarkProvider : public IInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Bookmarks")
    void OnBookmarkActivation(USimpleVPBookmark* Bookmark, bool bActivate);

	UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Bookmarks")
    void OnBookmarkChanged(USimpleVPBookmark* Bookmark);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Bookmarks")
    void UpdateBookmarkSplineMeshIndicator();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Bookmarks")
    void HideBookmarkSplineMeshIndicator();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Bookmarks")
    void GenerateBookmarkName();
};
