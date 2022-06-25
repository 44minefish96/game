#include <bits/stdc++.h>
#include <windows.h>
#define MAX 100
#define BOXSIZE 37
#define SPEED 300

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
struct Piece{
	int x;
	int y;	
};
struct Queue{
	int real;
	int front;
	int size;
	Piece p[MAX];
};
void init(Queue &Q){
	Q.real=4;
	Q.front=0;
	Q.p[1]={5,3};
	Q.p[2]={6,3};
	Q.p[3]={7,3};
	Q.p[4]={8,3};
	Q.size = Q.real - Q.front;
	return;
}
void SpwanFood(int &x, int &y){//生成食物 
	x=rand()%BOXSIZE+1;
	y=rand()%BOXSIZE+1;
	return;
}
void inq(Queue &Q, char face){
	switch(face){//方向-蛇头入队操作 
		case 'u':
			Q.p[Q.real+1].x=Q.p[Q.real].x-1;
			Q.p[Q.real+1].y=Q.p[Q.real].y;
			break;
		case 'd':
			Q.p[Q.real+1].x=Q.p[Q.real].x+1;
			Q.p[Q.real+1].y=Q.p[Q.real].y;
		break;
		case 'l':
			Q.p[Q.real+1].x=Q.p[Q.real].x;
			Q.p[Q.real+1].y=Q.p[Q.real].y-1;
		break;
		case 'r':
			Q.p[Q.real+1].x=Q.p[Q.real].x;
			Q.p[Q.real+1].y=Q.p[Q.real].y+1;
		break;
	}
	Q.real++;
	Q.size=Q.real-Q.front;
	return;
}
void ouq(Queue &Q){
	Q.front++;
	return;
}
void euq(Queue &Q){
	Q.front--;
	return;
}
void WindowSizeSpwan(){
	system("mode con cols=200 lines=200");
} 
void print(Queue &Q, int &foodX, int &foodY){
	int IsSnack=0;
	for(int i=1;i<=BOXSIZE;i++) cout<<'*';
	cout<<"            "<<Q.size-1;
	cout<<endl;
	
	for(int i=1;i<=BOXSIZE;i++){
		for(int j=1;j<=BOXSIZE;j++){
			IsSnack=0;
			if(i==foodX && j==foodY){
				cout<<'O';
				IsSnack=2;
			}
			for(int k=Q.front+1;k<=Q.real;k++){
				if(i==Q.p[k].x && j==Q.p[k].y){
					cout<<'#';
					IsSnack=1;
					break;
				}
				while(Q.p[k].x==foodX && Q.p[k].y==foodY){
					euq(Q);
					SpwanFood(foodX,foodY);
				}
			}
			if(IsSnack==0)cout<<' ';
		}
		cout<<'*'<<endl;
	}
	
	for(int i=1;i<=BOXSIZE;i++) cout<<'*';
	cout<<endl;
	return;
}

void cls(){
	Sleep(500-SPEED);
	system("cls");
	return;
}
bool check(char a){
	return KEY_DOWN(a); 
}
Queue Q;
int main(){
	WindowSizeSpwan();
	
	srand(time(NULL));
	int fX,fY;
	SpwanFood(fX, fY);
	
	init(Q);
	print(Q,fX,fY);//第一次显示
	char face='u';//默认前进 
	inq(Q,face);
	ouq(Q);
	cls();
	
	for(;;){
		print(Q,fX,fY);
		for(int i=1;i<=6;i++){
			if(check('W')){
				face='u';
				break;
			}
			if(check('A')){
				face='l';
				break;
			}
			if(check('S')){
				face='d';
				break;
			}
			if(check('D')){
				face='r';
				break;
			}
			Sleep(50);
		}
		inq(Q,face);
		ouq(Q);
		cls();
	}
}
