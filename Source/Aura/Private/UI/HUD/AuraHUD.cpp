// Copyright pesaher

#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"

UAuraOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(AAuraPlayerState* InPlayerState)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UAuraOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParameters(InPlayerState);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(AAuraPlayerState* InPlayerState)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, fill it in the AuraHUD child class"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, fill it in the AuraHUD child class"))

	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	GetOverlayWidgetController(InPlayerState);
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BroadcastInitialValues();
	OverlayWidget->AddToViewport();
}
