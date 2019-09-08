
#include <cstdlib>
#include "VMTHooks.hxx"
#include "memory.h"

namespace toolkit{

	unsigned int CountFuncs(void** vmt){
		unsigned int i = -1;
		do ++i;while(vmt[i]);
		return i;
	}

	int FindFunc(void** vmt, void* func, unsigned int vfuncs){
		if(!vfuncs) vfuncs = CountFuncs(vmt);
		for(unsigned int i = 0; i < vfuncs; i++){
			if(vmt[i] == func) return i;
		}
		return -1;
	}

	VMTBaseManager& VMTBaseManager::Init(void* inst, unsigned int offset, unsigned int vfuncs){
		_vftable = &_getvtbl(inst, offset);
		_oldvmt = *_vftable;
		if(!vfuncs){
			vfuncs = CountFuncs(_oldvmt);
			assert(vfuncs >= 1);
		}
		void** arr = _array = (void**) ::malloc((vfuncs + 4) * sizeof(void*));
		arr[0] = this;
		arr[1] = (void*) GUARD;
		(arr + 3)[vfuncs] = nullptr;
		{
			unsigned int i = -1;
			do arr[i + 3] = _oldvmt[i];
			while(++i < vfuncs);
		}
		return *this;
	}

	void VMTBaseManager::Kill(){
		if(IsInitialized()){
			Unhook();
			_vftable = nullptr;
		}
		::free(_array);
		_array = nullptr;
	}

	void VMTBaseManager::EraseHooks(){
		unsigned int i = 0;
		void** vmt = _array + 3;
		do vmt[i] = _oldvmt[i];
		while(vmt[++i]);
	}


	VMTBasePointer& VMTBasePointer::Init(void* inst, CallGateFn gate, unsigned int vfuncs){
		_inst = inst;
		_gate = gate;
		void** vmt = *(void***) inst;
		if(!vfuncs){
			vfuncs = CountFuncs(vmt);
			assert(vfuncs >= 1);
		}
		void** arr = (void**) ::malloc((vfuncs + 4) * sizeof(void*));
		_dummy.vtable = arr + 3;
		arr[0] = this;
		arr[1] = (void*) GUARD;
		arr[2] = vmt[-1];
		(arr + 3)[vfuncs] = nullptr;
		for(unsigned int i = 0; i < vfuncs; ++i)
			(arr + 3)[i] = gate;
		return *this;
	}

	void VMTBasePointer::Kill(){
		if(_dummy.vtable){
			::free(_dummy.vtable - 3);
		}
	}

	void* __fastcall VMTBasePointer::FindCallOffset(VMTBasePointer* _this, unsigned char* addr){
		unsigned int vfn;

#if defined(_M_IX86)
		if(addr[-2] == 0xFF && (addr[-1] & 0xC0) == 0xC0){
			unsigned char rm = (addr[-1] & 0x07) << 3;

			typedef unsigned char* iterator;
			for(iterator it = addr - 4, end = it - 64; it != end; --it){
				if(it[0] == 0x8B){
					unsigned char modrm = (it[1] & 0xF8);
					if(modrm == (0x00 | rm)){
						vfn = 0;
						break;
					}else if(modrm == (0x40 | rm)){
						vfn = it[2];
						break;
					}else if(modrm == (0x80 | rm)){
						vfn = *(unsigned int*) (it + 2);
						break;
					}
				}
			}
		}else if(addr[-2] == 0xFF && (addr[-1] & 0xC0) == 0x00){
			vfn = 0;
		}else if(addr[-3] == 0xFF && (addr[-2] & 0xC0) == 0x40){
			vfn = addr[-1];
		}else if(addr[-6] == 0xFF && (addr[-5] & 0xC0) == 0x80){
			vfn = *(unsigned int*) (addr - 4);
		}else{
			__debugbreak();
			vfn = -1;
		}
#else
		return nullptr;
#endif

		char* vmt = (char*) (*(void**) _this->_inst);
		return *(void**) (vmt + vfn);
	}

#if defined(_M_IX86)

	__declspec(naked) void __fastcall VMTBasePointer::CallGate_thiscall(){
		__asm
		{
		mov eax,[ecx + 4]
		push eax
		mov edx,[esp + 4]
		call FindCallOffset
		pop ecx
		jmp eax
		}
	}

	__declspec(naked) void __fastcall VMTBasePointer::CallGate_stdcall(){
		__asm
		{
		mov ecx,[esp + 4]
		mov eax,[ecx + 4]
		mov[esp + 4], eax
		mov edx,[esp]
		call FindCallOffset
		jmp eax
		}
	}

#else
#error Implement me for this architecture!
#endif

	VMTBaseHook& VMTBaseHook::Init(void** vmt, unsigned int vfuncs){
		_vftable = vmt;
		if(!vfuncs){
			vfuncs = CountFuncs(vmt);
			assert(vfuncs >= 1);
		}
		_vcount = vfuncs;
		_backup = (void**) ::malloc(vfuncs * sizeof(void*));
		for(unsigned int i = 0; i < vfuncs; ++i)
			_backup[i] = _vftable[i];
		return *this;
	}

	void VMTBaseHook::Kill(){
		if(_backup){
			EraseHooks();
			::free(_backup);
			_backup = nullptr;
		}
	}

	bool VMTBaseHook::WriteHook(void* dest, const void* src, unsigned int bytes){
		return memcpy(dest, src, bytes);
	}
}