#include "util.h"

using namespace std;

int main()
{
   Node n;

   //testing by manually entering
   n.nodeGraph.h[0][0] = n.nodeGraph.h[2][0] = n.nodeGraph.h[2][1] = n.nodeGraph.h[2][2] = n.nodeGraph.h[1][0] = lineH;
   n.nodeGraph.v[0][0] = n.nodeGraph.v[0][1] = n.nodeGraph.v[1][0] = n.nodeGraph.v[1][1] = n.nodeGraph.v[2][1] = n.nodeGraph.v[2][2] = lineV;
   n.nodeGraph.h[0][1] = n.nodeGraph.h[0][2] = n.nodeGraph.h[1][1] = n.nodeGraph.h[3][2] = n.nodeGraph.h[3][0] = lineH;
   n.nodeGraph.h[1][2] = lineH;
   n.nodeGraph.v[2][3] = n.nodeGraph.v[0][3] = lineV;
   n.nodeGraph.box[0][0] = n.nodeGraph.box[1][0] = 'C';
   n.nodeGraph.box[2][2] = 'C';
   n.player = 'C';


   printGraph(n.nodeGraph);
   setUtil(&n);

   cout << "ROOT NODE. util: " << n.utility << "\n\n";

   generateChildNodes(&n);
   setUtil(&n);

   cout << "\n\n\n";

   string input;
   
   
   while (!isLeaf(n.nodeGraph))
   {
      cin >> input;
      Node *newnode = new Node;
      newnode->nodeGraph = n.nodeGraph;
      addMove(newnode, input);

      for (Node *child : n.childrenH)
      {
         if (child->nodeGraph.h == newnode->nodeGraph.h && child->nodeGraph.v == newnode->nodeGraph.v)
         {
            n = *child;
            break;
         }
      }

      for (Node *child : n.childrenV)
      {
         if (child->nodeGraph.h == newnode->nodeGraph.h && child->nodeGraph.v == newnode->nodeGraph.v)
         {
            n = *child;
            break;
         }
      }

      printGraph(n.nodeGraph);
      
      int max = -999;
      Node *best;
      for (Node *child : n.childrenH)
      {
         if (child->utility > max)
         {
            best = child;
         }
      }

      for (Node *child : n.childrenV)
      {
         if (child->utility > max)
         {
            best = child;
         }
      }

      n = *best;
      printGraph(n.nodeGraph);

   }
   


}