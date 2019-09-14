//
// Created by Apple on 14/09/2019.
//

#ifndef FISTFUL_OF_FRAGS_SWITCHITEM_HXX
#define FISTFUL_OF_FRAGS_SWITCHITEM_HXX

#include "../SDK/SDK.hxx"
#include "../SDK/CDrawManager/DrawManager.hxx"

#include "MenuRewrite.hxx"

#include "BoolItem.hxx"

class SwitchItem : public BoolItem{
public:
	SwitchItem(std::string t_name, int* t_value, std::initializer_list<std::shared_ptr<BoolItem>> t_items) noexcept;

	~SwitchItem() noexcept;

	void RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
					int& index, int& curHeight) const noexcept override;

	[[nodiscard]] bool IsSwitch() const noexcept override;

private:
	std::vector<std::shared_ptr<BoolItem>> items;
};

#endif //FISTFUL_OF_FRAGS_SWITCHITEM_HXX
