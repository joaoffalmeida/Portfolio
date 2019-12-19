#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <algorithm>
#include <limits>

class Player
{
	int playerScore = 0;
public:

	//getter and setter for player score
	int getPlayerScore()
	{
		return this->playerScore;
	}
	void setPlayerScore(int pScore)
	{
		this->playerScore += pScore;
	}
};

class Bot
{
	int botScore = 0;
public:

	//getter and setter for player score
	int getBotScore()
	{
		return this->botScore;
	}
	void setBotScore(int bScore)
	{
		this->botScore += bScore;
	}
};

class Tile
{
private:
	int x;
	int y; //coordinates
	int score;
	bool isOccupied;
	std::string tileTitle;
	std::string bonus;
	std::string letter;
	std::string direction;
public:

	//Getters and Setters to manipulate the tiles
	void setDirection(std::string dir)
	{
		this->direction = dir;
	}
	std::string getDirection()
	{
		return this->direction;
	}

	int getCoordenateX()
	{
		return this->x;
	}
	void setCoordenateX(int x)
	{
		this->x = x;
	}

	int getCoordenateY()
	{
		return this->y;
	}
	void setCoordenateY(int y)
	{
		this->y = y;
	}

	std::string getBonus()
	{
		return this->bonus;
	}
	void setBonus(std::string newBonus)
	{
		this->bonus = newBonus;
	}

	std::string getTileTitle()
	{
		return this->tileTitle;
	}
	void setTileTitle(std::string newTileTitle)
	{
		this->tileTitle = newTileTitle;
	}

	int getScore()
	{
		return this->score;
	}
	void setScore(int newScore)
	{
		this->score = newScore;
	}

	std::string getLetter()
	{
		return this->letter;
	}
	void setLetter(std::string newLetter)
	{
		this->letter = newLetter;
	}

	bool getOccupation()
	{
		return this->isOccupied;
	}
	void setOccupation(bool newOccupation)
	{
		this->isOccupied = newOccupation;
	}
};

class Game
{

	std::vector<std::string> vecComp; //vector to compare with word
	//NPC stuff
	std::vector <std::string> npcHand;
	std::string botDir;

	//Player stuff
	std::vector <std::string> playerHand;
	std::vector <std::string> letterPool = {
	"a", "a", "a", "a", "a", "a", "a", "a", "a", "b",
	"b", "c", "c", "d", "d", "d", "d", "e", "e", "e",
	"e", "e", "e", "e", "e", "e", "e", "e", "e", "f",
	"f", "g", "g", "g", "h", "h", "i", "i", "i", "i",
	"i", "i", "i", "i", "i", "j", "k", "l", "l", "l",
	"l", "m", "m", "n", "n", "n", "n", "n", "n", "o",
	"o", "o", "o", "o", "o", "o", "o", "p", "p", "q",
	"r", "r", "r", "r", "r", "r", "s", "s", "s", "s",
	"t", "t", "t", "t", "t", "t", "u", "u", "u", "u",
	"v", "v", "w", "w", "x", "y", "y", "z", " ", " "
	};
	Player myPlayer;
	Tile myTile;
	Bot myBot;

public:
	int round_counter = 0;
	int score = 0;
	std::vector<std::string> botVec; //vector used to insert the playable words
	std::map<std::string, int> fR_existing_words = {}; //first round words
	std::map<std::string, int> oR_existing_words = {}; //other round words
	Tile boardArray[15][15]; // 15x15 board of type class Tile to use its methods and functions
	std::string word; //word to be played
	bool check;
	int botPassCounter = 0;


	void setBotDir(std::string newBotDir)
	{
		this->botDir = newBotDir;
	}
	std::string getBotDir()
	{
		return this->botDir;
	}

	void setLettersIntersec(std::vector <std::string> newLetterIntersect)
	{
		this->vecComp = newLetterIntersect;
	}
	std::vector <std::string> getLettersIntersec()
	{
		return this->vecComp;
	}

	std::vector<std::string> returnBotHand()
	{
		return this->npcHand;
	}

	std::vector<std::string> getPlayerHand(std::vector<std::string> myHand)
	{
		int selector = 0;
		std::string blankSpaceSwapper;
		for (int i = myHand.size(); i < 7; i++)
		{
			selector = rand() % getLetterPool().size();
			if (letterPool[selector] == " ")
			{
				std::cout << "You've been granted a blank space. You can swap it for any letter that you wish..." << std::endl;
				std::cout << "Swap blank space for: ";
				std::cin >> blankSpaceSwapper;
				myHand.push_back(blankSpaceSwapper);
			}
			else
			{
				myHand.push_back(letterPool[selector]);
			}
			letterPool.erase(letterPool.begin() + selector);
		}
		setLetterPool(letterPool);
		return myHand;
	}
	void setPlayerHand(std::vector<std::string> newPlayerHand)
	{
		this->playerHand = newPlayerHand;
	}

	std::vector<std::string> getLetterPool()
	{
		return this->letterPool;
	}
	void setLetterPool(std::vector <std::string> newLetterPool)
	{
		this->letterPool = newLetterPool;
	}

	//print hand onto the console
	void printHand(std::vector<std::string> myHand)
	{
		if (round_counter % 2 == 0)
		{
			std::cout << "Player Hand: [";
		}
		else
		{
			std::cout << "NPC Hand: [";
		}
		for (int i = 0; i < myHand.size(); i++)
		{
			if (i == myHand.size() - 1)
			{
				std::cout << myHand[i];
			}
			else
			{
				std::cout << myHand[i] << " ";
			}
		}
		std::cout << "]" << std::endl;
	}

	//create and shows hands
	void giveHand()
	{
		if (round_counter % 2 == 0)
		{
			playerHand = getPlayerHand(playerHand);
			printHand(playerHand);
		}
		else
		{
			npcHand = getPlayerHand(npcHand);
			printHand(npcHand);
		}
		
	}

	//check if hand can make word
	bool checkHand(std::string pWord, std::vector<std::string> letterIntersected)
	{
		int match_checker = 0;
		int wordSize = pWord.size(); // 3
		int letterInt = letterIntersected.size(); // 2
		int playerHandSize;
		
		int compWordBoard = wordSize - letterInt; // 1
		std::vector<std::string> handBackUp = playerHand;
		for (int i = 0; i < letterIntersected.size(); i++)
		{
			playerHand.push_back(letterIntersected[i]); //add letters intersected to the player hand
			//letterIntersected.erase(letterIntersected.begin() + i);
		}

		//compares the player hand with the word played
		for (int i = 0; i < wordSize; i++)
		{
			std::string s(1, pWord[i]);
			for (int j = 0; j < playerHand.size(); j++)
			{
				if (s == playerHand[j])
				{
					match_checker++;
					playerHand.erase(playerHand.begin() + j);
					break;
				}
			}
		}
		playerHandSize = playerHand.size(); //6
		if (match_checker == wordSize && compWordBoard > 0 && (7 - compWordBoard) == playerHandSize) //if we've got enough letters from both board and hand
		{
			return true;
		}
		else
		{
			playerHand = handBackUp;
			printHand(playerHand);
			return false;
		}
	}

	bool checkHandR0(std::string pWord)
	{
		int noElemToRemove = 0;
		for (int i = 0; i < pWord.length(); i++)
		{
			for (int c = 0; c < playerHand.size(); c++)
			{
				std::string converter(1, pWord[i]); //convert char to string
				if (playerHand[c] == converter)
				{
					playerHand.push_back(converter);
					playerHand.erase(playerHand.begin() + c);
					noElemToRemove++;
					break;
				}
			}
		}
		if (noElemToRemove == pWord.length())
		{
			for (int i = noElemToRemove; i > 0; i--)
			{
				playerHand.pop_back();
			}
			setPlayerHand(playerHand);
			return true;
		}
		else
		{
			return false;
		}
	}

	//creates the board internally
	void makeBoard()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				int j_s = j * j;
				int i_s = i * i;
				if (i == j || (i + j) == (15 - 1)) //will retrieve the diagonals
				{
					if (i == 0 || i == 14)
					{
						boardArray[i][j].setBonus("TWS");
						boardArray[i][j].setTileTitle("TWS");
						boardArray[i][j].setOccupation(false);
						boardArray[i][j].setScore(3);
					}
					if (i >= 1 && i <= 4 || i >= 10 && i <= 13 || i == 7)
					{
						boardArray[i][j].setBonus("DWS");
						boardArray[i][j].setTileTitle("DWS");
						boardArray[i][j].setOccupation(false);
						boardArray[i][j].setScore(2);
					}
					if (i == 5 || i == 9)
					{
						boardArray[i][j].setBonus("TLS");
						boardArray[i][j].setTileTitle("TLS");
						boardArray[i][j].setOccupation(false);
						boardArray[i][j].setScore(3);
					}
					if (i == 6 || i == 8)
					{
						boardArray[i][j].setBonus("DLS");
						boardArray[i][j].setTileTitle("DLS");
						boardArray[i][j].setOccupation(false);
						boardArray[i][j].setScore(2);
					}
				}
				else if (i_s + j_s == 49 || i_s + j_s == 245)
				{
					boardArray[i][j].setBonus("TWS");
					boardArray[i][j].setTileTitle("TWS");
					boardArray[i][j].setOccupation(false);
					boardArray[i][j].setScore(3);
				}
				else if (i_s + j_s == 26 || i_s + j_s == 82 || i_s + j_s == 194 || i_s + j_s == 250)
				{
					boardArray[i][j].setBonus("TLS");
					boardArray[i][j].setTileTitle("TLS");
					boardArray[i][j].setOccupation(false);
					boardArray[i][j].setScore(3);
				}
				else if (i_s + j_s == 9 || i_s + j_s == 121 || i_s + j_s == 40 || i_s + j_s == 68 || i_s + j_s == 58 ||
					i_s + j_s == 205 && i == 14 || i_s + j_s == 205 && i == 3 || i_s + j_s == 180 ||
					i_s + j_s == 170 || i_s + j_s == 208 || i_s + j_s == 317)
				{
					boardArray[i][j].setBonus("DLS");
					boardArray[i][j].setTileTitle("DLS");
					boardArray[i][j].setOccupation(false);
					boardArray[i][j].setScore(2);
				}
				else
				{
					boardArray[i][j].setBonus("   ");
					boardArray[i][j].setOccupation(false);
					boardArray[i][j].setScore(1);
				}
			}
		}
	}

	//prints the rules to the player
	void gameRules()
	{
		std::cout << "+--------------------------------------- INTRODUCTION ---------------------------------------+\n";
		std::cout << " Scrabble is a word game where players score points by placing tiles onto a\n";
		std::cout << " 15x15 board. The tiles the player plays must form words that, are read from left to right\n";
		std::cout << " or top to bottom. The words must belong to a standard dictionary or lexicon.\n";
		std::cout << "+---------------------------------------    RULES    ----------------------------------------+\n";
		std::cout << " 1. The first player combines two or more letters of her/his hand to form a word that will\n";
		std::cout << " start in the middle of the board;\n";
		std::cout << " 2. After the player plays his/her hand, the words and letters will be given a total score;\n";
		std::cout << " 3. The players must always have seven letters as long as there are letters available;\n";
		std::cout << " 4. Letters/Words can't be changed to new positions;\n";
		std::cout << " 5. The game ends when all letters have been given and when all possible plays have been made.\n";
		std::cout << " 6. To change a word before inserting, type 'x' instead of inserting the direction.\n";
		std::cout << " 7. If you want to skip your turn, type in 'pass' when being asked for the word.\n";
		std::cout << "+--------------------------------------------------------------------------------------------+\n";
		std::cout << std::endl;
	}

	//get the base score of the word as well as single letters
	int getScore(std::string myInput)
	{
		score = 0;
		int b = 0;

		for (char c : myInput)
		{
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'l' ||
				c == 'n' || c == 's' || c == 't' || c == 'r')
			{
				score += 1;
			}
			else if (c == 'd' || c == 'g')
			{
				score += 2;
			}
			else if (c == 'b' || c == 'c' || c == 'm' || c == 'p')
			{
				score += 3;
			}
			else if (c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y')
			{
				score += 4;
			}
			else if (c == 'k')
			{
				score += 5;
			}
			else if (c == 'j' || c == 'x')
			{
				score += 8;
			}
			else if (c == 'q' || c == 'z')
			{
				score += 10;
			}
		}
		return score;
	}

	//reads the file containing words and passes into onto a variable to check if the word doesn't have special characters
	void parseFile(std::ifstream& words_file, std::string words_input)
	{
		int checkIntegrity;
		while (words_file >> words_input) //while reading the file
		{
			checkIntegrity = 0;
			for (unsigned i = 0; i < words_input.length(); i++)
			{
				if ((int)words_input[i] >= 97 && (int)words_input[i] <= 122 && words_input.length() <= 15) //if letters in word are in the alphabet
				{
					checkIntegrity++;
				}

				if (checkIntegrity == words_input.length()) //if all letters match with the requirements
				{
					if (words_input.length() <= 7)
					{
						fR_existing_words[words_input] = getScore(words_input); //first row can only take words up to 7 letters
					}
					else
					{
						oR_existing_words[words_input] = getScore(words_input);
					}
				}
			}
		}

		std::cout << "\nNumber of usable words: " << fR_existing_words.size() + oR_existing_words.size() << std::endl;
		std::cout << std::endl;
	}

	void checkPlayerWord() // check if the player's word is valid
	{
		std::map<std::string, int>::iterator it; // will be used to iterate over the map;
		std::cout << "Word to play: ";
		std::cin >> this->word;

		if (this->word == "pass")
		{
			botPassCounter++;
			round_counter++;
		}
		else if (this->word.length() <= 7)
		{
			it = fR_existing_words.find(this->word);
			if (it == fR_existing_words.end())
			{
				this->check = false;
				std::cout << "The word is not in the dictionary. Type in another one.\n";
				std::cout << std::endl;

				checkPlayerWord();
			}
			else
			{
				this->check = true;
				checkCoordenates();
			}
		}
		else
		{
			it = oR_existing_words.find(this->word);
			if (it == oR_existing_words.end())
			{
				this->check = false;
				std::cout << "The word is not in the dictionary. Type in another one.\n";
				std::cout << std::endl;

				checkPlayerWord();
			}
			else
			{
				this->check = true;
				checkCoordenates();
			}
		}
	}

	void askDirection()
	{
		std::string dir;
		std::cout << "Direction (v/h): ";
		std::cin >> dir;
		dir = tolower(dir[0]);
		if (dir == "v" || dir == "h")
		{
			myTile.setDirection(dir);
		}
		else if (dir == "x")
		{
			std::cout << "You've reseted your word input successfuly. Input a new word." << std::endl;
			printHand(playerHand);
			checkPlayerWord();
		}
		else
		{			
			std::cout << "Invalid direction. Type in a new one..." << std::endl;
			askDirection();
		}
	}

	void checkCoordenates()
	{
		if (this->check == true)
		{
			int x = 0;
			int y = 0;
			askDirection();
			if (round_counter == 0)
			{
				if (this->word.length() > 7)
				{
					std::cout << "Size of the first word must be <= 7. Please play again!" << std::endl;
				}
				else
				{
					myTile.setCoordenateX(8);
					myTile.setCoordenateY(8);
					insertWordInBoard(this->word);
				}
			}
			else
			{
				std::cout << "Coordinate x (1-15): ";
				std::cin >> x;
				myTile.setCoordenateX(x);
				std::cout << "Coordinate y (1-15): ";
				std::cin >> y;
				myTile.setCoordenateY(y);
				insertWordInBoard(this->word);
			}
		}
	}

	//mathmatically gets the final score depending on where it was played
	int getWordFinalScore(std::string pWord, std::string dir, int y, int x)
	{
		int bonValue = 0; //bonus va
		int twsM = 1;
		int dwsM = 1;

		std::string bonTag;

		if (dir == "v")
		{
			for (char c : pWord)
			{
				bonTag = boardArray[y - 1][x - 1].getTileTitle(); //gets the information for each tile
				std::string ch(1, c);
				if (bonTag == "DLS") //double letter
				{
					bonValue += getScore(ch) * boardArray[y - 1][x - 1].getScore();
				}
				else if (bonTag == "TLS") //triple letter
				{
					bonValue += getScore(ch) * boardArray[y - 1][x - 1].getScore();
				}
				else //no bonus
				{
					bonValue += getScore(ch);
				}
				y++;
			}
			y = myTile.getCoordenateY();
			for (char c : pWord)
			{
				bonTag = boardArray[y - 1][x - 1].getTileTitle();
				if (bonTag == "TWS") //triple word
				{
					twsM = boardArray[y - 1][x - 1].getScore();
					bonValue *= twsM;
				}
				else if (bonTag == "DWS") //double word
				{
					dwsM = boardArray[y - 1][x - 1].getScore();
					bonValue *= dwsM;
				}
				y++;
			}
		}
		else
		{
			for (char c : pWord)
			{
				bonTag = boardArray[y - 1][x - 1].getTileTitle();
				std::string ch(1, c);
				if (bonTag == "DLS")
				{
					bonValue += getScore(ch) * boardArray[y - 1][x - 1].getScore();
				}
				else if (bonTag == "TLS")
				{
					bonValue += getScore(ch) * boardArray[y - 1][x - 1].getScore();
				}
				else
				{
					bonValue += getScore(ch);
				}
				x++;
			}
			x = myTile.getCoordenateX();
			for (char c : pWord)
			{
				bonTag = boardArray[y - 1][x - 1].getTileTitle();
				if (bonTag == "TWS")
				{
					twsM = boardArray[y - 1][x - 1].getScore();
					bonValue *= twsM;
				}
				else if (bonTag == "DWS")
				{
					dwsM = boardArray[y - 1][x - 1].getScore();
					bonValue *= dwsM;
				}
				x++;
			}
		}
		return bonValue;
	}

	void insertInBoardInH(std::string pWord, unsigned int ocpCounter)
	{
		int x = 0;
		x = myTile.getCoordenateX(); //retrieve the Y coordenate played by the player
		int xCoorBackUp = 0;
		xCoorBackUp = x; //creates a backup because we will need the value of Y untouched
		unsigned int attempt = 0; //variable to check if the word played intersects another one (it must)

		int score = 0;

		vecComp.clear(); //clear vector

		if (pWord.length() + x > 16) //if the word won't fit the board
		{
			std::cout << "Word is too big for coordinates given.\n Type in other coordinates." << std::endl;
			checkCoordenates();
		}
		else
		{
			if (round_counter == 0) //the first round
			{
				if (checkHandR0(pWord)) //if word is playable
				{
					score = getWordFinalScore(pWord, myTile.getDirection(), 8, 8);
					x = myTile.getCoordenateX();
					std::string forHandComparison(1, pWord[0]);
					for (char c : pWord)
					{
						std::string ch(1, toupper(c));
						std::string forHandComparison(1, c);
						boardArray[7][x - 1].setBonus(' ' + ch + ' ');
						boardArray[7][x - 1].setLetter(' ' + ch + ' ');
						boardArray[7][x - 1].setOccupation(true);
						vecComp.push_back(forHandComparison);
						x++;
					}
					vecComp.push_back(forHandComparison);
					setLettersIntersec(vecComp);
					myPlayer.setPlayerScore(score);
					round_counter = 1;
				}
				else
				{
					std::cout << "The letters you hold do not match the letters in the word. Please play again." << std::endl;
					printHand(playerHand);
					checkPlayerWord();
				}
			}
			else
			{
				//runs through all coordinates that the word might occupie
				for (unsigned int i = 0; i < pWord.length(); i++)
				{
					if (boardArray[myTile.getCoordenateY() - 1][x - 1].getOccupation() == false)
					{
						x++;
						ocpCounter++; //counter for empty tiles
					}
					else
					{
						x++;
					}
				}

				if (ocpCounter < pWord.length()) // if the word intersects another one...
				{
					for (char c : pWord)
					{
						char comp;
						std::string comparator;
						comparator = boardArray[myTile.getCoordenateY() - 1][xCoorBackUp - 1].getLetter(); //gets the data on that tile
						comparator.erase(std::remove_if(comparator.begin(), comparator.end(), isspace), comparator.end()); //remove white spaces from string
						std::transform(comparator.begin(), comparator.end(), comparator.begin(), ::tolower); //converts string to lower case
						comp = comparator[0];
						if (int(comp) >= 97 && int(comp) <= 122)
						{
							vecComp.push_back(comparator); //insert the letters that will be intersected onto the vector to compare
						}
						setLettersIntersec(vecComp);
						xCoorBackUp++;
					}
					xCoorBackUp = myTile.getCoordenateX();
					if (checkHand(pWord, vecComp)) //if word is playable
					{
						for (char c : pWord)
						{
							std::string s(1, toupper(c));
							std::string concatenated;
							std::string comparator;
							concatenated = " " + s + " ";
							comparator = boardArray[myTile.getCoordenateY() - 1][xCoorBackUp - 1].getLetter();
							if (comparator == concatenated) //if letters match and there are enough words in hand and board to build up the word
							{
								attempt++; //attempt to see if word will be playable
							}

							else if (comparator != concatenated && comparator == "") //if the player is trying to place a letter in a blank tile
							{
								attempt++;
							}

							else //if they do not match, tells the user why it didn't
							{
								std::cout << "\n" << s << " of " << pWord << " and " << comparator << " in (" <<
									xCoorBackUp << "," << myTile.getCoordenateY() << ") do not match!\n\n";
								checkCoordenates();
							}
							xCoorBackUp++;
						}

						if (attempt == pWord.length()) //if there are enough spaces for the tile
						{
							xCoorBackUp = myTile.getCoordenateX();
							score = getWordFinalScore(pWord, myTile.getDirection(), myTile.getCoordenateY(), xCoorBackUp);
							for (unsigned int i = 0; i < pWord.length(); i++)
							{
								std::string s(1, toupper(pWord[i]));
								boardArray[myTile.getCoordenateY() - 1][xCoorBackUp - 1].setBonus(' ' + s + ' ');
								boardArray[myTile.getCoordenateY() - 1][xCoorBackUp - 1].setLetter(' ' + s + ' ');
								boardArray[myTile.getCoordenateY() - 1][xCoorBackUp - 1].setOccupation(true);
								xCoorBackUp++;
							}
							attempt = 0;
							myPlayer.setPlayerScore(score);
						}
					}
					else
					{
						std::cout << "Can't build up '" << pWord << "' in H from letters in hand.\nType in a new one." << std::endl;
						printHand(playerHand);
						checkPlayerWord();
					}

					round_counter++;
				}
				else
				{
					std::cout << "Words are too far away!\n\n" << std::endl;
					checkCoordenates();
				}				
			}
		}
	}

	void insertInBoardInV(std::string pWord, unsigned int ocpCounter)
	{
		int y = 0;
		y = myTile.getCoordenateY(); //retrieve the Y coordenate played by the player
		int yCoorBackUp = 0;
		yCoorBackUp = y; //creates a backup because we will need the value of Y untouched
		unsigned int attempt = 0; //variable to check if the word played intersects another one (it must)

		int score = 0;

		vecComp.clear(); //clear vector

		if (pWord.length() + y > 16) //if the word won't fit the board
		{
			std::cout << "Word is too big for coordinates given.\n Type in other coordinates." << std::endl;
			checkCoordenates();
		}
		else
		{
			if (round_counter == 0)
			{
				if (checkHandR0(pWord))
				{
					score = getWordFinalScore(pWord, myTile.getDirection(), 8, 8);
					y = myTile.getCoordenateY();
					std::string forHandComparison(1, pWord[0]);
					for (char c : pWord)
					{
						std::string ch(1, toupper(c));
						//std::string forHandComparison(1, c);
						boardArray[y - 1][7].setBonus(' ' + ch + ' ');
						boardArray[y - 1][7].setLetter(' ' + ch + ' ');
						boardArray[y - 1][7].setOccupation(true);
						//vecComp.push_back(forHandComparison);
						y++;
					}
					vecComp.push_back(forHandComparison);
					setLettersIntersec(vecComp);
					myPlayer.setPlayerScore(score);
					round_counter = 1;
				}
				else
				{
					std::cout << "The letters you hold do not match the letters in the word. Please play again." << std::endl;
					printHand(playerHand);
					checkPlayerWord();
				}
			}
			else
			{
				for (unsigned int i = 0; i < pWord.length(); i++)
				{
					if (boardArray[y - 1][myTile.getCoordenateX() - 1].getOccupation() == false)
					{
						y++;
						ocpCounter++;
					}
					else
					{
						y++;
					}
				}

				if (ocpCounter < pWord.length()) // if the words intersects another one...
				{
					for (char c : pWord) //insert letters in vec to compare
					{
						char comp;
						std::string comparator;
						comparator = boardArray[yCoorBackUp - 1][myTile.getCoordenateX() - 1].getLetter();
						comparator.erase(std::remove_if(comparator.begin(), comparator.end(), isspace), comparator.end()); //remove white spaces from string
						std::transform(comparator.begin(), comparator.end(), comparator.begin(), ::tolower); //converts string to lower case
						comp = comparator[0];
						if (int(comp) >= 97 && int(comp) <= 122)
						{
							vecComp.push_back(comparator);
						}
						setLettersIntersec(vecComp);
						yCoorBackUp++;
					}

					yCoorBackUp = myTile.getCoordenateY();
					if (checkHand(pWord, vecComp)) //if there are enough words in hand and board to build up the word
					{
						for (char c : pWord)
						{
							std::string s(1, toupper(c));
							std::string concatenated;
							std::string comparator;
							//std::string comp_lower;
							concatenated = " " + s + " ";
							comparator = boardArray[yCoorBackUp - 1][myTile.getCoordenateX() - 1].getLetter();
							if (comparator == concatenated) //if letter of word played match a letter in the tile
							{
								attempt++;
							}

							else if (comparator != concatenated && comparator == "") //if the player is trying to place a letter in a blank tile
							{
								attempt++;
							}

							else
							{
								std::cout << "\n" << s << " of " << pWord << " and " << comparator << " in (" <<
									myTile.getCoordenateX() << "," << yCoorBackUp << ") do not match!\n\n";
								checkCoordenates();
							}
							yCoorBackUp++;
						}

						if (attempt == pWord.length())
						{
							yCoorBackUp = myTile.getCoordenateY();
							score = getWordFinalScore(pWord, myTile.getDirection(), yCoorBackUp, myTile.getCoordenateX());
							for (unsigned int i = 0; i < pWord.length(); i++)
							{
								std::string s(1, toupper(pWord[i]));
								boardArray[yCoorBackUp - 1][myTile.getCoordenateX() - 1].setBonus(' ' + s + ' ');
								boardArray[yCoorBackUp - 1][myTile.getCoordenateX() - 1].setLetter(' ' + s + ' ');
								boardArray[yCoorBackUp - 1][myTile.getCoordenateX() - 1].setOccupation(true);
								yCoorBackUp++;
							}
							attempt = 0;
							myPlayer.setPlayerScore(score);
						}
					}
					else
					{
						std::cout << "Can't build up '" << pWord << "' in V from letters in hand.\nType in a new one." << std::endl;
						printHand(playerHand);
						checkPlayerWord();
					}
					round_counter++;
				}
				else
				{
					std::cout << "Words are too far away!\n\n" << std::endl;
					checkCoordenates();
				}
			}
		}
	}

	void insertWordInBoard(std::string pWord)
	{
		unsigned int ocpCounter = 0;
		if (myTile.getDirection() == "v")
		{
			insertInBoardInV(pWord, ocpCounter);
		}
		else if (myTile.getDirection() == "h")
		{
			insertInBoardInH(pWord, ocpCounter);
		}
	}

	//draw board to the user
	void drawBoard()
	{
		std::cout << "      1     2     3     4     5     6     7     8     9    10    11    12    13    14    15" << std::endl;
		std::cout << "   +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << std::endl;
		for (int i = 0; i < 15; i++)
		{
			if (i <= 8)
			{
				std::cout << " " << i + 1 << " | ";
			}
			else
			{
				std::cout << i + 1 << " | ";
			}

			for (int j = 0; j < 15; j++)
			{
				std::cout << boardArray[i][j].getBonus() << " | ";
			}

			std::cout << std::endl;
			std::cout << "   +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << std::endl;
		}
	}

	//------------------------------------ NPC ----------------------------------------------
	bool isGoodWord(std::string fWord, std::vector<std::string> npcHand)
	{
		std::vector<std::string> npcHandBackUp = npcHand;
		int matcher = 0; //check if letters in "hand" and letters in word match
		for (int i = 0; i < fWord.length(); i++)
		{
			std::string s(1,fWord[i]); //convert char into string
			for (int j = 0; j < npcHand.size(); j++)
			{
				if (npcHand[j] == s)
				{
					matcher++;
					npcHand.erase(npcHand.begin() + j);
					break;
				}
			}
			
		}
		if (matcher == fWord.length()) //if the number of letters in hand are the same has in word, they match
		{
			return true;
		}
		else
		{
			npcHand = npcHandBackUp;
			return false;
		}
	}

	std::string botWord(std::vector<std::string> npcHand) //npcHand contains 7 random letters from the english alphabet
	{
		std::vector<std::string> handBU = npcHand; //npcHand back up
		botVec.clear(); //clear all words (to make sure there is no word left from previous round)
		bool checkLetterInterShow = false;
		int x = myTile.getCoordenateX(); //gets the coordenate x of last played word
		int y = myTile.getCoordenateY(); //gets the coordenate y of last played word
		std::string ltInter = boardArray[y - 1][x - 1].getLetter(); //gets the letter residing in those coorddinates
		ltInter.erase(std::remove_if(ltInter.begin(), ltInter.end(), isspace), ltInter.end()); //remove white spaces from string
		std::transform(ltInter.begin(), ltInter.end(), ltInter.begin(), ::tolower); //converts string to lower case
		std::map<std::string, int>::iterator it = fR_existing_words.begin();
		int randSelect = 0;
		std::vector<std::string> wordToRem;
		npcHand.push_back(ltInter);
		while (it != fR_existing_words.end()) //while reading through all dictionary of acceptable words...
		{
			std::string fWord = it->first;
			if (fWord.length() > 1)
			{
				for (int i = 0; i < fWord.length(); i++)
				{
					std::string s(1, fWord[i]);
					if (s == ltInter) //if the word contains the letter we will intersect...
					{
						checkLetterInterShow = true;
						break;
					}
				}
				if (checkLetterInterShow == true)
				{
					if (isGoodWord(fWord, npcHand)) //check word with hand
					{
						botVec.push_back(fWord);
					}
					checkLetterInterShow = false;
				}
			}
			it++;
		}
		if (botVec.size() == 0)
		{
			botVec.push_back("pass"); //if the bot can't find words, passes...
		}
		else
		{
			randSelect = rand() % botVec.size(); // chooses a random word for the bot to play
			return botVec[randSelect];
		}
	}

	void insertBotWordInBoard(std::string word)
	{
		int canInsert = 0;
		int score = 0;
		std::string newbWord;
		std::string comp;
		int x = myTile.getCoordenateX();
		int y = myTile.getCoordenateY();
		std::string letter = boardArray[y - 1][x - 1].getBonus();
		int indexInter = 0; //indice of word that intersect

		letter.erase(std::remove_if(letter.begin(), letter.end(), isspace), letter.end()); //remove white spaces from string
		std::transform(letter.begin(), letter.end(), letter.begin(), ::tolower); //converts string to lower case
		comp = letter[0];
		for (int j = 0; j < word.length(); j++)
		{
			std::string s(1, word[j]);
			if (s == comp) //if there is a match on word and letter to intersect
			{
				indexInter = j; //return the positions at which the word must be played in order to intersect it
				break;
			}
		}
		if (this->botDir == "v")
		{
			if (word.length() + y > 16 || y - word.length() < 1) //if word goes out of range
			{
				std::cout << "Word is too big... Trying another one." << std::endl;
				auto itr = std::find(botVec.begin(), botVec.end(), word);
				if (itr != botVec.end())
				{
					botVec.erase(itr);
					newbWord = botWord(npcHand); //grabs a random word
					std::cout << "New word to try: " << newbWord << std::endl;
					insertBotWordInBoard(newbWord); //tries to insert this new word
				}
				else
				{
					std::cout << word << " couldn't be removed from the dictionary!" << std::endl;
				}
			}
			else
			{
				for (unsigned int i = 0; i < word.length(); i++)
				{
					bool checkEmptiness = boardArray[y - indexInter - 1][x - 1].getOccupation();
					if (checkEmptiness == false)
					{
						canInsert++;
					}
					y++;
				}
				if (canInsert == word.size() - 1) //if the word is big enough to NOT intersect another word
				{
					y = myTile.getCoordenateY();
					for (unsigned int i = 0; i < word.length(); i++)
					{
						//writes word and all properties
						std::string s(1, toupper(word[i]));
						boardArray[y - indexInter - 1][x - 1].setBonus(' ' + s + ' ');
						boardArray[y - indexInter - 1][x - 1].setLetter(' ' + s + ' ');
						boardArray[y - indexInter - 1][x - 1].setOccupation(true);
						y++;
					}
					score = getWordFinalScore(word, myTile.getDirection(), myTile.getCoordenateY(), myTile.getCoordenateX());
				}
				else
				{
					canInsert = 0;
					y = myTile.getCoordenateY();
					auto itr = std::find(botVec.begin(), botVec.end(), word);
					if (itr != botVec.end())
					{
						botVec.erase(itr); //remove that word from the vector since we have checked its usability
						newbWord = botWord(npcHand); //grabs a random word
						std::cout << "New word to try: " << newbWord << std::endl;
						insertBotWordInBoard(newbWord); //tries to insert this new word
					}
				}
			}
		}
		else //in "h"
		{
			if (word.length() + x > 16 || x - word.length() < 1) //if word goes out of range
			{
				std::cout << "Word is too big... Trying another one." << std::endl;
				auto itr = std::find(botVec.begin(), botVec.end(), word);
				if (itr != botVec.end())
				{
					botVec.erase(itr);
					newbWord = botWord(npcHand); //grabs a random word
					std::cout << "New word to try: " << newbWord << std::endl;
					insertBotWordInBoard(newbWord); //tries to insert this new word
				}
				else
				{
					std::cout << word << " couldn't be removed from the dictionary!" << std::endl;
				}
			}
			else
			{
				for (unsigned int i = 0; i < word.length(); i++)
				{
					bool checkEmptiness = boardArray[y - 1][x - indexInter - 1].getOccupation();
					if (checkEmptiness == false)
					{
						canInsert++;
					}
					x++;
				}
				if (canInsert == word.size() - 1) //if the word is big enough to NOT intersect another word
				{
					y = myTile.getCoordenateY();
					for (unsigned int i = 0; i < word.length(); i++)
					{
						//writes word and all properties
						std::string s(1, toupper(word[i]));
						boardArray[y - 1][x - indexInter - 1].setBonus(' ' + s + ' ');
						boardArray[y - 1][x - indexInter - 1].setLetter(' ' + s + ' ');
						boardArray[y - 1][x - indexInter - 1].setOccupation(true);
						x++;
					}
					score = getWordFinalScore(word, myTile.getDirection(), myTile.getCoordenateY(), myTile.getCoordenateX());
				}
				else
				{
					canInsert = 0;
					x = myTile.getCoordenateX();
					auto itr = std::find(botVec.begin(), botVec.end(), word);
					if (itr != botVec.end())
					{
						botVec.erase(itr); //remove that word from the vector since we have checked its usability
						newbWord = botWord(npcHand); //grabs a random word
						std::cout << "New word to try: " << newbWord << std::endl;
						insertBotWordInBoard(newbWord); //tries to insert this new word
					}
				}
			}
		}
		myBot.setBotScore(score);
	}

	void theWinner()
	{
		if (botPassCounter > 1)
		{
			std::cout << "NPC has forfeited!" << std::endl;
		}
		else if (myBot.getBotScore() > myPlayer.getPlayerScore())
		{
			std::cout << "NPC WINS!" << std::endl;
		}
		else if (myBot.getBotScore() < myPlayer.getPlayerScore())
		{
			std::cout << "Player WINS!" << std::endl;
		}
		else if (myBot.getBotScore() == myPlayer.getPlayerScore())
		{
			std::cout << "IT'S A TIE" << std::endl;
		}
	}

	void printScores()
	{
		std::cout << "\nPlayer Score: " << myPlayer.getPlayerScore() << std::endl;
		std::cout << "NPC Score: " << myBot.getBotScore() << std::endl;
		std::cout << "-------------------------------------------------------------------------" << std::endl << std::endl;
	}
};

int main()
{
	Game myGame;
	Tile myTile;
	Bot myBot;
	Player myPlayer;
	myGame.gameRules();
	myGame.makeBoard();
	//myGame.drawBoard();

	srand(time(NULL));

	std::ifstream wordsFile("scrabble_words.txt");

	std::vector<std::string> nHand;
	std::string bWord;
	std::string bDir;

	if (wordsFile.is_open())
	{
		std::string input;
		myGame.parseFile(wordsFile, input);
		while (myGame.getLetterPool().size() > 1)
		{
			myGame.drawBoard();
			myGame.printScores();
			if (myGame.round_counter % 2 == 0) // player round
			{
				std::cout << "Round Number: " << myGame.round_counter + 1 << std::endl << std::endl;
				myGame.giveHand();
				myGame.checkPlayerWord();
				std::cout << std::endl;
			}
			else // bot round
			{
				std::cout << "Round Number: " << myGame.round_counter + 1 << std::endl << std::endl;
				myGame.giveHand(); //set a hand to the npc
				nHand = myGame.returnBotHand();
				bWord = myGame.botWord(nHand);
				myGame.setBotDir("v");
				std::cout << "Word to play: " << bWord << std::endl;
				myGame.insertBotWordInBoard(bWord);
				myGame.round_counter++;
				if (myGame.botPassCounter > 1)
				{
					break;
				}
			}
		}
		std::cout << "\nGAME OVER!" << std::endl;
		myGame.theWinner();
	}

	else
	{
		std::cout << "File has NOT been opened.\n\n";
	}

	return 0;
}

//Easy Bot:
//- Plays on vertical
//- Searches for all possible words and play a random one
//- Only plays on the coordinates of the first letters of last played word by the player
//- Hand does not refresh