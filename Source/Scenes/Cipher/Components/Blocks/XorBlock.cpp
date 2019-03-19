#include "XorBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/XOR.h"

using namespace cocos2d;

XorBlock* XorBlock::create(bool isToolBoxItem)
{
	XorBlock* instance = new XorBlock(isToolBoxItem);

	instance->autorelease();

	return instance;
}

XorBlock::XorBlock(bool isToolBoxItem) : super(isToolBoxItem, ClickableNode::create(CipherResources::BlockBin, CipherResources::BlockBin), CipherResources::Icons_LogicalXor, Strings::Cipher_Operations_XOR::create())
{
}

XorBlock::~XorBlock()
{
}

void XorBlock::onEnter()
{
	super::onEnter();
}

void XorBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* XorBlock::spawn()
{
	return XorBlock::create();
}