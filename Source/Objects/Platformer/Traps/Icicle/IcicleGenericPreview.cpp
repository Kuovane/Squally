#include "IcicleGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

IcicleGenericPreview* IcicleGenericPreview::create()
{
	IcicleGenericPreview* instance = new IcicleGenericPreview();

	instance->autorelease();

	return instance;
}

IcicleGenericPreview::IcicleGenericPreview()
{
	this->previewAsteroid = Sprite::create(ObjectResources::Physics_Asteroid_Asteroid);

	this->previewAsteroid->setScale(0.35f);

	this->previewNode->addChild(this->previewAsteroid);
}

HackablePreview* IcicleGenericPreview::clone()
{
	return IcicleGenericPreview::create();
}

void IcicleGenericPreview::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	this->previewAsteroid->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
}

void IcicleGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->previewAsteroid->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
