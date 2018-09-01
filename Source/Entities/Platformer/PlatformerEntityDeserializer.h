#pragma once
#include "cocos2d.h"

#include "Engine/Maps/IObjectDeserializer.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Resources.h"

using namespace cocos2d;

class PlatformerEntityDeserializer : public IObjectDeserializer
{
public:
	PlatformerEntityDeserializer();
	~PlatformerEntityDeserializer();

	void onDeserializationRequest(ObjectDeserializationRequestArgs* args) override;

	static const std::string KeyTypeEntity;


};