#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <functional>
#include <windows.h>
using namespace std;

string s;
int WIDTH = 0;
int HEIGHT = 0;
char **maze;
int **visited;
pair<int, int> start;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

// 미로 설정
void setMap() {
	// 미로 가로, 세로 길이 구하는 곳
	ifstream in("./maze/2.txt");
	string line;
	while (getline(in, line)) {
		line.erase(line.find_last_not_of(" \n\r\t") + 1);
		HEIGHT++;
		if (line.length() > WIDTH) {
			WIDTH = (int)line.length();
		}
	}
	in.close();

	maze = new char*[HEIGHT];
	visited = new int* [HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		maze[i] = new char[WIDTH];
		visited[i] = new int[WIDTH];
	}
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			maze[i][j] = '0';
			visited[i][j] = 0;
		}
	}

	// 미로 벽, 길, 시작, 끝 설정
	ifstream file("./maze/2.txt");
	int i = 0;
	while (getline(file, line) && i < HEIGHT) {
		for (int j = 0; j < WIDTH; j++) {
			maze[i][j] = line[j];
			if (line[j] == '2') {
				start = { i, j };
			}
			else if (line[j] == '1') {
				visited[i][j] = 1;
			}
		}
		i++;
	}
	file.close();
}

// 콘솔에 미로 그리기
void drawMap() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (maze[i][j] == '0') {		// 길
				SetConsoleTextAttribute(console, 8);
				cout << ' ';
			}
			else if (maze[i][j] == '1') {	// 벽
				SetConsoleTextAttribute(console, 15);
				cout << '#';
			}
			else if (maze[i][j] == '2') {	// 현재 위치
				SetConsoleTextAttribute(console, 10);
				cout << '8';
			}
			else if (maze[i][j] == '3') {	// 목표
				SetConsoleTextAttribute(console, 9);
				cout << '7';
			}
			else if (maze[i][j] == '4') {	// 지나간 길
				SetConsoleTextAttribute(console, 10);
				cout << '@';
			}
		}
		cout << endl;
	}
}

// 길 찾기
void BFS() {
	int mvX[4] = { 0, 0, 1, -1 };
	int mvY[4] = { 1, -1, 0, 0 };
	queue<pair<int, int>> que;
	que.push(start);

	while (!que.empty()) {
		pair<int, int> f = que.front();
		que.pop();
		int x = f.first;
		int y = f.second;
		if (!visited[x][y]) {
			visited[x][y] = 1;
			if (maze[x][y] == '3') {	// 끝에 도달했을 때
				maze[x][y] = '2';
				system("cls");
				drawMap();
				Sleep(200);
				return;
			}
			maze[x][y] = '2';
			system("cls");
			drawMap();
			Sleep(200);
			if (maze[x][y] != '2' && maze[x][y] != '3') {	// 지나간 길 표시
				maze[x][y] = 4;
			}

			for (int i = 0; i < 4; i++) {	// 근처 길 찾기
				int _x = x + mvX[i];
				int _y = y + mvY[i];
				if (_x > 0 && _x < HEIGHT-1 && _y > 0 && _y < WIDTH-1) {
					que.push({ _x, _y });
				}
			}
		}
	}
}

int main() {
	setMap();
	BFS();
} 