//
// Created by Apple on 08/09/2019.
//

#include "MenuRewrite.hxx"

Menu gMenu;

int testValue = 0;

BaseItem::BaseItem(std::string t_name, int* t_value) : name(std::move(t_name)), value(t_value){}

void BaseItem::RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
						  const int& index) const noexcept{
	gDraw.DrawString(menuX + 5, menuY + itemHeight * index, gDraw.dwGetTeamColor(3), "- %s", this->GetName().c_str());
	gDraw.DrawString(menuX + menuW - 35, menuY + itemHeight * index, gDraw.dwGetTeamColor(3),
					 this->GetValue() ? "ON" : "OFF");
}

void BaseItem::SetName(const std::string& t_name) noexcept{
	this->name = t_name;
}

void BaseItem::SetValue(int* t_value) noexcept{
	this->value = t_value;
}

std::string BaseItem::GetName() const noexcept{
	return this->name;
}

int BaseItem::GetValue() const noexcept{
	return *this->value;
}

SwitchItem::SwitchItem(std::string t_name, int* t_value) : BaseItem(std::move(t_name), t_value){}

void SwitchItem::RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
							const int& index) const noexcept{
	gDraw.DrawString(menuX + 5, menuY + itemHeight * index, gDraw.dwGetTeamColor(3), "%s %s",
					 this->GetValue() ? "-" : "+", this->GetName().c_str());
}

void Menu::Draw(){
	int index = 1;

	int h = (this->menuItems.size() + 1) * this->menuItemHeight;

	gDraw.DrawRect(this->x, this->y, this->w, h, COLORCODE(0, 0, 0, 150));
	gDraw.OutlineRect(this->x, this->y, this->w, h, COLORCODE(15, 150, 150, 255));
	gDraw.DrawString(this->x + this->w / 2 - 50 / 2, this->y, gDraw.dwGetTeamColor(3), "Darkstorm");


	for(const auto& item : this->menuItems){
		item->RenderItem(this->x, this->y, this->w, this->menuItemHeight, index);
		++index;
	}
}

void Menu::PopulateMenu(){
	if(!this->menuItems.empty()){
		for(auto& item : this->menuItems){
			delete item;
		}
		this->menuItems.clear();
	}

	this->AddItem(new SwitchItem("Aimbot", &testValue));
	this->AddItem(new SwitchItem("Visuals", &testValue));
	this->AddItem(new SwitchItem("Misc", &testValue));
}

void Menu::AddItem(BaseItem* t_item){
	this->menuItems.push_back(t_item);
}
