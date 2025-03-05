#include "MyDamageTypes.h"

TSubclassOf<UDamageType> UMyDamageTypes::GetDamageTypeClass(EMyDamageTypes DamageType)
{
	switch (DamageType)
	{
		case EMyDamageTypes::Gas:
			return UGasDamageType::StaticClass();
		case EMyDamageTypes::Fire:
			return UFireDamageType::StaticClass();
		case EMyDamageTypes::Water:
			return UWaterDamageType::StaticClass();
		default:
			return UDamageType::StaticClass();
	}
}
