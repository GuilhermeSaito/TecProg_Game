#include "save.h"

#include <iomanip>
#include <fstream>
using std::endl;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::setw;

using namespace SaveGame;

Save::Save()
{
}
Save::~Save()
{
}

void Save::continueSave(const string player1Name, const string player2Name, const bool multiplayer, const int phaseIs, sf::Vector2f player1Location, sf::Vector2f player2Location)
{
	ofstream out("src/saveFile/continueSave.json", ios::out | ios::trunc);
	out.exceptions(ios::badbit);

	json j;
	j["players"]["player1Name"] = player1Name;
	j["players"]["player1PositionX"] = player1Location.x;
	j["players"]["player1PositionY"] = player1Location.y;
	j["players"]["multiplayer"] = multiplayer;
	j["players"]["phase"] = phaseIs;
	if (multiplayer)
	{
		j["players"]["player2Name"] = player2Name;
		j["players"]["player2PositionX"] = player2Location.x;
		j["players"]["player2PositionY"] = player2Location.y;
	}

	try
	{
		out << setw(4) << j << endl;
	}
	catch (std::ofstream::failure e)
	{
		std::cerr << "[!] Error writing src/saveFile/continueSave.json.";
		std::cerr << e.what() << "\n";
	}

	out.close();
}

json Save::continueRestore()
{
	ifstream in("src/saveFile/continueSave.json");
	// Testa se o arquivo existe
	if (!in.good())
	{
		throw "[!] src/saveFile/continueSave.json file doesn't exist.";
		exit(EXIT_FAILURE);
	}
	// Testa se o arquivo ta vazio
	in.seekg(0, std::ios::end);
	if (!in.tellg())
	{
		throw "[!] src/saveFile/continueSave.json file is empty.";
		exit(EXIT_FAILURE);
	}
	in.seekg(0, std::ios::beg);

	json j;

	try
	{
		in >> j;
	}
	catch (json::exception &e)
	{
		std::cerr << "[!] Erro na leitura do arquivo src/saveFile/continueSave.json." << std::endl;
		std::cerr << e.what() << std::endl;
		in.close();
		exit(EXIT_FAILURE);
	}
	in.close();

	return j;
}