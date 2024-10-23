// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/LoggerLib.h"

#include "AdvancedLogger.h"
#include "LoggerSettings.h"

void ULoggerLib::SetConsoleColor(EConsoleColor InColor)
{
	switch (InColor)
	{
	case EConsoleColor::COLOR_BLACK:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_BLACK);
		break;
	case EConsoleColor::COLOR_DARK_RED:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_DARK_RED);
		break;
	case EConsoleColor::COLOR_DARK_GREEN:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_DARK_GREEN);
		break;
	case EConsoleColor::COLOR_DARK_BLUE:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_DARK_BLUE);
		break;
	case EConsoleColor::COLOR_DARK_YELLOW:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_DARK_YELLOW);
		break;
	case EConsoleColor::COLOR_DARK_CYAN:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_DARK_CYAN);
		break;
	case EConsoleColor::COLOR_DARK_PURPLE:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_DARK_PURPLE);
		break;
	case EConsoleColor::COLOR_GRAY:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_GRAY);
		break;
	case EConsoleColor::COLOR_RED:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_RED);
		break;
	case EConsoleColor::COLOR_GREEN:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_GREEN);
		break;
	case EConsoleColor::COLOR_BLUE:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_BLUE);
		break;
	case EConsoleColor::COLOR_YELLOW:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_YELLOW);
		break;
	case EConsoleColor::COLOR_CYAN:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_CYAN);
		break;
	case EConsoleColor::COLOR_PURPLE:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_PURPLE);
		break;
	case EConsoleColor::COLOR_WHITE:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_WHITE);
		break;
	case EConsoleColor::COLOR_NONE:
		SET_WARN_COLOR(OutputDeviceColor::COLOR_NONE);
		break;
	default:
		// Optional: Handle unexpected colors if needed
		break;
	}
}

const ULoggerSettings* ULoggerLib::GetSettings()
{
	return GetDefault<ULoggerSettings>();
}

FString ULoggerLib::MakeSidePrefix(UWorld* InWorld)
{
	FString Prefix;
	if (InWorld)
	{
		
		if (InWorld->WorldType == EWorldType::PIE)
		{
			switch (InWorld->GetNetMode())
			{
			case NM_Client:
				// GPlayInEditorID 0 is always the server, so 1 will be first client.
				Prefix = FString::Printf(TEXT("Client %d: "), static_cast<int32>(UE::GetPlayInEditorID()));
				break;
			case NM_DedicatedServer:
			case NM_ListenServer:
				Prefix = FString::Printf(TEXT("Server: "));
				break;
			case NM_Standalone:
				break;
			default:
				break;
			}
		}
	}
	return Prefix;
}

void ULoggerLib::Log(const UObject* InContextObject, FString InMessage, int32 InKey, float InTime,
                     bool bConsoleLog)
{
	const ULoggerSettings* settings = GetSettings();

	if (UWorld* World = GEngine->GetWorldFromContextObject(InContextObject, EGetWorldErrorMode::ReturnNull))
	{
		ScreenMessage(InContextObject, MakeSidePrefix(World) + InMessage, InKey, settings->Log.ScreenColor, InTime);
	}
	else
	{
		ScreenMessage(InContextObject, InMessage, InKey, settings->Log.ScreenColor, InTime);
	}

	if (bConsoleLog)
	{
		ConsoleLog(InContextObject, InMessage, settings->Log.ConsoleColor);
	}
}

void ULoggerLib::LogStatic(FString InMessage, int32 InKey, float InTime, bool bConsoleLog)
{
	ULoggerLib::Log(nullptr, InMessage, InKey, InTime, bConsoleLog);
}

void ULoggerLib::WarningStatic(FString InMessage, int32 InKey, float InTime, bool bConsoleLog)
{
	ULoggerLib::Warning(nullptr, InMessage, InKey, InTime, bConsoleLog);
}

void ULoggerLib::ErrorStatic(FString InMessage, int32 InKey, float InTime, bool bConsoleLog)
{
	ULoggerLib::Error(nullptr, InMessage, InKey, InTime, bConsoleLog);
}

void ULoggerLib::ScreenMessageStatic(FString InMessage, int32 InKey, FLinearColor InColor, float InTime)
{
	ULoggerLib::ScreenMessage(nullptr, InMessage, InKey, InColor, InTime);
}

void ULoggerLib::ConsoleLogStatic(FString InMessage, EConsoleColor InColor)
{
	ULoggerLib::ConsoleLog(nullptr, InMessage, InColor);
}

void ULoggerLib::Warning(const UObject* InContextObject, FString InMessage, int32 InKey, float InTime,
                         bool bConsoleLog)
{
	const ULoggerSettings* settings = GetSettings();

	if (UWorld* World = GEngine->GetWorldFromContextObject(InContextObject, EGetWorldErrorMode::ReturnNull))
	{
		ScreenMessage(InContextObject, MakeSidePrefix(World) + FString::Printf(TEXT("*WRN* %s"), *InMessage), InKey,
		              settings->Warn.ScreenColor,
		              InTime);
	}
	else
	{
		ScreenMessage(InContextObject, FString::Printf(TEXT("*WRN* %s"), *InMessage), InKey,
		              settings->Warn.ScreenColor,
		              InTime);
	}

	if (bConsoleLog)
	{
		ConsoleLog(InContextObject, InMessage, settings->Warn.ConsoleColor);
	}
}

void ULoggerLib::Error(const UObject* InContextObject, FString InMessage, int32 InKey, float InTime,
                       bool bConsoleLog)
{
	const ULoggerSettings* settings = GetSettings();
	if (UWorld* World = GEngine->GetWorldFromContextObject(InContextObject, EGetWorldErrorMode::ReturnNull))
	{
		ScreenMessage(InContextObject, MakeSidePrefix(World) + FString::Printf(TEXT("*ERR* %s"), *InMessage),
		              InKey, settings->Error.ScreenColor, InTime);
	}
	else
	{
		ScreenMessage(InContextObject, FString::Printf(TEXT("*ERR* %s"), *InMessage),
		              InKey, settings->Error.ScreenColor, InTime);
	}

	if (bConsoleLog)
	{
		ConsoleLog(InContextObject, InMessage, settings->Error.ConsoleColor);
	}
}

void ULoggerLib::ScreenMessage(const UObject* InContextObject, FString InMessage, int32 InKey,
                               FLinearColor InColor,
                               float InTime)
{
	const ULoggerSettings* settings = GetSettings();
	bool bCanScreenLog = true;
#if NO_LOGGING
	bCanScreenLog = settings->bScreenLog;
#endif

	if (!bCanScreenLog)
		return;

	FString contextString = IsValid(InContextObject)
		                        ? FString::Printf(TEXT("%s:"), *InContextObject->GetClass()->GetFName().ToString())
		                        : TEXT("");

	GEngine->AddOnScreenDebugMessage(InKey, InTime, InColor.ToFColor(true),
	                                 FString::Printf(TEXT("[%s] %s"), *contextString, *InMessage));
}

void ULoggerLib::ConsoleLog(const UObject* InContextObject, FString InMessage, EConsoleColor InColor)
{
	const ULoggerSettings* settings = GetSettings();
	bool bCanConsoleLog = true;

#if NO_LOGGING
	bCanConsoleLog = settings->bConsoleLog;
#endif

	if (!bCanConsoleLog)
		return;

	if (InColor == EConsoleColor::COLOR_NONE)
	{
		CLEAR_WARN_COLOR();
	}
	else
	{
		SetConsoleColor(InColor);
	}
	FString contextString = IsValid(InContextObject)
		                        ? FString::Printf(TEXT("%s:"), *InContextObject->GetClass()->GetFName().ToString())
		                        : TEXT("");
	auto world = GEngine->GetWorldFromContextObject(InContextObject, EGetWorldErrorMode::ReturnNull);
	FString netMode = FString(NETMODE(world));
	UE_LOG(LogAdvanced, Log, TEXT("%s %s %s"),
	       *netMode,
	       *contextString,
	       *InMessage
	);

	CLEAR_WARN_COLOR();
}
