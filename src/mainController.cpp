#include "mainController.h"

MainController::MainController() : splashScreen(&window),
								   openMenu(&window),
								   phaseSelection(&window),
								   characterSelection(&window),
								   rankingScreen(&window),
								   playerDieScreen(&window),
								   phaseManager(&window)
{
	window.create(sf::VideoMode(1080, 720), "Arudina's Game");
	window.setFramerateLimit(60);

	window.setMouseCursorVisible(false);

	Start();
}

MainController::~MainController()
{
}

void MainController::Start()
{
	int controller = 0;

	switcher.push_back(static_cast<Menu *>(&splashScreen));
	switcher.push_back(static_cast<Menu *>(&openMenu));
	switcher.push_back(static_cast<Menu *>(&phaseSelection));
	switcher.push_back(static_cast<Menu *>(&characterSelection));
	switcher.push_back(static_cast<Menu *>(&rankingScreen));
	switcher.push_back(static_cast<Menu *>(&playerDieScreen));

	// Soh eh permitido entrar no phaseManager depois de passar do splashScreen, openMenu, phaseSelection e characterSelection, por isso que todos esses elementos passados para o phaseManager ja estao prontos
	while (controller >= 0)
	{
		if (controller != PHASE_MANAGER)				// Esses nomes PHASE_MANAGER, CHARACTER_SELECTION, etc, estao definidas no SwitchPanel
			controller = switcher[controller]->Start(); // Esse metodo Start eh override nas classes, mas a definicao estah no SwitchPanel, um metodo virtual puro
		else
			controller = phaseManager.Start(openMenu.getContinueSave(), characterSelection.getPlayer1Name(), characterSelection.getPlayer2Name(), characterSelection.getIsMultiplayer(), phaseSelection.getWitchPhaseIs());
		// Esse Start do phaseManager, nao estah no SwitchPanel, Eh um metodo da classe phaseManager mesmo, isso porque nao consigo dar override em 1 metodo soh, teria que dar override nesses 2 metodos em todas as classes que fosse usar o outro start
	}

	window.close();
}