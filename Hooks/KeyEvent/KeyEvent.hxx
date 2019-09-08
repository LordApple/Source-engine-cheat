//
// Created by Apple on 08/09/2019.
//

#ifndef FISTFUL_OF_FRAGS_KEYEVENT_HXX
#define FISTFUL_OF_FRAGS_KEYEVENT_HXX

#include "../../SDK/SDK.hxx"

int __fastcall Hooked_KeyEvent(PVOID ClientMode, int edx, InputEventType eventCode, ButtonCode keyNum,
							   const char* pszCurrentBinding);


#endif //FISTFUL_OF_FRAGS_KEYEVENT_HXX
