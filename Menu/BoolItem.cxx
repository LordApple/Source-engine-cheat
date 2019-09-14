//
// Created by Apple on 14/09/2019.
//

#include "BoolItem.hxx"

BoolItem::BoolItem(std::string t_name, int* t_value) noexcept : name(std::move(t_name)), value(t_value){}

void BoolItem::RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
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

void BoolItem::SetName(const std::string& t_name) noexcept{
	this->name = t_name;
}

void BoolItem::SetValue(const int& t_value) noexcept{
	*this->value = t_value;
}

std::string BoolItem::GetName() const noexcept{
	return this->name;
}

int BoolItem::GetValue() const noexcept{
	return *this->value;
}

bool BoolItem::IsSwitch() const noexcept{
	return false;
}
