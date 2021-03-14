#include "data.h"

Data *Data::instance = NULL;

Data::Data()
{
	if (!splashScreen.loadFromFile("src/data/erase.png"))
		EXIT_FAILURE;
	if (!splashScreen2.loadFromFile("src/data/possibleSplashScreen.jpg"))
		EXIT_FAILURE;
	if (!openMenuBackGround.loadFromFile("src/data/imageOpenMenu.png"))
		EXIT_FAILURE;
	if (!beginnerPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/beginnerPhaseBackGround.jpeg"))
		EXIT_FAILURE;
	if (!blueOceanPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/blueOceanPhaseBackGround.png"))
		EXIT_FAILURE;
	if (!cavePhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/cavePhaseBackGround.png"))
		EXIT_FAILURE;
	if (!deathPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/deathPhaseBackGround.png"))
		EXIT_FAILURE;
	if (!fireVolcanoPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/fireVolcanoPhaseBackGround.png"))
		EXIT_FAILURE;
	if (!forestPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/forestPhaseBackGround.jpg"))
		EXIT_FAILURE;
	if (!speranzaPhaseBackGround.loadFromFile("src/data/possiblePhasesBackGround/speranzaPhaseBackGround.jpg"))
		EXIT_FAILURE;
	if (!player1Image.loadFromFile("src/data/players/Player1Image.png"))
		EXIT_FAILURE;
	if (!player2Image.loadFromFile("src/data/players/player2Image.png"))
		EXIT_FAILURE;
	if (!brickFloor.loadFromFile("src/data/phaseMap/tilesUsed/BrickFloor.jpg"))
		EXIT_FAILURE;
	if (!iceFloor.loadFromFile("src/data/phaseMap/tilesUsed/iceFloor1.jpg"))
		EXIT_FAILURE;
	if (!iceFloor2.loadFromFile("src/data/phaseMap/tilesUsed/iceFloor2.jpg"))
		EXIT_FAILURE;
	if (!purpleFloor.loadFromFile("src/data/phaseMap/tilesUsed/purpleFloor.jpg"))
		EXIT_FAILURE;
	if (!playerDieBackGround.loadFromFile("src/data/playerDieImageScenario/deathWithEffectPhrase.jpg"))
		EXIT_FAILURE;
	if (!zombieTexture.loadFromFile("src/data/enemy/zombieTexture.png"))
		EXIT_FAILURE;
	if (!goblinMageTexture.loadFromFile("src/data/enemy/goblinMageTexture.png"))
		EXIT_FAILURE;
	if (!reaperFlyTexture.loadFromFile("src/data/enemy/reaperFlyTexture.png"))
		EXIT_FAILURE;
	if (!bossTexture.loadFromFile("src/data/enemy/bossTexture.png"))
		EXIT_FAILURE;

	if (!openMenufont.loadFromFile("src/data/fonts/TurretRoad-Medium.ttf"))
		EXIT_FAILURE;

	if (!notImplementedYet.loadFromFile("src/data/notImplementedYet.png"))
		EXIT_FAILURE;
}

Data::~Data()
{
	delete instance;
}

Data *Data::getInstance()
{
	if (instance == NULL)
		instance = new Data;
	return instance;
}

sf::Texture *Data::getSplashScreenTexture()
{
	return &splashScreen;
}
sf::Texture *Data::getSplashScreenTexture2()
{
	return &splashScreen2;
}
sf::Texture *Data::getOpenMenuBackGround()
{
	return &openMenuBackGround;
}
sf::Texture *Data::getBeginnerPhaseBackGround()
{
	return &beginnerPhaseBackGround;
}
sf::Texture *Data::getBlueOceanPhaseBackGround()
{
	return &blueOceanPhaseBackGround;
}
sf::Texture *Data::getCavePhaseBackGround()
{
	return &cavePhaseBackGround;
}
sf::Texture *Data::getDathPhaseBackGround()
{
	return &deathPhaseBackGround;
}
sf::Texture *Data::getFireVolcanoPhaseBackGround()
{
	return &fireVolcanoPhaseBackGround;
}
sf::Texture *Data::getForestPhaseBackGround()
{
	return &forestPhaseBackGround;
}
sf::Texture *Data::getSperanzaPhaseBackGround()
{
	return &speranzaPhaseBackGround;
}
sf::Texture *Data::getPlayer1Texture()
{
	return &player1Image;
}
sf::Texture *Data::getPlayer2Texture()
{
	return &player2Image;
}
sf::Texture *Data::getBrickFloor()
{
	return &brickFloor;
}
sf::Texture *Data::getIceFloor()
{
	return &iceFloor;
}
sf::Texture *Data::getIceFloor2()
{
	return &iceFloor2;
}
sf::Texture *Data::getPurpleFloor()
{
	return &purpleFloor;
}
sf::Texture *Data::getPlayerDieBackGroundTexture()
{
	return &playerDieBackGround;
}
sf::Texture *Data::getZombieTexture()
{
	return &zombieTexture;
}
sf::Texture *Data::getGoblinMageTexture()
{
	return &goblinMageTexture;
}
sf::Texture *Data::getReaperFlyTexture()
{
	return &reaperFlyTexture;
}
sf::Texture *Data::getBossTexture()
{
	return &bossTexture;
}

sf::Font *Data::getOpenMenufont()
{
	return &openMenufont;
}

sf::Texture *Data::getNotImplementedYet()
{
	return &notImplementedYet;
}