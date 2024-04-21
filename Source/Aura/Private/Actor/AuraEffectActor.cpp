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
	if (UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor); IsValid(AbilitySystemComponent))
	{
		FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		GameplayEffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, GameplayEffectContextHandle);
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
		if (GameplayEffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite)
		{
			for (const FAuraRemovableEffect& InfiniteGameplayEffect : InfiniteGameplayEffects)
			{
				if (InfiniteGameplayEffect.GameplayEffectClass == GameplayEffectClass)
				{
					if (InfiniteGameplayEffect.EffectRemovalPolicy != EAuraEffectPolicy::None)
					{
						ActiveGameplayEffectHandlesMap.Add(ActiveGameplayEffectHandle, AbilitySystemComponent);
					}
					break;
				}
			}
		}
	}
}

void AAuraEffectActor::RemoveEffectFromTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor); IsValid(AbilitySystemComponent))
	{
		TArray<FActiveGameplayEffectHandle> GameplayEffectHandlesToRemove;
		for (const TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*>& ActiveGameplayEffectHandlePair : ActiveGameplayEffectHandlesMap)
		{
			if (ActiveGameplayEffectHandlePair.Value == AbilitySystemComponent)
			{
				const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = ActiveGameplayEffectHandlePair.Key;
				AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveGameplayEffectHandle, 1);
				GameplayEffectHandlesToRemove.Add(ActiveGameplayEffectHandle);
			}
		}
		for (const FActiveGameplayEffectHandle& GameplayEffectHandleToRemove : GameplayEffectHandlesToRemove)
		{
			ActiveGameplayEffectHandlesMap.Remove(GameplayEffectHandleToRemove);
		}
	}
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	for (const FAuraEffect& InstantGameplayEffect : InstantGameplayEffects)
	{
		if (InstantGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnOverlap)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffect.GameplayEffectClass);
		}
	}

	for (const FAuraEffect& DurationGameplayEffect : DurationGameplayEffects)
	{
		if (DurationGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnOverlap)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffect.GameplayEffectClass);
		}
	}

	for (const FAuraRemovableEffect& InfiniteGameplayEffect : InfiniteGameplayEffects)
	{
		if (InfiniteGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnOverlap)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect.GameplayEffectClass);
		}

		if (InfiniteGameplayEffect.EffectRemovalPolicy == EAuraEffectPolicy::OnOverlap)
		{
			RemoveEffectFromTarget(TargetActor, InfiniteGameplayEffect.GameplayEffectClass);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	for (const FAuraEffect& InstantGameplayEffect : InstantGameplayEffects)
	{
		if (InstantGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffect.GameplayEffectClass);
		}
	}

	for (const FAuraEffect& DurationGameplayEffect : DurationGameplayEffects)
	{
		if (DurationGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffect.GameplayEffectClass);
		}
	}

	for (const FAuraRemovableEffect& InfiniteGameplayEffect : InfiniteGameplayEffects)
	{
		if (InfiniteGameplayEffect.EffectApplicationPolicy == EAuraEffectPolicy::OnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect.GameplayEffectClass);
		}

		if (InfiniteGameplayEffect.EffectRemovalPolicy == EAuraEffectPolicy::OnEndOverlap)
		{
			RemoveEffectFromTarget(TargetActor, InfiniteGameplayEffect.GameplayEffectClass);
		}
	}
}
