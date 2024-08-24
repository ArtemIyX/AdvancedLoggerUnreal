// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/LoggerSubsystem.h"

#include "AdvancedLogger.h"

void ULoggerSubsystem::SetConsoleColor(EConsoleColor InColor)
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

void ULoggerSubsystem::Log(const UObject* InContextObject, FString InMessage, int32 InKey, float InTime,
                           bool bConsoleLog)
{
	//TODO: Color to settings
	ScreenMessage(InContextObject, InMessage, InKey, FColor::Purple, InTime);

	if (bConsoleLog)
	{
		//TODO: Console color to settings
		ConsoleLog(InContextObject, InMessage, EConsoleColor::COLOR_NONE);
	}
}

void ULoggerSubsystem::Warning(const UObject* InContextObject, FString InMessage, int32 InKey, float InTime,
                               bool bConsoleLog)
{
	//TODO: Color to settings
	ScreenMessage(InContextObject, InMessage, InKey, FColor::Yellow, InTime);

	if (bConsoleLog)
	{
		//TODO: Console color to settings
		ConsoleLog(InContextObject, InMessage, EConsoleColor::COLOR_YELLOW);
	}
}

void ULoggerSubsystem::Error(const UObject* InContextObject, FString InMessage, int32 InKey, float InTime,
                             bool bConsoleLog)
{
	//TODO: Color to settings
	ScreenMessage(InContextObject, InMessage, InKey, FColor::Red, InTime);

	if (bConsoleLog)
	{
		//TODO: Console color to settings
		ConsoleLog(InContextObject, InMessage, EConsoleColor::COLOR_RED);
	}
}

void ULoggerSubsystem::ScreenMessage(const UObject* InContextObject, FString InMessage, int32 InKey, FColor InColor,
                                     float InTime)
{
	FString contextString = IsValid(InContextObject)
		                        ? FString::Printf(TEXT("%s:"), *InContextObject->GetClass()->GetFName().ToString())
		                        : TEXT("");

	GEngine->AddOnScreenDebugMessage(InKey, InTime, InColor,
	                                 FString::Printf(TEXT("[%s] %s"), *contextString, *InMessage));
}

void ULoggerSubsystem::ConsoleLog(const UObject* InContextObject, FString InMessage, EConsoleColor InColor)
{
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
	FString netMode = FString(NETMODE_WORLD);
	UE_LOG(LogAdvanced, Log, TEXT("[%s] %s %s"),
	       *netMode,
	       *contextString,
	       *InMessage
	);

	CLEAR_WARN_COLOR();
}
