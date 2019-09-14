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


		for(int x = 0; x < gInts.Engine->GetMaxClients(); ++x){
			if(x == me){
				continue;
			}

			BaseEntity* pEntity = GetBaseEntity(x);

			if(!pEntity || pEntity->IsDormant() ||
			   pEntity->GetLifeState() != static_cast<BYTE>(SourceLifeStates::LIFE_ALIVE)){
				continue;
			}

			Vector vecWorld, vecScreen;

			pEntity->GetWorldSpaceCenter(vecWorld);

			if(gDraw.WorldToScreen(vecWorld, vecScreen)){
				gDraw.DrawString(vecScreen.x, vecScreen.y, 0xFFFFFFFF, "Player");
			}
		}
	}
}

void Intro(){
	gDraw.Initialize();
	gNetVars.Initialize();
}