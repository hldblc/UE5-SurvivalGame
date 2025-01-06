// ItemInfo.h

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ItemEnums.h"
#include "Structs/ItemStructure.h"
#include "Engine/DataAsset.h"
#include "ItemInfo.generated.h"

class UStaticMesh;
class USkeletalMesh;
class USoundBase;
class UParticleSystem;

/**
 * @brief Primary Data Asset for defining static item properties
 * Used as a template for creating item instances in the game
 */
UCLASS(BlueprintType, Blueprintable)
class SURVIVALGAME_API UItemInfo : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UItemInfo();

    /** Basic Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic")
    FText ItemName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic", meta = (MultiLine = true))
    FText ItemDescription;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic")
    UTexture2D* ItemIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic")
    bool bIsStackable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic", meta = (EditCondition = "bIsStackable", ClampMin = "1"))
    int32 MaxStackSize;

    /** Visual Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Visual")
    UStaticMesh* ItemMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Visual")
    USkeletalMesh* ItemSkeletalMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Visual")
    UParticleSystem* ItemParticle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Audio")
    USoundBase* ItemPickupSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Audio")
    USoundBase* ItemUseSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Audio")
    USoundBase* ItemDropSound;

    /** Gameplay Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay")
    E_ItemCategory ItemCategory;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay")
    E_ItemType ItemType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay")
    E_ItemRarity ItemRarity;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay")
    E_WeightClass WeightClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay")
    bool bIsConsumable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay")
    bool bIsEquippable;

    /** Equipment Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment", meta = (EditCondition = "bIsEquippable"))
    E_ToolType ToolType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment", meta = (EditCondition = "bIsEquippable"))
    E_WeaponType WeaponType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment", meta = (EditCondition = "bIsEquippable"))
    E_ArmorType ArmorType;

    /** Item Tags */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Tags")
    FGameplayTagContainer ItemTags;

    /** Durability Settings */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Durability")
    int32 MaxDurability;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Durability")
    float DurabilityDecayRate;

    /** Economic Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Economic")
    int32 BaseValue;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Economic")
    float SellValueMultiplier;

    /** Special Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Special")
    bool bIsQuestItem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Special")
    bool bIsUnique;

    /** Default Modifiers */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Modifiers")
    TArray<FItemModifier> DefaultModifiers;

    /** Requirements */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Requirements")
    int32 RequiredLevel;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Requirements")
    FGameplayTagContainer RequiredTags;

public:
    /** Get unique asset identifier */
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    /** Create runtime item structure */
    UFUNCTION(BlueprintPure, Category = "Item")
    FItemStructure CreateItemInstance(int32 Quantity = 1) const;

    /** Get adjusted value based on condition */
    UFUNCTION(BlueprintPure, Category = "Item")
    int32 GetAdjustedValue(float Condition = 1.0f) const;

    /** Check if the item can be used by an entity with given tags */
    UFUNCTION(BlueprintPure, Category = "Item")
    bool CanBeUsedBy(const FGameplayTagContainer& EntityTags) const;

    /** Get the sell value of the item */
    UFUNCTION(BlueprintPure, Category = "Item")
    int32 GetSellValue(float Condition = 1.0f) const;

protected:
    /** Calculate value modifiers based on properties */
    float CalculateValueModifiers() const;
};