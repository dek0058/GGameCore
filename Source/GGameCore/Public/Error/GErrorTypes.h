// Copyright (c) 2025 cannot206.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "GErrorTypes.generated.h"

UENUM(BlueprintType)
enum class EGErrType : uint8
{
	None,
	Verbose,
	Warning,
	Error
};

USTRUCT(BlueprintType)
struct FGErrorInfo : public FTableRowBase
{
	GENERATED_BODY()

	FGErrorInfo() {}

	FGErrorInfo(EGErrType InErrType, const FString& InErrCode, const FText& InDescription)
		: ErrType(InErrType)
		, ErrCode(InErrCode)
		, Description(InDescription)
	{
	}

	virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName) override
	{
		if (!InDataTable)
		{
			return;
		}

		auto Row = InDataTable->FindRow<FGErrorInfo>(InRowName, TEXT(""));
		if (!Row)
		{
			return;
		}

		Row->ErrCode = InRowName.ToString();
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGErrType ErrType = EGErrType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ErrCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
};
