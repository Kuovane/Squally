#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class SpeedRune : public Consumable
{
public:
	static SpeedRune* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeySpeedRune;

protected:
	SpeedRune();
	virtual ~SpeedRune();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
};
