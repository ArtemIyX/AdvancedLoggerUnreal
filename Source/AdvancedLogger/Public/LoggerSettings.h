// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Subsystems/LoggerLib.h"
#include "LoggerSettings.generated.h"

/**
 * @brief A struct that defines settings for logger categories, including screen and console colors.
 * 
 * The FLoggerCategorySettings struct allows you to specify the colors that will be used
 * for different logger categories when displayed on the screen and in the console.
 */
USTRUCT(Blueprintable, BlueprintType)
struct ADVANCEDLOGGER_API FLoggerCategorySettings
{
	GENERATED_BODY()

public:
	/**
	 * @brief Default constructor for FLoggerCategorySettings.
	 * 
	 * Initializes the logger category settings with default values.
	 */
	FLoggerCategorySettings();

	/**
	 * @brief Constructor with parameters for screen and console colors.
	 * 
	 * @param InScreenColor The color to be used on the screen.
	 * @param InConsoleColor The color to be used in the console.
	 */
	FLoggerCategorySettings(const FColor& InScreenColor, EConsoleColor InConsoleColor);

public:
	/** 
	 * @brief The color used for displaying the log category on the screen.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="FLoggerCategorySettings")
	FLinearColor ScreenColor;

	/** 
	 * @brief The color used for displaying the log category in the console.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="FLoggerCategorySettings")
	EConsoleColor ConsoleColor;
};

/**
 * @brief A class that defines the settings for the advanced logger, including different log categories.
 * 
 * ULoggerSettings allows for configuration of logger settings, including different colors for 
 * Log, Warn, and Error categories. This class is configurable from the game settings and can be 
 * customized in the Unreal Editor.
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Logger Settings"))
class ADVANCEDLOGGER_API ULoggerSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * @brief Constructor for ULoggerSettings.
	 * 
	 * Initializes the logger settings with an optional object initializer.
	 * 
	 * @param ObjectInitializer The object initializer to use for setting up the logger settings.
	 */
	ULoggerSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	/**
	 * @brief Should the screen logs remain in the 'NO_LOGGING' build?
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Config, Category="Build",
		meta=(ShowOnlyInnerProperties))
	bool bScreenLog;

	/**
	 * @brief Should the console logs remain in the 'NO_LOGGING' build?
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Config, Category="Build",
		meta=(ShowOnlyInnerProperties))
	bool bConsoleLog;
	
	/**
	 * @brief Settings for the Log category.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Config, Category="Colors",
		meta=(ShowOnlyInnerProperties))
	FLoggerCategorySettings Log;

	/** 
	 * @brief Settings for the Warn category.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Config, Category="Colors",
		meta=(ShowOnlyInnerProperties))
	FLoggerCategorySettings Warn;

	/** 
	 * @brief Settings for the Error category.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Config, Category="Colors",
		meta=(ShowOnlyInnerProperties))
	FLoggerCategorySettings Error;
};
