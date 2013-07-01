//Driver.cpp

/**************************************************************
*	Author:			Andy Giese
*	Dates Modified:  
*	June 30, 2013:
*		Cleaning up a little bit before pushing to GitHub
*		
*	February 17, 2008 (ensured no duplicates in sorted list)
*   Declared Code-complete November 11th 2007
*	The purpose of this project is to implement a game of Hangman
*	Features: Play single player
		      Play against a partner
			  View leaderboards
			  Be added to the leaderboards
			  Add a new category and/or word
*	Types of things being practiced:
		Parsing strings for proper input
		Parsing strings for numbers
		Using and modifying files
		Using linked sorted/unsorted lists
		Using linked sorted/unsorted lists that are templated
		Using linked sorted/unsorted lists containing other linked lists
		Creating ADTs
		Clean navigation between game modes
		Random drawing
		Preventing same item to be drawn randomly twice
		User generated content
**************************************************************/

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
#include "Leaderboard.h"
#include "Name.h"
#include "UnsortedList.h"
#include "SortedList.h"

bool Load();
//pre: none
//post: loads data, returns true if successful, false if not

string GenerateGuessWord (string _theWord);
//pre: _theWord is not an empty string
//post: generates the underscored word that lacks characters a user will see

double ParseInt (string _toBeParsed);
//pre: string _toBeParsed is at least 1 value long and contains only numbers
//post: returns an integer with value equivalent to the numbers in the string
//Note: this is a good example of my unfamiliarity with the atoi() command in 2007

bool ReturnResults(char _letter, string& _currentWord, string _theAnswer);
//pre: currentWord contains underscores in places user has not uncovered
//post: currentWord is changed to reveal letters, returns true if any are changed
//      else returns false (user made a wrong guess)

void ProcessChoice(string _theChoice, bool& _userContinues);
//pre: none
//post: depending on user input, action is taken

string ToLowerCase(string &beCleaned);
//pre: none
//post: makes a word completely lower case

void ViewLeaders();
//pre: none
//post: view current leaderboards

void ShowMenu();
//pre: none
//post: displays the menu for user to read

string GenerateRandomWord(string& _categoryName);
//pre: master category list is not empty
//post: returns a random word from a random category, categoryName is the name
//		of the category it is from

void PlayGame();
//pre: words and categories have been loaded
//post: allows user to play versus the PC in Hangman

void PlayVersus();
//pre: none
//post: allows two users to play, one enters word and the other tries to guess it

void AddToLeaderboard(int points, int wordCount);
//pre: none
//post: attempts to add a new Name to leaderboard

void AddWord();
//pre: none
//post: attempts to allow user to add a new word or category to database

//declare global variables
#define MAX_MISSES 6
UnsortedType< SortedType<string> > categoryList;
string hangmanPics [MAX_MISSES+1];
int totalWords;
int numWordsPicked = 0;
Leaderboard theBoard;

int main()
{
	//declare variables
	string userChoice;
	bool userContinues = true;
	string currentWord;
	
	//seed random number generator
	srand( (int)time(0) );

	//load data
	if (!Load())
	{
		cout << "Error loading necessary files" << endl;
		cout << "Exiting game..." << endl;
		system("pause");
		return 1;
	}
	//system("pause");
	
	
	
	//process
	do{
		ShowMenu();
		while (isspace(cin.peek()))
			cin.ignore();
		getline(cin,userChoice);
		ProcessChoice(userChoice, userContinues);

	}while (userContinues);


	system("pause");
	return 0;
}// end of main method

void ProcessChoice(string theChoice, bool &continues)
{
	//run whichever option user selected
	//1: Play Game
	//2: Play Versus
	//3: View Leaderboards
	//4: Add new word
	//5: Quit
	char choice = theChoice[0];

	if (choice == '1')
	{

		PlayGame();
		system("pause");
		return;
		
	}
	else if (choice == '2')
	{

		PlayVersus();
		system("pause");
		return;
	}

	else if (choice == '3')
	{
		ViewLeaders();
		return;
	}
	else if (choice == '4')
	{
		AddWord();
		system("pause");
		return;
	}
	else if (choice == '5')
	{
		//cout << "\nFeature not yet implemented" << endl << endl;
		cout << "------------------" << endl;
		cout << "Tips for Hangman: " << endl;
		cout << "\n----------\n" << endl;
		cout << "You need to guess a word one letter at a time" << endl;
		cout << "\n----------\n" << endl;
		cout << "Simply type your m_next guess and press ENTER at the prompt" << endl;
		cout << "\n----------\n" << endl;
		cout << "Guesses can be letters OR numbers, although numbers are EXTREMELY rare" << endl;
		cout << "\n----------\n" << endl;
		cout << "Type ! as your m_next guess if you wish to quit" << endl;
		cout << "\n----------\n" << endl;
		cout << "After every 5 words guessed correctly, you are awarded a new life" << endl;
		cout << "\n----------\n" << endl;
		cout << "You have 3 lives to begin with. Each word will allow you 5 misses, and you lose on the 6th" << endl;
		cout << "\n----------\n" << endl;
		cout << "Every time you guess incorrectly, you lose a miss. Lose all your misses and you lose a life" << endl;
		cout << "\n----------\n" << endl;
		cout << "Points are awarded after a word is completed based on number of misses" << endl;
		cout << "\n----------\n" << endl;
		cout << "Good Luck!" << endl;
		system("pause");
		return;
	}

	else if (choice == '6'){
		cout << "\nThanks for playing!" << endl;
		continues = false;
		return;
	}

	else{
		cout << "\nInvalid choice" << endl;
		system("pause");
		return;
	}
}//end ProcessChoice

void ViewLeaders()
{
	system("cls");
	ifstream fin;
	fin.open("leaderboards.txt");
	if (fin.fail())
	{
		cout << "Error. Leaderboards unavailable" << endl;
		system("pause");
		return;
	}
	
	//simply print each character in the file, no need to do anything more
	string printNext;
	cout << "Current Leaders:  " << endl;
	getline(fin,printNext,'\n');
	cout << printNext << endl;
	while(!fin.fail())
	{
		
		getline(fin,printNext);
		cout << printNext << endl;
	}// end of while loop

	fin.close();
	cout << "Press Enter to return to the main menu" << endl;
	system("pause");
	return;
}

void ShowMenu(){
	system("cls");
	ifstream fin;
	fin.open("hangmanLogo.txt");
	if (fin.fail())
			cout << "H A N G M A N" << endl;
	else
	{
		string logo;
		getline(fin, logo, '\n');
		cout << logo << endl;
		while (!fin.fail())
		{
			getline(fin,logo,'\n');
			cout << logo << endl;
		}// end of while loop

		fin.close();
		fin.clear();
		fin.open("HangmanLogo2.txt");
		if (fin.fail())
			cout << "Don't get killed!" << endl;
		else
		{
			getline(fin, logo, '\n');
			while (!fin.fail())
			{
				cout << logo << endl;
				getline(fin,logo,'\n');
			}//end of while loop
		}//end of -else conditional
		fin.close();

	}//end of -else conditional

	cout << "Menu:" << endl;
	cout << "1: Play Game" << endl;
	cout << "2: Play vs Human" << endl;
	cout << "3: View Leaderboards" << endl;
	cout << "4: Add New Word" << endl;
	cout << "5: Help/How to Play" << endl;
	cout << "6: Quit" << endl;
	cout << "You pick: ";
}//end of showMenu


//we want to generate the underscored (_) blank word that the user is trying to guess
//it needs to be of the same length as the word, but with underscores instead of letters
//example, if word is "hangman", we want the user to initially see "_ _ _ _ _ _ _"

string GenerateGuessWord(string _theWord){

	//start with an empty string
	string currentWord = "";

	//simply step through the word, adding underscores to the new word for every spot
	for (size_t i=0; i<_theWord.length();i++){
		if (!isalnum(_theWord[i]))
			currentWord += _theWord[i];
		else
			currentWord += '_';
	}

	//return the new word to be displayed to user
	return currentWord;
}

bool ReturnResults(char _letter, string& _currentWord, string _theAnswer)
{
	int numCharsChanged = 0;
	string tempWord = "";
	char tempChar;

	for (size_t i=0; i<_theAnswer.length();i++)
		{
			tempChar = _currentWord[i];
			if (_theAnswer[i] == _letter)
			{
				tempChar = _theAnswer[i];
				numCharsChanged++;
			}
			tempWord += tempChar;
		}
	_currentWord = tempWord;

	if (numCharsChanged > 0)
		return true;
	return false;
}

string GenerateRandomWord(string &categoryName){
	//reset master category list
	//get a random category
	//reset category list
	//get a random word
	//set category name to category list name
	//return random word
	
	categoryList.ResetList();

	SortedType<string> tempCategory;
	int randomNum;
	
	if (categoryList.LengthIs() == 0){
		cout << "Could not call random due to a division by 0 error" << endl;
		return "Default";
	}
	randomNum = (rand() % (categoryList.LengthIs()));
	
	for (int i = -1; (i < randomNum); i++){
		categoryList.GetNextItem(tempCategory);
	}

	tempCategory.ResetList();
	string tempWord;
	if (tempCategory.LengthIs() == 0){
		cout << "Could not call random due to a division by 0 error" << endl;
		return "Default";
	}
	
	categoryName = tempCategory.getName();

	randomNum = rand() % tempCategory.LengthIs();

	for (int i = -1; (i < randomNum); i++){
		tempCategory.GetNextItem(tempWord);
	}

	return tempWord;

}//end of function

bool Load(){
	//declare filestream
	ifstream fin;

	//load category names
	//open file
	fin.open("categoryNames.txt");
	string categoryName;
	while (isspace(fin.peek()))
			fin.ignore();

	//get first category name
	getline(fin,categoryName);
	while (!fin.fail()){
		//create a new category
		SortedType<string>* newCategory = new SortedType<string>;

		//set category name
		newCategory->setName(categoryName);

		//put new category into master category list
		categoryList.InsertItem(*newCategory);
		
		//get m_next category name
		while (isspace(fin.peek()))
			fin.ignore();
		getline(fin,categoryName);
		delete newCategory;
	}
	cout << "Categories loaded" << endl;

	//load words in categories
	//close original file stream
	fin.close();
	fin.clear();
	SortedType<string> nextCat;
	string nextCatFileName;

	//reset master category list for traversing
	categoryList.ResetList();
	
	
	//get first category name, open its file
	while(categoryList.GetNextItem(nextCat)){
		nextCatFileName = nextCat.getName() + ".txt";
		fin.open(nextCatFileName.c_str());
		if (fin.fail()){
			cout << "Opening file failed" << endl;
			system("pause");
			return false;
		}

		//grab words from the file and insert them into category
		string nextWord;
		while (isspace(fin.peek()))
			fin.ignore();
		getline(fin,nextWord);
		
		
		while(!fin.fail())
		{
			nextCat.InsertItem(nextWord);
			totalWords++;
			//cout << nextWord << endl;
			while (isspace(fin.peek()))
			fin.ignore();
			getline(fin,nextWord);
		}

		//since nextCat is only a copy of a node in category list, we need to re-insert it
		// do this by calling the updateItem function
		categoryList.updateItem(nextCat);
		
		nextCat.MakeEmpty();
		fin.close();
		fin.clear();
	}
	cout << "Words loaded" << endl;
	fin.close();
	fin.clear();

	//load hangman pictures
	fin.open("hangmanPics.txt");
	if (fin.fail()){
		cout << "Error opening hangmanPics.txt" << endl;
		return false;
	}

	//load first image
	int j = 0; //index for the hangmanPics array
	string nextPic;
	getline(fin,nextPic,'`');
	while(!fin.fail()){
		hangmanPics[j] = nextPic;
		j++;

		getline(fin,nextPic,'`');
	}//end of while loop
	fin.close();
	fin.clear();

	//June 2013: Magic number 5 here???
	if (j < 5){
		cout << "Not enough hangmanpictures loaded" << endl;
		return false;
	}

	cout << "hangman pictures loaded" << endl;

	//load high scores
	fin.open("leaderboards.txt");
	if (fin.fail())
	{
		cout << "Failed to load leaderboards" << endl;
		return true;
	}
	string deleteLine;
	while (isspace(fin.peek()))
		fin.ignore();
	getline(fin,deleteLine);

	while(isspace(fin.peek()))
		fin.ignore();
	getline(fin,deleteLine);
	fin >> theBoard;

	//close filestream
	fin.close();
	fin.clear();
	cout << "Leaderboards loaded" << endl;

	return true;
}//end of load function

	//there is an array of hangman pictures (of type string), with 6 being index with no misses and 0 
//being index with 6 misses lets call it hangmanPics;


//display category, current hangman status, misses left, words guessed, and word
		//prompt for m_next guess, validate it
		//process m_next guess
			// miss = subtract a miss and advance hangman status
			// correct = reveal letter in its spots on word
				//if word is complete, m_numWords++, increment score, and reset misses
					//check if m_numWords % 5 = 0
						//give life if true
					//generate m_next word
			//if misses left = 0, subtract life
			//if lives = 0, end this game session
			// else generate m_next word, reset misses

void PlayGame()
{
	//initialize variables
	
	int lives, m_numWords, points, misses;
	SortedType<string> usedWords;
	lives = 3;
	m_numWords = 0;
	points = 0;
	misses = MAX_MISSES;
	char *lettersGuessed = new char [36]; //June 2013: another magic number?
	int size = 0;
	char nextGuess;
	string parseGuess;
	string category_Name;
	string currentWord = GenerateRandomWord(category_Name);
	usedWords.InsertItem(currentWord);
	string guessWord = GenerateGuessWord(currentWord);
	bool invalidGuess, isCorrect = false;

	while (lives > 0){
		system("cls");
		invalidGuess = true;

		cout << "Lives: " << lives << "\t\tMisses left: " << misses << endl;
		cout << "Words completed: " << m_numWords << "\t\tScore: " << points << endl;
		cout << "\n\n" << hangmanPics[misses] << endl << endl;

		if (isCorrect)
			cout << "\nNice Guess!" << endl;
		cout << "Category: " << category_Name << endl << endl;

		//display the word to the user
		for (size_t i=0; i < guessWord.size();i++)
		{
			//place a space after each letter so the word is easy to read by users
			cout << guessWord[i] << ' ';
		}//end for loop

		//example, if word is hangman, currentword is _a__a_, current word will be displayed as
		// _ a _ _ _ a _  which is easier to read and falls in line with traditional hangman
		//cout << "\nAnswer: " << currentWord << endl;
		cout << "\n\nCharacters guessed: " << endl;
		
		for (int i=0; i<size; i++){
			cout << lettersGuessed[i] << ", ";
		}//end for loop
		cout << endl << "Next guess (Type '!' to Quit): " << endl;
		while (isspace(cin.peek())){
			cin.ignore();
		}//end while loop
		getline(cin,parseGuess);
		nextGuess = parseGuess[0];
		nextGuess = tolower(nextGuess);

		//check if user wants to quit
		while (nextGuess == '!')
		{
			cout << "Quit to main menu? (Y/N)" << endl;
			char userQuits;
			while (isspace(cin.peek()))
			{
				cin.ignore();
			}//end nested while loop
			getline(cin,parseGuess);
			userQuits = parseGuess[0];
			userQuits = toupper(userQuits);
			if (userQuits == 'Y')
			{
				AddToLeaderboard(points, m_numWords);
				return;
			}
			cout << endl << "Next guess (Type '!' to Quit): " << endl;
			while (isspace(cin.peek()))
			{
				cin.ignore();
			}//end nested while loop
			getline(cin,parseGuess);
			nextGuess = parseGuess[0];
			nextGuess = tolower(nextGuess);
		}

		//display guess
		cout << "You guessed: " << nextGuess << endl;

		//this index variable will be important for determing whether
		//we are just entering the loop for the first time (in which case we shouldn't assume
		//an invalid guess)
		// or if they are returning to it from inside (in which case there is a definite invalid
		// guess

		int index = 0;
		while (invalidGuess)
		{
			if (index != 0)
			{
				cout << "Invalid guess" << endl;
				cout << "Next guess (Type '!' to Quit): " << endl;
				while (isspace(cin.peek()))
				{
					cin.ignore();
				}//end nested while loop
				getline(cin,parseGuess);
				nextGuess = parseGuess[0];
				nextGuess = tolower(nextGuess);

				//check if user wants to quit
				while (nextGuess == '!')
				{
					cout << "Quit to main menu? (Y/N)" << endl;
					char userQuits;
					while (isspace(cin.peek()))
					{
						cin.ignore();
					}//end nested while loop
					getline(cin,parseGuess);
					userQuits = parseGuess[0];
					userQuits = toupper(userQuits);
					if (userQuits == 'Y')
					{
						AddToLeaderboard(points, m_numWords);
						return;
					}
					cout << "Next guess (Type '!' to Quit): " << endl;
					while (isspace(cin.peek()))
					{
						cin.ignore();
					}//end nested while loop
					getline(cin,parseGuess);
					nextGuess = parseGuess[0];
					nextGuess = tolower(nextGuess);

				}//end while loop
			}//end -if conditional

			while (!isalnum(nextGuess))
			{
				cout << "Invalid guess" << endl;
				cout << "Next guess (Type '!' to Quit): " << endl;
				while (isspace(cin.peek()))
				{
					cin.ignore();
				}//end nested while loop

				getline(cin,parseGuess);
				nextGuess = parseGuess[0];
				nextGuess = tolower(nextGuess);

				//check if user wants to quit
				while (nextGuess == '!')
				{
					cout << "Quit to main menu? (Y/N)" << endl;
					char userQuits;
					while (isspace(cin.peek()))
					{
						cin.ignore();
					}
					getline(cin,parseGuess);
					userQuits = parseGuess[0];
					userQuits = toupper(userQuits);
					if (userQuits == 'Y')
					{
						AddToLeaderboard(points, m_numWords);
						return;
					}
					cout << "Next guess (Type '!' to Quit): " << endl;
					while (isspace(cin.peek()))
					{
						cin.ignore();
					}//end nested while loop
					getline(cin,parseGuess);
					nextGuess = parseGuess[0];
					nextGuess = tolower(nextGuess);
				}//end nested while loop
			}//end while loop

			//ensure guess has not been made before
			
			//reset index
			index = 0;
			while(index < size && nextGuess != tolower(lettersGuessed[index]))
			{
				index++;
			}
			if (index == size)
			{
				invalidGuess = false;
			}
			else
			{
				invalidGuess = true;
				index = 1;
			}
			
		}//end of while loop
		
		//valid guess has been made, add guess to letters guessed
		lettersGuessed[size] = toupper(nextGuess);
		size++;

	//process the valid guess
		//invoke a function that decides if guess is a hit or miss, returns true if hit
		isCorrect = ReturnResults(nextGuess,guessWord,currentWord);
		//set isCorrect to the return of that function
		if (isCorrect == false)
		{
			cout << "\nWrong!" << endl << endl;
			misses--;
			system("pause");
			
		}
		else{
			cout << "Nice Guess!" << endl;
			for (size_t i=0; i < guessWord.size();i++){
				//place a space after each letter so the word is easy to read by users
				cout << guessWord[i] << ' ';
			}
			cout << endl;

		}
		//check to see if word is complete
		if (currentWord == guessWord){
			m_numWords++;
			//increment score

			switch(misses)
			{
			case 6: 
				{
					points += 1000;
				}
				break;
			case 5: 
				{
					points += 900;
				}
				break;
			case 4: 
				{
					points += 750;
				}
				break;
			case 3: 
				{
					points += 600;
				}
				break;
			case 2: 
				{
					points += 500;
				}
				break;
			case 1: 
				{
					points += 300;
				}
				break;
			default: points += 69;
			}//end switch statement

			currentWord = GenerateRandomWord(category_Name);

			//do not grab a word if it has been used before
			int counter = 0;
			while(usedWords.RetrieveItem(currentWord)){
				if (counter == totalWords){
					cout << "Congratulations! You've played through every single word!" << endl;
					cout << "Returning to main menu" << endl;
					AddToLeaderboard(points, m_numWords);
					system("pause");
					return;
				}
				currentWord = GenerateRandomWord(category_Name);
				counter++;
			}
			usedWords.InsertItem(currentWord);
			guessWord = GenerateGuessWord(currentWord);
			misses = MAX_MISSES;
			if (m_numWords % 5 == 0 && m_numWords != 0){
				lives++;
				cout << "\nYou gained a life!" << endl;
			}//end -if conditional
			
			//reset wordsGuessed
			delete [] lettersGuessed;
			lettersGuessed = new char[36];
			size = 0;

			cout << "You finished the word!" << endl;
			system("pause");
			
		}//end -if conditional

		if (misses == 0){
			//decrement lives, generate new word, reset guessed words
			lives--;
			system("cls");
			cout << "The Answer was: " << currentWord << endl;
			currentWord = GenerateRandomWord(category_Name);

			//do not grab a word if it has been used before
			int counter = 0;
			while(usedWords.RetrieveItem(currentWord)){
				if (counter == totalWords){
					cout << "Congratulations! You've played through every single word!" << endl;
					AddToLeaderboard(points, m_numWords);
					cout << "Returning to main menu" << endl;
					system("pause");
					return;
				}
				currentWord = GenerateRandomWord(category_Name);
				counter++;
			}
			usedWords.InsertItem(currentWord);
			guessWord = GenerateGuessWord(currentWord);
			delete [] lettersGuessed;
			lettersGuessed = new char[36];
			size = 0;
			//reset misses
			misses = MAX_MISSES;

			cout << "You lose a life!" << endl;
			system("pause");
		}
		if (lives == 0){
			//end game session
			cout << "Game over" << endl;
			AddToLeaderboard(points,m_numWords);
		}
		// miss = subtract a miss
		// correct = reveal letter in its spots on word
			//if word is complete, m_numWords++, increment score, generate nextWordand reset misses
				//check if m_numWords % 5 = 0
					//give life if true
					//generate m_next word
		//if misses left = 0, subtract life, reset misses,
		//if lives = 0, end this game session
		// else generate m_next word, reset misses			
		
	}//end of while loop

	return;
}//end of PlayGame()

void PlayVersus(){
	system ("cls");
		//initialize variables
	cout << "\n\tWELCOME TO VERSUS PLAY!" << endl << endl;
	
	int lives, misses;
	lives = 1;
	misses = MAX_MISSES;
	char *lettersGuessed = new char [36];
	int size = 0;
	char nextGuess;
	char userQuits = 'N';
	string parseGuess;
	string currentWord;
	string category_Name;

	//prompt user for word and category
	while (userQuits != 'Y'){
		cout << "Player ONE, please enter a CATEGORY for your word" << endl;
		while (isspace(cin.peek()))
			cin.ignore();
		getline(cin,category_Name);
		cout << endl << category_Name << endl;
		cout << "...Is this right? (Y/N) "<< endl;
		while (isspace(cin.peek()))
			cin.ignore();
		getline(cin,parseGuess);
		userQuits = parseGuess[0];
		userQuits = toupper(userQuits);
	}//end while loop

	//reset userQuits for m_next prompt
	userQuits = 'N';

	while (userQuits != 'Y'){
		cout << "Player ONE, please enter a WORD or PHRASE for Player TWO to guess" << endl;
		while (isspace(cin.peek()))
			cin.ignore();
		getline(cin,currentWord);
		ToLowerCase(currentWord);
		cout << endl << currentWord << endl;
		cout << "...Is this right? (Y/N) "<< endl;
		while (isspace(cin.peek()))
			cin.ignore();
		getline(cin,parseGuess);
		userQuits = parseGuess[0];
		userQuits = toupper(userQuits);
	}//end while loop
	string guessWord = GenerateGuessWord(currentWord);

	bool invalidGuess, isCorrect = false;
	while (lives > 0){
		system("cls");
		invalidGuess = true;

		cout << "Lives: " << lives << "\t\tMisses left: " << misses << endl;
		cout << "\n\n" << hangmanPics[misses] << endl << endl;

		if (isCorrect)
			cout << "\nNice Guess!" << endl;
		cout << "Category: " << category_Name << endl << endl;

		//display the word to the user
		for (size_t i=0; i < guessWord.size();i++){
			//place a space after each letter so the word is easy to read by users
			cout << guessWord[i] << ' ';
		}//end for loop

		//example, if word is hangman, currentword is _a__a_, current word will be displayed as
		// _ a _ _ _ a _  which is easier to read and falls in line with traditional hangman
		//cout << "\nAnswer: " << currentWord << endl;
		cout << "\n\nCharacters guessed: " << endl;
		
		for (int i=0; i<size; i++){
			cout << lettersGuessed[i] << ", ";
			//if (i % 9 == 0)
				//cout << endl;
		}//end for loop
		cout << endl << "Next guess: " << endl;
		while (isspace(cin.peek())){
			cin.ignore();
		}//end while loop
		getline(cin,parseGuess);
		nextGuess = parseGuess[0];
		nextGuess = tolower(nextGuess);

		//check if user wants to quit
		while (nextGuess == '!'){
			cout << "Quit to main menu? (Y/N)" << endl;
			char userQuits;
			while (isspace(cin.peek())){
				cin.ignore();
			}//end nested while loop
			getline(cin,parseGuess);
			userQuits = parseGuess[0];
			userQuits = toupper(userQuits);
			if (userQuits == 'Y')
					return;
			cout << endl << "Next guess: " << endl;
			while (isspace(cin.peek())){
				cin.ignore();
			}//end nested while loop
			getline(cin,parseGuess);
			nextGuess = parseGuess[0];
			nextGuess = tolower(nextGuess);

		}

		//display guess
		cout << "You guessed: " << nextGuess << endl;

		//this index variable will be important for determing whether
		//we are just entering the loop for the first time (in which case we shouldn't assume
		//an invalid guess)
		// or if they are returning to it from inside (in which case there is a definite invalid
		// guess

		int index = 0;
		while (invalidGuess){
			if (index != 0){
				cout << "Invalid guess" << endl;
				cout << "Next guess: " << endl;
				while (isspace(cin.peek())){
					cin.ignore();
				}//end nested while loop
				getline(cin,parseGuess);
				nextGuess = parseGuess[0];
				nextGuess = tolower(nextGuess);

				//check if user wants to quit
				while (nextGuess == '!'){
					cout << "Quit to main menu? (Y/N)" << endl;
					char userQuits;
					while (isspace(cin.peek())){
						cin.ignore();
					}//end nested while loop
					getline(cin,parseGuess);
					userQuits = parseGuess[0];
					userQuits = toupper(userQuits);
					if (userQuits == 'Y')
							return;
					cout << "Next guess: " << endl;
					while (isspace(cin.peek())){
						cin.ignore();
					}//end nested while loop
					getline(cin,parseGuess);
					nextGuess = parseGuess[0];
					nextGuess = tolower(nextGuess);

				}//end while loop
			}//end -if conditional

			while (!isalnum(nextGuess)){
				cout << "Invalid guess" << endl;
				cout << "Next guess: " << endl;
				while (isspace(cin.peek())){
					cin.ignore();
				}//end nested while loop

				getline(cin,parseGuess);
				nextGuess = parseGuess[0];
				nextGuess = tolower(nextGuess);

				//check if user wants to quit
				while (nextGuess == '!'){
					cout << "Quit to main menu? (Y/N)" << endl;
					char userQuits;
					while (isspace(cin.peek())){
						cin.ignore();
					}
					getline(cin,parseGuess);
					userQuits = parseGuess[0];
					userQuits = toupper(userQuits);
					if (userQuits == 'Y')
						return;
					cout << "Next guess: " << endl;
					while (isspace(cin.peek())){
						cin.ignore();
					}//end nested while loop
					getline(cin,parseGuess);
					nextGuess = parseGuess[0];
					nextGuess = tolower(nextGuess);
				}//end nested while loop
			}//end while loop

			//ensure guess has not been made before
			
			//reset index
			index = 0;
			while(index < size && nextGuess != tolower(lettersGuessed[index])){
				index++;
			}
			if (index == size){
				invalidGuess = false;
			}
			else{
				invalidGuess = true;
				index = 1;
			}
			
		}//end of while loop
		
		//valid guess has been made, add guess to letters guessed
		lettersGuessed[size] = toupper(nextGuess);
		size++;

		//process the valid guess
		//invoke a function that decides if guess is a hit or miss, returns true if hit
		isCorrect = ReturnResults(nextGuess,guessWord,currentWord);
		//set isCorrect to the return of that function
		if (isCorrect == false){
			cout << "\nWrong!" << endl << endl;
			misses--;
			system("pause");
			
		}
		else{
			cout << "Nice Guess!" << endl;
			for (size_t i=0; i < guessWord.size();i++)
			{
				//place a space after each letter so the word is easy to read by users
				cout << guessWord[i] << ' ';
			}
			cout << endl;

		}
		//check to see if word is complete
		if (currentWord == guessWord){
			//Player TWO wins

			//reallocate lettersGuessed
			delete [] lettersGuessed;
			size = 0;

			cout << "Player TWO wins!" << endl;
			system("pause");
			return;
			
		}//end -if conditional

		if (misses == 0){
			//player one wins!

			//decrement lives, generate new word, reset guessed words
			lives--;
			delete [] lettersGuessed;
			size = 0;

			system("cls");
			cout << "Player ONE Wins!" << endl;
			cout << "\nThe correct answer was " << currentWord << endl << endl;
			system("pause");
			return;
		}
		if (lives == 0){
			//end game session
			cout << "Play again soon!" << endl;
			system("pause");
			return;
		}
		// miss = subtract a miss
		// correct = reveal letter in its spots on word
			//if word is complete, m_numWords++, increment score, generate nextWordand reset misses
				//check if m_numWords % 5 = 0
					//give life if true
					//generate m_next word
		//if misses left = 0, subtract life, reset misses,
		//if lives = 0, end this game session
		// else generate m_next word, reset misses			
		
	}//end of while loop

	return;
}//end of PlayVersus


void AddToLeaderboard(int _points, int _wordCount){
	if (theBoard.IsHighScore(_points)){
		Name userName;
		cout << "Congratulations! You qualified for a high score!" << endl;
		cout << "What is your name? " << endl;
		cin >> userName.m_theName;

		userName.m_points = _points;
		userName.m_numWords = _wordCount;
		cout << "Thanks, " << userName.m_theName << endl;
		theBoard.Insert(userName);
		cout << "Name inserted" << endl;
		ofstream fout;
		fout.open("leaderboards.txt");
		if (fout.fail())
		{
			cout << "Error adding name to high scores" << endl;
			return;
		}
		fout << theBoard;
		cout << "Written to file" << endl;
		fout.close();
	}//end -if conditional
	return;

}//end of AddToLeaderboard


string ToLowerCase(string& _beCleaned){
	//declare variables
	char nextItem;
	int start;
	int length;

	start = 0;
	length = (int)_beCleaned.length();
	
	//parse the string of characters
	while (start < length){
		
		nextItem = _beCleaned[start];
		if (!isalpha(nextItem) && !isspace(nextItem)){
			//m_next character is not a letter or a space, so it is probably punctuation
			//let's delete that
			_beCleaned.erase(start,1);
			start--;
			length = (int)_beCleaned.length();
		}
		if (isalpha(nextItem)){
			//if it is a space of alphabetic character add it to temporary string to be checked
			//put the character to upper case
			_beCleaned[start] = tolower(nextItem);
		}

		//increment counter
		start++;
	}

	return _beCleaned;
}//end of toUpper function

void AddWord(){
	system("cls");

	string addWord;
	string parseWord;
	double parsedValue;
	char userChoice;
	SortedType<string> tempCat;
	//display a menu for user to add a new word
	//  under A) An existing category or B) Under a new category
	//  C) is to return
	do{
		cout << "Would you like to:" << endl;
		cout << "1) Add a new word under an existing category" << endl;
		cout << "2) Add a new word under a new category" << endl;
		cout << "3) Cancel" << endl;
		while(isspace(cin.peek()))
			cin.ignore();
		getline(cin,parseWord);
		userChoice = parseWord[0];
		if (userChoice != '1' && userChoice != '2' && userChoice != '3'){
			system("cls");
			cout << "Invalid Choice" << endl;
		}// end -if conditional

		//choice is valid, process it now
		//if choice is 1) display current categories and let user choose

		if (userChoice == '1'){
			int i = 0; // use this to move through parseWord
			bool invalidChoice = true; // use this for validating choice
			int index = 1;// use this to print current categories 

			system("cls");
			cout << "Here is a list of current categories:" << endl;
			categoryList.ResetList();
			SortedType<string> listPtr;
			while (categoryList.GetNextItem(listPtr)){
				cout << index << ") " << listPtr.getName() << endl;
				index++;
			}//end of nested while loop

			cout << "\n0) Return to previous menu." << endl;
			cout << "Select one: " << endl;
			while (isspace(cin.peek()))
				cin.ignore();
			getline(cin,parseWord);
		
			while (invalidChoice){
				//ensure all characters in string are digits
				while (i < (int)parseWord.length()){
					userChoice = parseWord[i];
					if (!isdigit(userChoice)){
						cout << "Invalid choice. Choose again." << endl;
						while (isspace(cin.peek()))
							cin.ignore();
						getline(cin,parseWord);
						i = -1;
					}// end -if conditional
					i++;
				}//end while loop

				//check for user wishing to quit
				if (parseWord[0] == '0')
					return;

				//ensure user has typed a value in appropriate range
				parsedValue = ParseInt(parseWord);
				if ( 0 <= parsedValue && parsedValue <= categoryList.LengthIs()){
					invalidChoice = false;
				}//end -if conditional
				else{
						cout << "Invalid choice. Choose again." << endl;
						while (isspace(cin.peek()))
							cin.ignore();
						getline(cin,parseWord);
						i = 0;

				}//end -else conditional
			}//end while loop
			categoryList.ResetList();
			
			for (int index = 0; index < parsedValue; index++){
				categoryList.GetNextItem(tempCat);
			}
			
			invalidChoice = true;
			while (invalidChoice){
				system("cls");
				cout << "You chose " << tempCat.getName() << endl;
				cout << "Type your word in, or enter '0' to exit" << endl;
				while (isspace(cin.peek()))
					cin.ignore();
				getline(cin,parseWord);
				if (parseWord[0] == '0')
					return;
				ToLowerCase(parseWord);
				addWord = parseWord;
				cout << "You entered " << parseWord << endl;
				cout << "Add to list? (Y/N)" << endl;
				while (isspace(cin.peek()))
					cin.ignore();
				getline(cin,parseWord);
				userChoice = parseWord[0];
				if (toupper(userChoice) == 'Y')
					invalidChoice = false;
			}
			if(!tempCat.InsertItem(addWord)){
				cout << "Failed to insert item" << endl;
				return;
			}
			categoryList.updateItem(tempCat);
			cout << "Word added to list" << endl;
			ofstream print;
			string outputFileName = tempCat.getName()+".txt";
			print.open(outputFileName.c_str());
			if (print.fail()){
				cout << "Error creating output file. Word will not be available on m_next run" << endl;
				return;
			}
			tempCat.PrintToFile(print);
			print.close();
			return;
	
			//*done*ensure user has selected a valid number (1-index)
			//  *done*allow them to type '0' if they want to go back
			//reset category list and use a for loop to step through it until proper category is
			// selected *done*
		    //prompt user for word to add to the list *done*
			// *done* 'clean word' and add word (in all lower case) to the list
			// *done*updateItem() in master category list 
			// *done*create a text file with same name as list
			// *done*output list to the file

		}//end -if conditional

		else if (userChoice == '2'){
			bool invalidChoice = true;
			SortedType <string> categoryNames;
			string addCategory;
			string addWord;
			system("cls");
			//cout << "This section not implemented yet" << endl;
			//return;
			system("cls");
			cout << "Here is a list of current categories:" << endl;
			categoryList.ResetList();
			SortedType<string> listPtr;
			while (categoryList.GetNextItem(listPtr)){
				cout << listPtr.getName() << endl;
				categoryNames.InsertItem(listPtr.getName());
			}//end of nested while loop

			while (invalidChoice){
				cout << "Input the name of the new category or type '0' to return" << endl;
				cout << "Category names need to be 2 letters or longer" << endl << endl;
				while (isspace(cin.peek()))
					cin.ignore();
				getline(cin,parseWord);
				if (parseWord[0] == '0')
					return;
				ToLowerCase(parseWord);
				if (parseWord.size() >= 2){
					char firstLetter = parseWord[0];
					firstLetter = toupper(firstLetter);
					addCategory = firstLetter + parseWord.substr(1,parseWord.length()-1);

					cout << "You entered " << addCategory << endl;
					cout << "Add to list? (Y/N)" << endl;
					while (isspace(cin.peek()))
						cin.ignore();
					getline(cin,parseWord);
					userChoice = parseWord[0];
					if (toupper(userChoice) == 'Y'){
						invalidChoice = false;
						if (!(categoryNames.InsertItem(addCategory))){
							cout << "Name already in list" << endl;
							invalidChoice = true;
							system("pause");
						}//end nested -if
					}//end nested -if
				}//end nested -if
				system("cls");
			}//end while loop
			SortedType<string> newCategory;
			newCategory.setName(addCategory);

			invalidChoice = true;
			while (invalidChoice){
				system("cls");
				cout << "Type your word in, or enter '0' to exit" << endl;
				while (isspace(cin.peek()))
					cin.ignore();
				getline(cin,parseWord);
				if (parseWord[0] == '0')
					return;
				ToLowerCase(parseWord);
				addWord = parseWord;
				cout << "You entered " << parseWord << endl;
				cout << "Add to list? (Y/N)" << endl;
				while (isspace(cin.peek()))
					cin.ignore();
				getline(cin,parseWord);
				userChoice = parseWord[0];
				if (toupper(userChoice) == 'Y')
					invalidChoice = false;
			}
			if(newCategory.InsertItem(addWord));
			else{
				cout << "Failed to insert item" << endl;
				return;
			}

			categoryList.InsertItem(newCategory);
			ofstream fout;
			string fileName = addCategory + ".txt";
			fout.open(fileName.c_str());
			if (fout.fail()){
				cout << "Opening of output file failed" << endl;
				return;
			}
			newCategory.PrintToFile(fout);
			fout.close();
			fout.clear();
			fileName = "CategoryNames.txt";
			fout.open(fileName.c_str());
			if (fout.fail()){
				cout << "Opening of output file failed" << endl;
				return;
			}
			string tempCatName;
			categoryNames.PrintToFile(fout);
			cout << "Word added successfully" << endl;
			fout.close();
			fout.clear();
			return;

			//*done*prompt them for a category name
			//*done*allow them to type '0' to go back
			//*done*check the name against current category names
			//*done*create a sorted list with name of category name
			//*done*prompt user for word to add to the list
			//*done*'clean word' and add word (in all lower case) to the list
			//*done*add list to master category list
			//*done*create a text file with same name as list
			// *done*output list to the file
			// *done*ouput all category names to text file named CategoryNames.txt

			
		}//end -if conditional
	} while (userChoice != '3'); // end of do-while loop

}//end of addWord()


double ParseInt (string _parseMe){
	double sum = 0;
	int multiple = _parseMe.length() - 1;
	double nextNum;
	for (size_t index=0; index < _parseMe.length(); index++){
   		char nextDigit = _parseMe[index];
   		switch (nextDigit){
			case '0': nextNum = 0;
			break;
			case '1': nextNum = 1;
			break;
			case '2': nextNum = 2;
			break;
			case '3': nextNum = 3;
			break;
			case '4': nextNum = 4;
			break;
			case '5': nextNum = 5;
			break;
			case '6': nextNum = 6;
			break;
			case '7': nextNum = 7;
			break;
			case '8': nextNum = 8;
			break;
			case '9': nextNum = 9;
			break;
   		 }//end switch statement
  	
		int j = multiple;
		while (j > 0){
			nextNum = nextNum * 10;
			j--;
		}//end while loop

		sum += nextNum;
		multiple--;
	}//end for loop

	return sum;
}//end of ParseInt method