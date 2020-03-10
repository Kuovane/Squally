#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemAttacking : public HelpTotem
{
public:
	static HelpTotemAttacking* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHelpTotemAttacking;

protected:
	HelpTotemAttacking(cocos2d::ValueMap& properties);
	virtual ~HelpTotemAttacking();

private:
	typedef HelpTotem super;
};
