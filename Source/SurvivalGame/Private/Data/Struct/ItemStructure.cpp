// ItemStructure.cpp

#include "SurvivalGame/Public/Data/Struct/ItemStructure.h"

FItemStructure::FItemStructure()
{
    // Basic Properties
    RegistryKey = NAME_None;
    ItemQuantity = 1;
    MaxStackSize = 1;
    bIsStackable = false;
    UniqueInstanceID = FGuid::NewGuid();

    // Classification
    ItemCategory = E_ItemCategory::None;
    ItemType = E_ItemType::Resource;
    ItemRarity = E_ItemRarity::Common;

    // Equipment Properties
    bIsEquippable = false;
    ToolType = E_ToolType::None;
    WeaponType = E_WeaponType::None;
    ArmorType = E_ArmorType::None;

    // Durability
    CurrentDurability = 100;
    MaxDurability = 100;
    DurabilityDecayRate = 0.0f;
    bIsDestroyable = true;

    // Ammunition
    bUsesAmmo = false;
    CurrentAmmo = 0;
    MaxAmmo = 0;

    // Consumable Properties
    bIsConsumable = false;
    NutritionValue = 0;
    Toxicity = 0;
    DecayTime = 0.0f;

    // Physical Properties
    WeightClass = E_WeightClass::Light;
    bIsFireSource = false;
    TemperatureEffect = 0.0f;
    WarmthRating = 0.0f;
    bIsFlammable = false;
    BurnTime = 0.0f;

    // Special Properties
    bIsQuestItem = false;
    bIsUnique = false;

    // Container Properties
    bIsContainer = false;
    ContainerSize = 0;

    // Economic Properties
    ItemValue = 0;

    // State Properties
    InitialItemState = E_ItemState::Normal;
    ItemState = E_ItemState::Normal;

    // Initialize Arrays
    DefaultModifiers = TArray<FItemModifier>();
    ItemModifiers = TArray<FItemModifier>();
}

void FItemStructure::InitializeFromData(const FItemStructure& LoadedItem)
{
    // Copy all properties
    *this = LoadedItem;

    // Generate new unique ID
    UniqueInstanceID = FGuid::NewGuid();

    // Initialize state
    ItemState = LoadedItem.InitialItemState;

    // Copy modifiers
    DefaultModifiers = LoadedItem.DefaultModifiers;
    ItemModifiers = LoadedItem.DefaultModifiers;  // Start with default modifiers

    // Set current values
    CurrentDurability = MaxDurability;
    if (bUsesAmmo)
    {
        CurrentAmmo = MaxAmmo;
    }

    // Handle additional initialization based on item type
    if (bIsEquippable)
    {
        CurrentDurability = MaxDurability;
    }

    if (bIsConsumable)
    {
        // Initialize decay timer if needed
        if (DecayTime > 0.0f)
        {
            // Set up decay logic here if needed
        }
    }
}

bool FItemStructure::operator==(const FItemStructure& Other) const
{
    return UniqueInstanceID == Other.UniqueInstanceID;
}