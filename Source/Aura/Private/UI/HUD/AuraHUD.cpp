// Copyright pesaher

#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* NewOverlayWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	NewOverlayWidget->AddToViewport();
}
