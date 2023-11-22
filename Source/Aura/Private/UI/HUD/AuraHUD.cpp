// Copyright pesaher

#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"

UAuraOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParameters& InWidgetControllerParameters)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UAuraOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParameters(InWidgetControllerParameters);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(const FWidgetControllerParameters& WidgetControllerParameters)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, fill it in the AuraHUD child class"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, fill it in the AuraHUD child class"))

	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	GetOverlayWidgetController(WidgetControllerParameters);
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidget->AddToViewport();
}
