#pragma once

#include "Engine/Quests/QuestTask.h"

class HexusOpponentData;
class MagePortal;
class PlatformerEntity;
class QuestLine;
class Squally;

class BeatTutorialF : public QuestTask
{
public:
	static BeatTutorialF* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	BeatTutorialF(GameObject* owner, QuestLine* questLine);
	virtual ~BeatTutorialF();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	MagePortal* portal;
	PlatformerEntity* mage;
	Squally* squally;

	static const std::string QuestPortalTag;
	static const std::string WinLossTrackIdentifier;
};
