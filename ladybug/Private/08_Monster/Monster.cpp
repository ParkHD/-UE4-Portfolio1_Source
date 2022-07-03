// Fill out your copyright notice in the Description page of Project Settings.


#include "08_Monster/Monster.h"

const FMonsterInfo* UMonster::GetMonsterInfo()
{
	if (monsterDT != nullptr)
	{
		return monsterDT->FindRow<FMonsterInfo>(monsterTag.GetTagName(), "");
	}
	return nullptr;
}

