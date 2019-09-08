#pragma once

#include "../../SDK/SDK.hxx"

bool __fastcall Hooked_CreateMove(PVOID ClientMode, int edx, float input_sample_frametime, UserCmd* pCommand);