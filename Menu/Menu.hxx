//
// Created by Apple on 08/09/2019.
//

#ifndef FISTFUL_OF_FRAGS_MENU_HXX
#define FISTFUL_OF_FRAGS_MENU_HXX

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include "../SDK/CDrawManager/DrawManager.hxx"

class menuItem{
public:
	menuItem(std::string t_name, int& t_index, int* t_value, std::initializer_list<std::string> t_items,
			 bool t_isSwitch)
			: name(std::move(t_name)),
			  index(t_index), value(t_value),
			  isSwitch(t_isSwitch),
			  items(t_items){}

	const std::string name;

	bool isSwitch;
	int index;
	int* value;

	std::vector<std::string> items{};
};

class Menu{
public:
	void AddItem(const std::string& name, int& index, int* value, std::initializer_list<std::string> t_items = {},
				 bool isSwitch = false) noexcept;

	void CreateItems() noexcept;

	void Draw() const noexcept;

private:
	int currentIndex;
	int menuItemHeight = 15;

	int x = 300;
	int y = 50;
	int w = 200;

	std::vector<menuItem> items{};

private:
	std::unordered_map<std::string, int> menuVars{
			{"AimbotSwitch",  0},

			{"VisualsSwitch", 0},

			{"MiscSwitch",    1},
	};

};

extern Menu gMenu;

#endif //FISTFUL_OF_FRAGS_MENU_HXX
