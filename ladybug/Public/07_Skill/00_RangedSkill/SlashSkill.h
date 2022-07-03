// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "07_Skill/SKillBase.h"
#include "SlashSkill.generated.h"

/**
 * Animation���� ����Ǵ� Skill
 */
UCLASS()
class LADYBUG_API USlashSkill : public USKillBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float skillFast = 1.0f;				// �ִϸ��̼� ���� �ӵ�
public:
	virtual void ActivateSkill() override;
};
