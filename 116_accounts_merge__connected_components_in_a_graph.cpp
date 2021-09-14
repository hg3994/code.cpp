
/*

Harshit Gupta | 13th June, 2021
---------------------------------

C++ program for 

Given a list of accounts where each element accounts[i] is a list of strings, where the first
 element accounts[i][0] is a name, and the rest of the elements are emails representing emails 
 of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person 
if there is some common email to both accounts. Note that even if two accounts have the same 
name, they may belong to different people as people could have the same name. A person can 
have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of 
each account is the name, and the rest of the elements are emails in sorted order. The 
accounts themselves can be returned in any order.


Example 1:
    Input: accounts = [ ["John","johnsmith@mail.com","john_newyork@mail.com"],
                        ["John","johnsmith@mail.com","john00@mail.com"],
                        ["Mary","mary@mail.com"],
                        ["John","johnnybravo@mail.com"]]
    
    Output: [   ["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
                ["Mary","mary@mail.com"],
                ["John","johnnybravo@mail.com"]]
    
    Explanation:
        The first and third John's are the same person as they have the common email "johnsmith@mail.com".
        The second John and Mary are different people as none of their email addresses are used by other accounts.
        We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
            ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.



https://leetcode.com/problems/accounts-merge/

------

Solution: We create a graph of emails. Draw two edges between the two related emails, if they belong to the same person.
    1. Draw an edge between two emails if they occur in the same account. 
        The problem comes down to finding connected components of this graph.
    2. We'll remember a map from emails to names on the side. 
    3. After finding each connected component using a depth-first search, add that to our answer.

TC: O(Ai logAi)  where Ai is the length of accounts[i]. Without the log factor, this is the complexity 
    to build the graph and search for each component. The log factor is for sorting each component at the end.
SC: O(Ai), space used by our graph

Paradigm: Graph, conncted components

---
  NOTE: 

*/

class Solution {
public:
    unordered_map<string, vector<string>> graph;
    unordered_map<string,string> email_to_name;
    unordered_set<string> visited;
    
    
    void dfs(string email, set<string> &email_set) {
        if(visited.count(email))
            return;
        visited.insert(email);
        email_set.insert(email);
        for(auto email : graph[email])
            dfs(email, email_set);
    }

    void buildGraph(vector<vector<string>>& accounts){
        for(int i = 0; i < accounts.size(); ++i) {
            string name = accounts[i][0];
            string first_email = accounts[i][1];
            
            for(int j = 1; j < accounts[i].size(); ++j) {
                string email = accounts[i][j];
                graph[first_email].push_back(email);
                graph[email].push_back(first_email);
                if(!email_to_name.count(email))
                    email_to_name[email] = name;
            }
        }
    }

    // Print the graph
    // void printGraph(vector<vector<string>>& accounts){
    //     for(auto [email, related_emails] : graph) {
    //         cout<<email<<"->";
    //         for(int i=0;i<related_emails.size(); i++){
    //             cout<<related_emails[i]<<" , ";
    //         }
    //         cout<<endl;
    //     }
    // }

    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> res;
        buildGraph(accounts);
        
        // printGraph(accounts);
        
        // This is how we iterate over all the elements of the unordered_map
        for(auto [email, _] : graph) {
            if(!visited.count(email)) {
                set<string> email_set; // due to this, the email list remain sorted (its a set)
                dfs(email, email_set);
                
                vector<string> account(email_set.size() + 1);
                string name = email_to_name[email];
                account = {email_set.begin(), email_set.end()};
                account.insert(account.begin(), name); // insert name at the beginning.
                res.push_back(account);
            }
        }
        return res;
        
    }
};