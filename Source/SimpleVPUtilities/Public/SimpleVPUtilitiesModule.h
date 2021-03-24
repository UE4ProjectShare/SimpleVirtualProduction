// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/** 
* A macro to declare a logging category as a C++ "extern", usually declared in the header and paired with DEFINE_LOG_CATEGORY in the source. Accessible by all files that include the header.
* @param CategoryName, category to declare
* @param DefaultVerbosity, default run time verbosity
* @param CompileTimeVerbosity, maximum verbosity to compile into the code
**/
DECLARE_LOG_CATEGORY_EXTERN(LogSimpleVPUtilities, Log, Log);