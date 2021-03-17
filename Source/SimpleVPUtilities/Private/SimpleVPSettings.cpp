// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleVPSettings.h"

#include "Misc/CommandLine.h"
#include "SimpleVPUtilitiesModule.h"

USimpleVPSettings::USimpleVPSettings()
{
	FString ComandlineRoles;
	bIsCommandLineRolesValid = FParse::Value(FCommandLine::Get(), TEXT("-VPRole="), ComandlineRoles);

	if (bIsCommandLineRolesValid)
	{
		TArray<FString> RoleList;
		ComandlineRoles.ParseIntoArray(RoleList, TEXT("|"), true);

		for (const FString& Role : RoleList)
		{
			FGameplayTag Tag = FGameplayTag::RequestGameplayTag(*Role, false);
			if (Tag.IsValid())
			{
				CommandLineRoles.AddTag(Tag);
			}
			else
			{
				UE_LOG(LogVPUtilities, Fatal, TEXT("Role %s doesn't exist."), *Role);
			}
		}
	}
}

USimpleVPSettings* USimpleVPSettings::GetVPSettings()
{
	return GetMutableDefault<USimpleVPSettings>();
}

#if WITH_EDITOR

void USimpleVPSettings::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(ThisClass, Roles))
	{
		OnRolesChanged.Broadcast();
	}

	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}
#endif
