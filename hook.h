#pragma once
bool __forceinline Main()
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, ("CONOUT$"), ("w"), stdout);
	CachedData::Base = *(uint64_t*)(__readgsqword(0x60) + 0x10);
	auto scanneduworld = ResolveRelativeAddress(PScan(("48 89 05 ?? ?? ?? ?? 0F 28 D7")), 7);
	GetNameByIndex = decltype(GetNameByIndex)(PScan(("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 8B 19 4C 8B F2 E8 ? ? ? ? 8B D3 0F B7 CB C1 EA 10 89 54 24 20")));
        GetBoneMatrix = PScan(("E8 ? ? ? ? 0F 10 40 68"));
	GetBoneMatrix = RVA(GetBoneMatrix, 5);
	auto GWorld = *(uintptr_t*)(scanneduworld);
	auto World = (UWorld*)GWorld;
	auto Game = World->GameInstance();
	auto LocalPlayers = Game->LocalPlayers();
	auto LocalPlayer = LocalPlayers->LocalPlayer();
	auto Controller = LocalPlayer->PlayerController();
	auto Viewport = LocalPlayer->ViewPortClient();
	UKismetStringLibrary::SetupKeys();
	auto index = 110;
	vmt((void*)(std::uintptr_t)Viewport, Hook, index, (void**)&Orig);
	return true;
}