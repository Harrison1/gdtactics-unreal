#include "MyWeapon.h"
#include "MyWeaponsStruct.h"
#include "Engine/DataTable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AMyWeapon::AMyWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MySceneComponent"));
#if WITH_EDITORONLY_DATA
	MySceneComponent->bVisualizeComponent = true;
#endif
	RootComponent = MySceneComponent;

	MySkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MySkeletalMesh"));
	MySkeletalMesh->SetupAttachment(RootComponent);

	MyWeaponNameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("My Weapon Name Text"));
	MyWeaponNameText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	MyWeaponNameText->SetupAttachment(RootComponent);

	MyWeaponDamangeText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("My Weaopn Damage Text"));
	MyWeaponDamangeText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	MyWeaponDamangeText->SetupAttachment(RootComponent);

}

void AMyWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetGun();
}

void AMyWeapon::SetGun()
{
	if (MyDataTable != nullptr)
	{
		TArray<FName> Rows = MyDataTable->GetRowNames();
		static const FString ContextString(TEXT("Finding Row in Weapons Data Table"));

		MyIndex = FMath::Clamp(MyIndex, 0, Rows.Num() - 1);
	
		FMyWeaponsStruct* MyRow = MyDataTable->FindRow<FMyWeaponsStruct>(Rows[MyIndex], ContextString);

		if (MyRow != nullptr)
		{
			MySkeletalMesh->SetSkeletalMeshAsset(MyRow->SkeletalMesh);
			MyWeaponNameText->SetText(FText::FromString(MyRow->Name));
			FText DamageText = FText::FromString(FString::Printf(TEXT("Damage: %.1f"), MyRow->Damage));
			MyWeaponDamangeText->SetText(DamageText);
			
			if (MySkeletalMesh != nullptr && IsValid(MySkeletalMesh->GetMaterial(0)))
			{
				if (MySkeletalMesh->GetMaterial(0)->IsA(UMaterialInstanceDynamic::StaticClass()))
				{
					if (DynamicMaterial != nullptr)
					{
						MySkeletalMesh->SetMaterial(0, DynamicMaterial);
						DynamicMaterial->SetVectorParameterValue(FName("BodyColor"), MyRow->Color);
					}
				}
				else
				{
					UMaterialInterface* Material = MySkeletalMesh->GetMaterial(0);
					if (Material != nullptr)
					{
						DynamicMaterial = UMaterialInstanceDynamic::Create(Material, MySkeletalMesh);
						MySkeletalMesh->SetMaterial(0, DynamicMaterial);
						DynamicMaterial->SetVectorParameterValue(FName("Color"), MyRow->Color);
					}
				}
			}
		}
	}
}
