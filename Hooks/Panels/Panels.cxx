#include "../../SDK/SDK.hxx"
#include "Panels.hxx"
#include "../../SDK/CDrawManager/DrawManager.hxx"
#include "../../Menu/MenuRewrite.hxx"

ScreenSize gScreenSize;

void
__fastcall Hooked_PaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce){
	VMTManager& hook = VMTManager::GetHook(pPanels);
	hook.GetMethod < void(__thiscall*)(PVOID, unsigned int, bool, bool) >
									  (gOffsets.iPaintTraverseOffset)(pPanels, vguiPanel, forceRepaint,
																	  allowForce);

	static unsigned int vguiMatSystemTopPanel;

	if(!vguiMatSystemTopPanel){
		const char* szName = gInts.Panels->GetName(vguiPanel);
		if(szName[0] == 'M' && szName[3] == 'S'){
			vguiMatSystemTopPanel = vguiPanel;
			Intro();
		}
	}

	if(vguiMatSystemTopPanel == vguiPanel){
		if(gInts.Engine->IsDrawingLoadingImage() || !gInts.Engine->IsInGame() || !gInts.Engine->IsConnected() ||
		   gInts.Engine->ConIsVisible() || ((GetAsyncKeyState(VK_F12) || gInts.Engine->IsTakingScreenshot()))){
			return;
		}

		gDraw.DrawString((gScreenSize.iScreenWidth / 2) - 55, 200, gDraw.dwGetTeamColor(3),
						 "Welcome to Darkstorm");

		gMenu.PopulateMenu();
		gMenu.Draw();

		BaseEntity* pLocal = gInts.EntList->GetClientEntity(me);

		if(!pLocal){
			return;
		}


		gSpec.ClearPlayers();

		for(int x = 1; x < gInts.Engine->GetMaxClients(); ++x){
			if(x == me){
				continue;
			}

			BaseEntity* pEntity = GetBaseEntity(x);

			if(!pEntity || pEntity->IsDormant()){
				continue;
			}

			int obsMode = pEntity->GetObserverMode();
			int obsTarget = pEntity->GetObserverTarget();

			BaseEntity* pTarget = gInts.EntList->GetClientEntityFromHandle(obsTarget);

			if(pTarget && ((obsMode == static_cast<int>(OBSMODES::OBS_MODE_DEATHCAM) ||
							obsMode == static_cast<int>(OBSMODES::OBS_MODE_IN_EYE) ||
							obsMode == static_cast<int>(OBSMODES::OBS_MODE_FREEZECAM) ||
							obsMode == static_cast<int>(OBSMODES::OBS_MODE_CHASE)) && pTarget == pLocal)){
				PlayerInfo pInfo{};
				gInts.Engine->GetPlayerInfo(pEntity->GetIndex(), &pInfo);
				auto mode = static_cast<OBSMODES>(obsMode);
				gSpec.AddPlayer(pInfo.name, mode);
			}

			if(pEntity->GetLifeState() != static_cast<BYTE>(SourceLifeStates::LIFE_ALIVE)){
				continue;
			}

			Vector vecWorld, vecScreen;

			pEntity->GetWorldSpaceCenter(vecWorld);

			if(gDraw.WorldToScreen(vecWorld, vecScreen)){
				gDraw.DrawLine(vecScreen.x, vecScreen.y, gScreenSize.iScreenWidth / 2,
							   gScreenSize.iScreenHeight / 2, COLORCODE(0, 0, 0, 255));
				gDraw.DrawString(vecScreen.x, vecScreen.y, 0xFFFFFFFF, "Player");
			}
		}

		gSpec.Render();
	}
}

void Intro(){
	gDraw.Initialize();
	gNetVars.Initialize();
}