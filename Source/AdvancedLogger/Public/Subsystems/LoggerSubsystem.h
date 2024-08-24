// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LoggerSubsystem.generated.h"

#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
    : (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
    : (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
    : (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
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
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ADVANCEDLOGGER_API ULoggerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    
};
