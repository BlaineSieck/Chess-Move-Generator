//Name = Blaine Sieck
//Lab501

#include "project2.h"

//_________________________________________________________________________

//function definition:
//project 1 stuff

//function for merging the vectors from scansquares and scanpieces to create the 2D vector of the chessboard
position merge(vector<string> squares, vector<string> pieces, string s1) {
	vector<string> rowvec;
	for (int i = 0; i < 64; ++i) {
		string currentSquare = squares[i];
		if (squares[i] != "e") {
			for (int j = 0; j < pieces.size(); ++j) {
			string s2 = pieces[j] + currentSquare;
			int occurrences = count(pieces.begin(), pieces.end(), pieces[j]);
			if ((s1.find(s2) != string::npos) && occurrences == 1) {
				rowvec.push_back(pieces[j]);
			}
			else if ((s1.find(s2) != string::npos) && occurrences > 1) {
				rowvec.push_back(pieces[j]);
				break;
			}
		}
		}
		else
			rowvec.push_back("e");
	}
	
	vector<vector<string> > chessboard;
	vector<string> temp;
	int counter = 0;
	for (int a = 0; a < rowvec.size(); a++) {
		if (counter < 8) {
			string & element = rowvec[a];
			temp.push_back(element);
			counter += 1;
		}
		if (counter == 8) {
			chessboard.push_back(temp);
			temp.clear();
			counter = 0;
		}
	}
		return chessboard;
	}

//function to check if the same piece is on the board multiple times or not
int substringOccurences(const string &substring, const string &str) {
    int n = 0;
    string ::size_type pos = 0;
    while((pos = str.find(substring, pos)) != string::npos ) {
        n++;
        pos += substring.size();
    }
    return n;
}

//function for scanning each square on the board that is non-empty and creating a vector with all of the found pieces on the board
vector<string> scanPieces(string s1) {
	vector<string> pieces;
	string piece_type_array[6] = {"p", "r", "k", "b", "Q", "K"};
	string color_array[2] = {"B", "W"};
	for (int i = 0; i < 6; i++) {
		string currenttype = piece_type_array[i];
		for (int j = 0; j < 2; j++) {
			string currentcolor = color_array[j];
			string s2 = currentcolor + currenttype;
			if (s1.find(s2) != string::npos) {
				int count = substringOccurences(s2, s1);
				for(int k = 0; k < count; k++) {
					pieces.push_back(s2);
				}
			}
		}
	}
	return pieces;
}

//function for scanning each square of the chessboard and determining if it is empty or not and creating a vector with 64 members representing each square
vector<string> scanSquares(string s3) {
	vector<string> squares;
	string rankarray[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
	string filearray[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
	for (int i = 0; i < 8; i++) {
		string currentrank = rankarray[i];
		for (int j = 0; j < 8; j++) {
			string currentfile = filearray[j];
			string s4 = currentrank + currentfile;
			if (s3.find(s4) != string::npos) {
				squares.push_back(s4); 
				}
				else {
					squares.push_back("e");
				}
		}
	}
	return squares;
}

//function for constructing the chessboard based on the given puzzle string
position readPosition(string s)
{
	vector<string> squaresresult = scanSquares(s);
	vector<string> piecesresult = scanPieces(s);
	position boardresult = merge(squaresresult, piecesresult, s);
	
	return boardresult;
}

//_________________________________________________________________________

//project 2 stuff
//legalMoves	
set<mov> legalMoves(position P, color c) {
	set<mov> temp;
	set<mov> tempking;
	set<mov> playermoves;
	set<mov> playerkingmoves;
	set<mov> opponentmoves;
	char oppc;
	if (c == 'W')
		oppc = 'B';
	if (c == 'B')
		oppc = 'W';
	char filearray[8] = {'a','b','c','d','e','f','g','h'};
	string cstring(1, c);
	string playerking = cstring + "K";
	int playerkingrank;
	char playerkingfile;
	//find all legal player moves (simple chess)
	for (int i = 1; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			int rank = i; 
			char file = filearray[j];
			if (playerking == identifypiece(rank, file, P)) {
				playerkingrank = rank;
				playerkingfile = file;
				if (occupied(rank, file, P, c)) {
					tempking = (legalMovesBreakdown(rank, file, P, c));
					playerkingmoves.insert(tempking.begin(), tempking.end());
				}
			}
			if (occupied(rank, file, P, c)) {
				temp = (legalMovesBreakdown(rank, file, P, c));
				playermoves.insert(temp.begin(), temp.end());
			}
		}
	}
	for (int i = 1; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			int opprank = i; 
			char oppfile = filearray[j];
			if (occupied(opprank, oppfile, P, oppc)) {
				temp = (legalMovesBreakdown(opprank, oppfile, P, oppc));
				opponentmoves.insert(temp.begin(), temp.end());
			}
		}
	}
	
	mov move;
	position updatedboard;
	string kingsource;
	string playerkingrankstr = to_string(playerkingrank);
	kingsource = playerkingrankstr + playerkingfile;
	//cout << "kingsource = " << kingsource << endl;
	bool incheck;
	
	for (auto oit = opponentmoves.begin(); oit != opponentmoves.cend(); ++oit) {
			if (oit->dst == kingsource) {
				//cout << "GAME IS IN CHECK" << endl;
				incheck = true;
				break;
			}
			else {
				//cout << "GAME IS NOT IN CHECK" << endl;
				incheck = false;
			}
	}
	
	//cout << "The unfiltered set of legal moves for " << c << " is: " << endl;
	for (auto it = playermoves.begin(); it != playermoves.cend(); ++it) {
		//cout << "{" << it->src << "," << it->dst << "}, ";
		move.src = it->src;
		move.dst = it->dst;
		updatedboard = update(P, move, c);
		//////
		/*cout << endl << "printing position" << endl;
		for (int i = 0; i < (signed)updatedboard.size(); ++i) {
			for (int j = 0; j < 8; ++j) {
				cout << updatedboard[i][j] << "   ";
			}// 
			cout << endl;
		}*/
		/////
	}
	cout << endl;
	
	//for printing out move sets
	/*cout << "The unfiltered set of legal king moves for " << c << " is: " << endl;
	for (auto it = playerkingmoves.begin(); it != playerkingmoves.cend(); ++it) {
		cout << "{" << it->src << "," << it->dst << "}, ";
	}
	cout << endl;
	
	cout << "The unfiltered set of legal moves for " << oppc << " is: " << endl;
	for (auto it = opponentmoves.begin(); it != opponentmoves.cend(); ++it) {
		cout << "{" << it->src << "," << it->dst << "}, ";
	}
	cout << endl;*/
	
	chessresult res;
	res = (check(P, playermoves, playerkingmoves, kingsource, incheck, c));
	set<mov> filteredplayermoves;
	filteredplayermoves = res.playermoves;
	bool incheckmate = res.checkmate;
	bool instalemate = res.stalemate;
	//cout << "checkmate = " << incheckmate << endl;
	//cout << "stalemate = " <<	instalemate << endl;
	if (incheckmate == true) {
		//cout << "CHECKMATE" << endl;
		return {};
	}
	if (instalemate == true) {
		//cout << "STALEMATE" << endl;
		return {};
	}
	else {
		/*cout << "The set of legal moves for " << c << " is: " << endl;
		for (auto it = filteredplayermoves.begin(); it != filteredplayermoves.cend(); ++it) {
		cout << "{" << it->src << "," << it->dst << "}, ";
		}
		cout << endl;*/
		return filteredplayermoves;
	}
}

position update(position P, mov m, color c) {
	position newP;
	newP = P;
	string source = m.src;
	string destination = m.dst;
	char sourcerankchar = source[0];
	int sourcerank = sourcerankchar - '0';
	char sourcefile = source[1];
	char destinationrankchar = destination[0];
	int destinationrank = destinationrankchar - '0';
	char destinationfile = destination[1];
	string piece = identifypiece(sourcerank, sourcefile, P);
	char filearray[8] = {'a','b','c','d','e','f','g','h'};
	int srcindex;
	int dstindex;
	for (int i = 0; i < 8; i++) {
		if (sourcefile == filearray[i])
			srcindex = i;
		if (destinationfile == filearray[i])
			dstindex = i;
	}
	newP[sourcerank - 1][srcindex] = "e";
	newP[destinationrank - 1][dstindex] = piece;
	return newP;
	
}

chessresult check(position P, set<mov> playermoves, set<mov> playerkingmoves, string kingsource, bool chk, color c) {
	set<mov> testmoves = playermoves;
	set<mov> testkingmoves = playerkingmoves;
	char oppc;
	if (c == 'W')
		oppc = 'B';
	if (c == 'B')
		oppc = 'W';
	bool incheck = chk;
	//cout << "incheck? " << incheck << endl;
	bool incheckmate = false;
	bool instalemate = false;
	mov move;
	mov move2;
	position updatedboard;
	set<mov> temp;
	set<mov> oppmovesupdated;
	char filearray[8] = {'a','b','c','d','e','f','g','h'};
	for (auto it = playermoves.begin(); it != playermoves.cend(); ++it) {
		//cout << "MOVE IS {" << it->src << "," << it->dst << "}, " << endl;
		move.src = it->src;
		move.dst = it->dst;
		updatedboard = update(P, move, c);
		for (int i = 1; i < 9; i++) {
			for (int j = 0; j < 8; j++) {
				int rank = i;
				char file = filearray[j];
				if (occupied(rank, file, P, c)) {
					temp = (legalMovesBreakdown(rank, file, updatedboard, oppc));
					oppmovesupdated.insert(temp.begin(), temp.end());
				}
			}
		}
		for (auto playerit = testkingmoves.begin(); playerit != testkingmoves.cend(); ++playerit) {
			for (auto oppit = oppmovesupdated.begin(); oppit != oppmovesupdated.cend(); ++oppit) {
				if (playerit->dst == oppit->dst) {
					move2.src = playerit->src;
					move2.dst = playerit->dst;
					//cout << "Move is being deleted because playerit = " << playerit->dst << " and oppit = " << oppit->dst << endl;
					//cout << "Move is " << move2.src << " to " << move2.dst << endl;
					testmoves.erase(move2);
					//cout << "size of player moves is: " << testmoves.size() << endl;
				}
				if (incheck == false && (oppit->dst == kingsource)) {
					string oppsrc = oppit->src;
					char rankchar = oppsrc[0];
					string rankstr(1, rankchar);
					int opprank = stoi(rankstr);
					char oppfile = oppsrc[1];
					char opppiece = identifypiecetype(opprank, oppfile, P);
					//cout << "opppiece = " << opppiece << endl;
					if (opppiece != 'p') {
						//cout << "Move is being deleted because oppit = " << oppit->dst << " and kingsource = " << kingsource << endl;
						testmoves.erase(move);
						//cout << "size of player moves is: " << testmoves.size() << endl;
						//cout << "MOVE INTO CHECK" << endl;
					}
				}
			}
		}
		
		//cout << "size of player moves is: " << testmoves.size() << endl;
			
		if (incheck == true && testmoves.size() == 0) {
			incheckmate = true;
			break;
		}
		if (incheck == false && testmoves.size() == 0) {
			instalemate = true;
			break;
		}
	}
	chessresult filtered;
	filtered.checkmate = incheckmate;
	//filtered.check = incheck;
	filtered.stalemate = instalemate;
	filtered.playermoves = testmoves;
	return filtered;
}

//for the functions below we assume the game is not in checkmate or stalemate
string createrankfile(int rank, char file) {
	string rankstring = to_string(rank);
	string rankfile = rankstring + file;
	return rankfile;
}

char identifypiecetype(int rank, char file, position P) {
	string piece = identifypiece(rank, file, P);
	string piecetype = piece.substr(1,1);
	assert(piecetype.size() == 1);
	char piecetypechar = piecetype[0];
	return piecetypechar;
}

string identifypiece(int rank, char file, position P) {
	int ifile;
	if (file == 'a')
		ifile = 0;
	if (file == 'b')
		ifile = 1;
	if (file == 'c')
		ifile = 2;
	if (file == 'd')
		ifile = 3;
	if (file == 'e')
		ifile = 4;
	if (file == 'f')
		ifile = 5;
	if (file == 'g')
		ifile = 6;
	if (file == 'h')
		ifile = 7;
	rank = rank - 1;
	string piece = P[rank][ifile];
	return piece;
}

char identifycolor(int rank, char file, position P) {
	string piece = identifypiece(rank, file, P);
	string piececolor = piece.substr(0,1);
	assert(piececolor.size() == 1);
	char piececolorcharacter = piececolor[0];
	return piececolorcharacter;
}

bool occupied(int rank, char file, position P, color c) {
	string piece = identifypiece(rank, file, P);
	char piececolor = identifycolor(rank, file, P);
	if (piece != "e") {
		if (c == piececolor) {
			//cout << "color is " << piececolor << endl;
			//cout << "occupied by " << piece << endl;
			return true;
		}
		else {
			//cout << "square is occupied but by the other color" << endl;
			return true; //occupied but by other color!!!
		}
	}
	else {
		//cout << "empty square" << endl;
		return false;
	}
}

set<mov> legalMovesBreakdown(int rank, char file, position P, color c) {
	//assume no check, checkmate, or stalemate
	set<mov> temp{};
	char piecetype = identifypiecetype(rank, file, P);
	char piececolor = identifycolor(rank, file, P);
	/*********THESE SHOULD RETURN THE SETS CREATED FROM THE LEGALMOVES FUNCTIONS********/
	if (piececolor == c) {
		//King - DONE
		if (piecetype == 'K') {
			temp = (legalMovesKing(rank, file, P, c));
			return temp;
		}
		//Queen - DONE
		if (piecetype == 'Q') {
			temp = (legalMovesQueen(rank, file, P, c));
			return temp;
		}
		//Bishop - DONE
		if (piecetype == 'b') {
			temp = (legalMovesBishop(rank, file, P, c));
			return temp;
		}
		//Rook - DONE
		if (piecetype == 'r') {
			temp = (legalMovesRook(rank, file, P, c));
			return temp;
		}
		//Knight - DONE
		if (piecetype == 'k') {
			temp = (legalMovesKnight(rank, file, P, c));
			return temp;
		}
		if (piecetype == 'p') {
			temp = (legalMovesPawn(rank, file , P, c));
			return temp;
		}
		else
			return temp;
	}
	else
		return temp;
}

set<mov> legalMovesKing(int rank, char file, position P, color c) {
	//the king can move one square at a time in any direction
	//the king can attack any piece other than the king and queen
	int temprank;
	char tempfile;
	char tempfile1; //decremented
	char tempfile2; //incremented
	char filearray[8] = {'a','b','c','d','e','f','g','h'};
	int index;
	for (int i = 0; i < 8; i++) {
		if (file == filearray[i])
			index = i;
	}
	mov move;
	set<mov> temp{};
	set<mov> allkingmoves;
	//check for increasing rank by one and keeping file
	if (rank < 8) {
		temprank = rank + 1;
		tempfile = file;
		if (temprank != rank || tempfile != file) {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (kingScan(temprank, tempfile, P, c, move));
			allkingmoves.insert(temp.begin(), temp.end());
		}
	}
	//check for decreasing rank by one and keeping file
	if (rank > 1) {
		temprank = rank - 1;
		tempfile = file;
		if (temprank != rank || tempfile != file) {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (kingScan(temprank, tempfile, P, c, move));
			allkingmoves.insert(temp.begin(), temp.end());
		}
	}
	//check for increasing rank by one and file one less and one greater
	if (rank < 8 && index > 0) {
		temprank = rank + 1;
		tempfile1 = filearray[index - 1];
		if (temprank != rank || tempfile1 != file) {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile1);
			temp = (kingScan(temprank, tempfile1, P, c, move));
			allkingmoves.insert(temp.begin(), temp.end());
		}
	}
	if (rank < 8 && index < 7) {
		temprank = rank + 1;
		tempfile2 = filearray[index + 1];
		if (temprank != rank || tempfile2 != file) {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile2);
			temp = (kingScan(temprank, tempfile2, P, c, move));
			allkingmoves.insert(temp.begin(), temp.end());
		}
	}
	//check for decreasing rank by one and file one less and one greater
	if (rank > 1 && index > 0) {
		temprank = rank - 1;
		tempfile1 = filearray[index - 1];
		if (temprank != rank || tempfile1 != file) {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile1);
			temp = (kingScan(temprank, tempfile1, P, c, move));
			allkingmoves.insert(temp.begin(), temp.end());
		}
	}
	if (rank > 1 && index < 7) {
		temprank = rank - 1;
		tempfile2 = filearray[index + 1];
		if (temprank != rank || tempfile2 != file) {
				move.src = createrankfile(rank, file);
				move.dst = createrankfile(temprank, tempfile2);
				temp = (kingScan(temprank, tempfile2, P, c, move));
				allkingmoves.insert(temp.begin(), temp.end());
		}
	}
	
	//check for keeping rank and file one less and one greater
	if (index > 0) {
		temprank = rank;
		tempfile1 = filearray[index - 1];
		if (temprank != rank || tempfile1 != file) {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile1);
			temp = (kingScan(temprank, tempfile1, P, c, move));
				allkingmoves.insert(temp.begin(), temp.end());
		}
	}
	if (index < 7) {
		temprank = rank;
		tempfile2 = filearray[index + 1];
		if (temprank != rank || tempfile2 != file) {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile2);
			temp = (kingScan(temprank, tempfile2, P, c, move));
				allkingmoves.insert(temp.begin(), temp.end());
		}
	}
	
	//CASTLING:
	//if the king and the rook haven't moved -- DONE
	//the king can move 2 squares horizontally toward the rook (if nothing is inbetween them) -- DONE
	//the rook jumps over the king and lands in the piece next to it -- n/a
	//the mov added to the set of mov's will be the initial and final position of the king (though the rook also moves) -- DONE
	if (c == 'B') {
		if (rank == 8 && file == 'e') {
			if (identifypiece(8, 'h', P) == "Br") {
				if (occupied(8, 'f', P, c) == false && occupied(8, 'g', P, c) == false) {
					temprank = rank;
					tempfile = filearray[index + 2];
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (kingScan(temprank, tempfile, P, c, move));
					allkingmoves.insert(temp.begin(), temp.end());
					//cout << "The black king castled right" << endl;
				}
			}
			if (identifypiece(8, 'a', P) == "Br") {
				if (occupied(8, 'd', P, c) == false && occupied(8, 'c', P, c) == false && occupied(8, 'b', P, c) == false) {
					temprank = rank;
					tempfile = filearray[index - 2];
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (kingScan(temprank, tempfile, P, c, move));
					allkingmoves.insert(temp.begin(), temp.end());
					//cout << "The black king castled left" << endl;
				}
			}
		}
	}
	if (c == 'W') {
		if (rank == 1 && file == 'e') {
			if (identifypiece(1, 'h', P) == "Wr") {
				if (occupied(1, 'f', P, c) == false && occupied(1, 'g', P, c) == false) {
					temprank = rank;
					tempfile = filearray[index + 2];
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (kingScan(temprank, tempfile, P, c, move));
					allkingmoves.insert(temp.begin(), temp.end());
					//cout << "The white king castled right" << endl;
				}
			}
			if (identifypiece(1, 'a', P) == "Wr") {
				if (occupied(1, 'd', P, c) == false && occupied(1, 'c', P, c) == false && occupied(1, 'b', P, c) == false) {
					temprank = rank;
					tempfile = filearray[index - 2];
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (kingScan(temprank, tempfile, P, c, move));
					allkingmoves.insert(temp.begin(), temp.end());
					//cout << "The white king castled left" << endl;
				}
			}
		}
	}
	return allkingmoves;
}

set<mov> kingScan (int rank, char file, position P, color c, mov move) {
	set<mov> kingmoves{};
	string piece = identifypiece(rank, file, P);
	string piecetype = piece.substr(1,1);
	char piececolor = identifycolor(rank, file, P);
	if (occupied(rank, file, P, c) == false) {
		//cout << "King can move here: " << rank << file << endl;
		kingmoves.insert(move);
	}
	//if (occupied(rank, file, P, c) == true && piececolor == c) //piece is same color
		//cout << "King move is blocked by one of its own pieces: " << piece << endl;
	if (occupied(rank, file, P, c) == true && piececolor != c && (piecetype == "K")) {
		//cout << "King can't really move here, it's a move into check" << endl;
		kingmoves.insert(move);
	}
	if (occupied(rank, file, P, c) == true && piececolor != c && (piecetype != "K")) {
		//cout << "King can move here: " << rank << file << " and capture " << piece << endl;
		kingmoves.insert(move);
	}
	return kingmoves;
}

set<mov> legalMovesQueen(int rank, char file, position P, color c) {
	//the queen can move any number of squares at a time in any direction
	int temprank;
	char tempfile;
	char filearray[8] = {'a','b','c','d','e','f','g','h'};
	int index;
	for (int i = 0; i < 8; i++) {
		if (file == filearray[i])
			index = i;
	}
	mov move;
	set<mov> temp{};
	set<mov> allqueenmoves;
	//check rank stays the same and file decreases by one until end of board and increases by one until end of board
	temprank = rank;
	for (int i = index; i >= 0; i--) {
		tempfile = filearray[i];
		if (tempfile != file) {
			if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (queenScan(temprank, tempfile, P, c, move));
					allqueenmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
			if (occupied(temprank, tempfile, P, c) == true)
			break; 
		}
	}
	for (int i = index; i < 8; i++) {
		tempfile = filearray[i];
		if (tempfile != file)  {
			if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (queenScan(temprank, tempfile, P, c, move));
					allqueenmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
			if (occupied(temprank, tempfile, P, c) == true)
				break;
		}
	}
	//check rank decreases by one until end of board and increases by one until end of board and file stays the same
	for (int i = rank; i > 1; i--) {
		temprank = i - 1;
		tempfile = file;
		if (temprank != rank)  {
			if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (queenScan(temprank, tempfile, P, c, move));
					allqueenmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
			if (occupied(temprank, tempfile, P, c) == true)
				break;
		}
	}
	for (int i = rank; i < 8; i++) {
		temprank = i + 1;
		tempfile = file;
		if (temprank != rank)  {
			if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (queenScan(temprank, tempfile, P, c, move));
					allqueenmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
			if (occupied(temprank, tempfile, P, c) == true)
				break;
		}
	}
	//check for rank and file inreasing by one until end of board and rank and file decreasing by one until end of board
	temprank = rank;
	int tempindex1 = index;
	int tempindex2 = index;
	int tempindex3 = index;
	int tempindex4 = index;
	for (int i = rank; i > 1; i--) {
		temprank = i - 1;
		tempfile = filearray[tempindex1 - 1];
		if (tempindex1 > 0) {
			tempindex1 -= 1;
			if (temprank != rank && tempfile != file) {
				if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (queenScan(temprank, tempfile, P, c, move));
					allqueenmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
				if (occupied(temprank, tempfile, P, c) == true)
						break;
			}
		}
	}
	for (int i = rank; i < 8; i++) {
		temprank = i + 1;
		tempfile = filearray[tempindex2 + 1];
		if (tempindex2 < 7) {
			tempindex2 += 1;
			if (temprank != rank && tempfile != file) {
				if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (queenScan(temprank, tempfile, P, c, move));
					allqueenmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
				if (occupied(temprank, tempfile, P, c) == true)
					break;
			}
		}
	}
	//check for rank increasing and file decreasing and rank decreasing and file increasing
	for (int i = rank; i < 8; i++) {
		temprank = i + 1;
		tempfile = filearray[tempindex3 - 1];
		if (tempindex3 > 0) {
			tempindex3 -= 1;
			if (temprank != rank && tempfile != file) {
				if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (queenScan(temprank, tempfile, P, c, move));
					allqueenmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
				if (occupied(temprank, tempfile, P, c) == true)
						break;
			}
		}
	}
	for (int i = rank; i > 1; i--) {
		temprank = i - 1;
		tempfile = filearray[tempindex4 + 1];
		if (tempindex4 < 7) {
			tempindex4 += 1;
			if (temprank != rank && tempfile != file) {
				if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (queenScan(temprank, tempfile, P, c, move));
					allqueenmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
				if (occupied(temprank, tempfile, P, c) == true)
						break;
			}
		}
	}
	return allqueenmoves;
}

set<mov> queenScan (int rank, char file, position P, color c, mov move) {
	set<mov> queenmoves{};
	string piece = identifypiece(rank, file, P);
	string piecetype = piece.substr(1,1);
	char piececolor = identifycolor(rank, file, P);
	if (occupied(rank, file, P, c) == false) {
		//cout << "Queen can move here: " << rank << file << endl;
		queenmoves.insert(move);
	}
	//if (occupied(rank, file, P, c) == true && piececolor == c) //piece is same color
		//cout << "Queen move is blocked by one of its own pieces: " << piece << endl;
	if (occupied(rank, file, P, c) == true && piececolor != c) {
		//cout << "Queen can move here: " << rank << file << " and capture " << piece << endl;
		queenmoves.insert(move);
	}
	return queenmoves;
}

set<mov> legalMovesBishop(int rank, char file, position P, color c) {
	//the bishop can move any number of squares diagonally
	int temprank;
	char tempfile;
	char filearray[8] = {'a','b','c','d','e','f','g','h'};
	int index;
	for (int i = 0; i < 8; i++) {
		if (file == filearray[i])
			index = i;
	}
	mov move;
	set<mov> temp{};
	set<mov> allbishopmoves;
	//check for rank and file inreasing by one until end of board and rank and file decreasing by one until end of board
	temprank = rank;
	int tempindex1 = index;
	int tempindex2 = index;
	int tempindex3 = index;
	int tempindex4 = index;
	for (int i = rank; i > 1; i--) {
		temprank = i - 1;
		tempfile = filearray[tempindex1 - 1];
		if (tempindex1 > 0) {
			tempindex1 -= 1;
			if (temprank != rank && tempfile != file) {
				//if (identifypiecetype(temprank, tempfile, P) != 'K') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (bishopScan(temprank, tempfile, P, c, move));
					allbishopmoves.insert(temp.begin(), temp.end());
				//}
			}
				else
					break;
				if (occupied(temprank, tempfile, P, c) == true)
						break;
		}
	}
	for (int i = rank; i < 8; i++) {
		temprank = i + 1;
		tempfile = filearray[tempindex2 + 1];
		if (tempindex2 < 7) {
			tempindex2 += 1;
			if (temprank != rank && tempfile != file) {
				//if (identifypiecetype(temprank, tempfile, P) != 'K') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (bishopScan(temprank, tempfile, P, c, move));
					allbishopmoves.insert(temp.begin(), temp.end());
				//}
			}
				else
					break;
				if (occupied(temprank, tempfile, P, c) == true)
					break;
		}
	}
	//check for rank increasing and file decreasing and rank decreasing and file increasing
	for (int i = rank; i < 8; i++) {
		temprank = i + 1;
		tempfile = filearray[tempindex3 - 1];
		if (tempindex3 > 0) {
			tempindex3 -= 1;
			if (temprank != rank && tempfile != file) {
				move.src = createrankfile(rank, file);
				move.dst = createrankfile(temprank, tempfile);
				temp = (bishopScan(temprank, tempfile, P, c, move));
				allbishopmoves.insert(temp.begin(), temp.end());
				if (occupied(temprank, tempfile, P, c) == true)
						break;
			}
		}
	}
	for (int i = rank; i > 1; i--) {
		temprank = i - 1;
		tempfile = filearray[tempindex4 + 1];
		if (tempindex4 < 7) {
			tempindex4 += 1;
			if (temprank != rank && tempfile != file) {
				move.src = createrankfile(rank, file);
				move.dst = createrankfile(temprank, tempfile);
				temp = (bishopScan(temprank, tempfile, P, c, move));
				allbishopmoves.insert(temp.begin(), temp.end());
				if (occupied(temprank, tempfile, P, c) == true)
						break;
			}
		}
	}
	return allbishopmoves;
}

set<mov> bishopScan (int rank, char file, position P, color c, mov move) {
	set<mov> bishopmoves{};
	string piece = identifypiece(rank, file, P);
	string piecetype = piece.substr(1,1);
	char piececolor = identifycolor(rank, file, P);
	if (occupied(rank, file, P, c) == false) {
		//cout << "Bishop can move here: " << rank << file << endl;
		bishopmoves.insert(move);
	}
	//if (occupied(rank, file, P, c) == true && piececolor == c) //piece is same color
		//cout << "Bishop move is blocked by one of its own pieces: " << piece << endl;
	if (occupied(rank, file, P, c) == true && piececolor != c) {
		//cout << "Bishop can move here: " << rank << file << " and capture " << piece << endl;
		bishopmoves.insert(move);
	}
	return bishopmoves;
}

set<mov> legalMovesRook(int rank, char file, position P, color c) {
	//the rook can move any number of squares horizontally or vertically
	int temprank;
	char tempfile;
	char filearray[8] = {'a','b','c','d','e','f','g','h'};
	int index;
	for (int i = 0; i < 8; i++) {
		if (file == filearray[i])
			index = i;
	}
	mov move;
	set<mov> temp{};
	set<mov> allrookmoves;
	//check rank stays the same and file decreases by one until end of board and increases by one until end of board
	temprank = rank;
	for (int i = index; i >= 0; i--) {
		tempfile = filearray[i];
		if (tempfile != file) {
			if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (rookScan(temprank, tempfile, P, c, move));
					allrookmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
			if (occupied(temprank, tempfile, P, c) == true)
				break; 
		}
	}
	for (int i = index; i < 8; i++) {
		tempfile = filearray[i];
		if (tempfile != file)  {
			if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (rookScan(temprank, tempfile, P, c, move));
					allrookmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
			if (occupied(temprank, tempfile, P, c) == true)
				break;
		}
	}
	//check rank decreases by one until end of board and increases by one until end of board and file stays the same
	for (int i = rank; i > 1; i--) {
		temprank = i - 1;
		tempfile = file;
		if (temprank != rank)  {
			if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (rookScan(temprank, tempfile, P, c, move));
					allrookmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
			if (occupied(temprank, tempfile, P, c) == true)
				break;
		}
	}
	for (int i = rank; i < 8; i++) {
		temprank = i + 1;
		tempfile = file;
		if (temprank != rank)  {
			if (identifypiecetype(temprank, tempfile, P) != 'e') {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile);
					temp = (rookScan(temprank, tempfile, P, c, move));
					allrookmoves.insert(temp.begin(), temp.end());
			}
				else
					break;
			if (occupied(temprank, tempfile, P, c) == true)
				break;
		}
	}
	return allrookmoves;
}

set<mov> rookScan (int rank, char file, position P, color c, mov move) {
	set<mov> rookmoves{};
	string piece = identifypiece(rank, file, P);
	string piecetype = piece.substr(1,1);
	char piececolor = identifycolor(rank, file, P);
	if (occupied(rank, file, P, c) == false) {
		//cout << "Rook can move here: " << rank << file << endl;
		rookmoves.insert(move);
	}
	//if (occupied(rank, file, P, c) == true && piececolor == c) //piece is same color
		//cout << "Rook move is blocked by one of its own pieces: " << piece << endl;
	if (occupied(rank, file, P, c) == true && piececolor != c) {
		//cout << "Rook can move here: " << rank << file << " and capture " << piece << endl;
		rookmoves.insert(move);
	}
	return rookmoves;
}

set<mov> legalMovesKnight(int rank, char file, position P, color c) {
	int temprank;
	char tempfile;
	char filearray[8] = {'a','b','c','d','e','f','g','h'};
	int index;
	for (int i = 0; i < 8; i++) {
		if (file == filearray[i])
			index = i;
	}
	mov move;
	set<mov> temp{};
	set<mov> allknightmoves;
	temprank = rank;
	//rank + 2 and file + 1
	if (rank < 7 && index < 7) {
		temprank = rank;
		temprank = rank + 2;
		tempfile = filearray[index + 1];
		if (identifypiecetype(temprank, tempfile, P) != 'e') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (knightScan(temprank, tempfile, P, c, move));
			allknightmoves.insert(temp.begin(), temp.end());
		}
	}
	//rank + 2 and file - 1
	if (rank < 7 && index > 0) {
		temprank = rank;
		temprank = rank + 2;
		tempfile = filearray[index - 1];
		if (identifypiecetype(temprank, tempfile, P) != 'e') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (knightScan(temprank, tempfile, P, c, move));
			allknightmoves.insert(temp.begin(), temp.end());
		}
	}
	//rank + 1 and file + 2
	if (rank < 8 && index < 6) {
		temprank = rank;
		temprank = rank + 1;
		tempfile = filearray[index + 2];
		if (identifypiecetype(temprank, tempfile, P) != 'e') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (knightScan(temprank, tempfile, P, c, move));
			allknightmoves.insert(temp.begin(), temp.end());
		}
	}
	//rank + 1 and file - 2
	if (rank < 8 && index > 1) {
		temprank = rank;
		temprank = rank + 1;
		tempfile = filearray[index - 2];
		if (identifypiecetype(temprank, tempfile, P) != 'e') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (knightScan(temprank, tempfile, P, c, move));
			allknightmoves.insert(temp.begin(), temp.end());
		}
	}
	//rank - 2 and file - 1
	if (rank > 2 && index > 0) { //changed rank > 1 to rank > 2***
		temprank = rank;
		temprank = rank - 2;
		tempfile = filearray[index - 1];
		if (identifypiecetype(temprank, tempfile, P) != 'e') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (knightScan(temprank, tempfile, P, c, move));
			allknightmoves.insert(temp.begin(), temp.end());
		}
	}
	//rank - 2 and file + 1
	if (rank > 2 && index < 7) { //changed rank > 1 to rank > 2***
		temprank = rank;
		temprank = rank - 2;
		tempfile = filearray[index + 1];
		if (identifypiecetype(temprank, tempfile, P) != 'e') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (knightScan(temprank, tempfile, P, c, move));
			allknightmoves.insert(temp.begin(), temp.end());
		}
	}
	//rank - 1 and file + 2
	if (rank > 1 && index < 6) { //changed rank > 0 to rank > 1***
		temprank = rank;
		temprank = rank - 1;
		tempfile = filearray[index + 2];
		if (identifypiecetype(temprank, tempfile, P) != 'e') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (knightScan(temprank, tempfile, P, c, move));
			allknightmoves.insert(temp.begin(), temp.end());
		}
	}
	//rank - 1 and file - 2
	if (rank > 1 && index > 1) { //changed rank > 0 to rank > 1***
		temprank = rank;
		temprank = rank - 1;
		tempfile = filearray[index - 2];
		if (identifypiecetype(temprank, tempfile, P) != 'e') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (knightScan(temprank, tempfile, P, c, move));
			allknightmoves.insert(temp.begin(), temp.end());
		}
	}
	return allknightmoves;
}

set<mov> knightScan (int rank, char file, position P, color c, mov move) {
	set<mov> knightmoves{};
	string piece = identifypiece(rank, file, P);
	string piecetype = piece.substr(1,1);
	char piececolor = identifycolor(rank, file, P);
	if (occupied(rank, file, P, c) == false) {
		//cout << "Knight can move here: " << rank << file << endl;
		knightmoves.insert(move);
	}
	//if (occupied(rank, file, P, c) == true && piececolor == c) //piece is same color
		//cout << "Knight move is blocked by one of its own pieces: " << piece << endl;
	if (occupied(rank, file, P, c) == true && piececolor != c) {
		//cout << "Knight can move here: " << rank << file << " and capture " << piece << endl;
		knightmoves.insert(move);
	}
	return knightmoves;
}

set<mov> legalMovesPawn(int rank, char file, position P, color c) {
	//pawns can only capture a piece if it is one forward diagonal from it
	//Need to account for:
	//if a pawn is blocked by a piece moving 1 square, the 2 square move shouldn't happen
	//if a pawn can capture one square diagonally without moving, do it
	int temprank;
	char tempfile;
	int tempfile1;
	int tempfile2;
	string diagonalpiece;
	char filearray[8] = {'a','b','c','d','e','f','g','h'};
	int index;
	for (int i = 0; i < 8; i++) {
		if (file == filearray[i])
			index = i;
	}
	mov move;
	set<mov> temp{};
	set<mov> allpawnmoves;
	tempfile = file;
	if (c == 'W' && rank == 2) { //can move 1 or 2 squares up the board (rank + 1 or rank + 2)
		temprank = rank;
		temprank = rank + 1;
		//if (identifypiecetype(temprank, tempfile, P) != 'K') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (pawnScan(temprank, tempfile, P, c, move));
			allpawnmoves.insert(temp.begin(), temp.end());
		//}
		if (occupied(temprank, tempfile, P, c) == false) {
			temprank = rank;
			temprank = rank + 2;
			//if (identifypiecetype(temprank, tempfile, P) != 'K') {
				move.src = createrankfile(rank, file);
				move.dst = createrankfile(temprank, tempfile);
				temp = (pawnScan(temprank, tempfile, P, c, move));
				allpawnmoves.insert(temp.begin(), temp.end());
			//}
		}
	}	
	else if (c == 'W' && rank != 2) { //can only move 1 square up the board (rank + 1)
		temprank = rank;
		if (rank < 8) {
			temprank = rank + 1;
			//if (identifypiecetype(temprank, tempfile, P) != 'K') {
				move.src = createrankfile(rank, file);
				move.dst = createrankfile(temprank, tempfile);
				temp = (pawnScan(temprank, tempfile, P, c, move));
				allpawnmoves.insert(temp.begin(), temp.end());
			//}
		}
	}
	///////
	if (c == 'W') {
		if (rank < 8 && index > 0) {
				temprank = rank + 1;
				tempfile1 = filearray[index - 1];
				if (/*identifypiecetype(temprank, tempfile1, P) != 'K' && */occupied(temprank, tempfile1, P, c) == true) {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile1);
					temp = (pawnScanDiagonal(temprank, tempfile1, P, c, move));
					allpawnmoves.insert(temp.begin(), temp.end());
				}
		}
		if (rank < 8 && index < 7) {
			temprank = rank + 1;
			tempfile2 = filearray[index + 1];
				if (/*identifypiecetype(temprank, tempfile2, P) != 'K' && */occupied(temprank, tempfile2, P, c) == true) {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile2);
					temp = (pawnScanDiagonal(temprank, tempfile2, P, c, move));
					allpawnmoves.insert(temp.begin(), temp.end());
				}
		}
	}
	///////
	if (c == 'B' && rank == 7) { //can move 1 or 2 squares down the board (rank - 1 or rank - 2)
		temprank = rank;
		temprank = rank - 1;
		//if (identifypiecetype(temprank, tempfile, P) != 'K') {
			move.src = createrankfile(rank, file);
			move.dst = createrankfile(temprank, tempfile);
			temp = (pawnScan(temprank, tempfile, P, c, move));
			allpawnmoves.insert(temp.begin(), temp.end());
		//}
		if (occupied(temprank, tempfile, P, c) == false) {
			temprank = rank;
			temprank = rank - 2;
			//if (identifypiecetype(temprank, tempfile, P) != 'K') {
				move.src = createrankfile(rank, file);
				move.dst = createrankfile(temprank, tempfile);
				temp = (pawnScan(temprank, tempfile, P, c, move));
				allpawnmoves.insert(temp.begin(), temp.end());
			//}
		}
	}
	else if (c == 'B' && rank != 7) { //can only move 1 square down the board (rank - 1)
		temprank = rank;
		if (rank > 1) {
		temprank = rank - 1;
			//if (identifypiecetype(temprank, tempfile, P) != 'K') {
				move.src = createrankfile(rank, file);
				move.dst = createrankfile(temprank, tempfile);
				temp = (pawnScan(temprank, tempfile, P, c, move));
				allpawnmoves.insert(temp.begin(), temp.end());
			//}
		}
	}
	//////
	if (c == 'B') {
		if (rank > 1 && index > 0) {
			temprank = rank - 1;
			tempfile1 = filearray[index - 1];
				if (/*identifypiecetype(temprank, tempfile1, P) != 'K' && */occupied(temprank, tempfile1, P, c) == true) {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile1);
					temp = (pawnScanDiagonal(temprank, tempfile1, P, c, move));
					allpawnmoves.insert(temp.begin(), temp.end());
				}
		}
		if (rank > 1 && index < 7) {
			temprank = rank - 1;
			tempfile2 = filearray[index + 1];
				if (/*identifypiecetype(temprank, tempfile2, P) != 'K' && */occupied(temprank, tempfile2, P, c) == true) {
					move.src = createrankfile(rank, file);
					move.dst = createrankfile(temprank, tempfile2);
					temp = (pawnScanDiagonal(temprank, tempfile2, P, c, move));
					allpawnmoves.insert(temp.begin(), temp.end());
				}
		}
	}
	/////
	return allpawnmoves;
}

set<mov> pawnScan (int rank, char file, position P, color c, mov move) {
	set<mov> pawnmoves{};
	string piece = identifypiece(rank, file, P);
	string piecetype = piece.substr(1,1);
	char piececolor = identifycolor(rank, file, P);
	if (occupied(rank, file, P, c) == false) {
		//cout << "Pawn can move here: " << rank << file << endl;
		pawnmoves.insert(move);
	}
	//if (occupied(rank, file, P, c) == true)
		//cout << "Pawn move is blocked by another piece: " << piece << endl;
	return pawnmoves;
}

set<mov> pawnScanDiagonal (int rank, char file, position P, color c, mov move) {
	set<mov> pawnmoves{};
	string piece = identifypiece(rank, file, P);
	string piecetype = piece.substr(1,1);
	char piececolor = identifycolor(rank, file, P);
	if (occupied(rank, file, P, c) == true && piececolor != c) {
		//cout << "Pawn can move here: " << rank << file << " and capture: " << piece << endl;
		pawnmoves.insert(move);
	}
	return pawnmoves;
}