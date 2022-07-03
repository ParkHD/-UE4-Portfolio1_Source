// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_FixRotation.generated.h"

// �ִϸ��̼��� ��Ʈ������� �ٲ��� �� ȸ������ �̻��ϰ� �����Ǵ� ���� ����
// ȸ���� ����
UCLASS()
class LADYBUG_API UNotifyState_FixRotation : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	class ABaseCharacter* owner;	// owner

	FRotator ownerRotation;			// owner�� �ִϸ��̼� ���� �� ȸ����
};
