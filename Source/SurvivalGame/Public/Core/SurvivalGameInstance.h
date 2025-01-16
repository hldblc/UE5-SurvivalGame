// SurvivalGameInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Registry/ItemRegistry.h"
#include "UI/Widgets//MasterUILayout.h"
#include "SurvivalGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRootLayoutChanged, UMasterUILayout*, NewLayout);

/**
 * @brief Game instance for managing global game state and systems
 * Handles core game systems like inventory, UI, and other global states
 */
UCLASS(Config=Game)
class SURVIVALGAME_API USurvivalGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    USurvivalGameInstance();
    
    virtual void Init() override;

    /** System Access */
    
    /** Get the item registry */
    UFUNCTION(BlueprintPure, Category = "Systems|Items", meta=(DisplayName="Get Item Registry"))
    FORCEINLINE UItemRegistry* GetItemRegistry() const { return ItemRegistry; }

    /** Get the main UI layout */
    UFUNCTION(BlueprintPure, Category = "Systems|UI", meta=(DisplayName="Get UI Root Layout"))
    FORCEINLINE UMasterUILayout* GetRootLayout() const { return RootLayout; }

    /** Set the root layout with proper notification */
    UFUNCTION(BlueprintCallable, Category = "Systems|UI")
    void SetRootLayout(UMasterUILayout* NewLayout);

    /** Static accessor for GameInstance */
    UFUNCTION(BlueprintPure, Category = "Systems", meta = (DisplayName = "Get Survival Game Instance", WorldContext = "WorldContextObject"))
    static USurvivalGameInstance* Get(const UObject* WorldContextObject);

    /** Static accessor for UI Layout */
    UFUNCTION(BlueprintPure, Category = "Systems|UI", meta = (DisplayName = "Get UI Root Layout", WorldContext = "WorldContextObject"))
    static UMasterUILayout* GetUILayout(const UObject* WorldContextObject);

protected:
    /** Core Systems */
    
    /** The item registry */
    UPROPERTY(Transient)
    TObjectPtr<UItemRegistry> ItemRegistry;

    /** The main UI layout */
    UPROPERTY(Transient)
    TObjectPtr<UMasterUILayout> RootLayout;

    /** System Initialization */
    
    /** Initialize all game systems */
    virtual void InitializeSystems();

    /** Initialize the UI system */
    virtual void InitializeUISystem();

public:
    /** Delegates */
    
    /** Broadcast when root layout changes */
    UPROPERTY(BlueprintAssignable, Category = "Systems|UI")
    FOnRootLayoutChanged OnRootLayoutChanged;

protected:
    /** Configuration */
    
    /** Class to use for the root UI layout */
    UPROPERTY(EditDefaultsOnly, Category = "UI Configuration")
    TSubclassOf<UMasterUILayout> RootLayoutClass;
};