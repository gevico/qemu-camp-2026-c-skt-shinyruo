#include <stdio.h>

#define N 5

struct Point {
	int r, c;
};

int maze[N][N] = {
	{0, 1, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0},
};

int main(void)
{
	struct Point queue[N * N];   /* 队列 */
	struct Point parent[N][N];   /* 每个格子的前驱 */
	int front = 0, rear = 0;

	/* 起点入队 */
	queue[rear++] = (struct Point){0, 0};
	maze[0][0] = 2;
	parent[0][0] = (struct Point){-1, -1};

	/* BFS */
	int dr[] = {-1, 1, 0, 0};
	int dc[] = {0, 0, -1, 1};

	while (front < rear) {
		struct Point cur = queue[front++];

		if (cur.r == N - 1 && cur.c == N - 1)
			break;

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			if (nr >= 0 && nr < N && nc >= 0 && nc < N && maze[nr][nc] == 0) {
				maze[nr][nc] = 2;
				parent[nr][nc] = cur;
				queue[rear++] = (struct Point){nr, nc};
			}
		}
	}

	/* 从终点沿 parent 回溯，收集路径 */
	struct Point path[N * N];
	int len = 0;
	struct Point p = {N - 1, N - 1};
	while (p.r != -1) {
		path[len++] = p;
		p = parent[p.r][p.c];
	}

	/* 打印路径 */
	for (int i = 0; i < len; i++)
		printf("(%d, %d)\n", path[i].r, path[i].c);

	return 0;
}