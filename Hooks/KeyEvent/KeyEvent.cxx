////
//// Created by Apple on 08/09/2019.
////
//
//#include "KeyEvent.hxx"
//#include "../../Menu/Menu.hxx"
//
//int __fastcall Hooked_KeyEvent(PVOID CHLClient, int edx, InputEventType eventCode, ButtonCode keyNum,
//							   const char* currentBinding){
//
//	if(eventCode == InputEventType::IE_ButtonPressed){
//		switch(keyNum){
//			case ButtonCode::KEY_INSERT:
//				gMenu.SetActiveState(!gMenu.GetActiveState());
//				break;
//			case ButtonCode::BUTTON_CODE_INVALID:
//				break;
//			case ButtonCode::BUTTON_CODE_NONE:
//				break;
//			case ButtonCode::KEY_0:
//				break;
//			case ButtonCode::KEY_1:
//				break;
//			case ButtonCode::KEY_2:
//				break;
//			case ButtonCode::KEY_3:
//				break;
//			case ButtonCode::KEY_4:
//				break;
//			case ButtonCode::KEY_5:
//				break;
//			case ButtonCode::KEY_6:
//				break;
//			case ButtonCode::KEY_7:
//				break;
//			case ButtonCode::KEY_8:
//				break;
//			case ButtonCode::KEY_9:
//				break;
//			case ButtonCode::KEY_A:
//				break;
//			case ButtonCode::KEY_B:
//				break;
//			case ButtonCode::KEY_C:
//				break;
//			case ButtonCode::KEY_D:
//				break;
//			case ButtonCode::KEY_E:
//				break;
//			case ButtonCode::KEY_F:
//				break;
//			case ButtonCode::KEY_G:
//				break;
//			case ButtonCode::KEY_H:
//				break;
//			case ButtonCode::KEY_I:
//				break;
//			case ButtonCode::KEY_J:
//				break;
//			case ButtonCode::KEY_K:
//				break;
//			case ButtonCode::KEY_L:
//				break;
//			case ButtonCode::KEY_M:
//				break;
//			case ButtonCode::KEY_N:
//				break;
//			case ButtonCode::KEY_O:
//				break;
//			case ButtonCode::KEY_P:
//				break;
//			case ButtonCode::KEY_Q:
//				break;
//			case ButtonCode::KEY_R:
//				break;
//			case ButtonCode::KEY_S:
//				break;
//			case ButtonCode::KEY_T:
//				break;
//			case ButtonCode::KEY_U:
//				break;
//			case ButtonCode::KEY_V:
//				break;
//			case ButtonCode::KEY_W:
//				break;
//			case ButtonCode::KEY_X:
//				break;
//			case ButtonCode::KEY_Y:
//				break;
//			case ButtonCode::KEY_Z:
//				break;
//			case ButtonCode::KEY_PAD_0:
//				break;
//			case ButtonCode::KEY_PAD_1:
//				break;
//			case ButtonCode::KEY_PAD_2:
//				break;
//			case ButtonCode::KEY_PAD_3:
//				break;
//			case ButtonCode::KEY_PAD_4:
//				break;
//			case ButtonCode::KEY_PAD_5:
//				break;
//			case ButtonCode::KEY_PAD_6:
//				break;
//			case ButtonCode::KEY_PAD_7:
//				break;
//			case ButtonCode::KEY_PAD_8:
//				break;
//			case ButtonCode::KEY_PAD_9:
//				break;
//			case ButtonCode::KEY_PAD_DIVIDE:
//				break;
//			case ButtonCode::KEY_PAD_MULTIPLY:
//				break;
//			case ButtonCode::KEY_PAD_MINUS:
//				break;
//			case ButtonCode::KEY_PAD_PLUS:
//				break;
//			case ButtonCode::KEY_PAD_ENTER:
//				break;
//			case ButtonCode::KEY_PAD_DECIMAL:
//				break;
//			case ButtonCode::KEY_LBRACKET:
//				break;
//			case ButtonCode::KEY_RBRACKET:
//				break;
//			case ButtonCode::KEY_SEMICOLON:
//				break;
//			case ButtonCode::KEY_APOSTROPHE:
//				break;
//			case ButtonCode::KEY_BACKQUOTE:
//				break;
//			case ButtonCode::KEY_COMMA:
//				break;
//			case ButtonCode::KEY_PERIOD:
//				break;
//			case ButtonCode::KEY_SLASH:
//				break;
//			case ButtonCode::KEY_BACKSLASH:
//				break;
//			case ButtonCode::KEY_MINUS:
//				break;
//			case ButtonCode::KEY_EQUAL:
//				break;
//			case ButtonCode::KEY_ENTER:
//				break;
//			case ButtonCode::KEY_SPACE:
//				break;
//			case ButtonCode::KEY_BACKSPACE:
//				break;
//			case ButtonCode::KEY_TAB:
//				break;
//			case ButtonCode::KEY_CAPSLOCK:
//				break;
//			case ButtonCode::KEY_NUMLOCK:
//				break;
//			case ButtonCode::KEY_ESCAPE:
//				break;
//			case ButtonCode::KEY_SCROLLLOCK:
//				break;
//			case ButtonCode::KEY_DELETE:
//				break;
//			case ButtonCode::KEY_HOME:
//				break;
//			case ButtonCode::KEY_END:
//				break;
//			case ButtonCode::KEY_PAGEUP:
//				break;
//			case ButtonCode::KEY_PAGEDOWN:
//				break;
//			case ButtonCode::KEY_BREAK:
//				break;
//			case ButtonCode::KEY_LSHIFT:
//				break;
//			case ButtonCode::KEY_RSHIFT:
//				break;
//			case ButtonCode::KEY_LALT:
//				break;
//			case ButtonCode::KEY_RALT:
//				break;
//			case ButtonCode::KEY_LCONTROL:
//				break;
//			case ButtonCode::KEY_RCONTROL:
//				break;
//			case ButtonCode::KEY_LWIN:
//				break;
//			case ButtonCode::KEY_RWIN:
//				break;
//			case ButtonCode::KEY_APP:
//				break;
//			case ButtonCode::KEY_UP:
//				if(gMenu.GetCurrentIndex() - 1 < 1){
//					gMenu.SetCurrentIndex(gMenu.GetItemsSize());
//				}else{
//					gMenu.SetCurrentIndex(gMenu.GetCurrentIndex() - 1);
//				}
//				break;
//			case ButtonCode::KEY_DOWN:
//				if(gMenu.GetCurrentIndex() + 1 > gMenu.GetItemsSize()){
//					gMenu.SetCurrentIndex(1);
//				}else{
//					gMenu.SetCurrentIndex(gMenu.GetCurrentIndex() + 1);
//				}
//				break;
//			case ButtonCode::KEY_RIGHT:
//				if(gMenu.GetCurrentItemValue() + 1 > gMenu.GetCurrentItemMax()){
//					gMenu.SetCurrentItemValue(0);
//				}else{
//					gMenu.SetCurrentItemValue(gMenu.GetCurrentItemValue() + 1);
//				}
//				break;
//			case ButtonCode::KEY_LEFT:
//				if(gMenu.GetCurrentItemValue() - 1 < gMenu.GetCurrentItemMin()){
//					gMenu.SetCurrentItemValue(gMenu.GetCurrentItemMax());
//				}else{
//					gMenu.SetCurrentItemValue(gMenu.GetCurrentItemValue() - 1);
//				}
//				break;
//			case ButtonCode::KEY_F1:
//				break;
//			case ButtonCode::KEY_F2:
//				break;
//			case ButtonCode::KEY_F3:
//				break;
//			case ButtonCode::KEY_F4:
//				break;
//			case ButtonCode::KEY_F5:
//				break;
//			case ButtonCode::KEY_F6:
//				break;
//			case ButtonCode::KEY_F7:
//				break;
//			case ButtonCode::KEY_F8:
//				break;
//			case ButtonCode::KEY_F9:
//				break;
//			case ButtonCode::KEY_F10:
//				break;
//			case ButtonCode::KEY_F11:
//				break;
//			case ButtonCode::KEY_F12:
//				break;
//		}
//	}
//
//
//	VMTManager& hook = VMTManager::GetHook(CHLClient);
//	return hook.GetMethod < int(__thiscall *)(PVOID, InputEventType, ButtonCode,
//	const char *)>(gOffsets.iKeyEventOffset)(CHLClient, eventCode, keyNum, currentBinding);
//}