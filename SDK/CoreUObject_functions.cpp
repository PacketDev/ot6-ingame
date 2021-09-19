﻿// Name: Fortnite, Version: OT-6_5

#pragma once
#include "pch.h"
#include "../pch.h"

/*!!DEFINE!!*/

/*!!HELPER_DEF!!*/

/*!!HELPER_INC!!*/

#ifdef _MSC_VER
	#pragma pack(push, 0x01)
#endif

namespace CG
{
//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

typedef void(__thiscall* fGetFullName)(const UObject*, FString&, UObject*);
fGetFullName _GetFullName = reinterpret_cast<fGetFullName>(reinterpret_cast<uintptr_t>(GetModuleHandle(0)) + 0x9A4C30);

std::string UObject::GetName() const
{
	std::string name = this->Name.ToString();
	if (Name.Number > 0)
		name += '_' + std::to_string(Name.Number);
	
	auto pos = name.rfind('/');
	if (pos == std::string::npos)
		return name;
	
	return name.substr(pos + 1);
}

std::string UObject::GetFullName() const
{
	if (!this)
		return "";

	FString outName;
	_GetFullName(this, outName, nullptr);

	std::string name = outName.ToString();


	size_t first = name.find_first_of("/");

	if (first != std::string::npos)
	{
		size_t second = name.find_last_of("/");

		size_t eraseLength = second - first;

		if (name.length() > eraseLength)
			name.erase(first, eraseLength + 1);
	}
	
	if (name.find(":") != std::string::npos)
		name.replace(name.find(":"), 1, ".");

	return name;
}

bool UObject::IsA(UClass* cmp) const
{
	for (auto super = Class; super; super = static_cast<UClass*>(super->SuperField))
	{
		if (super == cmp)
		{
			return true;
		}
	}

	return false;
}

// Function CoreUObject.Object.ExecuteUbergraph
// (Event, Public, BlueprintEvent)
// Parameters:
// int                            EntryPoint                     (Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
void UObject::ExecuteUbergraph(int EntryPoint)
{
	static UFunction* fn = UObject::FindObject<UFunction>("Function CoreUObject.Object.ExecuteUbergraph");

	UObject_ExecuteUbergraph_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);
	fn->FunctionFlags = flags;

}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
