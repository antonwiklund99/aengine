#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include "position.h"
#include "move.h"
#include "board.h"
#include "magic.h"
#include "piecePatterns.h"
#include "minimax.h"
using std::cout; using std::endl; using namespace std::chrono;

Position startPos;
Position white1("1r3r2/ppp1kP1p/3pppp1/8/1BnP1P2/P3PK2/6NP/8 w KQkq - 0 1");
Position white2("r1b1k2r/ppppbppp/4p3/8/6K1/6P1/PP1n1P1P/nN6 w KQkq - 0 1");
Position black1("rnbqk2r/pp3ppp/5n2/3p2B1/1b1P4/2N2N2/PP2PPPP/R2QKB1R b KQkq - 3 8");
Position black2("2kr1br1/pp3p1p/2p2n2/2p3p1/2P5/1P1bP3/PB1P1PPP/R2NK2R b KQ - 1 12");
Position positions[] = {startPos, white1, white2, black1, black2};

int main(int argc, char *argv[]) {
	std::ofstream out("benchmarks.txt");
	cout << "Setting up magic" << endl;
	initMagic();
	cout << "done\nSetting up piecepatternsm";
	PiecePatterns::initEasyBitboards();
	cout << "done" << endl;

	out << "GENERATE PSEUDO-LEGAL MOVES" << endl;
	std::vector<Move> m;
	for (auto pos: positions) {
		float sum = 0;
		for (int i = 0; i < 100; i++) {
			auto start = high_resolution_clock::now();
			generateMoves(pos, m);
			auto stop = high_resolution_clock::now();
			sum += duration_cast<nanoseconds>(stop -start).count();
		}
	  out << "average time = " << sum/100 << " ns" << endl;
	}

	out << "GENERATE LEGAL MOVES" << endl;
	for (auto pos: positions) {
		float sum = 0;
		for (int i = 0; i < 100; i++) {
			auto start = high_resolution_clock::now();
			generateMoves(pos, m);
			auto stop = high_resolution_clock::now();
			sum += duration_cast<nanoseconds>(stop -start).count();
		}
		out << "average time = " << sum/100 << " ns" << endl;
	}

	int depth = (argc > 1) ? std::stoi(argv[1]) : 4;
	out << "BEST MOVE SEARCH (depth = " << depth << ")" << endl;
	for (auto pos: positions) {
		float sum = 0;
		for (int i = 0; i < 10; i++) {
			auto start = high_resolution_clock::now();
			minimaxComputeBestMove(pos, depth);
			auto stop = high_resolution_clock::now();
			sum += duration_cast<milliseconds>(stop -start).count();
		}
		out << "average time = " << sum/10 << " microseconds" << endl;
	}
	cout << "done searching see benchmarks.txt and below for results:" << endl;
	system("cat benchmarks.txt");
	return 0;
}
