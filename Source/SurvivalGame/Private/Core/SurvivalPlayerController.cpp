// SurvivalPlayerController.cpp
#include "Core/SurvivalPlayerController.h"

ASurvivalPlayerController::ASurvivalPlayerController()
	: RootLayout(nullptr)
	, bAutoEnableUIInput(true)
	, bLockMouseToViewport(false)
	, bHideCursorDuringCapture(true)
	, bIsUIInitialized(false)
	, bIsLocalController(false)
{
}

void ASurvivalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bIsLocalController = IsLocalController();

	// Only create UI for local players (clients and listen servers)
	if (!HasAuthority() || IsLocalPlayerController())
	{
		InitializeUILayout();
	}
}

void ASurvivalPlayerController::InitializeUILayout()
{
	if (!ensureMsgf(MasterUIClass, TEXT("%s: MasterUIClass not set! Please set it in Blueprint."), *GetNameSafe(this)))
	{
		return;
	}

	RootLayout = CreateWidget<UMasterUILayout>(this, MasterUIClass);
	if (!ensureMsgf(RootLayout, TEXT("%s: Failed to create MasterUILayout widget!"), *GetNameSafe(this)))
	{
		return;
	}

	RootLayout->AddToViewport(0);
    
	if (bAutoEnableUIInput)
	{
		SetUIInputMode(true);
	}

	bIsUIInitialized = true;
	OnUIInitialized.Broadcast();
}

void ASurvivalPlayerController::SetUIInputMode(bool bUIMode)
{
	if (bUIMode)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(bLockMouseToViewport ? EMouseLockMode::LockOnCapture : EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(bHideCursorDuringCapture);
		SetInputMode(InputMode);
		bShowMouseCursor = true;
	}
	else
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
	}
}