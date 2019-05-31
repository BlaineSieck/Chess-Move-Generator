//Name = Blaine Sieck
//Lab501

#ifndef  PROJECT2
#define PROJECT2

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>

using namespace std;
typedef vector<string> row;
typedef vector<row> position;
typedef string square;
typedef char color;

struct mov {
	square src;
	square dst;
	// compare for order.     
	bool operator <(const mov& mv) const
	{

		return (src < mv.src) || ((!(mv.src < src)) && (dst < mv.dst));
	}
};

struct chessresult {
	bool checkmate;
	bool stalemate;
	set<mov> playermoves;
};

//_________________________________________________________________________
// Function declaration
position readPosition(string s);
//my helper function declarations:
vector<string> scanSquares(string s1);
vector<string> scanPieces(string s1);
int substringOccurences(const string &substring, const string &str);
position merge(vector<string> squares, vector<string> pieces, string s1);

//_________________________________________________________________________

set<mov> legalMoves(position P, color c);
chessresult check(position P, set<mov> playermoves, set<mov> playerkingmoves, string kingsource, bool chk, color c);
position update(position P, mov m, color c);
//for the functions below we assume the game is not in checkmate or stalemate
bool occupied(int rank, char file, position P, color c);
char identifypiecetype(int rank, char file, position P);
string identifypiece(int rank, char file, position P);
char identifycolor(int rank, char file, position P);
string createrankfile(int rank, char file);
set<mov> legalMovesBreakdown(int rank, char file, position P, color c);
set<mov> legalMovesKing(int rank, char file, position P, color c);
set<mov> kingScan (int rank, char file, position P, color c, mov move);
set<mov> legalMovesQueen(int rank, char file, position P, color c);
set<mov> queenScan (int rank, char file, position P, color c, mov move);
set<mov> legalMovesBishop(int rank, char file, position P, color c);
set<mov> bishopScan (int rank, char file, position P, color c, mov move);
set<mov> legalMovesRook(int rank, char file, position P, color c);
set<mov> rookScan (int rank, char file, position P, color c, mov move);
set<mov> legalMovesKnight(int rank, char file, position P, color c);
set<mov> knightScan (int rank, char file, position P, color c, mov move);
set<mov> legalMovesPawn(int rank, char file, position P, color c);
set<mov> pawnScan (int rank, char file, position P, color c, mov move);
set<mov> pawnScanDiagonal (int rank, char file, position P, color c, mov move);

#endif

#pragma once