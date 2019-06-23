#include "RewardsMenu.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Inventory/Currency/Gold.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Combat/ItemFound.h"
#include "Strings/Combat/Rewards.h"
#include "Strings/Combat/Victory.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

RewardsMenu* RewardsMenu::create()
{
	RewardsMenu* instance = new RewardsMenu();

	instance->autorelease();

	return instance;
}

RewardsMenu::RewardsMenu()
{
	this->victoryMenu = Sprite::create(UIResources::Combat_VictoryMenu);
	this->expSprite = Sprite::create(UIResources::Menus_Icons_Stars);
	this->goldSprite = Sprite::create(UIResources::Menus_Icons_Coins);
	this->expValue = ConstantString::create(std::to_string(0));
	this->goldValue = ConstantString::create(std::to_string(0));
	this->expLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, this->expValue);
	this->goldLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, this->goldValue);

	this->victoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2, Strings::Combat_Victory::create());

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);

	this->returnButton = ClickableTextNode::create(returnLabel, returnLabelHover, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->expLabel->enableOutline(Color4B::BLACK, 2);
	this->goldLabel->enableOutline(Color4B::BLACK, 2);
	this->victoryLabel->enableOutline(Color4B::BLACK, 2);

	this->expLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->goldLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->victoryMenu);
	this->addChild(this->expSprite);
	this->addChild(this->goldSprite);
	this->addChild(this->expLabel);
	this->addChild(this->goldLabel);
	this->addChild(this->victoryLabel);
	this->addChild(this->returnButton);
}

RewardsMenu::~RewardsMenu()
{
}

void RewardsMenu::onEnter()
{
	super::onEnter();

	this->setOpacity(0);
}

void RewardsMenu::initializePositions()
{
	super::initializePositions();

	this->victoryLabel->setPosition(Vec2(0.0f, 176.0f));
	this->victoryMenu->setPosition(Vec2(0.0f, 0.0f));
	this->expSprite->setPosition(Vec2(-48.0f, 32.0f));
	this->expLabel->setPosition(Vec2(16.0f, 32.0f));
	this->goldSprite->setPosition(Vec2(-48.0f, -48.0f));
	this->goldLabel->setPosition(Vec2(16.0f, -48.0f));
	this->returnButton->setPosition(Vec2(16.0f, -160.0f));
}

void RewardsMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGiveRewards, [=](EventCustom* args)
	{
		this->loadRewards();
	}));

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		CombatEvents::TriggerReturnToMap();
	});
}

void RewardsMenu::show()
{
	this->runAction(FadeTo::create(1.0f, 255));
}

void RewardsMenu::loadRewards()
{
	const int DISPLAY_LIMIT = 32;
	int index = 0;
	int totalGoldGain = 0;
	int totalExpGain = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* entity)
	{
		totalGoldGain += entity->getCurrencyInventory()->getCurrencyCount(Gold::getIdentifier());
		totalExpGain += StatsTables::calculateEnemyExp(entity->getMaxHealth(), entity->getMaxMana());

		std::vector<Item*> items = entity->getInventory()->getItems();

		const float onsetDuration = 0.5f;
		const float interleaveDuration = 0.75f;
		const float fadeInDuration = 0.35f;
		const float sustainDuration = 2.0f;
		const float fadeOutDuration = 0.5f;
		const float roundDelay = 0.35f;

		for (auto it = items.begin(); it != items.end(); it++, index++)
		{
			if (index >= DISPLAY_LIMIT)
			{
				return;
			}

			int slot = index % 3;
			int round = index / 3;

			Node* container = Node::create();
			Sprite* itemFrame = Sprite::create(UIResources::Combat_ItemFrame);
			ClickableNode* itemIcon = ClickableNode::create((*it)->getIconResource(), (*it)->getIconResource());
			LocalizedLabel* title = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Combat_ItemFound::create());
			LocalizedLabel* itemName = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, (*it)->getString());

			title->enableOutline(Color4B::BLACK, 2);
			itemName->enableOutline(Color4B::BLACK, 2);

			container->setPosition(Vec2(visibleSize.width / 2.0f - 256.0f, -visibleSize.height / 2.0f + 256.0f + 256.0f * float(slot)));
			itemIcon->setPosition(Vec2(-96.0f, 0.0f));
			itemName->setPosition(Vec2(32.0f, 0.0f));
			title->setPosition(Vec2(0.0f, 96.0f));

			container->addChild(itemFrame);
			container->addChild(itemIcon);
			container->addChild(itemName);
			container->addChild(title);
			this->addChild(container);

			container->setOpacity(0);

			container->runAction(Sequence::create(
				DelayTime::create(onsetDuration + float(index) * interleaveDuration + float(round) * roundDelay),
				FadeTo::create(fadeInDuration, 255),
				DelayTime::create(sustainDuration),
				FadeTo::create(fadeOutDuration, 0),
				nullptr
			));
		}
	}));

	this->goldValue->setString(std::to_string(totalGoldGain));
	this->expValue->setString(std::to_string(totalExpGain));
}
