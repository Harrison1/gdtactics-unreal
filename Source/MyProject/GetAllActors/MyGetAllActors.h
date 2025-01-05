#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGetAllActors.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FStatStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString FunctionName;
	
	UPROPERTY(BlueprintReadOnly)
	double Time;

	UPROPERTY(BlueprintReadOnly)
	int32 Total;
};

UCLASS(BlueprintType, Blueprintable)
class MYPROJECT_API UMyStatObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FStatStruct MyStats;	
};

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateStatArray, const TArray<UMyStatObject*>&, StatArray);

UCLASS()
class AMyGetAllActors : public AActor
{
	GENERATED_BODY()

public:
	AMyGetAllActors();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	USceneComponent* MySceneComponent;

	UPROPERTY()
	UWorld* MyWorld;

	UPROPERTY(EditAnywhere)
	int32 SpawnAmount = 1000;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FUpdateStatArray UpdateStatArray;

	UPROPERTY()
	UMyStatObject* ByClass;

	UPROPERTY()
	UMyStatObject* ByClassInt;

	UPROPERTY()
	UMyStatObject* ByInterface;

	UPROPERTY()
	UMyStatObject* ByTag;

	UPROPERTY()
	UMyStatObject* ByRange;

	UPROPERTY()
	UMyStatObject* ByIterator;
	
	UPROPERTY()
	TMap<int32, UMyStatObject*> StatMap;

	UFUNCTION()
	void SpawnTestActors() const;
	
	void LogAndCompare(const FString& GetAllMethod, const double Time, const int32 TotalActors);
	void TestGetAll();
	void TestGetAllTestInt();
	void TestGetAllWithInterface();
	void TestGetAllWithTag();
	void TestGetAllWithRange();
	void TestGetAllWithIterator();
	void CompareTime();
};
