#include "MiscFilter.h"

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

MiscFilter* MiscFilter::create()
{
	MiscFilter* itemPreview = new MiscFilter();

	itemPreview->autorelease();

	return itemPreview;
}

MiscFilter::MiscFilter() : super (Strings::Menus_Inventory_Misc::create(), UIResources::Menus_InventoryMenu_MiscIcon)
{
}

MiscFilter::~MiscFilter()
{
}

void MiscFilter::onEnter()
{
	super::onEnter();
}

void MiscFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> MiscFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<Misc*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
