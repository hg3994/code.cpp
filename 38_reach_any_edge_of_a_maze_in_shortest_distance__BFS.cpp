/* 
Harshit Gupta | 22nd November, 2018

C++ program for the problem:
    You are inside a maze and you have to reach any boundary of the maze to exit it.
    The maze is represented as a grid of 0s, 1s, and 2s.
        0 -> Places you can walk
        1 -> Walls. you can't walk on them
        2 -> Your position inside the maze
    You can move in top, down, left and right direction.
    What is the smallest number of moves in which you can exit the maze?


Solution: 1. Store each cell as a tuple with their row, column values and distance from source cell.
          2. Start BFS traversal from the source cell(where you are standing, position of 2) by pushing it in a queue.
          3. Make a visited array with all having “false” values except '1' cells and '2' cells
              which are assigned “true” values as they can not be traversed.
              This array will help us know which cells are already traversed 
              and would help us by not solving the same problem again and again (DEADLOCK)
          4. while the queue is not empty, keep popping the front 
              If the popped cell is the destination(edge), print the distance and return
              Else if its adjacent cells has '0' and they are not visited, then 
                  add it in the queue (since it is reachable) with distance+1
    

Paradigm: Graphs, BFS, Queues.

Time Complexity: O(n)

NOTE: We can always use BFS to find shortest path if graph is unweighted.

Similar Question: 
    1. https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/
        - The only difference here is that if the person is already standing at the 
            exit, he must exit from some other exit

*/

#include <bits/stdc++.h>
using namespace std;

int escape_from_grid(vector<vector<int>> grid, int N, int M, pair<int, int> source){
    
    bool visited[N][M];
    
    // Filling up the visited[][] array with false. We will assume 
    // that '1's and '2's as visited since we can't visit them as given in the question.
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(grid[i][j]==1 || grid[i][j]==2)
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

        // Iterate over its top, bottom, left and right cells
        for(int i=0;i<4;i++){

            // If the accessed cell is within the range and is the destination cell (EDGE CELL)
            // then print its distance and return. Note: distance is dist+1
            if(x+row[i]<N && x+row[i]>=0 && y+col[i]<M && y+col[i]>=0 && (x+row[i] == N-1 || x+row[i] == 0 || y+col[i]==0 || y+col[i]==M-1)){
                return dist+1;
            }

            // If the accessed cell is not destination and not yet visited and 
            // can be traversed( has a '0'), then push it in the queue with dist+1
            // Also, mark this place as visited[][].
            else if(x+row[i]<N && x+row[i]>=0 && y+col[i]<M && y+col[i]>=0 && visited[x+row[i]][y+col[i]] == false && grid[x+row[i]][y+col[i]] == 0){
                q.push(make_tuple(x+row[i],y+col[i],dist+1));
                visited[x+row[i]][y+col[i]] = true;
            }
        }
    }
    // If the queue becomes empty at some point and reaches here. 
    // EDGE can't be reached so return -1.
    return -1;
}

int main(){
	long long int n,m;
	cin>>n>>m;
	vector<vector<int> > a(n,vector<int> (m));
	pair <int, int> start;
	for(int i=0;i<n;i++){
	    for(int j=0;j<m;j++){
	        cin>>a[i][j];
	        if(a[i][j]==2){
	            start = make_pair(i,j);
	        }
	    }
	}
	
	int dist = escape_from_grid(a, n, m, start);
  if(dist==-1)
    cout<<"Edge can't be reached."<<endl;
	else
    cout<<dist<<endl;
	
	return 0;
}

// -----------------------
// LEETCODE QUESTION BELOW
// -----------------------

class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size();
        int n = maze[0].size();
        
        vector<int> t(n, 0);
        vector<vector<int>> visited(m, t);
        
        // Filling up the visited[][] array with false. We will assume 
        // that '0's as visited since we can't visit them as given in the question.
        for(int i=0;i<m; i++){
            for(int j=0; j<n; j++){
                if(maze[i][j] == '+')
                    visited[i][j] = 1;
            }
        }
        
        int moves = 0;
        queue<pair<int, int>> q;
        // Pushing the enterance and marking it visited
        q.push({entrance[0], entrance[1]});
        visited[entrance[0]][entrance[1]] = 1;
        
        while(!q.empty()){
            int size = q.size();
            for(int k=0; k<size; k++) {
                pair<int, int> f = q.front();
                q.pop();
                
                // If it is an edge && not the starting place, return moves
                if((f.first == 0 || f.first == m-1 || f.second == 0 || f.second == n-1) && (moves!=0)){
                    return moves;
                }
                
                // To iterate over the left, right, up and down cells.
                vector<int> row = {1,-1,0,0};
                vector<int> col = {0,0,1,-1};
                
                // Check for 4 adjacent plces and push them in queue if it satisfies the condns.
                for(int i=0; i<4; i++){
                    if(f.first+row[i] >=0  && f.first+row[i] < m &&
                       f.second+col[i] >=0 && f.second+col[i] <n &&
                       visited[f.first+row[i]][f.second+col[i]] == 0 &&
                       maze[f.first+row[i]][f.second+col[i]] == '.'
                      ) {
                        visited[f.first+row[i]][f.second+col[i]] = 1;
                        q.push({f.first+row[i], f.second+col[i]});
                    }
                }
            }
            // Increment the moves after every iteration.
            moves++;
        }
        
        // If it reaches here, it means that an edge is not reachable
        return -1;
    }
};