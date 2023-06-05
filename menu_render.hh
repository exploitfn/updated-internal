#pragma once
#include "lazy.hpp"
#include "UnrealSDKClass.h"
FLinearColor rgb(float R, float G, float B)
{
	return { R / 255, G / 255, B / 255, 1 };
}
#define MIN(A, B)(((A) < (B)) ? (A) : (B))
#define MAX(A, B)(((A) >= (B)) ? (A) : (B))
UCanvas* canvas;
bool hover_element = false;
Vector2 menu_pos = Vector2{ 0, 0 };
float offset_x = 0.0f;
float offset_y = 0.0f;
Vector2 first_element_pos = Vector2{ 0, 0 };
Vector2 last_element_pos = Vector2{ 0, 0 };
Vector2 last_element_size = Vector2{ 0, 0 };
int current_element = -1;
Vector2 current_element_pos = Vector2{ 0, 0 };
Vector2 current_element_size = Vector2{ 0, 0 };
int elements_count = 0;
bool sameLine = false;
bool pushY = false;
float pushYvalue = 0.0f;
Vector2 dragPos;
APlayerController* PController;
wchar_t* s2wc(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}
namespace GUI
{
	namespace Input
	{
		bool mouseDown[5];
		bool mouseDownAlready[256];
		bool keysDown[256];
		bool keysDownAlready[256];

		bool IsAnyMouseDown()
		{
			if (mouseDown[0]) return true;
			if (mouseDown[1]) return true;
			if (mouseDown[2]) return true;
			if (mouseDown[3]) return true;
			if (mouseDown[4]) return true;

			return false;
		}

		bool IsMouseClicked(int button, int element_id, bool repeat)
		{
			if (mouseDown[button])
			{
				if (!mouseDownAlready[element_id])
				{
					mouseDownAlready[element_id] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				mouseDownAlready[element_id] = false;
			}
			return false;
		}
		bool IsKeyPressed(int key, bool repeat)
		{
			if (keysDown[key])
			{
				if (!keysDownAlready[key])
				{
					keysDownAlready[key] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				keysDownAlready[key] = false;
			}
			return false;
		}

		void Handle()
		{
			if ((GetAsyncKeyState)(0x01))
				mouseDown[0] = true;
			else
				mouseDown[0] = false;
		}
	}
}

namespace KGUI
{
	namespace Colors
	{
		FLinearColor Text{ 1.0f, 1.0f, 1.0f, 1.0f };
		FLinearColor Text_Shadow{ 0.0f, 0.0f, 0.0f, 0.0f };
		FLinearColor Text_Outline{ 0.0f, 0.0f, 0.0f, 0.30f };
		FLinearColor Window_Background{ 0.009f, 0.009f, 0.009f, 1.0f };
		FLinearColor Window_Header{ 0.10f, 0.15f, 0.84f, 1.0f };
		FLinearColor Button_Idle{ 0.10f, 0.15f, 0.84f, 1.0f };
		FLinearColor Button_Hovered{ 0.15f, 0.20f, 0.89f, 1.0f };
		FLinearColor Button_Active{ 0.20f, 0.25f, 0.94f, 1.0f };
		FLinearColor Checkbox_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		FLinearColor Checkbox_Hovered{ 0.22f, 0.30f, 0.72f, 1.0f };
		FLinearColor Checkbox_Enabled{ 0.20f, 0.25f, 0.94f, 1.0f };
		FLinearColor Combobox_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		FLinearColor Combobox_Hovered{ 0.17f, 0.16f, 0.23f, 1.0f };
		FLinearColor Combobox_Elements{ 0.239f, 0.42f, 0.82f, 1.0f };
		FLinearColor Slider_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		FLinearColor Slider_Hovered{ 0.17f, 0.16f, 0.23f, 1.0f };
		FLinearColor Slider_Progress{ 0.22f, 0.30f, 0.72f, 1.0f };
		FLinearColor Slider_Button{ 0.10f, 0.15f, 0.84f, 1.0f };
		FLinearColor ColorPicker_Background{ 0.006f, 0.006f, 0.006f, 1.0f };
	}
	void SetupCanvas(UCanvas* _canvas)
	{
		canvas = _canvas;
	}
	Vector2 CursorPos()
	{
		POINT cursorPos;
		IFH(GetCursorPos)(&cursorPos);
		return Vector2{ (float)cursorPos.x, (float)cursorPos.y };
	}
	bool MouseInZone(Vector2 pos, Vector2 size)
	{
		Vector2 cursor_pos = CursorPos();
		if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
		if (cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y)
		return true;
		return false;
	}
	void SameLine()
	{
		sameLine = true;
	}
	void PushNextElementY(float y, bool from_last_element = true)
	{
		pushY = true;
		if (from_last_element)
			pushYvalue = last_element_pos.y + last_element_size.y + y;
		else
			pushYvalue = y;
	}
	void NextColumn(float x)
	{
		offset_x = x;
		PushNextElementY(first_element_pos.y, false);
	}
	void ClearFirstPos()
	{
		first_element_pos = Vector2{ 0, 0 };
	}
	static void PushElementX(float value)
	{
		offset_x = value;
	}
	static void PushElementY(float value)
	{
		pushY = true;
		pushYvalue = menu_pos.y + value - 10;
	}
	static void TextLeft(const char* name, Vector2 pos, FLinearColor color, bool outline, bool big = false)
	{
		canvas->ADrawText(pos, FString(s2wc(name)),color, false, true);
	}
	static void TextCenter(const char* name, Vector2 pos, FLinearColor color, bool outline, bool big = false)
	{
		canvas->ADrawText(pos, FString(s2wc(name)), color, true, true);
	}
	void Draw_Line(Vector2 from, Vector2 to, int thickness, FLinearColor color)
	{
		canvas->DrawLine(Vector2{ from.x, from.y }, Vector2{ to.x, to.y }, thickness, color);
	}
	void drawRect(const Vector2 initial_pos, float w, float h, const FLinearColor color, float thickness = 1.f)
	{
		canvas->DrawLine(Vector2{ initial_pos.x, initial_pos.y}, Vector2(initial_pos.x + w, initial_pos.y),thickness,color);
		canvas->DrawLine(Vector2{ initial_pos.x, initial_pos.y}, Vector2(initial_pos.x, initial_pos.y + h), thickness, color);
		canvas->DrawLine(Vector2(initial_pos.x + w, initial_pos.y), Vector2(initial_pos.x + w, initial_pos.y + h), thickness, color);
		canvas->DrawLine(Vector2(initial_pos.x, initial_pos.y + h), Vector2(initial_pos.x + w, initial_pos.y + h), thickness, color);
	}

	void drawFilledRect(Vector2 initial_pos, float w, float h, FLinearColor color)
	{
		for (float i = 0.0f; i < h; i += 1.0f)
			canvas->DrawLine(Vector2{ initial_pos.x, initial_pos.y + i }, Vector2{ initial_pos.x + w, initial_pos.y + i }, 1.0f, color);
	}
	void drawReact(Vector2 initial_pos, float w, float h, FLinearColor color)
	{
		canvas->DrawLine(Vector2{ initial_pos.x, initial_pos.y }, Vector2{ initial_pos.x + w, initial_pos.y}, 2.0f, color);
	}
	void DrawFilledCircle(Vector2 pos, float r, FLinearColor color)
	{
		float smooth = 0.07f;
		double PI = 3.14159265359;
		int size = (int)(2.0f * PI / smooth) + 1;
		float angle = 0.0f;
		int i = 0;
		for (; angle < 2 * PI; angle += smooth, i++)
		{
			Draw_Line(Vector2{ pos.x, pos.y }, Vector2{ pos.x + cosf(angle) * r, pos.y + sinf(angle) * r }, 1.0f, color);
		}
	}
	void DrawCircle(Vector2 pos, int radius, FLinearColor Color, int numSides = 450)
	{
#define M_PI 3.14159265358979323846264338327950288419716939937510
		double Step = M_PI * 2.0 / numSides;
		int Count = 0;
		Vector2 V[128];
		for (double a = 0; a < M_PI * 2.0; a += Step) {
			double X1 = radius * cos(a) + pos.x;
			double Y1 = radius * sin(a) + pos.y;
			double X2 = radius * cos(a + Step) + pos.x;
			double Y2 = radius * sin(a + Step) + pos.y;
			V[Count].x = X1;
			V[Count].y = Y1;
			V[Count + 1].x = X2;
			V[Count + 1].y = Y2;
			canvas->DrawLine(Vector2{ V[Count].x, V[Count].y }, Vector2{ X2, Y2 }, 1.f, Color);
		}
	}
	bool Window(const char* name, Vector2* pos, Vector2 size, bool isOpen)
	{
		elements_count = 0;
		if (!isOpen)
		return false;
		bool isHovered = MouseInZone(Vector2{ pos->x, pos->y }, size);
		if (current_element != -1 && !(GetKeyState(VK_LBUTTON)))
		{
			current_element = -1;
		}
		if (hover_element && (GetKeyState(VK_LBUTTON)))
		{
		}
		else if ((isHovered || dragPos.x != 0) && !hover_element)
		{
			if (GUI::Input::IsMouseClicked(0, elements_count, true))
			{
				Vector2 cursorPos = CursorPos();
				cursorPos.x -= size.x;
				cursorPos.y -= size.y;
				if (dragPos.x == 0)
				{
					dragPos.x = (cursorPos.x - pos->x);
					dragPos.y = (cursorPos.y - pos->y);
				}
				pos->x = cursorPos.x - dragPos.x;
				pos->y = cursorPos.y - dragPos.y;
			}
			else
			{
				dragPos = Vector2{ 0, 0 };
			}
		}
		else
		{
			hover_element = false;
		}
		offset_x = 0.0f; offset_y = 0.0f;
		menu_pos = Vector2{ pos->x, pos->y };
		first_element_pos = Vector2{ 0, 0 };
		current_element_pos = Vector2{ 0, 0 };
		current_element_size = Vector2{ 0, 0 };
		drawFilledRect(Vector2{ pos->x, pos->y }, size.x, size.y, {0,0,0,1});
		drawFilledRect(Vector2{ pos->x, pos->y }, size.x, 25.0f, rgb(163, 8, 12));
		offset_y += 25.0f;
		Vector2 titlePos = Vector2{ pos->x + size.x / 2, pos->y + 25 / 2 };
		TextCenter(name, titlePos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
		return true;
	}
	void Text(const char* text, bool center = false, bool outline = false)
	{
		elements_count++;
		float size = 25;
		Vector2 padding = Vector2{ 10, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		if (!sameLine)
		offset_y += size + padding.y;
		Vector2 textPos = Vector2{ pos.x + 5.0f, pos.y + size / 2 };
		if (center)
		TextCenter(text, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
		else
		TextLeft(text, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
		sameLine = false;
		last_element_pos = pos;
		if (first_element_pos.x == 0.0f)
		first_element_pos = pos;
	}
	bool ButtonTab(const char* name, Vector2 size, bool active)
	{
		elements_count++;
		Vector2 padding = Vector2{ 5, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, size);
		if (active)
		{
			drawFilledRect(Vector2{ pos.x - 1, pos.y - 1 }, size.x + 2, size.y + 2, { 1.0f, 1.0f, 1.0f, 1.0f });
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, rgb(163, 8, 12));
			//drawFilledRect(Vector2{ pos.x, pos.y }, size.x, 15.0f, {0,0,0,1});
		}
		else if (isHovered)
		{
			drawFilledRect(Vector2{ pos.x - 1, pos.y - 1 }, size.x + 2, size.y + 2, { 1.0f, 1.0f, 1.0f, 1.0f });
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, { 0, 0, 0, 1 });
			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x - 1, pos.y - 1 }, size.x + 2, size.y + 2, { 1.0f, 1.0f, 1.0f, 1.0f });
			drawFilledRect(Vector2{ pos.x, pos.y }, size.x, size.y, rgb(163, 8, 12));
		}
		if (!sameLine)
		offset_y += size.y + padding.y;
		Vector2 textPos = Vector2{ pos.x + size.x / 2, pos.y + size.y / 2 };
		TextCenter(name, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
		first_element_pos = pos;
		if (isHovered && GUI::Input::IsMouseClicked(0, elements_count, false))
		return true;
		return false;
	}
	static void FakeElement()
	{
		Vector2 size = Vector2(1, 1);elements_count++;Vector2 padding = Vector2{ 1, 1 };Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };if (sameLine)	{  pos.x = last_element_pos.x + last_element_size.x + padding.x;pos.y = last_element_pos.y;}if (pushY){pos.y = pushYvalue;	pushY = false;pushYvalue = 0.0f;offset_y = pos.y - menu_pos.y;}if (!sameLine)offset_y += size.y + padding.y;sameLine = false;last_element_pos = pos;last_element_size = size;if (first_element_pos.x == 0.0f)first_element_pos = pos;return;
	}
	void Checkbox(const char* name, bool* value)
	{
		elements_count++;

		float size = 18;
		Vector2 padding = Vector2{ 10, 10 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y }, Vector2{ size, size });

		//Bg
		if (isHovered)
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size, size, rgb(163, 8, 12));
			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x, pos.y }, size, size, Colors::Checkbox_Idle);
		}

		if (!sameLine)
		{
          offset_y += size + padding.y;
		}
			

		if (*value)
		{
			drawFilledRect(Vector2{ pos.x + 3, pos.y + 3 }, size - 6, size - 6, rgb(163, 8, 12));
		}


		Vector2 textPos = Vector2{ pos.x + size + 10, (pos.y + size / 2) - 7 };
		TextLeft(name, textPos, FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
		sameLine = false;
		last_element_pos = pos;
		if (first_element_pos.x == 0.0f)
		first_element_pos = pos;
		if (isHovered && GUI::Input::IsMouseClicked(0, elements_count, false))
		*value = !*value;
	}
	void SliderFloat(const char* name, float* value, float min, float max, const char* format = "%.0f")
	{
		elements_count++;
		Vector2 size = Vector2{ 210, 40 };
		Vector2 slider_size = Vector2{ 170, 7 };
		Vector2 adjust_zone = Vector2{ 0, 20 };
		Vector2 padding = Vector2{ 10, 15 };
		Vector2 pos = Vector2{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(Vector2{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, Vector2{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

		if (!sameLine)
		offset_y += size.y + padding.y;
		if (isHovered || current_element == elements_count)
		{
			if (GUI::Input::IsMouseClicked(0, elements_count, true))
			{
				current_element = elements_count;

				Vector2 cursorPos = CursorPos();
				*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}
			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Hovered);
			DrawFilledCircle(Vector2{ pos.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Progress);
			DrawFilledCircle(Vector2{ pos.x + slider_size.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Hovered);
			hover_element = true;
		}
		else
		{
			drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Idle);
			DrawFilledCircle(Vector2{ pos.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Progress);
			DrawFilledCircle(Vector2{ pos.x + slider_size.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Idle);
		}
		Vector2 textPos = Vector2{ pos.x, pos.y };
		TextLeft(name, textPos, Colors::Text, false);
		float oneP = slider_size.x / (max - min);
		drawFilledRect(Vector2{ pos.x, pos.y + slider_size.y + padding.y }, oneP * (*value - min), slider_size.y, Colors::Slider_Progress);
		DrawFilledCircle(Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 2.66f + padding.y }, 8.0f, Colors::Slider_Button);
		DrawFilledCircle(Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 2.66f + padding.y }, 4.0f, Colors::Slider_Progress);
		char buffer[32];
		sprintf_s(buffer, format, *value);
		Vector2 valuePos = Vector2{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 20 + padding.y };
		TextCenter(buffer, valuePos, Colors::Text, false);
		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
		first_element_pos = pos;
	}
}