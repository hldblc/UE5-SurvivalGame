// SurvivalGameInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SurvivalGame/Public//Registry/ItemRegistry.h"
#include "SurvivalGameInstance.generated.h"

/**
 * Game instance for managing global game state and systems
 */
UCLASS()
class SURVIVALGAME_API USurvivalGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USurvivalGameInstance();

	virtual void Init() override;

	/** Get the item registry */
	UFUNCTION(BlueprintPure, Category = "Item System")
	FORCEINLINE UItemRegistry* GetItemRegistry() const { return ItemRegistry; }

protected:
	/** The item registry */
	UPROPERTY()
	UItemRegistry* ItemRegistry;

	/** Initialize game systems */
	virtual void InitializeSystems();
};