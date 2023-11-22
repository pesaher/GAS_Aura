// Copyright pesaher

#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(MeshComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		if (const UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent())
		{
			if (const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AbilitySystemComponent->GetAttributeSet(UAuraAttributeSet::StaticClass())))
			{
				//TODO Change to GameplayEffect
				const_cast<UAuraAttributeSet*>(AuraAttributeSet)->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
				const_cast<UAuraAttributeSet*>(AuraAttributeSet)->SetMana(AuraAttributeSet->GetMana() - 25.f);
				Destroy();
			}
		}
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}
