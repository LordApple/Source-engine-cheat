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
							const int& index) const noexcept;

// Setters
public:
	void SetName(const std::string& t_name) noexcept;

	void SetValue(int* t_value) noexcept;

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
	SwitchItem(std::string t_name, int* t_value);

	void RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
					const int& index) const noexcept override;

private:
};

class Menu{
public:
	void Draw();

	void PopulateMenu();

	void AddItem(BaseItem* t_item);

private:
	int menuItemHeight = 15;

	int x = 300;
	int y = 50;
	int w = 200;

	std::vector<BaseItem*> menuItems{};
};

extern Menu gMenu;

#endif //FISTFUL_OF_FRAGS_MENUREWRITE_HXX
