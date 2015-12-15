// Fill out your copyright notice in the Description page of Project Settings.

#include "Garden.h"
#include "MultiTouchPlayerController.h"
#include "MyWindowsMessageHandler.h"



static  FMyWindowsMessageHandler myMessageHandler;



void AMultiTouchPlayerController::BeginPlay(){
#if PLATFORM_WINDOWS
	TSharedPtr<GenericApplication> GenericApplication = FSlateApplication::Get().GetPlatformApplication();
	FWindowsApplication* WindowsApplication = (FWindowsApplication*)GenericApplication.Get();
	WindowsApplication->AddMessageHandler(myMessageHandler);
	myMessageHandler.TouchController = this;
	myMessageHandler.InitVariable();

#endif
}
void AMultiTouchPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason){
#if PLATFORM_WINDOWS
	TSharedPtr<GenericApplication> GenericApplication = FSlateApplication::Get().GetPlatformApplication();
	FWindowsApplication* WindowsApplication = (FWindowsApplication*)GenericApplication.Get();
	WindowsApplication->RemoveMessageHandler(myMessageHandler);
#endif
}
#
void  AMultiTouchPlayerController::OnTouchDownHandler(int32 x, int32 y, int32 index){
	OnTouchDownEventWindows(x, y, index);

}
void  AMultiTouchPlayerController::OnTouchMoveHandler(int32 x, int32 y, int32 index){
	OnTouchMoveEventWindows(x, y, index);

}
void  AMultiTouchPlayerController::OnTouchUpHandler(int32 x, int32 y, int32 index){
	OnTouchUpEventWindows(x, y, index);
}






