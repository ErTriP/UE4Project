// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInventoryItemDropped.h"

#include "PracticeCharacter.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseInventoryItemDropped::ABaseInventoryItemDropped()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxCollision->SetBoxExtent(FVector(75.f));

	SetReplicates(true);
}



ABaseInventoryItemDropped::ABaseInventoryItemDropped(ABaseInventoryItem* OwnerItem)
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxCollision->SetBoxExtent(FVector(75.f));

	Mesh->SetStaticMesh(OwnerItem->ItemData.StaticMesh);

	SetReplicates(true);

	Item = OwnerItem;
}

bool ABaseInventoryItemDropped::BeginOverlap_Validate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APracticeCharacter>(OtherActor))
	{
		return true;
	}

	return false;
}

void ABaseInventoryItemDropped::BeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                            AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                            const FHitResult& SweepResult)
{
	Cast<APracticeCharacter>(OtherActor)->InventorySystem->AddSlot(Item);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "SomeActor takes inventory item");
	Destroy();
}


// Called when the game starts or when spawned
void ABaseInventoryItemDropped::BeginPlay()
{
	Super::BeginPlay();
	if(!IsValid(Item))
	{
		Item = GetWorld()->SpawnActor<ABaseInventoryItem>();
		Mesh->SetStaticMesh(Item->ItemData.StaticMesh);
	}
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseInventoryItemDropped::BeginOverlap);
}

// Called every frame
void ABaseInventoryItemDropped::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
