//
// Created by Apple on 15/09/2019.
//

#include "SpecList.hxx"

SpecList gSpec;

void SpecList::Render() noexcept{
	int index = 1;

	gDraw.DrawRect(gScreenSize.iScreenWidth - 350, gScreenSize.iScreenHeight / 2,
				   SpecList::itemWidth,
				   SpecList::itemHeight * (this->players.size() == 0 ? 1 : this->players.size() + 1),
				   COLORCODE(47, 47, 47, 255));

	for(const auto&[name, mode] : this->players){
		std::string modeString;

		switch(mode){
			case OBSMODES::OBS_MODE_DEATHCAM:
				modeString = "Deathcam";
				break;
			case OBSMODES::OBS_MODE_FREEZECAM:
				modeString = "Freezecam";
				break;
			case OBSMODES::OBS_MODE_IN_EYE:
				modeString = "Firstperson";
				break;
			case OBSMODES::OBS_MODE_CHASE:
				modeString = "Thirdperson";
				break;
		}

		gDraw.DrawString(gScreenSize.iScreenWidth - 350 + 15,
						 gScreenSize.iScreenHeight / 2 + SpecList::itemHeight * index,
						 COLORCODE(255, 255, 255, 255),
						 name.c_str());

		gDraw.DrawString(gScreenSize.iScreenWidth - 350 + SpecList::itemWidth / 2 + 15,
						 gScreenSize.iScreenHeight / 2 + SpecList::itemHeight * index,
						 COLORCODE(255, 255, 255, 255),
						 modeString.c_str());

		++index;
	}

	gDraw.OutlineRect(gScreenSize.iScreenWidth - 350, gScreenSize.iScreenHeight / 2, SpecList::itemWidth,
					  SpecList::itemHeight,
					  COLORCODE(0, 0, 0, 255));

	gDraw.OutlineRect(gScreenSize.iScreenWidth - 350, gScreenSize.iScreenHeight / 2, SpecList::itemWidth,
					  SpecList::itemHeight * index,
					  COLORCODE(0, 0, 0, 255));

	gDraw.DrawLine(gScreenSize.iScreenWidth - 350 + SpecList::itemWidth / 2,
				   gScreenSize.iScreenHeight / 2,
				   gScreenSize.iScreenWidth - 350 + SpecList::itemWidth / 2,
				   gScreenSize.iScreenHeight / 2 + SpecList::itemHeight * index,
				   COLORCODE(0, 0, 0, 255));

	gDraw.DrawString(gScreenSize.iScreenWidth - 350 + 15, gScreenSize.iScreenHeight / 2, COLORCODE(255, 255, 255, 255),
					 "Spectator");

	gDraw.DrawString(gScreenSize.iScreenWidth - 350 + SpecList::itemWidth / 2 + 15,
					 gScreenSize.iScreenHeight / 2,
					 COLORCODE(255, 255, 255, 255),
					 "OBS Mode");
}

void SpecList::ClearPlayers() noexcept{
	this->players.clear();
}

void SpecList::AddPlayer(const std::string& name, const OBSMODES& mode) noexcept{
	this->players.emplace_back(name, mode);
}
