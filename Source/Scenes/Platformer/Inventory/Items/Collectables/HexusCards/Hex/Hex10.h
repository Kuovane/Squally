#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Hex10 : public HexusCard
{
public:
	static Hex10* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	Hex10();
	~Hex10();

private:
	typedef HexusCard super;
};
