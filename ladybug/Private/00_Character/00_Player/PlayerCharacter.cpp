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

	// ��Ʈ�ѷ��� Pawn�̶� ���� �����ΰ�
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;	// Controller�� ���缭 SpringArm�� �����δ�.
	//SpringArm->bInheritPitch = true;			// Y Controller���� Y���� �ȹ޾ƿ�
	//SpringArm->bInheritRoll = true;				// X
	//SpringArm->bInheritYaw = true;				// Z
	SpringArm->bDoCollisionTest = false;			// �þ߿� ���ع��� ������ Ȯ����

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

	// �� ����
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

	// SetMasterPoseComponent : OnConstruction���� �����ϱ�
	// �ִϸ��̼� ����
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

	// ��ȣ�ۿ� �������� Ȯ���ϱ�
	auto controller = GetController<ACustomController>();
	if (controller != nullptr)
	{
		// ī�޶� �������� Forward�������� Ray
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
			// ��ȣ�ۿ� ������ Actor���� Ȯ��
			auto interactionTarget = Cast<IInteractionInterface>(hit.GetActor());
			if (interactionTarget != nullptr)
			{
				if (interactAbleTarget == nullptr)
				{
					controller->SetUpTargetName(interactionTarget->GetName());
					controller->TurnOnInteractKey(true);
					// ���� �����ִ� Actor(��ȣ�ۿ� ������ Ÿ��) ����
					interactAbleTarget = hit.GetActor();
				}
			}
		}
		// ī�޶� ������ Ray�� Actor�� ����� ��ȣ�ۿ� Ÿ�� �ʱ�ȭ
		else
		{
			controller->TurnOnInteractKey(false);
			interactAbleTarget = nullptr;
		}
	}

	// Ÿ�ٰ��� ��ȣ�ۿ��� �����ϸ� Ÿ�� �������� ī�޶� �̵� �� ȸ��
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
	// ���� �� ī�޶� �̵� �� ȸ��, Aim ���� Ȱ��ȭ
	else if(isAimming)
	{
		SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, 200, DeltaTime, interpSpeed);
		controller->TurnOnAimWidget(true);
		// Aim ������ ���� �۾����� -> ���߷� ����
		controller->SetUpAimSize(FMath::Vector2DInterpTo(controller->GetAimWidgetSize(), FVector2D(50, 50), DeltaTime, interpSpeed));
	}
	// ī�޶��� ��ġ �� ȸ�� ������� ����
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
	check(PlayerInputComponent); // �߸��� ������ �����ϰ�� ���ִ� ��ũ��

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
	// ���� or �ǰ��߿� �̵� �Ұ�
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(attackMontage))
		return;
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(hitMontage))
		return;

	// ���� or ��ų ����߿� �̵� �Ұ�
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
	// MoveState ����
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
		// ���и� �����ϰ� �ִ��� Ȯ��
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
	// ��ų ��� �� Attack �Ұ�
	if (ActionState == EActionState::SKILL)
		return;
	// ���� ��Ÿ���� ���Ҵ� �� Ȯ�� �� ���⸦ ���� �ϰ� �ִ��� Ȯ��
	if(AttackState == EAttackState::READY && GetEquipmentComponent()->GetEquippedWeapon() != nullptr)
	{
		SetActionState(EActionState::ATTACK);

		// ���⿡ ���� �ٸ� ����
		if (EquipmentComponent->GetEquippedWeapon()->GetItemInfo<FWeaponInformation>()->WeaponType == EWeaponType::BOW)
		{
			// ��������� ȭ���� �����ߴ� �� Ȯ��
			if(GetEquipmentComponent()->GetEquippedSubWeapon() != nullptr)
			{
				SetActionState(EActionState::AIM);

				if (ShieldChildActorComponent->GetChildActor() != nullptr)
				{
					// ȭ�� ���� �� ȭ�� Actor���̱�
					ShieldChildActorComponent->GetChildActor()->SetActorHiddenInGame(false);
				}
				isAttackPressed = true;
				isAimming = true;
			}
		}
		else
		{
			// ���� ������ ��Ÿ�ַ� ���� ���� ��Ÿ�ְ� �ִ��� Ȯ��
			if (attackMontage != nullptr && ActionState != EActionState::SKILL)
			{
				// ù ������ �ƴ϶�� Combo ����
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
		// ���Ÿ� ���⸦ �����ϰ� ���� ��
		if (EquipmentComponent->GetEquippedWeapon()->GetItemInfo<FWeaponInformation>()->WeaponType == EWeaponType::BOW)
		{
			// ������ �Ϸᰡ ��ٸ�
			if(ActionState == EActionState::AIM)
			{
				// ���� ��Ÿ�� ����
				SetAttackState(EAttackState::COOLTIME);
			
				FTimerHandle coolTimer;
				FTimerDelegate coolDelegate = FTimerDelegate::CreateUObject(this, &ABaseCharacter::SetAttackState, EAttackState::READY);
				GetWorldTimerManager().SetTimer(
					coolTimer,
					coolDelegate,
					2.f,
					false);
			}
			// ������ �߰��� ��Ұ� ��ٸ�
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
		// ��ų ��� ���̰ų� �����߿� ��ų ��� �Ұ�
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
		// ��ų ��� ���̰ų� �����߿� ��ų ��� �Ұ�
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
			target->InterAction(this);	// (�������̽� �Լ�)
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

	// ��� ����Ű�� �Է� �ǰ� �ִ� ���� ���� �ٸ� ȸ�� ��Ÿ�� ����
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
	// Atan�� �̿��� �̵� ���� ���ϱ�
	float x = GetVelocity().Y;
	float y = GetVelocity().X;

	moveDirection = FMath::Atan2(x, y);
	moveDirection = FMath::RadiansToDegrees(moveDirection);

	moveDirection -= GetActorRotation().Yaw;

	// ���� ������ -180 ~ 180���� ����
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
