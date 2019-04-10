#include "util.h"
#include <string.h>

using namespace std;

int main()
{

   // print sample graph
   cout<<"."<<"_"<<"h1"<<"_"<<"."<<"_"<<"h2"<<"_"<<"."<<"_"<<"h3"<<"_"<<".\n";
   cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
   cout<<"v1"<<"   "<<"v2"<<"   "<<"v3"<<"   "<<"v4"<<"\n";
   cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
   cout<<"."<<"_"<<"h4"<<"_"<<"."<<"_"<<"h5"<<"_"<<"."<<"_"<<"h6"<<"_"<<".\n";
   cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
   cout<<"v5"<<"   "<<"v6"<<"   "<<"v7"<<"   "<<"v8"<<"\n";
   cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
   cout<<"."<<"_"<<"h7"<<"_"<<"."<<"_"<<"h8"<<"_"<<"."<<"_"<<"h9"<<"_"<<".\n";
   cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
   cout<<"v9"<<"   "<<"v10"<<"  "<<"v11"<<"  "<<"v12"<<"\n";
   cout<<"|"<<"    "<<"|"<<"    "<<"|"<<"    "<<"|"<<"\n";
   cout<<"."<<""<<"h10"<<"_"<<"."<<""<<"h11"<<"_"<<"."<<""<<"h12"<<"_"<<".\n";
   cout << endl;

   struct Node n;

   // n.nodeGraph.h[2][0] = lineH;

   // n.nodeGraph.v[1][3] = lineV;

   // n.nodeGraph.box[1][1] = 'C';
   // n.nodeGraph.box[0][0] = 'C';
   // n.nodeGraph.box[0][2] = 'P';

   string move;
   char player1, player2;

   // Ask player 1 to enter their initial of their first name
   cout << "Player 1: Enter the initial letter of your first name: ";
   cin >> player1;

   // Ask player 2 to enter their initial of their first name
   cout << "Player 2: Enter the initial letter of your first name: ";
   cin >> player2;

   // // start with player 1
   n.player = player1;

   do {

      // Player 1
      if (n.player == player1) {
         cout << "Player 1: \'" << player1 << "\'\n"; 
         cout << "Enter an edge to add according to map above: ";
         cin >> move;

         addMove(move, &n); // pass struct by reference
         // check for boxes and toggle player if no boxes made
         if (!checkNewBoxes(move, &n.nodeGraph, &n, player1)) {
            n.player = player2;
         }
         printGraph(n.nodeGraph);
         cout << endl;
         

         // Player 2
      } else if (n.player == player2) {
         cout << "Player 2: \'" << player2 << "\'\n"; 
         cout << "Enter an edge to add according to map above: ";
         cin >> move;

         addMove(move, &n); // pass struct by reference
         // check for boxes
         if (!checkNewBoxes(move, &n.nodeGraph, &n, player2)) {
            n.player = player1;
         }
         printGraph(n.nodeGraph);
         cout << endl;
      }
      
      
   } while (move != "exit");

   cout << "done?" << endl;
}