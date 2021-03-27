// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleVPBlueprintLibrary.h"


#include "SimpleVPSettings.h"
#include "ViewportWorldInteraction.h"
#include "SimpleVPUtilitiesModule.h"

#if WITH_EDITOR
#include "Editor.h"
#include "IVREditorModule.h"
#include "LevelEditorViewport.h"
#include "ViewportWorldInteraction.h"
#include "SimpleVPBookmarkEditorBlueprintLibrary.h"
#include "VREditorInteractor.h"
#endif

namespace SimpleVPBlueprintLibrary
{
#if WITH_EDITOR
	FLevelEditorViewportClient* GetViewPortClient()
	{
		return	GCurrentLevelEditingViewportClient ? GCurrentLevelEditingViewportClient :
            GLastKeyLevelEditingViewportClient ? GLastKeyLevelEditingViewportClient :
            nullptr;
	}

	UViewportWorldInteraction* GetViewportWorldInteraction(FString& FailMessage)
	{
		if (FLevelEditorViewportClient* Client = GetViewPortClient())
		{
			UViewportWorldInteraction* ViewportWorldInteraction = nullptr;

			if (UEditorWorldExtensionManager* ExtensionManager = GEditor->GetEditorWorldExtensionsManager())
			{
				check(GEditor);
				if (UEditorWorldExtensionCollection* Collection = ExtensionManager->GetEditorWorldExtensions(GEditor->GetEditorWorldContext().World()))
				{
					ViewportWorldInteraction = Cast<UViewportWorldInteraction>(Collection->FindExtension(UViewportWorldInteraction::StaticClass()));

					if (ViewportWorldInteraction != nullptr)
					{
						return ViewportWorldInteraction;
					}
				}
			}
		}

		UE_LOG(LogSimpleVPUtilities, Warning, TEXT("UVPBlueprintLibrary::GetViewportWorldInteraction - Failed to get VPI. %s"), *FailMessage);
		return nullptr;
	}
#endif
}

void USimpleVPBlueprintLibrary::Refresh3DEditorViewport()
{
#if WITH_EDITOR	
	if (FLevelEditorViewportClient* VP = SimpleVPBlueprintLibrary::GetViewPortClient())
	{
		VP->Invalidate(true);
	}
#endif
}

ASimpleVPViewportTickableBase* USimpleVPBlueprintLibrary::SpawnVPTickableActor(UObject* ContextObject,
	const TSubclassOf<ASimpleVPViewportTickableBase> ActorClass, const FVector Location, const FRotator Rotation)
{
	if (ActorClass.Get() == nullptr)
	{
		UE_LOG(LogSimpleVPUtilities, Warning, TEXT("USimpleVPBlueprintLibrary::SpawnVPTickableActor - The ActorClass is invalid"));
		return nullptr;
	}

	UWorld* World = ContextObject ? ContextObject->GetWorld() : nullptr;
	if (World == nullptr)
	{
		UE_LOG(LogSimpleVPUtilities, Warning, TEXT("USimpleVPBlueprintLibrary::SpawnVPTickableActor - The ContextObject is invalid."));
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ASimpleVPViewportTickableBase* NewActor = World->SpawnActor<ASimpleVPViewportTickableBase>(ActorClass.Get(), Location, Rotation, SpawnParams);
	return NewActor;
}

AActor* USimpleVPBlueprintLibrary::SpawnBookmarkAtCurrentLevelEditorPosition(const TSubclassOf<AActor> ActorClass,
	const FSimpleVPBookmarkCreationContext CreationContext, const FVector Offset, const bool bFlattenRotation)
{
	AActor* Result = nullptr;
#if WITH_EDITOR
	Result = USimpleVPBookmarkEditorBlueprintLibrary::AddBookmarkAtCurrentLevelEditorPosition(ActorClass, CreationContext, Offset, bFlattenRotation);
#endif
	return Result;
}

bool USimpleVPBlueprintLibrary::JumpToBookmarkInLevelEditor(const USimpleVPBookmark* Bookmark)
{
	bool bResult = false;
#if WITH_EDITOR
	bResult = USimpleVPBookmarkEditorBlueprintLibrary::JumpToBookmarkInLevelEditor(Bookmark);
#endif
	return bResult;
}

FGameplayTagContainer USimpleVPBlueprintLibrary::GetVirtualProductionRole()
{
	return GetDefault<USimpleVPSettings>()->GetRoles();
}

FTransform USimpleVPBlueprintLibrary::GetEditorViewportTransform()
{
#if WITH_EDITOR
	if (FLevelEditorViewportClient* Client = SimpleVPBlueprintLibrary::GetViewPortClient())
	{ 
		FRotator ViewportRotation(0, 0, 0);
		FVector ViewportLocation(0, 0, 0);
		
		if (!Client->IsOrtho())
		{
			ViewportRotation = Client->GetViewRotation();
		}

		ViewportLocation = Client->GetViewLocation();
		return FTransform(ViewportRotation, ViewportLocation, FVector::OneVector);
	}
#endif

	return FTransform();
}

FTransform USimpleVPBlueprintLibrary::GetEditorVRHeadTransform()
{
#if WITH_EDITOR
	FString ErrorText(TEXT("Head Transform will be invalid."));
	if (const UViewportWorldInteraction* VPI = SimpleVPBlueprintLibrary::GetViewportWorldInteraction(ErrorText))
	{
		return VPI->GetHeadTransform();
	}
#endif

	return FTransform::Identity;
}

FTransform USimpleVPBlueprintLibrary::GetEditorVRRoomTransform()
{
#if WITH_EDITOR
	FString ErrorText(TEXT("Room Transform will be invalid."));
	if (const UViewportWorldInteraction* VPI = SimpleVPBlueprintLibrary::GetViewportWorldInteraction(ErrorText))
	{
		return VPI->GetRoomTransform();
	}
#endif

	return FTransform::Identity;
}

void USimpleVPBlueprintLibrary::SetGrabSpeed(const float Speed)
{
	IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("VI.DragScale"));
	CVar->Set(Speed);
}

bool USimpleVPBlueprintLibrary::IsVREditorModeActive()
{
#if WITH_EDITOR
	if (IVREditorModule::IsAvailable())
	{
		return IVREditorModule::Get().IsVREditorModeActive();
	}
#endif

	return false;
}

FVector USimpleVPBlueprintLibrary::GetVREditorLaserHoverLocation()
{
#if WITH_EDITOR
	FString ErrorText(TEXT("VR laser hit location will be invalid."));
	if (const UViewportWorldInteraction* VPI = SimpleVPBlueprintLibrary::GetViewportWorldInteraction(ErrorText))
	{
		const TArray<UViewportInteractor*> Interactors = VPI->GetInteractors();

		for (UViewportInteractor* Interactor : Interactors)
		{
			if (UVREditorInteractor* EdInteractor = Cast<UVREditorInteractor>(Interactor))
			{
				if (EdInteractor->GetControllerType() == EControllerType::Laser)
				{
					//FVector Temp = EdInteractor->GetHoverLocation();
					//UE_LOG(LogVPUtilities, Warning, TEXT("%s"), *Temp.ToString());

					return EdInteractor->GetInteractorData().LastHoverLocationOverUI;
				}
			}
		}
	}
#endif

	return FVector(0);
}

bool USimpleVPBlueprintLibrary::EditorUndo()
{
#if WITH_EDITOR
	FString ErrorText(TEXT("Undo did not execute."));
	if (UViewportWorldInteraction* VPI = SimpleVPBlueprintLibrary::GetViewportWorldInteraction(ErrorText))
	{
		VPI->Undo();
		return true;
	}
#endif

	return false;
}

bool USimpleVPBlueprintLibrary::EditorRedo()
{
#if WITH_EDITOR
	FString ErrorText(TEXT("Redo did not execute."));
	if (UViewportWorldInteraction* VPI = SimpleVPBlueprintLibrary::GetViewportWorldInteraction(ErrorText))
	{
		VPI->Redo();
		return true;
	}
#endif

	return false;
}

bool USimpleVPBlueprintLibrary::EditorDuplicate()
{
#if WITH_EDITOR
	FString ErrorText(TEXT("Duplicate did not execute."));
	if (UViewportWorldInteraction* VPI = SimpleVPBlueprintLibrary::GetViewportWorldInteraction(ErrorText))
	{
		VPI->Duplicate();
		return true;
	}
#endif

	return false;
}

bool USimpleVPBlueprintLibrary::EditorDeleteSelectedObjects()
{
#if WITH_EDITOR
	FString ErrorText(TEXT("Delete did not execute."));
	if (UViewportWorldInteraction* VPI = SimpleVPBlueprintLibrary::GetViewportWorldInteraction(ErrorText))
	{
		VPI->DeleteSelectedObjects();
		return true;
	}
#endif

	return false;
}

void USimpleVPBlueprintLibrary::VPBookmarkSplineMeshIndicatorSetStartAndEnd(USplineMeshComponent* SplineMesh)
{
	SplineMesh->SetVisibility(true);
	const FTransform SplineTransform = SplineMesh->GetComponentTransform();
		
	// @todo: Fix - GetVREditorLaserHoverLocation() does not return the correct hover location
	// USplineMeshComponent::SetEndPosition expects local space
	SplineMesh->SetEndPosition(SplineTransform.InverseTransformPosition(IsVREditorModeActive() ? GetVREditorLaserHoverLocation() : GetEditorViewportTransform().TransformPosition(FVector(80, 0, -20))));
}

void USimpleVPBlueprintLibrary::VPBookmarkSplineMeshIndicatorDisable(USplineMeshComponent* SplineMesh)
{
	SplineMesh->SetVisibility(false);
}
