//
// Created by Apple on 08/09/2019.
//

#ifndef FISTFUL_OF_FRAGS_NETVAR_HXX
#define FISTFUL_OF_FRAGS_NETVAR_HXX

#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <memory>

#include "../../Headers/dt_recv2.hxx"


class NetVar{
	struct node;
	using map_type = std::unordered_map<std::string, std::shared_ptr<node>>;

	struct node{
		node(DWORD offset) : offset(offset){}

		map_type nodes;
		DWORD offset;
	};

	map_type nodes;

public:
	void Initialize();

private:
	void populate_nodes(class RecvTable* recv_table, map_type* map);

	DWORD get_offset_recursive(map_type& map, int acc, const char* name){
		return acc + map[name]->offset;
	}

	template<typename ...args_t>
	DWORD get_offset_recursive(map_type& map, int acc, const char* name, args_t ...args){
		const auto& node = map[name];
		return get_offset_recursive(node->nodes, acc + node->offset, args...);
	}

public:
	template<typename ...args_t>
	DWORD get_offset(const char* name, args_t ...args){
		const auto& node = nodes[name];
		return get_offset_recursive(node->nodes, node->offset, args...);
	}
};

extern NetVar gNetVars;

template<typename T>
class DynamicNetVar{
	DWORD off;

public:
	template<typename... args_t>
	DynamicNetVar(args_t... a){
		off = gNetVars.get_offset(a...);
	}

	template<typename... args_t>
	DynamicNetVar(int offset, args_t... a){
		off = gNetVars.get_offset(a...) + offset;
	}

	T GetValue(PVOID base){
		return *reinterpret_cast< T* >((DWORD) base + (DWORD) off);
	}

	void SetValue(PVOID base, T val){
		*reinterpret_cast<T* >((DWORD) (base) + ((DWORD) (off))) = val;
	}
};

#define DYNVAR(name, type, ...) static DynamicNetVar<type> ##name( __VA_ARGS__ )
#define DYNVAR_RETURN(type, base, ...) DYNVAR(n, type, __VA_ARGS__); return n.GetValue(base)

#define DYNVAR_OFF(name, type, offset, ...) static DynamicNetVar<type> ##name(offset, __VA_ARGS__)
#define DYNVAR_OFF_RETURN(type, base, offset, ...) DYNVAR_OFF(n, type, offset, __VA_ARGS__); return n.GetValue(base)


#endif //FISTFUL_OF_FRAGS_NETVAR_HXX
