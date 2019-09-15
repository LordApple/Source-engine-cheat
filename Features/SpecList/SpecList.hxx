//
// Created by Apple on 15/09/2019.
//

#ifndef FISTFUL_OF_FRAGS_SPECLIST_HXX
#define FISTFUL_OF_FRAGS_SPECLIST_HXX

#include <utility>

#include "../../SDK/SDK.hxx"
#include "../../SDK/CDrawManager/DrawManager.hxx"

class SpecList{
public:
	void Render() noexcept;

	void ClearPlayers() noexcept;

	void AddPlayer(const std::string& name, const OBSMODES& mode) noexcept;

private:
	const static int itemHeight = 15;
	const static int itemWidth = 250;

	std::vector<std::pair<std::string, OBSMODES>> players;
};

extern SpecList gSpec;

#endif //FISTFUL_OF_FRAGS_SPECLIST_HXX
