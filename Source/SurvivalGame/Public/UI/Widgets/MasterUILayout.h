// MasterUILayout.h
#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonUI/Public/CommonActivatableWidget.h"
#include "CommonUI/Public/Widgets/CommonActivatableWidgetContainer.h"
#include "MasterUILayout.generated.h"

class UCommonActivatableWidgetStack;

/** Defines different types of UI stacks in the game */
UENUM(BlueprintType)
enum class EUIStackType : uint8
{
    HUD         UMETA(DisplayName = "HUD Stack"),
    Inventory   UMETA(DisplayName = "Inventory Stack"),
    Menu        UMETA(DisplayName = "Menu Stack")
};

/** Delegate for UI stack changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIStackChanged, EUIStackType, StackType);

/**
 * @brief Master UI Layout that manages different UI stacks for game HUD, inventory, and menus
 * Handles the organization and management of different UI layers
 */
UCLASS(Abstract, BlueprintType, Blueprintable, meta=(DisplayName = "Master UI Layout", ShortTooltip="Main UI layout manager for the game"))
class SURVIVALGAME_API UMasterUILayout : public UCommonUserWidget
{
    GENERATED_BODY()

public:
    UMasterUILayout(const FObjectInitializer& ObjectInitializer);

    /** Push a widget to specified stack */
    UFUNCTION(BlueprintCallable, Category = "UI|Stack Management", meta=(DisplayName="Push Widget To Stack"))
    bool PushWidgetToStack(UPARAM(meta=(AllowAbstract="false")) UCommonActivatableWidget* Widget, EUIStackType StackType);

    /** Remove top widget from specified stack */
    UFUNCTION(BlueprintCallable, Category = "UI|Stack Management")
    bool PopWidgetFromStack(EUIStackType StackType);

    /** Get current active stack */
    UFUNCTION(BlueprintPure, Category = "UI|Stack Management")
    EUIStackType GetCurrentActiveStack() const { return CurrentActiveStack; }

protected:
    /** Core UI Stacks */
    UPROPERTY(Transient, BlueprintReadOnly, Category="UI|Stacks", meta=(BindWidget))
    UCommonActivatableWidgetStack* GameHUDStack;

    UPROPERTY(Transient, BlueprintReadOnly, Category="UI|Stacks", meta=(BindWidget))
    UCommonActivatableWidgetStack* GameInventoryStack;

    UPROPERTY(Transient, BlueprintReadOnly, Category="UI|Stacks", meta=(BindWidget))
    UCommonActivatableWidgetStack* GameMenuStack;

    /** Stack configuration */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI|Configuration")
    ESlateVisibility DefaultStackVisibility;

    /** Current state */
    UPROPERTY(BlueprintReadOnly, Category="UI|State")
    EUIStackType CurrentActiveStack;

    /** Events */
    UPROPERTY(BlueprintAssignable, Category="UI|Events")
    FOnUIStackChanged OnStackChanged;

    /** Widget lifecycle */
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    /** Utility functions */
    UFUNCTION(BlueprintPure, Category="UI|Utilities")
    UCommonActivatableWidgetStack* GetStackByType(EUIStackType StackType) const;
};