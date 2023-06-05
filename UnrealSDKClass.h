#pragma once
#include <cstdint>
#include "UE5Structure.h"
#include "PatternScanner.h"
#include "spoof.h"
#include "config.h"
#include "Engine.h"
#include "PatternScanner.h"
uintptr_t LineSightOfTo;
uintptr_t GetBoneMatrix;
#define RVA(addr, size) ((uintptr_t)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))
typedef FString* (__fastcall* tGetNameByIndex)(int* index, FString* res);
static tGetNameByIndex GetNameByIndex = nullptr;

namespace CachedData
{
	uint64_t Base;
}

struct FKey
{
	struct FName KeyName;
	unsigned char UnknownData00[0x10];
};

inline void cFixName(char* Name)
{
	for (int i = 0; Name[i] != '\0'; i++)
	{
		if (Name[i] == '_')
		{
			if (Name[i + 1] == '0' ||
			Name[i + 1] == '1' ||
			Name[i + 1] == '2' ||
			Name[i + 1] == '3' ||
			Name[i + 1] == '4' ||
			Name[i + 1] == '5' ||
			Name[i + 1] == '6' ||
			Name[i + 1] == '7' ||
			Name[i + 1] == '8' ||
			Name[i + 1] == '9')
			Name[i] = '\0';
		}
	}
	return;
}

std::string GetById(int index)
{
	FString result;
	hide(GetNameByIndex, &index, &result);
	if (result.c_str() == NULL) return (char*)"";
	auto tmp = result.ToString();
	char return_string[1024] = {};
	for (size_t i = 0; i < tmp.size(); i++)
	{
		return_string[i] += tmp[i];
	}
	cFixName(return_string);
	return std::string(return_string);
}

struct UCanvas
{
public:

	__forceinline void ADrawText(Vector2 ScreenPosition, FString RenderText, FLinearColor RenderColor, bool centered, bool bOutlined)
	{
		struct textparams
		{
			UObject* RenderFont;
			FString RenderText;
			Vector2 ScreenPosition;
			Vector2 Scale;
			FLinearColor RenderColor;
			double Kerning;
			FLinearColor ShadowColor;
			Vector2 ShadowOffset;
			bool bCentreX;
			bool bCentreY;
			bool bOutlined;
			FLinearColor OutlineColor;
		};
		static uintptr_t fn = NULL;
		static uintptr_t font = NULL;
		static bool setonce = false;
		if (!setonce)
		{
			fn = UObject::FindObject(("Function Engine.Canvas.K2_DrawText"));
			font = UObject::FindObject(("Font Roboto.Roboto"));
			setonce = true;
		}
		textparams params;
		params.RenderFont = (UObject*)font;
		params.RenderText = RenderText;
		params.ScreenPosition = ScreenPosition;
		params.Scale = Vector2{ 1.f, 1.f };
		params.RenderColor = RenderColor;
		params.Kerning = false;
		params.ShadowColor = FLinearColor{ 0.0f, 0.0f, 0.0f, 0.0f };
		params.ShadowOffset = ScreenPosition;
		if (centered) { params.bCentreX = true; params.bCentreY = true; }
		else { params.bCentreX = false; params.bCentreY = false; }
		params.bOutlined = bOutlined;
		params.OutlineColor = { 0.0f, 0.0f, 0.0f, 1.f };
		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);
	}

	void text(UCanvas* canvas, FString content, Vector2 location, FLinearColor color, bool center, bool outline)
	{
		canvas->ADrawText(location, content, color, false, false);
	}

	auto DrawLine(Vector2 a, Vector2 b, float thickness, FLinearColor rendercolor) -> void
	{
		static uintptr_t fn = NULL;
		if (!fn)
		{
			fn = UObject::FindObject(("Function Engine.Canvas.K2_DrawLine"));
		}

		struct
		{

			Vector2 a, b;
			float thickness;
			FLinearColor rendercolor;

		} params = { a, b, thickness, rendercolor };

		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);
	}

	__forceinline Vector2 SZE() const
	{
		return 
		{
			ScreenX, ScreenY 
		};
	};
private:
	uint8_t Padding_0[0x40];
	int ScreenX;
	int ScreenY;
};

struct ARootComponent
{
public:

	Vector3 RelativeLocation()
	{

		return *(Vector3*)(this + 0x128);

	}

};

struct AFortPawn
{
public:

	ARootComponent* RootComponent()
	{

		return (ARootComponent*)*(uint64_t*)(this + 0x190);

	}

	uint64_t Mesh()
	{

		return *(uint64_t*)(this + 0x310);

	}

	Vector3 GetBoneLocation(int Id)
	{

		auto mesh = Mesh();

		if (!mesh) return { 0, 0, 0 };

		auto function = ((FMatrix * (__fastcall*)(uintptr_t, FMatrix*, int))(GetBoneMatrix));

		function(mesh, mMatrix, Id);return { mMatrix->M[3][0], mMatrix->M[3][1], mMatrix->M[3][2]};

	}

};
struct APlayerController
{
public:

	AFortPawn* AcknowledgedPawn()
	{

		return (AFortPawn*)*(uintptr_t*)(this + 0x330);

	}

	bool w2s(Vector3 world, Vector2* screen)
	{
		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = UObject::FindObject(("Function Engine.PlayerController.ProjectWorldLocationToScreen"));
		}

		struct
		{
			Vector3 world;
			Vector2 screen;
			bool relative_viewport;
			bool return_value;
		} 

		params = { world, Vector2(), true };

		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);

		*screen = params.screen;

		return params.return_value;

	}

	bool IsInputKeyDown(const struct FKey& Key)
	{

		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = UObject::FindObject(("Function Engine.PlayerController.IsInputKeyDown"));
		}

		struct keystruct
		{
			struct FKey Key;
			bool ReturnValue;

		};

		keystruct params;

		params.Key = Key;

		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);

		return params.ReturnValue;

	}

	bool GetMousePosition(float* LocationX, float* LocationY)
	{

		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = UObject::FindObject(("Function Engine.PlayerController.GetMousePosition"));
		}

		struct APlayerController_GetMousePosition_Params
		{
			float LocationX;
			float LocationY;
			bool ReturnValue;
		};

		APlayerController_GetMousePosition_Params params;

		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);

		if (LocationX != nullptr)

		*LocationX = params.LocationX;

		if (LocationY != nullptr)

		*LocationY = params.LocationY;

		return params.ReturnValue;

	}

	bool WasInputKeyJustPressed(const struct FKey& Key)
	{
		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = UObject::FindObject(("Function Engine.PlayerController.WasInputKeyJustPressed"));
		}

		struct keystruct
		{
		
			struct FKey Key;	
			bool ReturnValue;

		};

		keystruct params;

		params.Key = Key;

		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);

		return params.ReturnValue;

	}

	BOOLEAN LineOfSightTo(AFortPawn* Actor)
	{

		Vector3 ViewPoint = { 0,0,0 };

		auto LOSTo = reinterpret_cast<bool(__fastcall*)(APlayerController * PlayerController, AFortPawn * Actor, Vector3 * ViewPoint)>(LineSightOfTo);

		return LOSTo(this, Actor, &ViewPoint);

	}

};

class UGameViewportClient
{
public:


};

class ULocalPlayer 
{
public:

	APlayerController* PlayerController() 
	{

		return (APlayerController*)(*(uintptr_t*)(this + 0x30));

	}

	UGameViewportClient* ViewPortClient()
	{

		return (UGameViewportClient*)(*(uintptr_t*)(this + 0x78));

	}

};

class ULocalPlayers 
{
public:

	ULocalPlayer* LocalPlayer() 
	{

	return (ULocalPlayer*)(*(uintptr_t*)(this));

	}

};

class UGameInstance 
{
public:

	ULocalPlayers* LocalPlayers() 
	{

	return (ULocalPlayers*)(*(uintptr_t*)(this + 0x38));

	}

};

struct UWorld
{
public:

	UGameInstance* GameInstance()
	{

		return (UGameInstance*)*(uintptr_t*)(this + 0x1B8);

	}

};

namespace keys
{
	FKey Insert;
	FKey RightClick;
	FKey LeftClick;
}

class UGameplayStatics
{
public:

	void GetAllActorsOfClass(UWorld* WorldContextObject, UClass* ActorClass, TArray<AFortPawn*>* OutActors)
	{

		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = UObject::FindObject(("Function Engine.GameplayStatics.GetAllActorsOfClass"));
		}

		struct UGameplayStatics_GetAllActorsOfClass_Params
		{
			UWorld* WorldContextObject;
			UClass* ActorClass;
			TArray<AFortPawn*> OutActors;
		};

		UGameplayStatics_GetAllActorsOfClass_Params params;

		params.WorldContextObject = WorldContextObject;

		params.ActorClass = ActorClass;

		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);

		if (OutActors != nullptr) *OutActors = params.OutActors;

	}

	static UGameplayStatics* StaticClass()
	{

		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = UObject::FindObject(("Class Engine.GameplayStatics"));
		}

		return (UGameplayStatics*)fn;

	}

};

class UKismetStringLibrary
{
public:

	struct FName Conv_StringToName(const struct FString& inString)
	{

		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = UObject::FindObject(("Function Engine.KismetStringLibrary.Conv_StringToName"));
		}

		struct UKismetStringLibrary_Conv_StringToName_Params
		{
			struct FString inString;
			struct FName ReturnValue;
		};

		UKismetStringLibrary_Conv_StringToName_Params params;
		params.inString = inString;
		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);
		return params.ReturnValue;

	}

	static UKismetStringLibrary* StaticClass()
	{
		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = UObject::FindObject(("Class Engine.KismetStringLibrary"));
		}

		return (UKismetStringLibrary*)fn;
	}

	static inline void SetupKeys()
	{

		UKismetStringLibrary* KismetStringLib = UKismetStringLibrary::StaticClass();
		keys::Insert = FKey{ FName{ KismetStringLib->Conv_StringToName((L"Insert")) }, 0 };
		keys::LeftClick = FKey{ FName{ KismetStringLib->Conv_StringToName((L"LeftMouseButton")) }, 0 };
		keys::RightClick = FKey{ FName{ KismetStringLib->Conv_StringToName((L"RightMouseButton")) }, 0 };
	}

};

class UFortKismetLibrary
{
public:
	TArray<AFortPawn*> GetFortPawn(UObject* WorldContextObject)
	{
		static uintptr_t fn = NULL;
		if (!fn)
			fn = UObject::FindObject(("Function FortniteGame.FortKismetLibrary.GetFortPlayerPawns"));
		struct GetFortPlayerPawns_Params
		{
			UObject* WorldContextObject;
			TArray<AFortPawn*> ReturnValue;
		};
		GetFortPlayerPawns_Params params;
		params.WorldContextObject = WorldContextObject;
		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);
		return params.ReturnValue;
	}
	static UFortKismetLibrary* StaticClass()
	{
		static uintptr_t fn = NULL;
		if (!fn)
			fn = UObject::FindObject(("Class FortniteGame.FortKismetLibrary"));
		return (UFortKismetLibrary*)fn;
	}
};
void* Orig;
auto Gworld = ResolveRelativeAddress(PScan(("48 89 05 ?? ?? ?? ?? 0F 28 D7")), 7);
AFortPawn* AcknowledgedPawn;
void vmt(void* addr, void* pDes, int index, void** ret)
{
	auto vtable = *(std::uintptr_t**)addr;
	int methods = 0;
	do 
	{
		++methods;
	} while (*(std::uintptr_t*)((std::uintptr_t)vtable + (methods * 0x8)));
	auto vtable_buf = new uint64_t[methods * 0x8];
	for (auto count = 0; count < methods; ++count) 
	{
		vtable_buf[count] = *(std::uintptr_t*)((std::uintptr_t)vtable + (count * 0x8));

		*ret = (void*)vtable[index];

		vtable_buf[index] = (std::uintptr_t)(pDes);
		*(std::uintptr_t**)addr = vtable_buf;
	}
}
