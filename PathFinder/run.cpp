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

// �̷� ����
void setMap() {
	// �̷� ����, ���� ���� ���ϴ� ��
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

	// �̷� ��, ��, ����, �� ����
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

// �ֿܼ� �̷� �׸���
void drawMap() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (maze[i][j] == '0') {		// ��
				SetConsoleTextAttribute(console, 8);
				cout << ' ';
			}
			else if (maze[i][j] == '1') {	// ��
				SetConsoleTextAttribute(console, 15);
				cout << '#';
			}
			else if (maze[i][j] == '2') {	// ���� ��ġ
				SetConsoleTextAttribute(console, 10);
				cout << '8';
			}
			else if (maze[i][j] == '3') {	// ��ǥ
				SetConsoleTextAttribute(console, 9);
				cout << '7';
			}
			else if (maze[i][j] == '4') {	// ������ ��
				SetConsoleTextAttribute(console, 10);
				cout << '@';
			}
		}
		cout << endl;
	}
}

// �� ã��
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
			if (maze[x][y] == '3') {	// ���� �������� ��
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
			if (maze[x][y] != '2' && maze[x][y] != '3') {	// ������ �� ǥ��
				maze[x][y] = 4;
			}

			for (int i = 0; i < 4; i++) {	// ��ó �� ã��
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