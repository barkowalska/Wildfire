#include <cmath>
#include "AutomateCelular.h"
#include "read_file.h"
#include <string>
#include "WildFire.h"
#include "EasyBMP.h"

WildFire::WildFire(int** cels, int wildth, int length) : AutomateCelular(cels, width, length)
{

}


void WildFire::setVector(Vector vector)
{
	this->vector = vector;
}

double WildFire::probability(int i, int j,int x, int y)
{
	double wiatr;
	double cos = (x * vector.x + y * vector.y) / (sqrt(x*x+y*y)*sqrt(vector.x*vector.x+vector.y*vector.y));
	if (cos < 0)cos = abs(cos) / 4;
	double probability = (float)(std::rand()%4)/10.0f + cos * exp(0.00001*sqrt(vector.x * vector.x + vector.y * vector.y));
	return probability;
	
}

void WildFire::simulation()
{
	
	std::string dest;
	char bufor[10];
	for (int t = 0; t < iterationNumber; t++)
	{
		counter = 0;
		n = 1;
		_itoa_s(t, bufor, 10);
		dest = "./res/fire_" + std::string(bufor) + ".bmp";
		writeToBitMap(dest);
		int** matrixCopy = copy();
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (matrixCopy[i][j] == burning)
				{
					checkNeighborhood(i, j, matrixCopy);
					matrix[i][j] = burnt;
				}
				if (matrix[i][j] == rain)
				{
					matrix[i][j] = burnt;
				}
			}
		}
		
			int j;
			if (t < 10) continue;
			int method = std::rand() % 10 + 1;
			if (method > 4)
			{
				for (int i = std::rand() % length; i < length; i++)
				{
					for (j = std::rand() % width; j < width; j++)
					{
						if (matrix[i][j] == burning)
						{
							fireFighter(i, j, matrixCopy);
							matrix[i][j] = water;
							break;
						}
					}
					if (matrix[i][j] == water)break;

				}
			}
			else
			{
				raining();
			}
		deleteMatrix(matrixCopy, length, width);

	}

}

void WildFire::checkNeighborhood(int i, int j, int** matrixCopy)
{
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (x == 0 && y == 0)continue;
			else if (x + i < 0 || y + j < 0 || x + i >= length || y + j >= width) break;
			else
			{
				if (matrixCopy[i + x][j + y] == tree)
				{
					if (probability(i + x, j + y, x, y)*100 >= std::rand()%100)
					{
						matrix[i + x][j + y] = burning;
						counter++;
					}
				}
				
			}
		}

	}
			
}


void WildFire::fireFighter(int i, int j, int** matrixCopy)

{

	bool go = false;
	while (n< (counter*2 > 40? counter/2: 40) )
	{
		go = false;
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)continue;
				else if (x + i < 0 || y + j < 0 || x + i >= length || y + j >= width) break;
				else
				{
					if (matrix[i + x][j + y] == burning)
					{

						matrix[i + x][j + y] = water;
						i = i + x;
						j = j + y;
						n++;
						go = true;
						break;
					}

				}
			}
			if (go)break;

		}
		if (go == false) break;
		
	}

}

void WildFire::raining()

{
	int xS = std::rand() % width;
	int yS = std::rand() % length;
	int spreadX =  std::rand() % (width / 8);
	int spreadY =  std::rand() % (length / 8);
	int xEnd = (xS + spreadX) > width ? width : xS + spreadX;
	int yEnd = (yS + spreadY) > length ? length : yS + spreadY;
	for (int x = 0; x < xEnd; x++)
	{
		for (int y = 0; y < yEnd; y++)
		{
			if (matrix[y][x] == burning || matrix[y][x] == burnt)
				matrix[y][x] = rain;
		}
	}
}



void WildFire::writeToBitMap(std::string plik)
{
	BMP obraz;
	obraz.SetSize(width, length);
	RGBApixel pixel;

	RGBApixel pixel_green;
	pixel_green.Green = 255;
	pixel_green.Blue = 0;
	pixel_green.Red = 0;

	RGBApixel pixel_blue;
	pixel_blue.Green = 0;
	pixel_blue.Blue = 255;
	pixel_blue.Red = 0;

	RGBApixel pixel_red;
	pixel_red.Red = 255;
	pixel_red.Green = 0;
	pixel_red.Blue = 0;

	RGBApixel pixel_light;
	pixel_light.Blue = 230;
	pixel_light.Green = 213;
	pixel_light.Red = 0;


	RGBApixel pixel_black;
	pixel_black.Red = 0;
	pixel_black.Green = 0;
	pixel_black.Blue = 0;

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pixel = pixel_green;
			if (matrix[i][j] == water)
			{
				pixel = pixel_blue;
			}
			
			if (matrix[i][j] == tree)
			{
				pixel = pixel_green;
			}

			if (matrix[i][j] == burning)
			{
				pixel = pixel_red;
			}
			
			if (matrix[i][j] == burnt)
			{
				pixel = pixel_black;
			}
			if (matrix[i][j] == rain)
			{
				pixel = pixel_light;
			}

			obraz.SetPixel(j, i, pixel);
		}
	}

	obraz.WriteToFile(plik.c_str());
}

void WildFire::readBitmap(std::string plik)
{
	BMP obraz;
	obraz.ReadFromFile(plik.c_str());
	width = obraz.TellWidth();
	length = obraz.TellHeight();

	matrix = new int* [length];
	for (int i = 0; i < length; i++)
	{
		matrix[i] = new int[width];
	}

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (obraz.GetPixel(j, i).Green == 255)
			{
				matrix[i][j] = tree;
			}
			else if (obraz.GetPixel(j, i).Blue == 255)
			{
				matrix[i][j] = water;
			}
			else if (obraz.GetPixel(j, i).Red == 255)
			{
				matrix[i][j] = burning;
			}
			else
			{
				matrix[i][j] = tree;
			}
		}
	}


	
}

void WildFire::lightning(int n)
{
	int i = 0;
	while(i<n)
	{
		int x = std::rand() % width;
		int y = std::rand() % length;
		if (matrix[x][y] == tree)
		{
			matrix[x][y] = burning;
			i++;
		}
	}
}