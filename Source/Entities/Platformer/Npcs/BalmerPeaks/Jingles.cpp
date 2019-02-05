////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Jingles.h"

#include "Resources/EntityResources.h"

const std::string Jingles::MapKeyJingles = "jingles";

Jingles* Jingles::deserialize(cocos2d::ValueMap* initProperties)
{
	Jingles* instance = new Jingles(initProperties);

	instance->autorelease();

	return instance;
}

Jingles::Jingles(cocos2d::ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_BalmerPeaks_Jingles_Animations,
	EntityResources::Npcs_BalmerPeaks_Jingles_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	cocos2d::Size(112.0f, 160.0f),
	0.9f,
	cocos2d::Vec2(0.0f, 0.0f),
	10,
	10)
{
}

Jingles::~Jingles()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////