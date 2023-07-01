#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;
const int N=4;
int mp[10][10];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int cent=0;
void setColor(int forgC=7,int backC=0){
	WORD wc=((backC&0x0f)<<4)+(forgC&0x0f);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wc);
}
inline void cls(){system("cls");}
int getRand(){
	for(int i=1;i<=5;i++){
		int d=pow(2,i);
		if(rand()%2==0) return d;
	}
	return 2;
}
void put(){
	cls();
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			setColor(7,log2((int)mp[i][j]));
			printf("%5d ",mp[i][j]);
			setColor();
		}
		puts("\n");
	}
	puts("\n");
	printf("积分：%d\n",cent);
}
void init(){
	system("title 2048");
	srand(time(0));
	mp[rand()%4+1][rand()%4+1]=2;
	put();
}
bool check(){
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(mp[i][j]==2048){
				cls();
				printf("游戏结束了，你赢了！\n最终积分:%d\n",cent+200);
				exit(-1);
			}
			if(!mp[i][j]) return false;
		}
	}
	return true;
}
void work(int id){
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			int xx=i+dx[id],yy=j+dy[id];
			if(xx<1||xx>N||yy<1||yy>N||!mp[i][j]) continue;
			if(!mp[xx][yy]){
				mp[xx][yy]=mp[i][j];
				mp[i][j]=0;
			}
			else if(mp[xx][yy]==mp[i][j]){
				mp[xx][yy]*=2;
				cent+=log2((double)mp[xx][yy]);
				mp[i][j]=0;
			}
		}
	}
	if(!check()&&rand()%3){
		int xx=rand()%4+1,yy=rand()%4+1;
		while(mp[xx][yy]) xx=rand()%4+1,yy=rand()%4+1;
		mp[xx][yy]=getRand();
	}
	put();
}
int main(){
	init();
	do{
		char ch=getch();
		if(ch=='w') work(0);
		if(ch=='s') work(1);
		if(ch=='a') work(2);
		if(ch=='d') work(3);
	}while(!check());
	cls();
	printf("%游戏结束了，你输了！\n最终积分:%d\n",cent);
}
