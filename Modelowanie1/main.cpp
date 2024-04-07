#include "read_file.h"
#include "AutomateCelular.h"
#include "WildFire.h"
#include <iostream>
#include <vector>

int main()
{
	srand(time(NULL));
	Vector vector = { -8,5 };
	WildFire forest;
	forest.setVector(vector);
	forest.readBitmap("mapa_kolorowa.bmp");
	forest.lightning(5);
	forest.setIterationNumber(100);
	forest.simulation();
	system("pause");
}

