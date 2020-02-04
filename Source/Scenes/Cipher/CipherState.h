#pragma once
#include <chrono>
#include <vector>

#include "Engine/SmartNode.h"
#include "Events/CipherEvents.h"

namespace cocos2d
{
	class LayerColor;
}

class BlockBase;
class CipherLock;
class CipherPuzzleData;
class CipherState;
class ClickableNode;
class Connection;
class DestinationBlock;
class DisplayModeToggles;
class SourceBlock;

class CipherState : public SmartNode
{
public:
	enum class StateType
	{
		EmptyState,
		GameStart,
		LoadInitialState,
		Neutral,
		TransitionUnlocking,
		Unlocking,
		Testing,
		Wrong,
		Victory,
		GameEnd,
		Tutorial,
	};

	static CipherState* create();
	static void updateState(CipherState* gameState, StateType newState);
	void loadPuzzleData(CipherPuzzleData* puzzleData);
	void loadCipherAtIndex(int index);

	StateType stateType;
	StateType previousStateType;
	int gameDurationInSeconds;
	std::function<void(bool)> updateStateCallback;

	CipherPuzzleData* puzzleData;
	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMap;
	std::vector<std::string> tokens;

	std::vector<SourceBlock*> inputBlocks;
	std::vector<DestinationBlock*> outputBlocks;
	std::vector<BlockBase*> userBlocks;
	std::vector<Connection*> userConnections;
	cocos2d::Node* inputContent;
	cocos2d::Node* outputContent;
	cocos2d::Node* blockContent;
	cocos2d::Node* connectionContent;
	CipherEvents::DisplayDataType displayDataType;
	
	cocos2d::LayerColor* gameAreaDebug;

	std::string currentInput;
	std::string currentOutput;

	CipherLock* cipherLockPointer;
	DisplayModeToggles* displayModeTogglesPointer;

protected:
	CipherState();
	virtual ~CipherState();
	void initializePositions() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

private:
	typedef SmartNode super;

	void clearInteraction();

	std::chrono::time_point<std::chrono::high_resolution_clock> gameStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> gameEndTime;
};
