#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PotionPoolTier1 : public MinMaxPool
{
public:
	static PotionPoolTier1* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	PotionPoolTier1(SampleMethod sampleMethod, int min, int max);
	virtual ~PotionPoolTier1();

private:
	typedef MinMaxPool super;
};
