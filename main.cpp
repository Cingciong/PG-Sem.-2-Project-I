#include <iostream>     // std::cout, std::endl
#include <stdlib.h>     /* rand srand */
#include <time.h>       /* time */
#include <cmath>
#include <iomanip>      // std::setw


struct point{
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

//int left=0, right=1, up=2, down=3;

void randomPoints( int board[40][20]){

    bool exit=false;
    while(!exit){
        srand (time(NULL));
        for (int i = 0; i < 40; ++i) {
            for (int j = 0; j < 20; ++j) {
                if(board[i][j]==0){
                    if(200 == std::rand() % 400){
                        start.y=j;
                        start.x=i;
                        exit=true;
                    }
                }
            }
        }
    }
    exit=false;
    while(!exit){
        for (int i = 0; i < 40; ++i) {
            for (int j = 0; j < 20; ++j) {
                if(board[i][j]==0){
                    if(200 == std::rand() % 400){
                        end.y=j;
                        end.x=i;
                        exit=true;
                    }
                }
            }
        }
    }
    std::cout<<start.x<<" "<<start.y<<" ";
    std::cout<<board[start.y][start.x]<<"\n";
    std::cout<<end.x<<" "<<end.y<<" ";
    std::cout<<board[end.y][end.x]<<"\n";
}
void showBoard(int board[40][20], point start, point end){
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (board[i][j] ==1 ){
                std::cout<<char(254)<<" ";
            } else {
                if(start.x==i and start.y==j or end.x==i and end.y==j){
                    if (start.x==i and start.y==j ){
                        std::cout<<"S ";
                    }
                    if (end.x==i and end.y==j ){
                        std::cout<<"E ";
                    }
                }else {
                    if (board[i][j] ==0){
                        std::cout<<"."<<" ";
                    }
                }



            }
        }
        std::cout<<'\n';
    }
}
int generatingBoard(int board[40][20]) {

    //declaration of variables .
    int rand;

    //every segment mentioned in task is saved to array.
    int segments[6][5][5] = {
     {{1,1,0,1,1},{1,0,0,1,1},{0,0,1,0,0},{1,0,0,0,1},{1,1,0,1,1}}
    ,{{1,1,0,0,1},{0,1,1,0,1},{0,0,0,0,0},{1,0,0,0,1},{1,1,0,0,1}}
    ,{{0,0,0,0,0},{0,0,1,0,0},{0,0,1,1,0},{1,0,1,1,1},{1,0,0,0,0}}
    ,{{1,1,0,0,0},{1,0,0,1,0},{0,0,1,0,0},{0,1,0,0,1},{1,0,0,1,1}}
    ,{{0,0,0,1,1},{1,0,0,0,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,1}}
    ,{{1,1,0,1,1},{1,1,0,1,1},{0,0,0,0,0},{1,1,0,1,1},{1,1,0,1,1}}
    };

    // 4 loops save randomly chosen segments into board array
    srand (time(NULL));

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; ++j) {
            rand = std::rand() % 6;
            for (int k = 0; k < 5; ++k) {
                for (int l = 0; l < 5; ++l) {
                    //control cout.
                    //std::cout<<i*5+k<<" "<<i*5+k<<" -- "<< k<<" "<<l<<" = "<<segments[rand][k][l]<<"\n";
                    board[i*5+k][j*5+l] = segments[rand][k][l];
                }
            }
        }
    }
    return **board;
};
void creatingMap(node map[40][20], int board[40][20]){
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 20; ++j) {
            if(board[i][j]==0){
                map[i][j].x=j;
                map[i][j].y=i;
                map[i][j].isWall=false;
            }
            if (board[i][j]==1){
                map[i][j].x=j;
                map[i][j].y=i;
                map[i][j].isWall=true;
            }
        }
    }

    int dr[] = {-1,1,0,0};
    int dc[] = {0,0,1,-1};
    int rr,cc;

    //relating nodes
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 20; ++j) {
            if(board[i][j]==0) {
                map[i][j].howManyNeighbours=0;
                for (int k = 0; k < 4; ++k) {
                    rr = i + dr[k];
                    cc = j + dc[k];
                    if(!(rr<0 or cc<0 or cc>=20 or rr>=40 or map[rr][cc].isWall)){
                        map[i][j].neighbours[k] = &map[rr][cc];
                        map[i][j].howManyNeighbours++;
                        //std::cout<<rr<<" "<<cc<<"\n";
                    }else{
                        map[i][j].neighbours[k]= nullptr;
                        //std::cout<<"isWall: "<<map[rr][cc].isWall;
                        //std::cout<<" nullptr "<<rr<<" "<<cc<<"\n";
                    };




                }

            }
        }
    }
}
void showRelation(node map[40][20]){
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 20; ++j) {
            if(!(map[i][j].isWall==true)){
                std::cout<<"coridinates: "<<map[i][j].x<<", "<<map[i][j].y<<";\n";
                std::cout<<"how many neighbours: "<< map[i][j].howManyNeighbours<<";\n coridinates x,y of neighbours: \n";
                for (int k = 0; k < 4; ++k) {
                    if(!(map[i][j].neighbours[k]== nullptr)){
                        std::cout<<"    "<<map[i][j].neighbours[k]->x<<", "<<map[i][j].neighbours[k]->y;
                    }

                }
                std::cout<<"\n\n\n";
            }

        }

    }

}
//void deleteMap(node map[40][20]){
//    for (int i = 0; i < 40; ++i) {
//        for (int j = 0; j < 20; ++j) {
//            delete map[i][j];
//        }
//    }
//};

//int howManyZeros(int board[40][20]){
//    int howManyZeros;
//    for (int i = 0; i < 40; ++i) {
//
//        for (int j = 0; j < 20; ++j) {
//            if(board==0){
//                howManyZeros++;
//            }
//        }
//
//    }
//    std::cout<<howManyZeros;
//    return howManyZeros;
//}
//int getValue(int x, int y, int board[40][20]){
//    int value=0;
//    for (int i = 0; i < 40; ++i) {
//        for (int j = 0; j < 20; ++j) {
//            if(board[i][j]==0) value++;
//            if (i==y and j==x) {
//                return value;
//            }
//        }
//    }
//    return value;
//}

int main() {
    node map[40][20];
    int board[40][20];
    **board = generatingBoard(board);

    randomPoints(board);
    //creating board


    showBoard(board, start, end);

    //creating map
    creatingMap(map, board);
    //showRelation(map);

   //deleteMap(map); (woriking in process)






    return 0;
}
