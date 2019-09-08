#include "../../SDK/SDK.h"
#include "Panels.h"
#include "../../SDK/CDrawManager/CDrawManager.h"

CScreenSize gScreenSize;

//===================================================================================
void
__fastcall Hooked_PaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce){
	VMTManager& hook = VMTManager::GetHook(
			pPanels); //Get a pointer to the instance of your VMTManager with the function GetHook.
	hook.GetMethod < void(__thiscall*)(PVOID, unsigned int, bool, bool) >
									  (gOffsets.iPaintTraverseOffset)(pPanels, vguiPanel, forceRepaint,
																	  allowForce); //Call the original.

	static unsigned int vguiMatSystemTopPanel;

	if(vguiMatSystemTopPanel == NULL){
		const char* szName = gInts.Panels->GetName(vguiPanel);
		if(szName[0] == 'M' &&
		   szName[3] == 'S') //Look for MatSystemTopPanel without using slow operations like strcmp or strstr.
		{
			vguiMatSystemTopPanel = vguiPanel;
			Intro();
		}
	}

	if(vguiMatSystemTopPanel == vguiPanel) //If we're on MatSystemTopPanel, call our drawing code.
	{
		if(gInts.Engine->IsDrawingLoadingImage() || !gInts.Engine->IsInGame() || !gInts.Engine->IsConnected() ||
		   gInts.Engine->ConIsVisible() || ((GetAsyncKeyState(VK_F12) || gInts.Engine->IsTakingScreenshot()))){
			return; //We don't want to draw at the menu.
		}

		//This section will be called when the player is not at the menu game and can see the screen or not taking a screenshot.
		gDrawManager.DrawString((gScreenSize.iScreenWidth / 2) - 55, 200, gDrawManager.dwGetTeamColor(3),
								"Welcome to Darkstorm"); //Remove this if you want.

		//Test ESP code.

		BaseEntity* pBaseLocalEnt = gInts.EntList->GetClientEntity(me);  //Grab the local player's entity.

		if(pBaseLocalEnt == NULL) //Always check for null pointers.
			return;

		Vector vecWorld, vecScreen; //Setup the Vectors.

		pBaseLocalEnt->GetWorldSpaceCenter(vecWorld); //Get the center of the player.

		if(gDrawManager.WorldToScreen(vecWorld, vecScreen)) //If the player is visble.
		{
			gDrawManager.DrawString(vecScreen.x, vecScreen.y, 0xFFFFFFFF, "You"); //Draw on the player.
		}
	}
}

//===================================================================================
void Intro(void){
	gDrawManager.Initialize(); //Initalize the drawing class.
}