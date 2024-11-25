#include "MyWidget_List.h"

#include "Components/ListView.h"

void UMyWidget_List::NativeConstruct()
{
	// Call the base class implementation
	UE_LOG(LogTemp, Warning, TEXT("Widget List Constructed"));

	for (AActor* MyActor : MyActors)
	{
		MyList->AddItem(MyActor);
	}
}
