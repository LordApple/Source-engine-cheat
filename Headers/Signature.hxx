#pragma once

#include "../SDK/SDK.hxx"

class Signature{
public:
	DWORD dwFindPattern(DWORD dwAddress, DWORD dwLength, const char* szPattern);

	HMODULE GetModuleHandleSafe(const char* pszModuleName);

	DWORD GetClientSignature(char* chPattern);

	DWORD GetEngineSignature(char* chPattern);
};

extern Signature gSig;
