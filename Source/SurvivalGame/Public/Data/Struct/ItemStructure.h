// ItemStructure.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SurvivalGame/Public/Enums/ItemEnums.h"
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

    /** Basic Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName RegistryKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 ItemQuantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 MaxStackSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool bIsStackable;

    UPROPERTY(BlueprintReadOnly, Category = "Item")
    FGuid UniqueInstanceID;

    /** Classification */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    E_ItemCategory ItemCategory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    E_ItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    E_ItemRarity ItemRarity;

    /** Equipment Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    bool bIsEquippable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    E_ToolType ToolType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    E_WeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    E_ArmorType ArmorType;

    /** Durability */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    int32 CurrentDurability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    int32 MaxDurability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    float DurabilityDecayRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    bool bIsDestroyable;

    /** Ammunition */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
    bool bUsesAmmo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
    int32 CurrentAmmo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition")
    int32 MaxAmmo;

    /** Consumable Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    bool bIsConsumable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    int32 NutritionValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    int32 Toxicity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumable")
    float DecayTime;

    /** Physical Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    E_WeightClass WeightClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    bool bIsFireSource;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float TemperatureEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float WarmthRating;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    bool bIsFlammable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float BurnTime;

    /** Special Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
    FString SpecialAbility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
    bool bIsQuestItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
    bool bIsUnique;

    /** Container Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
    bool bIsContainer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
    int32 ContainerSize;

    /** Tags and Modifiers */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
    FGameplayTagContainer ItemTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    TArray<FItemModifier> DefaultModifiers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    TArray<FItemModifier> ItemModifiers;

    /** Economic Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economic")
    int32 ItemValue;

    /** State Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    E_ItemState InitialItemState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    E_ItemState ItemState;

    /** Constructor */
    FItemStructure();

    /** Initialize from template */
    void InitializeFromData(const FItemStructure& LoadedItem);

    /** Utility Functions */
    FORCEINLINE float GetConditionPercent() const
    {
        return MaxDurability > 0 ? (float)CurrentDurability / (float)MaxDurability : 1.0f;
    }

    FORCEINLINE bool IsEmpty() const
    {
        return RegistryKey.IsNone();
    }

    /** Operators */
    bool operator==(const FItemStructure& Other) const;
};