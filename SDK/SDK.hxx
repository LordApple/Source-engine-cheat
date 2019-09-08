#pragma once

#include <Windows.h>
#include <math.h>
#include <xstring>

#include "../Headers/Vector.hxx"
#include "../Headers/dt_recv2.hxx"
#include "../Headers/Signature.hxx"
#include "../Headers/GlobalVars.hxx"

#include "../Hooks/NetVar/NetVar.hxx"

#include "VMT/VMTHooks.hxx"
#include "VMT/getvfunc.hxx"

typedef void* ( __cdecl* CreateInterface_t )(const char*, int*);

typedef void* (* CreateInterfaceFn)(const char* pName, int* pReturnCode);

#define VMTManager toolkit::VMTManager
#define VMTBaseManager toolkit::VMTBaseManager

#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy", on)
#pragma warning( disable : 4244 ) //Possible loss of data

typedef float matrix3x4[3][4];

#define me gInts.Engine->GetLocalPlayer()
#define GetBaseEntity gInts.EntList->GetClientEntity
#define MASK_AIMBOT 0x200400B
#define    FL_ONGROUND (1<<0)
#define FL_DUCKING (1<<1)
#define CONTENTS_HITBOX 0x40000000
#define FLOW_OUTGOING 0
#define FLOW_INCOMING 1
#define PI 3.14159265358979323846f
#define DEG2RAD(x) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG(x) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define square(x) ( x * x )
#define RADPI 57.295779513082f
#define SQUARE(a) a*a
#define BLU_TEAM 3
#define RED_TEAM 2

enum class PlayerControls{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_ALT1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),    // Used by client.dll for when scoreboard is held down
	IN_SPEED = (1 << 17),    // Player is holding the speed key
	IN_WALK = (1 << 18),    // Player holding walk key
	IN_ZOOM = (1 << 19),    // Zoom key for HUD zoom
	IN_WEAPON1 = (1 << 20),    // weapon defines these bits
	IN_WEAPON2 = (1 << 21),    // weapon defines these bits
	IN_BULLRUSH = (1 << 22),
};

enum class SourceLifeStates{
	LIFE_ALIVE,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY,
};

enum class InputEventType{
	IE_ButtonPressed = 0,    // m_nData contains a ButtonCode_t
	IE_ButtonReleased,        // m_nData contains a ButtonCode_t
	IE_ButtonDoubleClicked,    // m_nData contains a ButtonCode_t
	IE_AnalogValueChanged,    // m_nData contains an AnalogCode_t, m_nData2 contains the value

	IE_FirstSystemEvent = 100,
	IE_Quit = IE_FirstSystemEvent,
	IE_ControllerInserted,    // m_nData contains the controller ID
	IE_ControllerUnplugged,    // m_nData contains the controller ID

	IE_FirstVguiEvent = 1000,    // Assign ranges for other systems that post user events here
	IE_FirstAppEvent = 2000,
};

enum class ButtonCode{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,
	KEY_FIRST = 0,
	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
};

struct PlayerInfo{
	char name[32];
	int userID;
	char guid[33];
	unsigned long friendsID;
	char friendsName[32];
	bool fakeplayer;
	bool ishltv;
	unsigned long customFiles[4];
	unsigned char filesDownloaded;
};

struct ClientClass{
private:
	BYTE _chPadding[8];
public:
	char* chName;
	RecvTable* Table;
	ClientClass* pNextClass;
	int iClassID;
};

struct Globals{
	float realTime;
	int frameCount;
	float absoluteFrametime;
	float curTime;
	float frameTime;
	int maxClients;
	int tickCount;
	float intervalPerTick;
	float interpolationAmount;
};

struct UserCmd{
	virtual ~UserCmd(){}; //Destructor 0
	int commandNumber; //4
	int tickCount; //8
	Vector viewAngles; //C
	float forwardMove; //18
	float sideMove; //1C
	float upMove; //20
	int buttons; //24
	std::byte impulse; //28
	int weaponSelect; //2C
	int weaponSubtype; //30
	int randomSeed; //34
	short mouseDX; //38
	short mouseDY; //3A
	bool hasBeenPredicted; //3C;
};

class CHLClient{
public:
	ClientClass* GetAllClasses() noexcept;
};

class BaseEntity{
public:
	Vector& GetAbsOrigin() noexcept;

	Vector& GetAbsAngles() noexcept;

	void GetWorldSpaceCenter(Vector& vWorldSpaceCenter) noexcept;

	DWORD* GetModel() noexcept;

	bool SetupBones(matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) noexcept;

	ClientClass* GetClientClass() noexcept;

	bool IsDormant() noexcept;

	int GetIndex() noexcept;

	int GetFlags() noexcept;

	void GetRenderBounds(Vector& minS, Vector& maxS) noexcept;
};

class EngineClient{
public:
	void GetScreenSize(int& width, int& height) noexcept;

	bool GetPlayerInfo(int entNum, PlayerInfo* pInfo) noexcept;

	bool ConIsVisible() noexcept;

	int GetLocalPlayer() noexcept;

	float Time() noexcept;

	void GetViewAngles(Vector& va) noexcept;

	void SetViewAngles(Vector& va) noexcept;

	int GetMaxClients() noexcept;

	bool IsInGame() noexcept;

	bool IsConnected() noexcept;

	bool IsDrawingLoadingImage() noexcept;

	const matrix3x4& WorldToScreenMatrix() noexcept;

	bool IsTakingScreenshot() noexcept;

	DWORD* GetNetChannelInfo() noexcept;

	void ClientCmdUnrestricted(const char* chCommandString) noexcept;
};

class Panel{
public:
	const char* GetName(unsigned int vGuiPanel) noexcept;
};

class Surface{
public:
	void DrawSetColor(int r, int g, int b, int a) noexcept;

	void DrawFilledRect(int x0, int y0, int x1, int y1) noexcept;

	void DrawOutlinedRect(int x0, int y0, int x1, int y1) noexcept;

	void DrawSetTextFont(unsigned long font) noexcept;

	void DrawSetTextColor(int r, int g, int b, int a) noexcept;

	void DrawSetTextPos(int x, int y) noexcept;

	void DrawPrintText(const wchar_t* text, int textLen) noexcept;

	unsigned long CreateFont() noexcept;

	void SetFontGlyphSet(unsigned long& font, const char* windowsFontName, int tall,
						 int weight, int blur, int scanlines, int flags) noexcept;

	void GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall) noexcept;
};

class EntList{
public:
	BaseEntity* GetClientEntity(int entNum) noexcept;

	BaseEntity* GetClientEntityFromHandle(int hEnt) noexcept;

	int GetHighestEntityIndex(void) noexcept;
};

class ClientModeShared{
public:
	bool IsChatPanelOutOfFocus() noexcept;
};

class Interfaces{
public:
	EntList* EntList;
	EngineClient* Engine;
	Panel* Panels;
	Surface* Surface;
	ClientModeShared* ClientMode;
	CHLClient* Client;
};

extern Interfaces gInts;
extern PlayerVariables gPlayerVars;
extern Offsets gOffsets;