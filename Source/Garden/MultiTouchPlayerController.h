// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MultiTouchPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GARDEN_API AMultiTouchPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:


	UFUNCTION(BlueprintImplementableEvent)
		void OnTouchDownEventWindows(int32 x, int32 y, int32 index);
	UFUNCTION(BlueprintImplementableEvent)
		void OnTouchMoveEventWindows(int32 x, int32 y, int32 index);
	UFUNCTION(BlueprintImplementableEvent)
		void OnTouchUpEventWindows(int32 x, int32 y, int32 index);

public:
	void OnTouchDownHandler(int32 x, int32 y, int32 index);
	void OnTouchMoveHandler(int32 x, int32 y, int32 index);
	void OnTouchUpHandler(int32 x, int32 y, int32 index);
	
	
};
