// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SimpleVPBookmarkContext.generated.h"


USTRUCT(BlueprintType)
struct SIMPLEVPBOOKMARK_API FSimpleVPBookmarkCreationContext
{
	GENERATED_BODY()

public:
	/** Username of the Concert client who is creating this bookmark. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FString ConcertCreator;

	/** Category of the Bookmark */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FName CategoryName;

	/** Name of the Bookmark */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")
	FString DisplayName;
};

