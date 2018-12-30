/* 
Harshit Gupta | 29th October, 2018

https://ide.geeksforgeeks.org/FRtwW9xuXI
https://www.geeksforgeeks.org/shortest-distance-two-cells-matrix-grid/

C++ program for finding the shortest distance from a source cell to a destination cell, 
    traversing through limited cells only. Also you can move only up, down, left and right. 
    If found output the distance else -1.
        s represents ‘source’
        d represents ‘destination’
        * represents cell you can travel
        0 represents cell you can not travel
    This problem is meant for single source and destination.

Solution:   1. Store each cell as a tuple with their row, column values and distance from source cell.
            2. Start BFS traversal from the source cell by pushing it in a queue.
            3. Make a visited array with all having “false” values except ‘0’cells 
                which are assigned “true” values as they can not be traversed.
                This array will help us know which elements are already traversed 
                and would help us by not solving the same problem again and again.
            4. while the queue is not empty, keep popping the front 
                If the popped cell is the destination, print the distance and return
                Else if its adjacent cells has '*' and they are not visited, then 
                    add it in the queue (since it is reachable) with distance+1

Paradigm: Graphs, BFS

NOTE: We can always use BFS to find shortest path if graph is unweighted.

*/

#include <bits/stdc++.h>
using namespace std; 
#define N 4
#define M 4


void findMinDistance(char grid[N][M], pair<int,int> source, pair<int,int> destination){
    bool visited[N][M];
    
    // Filling up the visited[][] array with false. We will assume 
    // that '0's as visited since we can't visit them as given in the question.
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(grid[i][j]==0)
                visited[i][j] = true;
            else
                visited[i][j] = false;
        }
    }
    
    // To iterate over the left, right, up and down cells.
    int row[4] = {-1, 1, 0, 0};
    int col[4] = {0, 0, 1, -1};
    
    // A queue defined as 'x','y' and 'dist of the cell with source'
    queue<tuple<int,int,int>> q;
    
    // Push the source into the queue and its distance with itself would be 0.
    q.push(make_tuple(source.first, source.second, 0));
    
    // Till the queue is empty, traverse (BFS)
    while(!q.empty()){
        
        // Get the element in the front and pop it.
        tuple<int,int,int> f = q.front();
        q.pop();
        
        // Get the x,y and dist of the popped element.
        int x = get<0>(f);
        int y = get<1>(f);
        int dist = get<2>(f);
        // cout<<"Popped x:"<<x<<" y: "<<y<<" dist: "<<dist<<endl;
        
        // Iterate over its top, bottom, left and right cells
        for(int i=0;i<4;i++){
            
            // If the accessed cell is within the range and is the destination cell
            // then print its distance and return. Note: distance is dist+1
            if(x+row[i]<N && x+row[i]>=0 && y+col[i]<M && y+col[i]>=0 && x+row[i] == destination.first && y+col[i] == destination.second){
                cout<<"Destination reached with shortest path: "<<dist+1<<endl;
                return;
            }
            
            // If the accessed cell is not destination and not yet visited and 
            // can be traversed( has a '*'), then push it in the queue with dist+1
            // Also, mark this place as visited[][].
            else if(x+row[i]<N && x+row[i]>=0 && y+col[i]<M && y+col[i]>=0 && visited[x+row[i]][y+col[i]] == false && grid[x+row[i]][y+col[i]] == '*'){
                q.push(make_tuple(x+row[i],y+col[i],dist+1));
                visited[x+row[i]][y+col[i]] = true;
            }
        }
    }
    
    // If the queue becomes empty at some point and reaches here. 
    // destination 'd' can't be reached
    cout<<"Can't reach destination!"<<endl;
    return;
}

int main() 
{
    char grid[N][M] = { { '0', 'd', '0', 's' }, 
                        { '*', '*', '0', '*' }, 
                        { '*', '0', '0', '*' }, 
                        { '*', '*', '*', '*' } };
    
    // Defining the source and destination as pairs. It will contain the row & colm.
    pair <int, int> source;
    pair <int, int> destination;
    
    // Getting the source and destination from the matrix as pairs.
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(grid[i][j]=='s')
                source = make_pair(i,j);
            else if(grid[i][j]=='d')
                destination = make_pair(i,j);
        }
    }
    
    // Getting the minimum distance from s to d if any.
    findMinDistance(grid, source, destination);
    return 0; 
} 
