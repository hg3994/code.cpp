
/*

Harshit Gupta | .........., 2021
---------------------------------

Problem Statement:

	Given a list of email folder, covert it to a list of Gmail labels

	Sample input:
		Folder(id = 15, displayName = "subscriptions", parentId = -1)
		Folder(id = 27, displayName = "comics", parentId = 15)
		Folder(id = 35, displayName = "xkcd", parentId = 27)
		Folder(id = 81, displayName = "oatmeal", parentId = 27)

	Sample output:
		Label(displayName="subscriptions")
		Label(displayName="subscriptions/comics")
		Label(displayName="subscriptions/comics/xkcd")
		Label(displayName="subscriptions/comics/oatmeal")

												(xkcd)
			   							--------->35
	15-------------------->27----------|
	(subscription)     (comics)			---------->81
											(oatmeal)
{
	-1 => [15]
	15 => [27],
	27 => [35, 81]
}

{
	15 => "subs",
	27 => "comics",
	35 => "xkcd",
	81 => "oatmeal"
}
	
Assumptions:
	1. There will always be 1 node with parentId=-1
	2. There will no cycles in the graph.


------

Solution: 

	TODO: Need to fix the vector<int, int, string> thing!!!

    TC: 
    SC:

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/

vector<string> convertToGmailLabels (vector<int, int, string> folders){
	unordered_map<int, vector<int>> parentIDToIDMap;
	unordered_map<int, string> IDToNameMap;
	queue<int, string> q;
	vector<int> roots;
	vector<string> labels;

	for(int i=0; i<folders.size(); i++){
		IDToParentIDMap[folders[i][1]] = folders[i][0];
		IDToNameMap[folders[i][0]] = folders[i][2];
		if (folders[i][1] == -1)
			roots.push_back(folders[i][0]);
	}

	for(int i=0; i<roots.size(); i++){
		q.push({root[i], IDToNameMap[root[i]]});
		string ans;
		while(!q.empty()) {
			int size = q.size();
			for(int i=0; i<size; i++) {
				int top = q.front();
				q.pop();
					
				ans += (top[1]);

				for(auto nbr: parentIDToIDMap[top[0]]){
					q.push({nbr, top[1]+'/'+IDToNameMap[nbr]});
				}

			}
		}
		labels.push_back(ans);
	}
	return labels;
}