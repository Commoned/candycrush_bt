#include "Bubble.h"
#include <string>
#include <iostream>

using std::string;

Bubble::Bubble(){}
Bubble::Bubble(int x,int y, string color)
{
	col = color;
}

//Getter and Setter
string Bubble::getcol()
{
	return col;
}

void Bubble::setcol(string c)
{
	col = c;
}

int Bubble::getneighbours()
{
	return sameneighbours;
}

void Bubble::setneighbours(int count,vector<void*> neighbX, vector<void*> neighbY)
{
	sameneighbours = count;
	neighboursX = neighbX; 
	neighboursY = neighbY;
}

vector<void*> Bubble::getXneighbours()
{
	return neighboursX;
}
vector<void*> Bubble::getYneighbours()
{
	return neighboursY;
}

bool Bubble::getwasmoved()
{
	return wasmoved;
}

void Bubble::setwasmoved(bool moved)
{
	wasmoved = moved;
}