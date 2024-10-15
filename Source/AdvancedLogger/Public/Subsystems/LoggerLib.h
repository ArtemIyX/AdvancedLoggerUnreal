// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LoggerLib.generated.h"

#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
    : (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
    : (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
    : (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
    : TEXT("[Standalone] "))

#define NETMODE(World) (((GEngine == nullptr) || (World == nullptr)) ? TEXT("") \
	: (GEngine->GetNetMode(World) == NM_Client) ? TEXT("[Client] ") \
	: (GEngine->GetNetMode(World) == NM_ListenServer) ? TEXT("[ListenServer] ") \
	: (GEngine->GetNetMode(World) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
	: TEXT("[Standalone] "))

#if PLATFORM_WINDOWS

#if _MSC_VER
#define FUNC_NAME    TEXT(__FUNCTION__)
#else
	    #define FUNC_NAME    TEXT(__func__)
#endif

#else
	#define FUNC_NAME    TEXT("")
#endif
#define TRACE(Category, Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_CYAN);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    if (Msg == "") \
    { \
        UE_LOG(Category, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *GetNameSafe(this));\
    } \
    else \
    { \
        UE_LOG(Category, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg);\
    } \
    CLEAR_WARN_COLOR();\
}

#define TRACESTATIC(Category, Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_CYAN);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(Category, Log, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACEWARN(Category, Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_YELLOW);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(Category, Warning, TEXT("**WARNING** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACEERROR(Category, Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_RED);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(Category, Error, TEXT("**ERROR** %s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define SCREENDEBUG(Format, ...) \
{ \
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    if (Msg == "") \
    { \
        TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
        FCString::Sprintf(StdMsg, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *GetNameSafe(this)); \
        GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Emerald, StdMsg); \
    } \
    else \
    { \
        GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Emerald, Msg); \
    } \
}

#define SCREENDEBUGT(Format, ...) \
{ \
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    if (Msg == "") \
    { \
    TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
    FCString::Sprintf(StdMsg, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *GetNameSafe(this)); \
        GEngine->AddOnScreenDebugMessage(-1, 0.0f,FColor::Emerald, StdMsg); \
    } \
    else \
    { \
        GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Emerald, Msg); \
    } \
}

/**
 * @brief Enum representing console color options for logging output.
 */
UENUM(Blueprintable, BlueprintType)
enum class EConsoleColor : uint8
{
	COLOR_BLACK UMETA(DisplayName = "Black"),              /**< Black color for console output. */
    COLOR_DARK_RED UMETA(DisplayName = "Dark Red"),        /**< Dark red color for console output. */
    COLOR_DARK_GREEN UMETA(DisplayName = "Dark Green"),    /**< Dark green color for console output. */
    COLOR_DARK_BLUE UMETA(DisplayName = "Dark Blue"),      /**< Dark blue color for console output. */
    COLOR_DARK_YELLOW UMETA(DisplayName = "Dark Yellow"),  /**< Dark yellow color for console output. */
    COLOR_DARK_CYAN UMETA(DisplayName = "Dark Cyan"),      /**< Dark cyan color for console output. */
    COLOR_DARK_PURPLE UMETA(DisplayName = "Dark Purple"),  /**< Dark purple color for console output. */
    COLOR_GRAY UMETA(DisplayName = "Gray"),                /**< Gray color for console output. */
    COLOR_RED UMETA(DisplayName = "Red"),                  /**< Red color for console output. */
    COLOR_GREEN UMETA(DisplayName = "Green"),              /**< Green color for console output. */
    COLOR_BLUE UMETA(DisplayName = "Blue"),                /**< Blue color for console output. */
    COLOR_YELLOW UMETA(DisplayName = "Yellow"),            /**< Yellow color for console output. */
    COLOR_CYAN UMETA(DisplayName = "Cyan"),                /**< Cyan color for console output. */
    COLOR_PURPLE UMETA(DisplayName = "Purple"),            /**< Purple color for console output. */
    COLOR_WHITE UMETA(DisplayName = "White"),              /**< White color for console output. */
    COLOR_NONE UMETA(DisplayName = "None"),                /**< No color, default console color. */
};


/**
 * @brief Subsystem class for logging messages in the console and on the screen.
 * 
 * This class provides methods to log messages at various levels (Log, Warning, Error)
 * both on the screen and in the console with specific colors.
 */
UCLASS(Blueprintable, BlueprintType)
class ADVANCEDLOGGER_API ULoggerLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
protected:
	/**
	* @brief Sets the console text color.
	* 
	* @param InColor The color to set the console text to. Defaults to EConsoleColor::COLOR_NONE.
	*/
	static void SetConsoleColor(EConsoleColor InColor = EConsoleColor::COLOR_NONE);

	/**
	* @brief Gets default object for ULoggerSettings
	* @see ULoggerSettings
	*/
	static const class ULoggerSettings* GetSettings();

	static FString MakeSidePrefix(UWorld* InWorld);
public:

	/**
	 * @brief Logs a message to the screen and optionally to the console.
	 * 
	 * @param InContextObject The context object, typically the calling UObject.
	 * @param InMessage The message to log. Defaults to "Log Message".
	 * @param InKey The key for the on-screen message. Defaults to 1.
	 * @param InTime The duration the message stays on the screen. Defaults to 5.0f seconds.
	 * @param bConsoleLog If true, logs the message to the console as well. Defaults to false.
	 */
	UFUNCTION(BlueprintCallable, meta=(WorldContext=InContextObject, Keywords="Log String Logger Print String Text Console"))
	static void Log(const UObject* InContextObject,
	                 FString InMessage = TEXT("Log Message"),
	                 int32 InKey = 1,
	                 float InTime = 5.0f,
	                 bool bConsoleLog = false);

	/**
	 * @brief Logs a message to the screen and optionally to the console.
	 * 
	 * @note Function can be use in UObject's
	 * 
	 * @param InMessage The message to log. Defaults to "Log Message".
	 * @param InKey The key for the on-screen message. Defaults to 1.
	 * @param InTime The duration the message stays on the screen. Defaults to 5.0f seconds.
	 * @param bConsoleLog If true, logs the message to the console as well. Defaults to false.
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Log String Logger Print String Text Console"))
	static void LogStatic(
					 FString InMessage = TEXT("Log Message"),
					 int32 InKey = 1,
					 float InTime = 5.0f,
					 bool bConsoleLog = false);

	/**
	 * @brief Logs a warning message to the screen and optionally to the console.
	 * 
	 * @param InContextObject The context object, typically the calling UObject.
	 * @param InMessage The warning message to log. Defaults to "Warning Message".
	 * @param InKey The key for the on-screen message. Defaults to 2.
	 * @param InTime The duration the message stays on the screen. Defaults to 5.0f seconds.
	 * @param bConsoleLog If true, logs the warning message to the console as well. Defaults to false.
	 */
	UFUNCTION(BlueprintCallable, meta=(WorldContext=InContextObject, Keywords="Warn Warning Logger Print String Text Console"))
	static void Warning(const UObject* InContextObject,
	                     FString InMessage = TEXT("Warning Message"),
	                     int32 InKey = 2,
	                     float InTime = 5.0f,
	                     bool bConsoleLog = false);

	/**
	 * @brief Logs a warning message to the screen and optionally to the console.
	 *
	 * @note Function can be use in UObject's
	 * 
	 * @param InMessage The warning message to log. Defaults to "Warning Message".
	 * @param InKey The key for the on-screen message. Defaults to 2.
	 * @param InTime The duration the message stays on the screen. Defaults to 5.0f seconds.
	 * @param bConsoleLog If true, logs the warning message to the console as well. Defaults to false.
	 */
	UFUNCTION(BlueprintCallable, meta=(WorldContext=InContextObject, Keywords="Warn Warning Logger Print String Text Console"))
	static void WarningStatic(
						 FString InMessage = TEXT("Warning Message"),
						 int32 InKey = 2,
						 float InTime = 5.0f,
						 bool bConsoleLog = false);
	/**
	* @brief Logs an error message to the screen and optionally to the console.
	* 
	* @param InContextObject The context object, typically the calling UObject.
	* @param InMessage The error message to log. Defaults to "Error Message".
	* @param InKey The key for the on-screen message. Defaults to 3.
	* @param InTime The duration the message stays on the screen. Defaults to 5.0f seconds.
	* @param bConsoleLog If true, logs the error message to the console as well. Defaults to false.
	*/
	UFUNCTION(BlueprintCallable, meta=(WorldContext=InContextObject, Keywords="Err Error Logger Print String Text Console"))
	static void Error(const UObject* InContextObject,
	                   FString InMessage = TEXT("Error Message"),
	                   int32 InKey = 3,
	                   float InTime = 5.0f,
	                   bool bConsoleLog = false);

	/**
	* @brief Logs an error message to the screen and optionally to the console.
	*
	* @note Function can be use in UObject's
	* 
	* @param InMessage The error message to log. Defaults to "Error Message".
	* @param InKey The key for the on-screen message. Defaults to 3.
	* @param InTime The duration the message stays on the screen. Defaults to 5.0f seconds.
	* @param bConsoleLog If true, logs the error message to the console as well. Defaults to false.
	*/
	UFUNCTION(BlueprintCallable, meta=(Keywords="Err Error Logger Print String Text Console"))
	static void ErrorStatic(
					   FString InMessage = TEXT("Error Message"),
					   int32 InKey = 3,
					   float InTime = 5.0f,
					   bool bConsoleLog = false);

	/**
	 * @brief Displays a message on the screen with a specified color and duration.
	 * 
	 * @param InContextObject The context object, typically the calling UObject.
	 * @param InMessage The message to display. Defaults to "Screen message".
	 * @param InKey The key for the on-screen message. Defaults to 1.
	 * @param InColor The color of the on-screen message. Defaults to white (FColor(255, 255, 255, 255)).
	 * @param InTime The duration the message stays on the screen. Defaults to 5.0f seconds.
	 */
	UFUNCTION(BlueprintCallable, meta=(WorldContext=InContextObject, Keywords="Log String Logger Screen Message Print String Text Console"))
	static void ScreenMessage(const UObject* InContextObject,
	                           FString InMessage = FString(TEXT("Screen message")),
	                           int32 InKey = 1,
	                           FLinearColor InColor = FLinearColor(255, 255, 255, 255),
	                           float InTime = 5.0f);

	/**
	 * @brief Displays a message on the screen with a specified color and duration.
	 * 
	 * @note Function can be use in UObject's
	 *
	 * @param InMessage The message to display. Defaults to "Screen message".
	 * @param InKey The key for the on-screen message. Defaults to 1.
	 * @param InColor The color of the on-screen message. Defaults to white (FColor(255, 255, 255, 255)).
	 * @param InTime The duration the message stays on the screen. Defaults to 5.0f seconds.
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Log String Logger Screen Message Print String Text Console"))
	static void ScreenMessageStatic(
							   FString InMessage = FString(TEXT("Screen message")),
							   int32 InKey = 1,
							   FLinearColor InColor = FLinearColor(255, 255, 255, 255),
							   float InTime = 5.0f);

	/**
	 * @brief Logs a message to the console with a specified color.
	 * 
	 * @param InContextObject The context object, typically the calling UObject.
	 * @param InMessage The message to log to the console. Defaults to "Console message".
	 * @param InColor The color of the console message. Defaults to EConsoleColor::COLOR_NONE.
	 */
	UFUNCTION(BlueprintCallable, meta=(WorldContext=InContextObject, Keywords="Console Log Logger Screen Message Print String Text"))
	static void ConsoleLog(const UObject* InContextObject,
	                        FString InMessage = FString(TEXT("Console message")),
	                        EConsoleColor InColor = EConsoleColor::COLOR_NONE);

	/**
	 * @brief Logs a message to the console with a specified color.
	 *
	 * @note Function can be use in UObject's
	 * 
	 * @param InMessage The message to log to the console. Defaults to "Console message".
	 * @param InColor The color of the console message. Defaults to EConsoleColor::COLOR_NONE.
	 */
	UFUNCTION(BlueprintCallable, meta=(Keywords="Console Log Logger Screen Message Print String Text"))
	static void ConsoleLogStatic(
							FString InMessage = FString(TEXT("Console message")),
							EConsoleColor InColor = EConsoleColor::COLOR_NONE);

};
