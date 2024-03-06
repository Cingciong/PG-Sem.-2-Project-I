#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//global variables
struct point {
    int x;
    int y;
};
struct node {
    int x;
    int y;
    node* parent;
    node* neighbours[4]{nullptr};
    int howManyNeighbours;
    bool visited;
    bool isWall;
};
point start;
point end;
node map[40][20];
int board[40][20];

//declaration
void randomPoints(int board[40][20]);
void showBoard(int board[40][20], point start, point end);
int generatingBoard(int board[40][20]);
void creatingMap(node map[40][20], int board[40][20]);
void printPath(node* endNode);
bool bfsIterative(node map[40][20], point start, point end);
void printPath(node* endNode);
void printMapWithQueue(node map[][20], int rows, int cols, point start, point end, node* current, node* queue[], int front, int rear);
void printFinalPath(node map[40][20], point start, point end);

//MAIN
int main() {

    std::cout<<"BFS searching algorithm PG Project I sem. 2 \n Project made by Karolina Wajszczuk and Igor Maciejak \n 198009 and 197838 respectively \n from ACiR 2\n---------------------------------\n";
    system("pause");

        **board = generatingBoard(board);
        randomPoints(board);
        showBoard(board, start, end);
        creatingMap(map, board);

        if (!bfsIterative(map, start, end)) {
            std::cout << "no path found" << std::endl;
        } else {
            printFinalPath(map, start, end);
        }


    return 0;
}

//definition
void creatingMap(node map[40][20], int board[40][20]) {
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (board[i][j] == 0) {
                map[i][j].x = j;
                map[i][j].y = i;
                map[i][j].isWall = false;
            }
            if (board[i][j] == 1) {
                map[i][j].x = j;
                map[i][j].y = i;
                map[i][j].isWall = true;
            }
        }
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    int rr, cc;

    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (board[i][j] == 0) {
                map[i][j].howManyNeighbours = 0;
                for (int k = 0; k < 4; ++k) {
                    rr = i + dr[k];
                    cc = j + dc[k];
                    if (!(rr < 0 or cc < 0 or cc >= 20 or rr >= 40 or map[rr][cc].isWall)) {
                        map[i][j].neighbours[k] = &map[rr][cc];
                        map[i][j].howManyNeighbours++;
                    } else {
                        map[i][j].neighbours[k] = nullptr;
                    };
                }
            }
        }
    }
}

bool bfsIterative(node map[40][20], point start, point end) {
    const int rows = 40;
    const int cols = 20;

    node* queue[rows * cols];
    int front = 0, rear = 0;

    node* startNode = &map[start.x][start.y];
    startNode->visited = true;
    queue[rear++] = startNode;

    while (front != rear) {
        node* current = queue[front++];

        //std::cout << "Current Node: (" << current->y << ", " << current->x << ")" << std::endl;

        if (current->x == end.y && current->y == end.x) {
            std::cout << "Path found:" << std::endl;
            printPath(current);
            break;  // Stop the loop when the path is found
        }

        //for debugging
        //printMapWithQueue(map, rows, cols, start, end, current, queue, front, rear);

        for (int i = 0; i < 4; ++i) {
            node* neighbour = current->neighbours[i];
            if (neighbour != nullptr && !neighbour->visited) {
                neighbour->visited = true;
                neighbour->parent = current;
                queue[rear++] = neighbour;
            }
        }
    }

    return true;
}

void printPath(node* endNode) {
    int counter=0;
    while (endNode != nullptr) {
        std::cout << "(" << endNode->x << ", " << endNode->y << ") ";
        endNode = endNode->parent;
        counter++;
    }

    std::cout <<"counter: " <<counter<< std::endl;
}

void printFinalPath(node map[40][20], point start, point end) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Use a separate boolean array to mark the path
    bool pathMarked[40][20] = {false};

    node* current = &map[end.x][end.y];

    while (current != nullptr) {
        pathMarked[current->y][current->x] = true; // Mark the path
        current = current->parent;
    }


    std::cout<<"\n";

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 40; ++j) {

            if (!pathMarked[j][i])
                if (map[j][i].isWall) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                    std::cout << "# ";
                } else {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                    std::cout << ". ";
                }
            else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                std::cout << char(254) << " ";
            }
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
}

void randomPoints(int (*board)[20]) {
    bool startSet = false;
    bool endSet = false;

    srand(time(NULL));

    while (!startSet || !endSet) {
        int randX = std::rand() % 40;
        int randY = std::rand() % 20;

        if (board[randX][randY] == 0) {
            if (!startSet) {
                start.x = randX;
                start.y = randY;
                startSet = true;
            } else if (!endSet) {
                end.x = randX;
                end.y = randY;
                endSet = true;
            }
        }
    }

    std::cout << "Start: (" << start.x << ", " << start.y << "), End: (" << end.x << ", " << end.y<<")\n";
}

void showBoard(int (*board)[20], point start, point end) {
    for (int i = 0; i < 20; ++i) {  // Change the loop limit to 20 for height
        for (int j = 0; j < 40; ++j) {  // Change the loop limit to 40 for width
            if (board[j][i] == 1) {  // Swap indices to access elements correctly
                std::cout << " "
                          << char(254);
            } else {
                if (start.x == j and start.y == i or end.x == j and end.y == i) {  // Swap indices for start and end points
                    if (start.x == j and start.y == i) {
                        std::cout << " S";
                    }
                    if (end.x == j and end.y == i) {
                        std::cout << " E";
                    }
                } else {
                    if (board[j][i] == 0) {  // Swap indices for the board
                        std::cout << " .";
                    }
                }
            }
        }
        std::cout << '\n';
    }
}

int generatingBoard(int (*board)[20]) {
    int rand;

    int segments[6][5][5] = {
            {{1, 1, 0, 1, 1}, {1, 0, 0, 1, 1}, {0, 0, 1, 0, 0}, {1, 0, 0, 0, 1}, {1, 1, 0, 1, 1}},
            {{1, 1, 0, 0, 1}, {0, 1, 1, 0, 1}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 1}, {1, 1, 0, 0, 1}},
            {{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 1, 1, 0}, {1, 0, 1, 1, 1}, {1, 0, 0, 0, 0}},
            {{1, 1, 0, 0, 0}, {1, 0, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 1, 0, 0, 1}, {1, 0, 0, 1, 1}},
            {{0, 0, 0, 1, 1}, {1, 0, 0, 0, 1}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 1}},
            {{1, 1, 0, 1, 1}, {1, 1, 0, 1, 1}, {0, 0, 0, 0, 0}, {1, 1, 0, 1, 1}, {1, 1, 0, 1, 1}},
    };

    srand(time(NULL));

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; ++j) {
            rand = std::rand() % 6;
            for (int k = 0; k < 5; ++k) {
                for (int l = 0; l < 5; ++l) {
                    board[i * 5 + k][j * 5 + l] = segments[rand][k][l];
                }
            }
        }
    }
    return **board;
}

//for debugging
void printMapWithQueue(node map[][20], int rows, int cols, point start, point end, node* current, node* queue[], int front, int rear) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == start.x && j == start.y) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                std::cout << "S ";
            } else if (i == end.x && j == end.y) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                std::cout << "E ";
            } else if (map[i][j].visited) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                std::cout << "V ";
            } else if (map[i][j].isWall) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                std::cout << "# ";
            } else {
                // Highlight the current node in the queue with blue
                bool isCurrentNode = false;
                for (int k = front; k < rear; ++k) {
                    if (queue[k]->x == i && queue[k]->y == j) {
                        isCurrentNode = true;
                        break;
                    }
                }

                if (isCurrentNode) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                    std::cout << ". ";
                } else {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
                    std::cout << ". ";
                }
            }
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
        }
        std::cout << std::endl;
    }
}