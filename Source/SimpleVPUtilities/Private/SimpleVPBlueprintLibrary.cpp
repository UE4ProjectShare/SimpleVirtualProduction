// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleVPBlueprintLibrary.h"

#include "ViewportWorldInteraction.h"
#include "SimpleVPUtilitiesModule.h"

#if WITH_EDITOR
#include "Editor.h"
#include "IVREditorModule.h"
#include "LevelEditorViewport.h"
#include "ViewportWorldInteraction.h"
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

void USimpleVPBlueprintLibrary::SetGrabSpeed(const float Speed)
{
	IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("VI.DragScale"));
	CVar->Set(Speed);
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
