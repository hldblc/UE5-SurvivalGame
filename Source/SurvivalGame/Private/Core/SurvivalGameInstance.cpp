// SurvivalGameInstance.cpp

#include "Core/SurvivalGameInstance.h"
#include "Kismet/GameplayStatics.h"

USurvivalGameInstance::USurvivalGameInstance()
{
    // Set default values
    RootLayoutClass = UMasterUILayout::StaticClass();
}

void USurvivalGameInstance::Init()
{
    Super::Init();

    // Initialize core systems
    InitializeSystems();
    InitializeUISystem();
}

void USurvivalGameInstance::InitializeSystems()
{
    // Create and initialize the item registry
    ItemRegistry = NewObject<UItemRegistry>(this);
    if (ensure(ItemRegistry))
    {
        ItemRegistry->Initialize();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create ItemRegistry in %s"), *GetName());
    }
}

void USurvivalGameInstance::InitializeUISystem()
{
    // Create the main UI layout if we have a valid class
    if (ensure(RootLayoutClass))
    {
        RootLayout = CreateWidget<UMasterUILayout>(this, RootLayoutClass);
        if (ensure(RootLayout))
        {
            // Additional initialization if needed
            OnRootLayoutChanged.Broadcast(RootLayout);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create RootLayout widget in %s"), *GetName());
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RootLayoutClass is not set in %s"), *GetName());
    }
}

void USurvivalGameInstance::SetRootLayout(UMasterUILayout* NewLayout)
{
    if (RootLayout != NewLayout)
    {
        RootLayout = NewLayout;
        OnRootLayoutChanged.Broadcast(NewLayout);
    }
}

USurvivalGameInstance* USurvivalGameInstance::Get(const UObject* WorldContextObject)
{
    if (WorldContextObject)
    {
        if (UWorld* World = WorldContextObject->GetWorld())
        {
            return Cast<USurvivalGameInstance>(World->GetGameInstance());
        }
    }
    return nullptr;
}

UMasterUILayout* USurvivalGameInstance::GetUILayout(const UObject* WorldContextObject)
{
    if (USurvivalGameInstance* GameInstance = Get(WorldContextObject))
    {
        return GameInstance->GetRootLayout();
    }
    return nullptr;
}