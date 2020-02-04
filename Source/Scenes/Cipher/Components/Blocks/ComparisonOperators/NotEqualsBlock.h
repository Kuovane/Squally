#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class NotEqualsBlock : public ComparisonBlockBase
{
public:
	static NotEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	NotEqualsBlock(BlockType blockType);
	virtual ~NotEqualsBlock();
	unsigned char compute() override;
	bool compare(unsigned char inputA, unsigned char inputB) override;

private:
	typedef ComparisonBlockBase super;
};
