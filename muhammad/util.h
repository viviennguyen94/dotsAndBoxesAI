#include <iostream>
#include <vector>
#include <string>

#define lineH 196
#define lineV 179
#define lineBlank 32

using namespace std;

struct Graph
{
    char h[4][3] = {32,32,32,32,32,32,32,32,32,32,32,32};
    char v[3][4] = {32,32,32,32,32,32,32,32,32,32,32,32};
    char box[3][3] = {32,32,32,32,32,32,32,32,32};
};

struct Node
{
    Graph nodeGraph;
    int utility = 0;
    char player = '\0';
    vector<Node *> childrenH;
    vector<Node *> childrenV;

};

int checkNewBoxes(string move, Graph *g, char player);
void printGraph(struct Graph g);
void generateChildNodes(Node *n);
bool isLeaf(Graph g);
int setUtil(Node *n);
void addMove(Node *n, string move);

void printGraph(struct Graph g)
{
    for (int i = 0; i < 4; i++)
    {
        cout<<"."<<g.h[i][0]<<g.h[i][0]<<g.h[i][0]<<"."<<g.h[i][1]<<g.h[i][1]<<g.h[i][1]<<"."<<g.h[i][2]<<g.h[i][2]<<g.h[i][2]<<".\n";
        if(i==3)break;
        cout<<g.v[i][0]<<" "<<g.box[i][0]<<" "<<g.v[i][1]<<" "<<g.box[i][1]<<" "<<g.v[i][2]<<" "<<g.box[i][2]<<" "<<g.v[i][3]<<"\n";
    }
}

void generateChildNodes(Node *n)
{
    Graph g = n->nodeGraph;
    int i = 0, j = 0;

    for (auto &row : g.h)
    {
        for (auto &col : row)
        {
            if (col == lineBlank)
            {
                Node *childNode = new Node;
                childNode->nodeGraph = g;

                string move = "h";
                move += to_string(i);
                move += to_string(j);

                addMove(childNode, move);
                if (checkNewBoxes(move, &childNode->nodeGraph, n->player) > 0)
                {
                    childNode->player = n->player;
                    n->childrenH.push_back(childNode);
                    return;
                }
                else
                {
                    if (n->player == 'C') childNode->player = 'P';
                    else childNode->player = 'C';
                    n->childrenH.push_back(childNode);
                }
                
            }

            j++;
        }
        
        j = 0;
        i++;
    }
        
    i = j = 0;
    for (auto &row : g.v)
    {
        for (auto &col : row)
        {
            if (col == lineBlank)
            {
                Node *childNode = new Node;
                childNode->nodeGraph = g;

                string move = "v";
                move += to_string(i);
                move += to_string(j);

                addMove(childNode, move);
                if (checkNewBoxes(move, &childNode->nodeGraph, n->player) > 0)
                {
                    childNode->player = n->player;
                    n->childrenV.push_back(childNode);
                    return;
                }
                else
                {
                    if (n->player == 'C') childNode->player = 'P';
                    else childNode->player = 'C';
                    n->childrenV.push_back(childNode);
                }
                
            }

            j++;
        }

        j = 0;
        i++;
    }


    for (Node *c : n->childrenH)
    {
        generateChildNodes(c);
        setUtil(c);
    }

    for (Node *c : n->childrenV)
    {
        generateChildNodes(c);
        setUtil(c);
    }


        
}

int checkNewBoxes(string move, Graph *g, char player)
{
    int i, j;
    i = move.at(1)-48;
    j = move.at(2)-48;

    if (move.at(0) == 'v')
    {
        if (j == 0)//first column
        {
            if (g->h[i][j] != 32 && g->v[i][j+1] != 32 && g->h[i+1][j] != 32)
            {
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
                    g->box[i][j-1] = player;
                    k++;
                }//left box

                if (g->h[i+1][j] != 32 && g->h[i][j] != 32 && g->v[i][j+1] != 32)
                {
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
                    g->box[i][j] = player;
                    k++;
                }//bottom box

                if (g->v[i-1][j] != 32 && g->v[i-1][j+1] != 32 && g->h[i-1][j] != 32) 
                {
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
                g->box[i-1][j] = player;
                return 1;
            }
            else return 0;
        }        
    }

    //shouldnt happen
    return false;
}

bool isLeaf(Graph g)
{
    for (auto &row : g.h)
        for (auto &col : row)
        {
            if (col == 32) return false;
        }

    for (auto &row : g.v)
        for (auto &col : row)
        {
            if (col == 32) return false;
        }

    return true;
}

int setUtil(Node *n)
{
    int util = 0;

    for (auto &row : n->nodeGraph.box)
        for (auto &col : row)
        {
            if (col == 'C') n->utility++;
            if (col == 'P') n->utility--;
        }

    return util;
}

void addMove(Node *n, string move)
{
    char c = move.at(0);
    int i = move.at(1)-48;
    int j = move.at(2)-48;

    if (c == 'h')
    {
        n->nodeGraph.h[i][j] = lineH;
    }

    else
    {
        n->nodeGraph.v[i][j] = lineV;
    }
    
}