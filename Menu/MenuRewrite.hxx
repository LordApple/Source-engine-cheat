//
// Created by Apple on 08/09/2019.
//

#ifndef FISTFUL_OF_FRAGS_MENUREWRITE_HXX
#define FISTFUL_OF_FRAGS_MENUREWRITE_HXX

#include "../SDK/SDK.hxx"
#include "../SDK/CDrawManager/DrawManager.hxx"

class BaseItem{
public:
	BaseItem(std::string t_name, int* t_value);

	virtual void RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
							int& index, int& curHeight) const noexcept;

	virtual bool IsSwitch() const noexcept;

// Setters
public:
	void SetName(const std::string& t_name) noexcept;

	void SetValue(const int& t_value) noexcept;

// Getters
public:
	[[nodiscard]] std::string GetName() const noexcept;

	[[nodiscard]] int GetValue() const noexcept;

private:
	std::string name;
	int* value;
};

class SwitchItem : public BaseItem{
public:
	SwitchItem(std::string t_name, int* t_value, std::initializer_list<BaseItem*> t_items);

	void RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
					int& index, int& curHeight) const noexcept override;

	[[nodiscard]] bool IsSwitch() const noexcept override;

private:
	std::vector<BaseItem*> items;
};

class Menu{
public:
	void Draw();

	void PopulateMenu();

	void AddItem(BaseItem* t_item);

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

	std::vector<BaseItem*> menuItems{};
};

extern Menu gMenu;

#endif //FISTFUL_OF_FRAGS_MENUREWRITE_HXX
