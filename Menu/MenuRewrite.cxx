//
// Created by Apple on 08/09/2019.
//

#include "MenuRewrite.hxx"

Menu gMenu;

int testValue = 0;
int testValue2 = 1;
int testValue3 = 0;
int testValue4 = 1;

void Menu::Draw(){
	int index = 1;

	int h = this->menuItemHeight;

	for(const auto& item : this->menuItems){
		item->RenderItem(this->x, this->y, this->w, this->menuItemHeight, index, h);
		++index;
	}

	gDraw.DrawRect(this->x, this->y, this->w, h, COLORCODE(0, 0, 0, 150));
	gDraw.OutlineRect(this->x, this->y, this->w, h, COLORCODE(15, 150, 150, 255));
	gDraw.DrawString(this->x + this->w / 2 - 50 / 2, this->y, gDraw.dwGetTeamColor(3), "Darkstorm");

	this->totalItems = index - 1;
}

void Menu::PopulateMenu(){
	if(!this->menuItems.empty()){
		for(auto& item : this->menuItems){
			delete item;
		}
		this->menuItems.clear();
	}

	this->AddItem(new SwitchItem("Aimbot", &testValue, {
			new BoolItem("Enabled", &testValue),
	}));
	this->AddItem(new SwitchItem("Visuals", &testValue, {
			new BoolItem("Enabled", &testValue),
	}));
	this->AddItem(new SwitchItem("Misc", &testValue2, {
			new BoolItem("Enabled", &testValue3),
			new SwitchItem("Options", &testValue4, {
					new BoolItem("Ignore Shit", &testValue3),
			}),
	}));
}

void Menu::AddItem(BoolItem* t_item){
	this->menuItems.push_back(t_item);
}

void Menu::SetActiveState(const bool& t_state) noexcept{
	this->isActive = t_state;
}

void Menu::SetCurrentIndex(const int& t_currentIndex) noexcept{
	this->currentIndex = t_currentIndex;
}

bool Menu::GetActiveState() const noexcept{
	return this->isActive;
}

int Menu::GetCurrentIndex() const noexcept{
	return this->currentIndex;
}

int Menu::GetTotalItems() const noexcept{
	return totalItems;
}

void Menu::SetCurrentItemValue(int t_value) noexcept{
	this->menuItems[this->currentIndex]->SetValue(t_value);
}

int Menu::GetCurrentItemValue() const noexcept{
	return this->menuItems[this->currentIndex]->GetValue();
}
