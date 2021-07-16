#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;
class Bubble
{
private:
	string col="";
	int sameneighbours=0;
	vector<void*> neighboursX;
	vector<void*> neighboursY;
	bool wasmoved = false;
public:
	Bubble();
	Bubble(int x, int y,string color);

	void setneighbours(int count,vector<void*> neighbX, vector<void*> neighbY);
	int getneighbours();

	vector<void*> getXneighbours();
	vector<void*> getYneighbours();
	bool getwasmoved();
	void setwasmoved(bool moved);
	string getcol();
	void setcol(string c);
};
