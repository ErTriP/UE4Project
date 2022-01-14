#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BaseGunC.generated.h"

USTRUCT()
struct FWeaponData
{
	GENERATED_BODY()

	int32 MaxAmmo;
	int32 CurrAmmo;
	float Damage;
	float FireRate;
	float Range;
	TSubclassOf<UDamageType> DamageType;

	FWeaponData()
	{
		MaxAmmo = 30;
		CurrAmmo = MaxAmmo;
		Damage = 10.f;
		FireRate = 0.35;
		Range = 6000.f;
	}
};

UENUM()
enum class EWeaponStatus : uint8
{
	Idle,
	Firering,
	Realoding,
	MAX
};

UCLASS()
class PRACTICE_API ABaseGunC : public AActor
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;	
		
	ABaseGunC();

	FWeaponData WeaponData;
	EWeaponStatus WeaponStatus;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void StartFire();
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StopFire();  

	UFUNCTION(Server, Reliable)
	void HandleFire();

	FTimerHandle FireRateTimer;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* Mesh; 
	

public:	
	
	virtual void Tick(float DeltaTime) override;

};
