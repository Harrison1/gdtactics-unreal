#pragma once

DECLARE_DELEGATE_OneParam(FStringDelegate, FString);

class FLogWriter
{
public:
	void WriteToLog(FString MyText);
};
