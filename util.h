#include <iostream>
#include <vector>

#define lineH 196
#define lineV 179
#define lineBlank 32

using namespace std;

bool addMove(string move, struct Node *n);
void playerPoints(struct Node *n, char player);
int checkNewBoxes(string move, struct Graph *g, struct Node *n);
bool checkWinner(struct Node *n);
bool checkWinnerMM(struct Node *n);
void playerPointsMM(struct Node *n, char player);
int minimaxWrapper(struct Node n, struct Graph g);
void bestMoveLabelMM(int bestMoveI, int bestMoveJ, struct Graph *g);
int minimaxRec(string testMove, struct Node *n, struct Graph *g, int depth, bool isMaximizer);
int checkNewBoxesMM(string testMove, struct Graph *g, struct Node *n);


struct Graph
{
    char h[4][3] = {32,32,32,32,32,32,32,32,32,32,32,32};
    char v[3][4] = {32,32,32,32,32,32,32,32,32,32,32,32};
    char box[3][3] = {32,32,32,32,32,32,32,32,32};

    // for picking best move from Minimax algorithm
    string hLabel[4][3] = {
                            {"h1","h2","h3"},
                            {"h4","h5","h6"},
                            {"h7","h8","h9"},
                            {"h10","h11","h12"}
                        };
    string vLabel[3][4] = { {"v1","v2","v3","v4"},
                            {"v5","v6","v7","v8"},
                            {"v9","v10","v11","v12"}
                        };

    int moveX, moveY, moveYv;
    string bestMove = "@@@@@@@@";
    char HorV;
};

struct Node
{
    Graph nodeGraph;
    int utility = 0;

    char player = '\0'; // 1 or 2
    char p1 = '\0'; // 'letter'
    char p2 = '\0'; // 'letter'
    int p1Count = 0;
    int p2Count = 0;
    int gameFull = 0; // should be 24
    char winner = '\0';

    char player_MM = '\0'; // 1 or 2
    int p1Count_MM = 0;
    int p2Count_MM = 0;
    int gameFull_MM = 0; // should be 24
    char winner_MM = '\0';

    vector<Node *> childrenH;
    vector<Node *> childrenV;
};

void printGraph(struct Graph g)
{
    for (int i = 0; i < 4; i++)
    {
        cout<<"."<<g.h[i][0]<<g.h[i][0]<<g.h[i][0]<<"."<<g.h[i][1]<<g.h[i][1]<<g.h[i][1]<<"."<<g.h[i][2]<<g.h[i][2]<<g.h[i][2]<<".\n";
        if(i==3)break;
        cout<<g.v[i][0]<<" "<<g.box[i][0]<<" "<<g.v[i][1]<<" "<<g.box[i][1]<<" "<<g.v[i][2]<<" "<<g.box[i][2]<<" "<<g.v[i][3]<<"\n";
    }
}

bool addMove(string move, struct Node *n) {
    if (move == "h1" && n->nodeGraph.h[0][0] == lineBlank) {                 // check for horizontal moves
         n->nodeGraph.h[0][0] = lineH;
         n->nodeGraph.moveX = 0;
         n->nodeGraph.moveY = 0;
         n->gameFull++;
      } else if (move == "h2" && n->nodeGraph.h[0][1] == lineBlank) {
         n->nodeGraph.h[0][1] = lineH;
         n->nodeGraph.moveX = 0;
         n->nodeGraph.moveY = 1;
         n->gameFull++;
      } else if (move == "h3" && n->nodeGraph.h[0][2] == lineBlank) {
         n->nodeGraph.h[0][2] = lineH;
         n->nodeGraph.moveX = 0;
         n->nodeGraph.moveY = 2;
         n->gameFull++;
      } else if (move == "h4" && n->nodeGraph.h[1][0] == lineBlank) {
         n->nodeGraph.h[1][0] = lineH;
         n->nodeGraph.moveX = 1;
         n->nodeGraph.moveY = 0;
         n->gameFull++;
      } else if (move == "h5" && n->nodeGraph.h[1][1] == lineBlank) {
         n->nodeGraph.h[1][1] = lineH;
         n->nodeGraph.moveX = 1;
         n->nodeGraph.moveY = 1;
         n->gameFull++;
      } else if (move == "h6" && n->nodeGraph.h[1][2] == lineBlank) {
         n->nodeGraph.h[1][2] = lineH;
         n->nodeGraph.moveX = 1;
         n->nodeGraph.moveY = 2;
         n->gameFull++;
      } else if (move == "h7" && n->nodeGraph.h[2][0] == lineBlank) {
         n->nodeGraph.h[2][0] = lineH;
         n->nodeGraph.moveX = 2;
         n->nodeGraph.moveY = 0;
         n->gameFull++;
      } else if (move == "h8" && n->nodeGraph.h[2][1] == lineBlank) {
         n->nodeGraph.h[2][1] = lineH;
         n->nodeGraph.moveX = 2;
         n->nodeGraph.moveY = 1;
         n->gameFull++;
      } else if (move == "h9" && n->nodeGraph.h[2][2] == lineBlank) {
         n->nodeGraph.h[2][2] = lineH;
         n->nodeGraph.moveX = 2;
         n->nodeGraph.moveY = 2;
         n->gameFull++;
      } else if (move == "h10" && n->nodeGraph.h[3][0] == lineBlank) {
         n->nodeGraph.h[3][0] = lineH;
         n->nodeGraph.moveX = 3;
         n->nodeGraph.moveY = 0;
         n->gameFull++;
      } else if (move == "h11" && n->nodeGraph.h[3][1] == lineBlank) {
         n->nodeGraph.h[3][1] = lineH;
         n->nodeGraph.moveX = 3;
         n->nodeGraph.moveY = 1;
         n->gameFull++;
      } else if (move == "h12" && n->nodeGraph.h[3][2] == lineBlank) {                  
         n->nodeGraph.h[3][2] = lineH;
         n->nodeGraph.moveX = 3;
         n->nodeGraph.moveY = 2;
         n->gameFull++;
      } else if (move == "v1" && n->nodeGraph.v[0][0] == lineBlank) {        // check for vertical moves
         n->nodeGraph.v[0][0] = lineV;
         n->nodeGraph.moveX = 0;
         n->nodeGraph.moveY = 0;
         n->gameFull++;
      } else if (move == "v2" && n->nodeGraph.v[0][1] == lineBlank) {
         n->nodeGraph.v[0][1] = lineV;
         n->nodeGraph.moveX = 0;
         n->nodeGraph.moveY = 1;
         n->gameFull++;
      } else if (move == "v3" && n->nodeGraph.v[0][2] == lineBlank) {
         n->nodeGraph.v[0][2] = lineV;
         n->nodeGraph.moveX = 0;
         n->nodeGraph.moveY = 2;
         n->gameFull++;
      } else if (move == "v4" && n->nodeGraph.v[0][3] == lineBlank) {
         n->nodeGraph.v[0][3] = lineV;
         n->nodeGraph.moveX = 0;
         n->nodeGraph.moveY = 3;
         n->gameFull++;
      } else if (move == "v5" && n->nodeGraph.v[1][0] == lineBlank) {        // check for vertical moves
         n->nodeGraph.v[1][0] = lineV;
         n->nodeGraph.moveX = 1;
         n->nodeGraph.moveY = 0;
         n->gameFull++;
      } else if (move == "v6" && n->nodeGraph.v[1][1] == lineBlank) {
         n->nodeGraph.v[1][1] = lineV;
         n->nodeGraph.moveX = 1;
         n->nodeGraph.moveY = 1;
         n->gameFull++;
      } else if (move == "v7" && n->nodeGraph.v[1][2] == lineBlank) {
         n->nodeGraph.v[1][2] = lineV;
         n->nodeGraph.moveX = 1;
         n->nodeGraph.moveY = 2;
         n->gameFull++;
      } else if (move == "v8" && n->nodeGraph.v[1][3] == lineBlank) {
         n->nodeGraph.v[1][3] = lineV;
         n->nodeGraph.moveX = 1;
         n->nodeGraph.moveY = 3;
         n->gameFull++;
      } else if (move == "v9" && n->nodeGraph.v[2][0] == lineBlank) {        // check for vertical moves
         n->nodeGraph.v[2][0] = lineV;
         n->nodeGraph.moveX = 2;
         n->nodeGraph.moveY = 0;
         n->gameFull++;
      } else if (move == "v10" && n->nodeGraph.v[2][1] == lineBlank) {
         n->nodeGraph.v[2][1] = lineV;
         n->nodeGraph.moveX = 2;
         n->nodeGraph.moveY = 1;
         n->gameFull++;
      } else if (move == "v11" && n->nodeGraph.v[2][2] == lineBlank) {
         n->nodeGraph.v[2][2] = lineV;
         n->nodeGraph.moveX = 2;
         n->nodeGraph.moveY = 2;
         n->gameFull++;
      } else if (move == "v12" && n->nodeGraph.v[2][3] == lineBlank) {
         n->nodeGraph.v[2][3] = lineV;
         n->nodeGraph.moveX = 2;
         n->nodeGraph.moveY = 3;
         n->gameFull++;
      } else {
         cout << "Move not on map or move already exists" << endl << endl;
         return false; // move was not able to be added
      }
      return true; // move was added
}
void playerPoints(struct Node *n, char player) {
    if (player == n->p1) {
        n->p1Count++;
    } else {
        n->p2Count++;
    }
}
int checkNewBoxes(string move, struct Graph *g, struct Node *n, char player)
{
    int i, j;

    cout << "X" << g->moveX << endl;
    cout << "Y" << g->moveY << endl;
    i = g->moveX;
    j = g->moveY;

    // vivien**** returns 1 if box found, else 0 
    if (move.at(0) == 'v')
    {
        if (j == 0)//first column
        {
            if (g->h[i][j] != 32 && g->v[i][j+1] != 32 && g->h[i+1][j] != 32)
            {
                // accumulate box points for corresponding player
                playerPoints(n, player);

                n->player = player;
                g->box[i][j] = player;
                return 1;
            }
            else return 0;
        }

        else if (j == 1 || j == 2)//2nd or 3rd column
        { 
            if ((g->h[i][j-1] != 32 && g->h[i+1][j-1] != 32 && g->v[i][j-1] != 32) || (g->h[i+1][j] != 32 && g->h[i][j] != 32 && g->v[i][j+1] != 32))
            {
                int k = 0;
                if (g->h[i][j-1] != 32 && g->h[i+1][j-1] != 32 && g->v[i][j-1] != 32)
                {   
                    // accumulate box points for corresponding player
                    playerPoints(n, player);

                    n->player = player;
                    g->box[i][j-1] = player;
                    k++;
                }//left box

                if (g->h[i+1][j] != 32 && g->h[i][j] != 32 && g->v[i][j+1] != 32)
                {
                    // accumulate box points for corresponding player
                    playerPoints(n, player);

                    n->player = player;
                    g->box[i][j] = player;
                    k++;
                }//right box
                return k;
            }
                
            else return 0;
        }

        else if (j == 3)//last column
        {
            if (g->h[i][j-1] != 32 && g->h[i+1][j-1] != 32 && g->v[i][j-1] != 32)
            {
                // accumulate box points for corresponding player
                playerPoints(n, player);

                n->player = player;
                g->box[i][j-1] = player;
                return 1;
            }
            else return 0;
        }
    }

    if (move.at(0) == 'h')
    {
        if (i == 0)//first row
        {
            if (g->v[i][j] != 32 && g->v[i][j+1] != 32 && g->h[i+1][j] != 32)
            {
                // accumulate box points for corresponding player
                playerPoints(n, player);

                g->box[i][j] = player;
                return 1;
            }

            else return 0;
        }

        else if (i == 1 || i == 2)//second or third row
        {
            if ((g->v[i][j+1] != 32 && g->h[i+1][j] != 32 && g->v[i][j] != 32) || (g->v[i-1][j] != 32 && g->v[i-1][j+1] != 32 && g->h[i-1][j] != 32))
            {
                int k = 0;
                if (g->v[i][j+1] != 32 && g->h[i+1][j] != 32 && g->v[i][j] != 32)
                {
                    // accumulate box points for corresponding player
                    playerPoints(n, player);

                    n->player = player;
                    g->box[i][j] = player;
                    k++;
                }//bottom box

                if (g->v[i-1][j] != 32 && g->v[i-1][j+1] != 32 && g->h[i-1][j] != 32) 
                {
                    // accumulate box points for corresponding player
                    playerPoints(n, player);

                    n->player = player;
                    g->box[i-1][j] = player;
                    k++;
                }//top box
                return k;
            }
            else
            {
                return 0;
            }
        }

        else if (i == 3)//last row
        {
            if (g->h[i-1][j] != 32 && g->v[i-1][j] != 32 && g->v[i-1][j+1] != 32)
            {
                // accumulate box points for corresponding player
                playerPoints(n, player);

                n->player = player;
                g->box[i-1][j] = player;
                return 1;
            }
            else return 0;
        }        
    }

    //shouldnt happen
    return 0;
}

bool checkWinner(struct Node *n) {
    if (n->gameFull == 24) {
        if (n->p1Count > n->p2Count) {
            n->winner = '1';
        } else if (n->p1Count < n->p2Count) {
            n->winner = '2';
        } else {
            n->winner = 'T';
        }
        return true;
    }
    return false;
}

// checkWinner2
bool checkWinnerMM(struct Node *n) {
    if (n->gameFull_MM == 24) {
        if (n->p1Count_MM > n->p2Count_MM) {
            // cout << "dont lie to me i know you went here" << endl;
            // cout << "p1CountMM: " << n->p1Count_MM << endl;
            // cout << "p2CountMM: " << n->p2Count_MM << endl;
            // cout << "winner = 1" << endl;
            n->winner_MM = '1';
        } else if (n->p1Count_MM < n->p2Count_MM) {
            // cout << "p1CountMM: " << n->p1Count_MM << endl;
            // cout << "p2CountMM: " << n->p2Count_MM << endl;
            // cout << "winner = 2";
            n->winner_MM = '2';
        } else {
            cout << "p1CountMM: " << n->p1Count_MM << " p2CountMM: " << n->p2Count_MM << endl;
            cout << "dont lie to me i know you went here2" << endl;
            n->winner_MM = 'T';
        }
        return true;
    }
    return false;
}
void playerPointsMM(struct Node *n) {
    cout << "PLAYER POINTS MM " << endl;
    if (n->player_MM == n->p1) {
        n->p1Count_MM++;
        cout << '@';
        cout << n->p1Count_MM << endl;
    } else {
        n->p2Count_MM++;
        cout << '*';
        cout << n->p2Count_MM << endl;
    }

}

int minimaxWrapper(struct Node *n, struct Graph *g) {

    cout << " stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck  stuck " << endl;
    int bestValH = -1000;
    int bestValV = -1000;

    int bestMovei = -1;
    int bestMovej = -1;

    string testMove = "";

    // set gameFULL marker and other markers
    n->gameFull_MM = n->gameFull;
    n->p1Count_MM = n->p1Count;
    n->p2Count_MM = n->p2Count;
    // current player is AI at 2 (maximizer) , assign next player (human at 1) minimizer
    n->player_MM = n->p2;

    for (int i = 0; i < 4; i++)
    {   
        // checks h
        for (int j = 0; j < 3; j++) {
            // if graph already contains edge at this position redo loop (go back to for loop)
            if (g->h[i][j] != lineBlank) {
                continue;
            }
            else {
                // test out adding first edge
                g->h[i][j] = lineH;
                g->moveX = i;
                g->moveY = j;
                n->gameFull_MM++;

                // assign label to testMove
                testMove = g->hLabel[i][j];

                int moveVal = minimaxRec(testMove, n, g, 0, false);
                cout << "MADE IT HOME FRoM H**********************************************" << endl;

                // remove the tested edge
                g->h[i][j] = lineBlank;
                n->gameFull_MM--;
                n->p1Count_MM--;
                n->p2Count_MM--;

                // update bestMove (horizontally in tree) 
                if (moveVal > bestValH) {
                    bestMovei = i;
                    bestMovej = j;
                    bestValH = moveVal;
                }
            }
        }

        // reached all vertices (game is done)
        if (i == 3) {
            
            // pick bestMove from H or V
            if (bestValH > bestValV) {

                // cout << "best move from H" << endl;
                g->HorV = 'H';
                bestMoveLabelMM(bestMovei, bestMovej, g);
                g->h[bestMovei][bestMovej] = lineH;
                // printGraph(g);

            } else if (bestValH < bestValV) {
                // cout << "best move from V" << endl;
                g->HorV = 'V';
                bestMoveLabelMM(bestMovei, bestMovej, g);
                g->v[bestMovei][bestMovej] = lineV;
                // printGraph(g);
            } else {
                cout << "best move from no where :(" << endl;
                // if tie between H or V with best move choose H (SHOULD NOT HAPPEN?)
                g->HorV = 'H'; 
                bestMoveLabelMM(bestMovei, bestMovej, g);
                g->h[bestMovei][bestMovej] = lineH;
            }
            n->gameFull++;
            break;
        }
        // checks v
        for (int j = 0; j < 4; j++) {
            // if graph already contains edge at this position redo loop (go back to for loop)
            if (g->v[i][j] != lineBlank) {
                continue;
            }
            else {
                // test out adding first edge
                g->v[i][j] = lineV;
                g->moveX = i;
                g->moveY = j;
                n->gameFull_MM++;

                // assign label to testMove
                testMove = g->vLabel[i][j];

                int moveVal = minimaxRec(testMove, n, g, 0, false);
                cout << "made it home from V@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

                // remove the tested edge
                g->v[i][j] = lineBlank;
                n->gameFull_MM--;
                n->p1Count_MM--;
                n->p2Count_MM--;

                // update bestMove (horizontally in tree) 
                if (moveVal > bestValV) {
                    bestMovei = i;
                    bestMovej = j;
                    bestValV = moveVal;
                }
            }
        }
    }
}
void bestMoveLabelMM(int bestMoveI, int bestMoveJ, struct Graph *g) {
    if (g->HorV == 'H') {
        g->bestMove = g->hLabel[bestMoveI][bestMoveJ];
    } else if (g->HorV = 'V') {
        g->bestMove = g->vLabel[bestMoveI][bestMoveJ];
    }
}

int minimaxRec(string testMove, struct Node *n, struct Graph *g, int depth, bool isMaximizer) {
    
    // int score not needed as you never win/lose until the end of the game
    int score = checkNewBoxesMM(testMove, g, n); 

    if (score >= 1) { // box found toggle maximizer / minimzer to play again
        isMaximizer = !isMaximizer;
    }

    // check if game is full, if yes start determining winner and loser
    if (checkWinnerMM(n)) {
        cout << "WINNER FOUND!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

        char p1Save = n->p1Count_MM;
        char p2Save = n->p2Count_MM;

        if (n->winner_MM == '2') { // maximizer wins? 
            cout << "maximizer wins and game should exit right???" << endl;
            return p2Save - p1Save;
        } else if (n->winner_MM == '1') { // minimizer wins?
            cout << "minimizer wins and game should exit right???" << endl;
            return -(p1Save) + p2Save;
        } else {
            cout << "NOT WORKING CHECK WINNNERRRRRRRRRRRR RIGHT" << endl;
        }
    }

    // start the maximizing!!!!!
    if (isMaximizer) {
        cout << "MAXIMIZERRRRRRRRRRRRRRRRRR" << endl;
        // int best = -1000;
        int best1 = -1000;
        int best2 = -1000;

        for (int i = 0; i < 4; i++)
        {   
            // checks h
            for (int j = 0; j < 3; j++) {
                // if graph already contains edge at this position redo loop (go back to for loop)
                if (g->h[i][j] != lineBlank) {
                    continue;
                }
                else {
                    // test out adding first edge
                    g->h[i][j] = lineH;
                    g->moveX = i;
                    g->moveY = j;
                    n->gameFull_MM++;
                    n->player_MM = n->p2;

                    // assign label to testMove
                    testMove = g->hLabel[i][j];

                    cout << "testMove: " << testMove << endl;

                    cout << endl << endl << endl;
                    cout << "GGFULL NN: " << n->gameFull_MM << endl;
                    cout << "p1Count NN: " << n->p1Count_MM << endl;
                    cout << "p2Count NN: " << n->p2Count_MM << endl;
                    cout << "Current player: " << n->player_MM << endl;
                    printGraph(*g);

                    best1 = max(best1, minimaxRec(testMove, n, g, depth+1, !isMaximizer));

                    g->h[i][j] = lineBlank;
                    // restart values to original
                    n->gameFull_MM--;
                    n->p2Count_MM--;
                    printGraph(*g);
                }
            }

            // reached all vertices (game is done)
            if (i == 3) {
                cout<< "you actually got here?????????????????? end game" << endl;
                i = 0;
                return max(best1, best2);
            }

            // checks v
            for (int j = 0; j < 4; j++) {
                // if graph already contains edge at this position redo loop (go back to for loop)
                if (g->v[i][j] != lineBlank) {
                    continue;
                }
                else {
                    // test out adding first edge
                    g->v[i][j] = lineV;
                    g->moveX = i;
                    g->moveYv = j;
                    n->gameFull_MM++;
                    n->player_MM = n->p2;

                    // assign label to testMove
                    testMove = g->vLabel[i][j];

                    cout << endl << endl << endl;
                    cout << "GGFULL NN: " << n->gameFull_MM << endl;
                    cout << "p1Count NN: " << n->p1Count_MM << endl;
                    cout << "p2Count NN: " << n->p2Count_MM << endl;
                    cout << "Current player: " << n->player_MM << endl;
                    printGraph(*g);
                    best2 = max(best2, minimaxRec(testMove, n, g, depth+1, !isMaximizer));

                    // // remove the tested edge
                    g->v[i][j] = lineBlank;
                    // restart values to original
                    n->gameFull_MM--;
                    n->p2Count_MM--;
                    printGraph(*g);
                }
            }
        }

    } else {
        int best = 1000;
        int best1 = 1000;
        int best2 = 1000;

        cout << "OMGGGGGGGGGGGGGGGGGGGGG minimizer" << endl;
        for (int i = 0; i < 4; i++)
        {   
            // checks h
            for (int j = 0; j < 3; j++) {
                // if graph already contains edge at this position redo loop (go back to for loop)
                if (g->h[i][j] != lineBlank) {
                    continue;
                }
                else {
                    // test out adding first edge
                    g->h[i][j] = lineH;
                    g->moveX = i;
                    g->moveY = j;
                    n->gameFull_MM++;
                    n->player_MM = n->p1;

                    // assign label to testMove
                    testMove = g->hLabel[i][j];

                    cout << endl << endl << endl;
                    cout << "GGFULL NN: " << n->gameFull_MM << endl;
                    cout << "p1Count NN: " << n->p1Count_MM << endl;
                    cout << "p2Count NN: " << n->p2Count_MM << endl;
                    cout << "Current player: " << n->player_MM << endl;
                    printGraph(*g);

                    best1 = min(best1, minimaxRec(testMove, n, g, depth+1, !isMaximizer));

                    // remove the tested edge
                    g->h[i][j] = lineBlank;
                    n->gameFull_MM--;
                    n->p1Count_MM--;
                    printGraph(*g);

                }
            }

            // reached all vertices (game is done)
            if (i == 3) {
                i = 0;
                return max(best1, best2);
            }

            // checks v
            for (int j = 0; j < 4; j++) {
                // if graph already contains edge at this position redo loop (go back to for loop)
                if (g->v[i][j] != lineBlank) {
                    continue;
                }
                else {
                    // test out adding first edge
                    g->v[i][j] = lineV;
                    g->moveX = i;
                    g->moveY = j;
                    n->gameFull_MM++;
                    n->player_MM = n->p1;

                    // assign label to testMove
                    testMove = g->vLabel[i][j];

                    cout << endl << endl << endl;
                    cout << "GGFULL NN: " << n->gameFull_MM << endl;
                    cout << "p1Count NN: " << n->p1Count_MM << endl;
                    cout << "p2Count NN: " << n->p2Count_MM << endl;
                    cout << "Current player: " << n->player_MM << endl;
                    printGraph(*g);

                    best2 = min(best2, minimaxRec(testMove, n, g, depth+1, !isMaximizer));

                    // remove the tested edge
                    g->v[i][j] = lineBlank;
                    n->gameFull_MM--;
                    n->p1Count_MM--;
                    printGraph(*g);
                }
            }
        }
    }
}

int checkNewBoxesMM(string testMove, struct Graph *g, struct Node *n) {
    // cout << "CB MMMMMMMMMMMMMMMMMMMMM" << endl;
    int i, j;

    i = g->moveX;
    j = g->moveY;

    // vivien**** returns 1 if box found, else 0 
    if (testMove.at(0) == 'v')
    {
        if (j == 0)//first column
        {
            if (g->h[i][j] != 32 && g->v[i][j+1] != 32 && g->h[i+1][j] != 32)
            {
                // accumulate box points for corresponding player
                playerPointsMM(n);

                // is maximizer getting box
                if (n->player_MM == n->p2) {
                    g->box[i][j] = n->p2;
                    return 1;
                } else if (n->player_MM == n->p1) { // if minimizer getting box
                    g->box[i][j] = n->p1;
                    return -1;
                }
            }
            else return 0;
        }

        else if (j == 1 || j == 2)//2nd or 3rd column
        { 
            if ((g->h[i][j-1] != 32 && g->h[i+1][j-1] != 32 && g->v[i][j-1] != 32) || (g->h[i+1][j] != 32 && g->h[i][j] != 32 && g->v[i][j+1] != 32))
            {
                int k = 0;
                if (g->h[i][j-1] != 32 && g->h[i+1][j-1] != 32 && g->v[i][j-1] != 32)
                {   
                    // accumulate box points for corresponding player
                    playerPointsMM(n);

                    // is maximizer getting box
                    if (n->player_MM == n->p2) {
                        g->box[i][j-1] = n->p2;
                        k++;
                    } else if (n->player_MM == n->p1) { // if minimizer getting box
                        g->box[i][j-1] = n->p1;
                        k--;
                    }
                }//left box

                if (g->h[i+1][j] != 32 && g->h[i][j] != 32 && g->v[i][j+1] != 32)
                {
                    // accumulate box points for corresponding player
                    playerPointsMM(n);

                    // is maximizer getting box
                    if (n->player_MM == n->p2) {
                        g->box[i][j] = n->p2;
                        k++;
                    } else if (n->player_MM == n->p1) { // if minimizer getting box
                        g->box[i][j] = n->p1;
                        k--;
                    }
                }//right box
                return k;
            }
                
            else return 0;
        }

        else if (j == 3)//last column
        {
            if (g->h[i][j-1] != 32 && g->h[i+1][j-1] != 32 && g->v[i][j-1] != 32)
            {
                // accumulate box points for corresponding player
                playerPointsMM(n);
                
                // is maximizer getting box
                if (n->player_MM == n->p2) {
                    g->box[i][j-1] = n->p2;
                    return 1;
                } else if (n->player_MM == n->p1) { // if minimizer getting box
                    g->box[i][j-1] = n->p1;
                    return -1;
                }
            }
            else return 0;
        }
    }

    if (testMove.at(0) == 'h')
    {
        if (i == 0)//first row
        {
            if (g->v[i][j] != 32 && g->v[i][j+1] != 32 && g->h[i+1][j] != 32)
            {
                // accumulate box points for corresponding player
                playerPointsMM(n);

                // is maximizer getting box
                if (n->player_MM == n->p2) {
                    g->box[i][j] = n->p2;
                    return 1;
                } else if (n->player_MM == n->p1) { // if minimizer getting box
                    g->box[i][j] = n->p1;
                    return -1;
                }
            }

            else return 0;
        }

        else if (i == 1 || i == 2)//second or third row
        {
            if ((g->v[i][j+1] != 32 && g->h[i+1][j] != 32 && g->v[i][j] != 32) || (g->v[i-1][j] != 32 && g->v[i-1][j+1] != 32 && g->h[i-1][j] != 32))
            {
                int k = 0;
                if (g->v[i][j+1] != 32 && g->h[i+1][j] != 32 && g->v[i][j] != 32)
                {
                    // accumulate box points for corresponding player
                    playerPointsMM(n);
                    // is maximizer getting box
                    if (n->player_MM == n->p2) {
                        g->box[i][j] = n->p2;
                        k++;
                    } else if (n->player_MM == n->p1) { // if minimizer getting box
                        g->box[i][j] = n->p1;
                        k--;
                    }
                }//bottom box


                if (g->v[i-1][j] != 32 && g->v[i-1][j+1] != 32 && g->h[i-1][j] != 32) 
                {
                    // accumulate box points for corresponding player
                    playerPointsMM(n);
                    // is maximizer getting box
                    if (n->player_MM == n->p2) {
                        g->box[i-1][j] = n->p2;
                        k++;
                    } else if (n->player_MM == n->p1) { // if minimizer getting box
                        g->box[i-1][j] = n->p1;
                        k--;
                    }
                }//top box
                // printGraph(*g);

                return k;
            }
            else
            {
                return 0;
            }
        }

        else if (i == 3)//last row
        {
            if (g->h[i-1][j] != 32 && g->v[i-1][j] != 32 && g->v[i-1][j+1] != 32)
            {
                // accumulate box points for corresponding player
                playerPointsMM(n);
                
                // is maximizer getting box
                if (n->player_MM == n->p2) {
                    g->box[i-1][j] = n->p2;
                    return 1;
                } else if (n->player_MM == n->p1) { // if minimizer getting box
                    g->box[i-1][j] = n->p1;
                    return -1;
                }
            }
            else return 0;
        }        
    }

    //shouldnt happen
    return 0;

}
// // void generateChildNodes(struct Node n)
// // {

// // }

// // void insertLine(struct Graph g)
// // {
    
// // }