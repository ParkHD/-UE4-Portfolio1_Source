// Fill out your copyright notice in the Description page of Project Settings.
#include "00_Character/00_Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "02_Item/ItemActor.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "02_Item/ItemActor.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/00_Player/CustomController.h"

#include "00_Character/02_Component/SkillComponent.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "08_Monster/Monster.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "02_Item/00_Equipment/Weapon.h"
#include "04_EuqipmentActor/00_WeaponActor/WeaponActor.h"
#include "06_ProjectileActor/ProjectileActor.h"

#include "Kismet/KismetSystemLibrary.h"														
#include "09_Interface/InteractionInterface.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "98_GameInstance/myGameInstance.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컨트롤러랑 Pawn이랑 같이 돌것인가
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;	// Controller에 맞춰서 SpringArm이 움직인다.
	//SpringArm->bInheritPitch = true;			// Y Controller에서 Y축은 안받아옴
	//SpringArm->bInheritRoll = true;				// X
	//SpringArm->bInheritYaw = true;				// Z
	SpringArm->bDoCollisionTest = false;			// 시야에 방해물이 있으면 확대기능

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
#pragma region skeletealMesh
	HeadMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMeshComponent"));
	HeadMeshComponent->SetupAttachment(GetMesh());

	HelmetMeshComponent1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HelmetMeshComponent1"));
	HelmetMeshComponent1->SetupAttachment(HeadMeshComponent);

	UpperBodyMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperBodyMeshComponent"));
	UpperBodyMeshComponent->SetupAttachment(GetMesh());

	ArmorMeshComponent1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmorMeshComponent1"));
	ArmorMeshComponent1->SetupAttachment(UpperBodyMeshComponent);

	ArmorMeshComponent2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmorMeshComponent2"));
	ArmorMeshComponent2->SetupAttachment(UpperBodyMeshComponent);

	ArmorMeshComponent3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmorMeshComponent3"));
	ArmorMeshComponent3->SetupAttachment(UpperBodyMeshComponent);

	CapeMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CapeMeshComponent"));
	CapeMeshComponent->SetupAttachment(GetMesh());

	ShoulderMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoulderMeshComponent"));
	ShoulderMeshComponent->SetupAttachment(GetMesh());

	HandMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMeshComponent"));
	HandMeshComponent->SetupAttachment(GetMesh());

	GloveMeshComponent1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GloveMeshComponent1"));
	GloveMeshComponent1->SetupAttachment(HandMeshComponent);

	GloveMeshComponent2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GloveMeshComponent2"));
	GloveMeshComponent2->SetupAttachment(HandMeshComponent);

	GloveMeshComponent3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GloveMeshComponent3"));
	GloveMeshComponent3->SetupAttachment(HandMeshComponent);

	LowerBodyMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBodyMeshComponent"));
	LowerBodyMeshComponent->SetupAttachment(GetMesh());

	PantsMeshComponent1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PantsMeshComponent1"));
	PantsMeshComponent1->SetupAttachment(LowerBodyMeshComponent);

	PantsMeshComponent2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PantsMeshComponent2"));
	PantsMeshComponent2->SetupAttachment(LowerBodyMeshComponent);

	PantsMeshComponent3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PantsMeshComponent3"));
	PantsMeshComponent3->SetupAttachment(LowerBodyMeshComponent);

	FootMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FootMeshComponent"));
	FootMeshComponent->SetupAttachment(GetMesh());

	ShoesMeshComponent1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoesMeshComponent1"));
	ShoesMeshComponent1->SetupAttachment(FootMeshComponent);

	ShoesMeshComponent2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoesMeshComponent2"));
	ShoesMeshComponent2->SetupAttachment(FootMeshComponent);
#pragma endregion

	if (weaponAnimationBP != nullptr)
	{
		GetMesh()->SetAnimInstanceClass(defaultAnimationBP->GetAnimBlueprintGeneratedClass());
	}

	// 팀 설정
	SetGenericTeamId(FGenericTeamId(5));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetMoveState(EMoveState::NORMAL);
}


void APlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// SetMasterPoseComponent : OnConstruction에서 구현하기
	// 애니메이션 설정
	HeadMeshComponent->SetMasterPoseComponent(GetMesh());
	HelmetMeshComponent1->SetMasterPoseComponent(GetMesh());

	UpperBodyMeshComponent->SetMasterPoseComponent(GetMesh());
	ArmorMeshComponent1->SetMasterPoseComponent(GetMesh());
	ArmorMeshComponent2->SetMasterPoseComponent(GetMesh());
	ArmorMeshComponent3->SetMasterPoseComponent(GetMesh());

	CapeMeshComponent->SetMasterPoseComponent(GetMesh());

	ShoulderMeshComponent->SetMasterPoseComponent(GetMesh());

	HandMeshComponent->SetMasterPoseComponent(GetMesh());
	GloveMeshComponent1->SetMasterPoseComponent(GetMesh());
	GloveMeshComponent2->SetMasterPoseComponent(GetMesh());
	GloveMeshComponent3->SetMasterPoseComponent(GetMesh());

	LowerBodyMeshComponent->SetMasterPoseComponent(GetMesh());
	PantsMeshComponent1->SetMasterPoseComponent(GetMesh());
	PantsMeshComponent2->SetMasterPoseComponent(GetMesh());
	PantsMeshComponent3->SetMasterPoseComponent(GetMesh());

	FootMeshComponent->SetMasterPoseComponent(GetMesh());
	ShoesMeshComponent1->SetMasterPoseComponent(GetMesh());
	ShoesMeshComponent2->SetMasterPoseComponent(GetMesh());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 상호작용 가능한지 확인하기
	auto controller = GetController<ACustomController>();
	if (controller != nullptr)
	{
		// 카메라를 기준으로 Forward방향으로 Ray
		FVector start = Camera->GetComponentLocation();
		FVector end = start + GetControlRotation().Vector() * 1000.f;
		TArray<TEnumAsByte<EObjectTypeQuery>> objects;
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		FHitResult hit;
		if (UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(),
			start,
			end,
			objects,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::None,
			hit,
			true))
		{
			// 상호작용 가능한 Actor인지 확인
			auto interactionTarget = Cast<IInteractionInterface>(hit.GetActor());
			if (interactionTarget != nullptr)
			{
				if (interactAbleTarget == nullptr)
				{
					controller->SetUpTargetName(interactionTarget->GetName());
					controller->TurnOnInteractKey(true);
					// 현재 보고있는 Actor(상호작용 가능한 타겟) 저장
					interactAbleTarget = hit.GetActor();
				}
			}
		}
		// 카메라를 돌려서 Ray가 Actor를 벗어나면 상호작용 타겟 초기화
		else
		{
			controller->TurnOnInteractKey(false);
			interactAbleTarget = nullptr;
		}
	}

	// 타겟과의 상호작용을 시작하면 타겟 방향으로 카메라 이동 및 회전
	if(isInteract)
	{
		if(interactAbleTarget != nullptr)
		{
			FVector dir = interactAbleTarget->GetActorLocation() - Camera->GetComponentLocation();
			FRotator dirRotation = Camera->GetComponentRotation();
			dirRotation.Pitch = dir.Rotation().Pitch;
		
			SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, 50, DeltaTime, interpSpeed);
			Camera->SetWorldRotation(FMath::RInterpTo(Camera->GetComponentRotation(), dirRotation, DeltaTime, interpSpeed));
		}
	}
	// 조준 시 카메라 이동 및 회전, Aim 위젯 활성화
	else if(isAimming)
	{
		SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, 200, DeltaTime, interpSpeed);
		controller->TurnOnAimWidget(true);
		// Aim 위젯이 점점 작아지게 -> 명중률 증가
		controller->SetUpAimSize(FMath::Vector2DInterpTo(controller->GetAimWidgetSize(), FVector2D(50, 50), DeltaTime, interpSpeed));
	}
	// 카메라의 위치 및 회전 원래대로 복구
	else
	{
		SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, originArmlength, DeltaTime, interpSpeed);
		SpringArm->SocketOffset = FMath::VInterpTo(SpringArm->SocketOffset, FVector(0, 0, 0), DeltaTime, interpSpeed);

		Camera->SetRelativeRotation(FMath::RInterpTo(Camera->GetRelativeRotation(), FRotator::ZeroRotator, DeltaTime, interpSpeed));

		controller->TurnOnAimWidget(false);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent); // 잘못된 포인터 변수일경우 꺼주는 매크로

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseRun);

	PlayerInputComponent->BindAction("PickUp", EInputEvent::IE_Pressed, this, &APlayerCharacter::PickUp);

	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressAttack);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseAttack);

	PlayerInputComponent->BindAction("Block", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressBlock);
	PlayerInputComponent->BindAction("Block", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseBlock);

	PlayerInputComponent->BindAction("Skill1", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressSkill1);
	PlayerInputComponent->BindAction("Skill2", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressSkill2);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressInteract);

	PlayerInputComponent->BindAction("Option", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressOption);
	PlayerInputComponent->BindAxis("SwapWeapon", this, &APlayerCharacter::SawpWeapon);

	PlayerInputComponent->BindAction("UpKey", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressUpKey);
	PlayerInputComponent->BindAction("UpKey", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseUpKey);
	PlayerInputComponent->BindAction("DownKey", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressDownKey);
	PlayerInputComponent->BindAction("DownKey", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseDownKey);
	PlayerInputComponent->BindAction("LeftKey", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressLeftKey);
	PlayerInputComponent->BindAction("LeftKey", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseLeftKey);
	PlayerInputComponent->BindAction("RightKey", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressRightKey);
	PlayerInputComponent->BindAction("RightKey", EInputEvent::IE_Released, this, &APlayerCharacter::ReleaseRightKey);

	PlayerInputComponent->BindAction("Dodge", EInputEvent::IE_Pressed, this, &APlayerCharacter::PressDodge);
}

void APlayerCharacter::MoveForward(float newAxisValue)
{
	// 공격 or 피격중에 이동 불가
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(attackMontage))
		return;
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(hitMontage))
		return;

	// 점프 or 스킬 사용중에 이동 불가
	if (newAxisValue != 0.0f && MoveState != EMoveState::JUMP &&  ActionState != EActionState::SKILL)
	{
		if(InputComponent->GetAxisValue("MoveForward") < 0)
			SetMoveState(EMoveState::NORMAL);

		FRotator newRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector direction = FRotationMatrix(newRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, newAxisValue);
	}
}
void APlayerCharacter::MoveRight(float newAxisValue)
{
	if (newAxisValue != 0.0f && MoveState != EMoveState::JUMP && ActionState != EActionState::ATTACK && ActionState != EActionState::SKILL)
	{
		SetMoveState(EMoveState::NORMAL);

		FRotator newRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector direction = FRotationMatrix(newRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), newAxisValue);
	}
}
void APlayerCharacter::LookUp(float newAxisValue)
{
	AddControllerPitchInput(newAxisValue);
}
void APlayerCharacter::Turn(float newAxisValue)
{
	AddControllerYawInput(newAxisValue);
}
void APlayerCharacter::Jump()
{
	if (MoveState != EMoveState::JUMP)
		Super::Jump();
}
void APlayerCharacter::PressRun()
{
	// MoveState 변경
	if(MoveState != EMoveState::JUMP)
		SetMoveState(EMoveState::RUN);
}
void APlayerCharacter::ReleaseRun()
{
	if (MoveState != EMoveState::JUMP)
	{
		SetMoveState(EMoveState::NORMAL);
	}
}
void APlayerCharacter::PressBlock()
{
	if (ActionState == EActionState::SKILL)
		return;
	if(GetEquipmentComponent()->GetEquippedSubWeapon() != nullptr)
	{
		// 방패를 장착하고 있는지 확인
		if (GetEquipmentComponent()->GetEquippedSubWeapon()->GetItemInfo<FWeaponInformation>()->WeaponType == EWeaponType::SHIELD
			&& ActionState == EActionState::NORMAL)
		{
			isBlockPressed = true;
			SetActionState(EActionState::BLOCK);
		}
	}
}
void APlayerCharacter::ReleaseBlock()
{
	isBlockPressed = false;
	SetActionState(EActionState::NORMAL);
}
void APlayerCharacter::PickUp()
{
	if (pickUpAbleItems.Num() > 0)
	{
		InventoryComponent->AddItem(pickUpAbleItems.Top()->Item);
		pickUpAbleItems.Top()->Destroy();
	}
}

void APlayerCharacter::PressAttack()
{
	// 스킬 사용 중 Attack 불가
	if (ActionState == EActionState::SKILL)
		return;
	// 공격 쿨타임이 돌았는 지 확인 및 무기를 장착 하고 있는지 확인
	if(AttackState == EAttackState::READY && GetEquipmentComponent()->GetEquippedWeapon() != nullptr)
	{
		SetActionState(EActionState::ATTACK);

		// 무기에 따른 다른 공격
		if (EquipmentComponent->GetEquippedWeapon()->GetItemInfo<FWeaponInformation>()->WeaponType == EWeaponType::BOW)
		{
			// 보조무기로 화살을 장착했는 지 확인
			if(GetEquipmentComponent()->GetEquippedSubWeapon() != nullptr)
			{
				SetActionState(EActionState::AIM);

				if (ShieldChildActorComponent->GetChildActor() != nullptr)
				{
					// 화살 장전 시 화살 Actor보이기
					ShieldChildActorComponent->GetChildActor()->SetActorHiddenInGame(false);
				}
				isAttackPressed = true;
				isAimming = true;
			}
		}
		else
		{
			// 근점 공격은 몽타주로 실행 따라서 몽타주가 있는지 확인
			if (attackMontage != nullptr && ActionState != EActionState::SKILL)
			{
				// 첫 공격이 아니라면 Combo 공격
				if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(attackMontage))
				{
					bInputComboAttack = true;
				}
				else
				{
					GetMesh()->GetAnimInstance()->Montage_Play(attackMontage);
				}
			}
		}
	}
}
void APlayerCharacter::ReleaseAttack()
{
	if(isAttackPressed)
	{
		// 원거리 무기를 장착하고 있을 때
		if (EquipmentComponent->GetEquippedWeapon()->GetItemInfo<FWeaponInformation>()->WeaponType == EWeaponType::BOW)
		{
			// 공격이 완료가 됬다면
			if(ActionState == EActionState::AIM)
			{
				// 공격 쿨타임 적용
				SetAttackState(EAttackState::COOLTIME);
			
				FTimerHandle coolTimer;
				FTimerDelegate coolDelegate = FTimerDelegate::CreateUObject(this, &ABaseCharacter::SetAttackState, EAttackState::READY);
				GetWorldTimerManager().SetTimer(
					coolTimer,
					coolDelegate,
					2.f,
					false);
			}
			// 공격이 중간에 취소가 됬다면
			else
			{
				if (ShieldChildActorComponent->GetChildActor() != nullptr)
				{
					ShieldChildActorComponent->GetChildActor()->SetActorHiddenInGame(true);
				}
			}
			
			isAimming = false;
		}

		
		isAttackPressed = false;
	}
}
void APlayerCharacter::PressSkill1()
{
	if(skillComponent->SkillUsable(0))
	{
		// 스킬 사용 중이거나 공격중엔 스킬 사용 불가
		if (ActionState != EActionState::SKILL && ActionState != EActionState::ATTACK)
		{
			skillComponent->UseSkill(0);
		}
	}
}

void APlayerCharacter::PressSkill2()
{
	if (skillComponent->SkillUsable(1))
	{
		// 스킬 사용 중이거나 공격중엔 스킬 사용 불가
		if (ActionState != EActionState::SKILL && ActionState != EActionState::ATTACK)
		{
			skillComponent->UseSkill(1);
		}
	}
}

void APlayerCharacter::PressInteract()
{
	if (interactAbleTarget != nullptr)
	{
		auto target = Cast<IInteractionInterface>(interactAbleTarget);
		if (target != nullptr)
		{
			isInteract = true;
			target->InterAction(this);	// (인터페이스 함수)
		}
	}
}

void APlayerCharacter::PressOption()
{
	GetController<ACustomController>()->OpenVillageExitWidget();
}
void APlayerCharacter::SawpWeapon(float newAxisValue)
{
	if(newAxisValue >= 1.f)
	{
		EquipmentComponent->SwapWeaponUp(true);
	}
	else if(newAxisValue <= -1.f)
	{
		EquipmentComponent->SwapWeaponUp(false);
	}
}

void APlayerCharacter::PressUpKey()
{
	bUpKey = true;
}

void APlayerCharacter::ReleaseUpKey()
{
	bUpKey = false;
}

void APlayerCharacter::PressDownKey()
{
	bDownKey = true;
}

void APlayerCharacter::ReleaseDownKey()
{
	bDownKey = false;
}

void APlayerCharacter::PressLeftKey()
{
	bLeftKey = true;
}

void APlayerCharacter::ReleaseLeftKey()
{
	bLeftKey = false;
}

void APlayerCharacter::PressRightKey()
{
	bRightKey = true;
}

void APlayerCharacter::ReleaseRightKey()
{
	bRightKey = false;
}

void APlayerCharacter::PressDodge()
{
	if (ActionState == EActionState::DODGE)
		return;
	class UAnimMontage* dodgeMontage = nullptr;

	// 어느 방향키가 입력 되고 있는 지에 따라 다른 회피 몽타주 설정
	if (bUpKey)
		dodgeMontage = ForwardDodgeMontage;
	else if (bDownKey)
		dodgeMontage = BackDodgeMontage;
	else if (bLeftKey)
		dodgeMontage = LeftDodgeMontage;
	else if (bRightKey)
		dodgeMontage = RightDodgeMontage;

	if(dodgeMontage != nullptr)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(dodgeMontage, 1.2f);
	}
}

float APlayerCharacter::GetMoveDirection()
{
	// Atan를 이용한 이동 방향 구하기
	float x = GetVelocity().Y;
	float y = GetVelocity().X;

	moveDirection = FMath::Atan2(x, y);
	moveDirection = FMath::RadiansToDegrees(moveDirection);

	moveDirection -= GetActorRotation().Yaw;

	// 각도 범위를 -180 ~ 180으로 설정
	if (moveDirection > 180.0f)
	{
		moveDirection -= 360.0f;
	}
	else if (moveDirection < -180.0f)
	{
		moveDirection += 360.0f;
	}
	
	return moveDirection;
}
void APlayerCharacter::SetAttackMontage(class UAnimMontage* montage)
{
	if (montage != nullptr)
	{
		attackMontage = montage;
	}
}
void APlayerCharacter::SetHitMontage(class UAnimMontage* montage)
{
	if (montage != nullptr)
	{
		hitMontage = montage;
	}
}
void APlayerCharacter::SetCharacter(AWorldBaseCharacter* WorldCharacter)
{
	EquipmentComponent->SetBattleCharacter(WorldCharacter->GetEquipmentComponent());
	statusComponent->SetBattleCharacterStat(WorldCharacter->GetStatusComponent());
}
