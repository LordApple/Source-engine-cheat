#include "../../SDK/SDK.hxx"
#include "Panels.hxx"
#include "../../SDK/CDrawManager/DrawManager.hxx"

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

		BaseEntity* pLocal = gInts.EntList->GetClientEntity(me);

		if(!pLocal)
			return;

		Vector vecWorld, vecScreen;

		pLocal->GetWorldSpaceCenter(vecWorld);

		if(gDraw.WorldToScreen(vecWorld, vecScreen)){
			gDraw.DrawString(vecScreen.x, vecScreen.y, 0xFFFFFFFF, "You");
		}
	}
}

void Intro(){
	gDraw.Initialize();
	gNetVars.Initialize();
}