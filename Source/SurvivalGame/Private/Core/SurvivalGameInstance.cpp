// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SurvivalGameInstance.h"



USurvivalGameInstance::USurvivalGameInstance()
{
}

void USurvivalGameInstance::Init()
{
	Super::Init();

	InitializeSystems();
}

void USurvivalGameInstance::InitializeSystems()
{
	// Create and initialize the item registry
	ItemRegistry = NewObject<UItemRegistry>(this);
	ItemRegistry->Initialize();
}