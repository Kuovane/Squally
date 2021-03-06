#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;
class LocalizedLabel;

class AxesFilter : public CraftFilterEntry
{
public:
	static AxesFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	AxesFilter();
	virtual ~AxesFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
