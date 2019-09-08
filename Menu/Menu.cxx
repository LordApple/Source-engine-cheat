//
// Created by Apple on 08/09/2019.
//

#include "Menu.hxx"

//Menu gMenu;

void Menu::CreateItems() noexcept{
	this->items.clear();
	int menuItems = 1;

	this->AddItem("Aimbot", menuItems, &menuVars["AimbotSwitch"], {}, 0, 1, true);
	this->AddItem("Visuals", menuItems, &menuVars["VisualsSwitch"], {}, 0, 1, true);
	this->AddItem("Misc", menuItems, &menuVars["MiscSwitch"], {}, 0, 1, true);
	if(menuVars["MiscSwitch"]){
		this->AddItem("TestKey", menuItems, &menuVars["MiscTestKey"],
					  {"Shift", "Mouse1", "Mouse2", "Mouse3", "Mouse4", "Mouse5"});
	}
}

void Menu::Draw() const noexcept{
	int h = (this->items.size() + 1) * this->menuItemHeight;

	gDraw.DrawRect(this->x, this->y, this->w, h, COLORCODE(0, 0, 0, 150));
	gDraw.OutlineRect(this->x, this->y, this->w, h, COLORCODE(15, 150, 150, 255));

	gDraw.DrawString(this->x + this->w / 2 - 50 / 2, this->y, gDraw.dwGetTeamColor(3), "Darkstorm");

	for(const auto& item : this->items){
		if(item.index == this->currentIndex && this->active){
			gDraw.DrawRect(this->x, this->y + this->menuItemHeight * item.index, this->w, this->menuItemHeight,
						   COLORCODE(255, 255, 255, 150));
		}

		if(item.isSwitch){

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

void Menu::AddItem(const std::string& name, int& index, int* value,
				   std::initializer_list<std::string> t_items, int t_min, int t_max, bool isSwitch) noexcept{
	this->items.emplace_back(name, index, value, t_items, t_min, t_max, isSwitch);
	++index;
}

bool Menu::GetActiveState() const noexcept{
	return this->active;
}

size_t Menu::GetItemsSize() const noexcept{
	return this->items.size();
}

int Menu::GetCurrentIndex() const noexcept{
	return this->currentIndex;
}

int Menu::GetCurrentItemMax() const noexcept{
	return this->items[this->currentIndex - 1].maxVal;
}

int Menu::GetCurrentItemMin() const noexcept{
	return this->items[this->currentIndex - 1].minVal;
}

int Menu::GetCurrentItemValue() const noexcept{
	return *this->items[this->currentIndex - 1].value;
}


void Menu::SetCurrentItemValue(int value) noexcept{
	*this->items[this->currentIndex - 1].value = value;
}

void Menu::SetCurrentIndex(const int& index) noexcept{
	this->currentIndex = index;
}

void Menu::SetActiveState(bool state) noexcept{
	this->active = state;
}