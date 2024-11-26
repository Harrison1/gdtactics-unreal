#include "MyWidget_List.h"
#include "Components/ListView.h"

void UMyWidget_List::NativeConstruct()
{
	for (AActor* MyActor : MyActors)
	{
		MyList->AddItem(MyActor);
	}
}
