#include "DivBlock.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Cipher/Config.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Operations/DIV.h"

using namespace cocos2d;

DivBlock* DivBlock::create(bool isToolBoxItem)
{
	DivBlock* instance = new DivBlock(isToolBoxItem);

	instance->autorelease();

	return instance;
}

DivBlock::DivBlock(bool isToolBoxItem) : super(isToolBoxItem, ClickableNode::create(CipherResources::BlockHex, CipherResources::BlockHex), CipherResources::Icons_Division, Strings::Cipher_Operations_DIV::create())
{
}

DivBlock::~DivBlock()
{
}

void DivBlock::onEnter()
{
	super::onEnter();
}

void DivBlock::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

BlockBase* DivBlock::spawn()
{
	return DivBlock::create();
}