//
// Created by Apple on 08/09/2019.
//

#include "SDK.hxx"

ClientClass* CHLClient::GetAllClasses() noexcept{
	typedef ClientClass* ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 8)(this);
}

Vector& BaseEntity::GetAbsOrigin() noexcept{
	typedef Vector& ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 9)(this);
}

Vector& BaseEntity::GetAbsAngles() noexcept{
	typedef Vector& ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 10)(this);
}

void BaseEntity::GetWorldSpaceCenter(Vector& vWorldSpaceCenter) noexcept{
	Vector vMin, vMax;
	this->GetRenderBounds(vMin, vMax);
	vWorldSpaceCenter = this->GetAbsOrigin();
	vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2;
}

DWORD* BaseEntity::GetModel() noexcept{
	auto pRenderable = reinterpret_cast<PVOID>(this + 0x4);
	typedef DWORD* ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(pRenderable, 9)(pRenderable);
}

bool BaseEntity::SetupBones(matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) noexcept{
	auto pRenderable = reinterpret_cast<PVOID>(this + 0x4);
	typedef bool ( __thiscall* OriginalFn )(PVOID, matrix3x4*, int, int, float);
	return getvfunc<OriginalFn>(pRenderable, 16)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}

ClientClass* BaseEntity::GetClientClass() noexcept{
	auto pNetworkable = reinterpret_cast<PVOID>(this + 0x8);
	typedef ClientClass* ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
}

int BaseEntity::GetObserverMode() noexcept{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_iObserverMode");
}

int BaseEntity::GetObserverTarget() noexcept{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_hObserverTarget");
}

bool BaseEntity::IsDormant() noexcept{
	auto pNetworkable = reinterpret_cast<PVOID>(this + 0x8);
	typedef bool ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(pNetworkable, 8)(pNetworkable);
}

int BaseEntity::GetIndex() noexcept{
	auto pNetworkable = reinterpret_cast<PVOID>(this + 0x8);
	typedef int ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(pNetworkable, 9)(pNetworkable);
}

void BaseEntity::GetRenderBounds(Vector& minS, Vector& maxS) noexcept{
	auto pRenderable = reinterpret_cast<PVOID>(this + 0x4);
	typedef void ( __thiscall* OriginalFn )(PVOID, Vector&, Vector&);
	getvfunc<OriginalFn>(pRenderable, 20)(pRenderable, minS, maxS);
}

int BaseEntity::GetFlags() noexcept{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_fFlags");
}

BYTE BaseEntity::GetLifeState() noexcept{
	DYNVAR_RETURN(BYTE, this, "DT_BasePlayer", "m_lifeState");
}


void EngineClient::GetScreenSize(int& width, int& height) noexcept{
	typedef void ( __thiscall* OriginalFn )(PVOID, int&, int&);
	return getvfunc<OriginalFn>(this, 5)(this, width, height);
}

bool EngineClient::GetPlayerInfo(int entNum, PlayerInfo* pInfo) noexcept{
	typedef bool ( __thiscall* OriginalFn )(PVOID, int, PlayerInfo*);
	return getvfunc<OriginalFn>(this, 8)(this, entNum, pInfo);
}

bool EngineClient::ConIsVisible() noexcept{
	typedef bool ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 11)(this);
}

int EngineClient::GetLocalPlayer() noexcept{
	typedef int ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 12)(this);
}

float EngineClient::Time() noexcept{
	typedef float ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 14)(this);
}

void EngineClient::GetViewAngles(Vector& va) noexcept{
	typedef void ( __thiscall* OriginalFn )(PVOID, Vector& va);
	return getvfunc<OriginalFn>(this, 19)(this, va);
}

void EngineClient::SetViewAngles(Vector& va) noexcept{
	typedef void ( __thiscall* OriginalFn )(PVOID, Vector& va);
	return getvfunc<OriginalFn>(this, 20)(this, va);
}

int EngineClient::GetMaxClients() noexcept{
	typedef int ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 21)(this);
}

bool EngineClient::IsInGame() noexcept{
	typedef bool ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 26)(this);
}

bool EngineClient::IsConnected() noexcept{
	typedef bool ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 27)(this);
}

bool EngineClient::IsDrawingLoadingImage() noexcept{
	typedef bool ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 28)(this);
}

const matrix3x4& EngineClient::WorldToScreenMatrix() noexcept{
	typedef const matrix3x4& ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 36)(this);
}

bool EngineClient::IsTakingScreenshot() noexcept{
	typedef bool ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 85)(this);
}

DWORD* EngineClient::GetNetChannelInfo() noexcept{
	typedef DWORD* ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 72)(this);
}

void EngineClient::ClientCmdUnrestricted(const char* chCommandString) noexcept{
	typedef void ( __thiscall* OriginalFn )(PVOID, const char*);
	return getvfunc<OriginalFn>(this, 106)(this, chCommandString);
}


const char* Panel::GetName(unsigned int vGuiPanel) noexcept{
	typedef const char* ( __thiscall* OriginalFn )(PVOID, unsigned int);
	return getvfunc<OriginalFn>(this, 36)(this, vGuiPanel);
}

void Surface::DrawSetColor(int r, int g, int b, int a) noexcept{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	getvfunc<OriginalFn>(this, 11)(this, r, g, b, a);
}

void Surface::DrawFilledRect(int x0, int y0, int x1, int y1) noexcept{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	getvfunc<OriginalFn>(this, 12)(this, x0, y0, x1, y1);
}

void Surface::DrawOutlinedRect(int x0, int y0, int x1, int y1) noexcept{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	getvfunc<OriginalFn>(this, 14)(this, x0, y0, x1, y1);
}

void Surface::DrawSetTextFont(unsigned long font) noexcept{
	typedef void(__thiscall* OriginalFn)(PVOID, unsigned long);
	getvfunc<OriginalFn>(this, 17)(this, font);
}

void Surface::DrawSetTextColor(int r, int g, int b, int a) noexcept{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	getvfunc<OriginalFn>(this, 19)(this, r, g, b, a);
}

void Surface::DrawSetTextPos(int x, int y) noexcept{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int);
	getvfunc<OriginalFn>(this, 20)(this, x, y);
}

void Surface::DrawPrintText(const wchar_t* text, int textLen) noexcept{
	typedef void(__thiscall* OriginalFn)(PVOID, const wchar_t*, int, int);
	return getvfunc<OriginalFn>(this, 22)(this, text, textLen, 0);
}

unsigned long Surface::CreateFontA() noexcept{
	typedef unsigned int(__thiscall* OriginalFn)(PVOID);
	return getvfunc<OriginalFn>(this, 66)(this);
}

void Surface::SetFontGlyphSet(unsigned long& font, const char* windowsFontName, int tall, int weight, int blur,
							  int scanlines, int flags) noexcept{
	typedef void(__thiscall* OriginalFn)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
	getvfunc<OriginalFn>(this, 67)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
}

void Surface::GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall) noexcept{
	typedef void(__thiscall* OriginalFn)(PVOID, unsigned long, const wchar_t*, int&, int&);
	getvfunc<OriginalFn>(this, 75)(this, font, text, wide, tall);
}

void Surface::DrawLine(int x0, int y0, int x1, int y1) noexcept{
	typedef void(__thiscall* DrawLineFn)(void*, int, int, int, int);
	getvfunc<DrawLineFn>(this, 15)(this, x0, y0, x1, y1);
}

BaseEntity* EntList::GetClientEntity(int entNum) noexcept{
	typedef BaseEntity* ( __thiscall* OriginalFn )(PVOID, int);
	return getvfunc<OriginalFn>(this, 3)(this, entNum);
}

BaseEntity* EntList::GetClientEntityFromHandle(int hEnt) noexcept{
	typedef BaseEntity* ( __thiscall* OriginalFn )(PVOID, int);
	return getvfunc<OriginalFn>(this, 4)(this, hEnt);
}

int EntList::GetHighestEntityIndex(void) noexcept{
	typedef int ( __thiscall* OriginalFn )(PVOID);
	return getvfunc<OriginalFn>(this, 6)(this);
}

bool ClientModeShared::IsChatPanelOutOfFocus() noexcept{
	typedef PVOID(__thiscall* OriginalFn)(PVOID);
	PVOID CHudChat = getvfunc<OriginalFn>(this, 19)(this);
	if(CHudChat){
		return !*reinterpret_cast<PFLOAT>(reinterpret_cast<DWORD>(CHudChat) + 0xFC);
	}
	return false;
}
