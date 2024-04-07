#pragma once
#include "AutomateCelular.h"
#include <string>

enum {burnt, burning, tree, water, rain};

struct Vector
{
	int x;
	int y;
};


class WildFire : public AutomateCelular
{
private:
	Vector vector;
	int counter;
	int n;

public:
	WildFire()=default;
	WildFire(int** cels, int wildth, int length);
	void setVector(Vector vector);
	double probability(int i, int j, int x, int y);
	void simulation();
	void checkNeighborhood(int i, int j,int** matrixCopy);
	void fireFighter(int i, int j, int** matrixCopy);
	void raining();
	void writeToBitMap(std::string plik);
	void readBitmap(std::string plik);
	void lightning(int n);
};