#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

struct Point {
    int row;
    int col;
};

struct Point stack[MAX_ROW * MAX_COL];
int stack_top = -1;

void push(int row, int col) { stack[++stack_top] = (struct Point){row, col}; }
struct Point pop(void) { return stack[stack_top--]; }
struct Point peek(void) { return stack[stack_top]; }
int is_empty(void) { return stack_top == -1; }

int main(void) {
    int dr[] = {1, -1, 0, 0};  // 下、上、右、左
    int dc[] = {0, 0, 1, -1};
    int visited[MAX_ROW][MAX_COL] = {0};

    push(0, 0);
    visited[0][0] = 1;

    while (!is_empty()) {
        struct Point curr = peek();
        if (curr.row == MAX_ROW - 1 && curr.col == MAX_COL - 1) {
            while (!is_empty()) {
                struct Point p = pop();
                printf("(%d, %d)\n", p.row, p.col);
            }
            return 0;
        }

        int moved = 0;
        for (int i = 0; i < 4; i++) {
            int nr = curr.row + dr[i];
            int nc = curr.col + dc[i];
            if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL && !visited[nr][nc] && maze[nr][nc] == 0) {
                push(nr, nc);
                visited[nr][nc] = 1;
                moved = 1;
                break;
            }
        }
        if (!moved) pop();
    }

    printf("No path!\n");
    return 0;
}