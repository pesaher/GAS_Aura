// Copyright pesaher

#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	bDestroyOnEffectRemoval = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		GameplayEffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, GameplayEffectContextHandle);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
	}
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffect.GameplayEffectClass);
	}

	if (DurationGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffect.GameplayEffectClass);
	}

	if (InfiniteGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect.GameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffect.GameplayEffectClass);
	}

	if (DurationGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffect.GameplayEffectClass);
	}

	if (InfiniteGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect.GameplayEffectClass);
	}
}
