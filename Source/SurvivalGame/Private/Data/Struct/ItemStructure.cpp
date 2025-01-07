// ItemStructure.cpp

#include "SurvivalGame/Public/Data/Struct/ItemStructure.h"

FItemStructure::FItemStructure()
{
    // Initialize Core Properties
    UniqueInstanceID = FGuid::NewGuid();
    RegistryKey = NAME_None;
    ItemType = E_ItemType::None;
    ItemCategory = E_ItemCategory::None;
    ItemRarity = E_ItemRarity::None;

    // Initialize Stack Properties
    bIsStackable = false;
    MaxStackSize = 1;
    ItemQuantity = 1;

    // Initialize Equipment Properties
    bIsEquippable = false;
    ToolType = E_ToolType::None;
    WeaponType = E_WeaponType::None;
    ArmorType = E_ArmorType::None;

    // Initialize Durability Properties
    bHasDurability = false;
    CurrentDurability = 100;
    MaxDurability = 100;
    DurabilityDecayRate = 0.0f;
    bIsDestroyable = true;

    // Initialize Physical Properties
    WeightClass = E_WeightClass::None;

    // Initialize Special Properties
    bIsQuestItem = false;
    bIsUnique = false;

    // Initialize State Properties
    InitialItemState = E_ItemState::None;
    ItemState = E_ItemState::None;

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

    // Set current state to initial state
    ItemState = LoadedItem.InitialItemState;

    // Copy modifiers
    DefaultModifiers = LoadedItem.DefaultModifiers;
    ItemModifiers = LoadedItem.DefaultModifiers;  // Start with default modifiers

    // Set current values to maximum values for new items
    if (bHasDurability)
    {
        CurrentDurability = MaxDurability;
    }
}

bool FItemStructure::operator==(const FItemStructure& Other) const
{
    return UniqueInstanceID == Other.UniqueInstanceID;
}