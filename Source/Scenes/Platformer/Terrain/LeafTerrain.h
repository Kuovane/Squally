#pragma once

#include "Engine/Terrain/TerrainObject.h"

class LeafTerrain : public TerrainObject
{
public:
	static LeafTerrain* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTerrainType;

protected:
	LeafTerrain(cocos2d::ValueMap& properties);
	virtual ~LeafTerrain();

private:
	typedef TerrainObject super;
};
