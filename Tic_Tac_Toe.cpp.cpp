/*
 (C)2023 02/05 Giorgi Gvichiani (Pt) (C++)

 This is a simple tic_tac_toe game engine. Here computeri is O and user is X.(user start the game)
 To see how it works compile and run it on terminal or consol. Your moove,type to intigers in range of (0,2)
 There are no easy/medium/impossible levels it is just impossible.(unless 
 u beat computer by nonlegal moves, code isn't protected so if u want to win
 just make illegal moves ;) )
  
  code description:
  * this engin uses simple backtracing and recursion functions.
  * they recursivly create and serch in the min-max trees of the possible moves.
  * I am not gonna tell what each vallue do, but I will describe all functions implemented in the code.
  * Soo, there is a four functions beside the main function:
  * 1) pr() _ this function just prints the board on the consul,it is called after each computer moove.
  * 2) XO_won_chk(x,y) _ this function is called to check the board if after a moove on (x,y) is there any wins.
  *	   it is a bollean type so if there is a win it returns true, and program exits.
  * 3) dfs1(i,j,mv) _ this is a recursive function that is caled to check each possible scenarios if move was made
  *    on (i,j). mv is a boolean ,and if it is true then Moove is for X and if it is false it coresponeds to the O.
  *    it may return (-1,0,1). (during O mooves it chooses highest,during X mooves it chooses lowest).
  *    if recursion reaches leaf (so there is win or drow) it returns -1 ,0 or 1 depending on whos moove it is.
  * 4) dfs_game() _ this function is called when O has to decide its new moove. It calles dfs1() from each empty 
  *    squear and chooses the one with the maximum score.
  
  
  This is a simple description. if you have some question you can reach me on gmail : g_gvichiani@cu.edu.ge


*/



#include<iostream>

using namespace std;


int board[3][3];

void pr(){
	cout<<'\n';
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<board[i][j]<<' ';
		}cout<<"\n";
	}cout<<'\n';
}

bool XO_won_chk(int x,int y){
	bool tr = true;
	for(int i=1;i<3;i++){
		if(board[x][i]!=board[x][i-1]||board[x][i]==0)tr = false;
	}
	if(tr) return tr;
	tr = true;
	for(int i=1;i<3;i++){
		if(board[i][y]!=board[i-1][y]||board[i][y]==0)tr = false;
	}
	if(tr) return tr;
	tr = true;
	for(int i=1;i<3;i++){
		if(board[i][i]!=board[i-1][i-1]||board[i][i]==0)tr = false;
	}
	if(tr) return tr;
	tr = true;
	for(int i=0;i<2;i++){
		if(board[2-i][i]!=board[1-i][i+1]||board[2-i][i]==0)tr = false;
	}
	return tr;
}


struct ret{
	int i,j;
};

float dfs1(int i,int j,bool mv){
	float mx=-1.1,mn=1.1,a,q=0;
	board[i][j]=(mv?(1):(-1));
	if(XO_won_chk(i,j)){
		board[i][j]=0;
		if(mv)return (float)(-1);
		else return (float)(1);
	}
	mv^=1;
	for(int k=0;k<3;k++){
		for(int h =0;h<3;h++){
			if(board[k][h]==0){
				q+=1;
				a = dfs1(k,h,mv);
				mn = min(mn,a);
				mx = max(mx,a);
			}
		}
	}
	board[i][j]=0;	
	if(q == 0)return (float)(0);
	return (mv?mn:mx);
}

ret dfs_game(){
	float Omx = -1;int Imx=0,Jmx=0;
	for(int k=0;k<3;k++){
		for(int h =0;h<3;h++){
			if(board[k][h]==0){
				float a = dfs1(k,h,false);
				if(a>Omx){
					Omx = a;
					Imx = k;
					Jmx = h;
				}
			}
		}
	}
	return {Imx,Jmx};
}
int main(){
	bool tr=true;int Xmv=0;
	while(true){
		if(!tr){
			ret a = dfs_game();
			board[a.i][a.j]=-1;
			if(XO_won_chk(a.i,a.j)){
				pr();
				cout<<(tr?"X":"O")<<" Won!\n";
				return 0;
			}
			tr^=1;
			pr();
			continue;
		}
		int i,j;
		cin>>i>>j;
		Xmv++;
		board[i][j]=1;
		if(XO_won_chk(i,j)){
			cout<<(tr?"X":"O")<<" Won!\n";
			return 0;
		}
		tr^=1;
		if(Xmv==5){
			cout<<"Draw\n";
			return 0;
		}
	}
	return 0;
}






