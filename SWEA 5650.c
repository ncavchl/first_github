#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
20190305 SWEA 5650 핀볼게임
웜홀 6~10
크기 N 5~100
블랙홀 -1 / 최대 5개
웜홀은 반드시 최대 5쌍
웜홀, 블랙홀 존재하지 않는 경우도 있음
웜홀 통과시 진행방향 유지
블럭 평면, 벽 닿으면 방향이 바뀜
블록 경사 닿으면 직각
*/
typedef struct {
	int x;
	int y;
	int exist;
	int dir;
}cite;
int N, ans;
cite ball;
cite hole[5][2] = { 0 };
int map[102][102];
//int xx = 0;
int ops(int i) {
	if (i == 0) return 2;
	if (i == 1) return 3;
	if (i == 2) return 0;
	if (i == 3) return 1;
}

int func(int dir, int A) {
	//dir 방향으로 왔고, A 경사로 일때
	if (A == 1) {
		if (dir == 1 || dir == 0) {
			return ops(dir);
		}
		if (dir == 2) return 1;
		if (dir == 3) return 0;
	}
	if (A == 2) {
		if (dir == 1 || dir == 2) {
			return ops(dir);
		}
		if (dir == 3) return 2;
		if (dir == 0) return 1;
	}
	if (A == 3) {
		if (dir == 2 || dir == 3) {
			return ops(dir);
		}
		if (dir == 1) return 2;
		if (dir == 0) return 3;
	}
	if (A == 4) {
		if (dir == 0 || dir == 3) {
			return ops(dir);
		}
		if (dir == 1) return 0;
		if (dir == 2) return 3;
	}

}

void solve() {
	int point;
	int max = 0;
	// 최대 점수 return
	// 핀볼의 모든 0자리, 4방향에서 다 봐야함
	// 방향 바뀌는 조건 1. 벽, 블럭수평수직 - 정반대 2.경사면 - 직각 3. 웜홀 - 번호같은 다른 웜홀, 방향 동일
	// 실패하는 조건  - 블랙홀, 출발 위치 돌아옴
	// 점수는 벽, 블록에 부딪힌 횟수 
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == 0) {
				for (int d = 0; d < 4; d++) { // 4방향에 대해서
					ball.x = i;
					ball.y = j;
					ball.dir = d;
					point = 0;
					// 지도 돌기 
					while (1) {
						// 이동부터
						if (ball.dir == 0) { // 위
							ball.x = ball.x - 1;
						}
						else if (ball.dir == 1) {// 오른
							ball.y = ball.y + 1;
						}
						else if (ball.dir == 2) {// 아래
							ball.x = ball.x + 1;
						}
						else {// ball.dir == 3 왼
							ball.y = ball.y - 1;
						}
						// 일단 이동방향 따라 이동
						int A = map[ball.x][ball.y];

						//1. 
						//if (ball.x < 0 || ball.y < 0 || ball.x >= N || ball.y >= N) break;
						//2. 이동 한곳이 처음 위치 또는 블랙홀 이면 break;
						if (A == -1 || (ball.x == i && ball.y == j)) break;
						// 4. 사각형이나 벽 닿으면 방향 반대로
						if (ball.x == 0 || ball.y == 0 || ball.x > N || ball.y > N || A == 5) {
							ball.dir = ops(ball.dir);
							point++; // 닿았으니 점수 증가 
						}

						// if (ball.x == i && ball.y == j) break;
						//3. 웜홀 만나면 짝 웜홀로 이동, 이동방향 유지
						if (A> 5) {
							if (hole[A - 6][0].x == ball.x && hole[A - 6][0].y == ball.y) {
								//   printf("e들어옴\n");
								ball.x = hole[A - 6][1].x;
								ball.y = hole[A - 6][1].y;
							}
							else {
								ball.x = hole[A - 6][0].x;
								ball.y = hole[A - 6][0].y;
							}
							//   printf("웜홀\n");
						} // 웜홀 이동

						  // 5. 경사면들 닿으면 방향 반대 또는 직각 꺾기
						if (A > 0 && A < 5) {
							// 삼각형 경사로 닿으면 
							ball.dir = func(ball.dir, A);
							point++;
						}
				//		printf("A %d , %d %d x,y   %d %d  dir %d/   %d   count : %d\n", A, i, j,ball.x, ball.y, ball.dir, d, point);
						if (point >= max) max = point;

						//      xx++;
					}// while
					 // 최대값 확인해주기
				}
			}
		}
	}

	ans = max;
}

int main() {
	int ts;
	scanf("%d", &ts);

	for (int t = 1; t <= ts; t++) {
		// hole 초기화 ?? 
		ans = 0;
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] > 5 && map[i][j] < 11) { // 웜홀이면
					if (hole[map[i][j] - 6][0].exist == 1) {
						//두번째 홀에 집어넣기
						hole[map[i][j] - 6][1].x = i;
						hole[map[i][j] - 6][1].y = j;
						hole[map[i][j] - 6][1].y = j;
					}
					else {
						//첫번째 홀에 집어넣기
						hole[map[i][j] - 6][0].x = i;
						hole[map[i][j] - 6][0].y = j;
						hole[map[i][j] - 6][0].exist = 1;
					}
				}
				//   printf("?\n");
			}
		}
		// 함수
		//printf("ff\n");


		solve();

		printf("#%d %d\n", t, ans);

		for (int a = 0; a < 5; a++) {
			//   printf("1. %d %d  2. %d %d\n", hole[a][0].x, hole[a][0].y, hole[a][1].x, hole[a][1].y);
			hole[a][0].x = 0;
			hole[a][0].y = 0;
			hole[a][1].x = 0;
			hole[a][1].y = 0;
			hole[a][0].exist = 0;
		}
		for (int i = 0; i < N+1; i++)
			for (int j = 0; j < N+1; j++)
				map[i][j] = 0;


	}

	//printf("%d\n", xx);
	return 0;

}

/*
1
6
1 1 1 1 1 1
1 1 -1 1 1 1
1 -1 0 -1 1 1
1 1 -1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
*/