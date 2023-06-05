#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

template<class T>
struct TArray
{
public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline void Clear()
	{
		Data = nullptr;
		Count = Max = 0;
	}

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}

	inline void Add(T A)
	{
		if (!Data)
			Data = (T*)malloc(4096);

		Max = 4096 / sizeof(T);
		Data[Count] = A;
		Count++;
	}

	inline void Free()
	{
		free(Data);
		Count = Max = 0;
	}

	T* Data;
	int32_t Count;
	int32_t Max;
};

class FTextData {
public:
	char pad_0x0000[0x28];  //0x0000
	wchar_t* Name;          //0x0028 
	__int32 Length;         //0x0030 
};

struct FText {
	FTextData* Data;
	char UnknownData[0x10];

	wchar_t* GetText() const {
		if (Data)
			return Data->Name;

		return nullptr;
	}
};

struct FString : private TArray<wchar_t>
{
	inline FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

struct Vector2
{
	double x, y;

	Vector2() : x(0.f), y(0.f)
	{

	}

	Vector2(double _x, double _y) : x(_x), y(_y)
	{

	}

	Vector2(int _x, int _y) : x(_x), y(_y)
	{

	}
	~Vector2()
	{

	}

	__forceinline bool IsNull()
	{
		return (!x && !y);
	}

	__forceinline bool IsOutOfBounds(int X, int Y)
	{
		if (x >= X || y >= Y)
			return false;
		else if (x <= 0 || y <= 0)
			return false;
	}

	__forceinline bool IsOutOfBounds(Vector2 v)
	{
		if ((x > v.x && y > v.y) || (x <= 0 && y <= 0))
			return true;

		return false;
	}

	__forceinline Vector2 operator+(Vector2 v)
	{
		return Vector2(x + v.x, y + v.y);
	}

	__forceinline Vector2 operator-(Vector2 v)
	{
		return Vector2(x - v.x, y - v.y);
	}

	__forceinline Vector2 operator+(float v)
	{
		return Vector2(x + v, y + v);
	}

	__forceinline Vector2 operator-(float v)
	{
		return Vector2(x - v, y - v);
	}

	__forceinline Vector2 operator+=(Vector2 v)
	{
		x += v.x;
		y += v.y;
		return Vector2(x, y);
	}

	__forceinline Vector2 operator-=(Vector2 v)
	{
		x -= v.x;
		y -= v.y;
		return Vector2(x, y);
	}

	__forceinline Vector2 operator/(Vector2 v)
	{
		return Vector2(x / v.x, y / v.y);
	}

	__forceinline Vector2 operator/(float v)
	{
		return Vector2(x / v, y / v);
	}

	void operator=(Vector2 _A)
	{
		x = _A.x;
		y = _A.y;
	}

	__forceinline Vector2 operator*(float flNum)
	{
		return Vector2(x * flNum, y * flNum);
	}
};

class Vector3
{
public:
	double x, y, z;

	__forceinline Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	__forceinline Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{

	}
	__forceinline ~Vector3()
	{

	}

	__forceinline bool IsNull()
	{
		return (!x && !y && !z);
	}

	__forceinline double DistanceFrom(const Vector3& Other) const {
		const Vector3& a = *this;
		double dx = (a.x - Other.x);
		double dy = (a.y - Other.y);
		double dz = (a.z - Other.z);

		return (sqrt((dx * dx) + (dy * dy) + (dz * dz)));
	}

	__forceinline Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	__forceinline Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	__forceinline Vector3 operator+(float v)
	{
		return Vector3(x + v, y + v, z + v);
	}

	__forceinline Vector3 operator-(float v)
	{
		return Vector3(x - v, y - v, z - v);
	}

	__forceinline Vector3 operator+=(Vector3 v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return Vector3(x, y, z);
	}

	__forceinline Vector3 operator-=(Vector3 v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return Vector3(x, y, z);
	}

	__forceinline Vector3 operator/(Vector3 v)
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}

	__forceinline Vector3 operator/(float v)
	{
		return Vector3(x / v, y / v, z / v);
	}

	Vector3 operator=(Vector3 _A)
	{
		x = _A.x;
		y = _A.y;
		z = _A.z;

		return Vector3(x, y, z);
	}

	__forceinline Vector3 operator*(float flNum)
	{
		return Vector3(x * flNum, y * flNum, z * flNum);
	}

	inline double Length()
	{
		return sqrt(x * x + y * y + z * z);
	}
};


struct FLinearColor
{
	FLinearColor() : R(0.f), G(0.f), B(0.f), A(0.f)
	{

	}

	FLinearColor(float _R, float _G, float _B, float _A) : R(_R), G(_G), B(_B), A(_A)
	{

	}

	FLinearColor ConvertRGB(Vector3 RGB)
	{
		if (RGB.x == 0)
			RGB.x = 1;
		if (RGB.y == 0)
			RGB.y = 1;
		if (RGB.z == 0)
			RGB.z = 1;
		return { (float)RGB.x / 255.f, (float)RGB.y / 255.f, (float)RGB.z / 255.f, 1.f };
	}

	float R, G, B, A;
};

struct FMatrix
{
	double M[4][4];
}; static FMatrix* mMatrix = new FMatrix();