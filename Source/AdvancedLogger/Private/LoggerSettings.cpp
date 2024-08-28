// Fill out your copyright notice in the Description page of Project Settings.


#include "LoggerSettings.h"

FLoggerCategorySettings::FLoggerCategorySettings()
{
	ScreenColor = FColor::White;
	ConsoleColor = EConsoleColor::COLOR_NONE;
}

FLoggerCategorySettings::FLoggerCategorySettings(const FColor& InScreenColor, EConsoleColor InConsoleColor)
{
	ScreenColor = InScreenColor;
	ConsoleColor = InConsoleColor;
}

ULoggerSettings::ULoggerSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer),
	ScreenLog(false),
	ConsoleLog(false)
{
	Log = FLoggerCategorySettings(FColor::Blue, EConsoleColor::COLOR_NONE);
	Warn = FLoggerCategorySettings(FColor::Yellow, EConsoleColor::COLOR_YELLOW);
	Error = FLoggerCategorySettings(FColor::Red, EConsoleColor::COLOR_RED);
}
