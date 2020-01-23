#include "CardsMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Inventory/FilterMenu/HexusFilter.h"
#include "Menus/Inventory/ItemMenu/ItemEntry.h"
#include "Menus/Inventory/ItemMenu/ItemMenu.h"
#include "Scenes/Title/TitleScreen.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const int CardsMenu::MinHexusCards = 20;
const int CardsMenu::MaxHexusCards = 60;

CardsMenu* CardsMenu::create()
{
	CardsMenu* instance = new CardsMenu();

	instance->autorelease();

	return instance;
}

CardsMenu::CardsMenu()
{
	this->equipmentInventory = EquipmentInventory::create(SaveKeys::SaveKeySquallyEquipment);
	this->inventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);
	this->cardsWindow = Sprite::create(UIResources::Menus_InventoryMenu_InventoryMenu);
	this->equippedCardsMenu = ItemMenu::create();
	this->unequippedCardsMenu = ItemMenu::create();
	this->cardsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Cards_Cards::create());
	this->hexusFilter = HexusFilter::create();
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->returnClickCallback = nullptr;
	this->equipmentChanged = false;

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->setTextColor(Color4B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->cardsLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->cardsLabel->enableGlow(Color4B::BLACK);
	this->hexusFilter->setVisible(false);

	this->unequippedCardsMenu->setTextOffset(ItemMenu::DefaultTextOffset + Vec3(50.0f, 0.0f, 0.0f));
	
	this->addChild(this->equipmentInventory);
	this->addChild(this->inventory);
	this->addChild(this->cardsWindow);
	this->addChild(this->equippedCardsMenu);
	this->addChild(this->unequippedCardsMenu);
	this->addChild(this->hexusFilter);
	this->addChild(this->cardsLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

CardsMenu::~CardsMenu()
{
}

void CardsMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->cardsWindow, delay, duration);
	GameUtils::fadeInObject(this->cardsLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
}

void CardsMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->unequippedCardsMenu->setPosition(Vec2(visibleSize.width / 2.0f - 340.0f, visibleSize.height / 2.0f - 44.0f));
	this->equippedCardsMenu->setPosition(Vec2(visibleSize.width / 2.0f - 1.0f, visibleSize.height / 2.0f - 44.0f));
	this->unequippedCardsMenu->setPreviewOffset(ItemMenu::DefaultPreviewOffset + (this->equippedCardsMenu->getPosition() - this->unequippedCardsMenu->getPosition()));
	this->cardsWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->cardsLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void CardsMenu::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->close();
	});
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();
		this->close();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->equippedCardsMenu->focus();
		this->unequippedCardsMenu->unfocus();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW }, [=](InputEvents::InputArgs* args)
	{
		this->equippedCardsMenu->unfocus();
		this->unequippedCardsMenu->focus();
	});
}

void CardsMenu::populateItemList()
{
	this->equippedCardsMenu->clearVisibleItems();
	this->unequippedCardsMenu->clearVisibleItems();
	std::vector<Item*> equipment = this->hexusFilter->filter(this->equipmentInventory->getItems());
	std::vector<Item*> items = this->hexusFilter->filter(this->inventory->getItems());
	
	for (auto it = equipment.begin(); it != equipment.end(); it++)
	{
		Item* item = *it;

		ItemEntry* entry = this->equippedCardsMenu->pushVisibleItem(item, [=]()
		{
			if (dynamic_cast<HexusCard*>(item) != nullptr)
			{
				this->unequipHexusCard(dynamic_cast<HexusCard*>(item));
			}
		});

		entry->showIcon();
	}
	
	for (auto it = items.begin(); it != items.end(); it++)
	{
		Item* item = *it;

		ItemEntry* entry = this->unequippedCardsMenu->pushVisibleItem(item, [=]()
		{
			if (dynamic_cast<HexusCard*>(item) != nullptr)
			{
				this->equipHexusCard(dynamic_cast<HexusCard*>(item));
			}
		});

		entry->hideIcon();
	}

	this->equippedCardsMenu->updateAndPositionItemText();
	this->unequippedCardsMenu->updateAndPositionItemText();
}

void CardsMenu::open()
{
	this->equipmentChanged = false;
	this->populateItemList();
	this->equippedCardsMenu->clearPreview();
	this->unequippedCardsMenu->clearPreview();
	
	this->equippedCardsMenu->focus();
	this->unequippedCardsMenu->unfocus();
}

void CardsMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}

void CardsMenu::equipHexusCard(HexusCard* card)
{
	if (this->equipmentInventory->getHexusCards().size() >= CardsMenu::MaxHexusCards)
	{
		return;
	}

	this->inventory->tryTransact(this->equipmentInventory, card, nullptr, [=](Item* item, Item* otherItem)
	{
		this->equipmentInventory->moveItem(item, this->equipmentInventory->getItems().size());

		this->populateItemList();
	},
	[=](Item* item, Item* otherItem)
	{
		// Failure
		LogUtils::logError("Error equipping card!");

		if (item != nullptr)
		{
			LogUtils::logError(item->getName());
		}

		if (otherItem != nullptr)
		{
			LogUtils::logError(otherItem->getName());
		}
	});
}

void CardsMenu::unequipHexusCard(HexusCard* card)
{
	if (this->equipmentInventory->getHexusCards().size() <= CardsMenu::MinHexusCards)
	{
		return;
	}

	this->equipmentInventory->tryTransact(this->inventory, card, nullptr, [=](Item* item, Item* otherItem)
	{
		// Success unequipping item -- visually best if this ends up in the 1st inventory slot
		this->inventory->moveItem(item, 0);

		this->populateItemList();
	},
	[=](Item* item, Item* otherItem)
	{
		// Failure
		LogUtils::logError("Error unequipping card!");

		if (otherItem != nullptr)
		{
			LogUtils::logError(otherItem->getName());
		}
	});
}

void CardsMenu::close()
{
	if (this->equipmentChanged)
	{
		PlatformerEvents::TriggerEquippedItemsChanged();
	}
	
	if (this->returnClickCallback != nullptr)
	{
		this->returnClickCallback();
	}
}
