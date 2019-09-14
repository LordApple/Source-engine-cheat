//
// Created by Apple on 08/09/2019.
//

#ifndef FISTFUL_OF_FRAGS_MENUREWRITE_HXX
#define FISTFUL_OF_FRAGS_MENUREWRITE_HXX

#include "../SDK/SDK.hxx"
#include "../SDK/CDrawManager/DrawManager.hxx"

#include "BoolItem.hxx"
#include "SwitchItem.hxx"

class Menu{
public:
	void Draw();

	void PopulateMenu();

	void AddItem(const std::shared_ptr<BoolItem>& t_item);

// Setters
public:
	void SetActiveState(const bool& t_state) noexcept;

	void SetCurrentIndex(const int& t_currentIndex) noexcept;

	void SetCurrentItemValue(int t_value) noexcept;

// Getters
public:
	[[nodiscard]] bool GetActiveState() const noexcept;

	[[nodiscard]] int GetCurrentIndex() const noexcept;

	[[nodiscard]] int GetTotalItems() const noexcept;

	[[nodiscard]] int GetCurrentItemValue() const noexcept;

private:
	bool isActive;

	int menuItemHeight = 15;
	int currentIndex = 1;
	int totalItems;

private:

	int x = 300;
	int y = 50;
	int w = 200;

	std::vector<std::shared_ptr<BoolItem>> menuItems{};
};

extern Menu gMenu;

#endif //FISTFUL_OF_FRAGS_MENUREWRITE_HXX
