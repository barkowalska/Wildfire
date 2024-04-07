#pragma once
#include<string>

int** read_file(int& verticies, int& edge, std::string txt);
void write_to_file(int** output, int width, int length, std::string dest);
int** read_bitmap(int& width, int& length, std::string bitmap);
void write_bitmap_to_file(int** output, int width, int length, std::string dest);
void write_bitmap_to_file01(int** output, int width, int length, std::string dest);