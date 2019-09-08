//
// Created by Apple on 08/09/2019.
//

#include "NetVar.hxx"

#include "../../SDK/SDK.hxx"

NetVar gNetVars;

#undef GetProp

void NetVar::Initialize(){
	const auto* client_class = gInts.Client->GetAllClasses();
	while(client_class != nullptr){
		const auto class_info = std::make_shared<node>(0);
		auto* recv_table = client_class->Table;
		populate_nodes(recv_table, &class_info->nodes);
		nodes.emplace(recv_table->GetName(), class_info);

		client_class = client_class->pNextClass;
	}
}

void NetVar::populate_nodes(RecvTable* recv_table, map_type* map){
	for(auto i = 0; i < recv_table->GetNumProps(); i++){
		const auto* prop = recv_table->GetPropA(i);
		const auto prop_info = std::make_shared<node>(prop->GetOffset());

		if(prop->GetType() == DPT_DataTable)
			populate_nodes(prop->GetDataTable(), &prop_info->nodes);

		map->emplace(prop->GetName(), prop_info);
	}
}