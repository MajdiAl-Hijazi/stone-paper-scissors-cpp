#include<iostream>
#include<ctime>

using namespace std;

enum enWinner { Player1 = 1 ,Computer = 2, Draw = 3 };

enum enGameChoice { Stone = 1 ,Paper = 2 ,Scissor = 3 };

struct stGameResults {

	short GameRounds = 0;
	short Player1WinTimes = 0;
	short Computer2WinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

struct stRoundInfo {

	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

short ReadHowManyRounds() {

	short GameRounds = 1;
	
	do
	{

		cout << "How Many Rounds 1 to 10 ? \n";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

enGameChoice ReadPlayer1Choice() {

	short Choice = 1;

	do
	{

		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

short RandomNumber(int From ,int To) {

	return ( rand() % (To - From + 1) + From);
}

enGameChoice GetComputerChoice() {

	return (enGameChoice)RandomNumber(1 ,3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {

	if (RoundInfo.ComputerChoice == RoundInfo.Player1Choice)
		return enWinner::Draw;

	switch (RoundInfo.Player1Choice) {
	
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
			return enWinner::Computer;
		break;
	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
		break;
	}

	return enWinner::Player1;
}

string WinnerName(enWinner Winner) {

	string arrWinnerName[3] = { "Player1", "Computer", "No Winner" };
	return arrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice) {

	string arrgameChoice[3] = { "Stone", "Paper", "Scissors"};
	return arrgameChoice[Choice - 1];
}

void PrintRoundResults(stRoundInfo RoundInfo) {

	cout << "\n_____________Round [" << RoundInfo.RoundNumber << "] _____________\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner  : [" << RoundInfo.WinnerName << "] \n";
	cout << "___________________________\n" << endl;

}

enWinner WhoWonTheGame(short Player1WinTimes ,short ComputerWinTimes) {

	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

string Tabs(short NumberofTabs) {

	string t = "";

	for (int i = 1; i < NumberofTabs; i++) {
	
		t += "\t";
	}

	return t;
}

void ShowGameOverScreen() {

	cout << Tabs(2) << "________________________________________________________\n\n";
	cout << Tabs(2) << "                  +++G a m e O v e r +++                \n\n";
	cout << Tabs(2) << "________________________________________________________\n\n";
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes) {

	stGameResults GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.Computer2WinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes ,ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

stGameResults PlayGame(short HowManyRounds) {

	stRoundInfo RoundfInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
	
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundfInfo.RoundNumber = GameRound;
		RoundfInfo.Player1Choice = ReadPlayer1Choice();
		RoundfInfo.ComputerChoice = GetComputerChoice();
		RoundfInfo.Winner = WhoWonTheRound(RoundfInfo);
		RoundfInfo.WinnerName = WinnerName(RoundfInfo.Winner);

		if (RoundfInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundfInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundfInfo);
	}

	return FillGameResults(HowManyRounds, Player1WinTimes ,ComputerWinTimes, DrawTimes);
}

void SetWinnerScreenColor(enWinner Winner) {

	switch (Winner) {
	
	case enWinner::Player1:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
		break;
	}
}

void ShowFinalGameResults(stGameResults GameResults) {

	cout << Tabs(2) << "_________________________ [Game Results ]_________________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.Computer2WinTimes << endl;
	cout << Tabs(2) << "Draw Times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "__________________________________________________________________" << endl;

	SetWinnerScreenColor(GameResults.GameWinner);
}

void ResetScreen() {

	system("cls");
	system("color 0F");
}

void StartGame() {

	char PlatAgain = 'Y';

	do
	{

		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do you want play again Y/N ? ";
		cin >> PlatAgain;

	} while (PlatAgain == 'Y' || PlatAgain == 'y');

}

int main() {

	StartGame();

	return 0;
}