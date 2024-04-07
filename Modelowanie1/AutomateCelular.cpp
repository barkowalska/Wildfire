#include <cmath>
#include "AutomateCelular.h"
#include "read_file.h"
#include <string>

AutomateCelular::~AutomateCelular()
{
	for (int i = 0; i < length; i++)
	{
		delete[]matrix[i];
	}
	delete []matrix;
}


void AutomateCelular::setIterationNumber(int num)
{
	iterationNumber = num;
}

void AutomateCelular::setBoundryCondition(BoundryCondition boundry)
{
	boundryCondition = boundry;
}

AutomateCelular::AutomateCelular()
{

}


AutomateCelular::AutomateCelular(int** cells, int width, int length)
{
	this->width = width;
	this->length = length;

	matrix = new int*[length];
	for (int i = 0; i < length; i++)
	{
		matrix[i] = new int[width];
	}
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrix[i][j] = cells[i][j];
		}
		
	}
	iterationNumber = 0;
}

int** AutomateCelular::copy()
{
	int** matrix_copy = new int* [length];
	for (int i = 0; i < length; i++)
	{
		matrix_copy[i] = new int[width];
	}
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrix_copy[i][j] = matrix[i][j];
		}
	}
	return matrix_copy;
}

void AutomateCelular::simulation()
{
	char bufor[10];
	std::string dest;
	for (int t = 0; t < iterationNumber; t++)
	{
		_itoa_s(t, bufor, 10);
		dest = "ca_" + std::string(bufor) + ".bmp";
		write_bitmap_to_file01(matrix, width, length, dest);
		int** matrix_copy = copy();
		for (int i = 0; i < length ; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//int counting_0 = 0;
				int counting_1 = 0;
				for (int x = -1; x < 2; x++)
				{
					for (int y = -1; y < 2; y++)
					{
						if (x == 0 && y == 0)continue;
						else if (x + i < 0 || y + j < 0 || x + i >= length || y + j >= width)
						{
							switch (boundryCondition)
							{
							case BoundryCondition::Periodic:
								if (x + i >= 0 && x + i < length)counting_1 += matrix[x+i][width - abs(y + j)];
								else if (y+j >= 0 && y+j < width)counting_1 += matrix[(length - abs(x + i))][y + j];
								else counting_1 += matrix[(length - abs(x + i))][width - abs(y + j)];
								break;
							case BoundryCondition::Absorbtion:
								break;
							case BoundryCondition::Bouncy:
								if (x + i >= 0 && x + i < length)counting_1 += matrix[x+i][(width - 1) * (y + i >= width) + 0];
								else if (y + j >= 0 && y + j < width)counting_1 += matrix[(length - 1) * (x + i >= length) + 0][y + j];
								else counting_1 += matrix[(length - 1) * (x + i >= length) + 0][(width - 1)* (y + i >= width) + 0];
								break;
							default:
								break;
							}
						}

						else
						{
							//if (matrix_copy[i + x][j + y] == 0)counting_0++;
							if (matrix_copy[i + x][j + y] == 1) counting_1++;
						}
					}
				}
				if (matrix[i][j] == 0)
				{
					if (counting_1 == 3)matrix[i][j] = 1;
					else continue;
				}
				else if (matrix[i][j] == 1)
				{
					if (counting_1 > 3 || counting_1 < 2)matrix[i][j] = 0;
					else continue;

				}

			}
		}
		deleteMatrix(matrix_copy, length, width);
	}

}

void AutomateCelular::deleteMatrix(int** matrix_copy, int length, int width)
{
	for(int i = 0; i < length; i++)delete[]matrix_copy[i];
	delete []matrix_copy;
}


void AutomateCelular::randomMatrix(int width,int length)
{
	this->width = width;
	this->length = length;
	matrix = new int* [length];
	for (int i = 0; i < length; i++)
	{
		matrix[i] = new int[width];
	}
	srand(time(NULL));
	int probability = 30;

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((std::rand() % 100 + 1) < probability)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}

}


void AutomateCelular::generateMatrix(int** matrix, double density, int width, int length)
{
	srand(time(NULL));
	double singleField = length * width;
	int max = (this->length * this->width) / singleField;
	int size = std::rand() % ((int)(max * density)) + 1;

	int randomRow;
	int randomColumn;
	for (int i = 0; i < size; i++)
	{
		randomRow = std::rand() % (this->length - length);
		randomRow += length*(randomRow<length);

		randomColumn = std::rand() % (this->width - width);
		randomRow += width * (randomColumn < width);

		for (int row = randomRow; row < randomRow + length; row++)
		{
			for (int column = randomColumn; column < randomColumn + width; column++)
			{
				this->matrix[row][column] = matrix[row - randomRow][column - randomColumn];
			}
		}
	}
}