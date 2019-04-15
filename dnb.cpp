#include "util.h"
#include <cstdlib>
#include <ctime>    // Enables use of time() function

using namespace std;

void recurse(struct Node *n)
{
    for (auto *child : n->children)
    {
        printGraph(child);
        cout << "\n";
        recurse(child);
    }
}

int main()
{
    srand(time(0));  // Unique seed for random AI part

    Node n;
    n.player = 'P';

    string randomArray[24] = {"h0","h1","h2","h3","h4","h5","h6","h7","h8","h9","h10","h11",
                                "v0","v1","v2","v3","v4","v5","v6","v7","v8","v9","v10","v11"};

    // map options
    cout<<"."<<"_"<<"h0"<<"_"<<"."<<"_"<<"h1"<<"_"<<"."<<"_"<<"h2"<<"_"<<".\n";
    cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
    cout<<"v0"<<"   "<<"v1"<<"   "<<"v2"<<"   "<<"v3"<<"\n";
    cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
    cout<<"."<<"_"<<"h3"<<"_"<<"."<<"_"<<"h4"<<"_"<<"."<<"_"<<"h5"<<"_"<<".\n";
    cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
    cout<<"v4"<<"   "<<"v5"<<"   "<<"v6"<<"   "<<"v7"<<"\n";
    cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
    cout<<"."<<"_"<<"h6"<<"_"<<"."<<"_"<<"h7"<<"_"<<"."<<"_"<<"h8"<<"_"<<".\n";
    cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
    cout<<"v8"<<"   "<<"v9"<<"  "<<"v10"<<"  "<<"v11"<<"\n";
    cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
    cout<<"."<<"_"<<"h9"<<"_"<<"."<<""<<"h10"<<"_"<<"."<<""<<"h11"<<"_"<<".\n";
    cout << endl;

    //    n.nodeGraph.h[2] = n.nodeGraph.h[3] = n.nodeGraph.h[4] = n.nodeGraph.h[5] = n.nodeGraph.h[11] = lineH;
    //    n.nodeGraph.v[0] = n.nodeGraph.v[1] = n.nodeGraph.v[6] = n.nodeGraph.v[7] = lineV;

    //    n.nodeGraph.v[2] = n.nodeGraph.v[4] = n.nodeGraph.v[11] = n.nodeGraph.v[9] = lineV;
    //    n.nodeGraph.h[8] = lineH;

    // start random first several moves (14 in total) to avoid program break (with 10 moves left)

    int moves = 0;
    Node *cursor = &n;
    while (moves <= 14) {
        if (n.player == 'P') {
            string input;
            cout << "Person, please enter a line: ";
            cin >> input;
            
            // adds move only if move does not exist
            if (!addMoveFirst(input, &n)) {
                continue;
            }
            // check for boxes and toggle player if no boxes made
            if (!checkNewBoxes(&n.nodeGraph, 'P')) {
                n.player = 'C';
            }
            
            printGraph(&n);
        } 
        else {
            string randomInput = AIPotentialWins(&n, &n.nodeGraph, 'C');
            // check for potential wins for AI and make move to make box(es)
            if (randomInput != "noWins") { // if anything besides "noWins"
                cout << "AI GOT BOX with: " << randomInput << endl;
                moves++;
                checkNewBoxes(&n.nodeGraph, 'C');
                printGraph(&n);
                continue;
            }
            
            else {
                // random variables
                int randomPos = rand() % 24;
                randomInput = randomArray[randomPos];
                // adds move only if move does not exist and avoids 
                if (!addMoveFirst(randomInput, &n)) {
                    continue;
                }
            }
            // if (!avoidBox(randomInput, &n.nodeGraph, 'C')) {
            //     printGraph(&n);
            //     removeEdgeFirst(randomInput, &n);
            //     printGraph(&n);
            //     continue;
            // }
            // check for boxes and toggle player if no boxes made
            if (!checkNewBoxes(&n.nodeGraph, 'C')) {
                n.player = 'P';
            }
            cout << "AI ENTERED: " << randomInput << endl;
            printGraph(&n);
        }
        moves++;
    }


    generateChildNodes(&n);
    n.utility = setUtil(&n);
    // printGraph(&n);

    while (!isLeaf(cursor))
    {
        if (cursor->player == 'P')
        {
            struct Graph temp;
            assignGraph(temp, cursor->nodeGraph);
            string input, modify;
            cout << "Person, please enter a line: ";
            cin >> input;
            modify = input;
            modify.erase(0,1);

            if (input.size() == 2)
            {
                if (input.at(0) == 'v') temp.v[stoi(modify)] = lineV;
                else temp.h[stoi(modify)] = lineH;
            }

            else
            {
                if (input.at(0) == 'v') temp.v[stoi(modify)] = lineV;
                else temp.h[stoi(modify)] = lineH;
            }

            for (auto x : cursor->children)
                if (compareGraph(x->nodeGraph,temp))
                        cursor = x;
        }

        else
        {
            cout << "AI entered: " << endl;
            struct Node *tmp = new Node;
            for (auto *child : cursor->children)
            {
                if (child->utility > tmp->utility) tmp = child;
            }

            cursor = tmp;
        }

        printGraph(cursor);
    }


    cout << "game ended..\n\nfinal graph:\n";
    printGraph(cursor);

    // tally total points and output winner
    for (int i = 0; i < 9; i++)
        if (cursor->nodeGraph.box[i] == 'C')
        {
            cursor->nodeGraph.totalC++;
        } else if (cursor->nodeGraph.box[i] == 'P') {
            cursor->nodeGraph.totalP++;
        }

    char winner;
    if (cursor->nodeGraph.totalP > cursor->nodeGraph.totalC) {
        winner = 'P';
    } else {
        winner = 'C';
    }
    cout << "Winner is " << winner << endl;
    cout << "Total points P: " << cursor->nodeGraph.totalP << endl;
    cout << "Total points C: " << cursor->nodeGraph.totalC << endl;
}

