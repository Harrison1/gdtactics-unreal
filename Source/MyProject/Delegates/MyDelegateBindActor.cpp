#include "MyDelegateBindActor.h"

// Sets default values
AMyDelegateBindActor::AMyDelegateBindActor()
{
	PrimaryActorTick.bCanEverTick = false;

	TSharedRef<FLogWriter> LogWriter(new FLogWriter());
	
	WriteToLogDelegate.BindRaw(&LogWriter.Get(), &FLogWriter::WriteToLog);

	/**
	 * Regarding BindSP, I Couldn't get BindSP to work with IsBound or ExecuteIfBound. So Instead I used BindRaw
	 * My BindSP Exammple: WriteToLogDelegate.BindSP(LogWriter, &FLogWriter::WriteToLog);
	 * However, Execute did work fine with BindSP e.g. WriteToLogDelegate.Execute(TEXT("Execute Delegate"));
	 */
}

// Called when the game starts or when spawned
void AMyDelegateBindActor::BeginPlay()
{
	Super::BeginPlay();

	WriteToLogDelegate.ExecuteIfBound(TEXT("Delegate Exectuing if Bound"));
}
