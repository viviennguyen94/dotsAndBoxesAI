#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string>

#define lineH 196
#define lineV 179
#define lineBlank 32

using namespace std;

ofstream myfile;

struct Graph
{
    char h[12] = {32,32,32,32,32,32,32,32,32,32,32,32};
    char v[12] = {32,32,32,32,32,32,32,32,32,32,32,32};
    char box[9] = {32,32,32,32,32,32,32,32,32};

    // vivien
    int totalP = 0;
    int totalC = 0;
};

struct Node
{
    Graph nodeGraph;
    int utility = -99;
    char player = '\0';
    vector<Node *> children;

};

int checkNewBoxes(Graph *g, char player);
void printGraph(Node *n);
void generateChildNodes(Node *n);
bool isLeaf(Node *n);
int setUtil(Node *n);
void assignGraph(struct Graph &lhs, struct Graph &rhs);
bool compareGraph(struct Graph &lhs, struct Graph &rhs);

// vivien
bool addMoveFirst(string input, struct Node *n);
void removeEdgeFirst(string input, struct Node *n);
string AIPotentialWins(struct Node *n, struct Graph *g, char player);

void printGraph(Node *n)
{
    int i = 0, k = 0, j = 0;
    for (;; i+=3,j+=4,k+=3)
    {
        cout<<"."<<n->nodeGraph.h[i]<<n->nodeGraph.h[i]<<n->nodeGraph.h[i]<<"."<<n->nodeGraph.h[i+1]<<
        n->nodeGraph.h[i+1]<<n->nodeGraph.h[i+1]<<"."<<n->nodeGraph.h[i+2]<<n->nodeGraph.h[i+2]<<n->nodeGraph.h[i+2]<<".\n";
        if (i>8) break;
        cout<<n->nodeGraph.v[j]<<" "<<n->nodeGraph.box[k]<<" "<<n->nodeGraph.v[j+1]<<" "<<n->nodeGraph.box[k+1]<<
        " "<<n->nodeGraph.v[j+2]<<" "<<n->nodeGraph.box[k+2]<<" "<<n->nodeGraph.v[j+3]<<"\n";
    }
    // cout << "util: " << n->utility << "\n\n";
}

void generateChildNodes(Node *n)
{
    if (isLeaf(n)) return;
    Graph g = n->nodeGraph;
    
    for (int i = 0; i < 12; i++)
    {
        if (g.h[i] == lineBlank)
        {
            Node *childNode = new Node;
            childNode->nodeGraph = g;
            childNode->utility = n->utility;
            childNode->nodeGraph.h[i] = lineH;

            if(checkNewBoxes(&childNode->nodeGraph, n->player) > 0) childNode->player = n->player;
            else if (n->player == 'P') childNode->player = 'C';
            else childNode->player = 'P';

            n->children.push_back(childNode);
        }

        if (g.v[i] == lineBlank)
        {
            Node *childNode = new Node;
            childNode->nodeGraph = g;
            childNode->utility = n->utility;
            childNode->nodeGraph.v[i] = lineV;

            if(checkNewBoxes(&childNode->nodeGraph, n->player) > 0) childNode->player = n->player;
            else if (n->player == 'P') childNode->player = 'C';
            else childNode->player = 'P';
            
            n->children.push_back(childNode);
        }
    }

     for (Node *c : n->children)
        if (!isLeaf(c))
            generateChildNodes(c);

}

int checkNewBoxes(Graph *g, char player)
{
    int amount = 0;

    // keep track of total boxes for each player
    g->totalP = 0;
    g->totalC = 0;

    for (int i = 0; i < 9; i++)
        if (g->box[i] == lineBlank)
        {
            if (i < 3)
                if (g->h[i] != 32 && g->v[i] != 32 && g->h[i+3] != 32 && g->v[i+1] != 32)
                {
                    g->box[i] = player;
                    amount++;
                }

            if (i >= 3 && i <= 5)
                if (g->h[i] != 32 && g->v[i+2] != 32 && g->h[i+3] != 32 && g->v[i+1] != 32)
                {
                    g->box[i] = player;
                    amount++;
                }

            if (i > 5)
                if (g->h[i] != 32 && g->v[i+2] != 32 && g->h[i+3] != 32 && g->v[i+3] != 32)
                {
                    g->box[i] = player;
                    amount++;
                }
        }

    return amount;
}

bool isLeaf(Node *n)
{
     for (int i = 0; i < 12; i++)
        if (n->nodeGraph.h[i] == lineBlank || n->nodeGraph.v[i] == lineBlank) return false;
    return true;
}

int setUtil(Node *n)
{
    for (auto *child : n->children)
    {
        if(isLeaf(child))
        {
            child->utility = 0;
            for (int i = 0; i < 9; i++)
            {
                if (child->nodeGraph.box[i] == 'P') child->utility--;
                else child->utility++;
            }
        }

        else
        {
            child->utility = setUtil(child);
        }
    }

    int best;

    if (n->player == 'P')
    {
        best = 99;
        for (auto *child : n->children)
            if (child->utility < best) best = child->utility;
    }
    else
    {
        best = -99;
        for (auto *child : n->children)
            if (child->utility > best) best = child->utility;
    }
    
    return best;
}

void assignGraph(struct Graph &lhs, struct Graph &rhs)
{
    for (int i = 0; i < 12; i++)
    {
        lhs.h[i] = rhs.h[i];
        lhs.v[i] = rhs.v[i];
        if (i < 10) lhs.box[i] = rhs.box[i];
    }
}

bool compareGraph(struct Graph &lhs, struct Graph &rhs)
{
    for (int i = 0; i < 12; i++)
        if (lhs.h[i] != rhs.h[i] || lhs.v[i] != rhs.v[i]) return false;

    return true;
}
// vivien
bool addMoveFirst(string input, struct Node *n) {
    
    string modify = input;
    modify.erase(0,1);

    if (input.size() == 2 || input.size() == 3)
    {
        if (input.at(0) == 'v' && n->nodeGraph.v[stoi(modify)] == lineBlank) {
            n->nodeGraph.v[stoi(modify)] = lineV;
        } else if (input.at(0) == 'h' && n->nodeGraph.h[stoi(modify)] == lineBlank) {
            n->nodeGraph.h[stoi(modify)] = lineH;
        } else {
            cout << "Move not on map or move already exists" << endl << endl;
            return false;
        }
            
    } else {
        cout << "Move not on map" << endl << endl;
        return false; // move was not able to be added
    }
    return true; // move was added
}
bool avoidBox(string randomInput, struct Graph *g, char player) {

    for (int i = 0; i < 9; i++)
        if (g->box[i] == lineBlank)
        {
            // first row
            if (i < 3)
                // top, left || bottom, right || left, bottom || right, top || top, bottom || right, left
                if (g->h[i] != 32 && g->v[i] != 32 || g->h[i+3] != 32 && g->v[i+1] != 32 || g->v[i] != 32 && g->h[i+3] != 32 || g->v[i+1] != 32 && g->h[i] != 32 || g->h[i] != 32 && g->h[i+3] != 32 || g->v[i] != 32 || g->v[i+1] != 32)
                {
                    return false;
                }
            // second row
            if (i >= 3 && i <= 5)
                // top, left || bottom, right || left, bottom || right, top || top, bottom || right, left
                if (g->h[i] != 32 && g->v[i] != 32 || g->h[i+3] != 32 && g->v[i+1] != 32 || g->v[i] != 32 && g->h[i+3] != 32 || g->v[i+1] != 32 && g->h[i] != 32 || g->h[i] != 32 && g->h[i+3] != 32 || g->v[i] != 32 || g->v[i+1] != 32)
                {
                    return false;
                }
            // third row
            if (i > 5)
                // top, left || bottom, right || left, bottom || right, top || top, bottom || right, left
                if (g->h[i] != 32 && g->v[i] != 32 || g->h[i+3] != 32 && g->v[i+1] != 32 || g->v[i] != 32 && g->h[i+3] != 32 || g->v[i+1] != 32 && g->h[i] != 32 || g->h[i] != 32 && g->h[i+3] != 32 || g->v[i] != 32 || g->v[i+1] != 32)
                {
                    return false;
                }
        }

    return true;
}
void removeEdgeFirst(string input, struct Node *n) {
    
    string modify = input;
    modify.erase(0,1);

    if (input.size() == 2)
    {
        if (input.at(0) == 'v') n->nodeGraph.v[stoi(modify)] = lineV;
        else n->nodeGraph.h[stoi(modify)] = lineBlank;
    } else {
        cout << "Move could not be deleted" << endl;
    }
}
string AIPotentialWins(struct Node *n, struct Graph *g, char player) {
    for (int i = 0; i < 9; i++)
        if (g->box[i] == lineBlank)
        {
            // first row
            if (i < 3) {
                // top, left, bottom full, right blank
                if (g->h[i] != 32 && g->v[i] != 32 && g->h[i+3] != 32 && g->v[i+1] == 32)
                {
                    string potWin = "v" + to_string(i+1);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
                // top, right, bottom full, left blank
                if (g->h[i] != 32 && g->v[i+1] != 32 && g->h[i+3] != 32 && g->v[i] == 32)
                {
                    string potWin = "v" + to_string(i);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
                // top blank, left, right, bottom full
                if (g->h[i] == 32 && g->v[i+1] != 32 && g->h[i+3] != 32 && g->v[i] != 32)
                {
                    string potWin = "h" + to_string(i);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
                // bottom blank, left, right, top full
                if (g->h[i+3] == 32 && g->v[i+1] != 32 && g->h[i] != 32 && g->v[i] != 32)
                {
                    string potWin = "h" + to_string(i+3);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
            }
            // second row
            if (i >= 3 && i <= 5) {
                // top, left, bottom full, right blank
                if (g->h[i] != 32 && g->v[i+1] != 32 && g->h[i+3] != 32 && g->v[i+2] == 32)
                {
                    string potWin = "v" + to_string(i+2);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
                // top, right, bottom full, left blank
                if (g->h[i] != 32 && g->v[i+2] != 32 && g->h[i+3] != 32 && g->v[i+1] == 32)
                {
                    string potWin = "v" + to_string(i+1);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
                // top blank, left, right, bottom full
                if (g->h[i] == 32 && g->v[i+1] != 32 && g->h[i+3] != 32 && g->v[i+2] != 32)
                {

                    string potWin = "h" + to_string(i);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
                // bottom blank, left, right, top full
                if (g->h[i+3] == 32 && g->v[i+1] != 32 && g->h[i] != 32 && g->v[i+2] != 32)
                {
                    string potWin = "h" + to_string(i+3);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
            }
            // third row
            if (i > 5) {
                // top, left, bottom full, right blank
                if (g->h[i] != 32 && g->v[i+2] != 32 && g->h[i+3] != 32 && g->v[i+3] == 32)
                {
                    string potWin = "v" + to_string(i+3);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
                // top, right, bottom full, left blank
                if (g->h[i] != 32 && g->v[i+3] != 32 && g->h[i+3] != 32 && g->v[i+2] == 32)
                {
                    string potWin = "v" + to_string(i+2);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
                // top blank, left, right, bottom full
                if (g->h[i] == 32 && g->v[i+2] != 32 && g->h[i+3] != 32 && g->v[i+3] != 32)
                {
                    string potWin = "h" + to_string(i);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
                // bottom blank, left, right, top full
                if (g->h[i+3] == 32 && g->v[i+2] != 32 && g->h[i] != 32 && g->v[i+3] != 32)
                {
                    string potWin = "h" + to_string(i+3);
                    addMoveFirst(potWin, n);
                    return potWin;
                }
            }
        }

    return "noWins";
}