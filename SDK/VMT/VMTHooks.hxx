#pragma once

#include <cassert>

namespace toolkit{

	unsigned int CountFuncs(void** pVMT);

	int FindFunc(void** pVMT, void* pFunc, unsigned int vfuncs = 0);

	class VMTBaseManager{
	public:
		enum{
			GUARD = 0xFAC0D775
		};

		VMTBaseManager& Init(void* inst, unsigned int offset = 0, unsigned int vfuncs = 0);

		void Kill();

		bool IsInitialized() const;

		VMTBaseManager& HookMethod(void* newfunc, unsigned int index);

		VMTBaseManager& UnhookMethod(unsigned int index);

		void EraseHooks();

		VMTBaseManager& Unhook();

		VMTBaseManager& Rehook();

		bool Hooked() const;

		template<typename Fn>
		const Fn& GetMethod(unsigned int index) const;

		void* UserData() const;

		void UserData(void* data);

		static bool HookPresent(void* inst, unsigned int offset = 0);

		static VMTBaseManager& GetHook(void* inst, unsigned int offset = 0);

	protected:
		static void**& _getvtbl(void* inst, unsigned int offset);

	protected:
		void*** _vftable;
		void** _oldvmt;
		void** _array;
		void* _userdata;
	};

	class VMTManager : public VMTBaseManager{
		VMTManager(const VMTManager&);

		VMTManager& operator=(const VMTManager&);

	public:
		VMTManager(void* inst, unsigned int offset = 0, unsigned int vfuncs = 0);

		~VMTManager();

		void Poof();

		static VMTManager& GetHook(void* inst, unsigned int offset = 0);
	};

	inline bool VMTBaseManager::IsInitialized() const{
		return _vftable != nullptr;
	}

	inline VMTBaseManager& VMTBaseManager::HookMethod(void* newfunc, unsigned int index){
		assert(index < CountFuncs(_array + 3) && IsInitialized());
		_array[index + 3] = newfunc;
		return *this;
	}

	inline VMTBaseManager& VMTBaseManager::UnhookMethod(unsigned int index){
		assert(index < CountFuncs(_array + 3) && IsInitialized());
		_array[index + 3] = _oldvmt[index];
		return *this;
	}

	inline VMTBaseManager& VMTBaseManager::Unhook(){
		*_vftable = _oldvmt;
		return *this;
	}

	inline VMTBaseManager& VMTBaseManager::Rehook(){
		*_vftable = _array + 3;
		return *this;
	}

	inline bool VMTBaseManager::Hooked() const{
		return *_vftable != _oldvmt;
	}

	template<typename Fn>
	inline const Fn& VMTBaseManager::GetMethod(unsigned int index) const{
		assert(index < CountFuncs(_array + 3));
		return *(const Fn*) &_oldvmt[index];
	}

	inline void* VMTBaseManager::UserData() const{
		return _userdata;
	}

	inline void VMTBaseManager::UserData(void* data){
		_userdata = data;
	}

	inline bool VMTBaseManager::HookPresent(void* inst, unsigned int offset){
		void** vmt = _getvtbl(inst, offset);
		return vmt[-2] == (void*) GUARD;
	}

	inline VMTBaseManager& VMTBaseManager::GetHook(void* inst, unsigned int offset){
		void** vmt = _getvtbl(inst, offset);
		return *reinterpret_cast<VMTBaseManager*>(vmt[-3]);
	}

	inline void**& VMTBaseManager::_getvtbl(void* inst, unsigned int offset){
		return *reinterpret_cast<void***>((char*) inst + offset);
	}

	inline VMTManager::VMTManager(void* inst, unsigned int offset, unsigned int vfuncs){
		Init(inst, offset, vfuncs).Rehook();
	}

	inline VMTManager::~VMTManager(){
		Kill();
	}

	inline void VMTManager::Poof(){
		_vftable = nullptr;
	}

	inline VMTManager& VMTManager::GetHook(void* inst, unsigned int offset){
		return static_cast<VMTManager&>(VMTBaseManager::GetHook(inst, offset));
	}


	class VMTBasePointer{
	public:
		enum{
			GUARD = 0xDE4DB3EF
		};

		VMTBasePointer& Init_thiscall(void* inst, unsigned int vfuncs = 0);

		VMTBasePointer& Init_stdcall(void* inst, unsigned int vfuncs = 0);

		void Kill();

		VMTBasePointer& HookMethod(void* newfunc, unsigned int index);

		VMTBasePointer& UnhookMethod(unsigned int index);

		VMTBasePointer& Rehook(void* var);

		VMTBasePointer& Unhook(void* var);

		template<typename Fn>
		const Fn& GetMethod(unsigned int index) const;

		void* UserData() const;

		void UserData(void* data);

		void* Instance() const;

		void* Dummy() const;

		static bool HookPresent(void* inst);

		static VMTBasePointer& GetHook(void* inst);

	protected:
		typedef void(__fastcall* CallGateFn)();

		VMTBasePointer& Init(void* inst, CallGateFn gate, unsigned int vfuncs = 0);

		static void* __fastcall FindCallOffset(VMTBasePointer* _this, unsigned char* addr);

		static void __fastcall CallGate_thiscall();

		static void __fastcall CallGate_stdcall();

		static void** _getvtbl(void* inst, unsigned int offset = 0);

	protected:
		struct dummy_t{
			void** vtable;
		} _dummy;
		void* _inst;
		CallGateFn _gate;
		void* _userdata;
	};

	class VMTPointer : public VMTBasePointer{
		VMTPointer(const VMTPointer&);

		VMTPointer& operator=(const VMTPointer&);

	public:
		VMTPointer(void** var, bool thiscall = true, unsigned int vfuncs = 0);

		~VMTPointer();

		VMTPointer& Unhook();

		VMTPointer& Rehook();

		bool Hooked() const;

		static VMTPointer& GetHook(void* inst);

	private:
		void** _var;
	};

	inline VMTBasePointer& VMTBasePointer::Init_thiscall(void* inst, unsigned int vfuncs){
		return Init(inst, &CallGate_thiscall, vfuncs);
	}

	inline VMTBasePointer& VMTBasePointer::Init_stdcall(void* inst, unsigned int vfuncs){
		return Init(inst, &CallGate_stdcall, vfuncs);
	}

	inline VMTBasePointer& VMTBasePointer::HookMethod(void* newfunc, unsigned int index){
		assert(index < CountFuncs(_dummy.vtable) && newfunc);
		_dummy.vtable[index] = newfunc;
		return *this;
	}

	inline VMTBasePointer& VMTBasePointer::UnhookMethod(unsigned int index){
		assert(index < CountFuncs(_dummy.vtable));
		_dummy.vtable[index] = _gate;
		return *this;
	}

	inline VMTBasePointer& VMTBasePointer::Rehook(void* var){
		void*& x = *(void**) var;
		assert(!x || x == _inst || x == &_dummy);
		x = &_dummy;
		return *this;
	}

	inline VMTBasePointer& VMTBasePointer::Unhook(void* var){
		void*& x = *(void**) var;
		assert(!x || x == _inst || x == &_dummy);
		x = _inst;
		return *this;
	}

	template<typename Fn>
	inline const Fn& VMTBasePointer::GetMethod(unsigned int index) const{
		assert(index < CountFuncs(_dummy.vtable));
		return *(const Fn*) (&_getvtbl(_inst)[index]);
	}

	inline void* VMTBasePointer::UserData() const{
		return _userdata;
	}

	inline void VMTBasePointer::UserData(void* data){
		_userdata = data;
	}

	inline void* VMTBasePointer::Instance() const{
		return _inst;
	}

	inline void* VMTBasePointer::Dummy() const{
		return const_cast<dummy_t*>(&_dummy);
	}

	inline bool VMTBasePointer::HookPresent(void* inst){
		void** vmt = *(void***) inst;
		return vmt[-2] == (void*) GUARD;
	}

	inline VMTBasePointer& VMTBasePointer::GetHook(void* inst){
		void** vmt = *(void***) inst;
		return *reinterpret_cast<VMTBasePointer*>(vmt[-3]);
	}

	inline void** VMTBasePointer::_getvtbl(void* inst, unsigned int offset){
		return *reinterpret_cast<void***>((char*) inst + offset);
	}

	inline VMTPointer::VMTPointer(void** var, bool thiscall, unsigned int vfuncs) : _var(var){
		if(thiscall)
			Init_thiscall(*var, vfuncs);
		else
			Init_stdcall(*var, vfuncs);
	}

	inline VMTPointer::~VMTPointer(){
		*_var = _inst;
		Kill();
	}

	inline VMTPointer& VMTPointer::Unhook(){
		*_var = _inst;
		return *this;
	}

	inline VMTPointer& VMTPointer::Rehook(){
		*_var = &_dummy;
		return *this;
	}

	inline bool VMTPointer::Hooked() const{
		return *_var == &_dummy;
	}

	inline VMTPointer& VMTPointer::GetHook(void* inst){
		return static_cast<VMTPointer&>(VMTBasePointer::GetHook(inst));
	}

	class VMTBaseHook{
	public:
		VMTBaseHook& Init(void* inst, unsigned int offset = 0, unsigned int vfuncs = 0);

		VMTBaseHook& Init(void** vmt, unsigned int vfuncs = 0);

		void Kill();

		VMTBaseHook& HookMethod(void* new_func, unsigned int index);

		VMTBaseHook& UnhookMethod(unsigned int index);

		void EraseHooks();

		template<typename Fn>
		const Fn& GetMethod(unsigned int index) const;

	protected:
		static bool WriteHook(void* dest, const void* src, unsigned int bytes);

	private:
		void** _vftable;
		void** _backup;
		unsigned int _vcount;
	};

	class VMTHook : public VMTBaseHook{
		VMTHook(const VMTHook&);

		VMTHook& operator=(const VMTHook&);

	public:
		VMTHook(void* inst, unsigned int offset = 0, unsigned int vfuncs = 0);

		VMTHook(void** vmt, unsigned int vfuncs = 0);

		~VMTHook();
	};

	inline VMTBaseHook& VMTBaseHook::Init(void* inst, unsigned int offset, unsigned int vfuncs){
		return Init(*reinterpret_cast<void***>((char*) inst + offset), vfuncs);
	}

	template<typename Fn>
	inline const Fn& VMTBaseHook::GetMethod(unsigned int index) const{
		return *(Fn*) &_backup[index];
	}

	inline VMTBaseHook& VMTBaseHook::HookMethod(void* func, unsigned int index){
		WriteHook(&_vftable[index], &func, sizeof(void*));
		return *this;
	}

	inline VMTBaseHook& VMTBaseHook::UnhookMethod(unsigned int index){
		WriteHook(&_vftable[index], &_backup[index], sizeof(void*));
		return *this;
	}

	inline void VMTBaseHook::EraseHooks(){
		WriteHook(_vftable, _backup, _vcount * sizeof(void*));
	}

	inline VMTHook::VMTHook(void* inst, unsigned int offset, unsigned int vfuncs){
		Init(inst, offset, vfuncs);
	}

	inline VMTHook::VMTHook(void** vmt, unsigned int vfuncs){
		Init(vmt, vfuncs);
	}

	inline VMTHook::~VMTHook(){
		Kill();
	}


}