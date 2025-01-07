// ItemInfo.cpp

#include "SurvivalGame/Public/Data/PrimaryData/ItemInfo.h"

UItemInfo::UItemInfo()
{
    // Initialize asset references
    ItemIcon = nullptr;
    ItemMesh = nullptr;
    ItemSkeletalMesh = nullptr;
    ItemParticle = nullptr;
    ItemPickupSound = nullptr;
    ItemUseSound = nullptr;
    ItemDropSound = nullptr;

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
    NewItem.bIsEquippable = bIsEquippable;
    
    // Set tool and weapon types if equippable
    if (bIsEquippable)
    {
        NewItem.ToolType = ToolType;
        NewItem.WeaponType = WeaponType;
        NewItem.ArmorType = ArmorType;
    }
    
    // Set economic properties
    NewItem.ItemValue = BaseValue;
    
    // Set special properties
    NewItem.bIsQuestItem = bIsQuestItem;
    NewItem.bIsUnique = bIsUnique;
    
    // Copy tags and modifiers
    NewItem.ItemTags = ItemTags;
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
    // Ensure condition is within valid range
    const float ClampedCondition = FMath::Clamp(Condition, 0.0f, 1.0f);
    
    // Calculate base value with condition modifier
    float AdjustedValue = BaseValue * FMath::Max(0.1f, ClampedCondition);
    
    // Apply rarity modifier
    const float RarityMultipliers[] = { 1.0f, 1.5f, 2.5f, 4.0f, 8.0f };
    if (static_cast<int32>(ItemRarity) > 0 && static_cast<int32>(ItemRarity) <= 5)
    {
        AdjustedValue *= RarityMultipliers[static_cast<int32>(ItemRarity) - 1];
    }
    
    // Apply additional modifiers
    AdjustedValue *= CalculateValueModifiers();
    
    return FMath::RoundToInt(AdjustedValue);
}

bool UItemInfo::CanBeUsedBy(const FGameplayTagContainer& EntityTags) const
{
    // If no requirements, anyone can use
    if (RequiredTags.IsEmpty() && RequiredLevel <= 1)
    {
        return true;
    }
    
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
    
    // Apply equipment type modifiers
    if (bIsEquippable)
    {
        // Weapons and tools are generally more valuable
        if (WeaponType != E_WeaponType::None || ToolType != E_ToolType::None)
        {
            Modifier *= 1.25f;
        }
        // Armor value modifier
        if (ArmorType != E_ArmorType::None)
        {
            Modifier *= 1.2f;
        }
    }
    
    // Apply modifiers from DefaultModifiers array
    for (const FItemModifier& ItemMod : DefaultModifiers)
    {
        // Add specific modifier calculations based on modifier type
        // This can be expanded based on your game's needs
    }
    
    return Modifier;
}