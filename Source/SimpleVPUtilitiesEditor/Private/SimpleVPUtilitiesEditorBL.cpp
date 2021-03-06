// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleVPUtilitiesEditorBL.h"

#include "ObjectTools.h"
#include "SimpleVPUtilitiesEditorModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "EditorFramework/AssetImportData.h"
#include "Factories/TextureFactory.h"
#include "Misc/FileHelper.h"

ASimpleVPEditorTickableActorBase* USimpleVPUtilitiesEditorBL::SpawnVPEditorTickableActor(UObject* ContextObject,
                                                                                         const TSubclassOf<ASimpleVPEditorTickableActorBase> ActorClass, const FVector Location, const FRotator Rotation)
{
	if (ActorClass.Get() == nullptr)
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("SimpleVPUtilitiesEditorBlueprintLibrary::SpawnVPEditorTickableActor - The ActorClass is invalid"));
		return nullptr;
	}

	UWorld* World = ContextObject ? ContextObject->GetWorld() : nullptr;
	if (World == nullptr)
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("SimpleVPUtilitiesEditorBlueprintLibrary::SpawnVPEditorTickableActor - The ContextObject is invalid."));
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ASimpleVPEditorTickableActorBase* NewActor = World->SpawnActor<ASimpleVPEditorTickableActorBase>(ActorClass.Get(), Location, Rotation, SpawnParams);
	return NewActor;
}

ASimpleVPTransientEdTickableBase* USimpleVPUtilitiesEditorBL::SpawnVPTransientEditorTickableActor(
	UObject* ContextObject, const TSubclassOf<ASimpleVPTransientEdTickableBase> ActorClass, const FVector Location,
	const FRotator Rotation)
{
	if (ActorClass.Get() == nullptr)
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("SimpleVPUtilitiesEditorBlueprintLibrary::SpawnSimpleVPTransientEditorTickableActor - The ActorClass is invalid"));
		return nullptr;
	}

	UWorld* World = ContextObject ? ContextObject->GetWorld() : nullptr;
	if (World == nullptr)
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("SimpleVPUtilitiesEditorBlueprintLibrary::SpawnSimpleVPTransientEditorTickableActor - The ContextObject is invalid."));
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ASimpleVPTransientEdTickableBase* NewActor = World->SpawnActor<ASimpleVPTransientEdTickableBase>(ActorClass.Get(), Location, Rotation, SpawnParams);
	return NewActor;
}

UTexture* USimpleVPUtilitiesEditorBL::ImportSnapshotTexture(FString FileName, FString SubFolderName,
	FString AbsolutePathPackage)
{
	UTexture* UnrealTexture = NULL;

	if (FileName.IsEmpty())
	{
		return UnrealTexture;
	}

	if (AbsolutePathPackage.IsEmpty())
	{
		AbsolutePathPackage = FPaths::ProjectSavedDir() + "SimpleVirtualProduction/Snapshots/" + SubFolderName + "/";
	}

	FString TextureName = FPaths::GetBaseFilename(FileName);
	TextureName = ObjectTools::SanitizeObjectName(TextureName);
	FString Extension = FPaths::GetExtension(FileName).ToLower();

	FString PackageName = TEXT("/Game/Snapshots/" + SubFolderName + "/");
	PackageName += TextureName;
	UPackage* Package = CreatePackage(*PackageName);
	Package->FullyLoad();

	// try opening from absolute path
	FileName = AbsolutePathPackage + FileName;
	TArray<uint8> TextureData;
	if (!(FFileHelper::LoadFileToArray(TextureData, *FileName) && TextureData.Num() > 0))
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("Unable to find Texture file %s"), *FileName);
	}
	else
	{
		UTextureFactory* TextureFactory = NewObject<UTextureFactory>();
		TextureFactory->AddToRoot();
		TextureFactory->SuppressImportOverwriteDialog();

		const uint8* PtrTexture = TextureData.GetData();
		UnrealTexture = Cast<UTexture>(TextureFactory->FactoryCreateBinary(UTexture2D::StaticClass(), Package, *TextureName, RF_Standalone | RF_Public, NULL, *Extension, PtrTexture, PtrTexture + TextureData.Num(), GWarn));
		if (UnrealTexture != nullptr)
		{
			UnrealTexture->AssetImportData->Update(FileName);

			Package->MarkPackageDirty();

			// Notify the asset registry
			FAssetRegistryModule::AssetCreated(UnrealTexture);
		}

		TextureFactory->RemoveFromRoot();
	}

	return UnrealTexture;
}

UOSCServer* USimpleVPUtilitiesEditorBL::GetDefaultOSCServer()
{
	return FSimpleVPUtilitiesEditorModule::Get().GetOSCServer();
}
