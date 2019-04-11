#include <iostream>
#include <vector>

#define lineH 196
#define lineV 179
#define lineBlank 32

using namespace std;

struct Graph
{
    char h[4][3] = {32,32,32,32,32,32,32,32,32,32,32,32};
    char v[3][4] = {32,32,32,32,32,32,32,32,32,32,32,32};
    char box[3][3] = {32,32,32,32,32,32,32,32,32};
    int moveX, moveY;
};

struct Node
{
    Graph nodeGraph;
    int utility = 0;
    char player = '\0';
    char p1 = '\0';
    char p2 = '\0';
    int p1Count = 0;
    int p2Count = 0;
    int gameFull = 0; // should be 24
    char winner = '\0';
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
         cout << "Move not on map or move already exists" << endl;
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


void generateChildNodes(struct Node n)
{

}

void insertLine(struct Graph g)
{
    
}