//
// Created by Apple on 14/09/2019.
//

#include "SwitchItem.hxx"

SwitchItem::SwitchItem(std::string t_name, int* t_value,
					   std::initializer_list<std::shared_ptr<BoolItem>> t_items) noexcept : BoolItem(std::move(t_name),
																									 t_value),
																							items(t_items){}

SwitchItem::~SwitchItem() noexcept{
	this->items.clear();
}

void SwitchItem::RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
							int& index, int& curHeight) const noexcept{


	if(index == gMenu.GetCurrentIndex() && gMenu.GetActiveState()){
		gDraw.DrawRect(menuX, menuY + itemHeight * index, menuW, itemHeight,
					   COLORCODE(255, 255, 255, 150));
	}

	curHeight += itemHeight;
	gDraw.DrawString(menuX + 5, menuY + itemHeight * index, gDraw.dwGetTeamColor(3), "%s %s",
					 this->GetValue() ? "-" : "+", this->GetName().c_str());

	if(this->GetValue()){
		for(const auto& item : this->items){
			++index;
			item->RenderItem(menuX, menuY, menuW, itemHeight, index, curHeight);
		}
	}
}

bool SwitchItem::IsSwitch() const noexcept{
	return true;
}