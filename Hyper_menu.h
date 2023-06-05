#pragma once 
#include "menu_render.hh"
#include "PatternScanner.h"
bool menu_opened = true;
struct FMinimalViewInfo {
	Vector3 Location;
	Vector3 Rotation;
	float FOV;
	float OrthoWidth;
	float OrthoNearClipPlane;
	float OrthoFarClipPlane;
	float AspectRatio;
};
APlayerController* PlayerController;
AFortPawn* LocalPawno;

void lit_menu()
{
	static Vector2 pos = Vector2(700, 700);
	if (KGUI::Window("[Hyper - lite]", &pos, Vector2{ 300.f, 490.f }, menu_opened))
	{
		static int tab = 1;
		if (KGUI::ButtonTab("Aimbot", Vector2{ 90, 25 }, tab == 0)) tab = 0;
		KGUI::NextColumn(100);
		if (KGUI::ButtonTab("Esp", Vector2{ 90, 25 }, tab == 1)) tab = 1;
		KGUI::NextColumn(200.0f);
		if (KGUI::ButtonTab("Misc", Vector2{ 90, 25 }, tab == 2)) tab = 2;
		KGUI::drawRect(Vector2(pos.x + 10, pos.y + 88), 280, 390,FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		if (tab == 0)
		{
			KGUI::PushElementX(5);
			KGUI::PushElementY(55);
			KGUI::FakeElement();
			KGUI::Text((" "));
			//KGUI::TextLeft(("Aimbot"), Vector2(pos.x + 15, pos.y + 15), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), false, false);
			KGUI::Checkbox("Aimbot", &config.AIm);
			KGUI::Checkbox("Fov Circle", &config.Fov_cricle);
			KGUI::SliderFloat("Fov Value", &config.Fov_cricle_value, 10, 100);

		}
		if (tab == 1)
		{
			KGUI::PushElementX(5);
			KGUI::PushElementY(55);
			KGUI::FakeElement();
			KGUI::Text((" "));
			KGUI::TextLeft(("Visuals"), Vector2(pos.x + 15, pos.y + 65), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), false, false);
			KGUI::Checkbox("Player Box", &config.Box);
			KGUI::Checkbox("Player Skeleton", &config.SkeletonESP);
			KGUI::Checkbox("Player SnapLine", &config.SnapLines);
			KGUI::Checkbox("Player Distance", &config.distance);

			KGUI::PushElementX(150);
			KGUI::PushElementY(55);
			KGUI::FakeElement();
			KGUI::Text((" "));
			KGUI::TextLeft(("World"), Vector2(pos.x + 170, pos.y + 65), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), false, false);
			//KGUI::Checkbox("Vehicle", &config.Cars);

		}
		if (tab == 2)
		{
			KGUI::PushElementX(5);
			KGUI::PushElementY(55);
			KGUI::FakeElement();
			KGUI::Text((" "));
			KGUI::Checkbox("Visible Check", &config.visble_check);
			//KGUI::Checkbox("Infinite Slide", &config.walk_slide);
			//KGUI::SliderFloat("Slide Time", &config.slide_time, 0, 100000);
		}
	}

}
Vector3 OriginalLocation;
Vector3 OriginalRotation;
Vector3 rot;
void(*o_GetViewPoint)(uintptr_t, FMinimalViewInfo*, BYTE) = nullptr;
void hk_GetViewPoint(uintptr_t this_LocalPlayer, FMinimalViewInfo* OutViewInfo, BYTE StereoPass)
{
	o_GetViewPoint(this_LocalPlayer, OutViewInfo, StereoPass);
	if ((uintptr_t(LocalPawno)))
	{
		//static bool GetCameraLocation = true;
		//static Vector3 NewLocation;

		//if (GetCameraLocation) {
		//	// Set our new location to the original spot once
		//	NewLocation = OutViewInfo->Location;
		//	GetCameraLocation = false;
		//}

		if (config.SilentAim)
		{
			if (PlayerController->IsInputKeyDown(FKey(keys::LeftClick)))
			{
				OutViewInfo->Rotation = OriginalRotation;
				OutViewInfo->Location = OriginalLocation;
				//OutViewInfo->Location = rot;

			}

			/*if (safe_call(GetAsyncKeyState)('W')) NewLocation.x += 5.f;
			else if (safe_call(GetAsyncKeyState)('S')) NewLocation.x -= 5.f;
			else if (safe_call(GetAsyncKeyState)('A')) NewLocation.y += 5.f;
			else if (safe_call(GetAsyncKeyState)('D')) NewLocation.y -= 5.f;
			else if (safe_call(GetAsyncKeyState)(VK_SPACE)) NewLocation.z += 5.f;
			else if (safe_call(GetAsyncKeyState)(VK_SHIFT)) NewLocation.z -= 5.f;

			OutViewInfo->Location = NewLocation;*/

			//OutViewInfo->Location = OriginalLocation;
		}
		//OutViewInfo->FOV = 1000;


	}
}