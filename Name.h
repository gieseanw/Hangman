//Name.h
//defines name ADT for use in leaderboard
//Author: Andy Giese
//I'm declaring all data in this adt as public mostly because I don't want to re-write some code

#ifndef NAME_H
#define NAME_H

class Name{
public:
	Name():m_theName(""),m_points(0),m_numWords(0),m_next(NULL){}
	string m_theName;
	size_t m_points;
	size_t m_numWords;
	Name* m_next;
};
#endif