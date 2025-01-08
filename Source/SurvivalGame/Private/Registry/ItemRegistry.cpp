// ItemRegistry.cpp

#include "SurvivalGame/Public/Registry/ItemRegistry.h"
#include "Engine/AssetManager.h"

UItemRegistry::UItemRegistry()
    : bIsInitialized(false)
{
}

void UItemRegistry::Initialize()
{
    if (bIsInitialized)
    {
        return;
    }

    // Clear any existing registrations
    RegisteredItems.Empty();

    // Load default items
    LoadDefaultItems();

    bIsInitialized = true;
    OnItemRegistryInitialized.Broadcast();
}

bool UItemRegistry::RegisterItem(UItemInfo* ItemInfo)
{
    if (!ItemInfo || !ValidateItemInfo(ItemInfo))
    {
        return false;
    }

    const FName RegistryKey = ItemInfo->GetRegistryKey();

    // Check if item is already registered
    if (RegisteredItems.Contains(RegistryKey))
    {
        UE_LOG(LogTemp, Warning, TEXT("Item with registry key %s is already registered!"), *RegistryKey.ToString());
        return false;
    }

    // Register the item
    RegisteredItems.Add(RegistryKey, ItemInfo);

    // Broadcast event
    OnItemRegistered.Broadcast(RegistryKey);

    return true;
}

FItemStructure UItemRegistry::CreateItemInstance(const FName& RegistryKey, int32 Quantity) const
{
    if (UItemInfo* ItemInfo = GetItemInfo(RegistryKey))
    {
        return ItemInfo->CreateItemInstance(Quantity);
    }

    // Return empty item structure if item not found
    return FItemStructure();
}

TArray<FName> UItemRegistry::GetAllRegisteredItemKeys() const
{
    TArray<FName> Keys;
    RegisteredItems.GetKeys(Keys);
    return Keys;
}

TArray<UItemInfo*> UItemRegistry::GetItemsByType(E_ItemType ItemType) const
{
    TArray<UItemInfo*> Items;
    
    for (const auto& Pair : RegisteredItems)
    {
        if (Pair.Value && Pair.Value->ItemType == ItemType)
        {
            Items.Add(Pair.Value);
        }
    }
    
    return Items;
}

TArray<UItemInfo*> UItemRegistry::GetItemsByCategory(E_ItemCategory ItemCategory) const
{
    TArray<UItemInfo*> Items;
    
    for (const auto& Pair : RegisteredItems)
    {
        if (Pair.Value && Pair.Value->ItemCategory == ItemCategory)
        {
            Items.Add(Pair.Value);
        }
    }
    
    return Items;
}

void UItemRegistry::LoadDefaultItems()
{
    // Create a streamable manager for async loading
    FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

    // Load all default items
    for (const auto& ItemPtr : DefaultItems)
    {
        if (!ItemPtr.IsNull())
        {
            // Load the item synchronously
            UItemInfo* LoadedItem = ItemPtr.LoadSynchronous();
            if (LoadedItem)
            {
                RegisterItem(LoadedItem);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to load default item %s"), *ItemPtr.ToString());
            }
        }
    }
}

bool UItemRegistry::ValidateItemInfo(const UItemInfo* ItemInfo) const
{
    if (!ItemInfo)
    {
        return false;
    }

    // Check for valid item type
    if (ItemInfo->ItemType == E_ItemType::None)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemInfo %s has invalid item type!"), *ItemInfo->GetName());
        return false;
    }

    // Check for valid item category
    if (ItemInfo->ItemCategory == E_ItemCategory::None)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemInfo %s has invalid item category!"), *ItemInfo->GetName());
        return false;
    }

    // Validate stack settings
    if (ItemInfo->bIsStackable && ItemInfo->MaxStackSize <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemInfo %s has invalid stack size!"), *ItemInfo->GetName());
        return false;
    }

    // Validate equipment settings
    if (ItemInfo->bIsEquippable)
    {
        const bool hasValidType = ItemInfo->ToolType != E_ToolType::None ||
                                ItemInfo->WeaponType != E_WeaponType::None ||
                                ItemInfo->ArmorType != E_ArmorType::None;
        
        if (!hasValidType)
        {
            UE_LOG(LogTemp, Warning, TEXT("Equippable item %s has no valid equipment type!"), *ItemInfo->GetName());
            return false;
        }
    }

    return true;
}