#include "LoadingScreen.h"

std::vector<ILayerDeserializer*> LoadingScreen::layerDeserializers = {
	new BackgroundDeserializer(),
	new MusicDeserializer(),
	new WeatherDeserializer(),
	new DefaultLayerDeserializer(),
};

std::vector<IObjectDeserializer*> LoadingScreen::objectDeserializers = {
	new IsometricEntityDeserializer(),
	new PlatformerEntityDeserializer(),
	new CollisionDeserializer(),
	new PlatformerDecorDeserializer(),
	new PlatformerObjectDeserializer(),
	new IsometricDecorDeserializer(),
	new IsometricObjectDeserializer(),
};

LoadingScreen * LoadingScreen::create()
{
	LoadingScreen* instance = new LoadingScreen();

	instance->autorelease();

	return instance;
}

LoadingScreen::LoadingScreen()
{
	this->background = Node::create();
	this->progressBar = CProgressBar::create();

	this->addChild(this->background);
	this->addChild(this->progressBar);
	this->addChild(Mouse::create());

	this->setFadeSpeed(0.0f);
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::onEnter()
{
	FadeScene::onEnter();

	this->background->addChild(MenuBackground::claimInstance());

	this->initializePositions();
}

void LoadingScreen::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->progressBar->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 480.0f));
}

void LoadingScreen::loadLevel(std::string levelFile, const std::function<void(SerializableMap*)> newOnLoadCallback)
{
	this->totalFileCount = 0;
	this->loadedFileCount = 0;
	this->currentLevelFile = levelFile;
	this->onLoadCallback = newOnLoadCallback;

	/*
	std::future<SerializableMap *> fut = std::async([levelFile]() {
		return SerializableMap::deserialize(levelFile, &LoadingScreen::layerDeserializers, &LoadingScreen::objectDeserializers);
	});
	*/

	this->map = SerializableMap::deserialize(levelFile, &LoadingScreen::layerDeserializers, &LoadingScreen::objectDeserializers);
	this->map->retain();

	// Asyncronously get all files under the game, and load them
	FileUtils::getInstance()->listFilesRecursivelyAsync(FileUtils::getInstance()->getDefaultResourceRootPath(), CC_CALLBACK_1(LoadingScreen::onFileEnumerationComplete, this));
}

void LoadingScreen::onFileEnumerationComplete(std::vector<std::string> files)
{
	// TEMP DEBUG: Remove this to re-enable loading screen
	if (this->onLoadCallback != nullptr)
	{
		this->onLoadCallback(this->map);
		return;
	}

	auto textureLoadCallback = CC_CALLBACK_1(LoadingScreen::onTextureAssetLoaded, this);
	auto soundLoadCallback = CC_CALLBACK_0(LoadingScreen::onSoundAssetLoaded, this);

	for (auto it = files.begin(); it != files.end(); it++)
	{
		std::string file = *it;

		if (LoadingScreen::isPreloadableImage(file) ||
			LoadingScreen::isPreloadableSound(file))
		{
			this->totalFileCount++;
		}
	}

	for (auto it = files.begin(); it != files.end(); it++)
	{
		std::string file = *it;

		if (LoadingScreen::isPreloadableImage(file))
		{
			// Load texture
			Director::getInstance()->getTextureCache()->addImageAsync(file, textureLoadCallback);
		}
		else if (LoadingScreen::isPreloadableSound(file))
		{
			// Load sound
			AudioEngine::preload(file, soundLoadCallback);
		}
	}

	// In case there are no assets to load we also need to check here
	this->enterLevelIfDoneLoading();
}

void LoadingScreen::onTextureAssetLoaded(Texture2D* asset)
{
	this->incrementLoadedFileCount();
	this->enterLevelIfDoneLoading();
}

void LoadingScreen::onSoundAssetLoaded()
{
	this->incrementLoadedFileCount();
	this->enterLevelIfDoneLoading();
}

void LoadingScreen::enterLevelIfDoneLoading()
{
	if (this->levelIsLoaded())
	{
		if (this->onLoadCallback != nullptr)
		{
			this->onLoadCallback(this->map);
		}
	}
}

void LoadingScreen::incrementLoadedFileCount()
{
	this->loadedFileCount.fetch_add(1);
	this->progressBar->setProgress(this->totalFileCount == 0 ? 0.0f : (float)this->loadedFileCount / (float)this->totalFileCount);
}

bool LoadingScreen::levelIsLoaded() 
{
	return this->loadedFileCount >= this->totalFileCount - 1;
}

bool LoadingScreen::isPreloadableImage(std::string filePath)
{
	if (StrUtils::endsWith(filePath, ".png", true) ||
		StrUtils::endsWith(filePath, ".jpg", true) ||
		StrUtils::endsWith(filePath, ".jpeg", true))
	{
		return true;
	}

	return false;
}

bool LoadingScreen::isPreloadableSound(std::string filePath)
{
	if (StrUtils::endsWith(filePath, ".mp3", true) ||
		StrUtils::endsWith(filePath, ".wav", true))
	{
		return true;
	}

	return false;
}