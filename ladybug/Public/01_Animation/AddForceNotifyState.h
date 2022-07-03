// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AddForceNotifyState.generated.h"

// 캐릭터가 움직일 방향
UENUM(BlueprintType)
enum class EForceDir : uint8
{
	UP,			// 위
	DOWN,		// 아래
	LEFT,		// 왼쪽
	RIGHT,		// 오른쪽
	FORWARD,	// 앞
	BACKWARD	// 뒤
};

// 캐릭터의 위치 이동 
UCLASS()
class LADYBUG_API UAddForceNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
		
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY()
	class ABaseCharacter* owner;	// owner

	UPROPERTY(EditAnywhere)
	EForceDir forceDir;				// 캐릭터 이동할 방향
	UPROPERTY(EditAnywhere)
	float force;					// 캐릭터 이동 속도

};
