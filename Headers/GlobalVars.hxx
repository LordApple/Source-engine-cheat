#include <unordered_map>

#include "../SDK/SDK.hxx"

class PlayerVariables{
public:
	int iWeaponID;
	bool bHasMeleeWeapon;
	bool bHasFlameThrower;
	int iClass;
	int iWeaponSlot;
	int iPlayerCond;
	int iPlayerCondEx;
	int iFlags;
	char chName[34];
};

struct Offsets{
	int iKeyEventOffset = 20;
	int iCreateMoveOffset = 21;
	int iPaintTraverseOffset = 41;
};