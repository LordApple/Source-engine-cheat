//
// Created by Apple on 08/09/2019.
//

#include "MenuRewrite.hxx"

Menu gMenu;

int testValue = 0;
int testValue2 = 1;
int testValue3 = 0;
int testValue4 = 1;

BaseItem::BaseItem(std::string t_name, int* t_value) : name(std::move(t_name)), value(t_value){}

void BaseItem::RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
						  int& index, int& curHeight) const noexcept{

	// This could be it's own function
	if(index == gMenu.GetCurrentIndex() && gMenu.GetActiveState()){
		gDraw.DrawRect(menuX, menuY + itemHeight * index, menuW, itemHeight,
					   COLORCODE(255, 255, 255, 150));
	}

	curHeight += itemHeight;
	gDraw.DrawString(menuX + 5, menuY + itemHeight * index, gDraw.dwGetTeamColor(3), "- %s", this->GetName().c_str());
	gDraw.DrawString(menuX + menuW - 35, menuY + itemHeight * index, gDraw.dwGetTeamColor(3),
					 this->GetValue() ? "ON" : "OFF");
}

void BaseItem::SetName(const std::string& t_name) noexcept{
	this->name = t_name;
}

void BaseItem::SetValue(const int& t_value) noexcept{
	*this->value = t_value;
}

std::string BaseItem::GetName() const noexcept{
	return this->name;
}

int BaseItem::GetValue() const noexcept{
	return *this->value;
}

bool BaseItem::IsSwitch() const noexcept{
	return false;
}

SwitchItem::SwitchItem(std::string t_name, int* t_value, std::initializer_list<BaseItem*> t_items) : BaseItem(
		std::move(t_name), t_value), items(t_items){}

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
			new BaseItem("Enabled", &testValue),
	}));
	this->AddItem(new SwitchItem("Visuals", &testValue, {
			new BaseItem("Enabled", &testValue),
	}));
	this->AddItem(new SwitchItem("Misc", &testValue2, {
			new BaseItem("Enabled", &testValue3),
			new SwitchItem("Options", &testValue4, {
					new BaseItem("Ignore Shit", &testValue3),
			}),
	}));
}

void Menu::AddItem(BaseItem* t_item){
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
