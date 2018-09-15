#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

#define CUT
#define LIMITED_FLY
//#define RANDOM_FLY
#define RANDOM


const int TOTALNUM = 25;
const int TOTALKIND = 12;
const int UPPER_RANGE_L = 11, UPPER_RANGE_R = 16;
const int LOWER_RANGE_L = 0, LOWER_RANGE_R = 5;
const int H = 17;
const int W = 5;
const int dx[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
const int dy[8] = { 0, 0, -1, 1, 1, -1, 1, -1 };

int rounds = 0;
int id;
int map[H][W];
int tmap[H][W];
int cnt[2][TOTALKIND] = { 0 };
int amount;
int ables[17][5][8] = {
	{ { 0, 0, 1, 0, 1, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 1, 0, 1, 0, 1, 0, 0, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 1, 0, 1, 0, 0, 0, 0, 0 } },//0
	{ { 0, 0, 14, 1, 4, 0, 1, 0 },{ 1, 0, 1, 0, 3, 0, 1, 0 },{ 2, 1, 1, 1, 2, 0, 1, 0 },{ 3, 0, 1, 0, 1, 0, 1, 0 },{ 4, 1, 14, 0, 0, 0, 1, 0 } },//1
	{ { 0, 0, 13, 0, 1, 0, 1, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 1, 0, 1, 0, 1, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 13, 0, 0, 0, 1, 0 } },//2
	{ { 0, 0, 12, 1, 1, 1, 2, 0 },{ 1, 0, 1, 0, 1, 0, 1, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 1, 0, 1, 0, 1, 0 },{ 1, 1, 12, 0, 0, 0, 2, 1 } },//3
	{ { 0, 0, 11, 0, 1, 0, 3, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 1, 0, 1, 0, 1, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 11, 0, 0, 0, 3, 0 } },//4
	{ { 0, 0, 10, 0, 4, 1, 4, 0 },{ 1, 0, 0, 0, 3, 0, 1, 0 },{ 2, 0, 6, 0, 2, 1, 1, 1 },{ 3, 0, 0, 0, 1, 0, 1, 0 },{ 4, 0, 10, 0, 0, 0, 4, 1 } },//5
	{ { 0, 0, 9, 0, 4, 0, 5, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ 2, 0, 5, 0, 2, 0, 1, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ 4, 0, 9, 0, 0, 0, 5, 0 } },//6
	{ { -1, 0, 0, 0, 0, 0, 0, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 } },//7
	{ { 0, 0, 7, 0, 4, 0, 7, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ 2, 0, 3, 0, 2, 0, 3, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ 4, 0, 7, 0, 0, 0, 7, 0 } },//8
	{ { -1, 0, 0, 0, 0, 0, 0, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 } },//9
	{ { 0, 0, 5, 0, 4, 0, 9, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ 2, 0, 1, 0, 2, 0, 5, 0 },{ -1, 0, 0, 0, 0, 0, 0, 0 },{ 4, 0, 5, 0, 0, 0, 9, 0 } },//10
	{ { 0, 0, 4, 1, 4, 0, 10, 0 },{ 1, 0, 1, 0, 3, 0, 0, 0 },{ 2, 1, 1, 1, 2, 0, 6, 0 },{ 3, 0, 1, 0, 1, 0, 0, 0 },{ 4, 1, 4, 0, 0, 0, 10, 0 } },//11
	{ { 0, 0, 3, 0, 1, 0, 11, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 1, 0, 1, 0, 1, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 3, 0, 0, 0, 11, 0 } },//12
	{ { 0, 0, 2, 1, 1, 1, 12, 0 },{ 1, 0, 1, 0, 1, 0, 1, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 1, 0, 1, 0, 1, 0 },{ 1, 1, 2, 0, 0, 0, 12, 1 } },//13
	{ { 0, 0, 1, 0, 1, 0, 13, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 1, 0, 1, 0, 1, 0 },{ 1, 1, 1, 1, 1, 1, 1, 1 },{ 1, 0, 1, 0, 0, 0, 13, 0 } },//14
	{ { 0, 0, 1, 0, 4, 1, 14, 0 },{ 1, 0, 1, 0, 3, 0, 1, 0 },{ 2, 0, 1, 0, 2, 1, 1, 1 },{ 3, 0, 1, 0, 1, 0, 1, 0 },{ 4, 0, 1, 0, 0, 0, 14, 1 } },//15
	{ { 0, 0, 0, 0, 1, 0, 1, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 1, 0, 0, 0, 1, 0, 1, 0 },{ 0, 0, 0, 0, 0, 0, 0, 0 },{ 1, 0, 0, 0, 0, 0, 1, 0 } } };//16
int ymap[17][5] = { { 0, 3, 0, 3, 0 },{ 2, 2, 2, 2, 2 },{ 2, 1, 0, 1, 2 },{ 2, 0, 1, 0, 2 },
{ 2, 1, 0, 1, 2 },{ 2, 2, 2, 2, 2 },{ 2, 0, 2, 0, 2 },{ 2, 0, 2, 0, 2 },
{ 2, 0, 2, 0, 2 },{ 2, 0, 2, 0, 2 },{ 2, 0, 2, 0, 2 },{ 2, 2, 2, 2, 2 },
{ 2, 1, 0, 1, 2 },{ 2, 0, 1, 0, 2 },{ 2, 1, 0, 1, 2 },{ 2, 2, 2, 2, 2 },
{ 0, 3, 0, 3, 0 } };
//编号方式：司令0	 军长1	师长2	旅长3 团长4	
//营长5	连长6	排长7	工兵8	地雷9	
//炸弹10	 军旗11	
double valuemy[TOTALKIND] = { 7.8e3, 5.4e3, 2.8e3, 1.5e3, 4e2, 2e2, 1e2, 30.0, 5e2, 5e3, 2.3e3, 1e13 };
double valueop[TOTALKIND] = { 7.8e3, 5.4e3, 2.8e3, 1.5e3, 4e2, 2e2, 1e2, 30.0, 5e2, 5e3, 2.3e3, 1e13 };
//  司令 军长 师长   旅长  团长  营长  连长 排长 工兵 地雷  炸弹  军棋  
clock_t clk;

struct dirk {
	int x, y, live = 0;
};
dirk direction[2][TOTALKIND][3];

inline bool exist(int x, int y) {
	return (LOWER_RANGE_L <= x && x <= LOWER_RANGE_R && 0 <= y && y < W)
		|| (UPPER_RANGE_L <= x && x <= UPPER_RANGE_R && 0 <= y && y < W)
		|| ((x == 6 || x == 8 || x == 10) && (y == 0 || y == 2 || y == 4));
}


void change() {
	int x, y, xx, yy, col, kind;
	cin >> x >> y >> xx >> yy >> col >> kind;
	//cerr << "Get updates:" << endl;
	//cerr << x << ' ' << y << ' ' << xx << ' ' << yy << ' ' << col << ' ' << kind << endl;
	int tar = col * TOTALKIND + kind;
	if (x == xx && y == yy) {
		map[x][y] = tar;
		tmap[x][y] = tar;
	}
	else {
		int okind = map[x][y] % TOTALKIND;
		int dkind = map[xx][yy] % TOTALKIND;
		int ocol = map[x][y] / TOTALKIND;
		int dcol = map[xx][yy] / TOTALKIND;
		if (map[xx][yy] != -2) {
			if (kind == -2) {
				for (int i = 0; i != 3; ++i) {
					if (direction[ocol][okind][i].live && direction[ocol][okind][i].x == x && direction[ocol][okind][i].y == y) {
						direction[ocol][okind][i].live = 0;//还没改好
					}
					if (direction[dcol][dkind][i].live && direction[dcol][dkind][i].x == xx && direction[dcol][dkind][i].y == yy) {
						direction[dcol][dkind][i].live = 0;
					}
				}
			}
			else {
				if (dkind != kind) {
					for (int i = 0; i != 3; ++i) {
						if (direction[ocol][okind][i].live && direction[ocol][okind][i].x == x && direction[ocol][okind][i].y == y) {
							direction[ocol][okind][i].x = xx;
							direction[ocol][okind][i].y = yy;
						}
						if (direction[dcol][dkind][i].live && direction[dcol][dkind][i].x == xx && direction[dcol][dkind][i].y == yy) {
							direction[dcol][dkind][i].live = 0;
						}
					}
				}
				else {
					for (int i = 0; i != 3; ++i) {
						if (direction[ocol][okind][i].live && direction[ocol][okind][i].x == x && direction[ocol][okind][i].y == y)
							direction[ocol][okind][i].live = 0;
					}
				}
			}
		}
		else {
			for (int i = 0; i != 3; ++i) {
				if (direction[ocol][okind][i].live && direction[ocol][okind][i].x == x && direction[ocol][okind][i].y == y) {
					direction[ocol][okind][i].x = xx;
					direction[ocol][okind][i].y = yy;
				}
			}
		}
		map[x][y] = -2;
		map[xx][yy] = tar;
		tmap[x][y] = -2;
		tmap[xx][yy] = tar;
		//还要更新direction,col,kind为xx,yy剩余的棋子
	}
	int countgong = 0;
	int countsi = 0;
	int countjun = 0;
	int countshi = 0;
	for (int i = 0; i != 3; ++i) {
		if (direction[id][8][i].live) countgong++;
		if (direction[(id + 1) % 2][0][i].live) ++countsi;
		if (direction[(id + 1) % 2][1][i].live) ++countjun;
		if (direction[(id + 1) % 2][2][i].live) ++countshi;
	}
	valuemy[8] = (3 - countgong) * 7e2 + 5e2;
	valuemy[10] = countsi * 6e2 + countjun * 4e2 + countshi * 2e2 + 1.1e3;
	countgong = 0;
	countsi = 0;
	countjun = 0;
	countshi = 0;
	for (int i = 0; i != 3; ++i) {
		if (direction[(id + 1) % 2][8][i].live) countgong++;
		if (direction[id][0][i].live) ++countsi;
		if (direction[id][1][i].live) ++countjun;
		if (direction[id][2][i].live) ++countshi;
	}
	valueop[8] = (3 - countgong) * 7e2 + 5e2;
	valueop[10] = countsi * 5e2 + countjun * 3e2 + countshi * 1.7e2 + 1.1e3;
}

void show_init(int id)
{
	//give a initializing map here
	//this line : kind1 kind2 ... etc
	//Imagine that the chesses are listed from the bottom to the top, left to right
	//This is a stupid start:
	//编号方式：司令0	 军长1	师长2	旅长3 团长4	
	//营长5	连长6	排长7	工兵8	地雷9	
	//炸弹10	 军旗11	
	int opt[25] = { 7, 7, 5, 11, 9, 6, 4, 9, 9, 3, 6, 5, 4, 3, 8, 6, 1, 10, 7, 10, 2, 8, 0, 8, 2 };
	for (int i = 0; i < 25; ++i)
		cout << opt[i] << ' ';
	cout << endl;
}
void get_init()
{
	int arr0[25], arr1[25];
	for (int i = 0; i < 25; ++i)
	{
		cin >> arr0[i];
	}
	for (int i = 0; i < 25; ++i)
	{
		cin >> arr1[i];
		arr1[i] += TOTALKIND;
	}
	map[0][0] = arr0[0];
	map[0][1] = arr0[1];
	map[0][2] = arr0[2];
	map[0][3] = arr0[3];
	map[0][4] = arr0[4];
	map[1][0] = arr0[5];
	map[1][1] = arr0[6];
	map[1][2] = arr0[7];
	map[1][3] = arr0[8];
	map[1][4] = arr0[9];
	map[2][0] = arr0[10];
	map[2][2] = arr0[11];
	map[2][4] = arr0[12];
	map[3][0] = arr0[13];
	map[3][1] = arr0[14];
	map[3][3] = arr0[15];
	map[3][4] = arr0[16];
	map[4][0] = arr0[17];
	map[4][2] = arr0[18];
	map[4][4] = arr0[19];
	map[5][0] = arr0[20];
	map[5][1] = arr0[21];
	map[5][2] = arr0[22];
	map[5][3] = arr0[23];
	map[5][4] = arr0[24];

	map[16][0] = arr1[4];
	map[16][1] = arr1[3];
	map[16][2] = arr1[2];
	map[16][3] = arr1[1];
	map[16][4] = arr1[0];
	map[15][0] = arr1[9];
	map[15][1] = arr1[8];
	map[15][2] = arr1[7];
	map[15][3] = arr1[6];
	map[15][4] = arr1[5];
	map[14][0] = arr1[12];
	map[14][2] = arr1[11];
	map[14][4] = arr1[10];
	map[13][0] = arr1[16];
	map[13][1] = arr1[15];
	map[13][3] = arr1[14];
	map[13][4] = arr1[13];
	map[12][0] = arr1[19];
	map[12][2] = arr1[18];
	map[12][4] = arr1[17];
	map[11][0] = arr1[24];
	map[11][1] = arr1[23];
	map[11][2] = arr1[22];
	map[11][3] = arr1[21];
	map[11][4] = arr1[20];
}



//编号方式：司令0	 军长1	师长2	旅长3 团长4	
//营长5	连长6	排长7	工兵8	地雷9	
//炸弹10	 军旗11	


//编号方式：司令0	 军长1	师长2	旅长3 团长4	
//营长5	连长6	排长7	工兵8	地雷9	
//炸弹10	 军旗11	
//k=0，1...,7从左开始顺时针

inline int modtotalkind(int getinput) {
	return ((getinput >= TOTALKIND) ? (getinput - TOTALKIND) : getinput);
}

inline int stepnotg(int x, int y, int &xx, int &yy, int k, int &remain, int &l, int startk) {//吃子或并子返回2，空格返回1，无效返回0
	switch (k) {
	case 0:
		xx = x;
		yy = y - 1;
		if (!exist(xx, yy)) --yy, ++l;
		break;
	case 1:
		xx = x + 1;
		yy = y - 1;
		break;
	case 2:
		xx = x + 1;
		yy = y;
		if (!exist(xx, yy))++xx, ++l;
		break;
	case 3:
		xx = x + 1;
		yy = y + 1;
		break;
	case 4:
		xx = x;
		yy = y + 1;
		if (!exist(xx, yy))++yy, ++l;
		break;
	case 5:
		xx = x - 1;
		yy = y + 1;
		break;
	case 6:
		xx = x - 1;
		yy = y;
		if (!exist(xx, yy)) --xx, ++l;
		break;
	case 7:
		xx = x - 1;
		yy = y - 1;
		break;
	}
	if (tmap[xx][yy] == -2) {
		remain = startk;
		return 1;
	}
	else if (ymap[xx][yy] == 1) return 0;
	else if ((startk / TOTALKIND) == (tmap[xx][yy] / TOTALKIND)) return 0;
	else if (modtotalkind(tmap[xx][yy]) == 10) {
		if (modtotalkind(startk) <= 4) return 0;
		else {
			remain = -2;
			return 2;
		}
	}
	else if ((modtotalkind(startk)) != 10) {
		if ((modtotalkind(startk)) < (modtotalkind(tmap[xx][yy])) && modtotalkind(tmap[xx][yy]) != 9) {
			remain = startk;
			return 2;
		}
		else if (modtotalkind(startk) == 8 && modtotalkind(tmap[xx][yy]) == 9) {
			remain = startk;
			return 2;
		}
		else if (modtotalkind(startk) == modtotalkind(tmap[xx][yy])) {
			remain = -2;
			return 2;
		}
		else return 0;
	}
	else if (modtotalkind(startk) == 10) {
		remain = -2;
		return 2;
	}
	return -1;
}

//const int dx[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
//const int dy[8] = { 0, 0, -1, 1, 1, -1, 1, -1 };
double eval() {
	double val = 0.0;
	int opid = (id + 1) % 2;

	int countgong = 0;
	int countsi = 0;
	int countjun = 0;
	int countshi = 0;
	for (int i = 0; i != 3; ++i) {
		if (direction[id][8][i].live) countgong++;
		if (direction[(id + 1) % 2][0][i].live) ++countsi;
		if (direction[(id + 1) % 2][1][i].live) ++countjun;
		if (direction[(id + 1) % 2][2][i].live) ++countshi;
	}
	valuemy[8] = (3 - countgong) * 7e2 + 5e2;
	valuemy[10] = countsi * 6e2 + countjun * 4e2 + countshi * 2e2 + 1.1e3;
	countgong = 0;
	countsi = 0;
	countjun = 0;
	countshi = 0;
	for (int i = 0; i != 3; ++i) {
		if (direction[(id + 1) % 2][8][i].live) countgong++;
		if (direction[id][0][i].live) ++countsi;
		if (direction[id][1][i].live) ++countjun;
		if (direction[id][2][i].live) ++countshi;
	}
	valueop[8] = (3 - countgong) * 7e2 + 5e2;
	valueop[10] = countsi * 5e2 + countjun * 3e2 + countshi * 1.7e2 + 1.1e3;



	for (int i = 0; i < 17; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (tmap[i][j] != -2) {
				if (tmap[i][j] / TOTALKIND == id) {
					if (ymap[i][j] != 3 || (tmap[i][j] == 11 || tmap[i][j] == 11 + TOTALKIND)) {
						val += valuemy[modtotalkind(tmap[i][j])];

					}
				}
				else {
					if (ymap[i][j] != 3 || (tmap[i][j] == 11 || tmap[i][j] == 11 + TOTALKIND))
						val -= valueop[modtotalkind(tmap[i][j])];
				}
			}
			//cerr << "i= " << i << " j= " << j << " val= " << val << endl;
		}
	}
	int targetx = direction[opid][11][0].x;
	int targety = direction[opid][11][0].y;
	bool flag[2] = { false };
	if (targetx == 16) {
		for (int i = 2; i != 4; ++i) {
			if (tmap[targetx + dx[i]][targety + dy[i]] / TOTALKIND == id) val += 6e3;
			if (modtotalkind(tmap[targetx + dx[i]][targety + dy[i]]) != 9 && modtotalkind(tmap[targetx + dx[7 - i]][targety + dy[7 - i]]) != 9) flag[i - 2] = true;
		}
		if (tmap[targetx - 1][targety] / TOTALKIND == id) val += 6e3;
		if (flag[0] && tmap[targetx + dx[5]][targety + dy[5]] / TOTALKIND == id) val += 3e3;
		if (flag[1] && tmap[targetx + dx[4]][targety + dy[4]] / TOTALKIND == id) val += 3e3;
	}
	else {
		for (int i = 2; i != 4; ++i) {
			if (tmap[targetx + dx[i]][targety + dy[i]] / TOTALKIND == id) val += 6e3;
			if (modtotalkind(tmap[targetx + dx[i]][targety + dy[i]]) != 9 && modtotalkind(tmap[targetx + dx[9 - i]][targety + dy[9 - i]]) != 9) flag[i - 2] = true;
		}
		if (tmap[targetx + 1][targety] / TOTALKIND == id) val += 6e3;
		if (flag[0] && tmap[targetx + dx[7]][targety + dy[7]] / TOTALKIND == id) val += 3e3;
		if (flag[1] && tmap[targetx + dx[6]][targety + dy[6]] / TOTALKIND == id) val += 3e3;

	}

	targetx = direction[id][11][0].x;
	targety = direction[id][11][0].y;
	flag[0] = false;
	flag[1] = false;
	if (targetx == 16) {
		for (int i = 2; i != 4; ++i) {
			if (tmap[targetx + dx[i]][targety + dy[i]] / TOTALKIND == opid) val -= 4e3;
			if (modtotalkind(tmap[targetx + dx[i]][targety + dy[i]]) != 9 && modtotalkind(tmap[targetx + dx[7 - i]][targety + dy[7 - i]]) != 9) flag[i - 2] = true;
		}
		if (tmap[targetx - 1][targety] / TOTALKIND == opid) val -= 4e3;
		if (flag[0] && tmap[targetx + dx[5]][targety + dy[5]] / TOTALKIND == opid) val -= 1.5e3;
		if (flag[1] && tmap[targetx + dx[4]][targety + dy[4]] / TOTALKIND == opid) val -= 1.5e3;
	}
	else {
		for (int i = 2; i != 4; ++i) {
			if (tmap[targetx + dx[i]][targety + dy[i]] / TOTALKIND == opid) val -= 4e3;
			if (modtotalkind(tmap[targetx + dx[i]][targety + dy[i]]) != 9 && modtotalkind(tmap[targetx + dx[9 - i]][targety + dy[9 - i]]) != 9) flag[i - 2] = true;
		}
		if (tmap[targetx + 1][targety] / TOTALKIND == opid) val -= 4e3;
		if (flag[0] && tmap[targetx + dx[7]][targety + dy[7]] / TOTALKIND == opid) val -= 1.5e3;
		if (flag[1] && tmap[targetx + dx[6]][targety + dy[6]] / TOTALKIND == opid) val -= 1.5e3;

	}

	//cerr << "}" << endl;
	return val;
}


//层数使用奇数层
double e, em = -1e14;
int x01, y01, xx0, yy0;
int i01 = 0, j01 = 0, remain0 = 0, origan0 = 0;
double negamax(int depth, int odepth, bool &flg) {//对对手层执行完后的局面估价，若比em
	if (!flg || 1.0 * (clock() - clk) / CLOCKS_PER_SEC >= 0.99) {
		flg = false;
		return -1;
	}
	int tmpid = (id + depth) % 2;
	int opid = (tmpid + 1) % 2;
	double emax = -1e12;
	amount = rand() % 2;
	if (odepth != 1 && depth == 0) {
		tmap[x01][y01] = -2;
		tmap[xx0][yy0] = remain0;
		direction[tmpid][i01][j01].x = xx0;
		direction[tmpid][i01][j01].y = yy0;
		direction[tmpid][i01][j01].live = ((remain0 == -2) ? 0 : 1);
		int t0;
		if (origan0 != -2) {
			for (t0 = 0; t0 != 3; ++t0) {
				if (direction[opid][modtotalkind(origan0)][t0].live && direction[opid][modtotalkind(origan0)][t0].x == xx0 && direction[opid][modtotalkind(origan0)][t0].y == yy0) {
					direction[opid][modtotalkind(origan0)][t0].live = 0;
					break;
				}
			}
		}
		e = -negamax(depth + 1, odepth, flg);

		if (emax < e) {
			emax = e;
		}
		if (emax > em) {
			em = emax;
			//cerr << "x01,y01 " << x01 << ',' << y01 << "  xx0, y0 " << xx0 << ',' << yy0 << endl;
			//cerr << "val: " << emax << endl;
		}
		tmap[x01][y01] = i01 + tmpid * TOTALKIND;
		tmap[xx0][yy0] = origan0;
		direction[tmpid][i01][j01].x = x01;
		direction[tmpid][i01][j01].y = y01;
		direction[tmpid][i01][j01].live = 1;
		if (origan0 != -2)
			direction[opid][modtotalkind(origan0)][t0].live = 1;
	}

	if (depth >= odepth)
		return ((odepth % 2) ? (-eval()) : (eval()));//偶数层改成正的
	else {
		//if ((clock() - clk) / CLOCKS_PER_SEC >= 0.9) return e;

		if (amount) {

			for (int i = 0; i <= 10; ++i) {
				for (int j = 0; j < cnt[tmpid][i]; ++j) {
					//非工兵的走子
					if (direction[tmpid][i][j].live && i != 9 && i != 8) {
						int tmpx = direction[tmpid][i][j].x;
						int tmpy = direction[tmpid][i][j].y;
						if (ymap[tmpx][tmpy] == 3)continue;
						int xx = tmpx, yy = tmpy, xx1 = tmpx, yy1 = tmpy;
						for (int k = 0; k <= 7; ++k) {
							xx = tmpx;
							yy = tmpy;
							for (int l = 1; l <= ables[tmpx][tmpy][k]; ++l) {
								int remain, origan;
								int avail = stepnotg(xx, yy, xx1, yy1, k, remain, l, tmap[tmpx][tmpy]);
								if (avail) {
									xx = xx1;
									yy = yy1;
									//cerr << "trying: (" << tmpx << ", " << tmpy << ") to (" << xx1 << ", " << yy1 << ")" << endl;

									origan = tmap[xx1][yy1];
									if (depth == 0 && modtotalkind(origan) == 11) {
										x01 = tmpx;
										y01 = tmpy;
										xx0 = xx1;
										yy0 = yy1;
										origan0 = 11;
										return 1e16;
									}
									int t = 0;
									if (origan != -2) {
										for (t = 0; t != 3; ++t) {
											if (direction[opid][modtotalkind(origan)][t].live && direction[opid][modtotalkind(origan)][t].x == xx1 && direction[opid][modtotalkind(origan)][t].y == yy1) {
												direction[opid][modtotalkind(origan)][t].live = 0;
												break;
											}
										}
									}
									tmap[xx1][yy1] = remain;
									tmap[tmpx][tmpy] = -2;
									direction[tmpid][i][j].x = xx1;
									direction[tmpid][i][j].y = yy1;
									direction[tmpid][i][j].live = ((remain == -2) ? 0 : 1);

									e = -negamax(depth + 1, odepth, flg);//may be a problem
																		 //cerr << "val: " << e << endl;//改成-1倍
																		 //cerr << "emax: " << emax << endl;
																		 //cerr << "em: " << em << endl;


									if ((depth == 1 || depth == 3 || depth == 5) && e > -em) {
										tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
										tmap[xx1][yy1] = origan;
										direction[tmpid][i][j].x = tmpx;
										direction[tmpid][i][j].y = tmpy;
										direction[tmpid][i][j].live = 1;
										if (origan != -2)
											direction[opid][modtotalkind(origan)][t].live = 1;
										return e;
									}


									if (emax < e) {
										emax = e;
										if (direction[tmpid][11][0].x == xx1 && direction[tmpid][11][0].y == yy1 && depth == 1) {
											tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
											tmap[xx1][yy1] = origan;
											direction[tmpid][i][j].x = tmpx;
											direction[tmpid][i][j].y = tmpy;
											direction[tmpid][i][j].live = 1;
											if (origan != -2)
												direction[opid][modtotalkind(origan)][t].live = 1;
											return 1e16;
										}
									}
									if (depth == 0 && emax > em) {
										em = emax;
										x01 = tmpx;
										xx0 = xx1;
										y01 = tmpy;
										yy0 = yy1;
										i01 = i;
										j01 = j;
										remain0 = remain;
										origan0 = origan;
										//cerr << "x01,y01 " << x01 << ',' << y01 << "  xx0, y0 " << xx0 << ',' << yy0 << endl;
										//cerr << "val: " << emax << endl;
									}
									tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
									tmap[xx1][yy1] = origan;
									direction[tmpid][i][j].x = tmpx;
									direction[tmpid][i][j].y = tmpy;
									direction[tmpid][i][j].live = 1;
									if (origan != -2)
										direction[opid][modtotalkind(origan)][t].live = 1;
								}
								else break;
								if (avail == 2) break;
							}
						}

					}
					else if (i == 8 && direction[tmpid][i][j].live) {//工兵的走子
						int tx = direction[tmpid][i][j].x, ty = direction[tmpid][i][j].y;
						int tmpx = direction[tmpid][i][j].x;
						int tmpy = direction[tmpid][i][j].y;
						if (ymap[tmpx][tmpy] == 3)continue;
						int xx = tmpx, yy = tmpy, xx1 = tmpx, yy1 = tmpy;
						for (int k = 0; k <= 7; ++k) {
							xx = tmpx;
							yy = tmpy;
							for (int l = 1; l <= ables[tmpx][tmpy][k]; ++l) {
								int remain, origan;
								int avail = stepnotg(xx, yy, xx1, yy1, k, remain, l, tmap[tmpx][tmpy]);
								if (avail) {
									xx = xx1;
									yy = yy1;
									//cerr << "trying: (" << tmpx << ", " << tmpy << ") to (" << xx1 << ", " << yy1 << ")" << endl;

									origan = tmap[xx1][yy1];
									if (depth == 0 && modtotalkind(origan) == 11) {
										x01 = tmpx;
										y01 = tmpy;
										xx0 = xx1;
										yy0 = yy1;
										origan0 = 11;
										return 1e16;
									}
									int t = 0;
									if (origan != -2) {
										for (t = 0; t != 3; ++t) {
											if (direction[opid][modtotalkind(origan)][t].live && direction[opid][modtotalkind(origan)][t].x == xx1 && direction[opid][modtotalkind(origan)][t].y == yy1) {
												direction[opid][modtotalkind(origan)][t].live = 0;
												break;
											}
										}
									}
									tmap[xx1][yy1] = remain;
									tmap[tmpx][tmpy] = -2;
									direction[tmpid][i][j].x = xx1;
									direction[tmpid][i][j].y = yy1;
									direction[tmpid][i][j].live = ((remain == -2) ? 0 : 1);

									e = -negamax(depth + 1, odepth, flg);//may be a problem
																		 //cerr << "val: " << e << endl;//改成-1倍
																		 //cerr << "emax: " << emax << endl;
																		 //cerr << "em: " << em << endl;

									if ((depth == 1 || depth == 3 || depth == 5) && e > -em) {
										tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
										tmap[xx1][yy1] = origan;
										direction[tmpid][i][j].x = tmpx;
										direction[tmpid][i][j].y = tmpy;
										direction[tmpid][i][j].live = 1;
										if (origan != -2)
											direction[opid][modtotalkind(origan)][t].live = 1;
										return e;
									}


									if (emax < e) {
										emax = e;
										if (direction[tmpid][11][0].x == xx1 && direction[tmpid][11][0].y == yy1 && depth == 1) {
											tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
											tmap[xx1][yy1] = origan;
											direction[tmpid][i][j].x = tmpx;
											direction[tmpid][i][j].y = tmpy;
											direction[tmpid][i][j].live = 1;
											if (origan != -2)
												direction[opid][modtotalkind(origan)][t].live = 1;
											return 1e16;
										}
									}
									if (depth == 0 && emax > em) {
										em = emax;
										x01 = tmpx;
										xx0 = xx1;
										y01 = tmpy;
										yy0 = yy1;
										i01 = i;
										j01 = j;
										remain0 = remain;
										origan0 = origan;
										//cerr << "x01,y01 " << x01 << ',' << y01 << "  xx0, y0 " << xx0 << ',' << yy0 << endl;
										//cerr << "val: " << emax << endl;
									}
									tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
									tmap[xx1][yy1] = origan;
									direction[tmpid][i][j].x = tmpx;
									direction[tmpid][i][j].y = tmpy;
									direction[tmpid][i][j].live = 1;
									if (origan != -2)
										direction[opid][modtotalkind(origan)][t].live = 1;
								}
								else break;
								if (avail == 2) break;
							}
						}
						if (ymap[tx][ty] == 2) {
							dirk que[105];
							que[0].x = tx;
							que[0].y = ty;
							int beg = 0, en = 1;
							int gmap[H][W];
							for (int a = 0; a < H; ++a)
								for (int b = 0; b < W; ++b) {
									if (ymap[a][b] == 2)
										gmap[a][b] = 5;
									else gmap[a][b] = -2;
								}
							for (int a = 0; a != 3; ++a) {
								if (direction[opid][9][a].live)
									gmap[direction[opid][9][a].x][direction[opid][9][a].y] += 9 + a;
							}
							gmap[tx][ty] = -1;
							int txx, tyy;
							int flag = 0;
							while (beg < en) {
								int tx0 = que[beg].x, ty0 = que[beg].y;
								for (int a = 0; a != 4; ++a) {
									txx = tx0 + dx[a];
									tyy = ty0 + dy[a];
									if (!exist(txx, tyy)) {
										txx += dx[a];//要改
										tyy += dy[a];
									}
									if (!exist(txx, tyy)) continue;
									if (gmap[txx][tyy] < 5) continue;

									if (tmap[txx][tyy] == -2) {
										que[en].x = txx;
										que[en].y = tyy;
										gmap[txx][tyy] = -1;
										++en;
									}



									else if (gmap[txx][tyy] >= 5 && (tmap[txx][tyy] / TOTALKIND == opid && modtotalkind(tmap[txx][tyy]) >= 8)) {
										int origan = tmap[txx][tyy];
										if (modtotalkind(origan) == 10 || modtotalkind(origan) == 8) {
											direction[tmpid][i][j].live = 0;
											int t;
											for (t = 0; t != 3; ++t) {
												if (direction[opid][modtotalkind(origan)][t].live && direction[opid][modtotalkind(origan)][t].x == txx && direction[opid][modtotalkind(origan)][t].y == tyy) {
													direction[opid][modtotalkind(origan)][t].live = 0;
													break;
												}
											}
											tmap[txx][tyy] = -2;
											tmap[tx][ty] = -2;
											e = -negamax(depth + 1, odepth, flg);

											if ((depth == 1 || depth == 3 || depth == 5) && e > -em) {
												direction[tmpid][i][j].x = tx;
												direction[tmpid][i][j].y = ty;
												direction[tmpid][i][j].live = 1;
												direction[opid][modtotalkind(origan)][t].live = 1;
												tmap[tx][ty] = i + tmpid * TOTALKIND;
												tmap[txx][tyy] = origan;
												return e;
											}


											if (emax < e) {
												emax = e;
											}
											if (depth == 0 && emax > em) {
												em = emax;
												x01 = tx;
												xx0 = txx;
												y01 = ty;
												yy0 = tyy;
												i01 = i;
												j01 = j;
												remain0 = -2;
												origan0 = origan;
												//cerr << "x01,y01 " << x01 << ',' << y01 << "  xx0, y0 " << xx0 << ',' << yy0 << endl;
												//cerr << "val: " << emax << endl;
											}
											direction[tmpid][i][j].x = tx;
											direction[tmpid][i][j].y = ty;
											direction[tmpid][i][j].live = 1;
											direction[opid][modtotalkind(origan)][t].live = 1;
											tmap[tx][ty] = i + tmpid * TOTALKIND;
											tmap[txx][tyy] = origan;

										}
										else if (gmap[txx][tyy] >= 14) {
											direction[tmpid][i][j].x = txx;
											direction[tmpid][i][j].y = tyy;
											direction[opid][9][gmap[txx][tyy] - 14].live = 0;
											tmap[tx][ty] = -2;
											tmap[txx][tyy] = i + tmpid * TOTALKIND;
											e = -negamax(depth + 1, odepth, flg);//may be a problem
																				 //cerr << "val: " << e << endl;//改成-1倍
																				 //cerr << "emax: " << emax << endl;
																				 //cerr << "em: " << em << endl;

											if ((depth == 1 || depth == 3 || depth == 5) && e > -em) {
												direction[tmpid][i][j].x = tx;
												direction[tmpid][i][j].y = ty;
												direction[opid][9][gmap[txx][tyy] - 14].live = 1;
												tmap[tx][ty] = i + tmpid * TOTALKIND;
												tmap[txx][tyy] = 9 + opid * TOTALKIND;
												return e;
											}



											if (emax < e) {
												emax = e;
											}
											if (depth == 0 && emax > em) {
												em = emax;
												x01 = tx;
												xx0 = txx;
												y01 = ty;
												yy0 = tyy;
												i01 = i;
												j01 = j;
												remain0 = i + tmpid * TOTALKIND;
												origan0 = origan;
												//cerr << "x01,y01 " << x01 << ',' << y01 << "  xx0, y0 " << xx0 << ',' << yy0 << endl;
												//cerr << "val: " << emax << endl;
											}
											direction[tmpid][i][j].x = tx;
											direction[tmpid][i][j].y = ty;
											direction[opid][9][gmap[txx][tyy] - 14].live = 1;
											tmap[tx][ty] = i + tmpid * TOTALKIND;
											tmap[txx][tyy] = 9 + opid * TOTALKIND;
										}

									}
								}
								++beg;
							}
						}
					}
				}
			}

		}
		else {

			for (int i = 10; i >= 0; --i) {
				for (int j = 0; j < cnt[tmpid][i]; ++j) {
					//非工兵的走子
					if (direction[tmpid][i][j].live && i != 9 && i != 8) {
						int tmpx = direction[tmpid][i][j].x;
						int tmpy = direction[tmpid][i][j].y;
						if (ymap[tmpx][tmpy] == 3)continue;
						int xx = tmpx, yy = tmpy, xx1 = tmpx, yy1 = tmpy;
						for (int k = 0; k <= 7; ++k) {
							xx = tmpx;
							yy = tmpy;
							for (int l = 1; l <= ables[tmpx][tmpy][k]; ++l) {
								int remain, origan;
								int avail = stepnotg(xx, yy, xx1, yy1, k, remain, l, tmap[tmpx][tmpy]);
								if (avail) {
									xx = xx1;
									yy = yy1;
									//cerr << "trying: (" << tmpx << ", " << tmpy << ") to (" << xx1 << ", " << yy1 << ")" << endl;

									origan = tmap[xx1][yy1];
									if (depth == 0 && modtotalkind(origan) == 11) {
										x01 = tmpx;
										y01 = tmpy;
										xx0 = xx1;
										yy0 = yy1;
										origan0 = 11;
										return 1e16;
									}
									int t = 0;
									if (origan != -2) {
										for (t = 0; t != 3; ++t) {
											if (direction[opid][modtotalkind(origan)][t].live && direction[opid][modtotalkind(origan)][t].x == xx1 && direction[opid][modtotalkind(origan)][t].y == yy1) {
												direction[opid][modtotalkind(origan)][t].live = 0;
												break;
											}
										}
									}
									tmap[xx1][yy1] = remain;
									tmap[tmpx][tmpy] = -2;
									direction[tmpid][i][j].x = xx1;
									direction[tmpid][i][j].y = yy1;
									direction[tmpid][i][j].live = ((remain == -2) ? 0 : 1);

									e = -negamax(depth + 1, odepth, flg);//may be a problem
																		 //cerr << "val: " << e << endl;//改成-1倍
																		 //cerr << "emax: " << emax << endl;
																		 //cerr << "em: " << em << endl;


									if ((depth == 1 || depth == 3 || depth == 5) && e > -em) {
										tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
										tmap[xx1][yy1] = origan;
										direction[tmpid][i][j].x = tmpx;
										direction[tmpid][i][j].y = tmpy;
										direction[tmpid][i][j].live = 1;
										if (origan != -2)
											direction[opid][modtotalkind(origan)][t].live = 1;
										return e;
									}


									if (emax < e) {
										emax = e;
										if (direction[tmpid][11][0].x == xx1 && direction[tmpid][11][0].y == yy1 && depth == 1) {
											tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
											tmap[xx1][yy1] = origan;
											direction[tmpid][i][j].x = tmpx;
											direction[tmpid][i][j].y = tmpy;
											direction[tmpid][i][j].live = 1;
											if (origan != -2)
												direction[opid][modtotalkind(origan)][t].live = 1;
											return 1e16;
										}
									}
									if (depth == 0 && emax > em) {
										em = emax;
										x01 = tmpx;
										xx0 = xx1;
										y01 = tmpy;
										yy0 = yy1;
										i01 = i;
										j01 = j;
										remain0 = remain;
										origan0 = origan;
										//cerr << "x01,y01 " << x01 << ',' << y01 << "  xx0, y0 " << xx0 << ',' << yy0 << endl;
										//cerr << "val: " << emax << endl;
									}
									tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
									tmap[xx1][yy1] = origan;
									direction[tmpid][i][j].x = tmpx;
									direction[tmpid][i][j].y = tmpy;
									direction[tmpid][i][j].live = 1;
									if (origan != -2)
										direction[opid][modtotalkind(origan)][t].live = 1;
								}
								else break;
								if (avail == 2) break;
							}
						}

					}
					else if (i == 8 && direction[tmpid][i][j].live) {//工兵的走子
						int tx = direction[tmpid][i][j].x, ty = direction[tmpid][i][j].y;
						int tmpx = direction[tmpid][i][j].x;
						int tmpy = direction[tmpid][i][j].y;
						if (ymap[tmpx][tmpy] == 3)continue;
						int xx = tmpx, yy = tmpy, xx1 = tmpx, yy1 = tmpy;
						for (int k = 0; k <= 7; ++k) {
							xx = tmpx;
							yy = tmpy;
							for (int l = 1; l <= ables[tmpx][tmpy][k]; ++l) {
								int remain, origan;
								int avail = stepnotg(xx, yy, xx1, yy1, k, remain, l, tmap[tmpx][tmpy]);
								if (avail) {
									xx = xx1;
									yy = yy1;
									//cerr << "trying: (" << tmpx << ", " << tmpy << ") to (" << xx1 << ", " << yy1 << ")" << endl;

									origan = tmap[xx1][yy1];
									if (depth == 0 && modtotalkind(origan) == 11) {
										x01 = tmpx;
										y01 = tmpy;
										xx0 = xx1;
										yy0 = yy1;
										origan0 = 11;
										return 1e16;
									}
									int t = 0;
									if (origan != -2) {
										for (t = 0; t != 3; ++t) {
											if (direction[opid][modtotalkind(origan)][t].live && direction[opid][modtotalkind(origan)][t].x == xx1 && direction[opid][modtotalkind(origan)][t].y == yy1) {
												direction[opid][modtotalkind(origan)][t].live = 0;
												break;
											}
										}
									}
									tmap[xx1][yy1] = remain;
									tmap[tmpx][tmpy] = -2;
									direction[tmpid][i][j].x = xx1;
									direction[tmpid][i][j].y = yy1;
									direction[tmpid][i][j].live = ((remain == -2) ? 0 : 1);

									e = -negamax(depth + 1, odepth, flg);//may be a problem
																		 //cerr << "val: " << e << endl;//改成-1倍
																		 //cerr << "emax: " << emax << endl;
																		 //cerr << "em: " << em << endl;

									if ((depth == 1 || depth == 3 || depth == 5) && e > -em) {
										tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
										tmap[xx1][yy1] = origan;
										direction[tmpid][i][j].x = tmpx;
										direction[tmpid][i][j].y = tmpy;
										direction[tmpid][i][j].live = 1;
										if (origan != -2)
											direction[opid][modtotalkind(origan)][t].live = 1;
										return e;
									}


									if (emax < e) {
										emax = e;
										if (direction[tmpid][11][0].x == xx1 && direction[tmpid][11][0].y == yy1 && depth == 1) {
											tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
											tmap[xx1][yy1] = origan;
											direction[tmpid][i][j].x = tmpx;
											direction[tmpid][i][j].y = tmpy;
											direction[tmpid][i][j].live = 1;
											if (origan != -2)
												direction[opid][modtotalkind(origan)][t].live = 1;
											return 1e16;
										}
									}
									if (depth == 0 && emax > em) {
										em = emax;
										x01 = tmpx;
										xx0 = xx1;
										y01 = tmpy;
										yy0 = yy1;
										i01 = i;
										j01 = j;
										remain0 = remain;
										origan0 = origan;
										//cerr << "x01,y01 " << x01 << ',' << y01 << "  xx0, y0 " << xx0 << ',' << yy0 << endl;
										//cerr << "val: " << emax << endl;
									}
									tmap[tmpx][tmpy] = i + tmpid * TOTALKIND;
									tmap[xx1][yy1] = origan;
									direction[tmpid][i][j].x = tmpx;
									direction[tmpid][i][j].y = tmpy;
									direction[tmpid][i][j].live = 1;
									if (origan != -2)
										direction[opid][modtotalkind(origan)][t].live = 1;
								}
								else break;
								if (avail == 2) break;
							}
						}
						if (ymap[tx][ty] == 2) {
							dirk que[105];
							que[0].x = tx;
							que[0].y = ty;
							int beg = 0, en = 1;
							int gmap[H][W];
							for (int a = 0; a < H; ++a)
								for (int b = 0; b < W; ++b) {
									if (ymap[a][b] == 2)
										gmap[a][b] = 5;
									else gmap[a][b] = -2;
								}
							for (int a = 0; a != 3; ++a) {
								if (direction[opid][9][a].live)
									gmap[direction[opid][9][a].x][direction[opid][9][a].y] += 9 + a;
							}
							gmap[tx][ty] = -1;
							int txx, tyy;
							int flag = 0;
							while (beg < en) {
								int tx0 = que[beg].x, ty0 = que[beg].y;
								for (int a = 0; a != 4; ++a) {
									txx = tx0 + dx[a];
									tyy = ty0 + dy[a];
									if (!exist(txx, tyy)) {
										txx += dx[a];//要改
										tyy += dy[a];
									}
									if (!exist(txx, tyy)) continue;
									if (gmap[txx][tyy] < 5) continue;

									if (tmap[txx][tyy] == -2) {
										que[en].x = txx;
										que[en].y = tyy;
										gmap[txx][tyy] = -1;
										++en;
									}


									else if (gmap[txx][tyy] >= 5 && (tmap[txx][tyy] / TOTALKIND == opid && modtotalkind(tmap[txx][tyy]) >= 8)) {
										int origan = tmap[txx][tyy];
										if (modtotalkind(origan) == 10 || modtotalkind(origan) == 8) {
											direction[tmpid][i][j].live = 0;
											int t;
											for (t = 0; t != 3; ++t) {
												if (direction[opid][modtotalkind(origan)][t].live && direction[opid][modtotalkind(origan)][t].x == txx && direction[opid][modtotalkind(origan)][t].y == tyy) {
													direction[opid][modtotalkind(origan)][t].live = 0;
													break;
												}
											}
											tmap[txx][tyy] = -2;
											tmap[tx][ty] = -2;
											e = -negamax(depth + 1, odepth, flg);
#ifdef CUT
											if ((depth == 1 || depth == 3 || depth == 5) && e > -em) {
												direction[tmpid][i][j].x = tx;
												direction[tmpid][i][j].y = ty;
												direction[tmpid][i][j].live = 1;
												direction[opid][modtotalkind(origan)][t].live = 1;
												tmap[tx][ty] = i + tmpid * TOTALKIND;
												tmap[txx][tyy] = origan;
												return e;
											}
#endif // CUT

											if (emax < e) {
												emax = e;
											}
											if (depth == 0 && emax > em) {
												em = emax;
												x01 = tx;
												xx0 = txx;
												y01 = ty;
												yy0 = tyy;
												i01 = i;
												j01 = j;
												remain0 = -2;
												origan0 = origan;
												//cerr << "x01,y01 " << x01 << ',' << y01 << "  xx0, y0 " << xx0 << ',' << yy0 << endl;
												//cerr << "val: " << emax << endl;
											}
											direction[tmpid][i][j].x = tx;
											direction[tmpid][i][j].y = ty;
											direction[tmpid][i][j].live = 1;
											direction[opid][modtotalkind(origan)][t].live = 1;
											tmap[tx][ty] = i + tmpid * TOTALKIND;
											tmap[txx][tyy] = origan;

										}
										else if (gmap[txx][tyy] >= 14) {
											direction[tmpid][i][j].x = txx;
											direction[tmpid][i][j].y = tyy;
											direction[opid][9][gmap[txx][tyy] - 14].live = 0;
											tmap[tx][ty] = -2;
											tmap[txx][tyy] = i + tmpid * TOTALKIND;
											e = -negamax(depth + 1, odepth, flg);//may be a problem
																				 //cerr << "val: " << e << endl;//改成-1倍
																				 //cerr << "emax: " << emax << endl;
																				 //cerr << "em: " << em << endl;
											if ((depth == 1 || depth == 3 || depth == 5) && e > -em) {
												direction[tmpid][i][j].x = tx;
												direction[tmpid][i][j].y = ty;
												direction[opid][9][gmap[txx][tyy] - 14].live = 1;
												tmap[tx][ty] = i + tmpid * TOTALKIND;
												tmap[txx][tyy] = 9 + opid * TOTALKIND;
												return e;
											}


											if (emax < e) {
												emax = e;
											}
											if (depth == 0 && emax > em) {
												em = emax;
												x01 = tx;
												xx0 = txx;
												y01 = ty;
												yy0 = tyy;
												i01 = i;
												j01 = j;
												remain0 = i + tmpid * TOTALKIND;
												origan0 = origan;
												//cerr << "x01,y01 " << x01 << ',' << y01 << "  xx0, y0 " << xx0 << ',' << yy0 << endl;
												//cerr << "val: " << emax << endl;
											}
											direction[tmpid][i][j].x = tx;
											direction[tmpid][i][j].y = ty;
											direction[opid][9][gmap[txx][tyy] - 14].live = 1;
											tmap[tx][ty] = i + tmpid * TOTALKIND;
											tmap[txx][tyy] = 9 + opid * TOTALKIND;
										}

									}
								}
								++beg;
							}
						}
					}
				}
			}
		}
	}
	return emax;
}

void make_decision(int &x, int &y, int &xx, int &yy) {
	int depth = 1;
	i01 = 0;
	j01 = 0;
	while (1.0 * (clock() - clk) / CLOCKS_PER_SEC < 0.8 && depth < 10) {
		bool flag = true;
		negamax(0, depth, flag);//调试中，完成后改成3层
								//cerr << "depth[" << depth << "]" << " nodes: " << nodes[depth] << endl;
		if (flag) {
			x = x01;
			y = y01;
			xx = xx0;
			yy = yy0;
			if (depth == 1 && origan0 == 11) break;
			em = -1e14;
			e = -1e14;
			//cerr << "depth = " << depth << endl;
			//cerr << "use " << 1.0 * (clock() - clk) / CLOCKS_PER_SEC << " seconds" << endl;
		}
		else break;
		++depth;
	}
}

inline void end() {
	std::cout << "END\n" << std::flush;
}


int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	unsigned seed = time(0);
	if (argc == 2) {
		//cerr << "Excited! Get given seed = " << argv[1] << endl;
		seed = 0;
		for (char *pc = argv[1]; *pc; ++pc)
			seed = seed * 10 + (*pc - '0');
	}
	srand(seed);

	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			map[i][j] = -2;
			tmap[i][j] = -2;
		}
	}
	string op;
	while (true) {
		cin >> op;
		if (op == "id") {
			cin >> id;
			//cerr << id << endl;
			cout << "wuzhanghao" << endl;
			end();
		}
		else if (op == "refresh") {
			get_init();

			//把各个棋子的坐标导入到direction
			int tmpid = map[0][0] / TOTALKIND;
			for (int i = LOWER_RANGE_L; i <= LOWER_RANGE_R; ++i) {
				for (int j = 0; j < W; ++j) {
					if (map[i][j] != -2) {
						direction[tmpid][(map[i][j] % TOTALKIND)][cnt[tmpid][(map[i][j] % TOTALKIND)]].x = i;
						direction[tmpid][(map[i][j] % TOTALKIND)][cnt[tmpid][(map[i][j] % TOTALKIND)]].y = j;
						direction[tmpid][(map[i][j] % TOTALKIND)][cnt[tmpid][(map[i][j] % TOTALKIND)]++].live = 1;
					}
					tmap[i][j] = map[i][j];
				}
			}
			int opid = (tmpid + 1) % 2;
			for (int i = UPPER_RANGE_L; i <= UPPER_RANGE_R; ++i) {
				for (int j = 0; j < W; ++j) {
					if (map[i][j] != -2) {
						direction[opid][(map[i][j] % TOTALKIND)][cnt[opid][(map[i][j] % TOTALKIND)]].x = i;
						direction[opid][(map[i][j] % TOTALKIND)][cnt[opid][(map[i][j] % TOTALKIND)]].y = j;
						direction[opid][(map[i][j] % TOTALKIND)][cnt[opid][(map[i][j] % TOTALKIND)]++].live = 1;
					}
					tmap[i][j] = map[i][j];
				}
			}
			for (int i = LOWER_RANGE_R + 1; i < UPPER_RANGE_L; ++i) {
				for (int j = 0; j < W; ++j) {
					tmap[i][j] = -2;
				}
			}
		}
		else if (op == "init") {
			show_init(id);
			end();
		}
		else if (op == "message") {
			change();
			srand(time(0));
		}
		else if (op == "action") {
			int x, y, xx, yy;
			clk = clock();
			//cerr << "{" << endl;
			make_decision(x, y, xx, yy);
			//cerr << "use " << 1.0 * (clock() - clk) / CLOCKS_PER_SEC << " seconds" << endl;
			//cerr << "}" << endl;
			//cerr << x << " " << y << " " << xx << " " << yy << endl;
			//cerr << "=================================================" << endl;
			cout << x << " " << y << " " << xx << " " << yy << endl;
			em = -1e14;
			e = 0;
			x01 = -1;
			y01 = -1;
			xx0 = -1;
			yy0 = -1;
			end();
		}

	}
}


