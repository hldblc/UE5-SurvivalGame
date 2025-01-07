// ItemInfo.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "SurvivalGame/Public/Enums/ItemEnums.h"
#include "SurvivalGame/Public/Data/Struct/ItemStructure.h"
#include "ItemInfo.generated.h"

class UStaticMesh;
class USkeletalMesh;
class USoundBase;
class UParticleSystem;
class UTexture2D;

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
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    /** Creates a new instance of this item with runtime data */
    UFUNCTION(BlueprintPure, Category = "Item")
    FItemStructure CreateItemInstance(int32 Quantity = 1) const;

    /** Gets the adjusted value based on condition */
    UFUNCTION(BlueprintPure, Category = "Item")
    int32 GetAdjustedValue(float Condition = 1.0f) const;

    /** Checks if entity with given tags can use this item */
    UFUNCTION(BlueprintPure, Category = "Item")
    bool CanBeUsedBy(const FGameplayTagContainer& EntityTags) const;

    /** Gets the sell value considering condition */
    UFUNCTION(BlueprintPure, Category = "Item")
    int32 GetSellValue(float Condition = 1.0f) const;

protected:
    /** Calculates value modifiers based on properties */
    float CalculateValueModifiers() const;

public:
    /** Basic Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic", meta = (DisplayName = "Name"))
    FText ItemName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic", meta = (DisplayName = "Description", MultiLine = true))
    FText ItemDescription;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic", meta = (DisplayName = "Icon"))
    UTexture2D* ItemIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic", meta = (DisplayName = "Is Stackable"))
    bool bIsStackable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Basic", 
        meta = (EditCondition = "bIsStackable", ClampMin = "1", DisplayName = "Stack Size"))
    int32 MaxStackSize;

    /** Visual Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Visual", meta = (DisplayName = "Static Mesh"))
    UStaticMesh* ItemMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Visual", meta = (DisplayName = "Skeletal Mesh"))
    USkeletalMesh* ItemSkeletalMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Visual", meta = (DisplayName = "Particle Effect"))
    UParticleSystem* ItemParticle;

    /** Audio Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Audio", meta = (DisplayName = "Pickup Sound"))
    USoundBase* ItemPickupSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Audio", meta = (DisplayName = "Use Sound"))
    USoundBase* ItemUseSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Audio", meta = (DisplayName = "Drop Sound"))
    USoundBase* ItemDropSound;

    /** Gameplay Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay", meta = (DisplayName = "Category"))
    E_ItemCategory ItemCategory;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay", meta = (DisplayName = "Type"))
    E_ItemType ItemType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay", meta = (DisplayName = "Rarity"))
    E_ItemRarity ItemRarity;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay", meta = (DisplayName = "Weight Class"))
    E_WeightClass WeightClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay", meta = (DisplayName = "Is Consumable"))
    bool bIsConsumable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Gameplay", meta = (DisplayName = "Can Be Equipped"))
    bool bIsEquippable;

    /** Equipment Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment", 
        meta = (EditCondition = "bIsEquippable", DisplayName = "Tool Type"))
    E_ToolType ToolType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment", 
        meta = (EditCondition = "bIsEquippable", DisplayName = "Weapon Type"))
    E_WeaponType WeaponType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Equipment", 
        meta = (EditCondition = "bIsEquippable", DisplayName = "Armor Type"))
    E_ArmorType ArmorType;

    /** Tags and Requirements */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Tags", meta = (DisplayName = "Item Tags"))
    FGameplayTagContainer ItemTags;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Requirements", meta = (DisplayName = "Required Level"))
    int32 RequiredLevel;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Requirements", meta = (DisplayName = "Required Tags"))
    FGameplayTagContainer RequiredTags;

    /** Durability Settings */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Durability", meta = (DisplayName = "Max Durability"))
    int32 MaxDurability;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Durability", meta = (DisplayName = "Decay Rate"))
    float DurabilityDecayRate;

    /** Economic Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Economic", meta = (DisplayName = "Base Value"))
    int32 BaseValue;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Economic", meta = (DisplayName = "Sell Multiplier"))
    float SellValueMultiplier;

    /** Special Properties */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Special", meta = (DisplayName = "Is Quest Item"))
    bool bIsQuestItem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Special", meta = (DisplayName = "Is Unique"))
    bool bIsUnique;

    /** Modifiers */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Modifiers", meta = (DisplayName = "Default Modifiers"))
    TArray<FItemModifier> DefaultModifiers;
};