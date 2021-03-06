#pragma once

#include "Engine/Deserializers/Objects/ObjectDeserializer.h"

class IsometricDecorDeserializer : public ObjectDeserializer
{
public:
	static IsometricDecorDeserializer* create();

	static const std::string MapKeyTypeDecor;

private:
	typedef ObjectDeserializer super;
	
	IsometricDecorDeserializer();
	~IsometricDecorDeserializer();

	void deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args) override;
};
