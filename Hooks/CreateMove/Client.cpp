#include "../../SDK/SDK.h"
#include "Client.h"

//============================================================================================
bool __fastcall Hooked_CreateMove(PVOID ClientMode, int edx, float input_sample_frametime, CUserCmd* pCommand){
	VMTManager& hook = VMTManager::GetHook(ClientMode);
	bool bReturn = hook.GetMethod < bool(__thiscall*)(PVOID, float, CUserCmd *) >
													 (gOffsets.iCreateMoveOffset)(ClientMode, input_sample_frametime,
																				  pCommand);

	CBaseEntity* pBaseEntity = GetBaseEntity(me);

	if(pBaseEntity == NULL)
		return bReturn;

	if(pCommand->buttons & IN_JUMP){
		pCommand->buttons |= IN_ATTACK; //Set the IN_ATTACK flag.
	}

	return bReturn; //If bReturn is true, CInput::CreateMove will call CEngine::SetViewAngles(pCommand->viewangles). If you want silent aim, return false, but make sure to call SetViewAngles manually.
}
//============================================================================================