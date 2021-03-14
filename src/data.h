#pragma once

#include <SFML/Graphics.hpp>

class Data
{
private:
	Data();
	static Data* instance;

	sf::Texture splashScreen;
	sf::Texture splashScreen2;
	sf::Texture openMenuBackGround;
	sf::Texture beginnerPhaseBackGround;
	sf::Texture blueOceanPhaseBackGround;
	sf::Texture cavePhaseBackGround;
	sf::Texture deathPhaseBackGround;
	sf::Texture fireVolcanoPhaseBackGround;
	sf::Texture forestPhaseBackGround;
	sf::Texture speranzaPhaseBackGround;
	sf::Texture player1Image;
	sf::Texture player2Image;
	sf::Texture brickFloor;
	sf::Texture iceFloor;
	sf::Texture iceFloor2;
	sf::Texture purpleFloor;
	sf::Texture playerDieBackGround;
	sf::Texture zombieTexture;
	sf::Texture goblinMageTexture;
	sf::Texture reaperFlyTexture;
	sf::Texture bossTexture;

	sf::Font openMenufont;

	sf::Texture notImplementedYet;

public:
	~Data();
	static Data* getInstance();

	sf::Texture* getSplashScreenTexture();
	sf::Texture* getSplashScreenTexture2();
	sf::Texture* getOpenMenuBackGround();
	sf::Texture* getBeginnerPhaseBackGround();
	sf::Texture* getBlueOceanPhaseBackGround();
	sf::Texture* getCavePhaseBackGround();
	sf::Texture* getDathPhaseBackGround();
	sf::Texture* getFireVolcanoPhaseBackGround();
	sf::Texture* getForestPhaseBackGround();
	sf::Texture* getSperanzaPhaseBackGround();
	sf::Texture* getPlayer1Texture();
	sf::Texture* getPlayer2Texture();
	sf::Texture* getBrickFloor();
	sf::Texture* getIceFloor();
	sf::Texture* getIceFloor2();
	sf::Texture* getPurpleFloor();
	sf::Texture* getPlayerDieBackGroundTexture();
	sf::Texture* getZombieTexture();
	sf::Texture* getGoblinMageTexture();
	sf::Texture* getReaperFlyTexture();
	sf::Texture* getBossTexture();

	sf::Font* getOpenMenufont();

	sf::Texture* getNotImplementedYet();
};

