#include <iostream>     // std::cout, std::endl
#include <stdlib.h>
#include <time.h>       /* time */


void generatingBoard() {

    //declaration of variables .
    int rand;
    int board[40][20];
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
            std::cout<<rand<<"\n";
            for (int k = 0; k < 5; ++k) {
                for (int l = 0; l < 5; ++l) {
                    //control cout.
                    //std::cout<<i*5+k<<" "<<i*5+k<<" -- "<< k<<" "<<l<<" = "<<segments[rand][k][l]<<"\n";
                    board[i*5+k][j*5+l] = segments[rand][k][l];
                }
            }
        }
    }



        for (int i = 0; i < 40; ++i) {
            if(i%5==0) std::cout<<"\n"<<"------------------------------------------------------"<<"\n";
            for (int j = 0; j < 20; ++j) {
                if(j%5==0) std::cout<<" | ";
                if (board[i][j] ==1 ){
                    std::cout<<char(254)<<" ";
                } else std::cout<<" "<<" ";
            }

            std::cout<<'\n';
        }







};


int main() {

    std::cout << "Hello, aaaaWorld!" << std::endl;
    generatingBoard();
    return 0;
}
