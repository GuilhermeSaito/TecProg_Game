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

void Save::rankingSave(const string player1Name, const string player2Name, const int score, const bool isMultiplayer)
{
	ifstream in("src/saveFile/rankingSave.json");

	json jSave = json::object();
	jSave["state"]["player1Name"] = player1Name;
	jSave["state"]["multiplayer"] = isMultiplayer;
	if (isMultiplayer)
		jSave["state"]["player2Name"] = player2Name;
	jSave["state"]["score"] = score;

	json j = json::object();
	// Verifica se o arquivo existe e nao estah vazio
	if ((in) && (!isFileEmpty(in)))
	{
		try
		{
			in >> j;
		}
		catch (json::exception &e)
		{
			std::cerr << "[!] Erro na leitura do arquivo src/saveFile/rankingSave.json." << std::endl;
			std::cerr << e.what() << std::endl;
			in.close();
			exit(EXIT_FAILURE);
		}
		int flag = 0;
		// Colocando em ordem decrescente em questao dos pontos
		for (auto it = j["ranking"].begin(); it != j["ranking"].end(); it++)
			if ((*it)["state"]["score"] < score)
			{
				flag = 1;
				j["ranking"].insert(it, jSave);
				break;
			}
		if (!flag)
			j["ranking"].push_back(jSave);
	}
	else
	{
		json jRankingArray = json::array();
		jRankingArray.push_back(jSave);
		j["ranking"] = jRankingArray;
	}
	in.close();

	ofstream out("src/saveFile/rankingSave.json", ios::out | ios::trunc);
	out.exceptions(ios::badbit);

	try
	{
		out << setw(4) << j;
	}
	catch (json::exception &e)
	{
		std::cerr << "[!] Erro na escrita do arquivo src/saveFile/rankingSave.json." << std::endl;
		std::cerr << e.what() << std::endl;
		out.close();
		exit(EXIT_FAILURE);
	}
	out.close();
}

json Save::rankingRecover()
{
	ifstream in("src/saveFile/rankingSave.json");
	// Testa se o arquivo existe
	if (!in.good())
	{
		throw "[!] src/saveFile/rankingSave.json file doesn't exist.";
		exit(EXIT_FAILURE);
	}
	// Testa se o arquivo ta vazio
	in.seekg(0, std::ios::end);
	if (!in.tellg())
	{
		throw "[!] src/saveFile/rankingSave.json file is empty.";
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
		std::cerr << "[!] Erro na leitura do arquivo src/saveFile/rankingSave.json." << std::endl;
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

const bool Save::isFileEmpty(std::ifstream &in)
{
	return in.peek() == std::ifstream::traits_type::eof();
}