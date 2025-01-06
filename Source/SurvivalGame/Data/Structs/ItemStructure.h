// ItemStructure.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "ItemEnums.h"
#include "ItemStructure.generated.h"

/**
 * @brief Structure representing an item modifier (enchantments, effects, etc.)
 */
USTRUCT(BlueprintType)
struct FItemModifier
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
    FString ModifierName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
    float ModifierValue;

    FItemModifier() : ModifierValue(0.0f) {}
};

/**
 * @brief Structure representing runtime item data
 */
USTRUCT(BlueprintType)
struct FItemStructure : public FTableRowBase
{
    GENERATED_BODY()

    /** Unique key for item identification */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName RegistryKey;

    /** Name of the item */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemName;

    /** Current quantity in stack */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemQuantity;

    /** Maximum stack size */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 MaxStackSize;

    /** Whether item can be stacked */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool bIsStackable;

    /** Unique instance ID for this specific item */
    UPROPERTY(BlueprintReadOnly, Category = "Item")
    FGuid UniqueInstanceID;

    /** Item category */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    E_ItemCategory ItemCategory;

    /** Item rarity */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    E_ItemRarity ItemRarity;

    /** Current durability */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    int32 CurrentDurability;

    /** Maximum durability */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    int32 MaxDurability;

    /** Rate at which durability decays */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    float DurabilityDecayRate;

    /** Whether item can be destroyed */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    bool bIsDestroyable;

    /** Current ammunition */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
    int32 CurrentAmmo;

    /** Maximum ammunition */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
    int32 MaxAmmo;

    /** Whether item uses ammunition */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
    bool bUsesAmmo;

    /** Whether item is consumable */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    bool bIsConsumable;

    /** Nutrition value if consumable */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    int32 NutritionValue;

    /** Toxicity level */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    int32 Toxicity;

    /** Time until item decays */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    float DecayTime;

    /** Weight class affecting movement */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    E_WeightClass WeightClass;

    /** Whether item can be used as fire source */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    bool bIsFireSource;

    /** Temperature effect on player */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float TemperatureEffect;

    /** Warmth rating for cold protection */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float WarmthRating;

    /** Whether item can burn */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    bool bIsFlammable;

    /** How long item can burn */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float BurnTime;

    /** Special ability description */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
    FString SpecialAbility;

    /** Base value in currency */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economic")
    int32 ItemValue;

    /** Whether item is quest-related */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
    bool bIsQuestItem;

    /** Whether item is unique */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
    bool bIsUnique;

    /** Whether item is a container */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
    bool bIsContainer;

    /** Container capacity */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
    int32 ContainerSize;

    /** Default modifiers */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    TArray<FItemModifier> DefaultModifiers;

    /** Current modifiers */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    TArray<FItemModifier> ItemModifiers;

    /** Initial state */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    E_ItemState InitialItemState;

    /** Current state */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    E_ItemState ItemState;

    /** Default constructor */
    FItemStructure();

    /** Initialize item structure from another structure */
    void InitializeFromData(const FItemStructure& LoadedItem);

    /** Get current condition as percentage */
    FORCEINLINE float GetConditionPercent() const
    {
        return MaxDurability > 0 ? (float)CurrentDurability / (float)MaxDurability : 1.0f;
    }

    /** Check if item is empty/invalid */
    FORCEINLINE bool IsEmpty() const
    {
        return RegistryKey.IsNone();
    }

    /** Equality operator */
    bool operator==(const FItemStructure& Other) const;
};