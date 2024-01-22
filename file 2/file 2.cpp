#include <iostream>

using namespace std;
int field[100][100];
int field_p[100][100];
const int N = 5, M = 5, K = 5;
void print_field() {
	system("cls");
	cout << "  ";
	for (int i = 0; i < M; ++i) {
		cout << " " << i + 1;
		if (i + 1 < 10)  cout << ' ';
	}
	cout << endl;
	for (int i = 0; i < N; i++) {
		cout << i + 1 << " ";
		if (i + 1 < 10)  cout << ' ';
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] == -2) cout << "_  ";
			else if (field_p[i][j] == -1) cout << "f  ";
			else if (field_p[i][j] == -3) cout << "*  ";
			else cout << field_p[i][j] << "  ";
		}
		cout << endl;
	}
}

void dfs(int x, int y) {
	if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] > -2) return;
	field_p[x][y] = field[x][y];
	if (field[x][y] > 0) return;
	for (int i2 = x - 1; i2 <= x + 1; ++i2) {
		for (int j2 = y - 1; j2 <= y + 1; ++j2) {
			if (i2 != x || j2 != y) dfs(i2, j2);
		}
	}
}
bool open_cell(int x, int y) {
	if (field[x][y] == -1) return false;
	if (field[x][y] > 0) {
		field_p[x][y] = field[x][y];
		return true;
	}
	dfs(x, y);
}
bool is_win() {
	int opened = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] >= 0) opened++;
		}
	}
	return (N * M - K == opened);
}

void end_game(bool is_win = false) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] == -1) field_p[i][j] = -2;
			if (field[i][j] == -1) field_p[i][j] = -3;
			}
	}
	print_field();
	cout << "vi" << (is_win ? "viigrali" : "proigrali") << ",\nctobi nachat new game enter eny string:\n";
	string s;
	cin >> s;
}

int main()
{
	while (true) 
	{
		srand(time(0));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				field[i][j] = 0;
				field_p[i][j] = -2;
			}
		}
		for (int i = 0; i < K; ++i) {
			while (true) {
				int x = rand() % N;
				int y = rand() % M;
				if (field[x][y] != -1) {
					field[x][y] = -1;
					break;
				}
			}
		}


		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (field[i][j] != -1) {
					field[i][j] = 0;
					for (int i2 = i - 1; i2 <= i + 1; ++i2) {
						for (int j2 = j - 1; j2 <= j + 1; ++j2) {
							if (i2 >= 0 && i2 < N && j2 >= 0 && j2 <= M &&
								field[i2][j2] == -1) ++field[i][j];
						}
					}
				}
			}
		}
		/*
			\o x y -выбор координат
			\f x y - поставить флажок
			\n - новая игра
			\q - завершать игру
			*/
		while (true) 
		{
			print_field();
			cout << "Enter command: ";
			string comand;
			cin >> comand;
			// команда ввода координат
				//открытие клетки...
		if (comand == "\\o") 
			{
				int x, y;
				cin >> x >> y;
				--x; --y;
				if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) continue;
				if (!open_cell(x, y)) {
					end_game();
					break;
				}
				if (is_win()) {
					end_game(true);
					break;
				}
			}
				// поставить флаг
						else if (comand == "\\f") 
						{
						int x, y;
						cin >> x >> y;
						--x; --y;
						if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) continue;
						if (field_p[x][y] == -1) field_p[x][y] = -2;
						else field_p[x][y] == -1;
						}// новая игра
					else if (comand == "\\n") {
						break;
					}// закрыть игру
					else if (comand == "\\q") {
						return 0;
					}
		}
	}
}
