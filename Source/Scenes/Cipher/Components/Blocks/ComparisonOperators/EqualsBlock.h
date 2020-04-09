#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class EqualsBlock : public ComparisonBlockBase
{
public:
	static EqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	EqualsBlock(BlockType blockType);
	virtual ~EqualsBlock();
	unsigned char compute() override;
	bool compare(unsigned char inputA, unsigned char inputB) override;

private:
	typedef ComparisonBlockBase super;
};
