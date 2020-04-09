#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class HexusOpponentData;
class LocalizedString;

class Ajax : public PlatformerFriendly
{
public:
	static Ajax* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKey;

protected:

private:
	typedef PlatformerFriendly super;
	Ajax(cocos2d::ValueMap& properties);
	virtual ~Ajax();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
