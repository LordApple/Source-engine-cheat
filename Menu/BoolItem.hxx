//
// Created by Apple on 14/09/2019.
//

#include "../SDK/SDK.hxx"
#include "../SDK/CDrawManager/DrawManager.hxx"

#include "MenuRewrite.hxx"

#ifndef FISTFUL_OF_FRAGS_BOOLITEM_HXX
#define FISTFUL_OF_FRAGS_BOOLITEM_HXX

class BoolItem{
public:
	BoolItem(std::string t_name, int* t_value) noexcept;
	
	virtual void RenderItem(const int& menuX, const int& menuY, const int& menuW, const int& itemHeight,
							int& index, int& curHeight) const noexcept;

// Setters
public:
	void SetName(const std::string& t_name) noexcept;

	void SetValue(const int& t_value) noexcept;

// Getters
public:
	[[nodiscard]] virtual bool IsSwitch() const noexcept;

	[[nodiscard]] std::string GetName() const noexcept;

	[[nodiscard]] int GetValue() const noexcept;

private:
	std::string name;
	int* value;
};


#endif //FISTFUL_OF_FRAGS_BOOLITEM_HXX
