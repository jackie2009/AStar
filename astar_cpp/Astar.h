#pragma once
#include <vector>;

struct AsGrid{
	AsGrid *parent;
	int score;
	bool closed;
	int cost;
	int last;
	int x;
	int y;
};
class Astar
{
public:
	Astar(void);
	static		std::vector<int>* find(unsigned short **mapdata,unsigned short row,unsigned short col,unsigned int start_x,unsigned int start_y,unsigned int end_x,unsigned int end_y,unsigned int limitR);
 
	~Astar(void);
};
class BinaryHeap{
private :
	std::vector<AsGrid*> list;
	void  tryDownAt(int index);
	void  tryUpAt(int index);
 
public :
BinaryHeap();
	int length;
	void push(AsGrid* val);
void clear();
	AsGrid* popMix();
	void updata(AsGrid * grid,int newScore); 
};