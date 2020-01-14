#pragma once
#include <functional>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class CurrencyInventory;
class EquipmentInventory;
class Item;
class ItemMenu;
class Inventory;
class LocalizedLabel;
class FilterMenu;

class CraftingMenu : public SmartNode
{
public:
	static CraftingMenu* create();

	void open();
	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	CraftingMenu();
	~CraftingMenu();

private:
	typedef SmartNode super;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onFilterChange();
	void populateItemList();
	void performEquipmentAction(Item* item);
	void performInventoryAction(Item* item);
	void equipHexusCard(Item* card);
	void unequipHexusCard(Item* card);
	void equipItem(Item* item);
	void unequipItem(Item* item);
	void close();

	cocos2d::LayerColor* backdrop;
	cocos2d::Sprite* craftingWindow;
	LocalizedLabel* craftingLabel;
	FilterMenu* filterMenu;
	ItemMenu* itemMenu;
	ClickableTextNode* returnButton;
	ClickableNode* closeButton;

	CurrencyInventory* currencyInventory;
	EquipmentInventory* equipmentInventory;
	Inventory* inventory;

	std::function<void()> returnClickCallback;
	bool equipmentChanged;

	static const int MinHexusCards;
	static const int MaxHexusCards;
};
