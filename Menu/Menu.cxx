//
// Created by Apple on 08/09/2019.
//

#include "Menu.hxx"

Menu gMenu;

void Menu::Draw() const noexcept{
	int h = (this->items.size() + 1) * this->menuItemHeight;

	gDraw.DrawRect(this->x, this->y, this->w, h, COLORCODE(0, 0, 0, 150));
	gDraw.OutlineRect(this->x, this->y, this->w, h, COLORCODE(15, 150, 150, 255));

	gDraw.DrawString(this->x + this->w / 2 - 50 / 2, this->y, gDraw.dwGetTeamColor(3), "Darkstorm");

	for(const auto& item : this->items){
		if(item.isSwitch){
			gDraw.DrawString(this->x + 5, this->y + this->menuItemHeight * item.index, gDraw.dwGetTeamColor(3), "%s %s",
							 *item.value ? "-" : "+", item.name.c_str());
		}else if(item.items.empty()){
			gDraw.DrawString(this->x + 5, this->y + this->menuItemHeight * item.index, gDraw.dwGetTeamColor(3), "- %s",
							 item.name.c_str());
			gDraw.DrawString(this->x + this->w - 35, this->y + this->menuItemHeight * item.index,
							 gDraw.dwGetTeamColor(3), *item.value ? "ON" : "OFF");
		}else{
			gDraw.DrawString(this->x + 5, this->y + this->menuItemHeight * item.index, gDraw.dwGetTeamColor(3), "- %s",
							 item.name.c_str());
			gDraw.DrawString(this->x + this->w - 35, this->y + this->menuItemHeight * item.index,
							 gDraw.dwGetTeamColor(3), item.items[*item.value].c_str());
		}
	}
}

void Menu::AddItem(const std::string& name, int& index, int* value, std::initializer_list<std::string> t_items,
				   bool isSwitch) noexcept{
	this->items.emplace_back(name, index, value, t_items, isSwitch);
	++index;
}

void Menu::CreateItems() noexcept{
	this->items.clear();
	int menuItems = 1;

	this->AddItem("Aimbot", menuItems, &menuVars["AimbotSwitch"], {}, true);
	this->AddItem("Visuals", menuItems, &menuVars["VisualsSwitch"], {}, true);
	this->AddItem("Misc", menuItems, &menuVars["MiscSwitch"], {}, true);
}

