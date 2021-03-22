#include "SimpleVPBookmarkEditorBlueprintLibrary.h"



#include "ISimpleVPBookmarkProvider.h"
#include "LevelEditorViewport.h"
#include "SimpleVPBookmark.h"
#include "SimpleVPBookmarkEditorModule.h"
#include "Bookmarks/IBookmarkTypeTools.h"
#include "GameFramework/WorldSettings.h"

namespace BookmarkLibrary
{
	static FLevelEditorViewportClient* GetUsableViewportClient()
	{
		return GCurrentLevelEditingViewportClient ? GCurrentLevelEditingViewportClient :
            GLastKeyLevelEditingViewportClient ? GLastKeyLevelEditingViewportClient :
            nullptr;
	}
}

bool USimpleVPBookmarkEditorBlueprintLibrary::JumpToBookmarkInLevelEditor(const USimpleVPBookmark* Bookmark)
{
	if (Bookmark)
	{
		return JumpToBookmarkInLevelEditorByIndex(Bookmark->GetBookmarkIndex());
	}
	else
	{
		UE_LOG(LogSimpleVPBookmarkEditor, Warning, TEXT("SimpleVPBookmarkEditorLibrary::ActivateBookmarkInLevelEditor - Invalid component"));
	}

	return false;
}

bool USimpleVPBookmarkEditorBlueprintLibrary::JumpToBookmarkInLevelEditorByIndex(const int32 BookmarkIndex)
{
	FEditorViewportClient* Client = BookmarkLibrary::GetUsableViewportClient();
	if (Client == nullptr)
	{
		UE_LOG(LogSimpleVPBookmarkEditor, Warning, TEXT("SimpleVPBookmarkEditorLibrary::ActivateBookmarkInLevelEditorByIndex - Unable to get viewport client"));
		return false;
	}

	UWorld* World = Client->GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogSimpleVPBookmarkEditor, Warning, TEXT("SimpleVPBookmarkEditorLibrary::ActivateBookmarkInLevelEditorByIndex - Unable to get world"));
		return false;
	}

	AWorldSettings* WorldSettings = World->GetWorldSettings();
	if (WorldSettings == nullptr)
	{
		UE_LOG(LogSimpleVPBookmarkEditor, Warning, TEXT("SimpleVPBookmarkEditorLibrary::ActivateBookmarkInLevelEditorByIndex - Unable to get world settings"));
		return false;
	}

	const TArray<UBookmarkBase*>& Bookmarks = WorldSettings->GetBookmarks();
	if (!Bookmarks.IsValidIndex(BookmarkIndex) || Bookmarks[BookmarkIndex] == nullptr)
	{
		UE_LOG(LogSimpleVPBookmarkEditor, Warning, TEXT("SimpleVPBookmarkEditorLibrary::ActivateBookmarkInLevelEditorByIndex - Invalid bookmark index %d"), BookmarkIndex);
		return false;
	}

	IBookmarkTypeTools::Get().JumpToBookmark(BookmarkIndex, nullptr, Client);
	return true;
}

AActor* USimpleVPBookmarkEditorBlueprintLibrary::AddBookmarkAtCurrentLevelEditorPosition(
	const TSubclassOf<AActor> ActorClass, const FSimpleVPBookmarkCreationContext CreationContext, const FVector Offset,
	const bool bFlattenRotation)
{
	if (ActorClass.Get() == nullptr)
	{
		UE_LOG(LogSimpleVPBookmarkEditor, Warning, TEXT("SimpleVPBookmarkEditorLibrary::AddBookmarkAtCurrentLevelEditorPosition - Invalid actor class"));
		return nullptr;
	}

	FEditorViewportClient* Client = BookmarkLibrary::GetUsableViewportClient();
	if (Client == nullptr)
	{
		UE_LOG(LogSimpleVPBookmarkEditor, Warning, TEXT("SimpleVPBookmarkEditorLibrary::AddBookmarkAtCurrentLevelEditorPosition - Unable to get viewport client"));
		return nullptr;
	}

	UWorld* World = Client->GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogSimpleVPBookmarkEditor, Warning, TEXT("SimpleVPBookmarkEditorLibrary::AddBookmarkAtCurrentLevelEditorPosition - Unable to get world"));
		return nullptr;
	}

	AWorldSettings* WorldSettings = World->GetWorldSettings();
	if (WorldSettings == nullptr)
	{
		UE_LOG(LogSimpleVPBookmarkEditor, Warning, TEXT("SimpleVPBookmarkEditorLibrary::AddBookmarkAtCurrentLevelEditorPosition - Unable to get world settings"));
		return nullptr;
	}

	//return FVPBookmarkTypeActions::SpawnBookmark(*Client, ActorClass, CreationContext, Offset, bFlattenRotation);
	return nullptr;
}

void USimpleVPBookmarkEditorBlueprintLibrary::GetAllActorsClassThamImplementsVPBookmarkInterface(
	TArray<TSubclassOf<AActor>>& OutActorClasses)
{
	OutActorClasses.Reset();

	TArray<UClass*> Classes;
	GetDerivedClasses(AActor::StaticClass(), Classes);

	for (UClass* Class : Classes)
	{
		if (Class->ImplementsInterface(USimpleVPBookmarkProvider::StaticClass()))
		{
			OutActorClasses.Add(Class);
		}
	}
}
