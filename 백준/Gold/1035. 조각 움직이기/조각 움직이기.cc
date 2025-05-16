#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 987654321

typedef struct {
    int x, y;
} Point;

Point stars[5];
int scnt;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int visited[5][5];
Point comb[5];
int comb_cnt;
int answer = INF;

int queue_x[25], queue_y[25];

int abs_dist(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void swap(Point* a, Point* b) {
    Point tmp = *a;
    *a = *b;
    *b = tmp;
}

int next_permutation(int* arr, int n) {
    int i = n - 1;
    while (i > 0 && arr[i - 1] >= arr[i]) i--;
    if (i == 0) return 0;
    int j = n - 1;
    while (arr[i - 1] >= arr[j]) j--;
    int tmp = arr[i - 1]; arr[i - 1] = arr[j]; arr[j] = tmp;
    j = n - 1;
    while (i < j) {
        tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        i++; j--;
    }
    return 1;
}

int is_connected(Point* list) {
    int front = 0, rear = 0, cnt = 1;
    int vis[5][5] = {0};
    queue_x[rear] = list[0].x;
    queue_y[rear++] = list[0].y;
    vis[list[0].x][list[0].y] = 1;

    while (front < rear) {
        int x = queue_x[front];
        int y = queue_y[front++];
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            for (int i = 0; i < scnt; i++) {
                if (list[i].x == nx && list[i].y == ny && !vis[nx][ny]) {
                    vis[nx][ny] = 1;
                    queue_x[rear] = nx;
                    queue_y[rear++] = ny;
                    cnt++;
                }
            }
        }
    }

    return cnt == scnt;
}

void test_comb(Point* comb) {
    if (!is_connected(comb)) return;

    int idx[5] = {0, 1, 2, 3, 4};
    int min_sum = INF;
    do {
        int sum = 0;
        for (int i = 0; i < scnt; i++)
            sum += abs_dist(stars[i], comb[idx[i]]);
        if (sum < min_sum)
            min_sum = sum;
    } while (next_permutation(idx, scnt));

    if (min_sum < answer)
        answer = min_sum;
}

void make_comb(int pos, int cnt) {
    if (cnt == scnt) {
        test_comb(comb);
        return;
    }
    for (int i = pos; i < 25; i++) {
        comb[cnt].x = i / 5;
        comb[cnt].y = i % 5;
        make_comb(i + 1, cnt + 1);
    }
}

int main() {
    char line[6];
    for (int i = 0; i < 5; i++) {
        scanf("%s", line);
        for (int j = 0; j < 5; j++) {
            if (line[j] == '*') {
                stars[scnt].x = i;
                stars[scnt].y = j;
                scnt++;
            }
        }
    }

    make_comb(0, 0);
    printf("%d\n", answer);
    return 0;
}
