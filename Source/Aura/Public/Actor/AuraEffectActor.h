// Copyright pesaher

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EAuraEffectPolicy
{
	None,
	OnOverlap,
	OnEndOverlap
};

USTRUCT(BlueprintType)
struct FAuraEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "GameplayEffectClass != nullptr", EditConditionHides))
	EAuraEffectPolicy EffectApplicationPolicy;
};

USTRUCT(BlueprintType)
struct FAuraRemovableEffect : public FAuraEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "GameplayEffectClassGameplayEffectClass != nullptr", EditConditionHides, DisplayAfter="EffectApplicationPolicy"))
	EAuraEffectPolicy EffectRemovalPolicy;
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void RemoveEffectFromTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	bool bDestroyOnEffectRemoval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	TArray<FAuraEffect> InstantGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	TArray<FAuraEffect> DurationGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AppliedEffects")
	TArray<FAuraRemovableEffect> InfiniteGameplayEffects;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveGameplayEffectHandlesMap;
};
