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

// Classe chamada depois que seta todos os saves
void Save::continueSave()
{
	ofstream out("src/saveFile/continueSave.json", ios::out | ios::trunc);
	out.exceptions(ios::badbit);

	//creating the object that will contain all the information from jArrayEnemies
	json jObjEnemy = json::object();
	jObjEnemy["enemies"] = jArrayEnemies;
	//including this object in the main array
	jArray.push_back(jObjEnemy);

	json jSave = json::object();
	jSave["gamePlaySave"] = jArray;
	try
	{
		out << setw(4) << jSave << endl;
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

void Save::setPhasePlayerName(const string player1Name, const string player2Name, const bool multiplayer, const int phaseIs)
{
	json j = json::object();

	// Na verdade, da para mudar o phaseIs, multiplayer, para outros nomes, mas ai vai ficando grande o save...
	j["players"]["player1Name"] = player1Name;
	j["players"]["multiplayer"] = multiplayer;
	j["players"]["phase"] = phaseIs;
	if (multiplayer)
		j["players"]["player2Name"] = player2Name;

	jArray.push_back(j);
}

void Save::setPlayer1Save(json jPlayer1)
{
	jArray.push_back(jPlayer1);
}

void Save::setEnemiesSave(json jEnemie)
{
	jArrayEnemies.push_back(jEnemie);
}

void Save::setPlayer2Save(json jPlayer2)
{
	if (!jPlayer2.empty())
		jArray.push_back(jPlayer2);
	else
		std::cout << "Player 2 json is empty!!" << std::endl;
}

void Save::clearJson()
{
	jArray.clear();
	jArrayEnemies.clear();
}