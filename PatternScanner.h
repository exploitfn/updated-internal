#pragma once
#include <string>
#include <vector>
__forceinline uintptr_t ResolveRelativeAddress(uintptr_t Address, int InstructionLength)
{
	DWORD Offset = *(DWORD*)(Address + (InstructionLength - 4));
	return Address + InstructionLength + Offset;
}
__forceinline uintptr_t PScan(std::string pattern, int result = 0)
{
	uintptr_t moduleAdress = *(uint64_t*)(__readgsqword(0x60) + 0x10);
	static auto patternToByte = [](const char* pattern)
	{
		auto bytes = std::vector<int>{};
		const auto start = const_cast<char*>(pattern);
		const auto end = const_cast<char*>(pattern) + strlen(pattern);
		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else
			{
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	const auto dosHeader = (PIMAGE_DOS_HEADER)moduleAdress;
	const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)moduleAdress + dosHeader->e_lfanew);
	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = patternToByte(pattern.c_str());
	const auto scanBytes = reinterpret_cast<std::uint8_t*>(moduleAdress);
	const auto s = patternBytes.size();
	const auto d = patternBytes.data();
	int CurrentRes = 0;

	for (auto i = 0ul; i < sizeOfImage - s; ++i)
	{
		bool found = true;
		for (auto j = 0ul; j < s; ++j)
		{
			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			if (!result)
				return reinterpret_cast<uintptr_t>(&scanBytes[i]);
			if (result)
			{
				if (result > CurrentRes)
				{
					CurrentRes++;
					found = false;
				}
				else
					return reinterpret_cast<uintptr_t>(&scanBytes[i]);
			}
		}
	}
	return NULL;
}
