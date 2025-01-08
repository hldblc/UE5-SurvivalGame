// ItemRegistry.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Data/PrimaryData/ItemInfo.h"
#include "Data/Struct/ItemStructure.h"
#include "ItemRegistry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemRegistryInitialized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRegistered, FName, ItemKey);

/**
 * @brief Manages the registration and retrieval of all items in the game
 * Acts as a central database for item information
 */
UCLASS(Blueprintable, BlueprintType)
class SURVIVALGAME_API UItemRegistry : public UObject
{
    GENERATED_BODY()

public:
    UItemRegistry();

    /** Initialize the registry */
    UFUNCTION(BlueprintCallable, Category = "Item Registry")
    void Initialize();

    /** Register a new item */
    UFUNCTION(BlueprintCallable, Category = "Item Registry")
    bool RegisterItem(UItemInfo* ItemInfo);

    /** Get item info by registry key */
    UFUNCTION(BlueprintPure, Category = "Item Registry")
    FORCEINLINE UItemInfo* GetItemInfo(const FName& RegistryKey) const
    {
        return RegisteredItems.Contains(RegistryKey) ? RegisteredItems[RegistryKey] : nullptr;
    }

    /** Create a new item instance */
    UFUNCTION(BlueprintCallable, Category = "Item Registry")
    FItemStructure CreateItemInstance(const FName& RegistryKey, int32 Quantity = 1) const;

    /** Check if an item is registered */
    UFUNCTION(BlueprintPure, Category = "Item Registry")
    FORCEINLINE bool IsItemRegistered(const FName& RegistryKey) const
    {
        return RegisteredItems.Contains(RegistryKey);
    }

    /** Get all registered item keys */
    UFUNCTION(BlueprintPure, Category = "Item Registry")
    TArray<FName> GetAllRegisteredItemKeys() const;

    /** Get all items of a specific type */
    UFUNCTION(BlueprintPure, Category = "Item Registry")
    TArray<UItemInfo*> GetItemsByType(E_ItemType ItemType) const;

    /** Get all items of a specific category */
    UFUNCTION(BlueprintPure, Category = "Item Registry")
    TArray<UItemInfo*> GetItemsByCategory(E_ItemCategory ItemCategory) const;

    /** Events */
    UPROPERTY(BlueprintAssignable, Category = "Item Registry|Events")
    FOnItemRegistryInitialized OnItemRegistryInitialized;

    UPROPERTY(BlueprintAssignable, Category = "Item Registry|Events")
    FOnItemRegistered OnItemRegistered;

protected:
    /** Map of registered items */
    UPROPERTY()
    TMap<FName, UItemInfo*> RegisteredItems;

    /** Default items to register on initialization */
    UPROPERTY(EditDefaultsOnly, Category = "Item Registry")
    TArray<TSoftObjectPtr<UItemInfo>> DefaultItems;

    /** Load and register default items */
    void LoadDefaultItems();

    /** Validate item info before registration */
    bool ValidateItemInfo(const UItemInfo* ItemInfo) const;

private:
    /** Whether the registry has been initialized */
    bool bIsInitialized;
};