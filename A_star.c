#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROW 5
#define COL 5

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point parent;
    int f, g, h;
    int is_closed;
    int is_open;
} Cell;

int isValid(int grid[ROW][COL], int x, int y) {
    return (x >= 0 && x < ROW && y >= 0 && y < COL && grid[x][y] == 0);
}

int isDestination(int x, int y, Point dest) {
    return (x == dest.x && y == dest.y);
}

int calculateH(int x, int y, Point dest) {
    return abs(x - dest.x) + abs(y - dest.y);
}

void tracePath(Cell cellDetails[ROW][COL], Point dest) {
    printf("Path: ");
    Point p = dest;
    while (!(cellDetails[p.x][p.y].parent.x == p.x && cellDetails[p.x][p.y].parent.y == p.y)) {
        printf("(%d,%d) <- ", p.x, p.y);
        p = cellDetails[p.x][p.y].parent;
    }
    printf("(%d,%d)\n", p.x, p.y);
}

void aStarSearch(int grid[ROW][COL], Point start, Point dest) {
    if (!isValid(grid, start.x, start.y) || !isValid(grid, dest.x, dest.y)) {
        printf("Invalid start or destination\n");
        return;
    }

    Cell cellDetails[ROW][COL];

    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++) {
            cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h = 0;
            cellDetails[i][j].is_closed = 0;
            cellDetails[i][j].is_open = 0;
            cellDetails[i][j].parent = (Point){-1, -1};
        }

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    int openCount = 0;
    Point openList[ROW * COL];
    openList[openCount++] = start;
    cellDetails[start.x][start.y].f = 0;
    cellDetails[start.x][start.y].g = 0;
    cellDetails[start.x][start.y].h = 0;
    cellDetails[start.x][start.y].parent = start;
    cellDetails[start.x][start.y].is_open = 1;

    while (openCount > 0) {
        int lowest = 0;
        for (int i = 1; i < openCount; i++) {
            Point p1 = openList[i];
            Point p2 = openList[lowest];
            if (cellDetails[p1.x][p1.y].f < cellDetails[p2.x][p2.y].f)
                lowest = i;
        }

        Point current = openList[lowest];
        openList[lowest] = openList[--openCount];
        cellDetails[current.x][current.y].is_closed = 1;

        if (isDestination(current.x, current.y, dest)) {
            tracePath(cellDetails, dest);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isValid(grid, nx, ny) && !cellDetails[nx][ny].is_closed) {
                int gNew = cellDetails[current.x][current.y].g + 1;
                int hNew = calculateH(nx, ny, dest);
                int fNew = gNew + hNew;

                if (!cellDetails[nx][ny].is_open || fNew < cellDetails[nx][ny].f) {
                    openList[openCount++] = (Point){nx, ny};
                    cellDetails[nx][ny].f = fNew;
                    cellDetails[nx][ny].g = gNew;
                    cellDetails[nx][ny].h = hNew;
                    cellDetails[nx][ny].parent = current;
                    cellDetails[nx][ny].is_open = 1;
                }
            }
        }
    }

    printf("No path found\n");
}

int main() {
    int grid[ROW][COL] = {
        { 0, 1, 0, 0, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0 }
    };

    Point start = {0, 0};
    Point dest = {4, 4};

    aStarSearch(grid, start, dest);

    return 0;
}
