// ItemInfo.cpp

#include "ItemInfo.h"

UItemInfo::UItemInfo()
{
    // Initialize basic properties
    bIsStackable = false;
    MaxStackSize = 1;
    ItemCategory = E_ItemCategory::None;
    ItemType = E_ItemType::Resource;
    ItemRarity = E_ItemRarity::Common;
    WeightClass = E_WeightClass::Light;
    
    // Initialize equipment properties
    bIsConsumable = false;
    bIsEquippable = false;
    ToolType = E_ToolType::None;
    WeaponType = E_WeaponType::None;
    ArmorType = E_ArmorType::None;
    
    // Initialize durability settings
    MaxDurability = 100;
    DurabilityDecayRate = 0.0f;
    
    // Initialize economic properties
    BaseValue = 0;
    SellValueMultiplier = 0.75f;
    
    // Initialize special properties
    bIsQuestItem = false;
    bIsUnique = false;
    RequiredLevel = 1;
}

FPrimaryAssetId UItemInfo::GetPrimaryAssetId() const
{
    // Use the class name and asset name as the primary asset identifier
    return FPrimaryAssetId(FPrimaryAssetType("Item"), GetFName());
}

FItemStructure UItemInfo::CreateItemInstance(int32 Quantity) const
{
    FItemStructure NewItem;
    
    // Set basic properties
    NewItem.ItemName = ItemName;
    NewItem.ItemQuantity = FMath::Clamp(Quantity, 1, bIsStackable ? MaxStackSize : 1);
    NewItem.MaxStackSize = MaxStackSize;
    NewItem.bIsStackable = bIsStackable;
    NewItem.ItemCategory = ItemCategory;
    NewItem.ItemRarity = ItemRarity;
    
    // Set durability
    NewItem.CurrentDurability = MaxDurability;
    NewItem.MaxDurability = MaxDurability;
    NewItem.DurabilityDecayRate = DurabilityDecayRate;
    
    // Set equipment properties
    NewItem.WeightClass = WeightClass;
    NewItem.bIsConsumable = bIsConsumable;
    
    // Set economic properties
    NewItem.ItemValue = BaseValue;
    
    // Set special properties
    NewItem.bIsQuestItem = bIsQuestItem;
    NewItem.bIsUnique = bIsUnique;
    
    // Copy default modifiers
    NewItem.DefaultModifiers = DefaultModifiers;
    NewItem.ItemModifiers = DefaultModifiers;
    
    // Generate unique ID
    NewItem.UniqueInstanceID = FGuid::NewGuid();
    
    // Set initial state
    NewItem.InitialItemState = E_ItemState::Normal;
    NewItem.ItemState = E_ItemState::Normal;
    
    return NewItem;
}

int32 UItemInfo::GetAdjustedValue(float Condition) const
{
    // Calculate base value with condition modifier
    float AdjustedValue = BaseValue * FMath::Max(0.1f, Condition);
    
    // Apply rarity modifier
    switch (ItemRarity)
    {
        case E_ItemRarity::Uncommon:
            AdjustedValue *= 1.5f;
            break;
        case E_ItemRarity::Rare:
            AdjustedValue *= 2.5f;
            break;
        case E_ItemRarity::Epic:
            AdjustedValue *= 4.0f;
            break;
        case E_ItemRarity::Legendary:
            AdjustedValue *= 8.0f;
            break;
        default:
            break;
    }
    
    // Apply additional modifiers
    AdjustedValue *= CalculateValueModifiers();
    
    return FMath::RoundToInt(AdjustedValue);
}

bool UItemInfo::CanBeUsedBy(const FGameplayTagContainer& EntityTags) const
{
    // If no requirements, anyone can use
    if (RequiredTags.IsEmpty())
    {
        return true;
    }
    
    // Check level requirement first
    // Note: You would typically get the entity's level from a component or interface
    // This is just a placeholder check
    // if (EntityLevel < RequiredLevel) return false;
    
    // Check if entity has any required tags
    return EntityTags.HasAny(RequiredTags);
}

int32 UItemInfo::GetSellValue(float Condition) const
{
    return FMath::RoundToInt(GetAdjustedValue(Condition) * SellValueMultiplier);
}

float UItemInfo::CalculateValueModifiers() const
{
    float Modifier = 1.0f;
    
    // Apply quest item modifier
    if (bIsQuestItem)
    {
        Modifier *= 1.5f;
    }
    
    // Apply unique item modifier
    if (bIsUnique)
    {
        Modifier *= 2.0f;
    }
    
    // Apply modifiers from DefaultModifiers array
    for (const FItemModifier& ItemMod : DefaultModifiers)
    {
        // You could add specific modifier calculations here
        // For example, quality modifiers, special attributes, etc.
    }
    
    return Modifier;
}