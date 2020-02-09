#include "TempleDarkTerrain.h"

#include "cocos/base/CCValue.h"

#include "Resources/TerrainResources.h"
#include "Resources/TextureResources.h"

using namespace cocos2d;

const std::string TempleDarkTerrain::MapKeyTerrainType = "temple-dark";

TempleDarkTerrain* TempleDarkTerrain::create(ValueMap& properties)
{
	TempleDarkTerrain* instance = new TempleDarkTerrain(properties);

	instance->autorelease();

	return instance;
}

TempleDarkTerrain::TempleDarkTerrain(ValueMap& properties) : super(
	properties,
	TerrainObject::TerrainData(
		0.5f,
		TempleDarkTerrain::MapKeyTerrainType,
		TextureResources::TempleDarkTexture,
		TerrainResources::Temple_Top,
		TerrainResources::Temple_TopLeft,
		TerrainResources::Temple_TopRight,
		TerrainResources::Temple_TopConnector,
		TerrainResources::Temple_TopConnectorConcave,
		TerrainResources::Temple_TopConnectorConcaveDeep,
		TerrainResources::Temple_TopConnectorConvex,
		TerrainResources::Temple_TopConnectorConvexDeep,
		TerrainResources::Temple_Bottom,
		TerrainResources::Temple_BottomLeft,
		TerrainResources::Temple_BottomRight,
		TerrainResources::Temple_BottomConnector,
		TerrainResources::Temple_Left,
		TerrainResources::Temple_LeftConnector,
		TerrainResources::Temple_Right,
		TerrainResources::Temple_RightConnector,
		// Top
		Vec2::ZERO,
		// Bottom
		Vec2::ZERO,
		// Left
		Vec2::ZERO,
		// Right
		Vec2::ZERO,
		// TopLeft
		Vec2::ZERO,
		// TopRight
		Vec2::ZERO,
		// BottomLeft
		Vec2::ZERO,
		// BottomRight
		Vec2::ZERO,
		// TopConnector
		Vec2::ZERO,
		// TopConnectorConcave
		Vec2(0.0f, 4.0f),
		// TopConnectorConcaveDeep
		Vec2(0.0f, 6.0f),
		// TopConnectorConvex
		Vec2(0.0f, -6.0f),
		// TopConnectorConvexDeep
		Vec2(0.0f, -8.0f),
		// BottomConnector
		Vec2::ZERO,
		// FillColor
		Color4B(11, 30, 39, 255)))
{
}

TempleDarkTerrain::~TempleDarkTerrain()
{
}
