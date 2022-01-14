#include "BaseGunC.h"

#include "PracticeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


ABaseGunC::ABaseGunC()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Muzzle"));
	SphereComp->SetupAttachment(RootComponent);

	WeaponStatus = EWeaponStatus::Idle;

	bReplicates = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/ThirdPersonCPP/Meshes/Colt_Python.Colt_Python"));
	if (DefaultMesh.Succeeded())
	{
		Mesh = DefaultMesh.Object;
	}

	StaticMeshComp->SetStaticMesh(Mesh);

	SetActorEnableCollision(false);
}

void ABaseGunC::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGunC::StartFire()
{
	if (WeaponStatus == EWeaponStatus::Idle)
	{
		HandleFire();
		GetWorldTimerManager().SetTimer(FireRateTimer, this, &ABaseGunC::StopFire, WeaponData.FireRate, false);
		WeaponStatus = EWeaponStatus::Firering;
		
	}
}

void ABaseGunC::StopFire()
{
	WeaponStatus = EWeaponStatus::Idle;
}

void ABaseGunC::HandleFire_Implementation()
{
	
	FHitResult HitResult;
	UCameraComponent* OwnerCamera = Cast<APracticeCharacter>(GetOwner())->GetFollowCamera();
	FVector StartLocation = OwnerCamera->GetComponentLocation();
	FVector EndLocation = StartLocation + OwnerCamera->GetForwardVector() * WeaponData.Range ;
	if(GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_WorldDynamic
		))
	{
		EndLocation = HitResult.Location;
		StartLocation = SphereComp->GetComponentLocation() + GetActorForwardVector()*50;
		UKismetSystemLibrary::DrawDebugLine(this, StartLocation, EndLocation, FColor::Red, 5.f, 3);
		if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_WorldDynamic
		))
		{
			const FDamageEvent DamageEvent(WeaponData.DamageType);
			HitResult.Actor->TakeDamage(WeaponData.Damage, DamageEvent , GetInstigatorController(), this);
			FString healthMessage = FString::Printf(
				TEXT("%s"), *HitResult.GetActor()->GetFName().ToString());
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
		}
	}


	
}

void ABaseGunC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
