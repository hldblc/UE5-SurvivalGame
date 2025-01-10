// SurvivalPlayerController.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/Widgets/MasterUILayout.h"
#include "SurvivalPlayerController.generated.h"

/** Delegate for UI initialization */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUIInitialized);

/**
 * @brief Main player controller class handling UI initialization and management
 * Manages UI states and input modes for the game
 */
UCLASS(Config=Game, BlueprintType, Blueprintable, meta=(ShortTooltip="Main player controller class for the survival game"))
class SURVIVALGAME_API ASurvivalPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ASurvivalPlayerController();

    /** Input mode management */
    UFUNCTION(BlueprintCallable, Category="UI|Input")
    void SetUIInputMode(bool bUIMode);

    /** UI access */
    UFUNCTION(BlueprintPure, Category="UI")
    UMasterUILayout* GetRootLayout() const { return RootLayout; }

    /** State queries */
    UFUNCTION(BlueprintPure, Category="UI")
    bool IsUIInitialized() const { return bIsUIInitialized; }

protected:
    virtual void BeginPlay() override;

    /** UI References */
    UPROPERTY(Transient, BlueprintReadOnly, Category="UI")
    UMasterUILayout* RootLayout;

    /** Configuration */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI|Setup", meta=(BlueprintBaseOnly))
    TSubclassOf<UMasterUILayout> MasterUIClass;

    /** Input settings */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI|Input")
    bool bAutoEnableUIInput;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI|Input")
    bool bLockMouseToViewport;

    UPROPERTY(EditDefaultsOnly, Category="UI|Input", meta=(AllowPrivateAccess="true"))
    bool bHideCursorDuringCapture;

    /** State */
    UPROPERTY(BlueprintReadOnly, Category="UI|State")
    uint8 bIsUIInitialized : 1;

    /** Events */
    UPROPERTY(BlueprintAssignable, Category="UI|Events")
    FOnUIInitialized OnUIInitialized;

private:
    /** Internal functions */
    void InitializeUILayout();
    uint8 bIsLocalController : 1;
};