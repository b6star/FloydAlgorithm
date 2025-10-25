#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


const int INF = 1e8;

void printMatrix(int n, int m, vector<vector<int>> matrix);

void floyd2(int n, const vector<vector<int>>& W, vector<vector<int>>& D, vector<vector<int>>& P) {
	int i, j, k;
	D = W;    
	P.assign(n, vector<int>(n, -1));
	for (k=0; k<n; k++) 
		for (i=0; i< n; i++) 
			for (j=0; j<n; j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
}

void path(int start, int end, vector<vector<int>>& P) {
	if (P[start][end] >= 0) {
		int k = P[start][end];
		path(start, k,  P);
		cout << " v" << k+1;  
		path(k, end, P);
	}
}

void main() {
	//SIZE 값은 vertex 개수
	int SIZE = 5;
	// weight 값 설정
	vector<vector<int>> weight = {
		{0, 1, INF, 1, 5},
		{9, 0, 3, 2, INF},
		{INF, INF, 0, 4, INF},
		{INF, INF, 2, 0, 3},
		{3, INF, INF, INF, 0}
	};
	//distance 값 초기화
	vector<vector<int>> distance(SIZE, vector<int>(SIZE, 0));
	vector<vector<int>> P(SIZE, vector<int>(SIZE));

	//floyd2 알고리즘 실행
	floyd2(SIZE, weight, distance, P);

	//결과 출력
	cout << "distance\n";
	printMatrix(SIZE, SIZE, distance);

	cout << "path for v5 to v3:";
	path(5-1, 3-1, P);
	return;
}


void printMatrix(int n, int m, vector<vector<int>> &matrix) {
	cout << " ";
	for (int i = 1; i <= m; i++) cout  << "|" << i;
	cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << i+1 << "|";
		for (int j = 0; j < m; j++) {
			if (matrix[i][j] >= INF) 
				cout << "INF" << " ";
			else
				cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}
