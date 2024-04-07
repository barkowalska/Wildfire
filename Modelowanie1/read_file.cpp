#include <fstream>
#include "EasyBMP.h"


using namespace std;


int** read_file(int& width, int& length,string txt)
{
	ifstream file;
	file.open(txt.c_str());

	file >> width;

	file >> length;
	int** input = new int* [length];
	for (int i = 0; i < length; i++)
	{
		input[i] = new int[width];
	}

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			file >> input[i][j];
		}
	}
	file.close();
	return input;

}

void write_to_file(int** output, int width, int length, string dest)
{
	ofstream file;
	file.open(dest);

	file << width << endl;

	file << length << endl;

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			file << output[i][j] << ' ';
		}
		file << endl;
	}
	file.close();
}

int** read_bitmap(int& width, int& length, string bitmap)
{
	BMP obraz;
	obraz.ReadFromFile(bitmap.c_str());
	width = obraz.TellWidth();
	length = obraz.TellHeight();

	int** input = new int* [length];
	for (int i = 0; i < length; i++)
	{
		input[i] = new int[width];
	}

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			input[i][j]=obraz.GetPixel(j,i).Red;
		}
	}
	return input;
}

void write_bitmap_to_file(int** output, int width, int length, string dest)
{
	BMP obraz;
	obraz.SetSize(width, length);
	RGBApixel pixel;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pixel.Blue = output[i][j];
			pixel.Green = output[i][j];
			pixel.Red = output[i][j];
			obraz.SetPixel(j, i, pixel);
		}
	}

	obraz.WriteToFile(dest.c_str());
}


void write_bitmap_to_file01(int** output, int width, int length, string dest)
{
	BMP obraz;
	obraz.SetSize(width, length);
	RGBApixel pixel;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pixel.Blue = output[i][j] *255;
			pixel.Green = output[i][j] * 255;
			pixel.Red = output[i][j] * 255;
			obraz.SetPixel(j, i, pixel);
		}
	}

	obraz.WriteToFile(dest.c_str());
}