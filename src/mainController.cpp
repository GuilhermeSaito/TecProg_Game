#include "mainController.h"

MainController::MainController()
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

	switcher.push_back(&splashScreen);
	switcher.push_back(&openMenu);
	switcher.push_back(&phaseSelection);
	switcher.push_back(&characterSelection);

	// Soh eh permitido entrar no phaseManager depois de passar do splashScreen, openMenu, phaseSelection e characterSelection, por isso que todos esses elementos passados para o phaseManager ja estao prontos
	while (controller >= 0)
	{
		if (controller != PHASE_MANAGER)					  // Esses nomes PHASE_MANAGER, CHARACTER_SELECTION, etc, estao definidas no SwitchPanel
			controller = switcher[controller]->Start(window); // Esse metodo Start eh override nas classes, mas a definicao estah no SwitchPanel, um metodo virtual puro
		else
			controller = phaseManager.Start(window, openMenu.getContinueSave(), characterSelection.getPlayer1Name(), characterSelection.getPlayer2Name(), characterSelection.getIsMultiplayer(), phaseSelection.getWitchPhaseIs());
		// Esse Start do phaseManager, nao estah no SwitchPanel, Eh um metodo da classe phaseManager mesmo, isso porque nao consigo dar override em 1 metodo soh, teria que dar override nesses 2 metodos em todas as classes que fosse usar o outro start
	}

	window.close();
}