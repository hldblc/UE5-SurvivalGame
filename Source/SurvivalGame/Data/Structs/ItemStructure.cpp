// ItemStructure.cpp

#include "ItemStructure.h"

FItemStructure::FItemStructure()
    : RegistryKey(NAME_None)
    , ItemQuantity(1)
    , MaxStackSize(1)
    , bIsStackable(false)
    , UniqueInstanceID(FGuid::NewGuid())
    , ItemCategory(E_ItemCategory::None)
    , ItemRarity(E_ItemRarity::Common)
    , CurrentDurability(100)
    , MaxDurability(100)
    , DurabilityDecayRate(0.0f)
    , bIsDestroyable(true)
    , CurrentAmmo(0)
    , MaxAmmo(0)
    , bUsesAmmo(false)
    , bIsConsumable(false)
    , NutritionValue(0)
    , Toxicity(0)
    , DecayTime(0.0f)
    , WeightClass(E_WeightClass::Light)
    , bIsFireSource(false)
    , TemperatureEffect(0.0f)
    , WarmthRating(0.0f)
    , bIsFlammable(false)
    , BurnTime(0.0f)
    , ItemValue(0)
    , bIsQuestItem(false)
    , bIsUnique(false)
    , bIsContainer(false)
    , ContainerSize(0)
    , InitialItemState(E_ItemState::Normal)
    , ItemState(E_ItemState::Normal)
{
    // Initialize arrays with empty default values
    DefaultModifiers = TArray<FItemModifier>();
    ItemModifiers = TArray<FItemModifier>();
}

void FItemStructure::InitializeFromData(const FItemStructure& LoadedItem)
{
    // Copy all properties from the loaded item
    *this = LoadedItem;

    // Generate a new unique ID for this instance
    UniqueInstanceID = FGuid::NewGuid();

    // Set current state to initial state
    ItemState = LoadedItem.InitialItemState;

    // Copy modifiers
    DefaultModifiers = LoadedItem.DefaultModifiers;
    ItemModifiers = LoadedItem.DefaultModifiers;  // Start with default modifiers

    // Set current values to maximum values for new items
    CurrentDurability = MaxDurability;
    if (bUsesAmmo)
    {
        CurrentAmmo = MaxAmmo;
    }
}

bool FItemStructure::operator==(const FItemStructure& Other) const
{
    // Items are considered equal if they have the same unique ID
    // This ensures each item instance is unique, even if they're the same type
    return UniqueInstanceID == Other.UniqueInstanceID;
}