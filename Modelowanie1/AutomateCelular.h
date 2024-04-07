#pragma once
#include <string>
#include <ctime>
enum class BoundryCondition{Periodic, Absorbtion, Bouncy};

class AutomateCelular
{
protected:
	int iterationNumber;
	int** matrix;
	int width;
	int length;
	BoundryCondition boundryCondition;
public:
	void setBoundryCondition(BoundryCondition boundry);
	void setIterationNumber(int num);
	AutomateCelular();
	AutomateCelular(int** cells, int width, int length);
	~AutomateCelular();
	int** copy();
	void simulation();
	void deleteMatrix(int** matrix_copy,int length, int width);
	void randomMatrix(int width, int length);
	void generateMatrix(int** matrix, double density, int width, int length);

};

