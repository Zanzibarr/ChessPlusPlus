#include<iostream>
#include "path.cpp"
#include <utility>
using namespace std;

int main (void) {

	pair<int,int> start {0,0};
	pair<int,int> end = {1,2};

	path currPath = get_path(start, end);	

	if(currPath == path::Horizontal) {
		cout<<"Horizontal\n";
		cout<<get_distance(currPath, start,end)<<"\n";
	}
	if(currPath == path::Vertical) {
	       	cout<<"Vertical\n";
		cout<<get_distance(currPath, start,end)<<"\n";
	}
	if(currPath == path::Diagonal) {
		cout<<"Diagonal\n";
		cout<<get_distance(currPath, start,end)<<"\n";
	}
	if(currPath == path::L) {
		cout<<"L\n";
		cout<<get_distance(currPath, start,end)<<"\n";
	}

	return 0;
}
