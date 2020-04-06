#include "Astar.h"
#include <algorithm>
#include <map>
using namespace std;
static int mycount=0;
#define isBlock(x,y) (y>=ROW||x>=COL)||(mapdt[y][x]&0x1)!=0
#define swapAt(pos1, pos2) swap(list[pos1],list[pos2])
	  static	BinaryHeap openList;
	  static	map<int,AsGrid *> gridMap;
		  static  unsigned short **mapdt;
	 	  static int COL;
		  static int ROW;
		  static int EndX;
		  static int EndY;
		  static int limitR;
Astar::Astar(void)
{

}

Astar::~Astar(void)
{
}
 static void open(int x,int y,int cost,AsGrid *parent, bool create){
			AsGrid * grid;
			int index;
			if(create){
				grid=new  AsGrid();
				grid->x=x;
				grid->y=y;
				grid->cost=cost;
				grid->parent=parent;
				grid->closed=false;
				grid->score=10000;
				
				 
				gridMap[(y<<16)+x]=grid;
				grid->last=(abs(x-EndX)+abs(y-EndY))*15;
				grid->score=grid->cost+grid->last;
				openList.push(grid);
			}else{
				grid=gridMap[(y<<16)+x];
				grid->parent=parent;;
				grid->cost=cost;
				openList.updata(grid,grid->cost+grid->last);
			}
		
			 mycount++;
			
		}

   static void  check(unsigned int new_x,unsigned int new_y,AsGrid *grid,int cost){

			if(abs(new_x-EndX)>limitR||abs(new_y-EndY)>limitR)return;
			if(isBlock(new_x,new_y)){return;}
		 
			AsGrid*  newGrid=gridMap[(new_y<<16)+new_x];
			if(newGrid==NULL){
				open(new_x,new_y,grid->cost+cost,grid,true);
			}else if(! newGrid->closed &&newGrid->cost>grid->cost+cost){
				open(new_x,new_y,grid->cost+cost,grid,false);
			}
			
		}	
 	static	vector<int>*     getRst(AsGrid *grid){
			vector<int> *return_dt=new vector <int>();
			do{
				return_dt->insert(return_dt->begin(),grid->y);
				return_dt->insert(return_dt->begin(),grid->x);

				grid=grid->parent;
			}while(grid);
				
				return (return_dt->size()>2?return_dt:NULL);
		}
	vector<int> * Astar::find(unsigned short **mapdata,unsigned short row,unsigned short col, unsigned int start_x, unsigned int start_y, unsigned int end_x,unsigned int end_y, unsigned int limitR){
	
		mapdt=mapdata;
	::limitR=limitR;
			
			if(start_x==end_x&&start_y==end_y)return NULL;
			ROW=row;
			COL=col;
			EndX=end_x;
			EndY=end_y;
			if(isBlock(start_x,start_y)){
				return NULL;
 			}
			if(isBlock(end_x,end_y)){return NULL;}
	vector<int> * rst=NULL;

 
			 
			 
			open(start_x,start_y,0,NULL,true);
			 		
			while(true){
				int len=openList.length;
				if(len==0){
				 break;
				}
				  AsGrid *c_grid=openList.popMix();
			
				if(c_grid->x==end_x&&c_grid->y==end_y){
						
					rst= getRst(c_grid);
					break;
				}
				c_grid->closed=true;
				unsigned int x=c_grid->x;
				unsigned int y=c_grid->y;

				check(x,y-1,c_grid,10);
				check(x-1,y,c_grid,10);
				check(x+1,y,c_grid,10);
				check(x,y+1,c_grid,10);
				check(x-1,y-1,c_grid,15);
				check(x+1,y-1,c_grid,15);
				check(x-1,y+1,c_grid,15);
				check(x+1,y+1,c_grid,15);
				 
			}//for over
			map<int ,AsGrid*>::iterator it=gridMap.begin();
			for(;it!=gridMap.end();it++){
			delete	it->second;
			}
			gridMap.clear();
			openList.clear();
		return rst;
}

	BinaryHeap::BinaryHeap(){
		length=0;
	}

void BinaryHeap::push(AsGrid *val){
	list.push_back(val);
	length=list.size();
	tryUpAt(length-1);
};

AsGrid * BinaryHeap::popMix(){
	AsGrid *val=list[0];
	swapAt(0,length-1);
	  list.pop_back();
	  length=list.size();
	tryDownAt(0);
	return val;
};
void BinaryHeap::tryUpAt(int index){
	if(index<=0)return;
	int headIndex=(index-1)/2;
	if(list[index]->score<list[headIndex]->score){
		swapAt(index,headIndex);
		tryUpAt(headIndex);
	}
};
void BinaryHeap::tryDownAt(int index){
	if(index<0)return;
	int childIndex=index*2+1;
	if(childIndex>=length){return;}

	if(childIndex+1<length&&list[childIndex+1]->score<list[childIndex]->score){
		if(list[index]->score>list[childIndex+1]->score){
			swapAt( index,childIndex+1);
			tryDownAt(childIndex+1);

		}
	}else{

		if(list[index]->score>list[childIndex]->score){
			swapAt( index,childIndex);
			tryDownAt(childIndex);

		}
	}
};
 
void BinaryHeap::updata(AsGrid *grid, int newScore){
	
	int index=-1;
	for(int i=0;i<length;i++){
		if(list[i]==grid){
		index=i;
		break;
		}
	}
 
	if(grid->score>newScore){
		grid->score=newScore;
		tryDownAt(index);
	}else if(grid->score<newScore){
		grid->score=newScore;
		tryUpAt(index);
	}
};
void BinaryHeap::clear(){
 list.clear();
 length=0;
}