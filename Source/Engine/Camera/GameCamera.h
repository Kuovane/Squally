#pragma once
#include <functional>
#include <stack>

#include "cocos/math/CCGeometry.h"

#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class DrawNode;
	class Node;
	class Vec2;
}

class ClickableNode;
class ConstantString;
class Hud;
class LocalizedLabel;

class GameCamera : public GlobalNode
{
public:
	static void registerGlobalNode();
	static GameCamera* getInstance();

	float getCameraDistance();
	float getCameraDepth();
	float getTargetDepth();
	void setCameraDistance(float distance);
	float getCameraZoomOnTarget(cocos2d::Node* target);
	float getCameraZoomOnTrackedTarget();
	float getCameraZoom();
	void setCameraZoom(float zoom);
	cocos2d::Vec2 getCameraPosition();
	cocos2d::Vec3 getCameraPosition3();
	void setCameraPosition(cocos2d::Vec2 position, bool addTrackOffset = false);
	void setCameraPosition3(cocos2d::Vec3 position, bool addTrackOffset = false);
	void setCameraPositionToTrackedTarget();
	cocos2d::Rect getMapBounds();
	void setMapBounds(cocos2d::Rect mapBounds);
	void shakeCamera(float magnitude, float shakesPerSecond, float duration);
	CameraTrackingData* getCurrentTrackingData();
	void setTarget(CameraTrackingData trackingData, bool immediatelyTrack = false);
	void pushTarget(CameraTrackingData trackingData, bool immediatelyTrack = false);
	void popTargetIfMultiple();
	void popTarget();
	void clearTargets();

protected:
	GameCamera();
	virtual ~GameCamera();
	
	void onEnter() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef GlobalNode super;

	void resetCamera();
	float getIntendedCameraDistance();
	cocos2d::Vec2 boundCameraByEllipses(cocos2d::Vec2 cameraPosition);
	cocos2d::Vec2 boundCameraByRectangle(cocos2d::Vec2 cameraPosition);
	cocos2d::Vec2 boundCameraByMapBounds(cocos2d::Vec2 cameraPosition);
	void updateCameraDebugLabels();

	std::stack<CameraTrackingData> targetStack;
	cocos2d::Rect mapBounds;
	float defaultDistance;

	Hud* hud;
	ClickableNode* debugScrollHitbox;
	LocalizedLabel* debugCameraLabelX;
	LocalizedLabel* debugCameraLabelY;
	LocalizedLabel* debugCameraLabelZoom;
	ConstantString* debugCameraStringX;
	ConstantString* debugCameraStringY;
	ConstantString* debugCameraStringZoom;
	cocos2d::DrawNode* debugCameraRectangle;

	static GameCamera* cameraInstance;
	static const std::string SchedulerKeyCameraShake;
};
