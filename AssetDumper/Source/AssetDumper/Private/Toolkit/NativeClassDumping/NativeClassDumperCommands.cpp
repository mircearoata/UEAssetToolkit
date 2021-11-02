﻿#include "Toolkit/NativeClassDumping/NativeClassDumperCommands.h"
#include "Toolkit/NativeClassDumping/NativeClassDumpProcessor.h"

#define LOCTEXT_NAMESPACE "NativeClassDumper"

void DumpAllNativeClasses(const TArray<FString>& Args, UWorld* World, FOutputDevice& Ar) {
	Ar.Log(TEXT("Starting console-driven native class dumping, dumping all native classes"));

	TArray<UClass*> Classes;
		
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt) {
		UClass* Class = *ClassIt;

		// Only interested in native C++ classes
		if (!Class->IsNative()) {
			continue;
		}

		Classes.Add(Class);
	}

	TArray<UStruct*> Structs;
		
	for (TObjectIterator<UStruct> StructIt; StructIt; ++StructIt) {
		UStruct* Struct = *StructIt;

		// Only interested in native C++ *structs*
		if (!Struct->IsNative() || Struct->IsA<UClass>() || Struct->IsA<UFunction>()) {
			continue;
		}

		Structs.Add(Struct);
	}
		
	Ar.Logf(TEXT("Asset data gathered successfully! Gathered %d native classes and %d native structs for dumping"), Classes.Num(), Structs.Num());

	FNativeClassDumpSettings DumpSettings{};
	DumpSettings.bExitOnFinish = true;
	FNativeClassDumpProcessor::StartNativeClassDump(DumpSettings, Classes, Structs);
	Ar.Log(TEXT("Native class dump started successfully, game will shutdown on finish"));
}

void FNativeClassDumperCommands::ProcessCommandLineArguments()
{
	UE_LOG(LogNativeClassDumper, Log, TEXT("Checking command line arguments"));
	if (FParse::Param(FCommandLine::Get(), TEXT("DumpNativeClasses")))
	{
		UE_LOG(LogNativeClassDumper, Log, TEXT("-DumpNativeClasses found, Starting native class dump"));
		TArray<UClass*> Classes;
		
		for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt) {
			UClass* Class = *ClassIt;

			// Only interested in native C++ classes
			if (!Class->IsNative()) {
				continue;
			}

			Classes.Add(Class);
		}

		TArray<UStruct*> Structs;
		
		for (TObjectIterator<UStruct> StructIt; StructIt; ++StructIt) {
			UStruct* Struct = *StructIt;

			// Only interested in native C++ *structs*
			if (!Struct->IsNative() || Struct->IsA<UClass>() || Struct->IsA<UFunction>()) {
				continue;
			}

			Structs.Add(Struct);
		}

		FNativeClassDumpSettings DumpSettings{};
		DumpSettings.bExitOnFinish = true;
		FNativeClassDumpProcessor::StartNativeClassDump(DumpSettings, Classes, Structs);
	}
}

static FAutoConsoleCommand DumpAllNativeClassesCommand(
	TEXT("DumpAllNativeClasses"),
	TEXT("Dumps all native classes existing in the game"),
	FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateStatic(&DumpAllNativeClasses));