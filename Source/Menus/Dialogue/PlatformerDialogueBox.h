#pragma once

#include "Engine/Dialogue/DialogueBox.h"

class LocalizedLabel;
class LocalizedString;
class SmartClippingNode;
 
class PlatformerDialogueBox : public DialogueBox
{
public:
	static PlatformerDialogueBox* create();

protected:
	void runDialogue(LocalizedString* localizedString, DialogueBox::DialogueDock dialogueDock, DialogueBox::DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose, bool allowSpace, bool unhijack);
	void hideDialogue() override;
	void onTypeWriterEffectComplete() override;

private:
	typedef DialogueBox super;
	PlatformerDialogueBox();
	virtual ~PlatformerDialogueBox();

	void initializePositions() override;
	void initializeListeners() override;

	LocalizedLabel* spaceToContinueLabel;
	SmartClippingNode* leftSpeakerClip;
	SmartClippingNode* rightSpeakerClip;
	cocos2d::DrawNode* leftSpeakerBackground;
	cocos2d::DrawNode* rightSpeakerBackground;
	cocos2d::Node* leftSpeakerNode;
	cocos2d::Node* rightSpeakerNode;

	bool isDialogueFocused;
	bool allowSpace;
	bool unhijack;

	static const cocos2d::Color4F SpeakerBackgroundColor;
	static const float TextWidth;
	static const float SpeakerPanelWidth;
	static const float SpeakerPanelOffset;
};
