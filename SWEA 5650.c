#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
20190305 SWEA 5650 �ɺ�����
��Ȧ 6~10
ũ�� N 5~100
��Ȧ -1 / �ִ� 5��
��Ȧ�� �ݵ�� �ִ� 5��
��Ȧ, ��Ȧ �������� �ʴ� ��쵵 ����
��Ȧ ����� ������� ����
�� ���, �� ������ ������ �ٲ�
��� ��� ������ ����
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
	//dir �������� �԰�, A ���� �϶�
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
	// �ִ� ���� return
	// �ɺ��� ��� 0�ڸ�, 4���⿡�� �� ������
	// ���� �ٲ�� ���� 1. ��, ��������� - ���ݴ� 2.���� - ���� 3. ��Ȧ - ��ȣ���� �ٸ� ��Ȧ, ���� ����
	// �����ϴ� ����  - ��Ȧ, ��� ��ġ ���ƿ�
	// ������ ��, ��Ͽ� �ε��� Ƚ�� 
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == 0) {
				for (int d = 0; d < 4; d++) { // 4���⿡ ���ؼ�
					ball.x = i;
					ball.y = j;
					ball.dir = d;
					point = 0;
					// ���� ���� 
					while (1) {
						// �̵�����
						if (ball.dir == 0) { // ��
							ball.x = ball.x - 1;
						}
						else if (ball.dir == 1) {// ����
							ball.y = ball.y + 1;
						}
						else if (ball.dir == 2) {// �Ʒ�
							ball.x = ball.x + 1;
						}
						else {// ball.dir == 3 ��
							ball.y = ball.y - 1;
						}
						// �ϴ� �̵����� ���� �̵�
						int A = map[ball.x][ball.y];

						//1. 
						//if (ball.x < 0 || ball.y < 0 || ball.x >= N || ball.y >= N) break;
						//2. �̵� �Ѱ��� ó�� ��ġ �Ǵ� ��Ȧ �̸� break;
						if (A == -1 || (ball.x == i && ball.y == j)) break;
						// 4. �簢���̳� �� ������ ���� �ݴ��
						if (ball.x == 0 || ball.y == 0 || ball.x > N || ball.y > N || A == 5) {
							ball.dir = ops(ball.dir);
							point++; // ������� ���� ���� 
						}

						// if (ball.x == i && ball.y == j) break;
						//3. ��Ȧ ������ ¦ ��Ȧ�� �̵�, �̵����� ����
						if (A> 5) {
							if (hole[A - 6][0].x == ball.x && hole[A - 6][0].y == ball.y) {
								//   printf("e����\n");
								ball.x = hole[A - 6][1].x;
								ball.y = hole[A - 6][1].y;
							}
							else {
								ball.x = hole[A - 6][0].x;
								ball.y = hole[A - 6][0].y;
							}
							//   printf("��Ȧ\n");
						} // ��Ȧ �̵�

						  // 5. ����� ������ ���� �ݴ� �Ǵ� ���� ����
						if (A > 0 && A < 5) {
							// �ﰢ�� ���� ������ 
							ball.dir = func(ball.dir, A);
							point++;
						}
				//		printf("A %d , %d %d x,y   %d %d  dir %d/   %d   count : %d\n", A, i, j,ball.x, ball.y, ball.dir, d, point);
						if (point >= max) max = point;

						//      xx++;
					}// while
					 // �ִ밪 Ȯ�����ֱ�
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
		// hole �ʱ�ȭ ?? 
		ans = 0;
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] > 5 && map[i][j] < 11) { // ��Ȧ�̸�
					if (hole[map[i][j] - 6][0].exist == 1) {
						//�ι�° Ȧ�� ����ֱ�
						hole[map[i][j] - 6][1].x = i;
						hole[map[i][j] - 6][1].y = j;
						hole[map[i][j] - 6][1].y = j;
					}
					else {
						//ù��° Ȧ�� ����ֱ�
						hole[map[i][j] - 6][0].x = i;
						hole[map[i][j] - 6][0].y = j;
						hole[map[i][j] - 6][0].exist = 1;
					}
				}
				//   printf("?\n");
			}
		}
		// �Լ�
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