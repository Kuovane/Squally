#include "HexusOpponentRadon.h"

const std::string HexusOpponentRadon::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RADON";
HexusOpponentRadon* HexusOpponentRadon::instance = nullptr;

HexusOpponentRadon* HexusOpponentRadon::getInstance()
{
	if (HexusOpponentRadon::instance == nullptr)
	{
		HexusOpponentRadon::instance = new HexusOpponentRadon();
	}

	return HexusOpponentRadon::instance;
}

HexusOpponentRadon::HexusOpponentRadon() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Mech_Npcs_Radon_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentRadon::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.97f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentRadon::~HexusOpponentRadon()
{
}