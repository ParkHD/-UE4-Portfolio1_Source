// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"

#include "CollisionRangeNotifyState.generated.h"


// Ⱦ�������� �ݸ����� �����Ͽ� ���� ���� : -range ~ range���� ��ŭ ����
// ��ų ����
UCLASS()
class LADYBUG_API UCollisionRangeNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
protected:
	UPROPERTY()
		class ABaseCharacter* owner;	// owner

	// ������ �� ĳ������ ��ġ �� ȸ����
	FVector startLocation;
	FRotator startRotator;

	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;	// ��ų �±�

	// ���� ����
	UPROPERTY(EditAnywhere)
		float range;			// ���� = ����			
	UPROPERTY(EditAnywhere)
		float length;			// �ݸ��� ����
	UPROPERTY(EditAnywhere)
		float collisionRadius;	// �ݸ��� ������

	UPROPERTY(EditAnywhere)
		float interpSpeed;		// Ⱦ���� ȸ�� �ӵ�

	float angle;	// �ݸ����� ���� �� ���� -range ~ range
};
