// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"

#include "CollisionRangeNotifyState.generated.h"


// 횡방향으로 콜리전을 생성하여 범위 공격 : -range ~ range각도 만큼 공격
// 스킬 공격
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

	// 시작할 때 캐릭터의 위치 및 회전값
	FVector startLocation;
	FRotator startRotator;

	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;	// 스킬 태그

	// 범위 설정
	UPROPERTY(EditAnywhere)
		float range;			// 범위 = 각도			
	UPROPERTY(EditAnywhere)
		float length;			// 콜리전 길이
	UPROPERTY(EditAnywhere)
		float collisionRadius;	// 콜리전 반지름

	UPROPERTY(EditAnywhere)
		float interpSpeed;		// 횡방향 회전 속도

	float angle;	// 콜리전이 생성 될 각도 -range ~ range
};
