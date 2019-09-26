#include "NpcInteractionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Common/Dash.h"
#include "Strings/Common/Empty.h"
#include "Strings/Common/Newline.h"
#include "Strings/Common/Triconcat.h"

using namespace cocos2d;

const std::string NpcInteractionBehavior::MapKeyAttachedBehavior = "npc-interaction";

NpcInteractionBehavior* NpcInteractionBehavior::create(GameObject* owner)
{
	NpcInteractionBehavior* instance = new NpcInteractionBehavior(owner);

	instance->autorelease();

	return instance;
}

NpcInteractionBehavior::NpcInteractionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));
	this->stringNode = Node::create();
	this->canInteract = false;
	this->dialogueCollision = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->dialogueCollision = CollisionObject::create(
			PhysicsBody::createBox(this->entity->getEntitySize()),
			(CollisionType)PlatformerCollisionType::Trigger,
			false,
			false
		);

		this->dialogueCollision->getPhysicsBody()->setPositionOffset(this->entity->getCollisionOffset() + Vec2(0.0f, this->entity->getMovementSize().height / 2.0f));
		this->interactMenu->setPosition(this->entity->getCollisionOffset() + Vec2(0.0f, this->entity->getMovementSize().height / 2.0f));

		this->addChild(this->dialogueCollision);
	}
	
	this->addChild(this->interactMenu);
	this->addChild(this->stringNode);
}

NpcInteractionBehavior::~NpcInteractionBehavior()
{
}

void NpcInteractionBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});

	this->dialogueCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = true;
		this->interactMenu->show();

		return CollisionObject::CollisionResult::DoNothing;
	});
		 
	this->dialogueCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = false;
		this->interactMenu->hide();

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_V }, [=](InputEvents::InputArgs* args)
	{
		this->showOptions();
	});

	// Debug
	this->addDialogueOption(DialogueOption(ConstantString::create("How do I buy something?"), nullptr));
	this->addDialogueOption(DialogueOption(ConstantString::create("How about a round of Hexus?"), nullptr));
	this->addDialogueOption(DialogueOption(ConstantString::create("Goodbye."), nullptr));
}

void NpcInteractionBehavior::addDialogueOption(DialogueOption dialogueOption)
{
	this->dialogueOptions.push_back(dialogueOption);

	if (dialogueOption.dialogueOption != nullptr)
	{
		this->stringNode->addChild(dialogueOption.dialogueOption);
	}
}

void NpcInteractionBehavior::showOptions()
{
	if (this->dialogueOptions.empty() || (this->squally != nullptr && this->squally->getStateOrDefaultBool(StateKeys::CinematicHijacked, false)))
	{
		return;
	}

	LocalizedString* options = Strings::Common_Triconcat::create();
	LocalizedString* nextOption = options;
	LocalizedString* currentOption = nextOption;
	int index = 1;

	for (auto it = this->dialogueOptions.begin(); it != this->dialogueOptions.end(); it++, index++)
	{
		bool lastIter = it == (--this->dialogueOptions.end());

		LocalizedString* newline = Strings::Common_Newline::create();
		nextOption = lastIter ? (LocalizedString*)Strings::Common_Empty::create() : (LocalizedString*)Strings::Common_Triconcat::create();
		LocalizedString* option = this->getOptionString(index, (*it).dialogueOption->clone());

		currentOption->setStringReplacementVariables({option , newline, nextOption });
		currentOption = nextOption;
	}

	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		options,
		DialogueBox::DialogueDock::Bottom,
		DialogueBox::DialogueAlignment::Left,
		[=]()
		{
		},
		DialogueEvents::BuildPreviewNode(this->entity, false),
		DialogueEvents::BuildPreviewNode(this->squally, true)
	));
}

LocalizedString* NpcInteractionBehavior::getOptionString(int index, LocalizedString* optionText)
{
	LocalizedString* dash = Strings::Common_Dash::create();
	LocalizedString* brackets = Strings::Common_Brackets::create();

	brackets->setStringReplacementVariables(ConstantString::create(std::to_string(index)));

	dash->setStringReplacementVariables({ brackets, optionText });

	return dash;
}