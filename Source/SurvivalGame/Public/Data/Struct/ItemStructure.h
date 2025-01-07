// ItemStructure.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SurvivalGame/Public/Enums/ItemEnums.h"
#include "ItemStructure.generated.h"

class UItemInfo;

/**
 * @brief Structure representing an item modifier
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

    /** Core Properties */
    UPROPERTY(BlueprintReadOnly, Category = "Core")
    FGuid UniqueInstanceID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
    FName RegistryKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
    TSoftObjectPtr<UItemInfo> ItemAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
    E_ItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
    E_ItemCategory ItemCategory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
    E_ItemRarity ItemRarity;

    /** Stack Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack")
    bool bIsStackable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack")
    int32 MaxStackSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack")
    int32 ItemQuantity;

    /** Equipment Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    bool bIsEquippable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    E_ToolType ToolType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    E_WeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
    E_ArmorType ArmorType;

    /** Durability Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    bool bHasDurability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    int32 CurrentDurability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    int32 MaxDurability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    float DurabilityDecayRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability")
    bool bIsDestroyable;

    /** Physical Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    E_WeightClass WeightClass;

    /** Special Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
    bool bIsQuestItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
    bool bIsUnique;

    /** Modifiers */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    TArray<FItemModifier> DefaultModifiers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
    TArray<FItemModifier> ItemModifiers;

    /** State Properties */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    E_ItemState InitialItemState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
    E_ItemState ItemState;

    /** Constructor */
    FItemStructure();

    /** Initialize from another structure */
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