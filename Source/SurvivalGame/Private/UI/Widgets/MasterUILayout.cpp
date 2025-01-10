// MasterUILayout.cpp
#include "UI/Widgets/MasterUILayout.h"

UMasterUILayout::UMasterUILayout(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , GameHUDStack(nullptr)
    , GameInventoryStack(nullptr)
    , GameMenuStack(nullptr)
    , DefaultStackVisibility(ESlateVisibility::SelfHitTestInvisible)
    , CurrentActiveStack(EUIStackType::HUD)
{
    bIsVariable = false;
}

void UMasterUILayout::NativeConstruct()
{
    Super::NativeConstruct();
    
    // Initialize all UI stacks with proper visibility
    const TArray<UCommonActivatableWidgetStack*> Stacks = { GameHUDStack, GameInventoryStack, GameMenuStack };
    
    for (UCommonActivatableWidgetStack* Stack : Stacks)
    {
        if (ensureMsgf(Stack, TEXT("UI Stack is null in %s. Check widget blueprint for properly set stack names."), *GetName()))
        {
            Stack->SetVisibility(DefaultStackVisibility);
        }
    }
}

void UMasterUILayout::NativeDestruct()
{
    Super::NativeDestruct();
    
    GameHUDStack = nullptr;
    GameInventoryStack = nullptr;
    GameMenuStack = nullptr;
}

bool UMasterUILayout::PushWidgetToStack(UCommonActivatableWidget* Widget, EUIStackType StackType)
{
    if (!ensureMsgf(Widget, TEXT("Attempted to push null widget to stack in %s"), *GetName()))
    {
        return false;
    }

    UCommonActivatableWidgetStack* TargetStack = GetStackByType(StackType);
    if (!ensureMsgf(TargetStack, TEXT("Invalid stack type specified in %s"), *GetName()))
    {
        return false;
    }

    // Activate the widget and add it to the stack
    Widget->AddToViewport();
    CurrentActiveStack = StackType;
    OnStackChanged.Broadcast(StackType);
    
    return true;
}

bool UMasterUILayout::PopWidgetFromStack(EUIStackType StackType)
{
    UCommonActivatableWidgetStack* TargetStack = GetStackByType(StackType);
    if (!ensureMsgf(TargetStack, TEXT("Invalid stack type specified in %s"), *GetName()))
    {
        return false;
    }

    if (UCommonActivatableWidget* ActiveWidget = Cast<UCommonActivatableWidget>(TargetStack->GetActiveWidget()))
    {
        // Deactivate and remove the widget
        ActiveWidget->RemoveFromParent();
        return true;
    }

    return false;
}

UCommonActivatableWidgetStack* UMasterUILayout::GetStackByType(EUIStackType StackType) const
{
    switch (StackType)
    {
        case EUIStackType::HUD:
            return GameHUDStack;
        case EUIStackType::Inventory:
            return GameInventoryStack;
        case EUIStackType::Menu:
            return GameMenuStack;
        default:
            ensureMsgf(false, TEXT("Invalid stack type requested in %s"), *GetName());
            return nullptr;
    }
}