#include "FLogWriter.h"

void FLogWriter::WriteToLog(FString MyText)
{
	UE_LOG(LogTemp, Warning, TEXT("Log Writer Delegate Text: %s"), *MyText);
}
