//Leaderboard.h

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "Name.h"
#include <vector>

#define MAX_NAMES 7

class Leaderboard
{
public:

	Leaderboard();
	//default constructor

	Leaderboard(const Leaderboard& leader);
	//copy constructor


	~Leaderboard();
	//destructor

	bool Insert(const Name& _newName);
	//pre: none
	//post: returns true if name was added to leaderboard, false if not

	bool Delete(Name _aName);
	//pre: none
	//post: returns true if aName was removed from leaderboard, false if not

	bool MakeEmpty();
	//pre: none
	//post: leaderboard is empty

	bool IsHighScore(size_t _newPoints) const;
	//pre: none
	//post: will check to see if points qualify as a high score, return true if yes, else false

	friend istream& operator >> (istream& _fin, Leaderboard& _leader);
	//pre: input file is open and ready for use. Leaderboard data is properly sorted
	//post: leader1 contains leaderboard data from fin

	friend ostream& operator << (ostream& _fout, const Leaderboard& _leader);
	//pre: output file is open and ready to use. Leaderboard data is sorted
	//post: data from leader1 is output to a file called leaderboards.txt


	private:
	size_t m_numNames;
	Name* m_info;

	bool InsertHelp(const Name& _newName, Name*& _t);
	//pre: newName is item to insert t is m_next node to check insertion
	//post: newName is inserted
};

#endif