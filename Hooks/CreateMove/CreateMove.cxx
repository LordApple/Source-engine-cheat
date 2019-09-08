#include "../../SDK/SDK.hxx"
#include "CreateMove.hxx"

bool __fastcall Hooked_CreateMove(PVOID ClientMode, int edx, float input_sample_frametime, UserCmd* pCommand){
	VMTManager& hook = VMTManager::GetHook(ClientMode);
	bool bReturn = hook.GetMethod < bool(__thiscall*)(PVOID, float, UserCmd *) >
													 (gOffsets.iCreateMoveOffset)(ClientMode, input_sample_frametime,
																				  pCommand);

	BaseEntity* pLocal = GetBaseEntity(me);

	if(!pLocal){
		return bReturn;
	}

	return bReturn;
}