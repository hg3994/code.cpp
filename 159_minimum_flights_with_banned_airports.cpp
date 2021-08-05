
/*

Harshit Gupta | 27th July, 2021
---------------------------------

Problem Statement:

There are some countries and google has direct flight in these countries. Let n denote the number of countries, 
let each F=(i,j) denote a flight between these countries. We want to fly from country s to d but due to restrictions 
we can not stop in some countries
we want to go from 0 to 3, we are banned to stop at country 2. Find the flight with least amt of stops.

	If no direct flights, find the flights with the least amt of stops in restricted countries.

EXAMPLES: These examples are pathetic, need to rewrite them.
	n=4
	flights = {(0, 1), (1, 2), (2, 3), (0, 3)}
	banned = {2}
	s=1, d=3 => -1

	n = 5
	flights = {(0, 1), (1, 2), (2, 4), (0, 4), (3, 4)}
	banned = {0, 4}
	s = 1, d = 3

1. Check if there is any way to reach the 'd' airport, If not, return -1.
2. Check if there is any way to start from 's' airport, If not, return -1.
3. 's' or 'd' will never be a banned airport.
4. If there exists a path of 2 with 1 banned airport and there exists a path of 10 from usual airports, we will return 10
5. If there exists a path of 4 with 2 banned airports and a path of 8 with 1 banned airport, which one should I return?
	I am considering a path of 8 should be returned.

------

Solution: TODO the writeup here.

    TC: 
    SC:

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/



int findLeastStopFlights(vector<vector<int>> flight, vector<int>banned, int numAirports, int source, int destination){
	vector<vector<int>> graph;
	unordered_map<int, int> isBanned;
	bool canReachDestination=false, canStartFromSource=false;

	// Create a map so that we can check if a airport X is banned or not.
	for(auto b: banned){
		isBanned[b] = true;
	}

	// Build a graph without the banned airports
	for(int i=0; i<flights.size(); i++){
		if(!isBanned[flights[i][0]] && !isBanned[flights[i][1]])
			graph[flights[i][0]].push_back(flights[i][1]);

		if(flights[i][1] == destination)
			canReachDestination=true;
		if(flights[i][0] == source)
			canStartFromSource=true;
	}
	
	// If there are no flights from source or no flights to destination, we can never reachd from s.
	if(!canStartFromSource || !canReachDestination)
		return -1;

	// Check for a apth from s to d without any banned airports
	int paths = bfs(graph, isBanned, source, destination, 0);

	if(paths == 0){
		return findLeastStopFlightsWithBanned(flight, banned, numAirports, source, destination);
	}
	else {
		return paths;
	}
}


int findLeastStopFlightsWithBanned(vector<vector<int>> flight, unordered_map<int, int> isBanned, int numAirports, 
															int source, int destination) {

	// Build Graph again with the banned airports
	vector<vector<int>> graph;
	for(int i=0; i<flights.size(); i++)
		graph[flights[i][0]].push_back(flights[i][1]);

	// Check if it can reach with just 1 banned airport allowed, then 2,.. once we get a valid path 
	// with the least bannedAllowed, we return.
	for(int i=1; i<isBanned.size(); i++){
		int paths = bfs(graph, isBanned, source, destination, i);
		if(paths != 0)
			return paths;
	}

	return -1;
}


int bfs(vector<vector<int>> graph, unordered_map<int, int> isBanned, int source, destination, int bannedAllowed) {
	queue<int> q;
	vector<int> visited;

	q.insert(source);
	visited[source] = true;
	int paths = 0;

	while(!q.empty()){
		int size = q.size();
		for(int i=0 ;i<size; i++){
			int t = q.front();
			q.pop();

			if(isBanned.count(t)) {
				if(bannedAllowed)
					bannedAllowed--;
				else
					continue;
			}

			if(t == destination){
				return paths;
			}

			for(auto nbr: graph[t]){
				if(!visited[nbr]){
					q.push(nbr);
					visited[nbr] = true;
				}
			}
		}
		paths++;
	}
	return paths;
}
