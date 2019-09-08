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

class Offsets{
public:
	int iCreateMoveOffset = 21, iPaintTraverseOffset = 41;
};