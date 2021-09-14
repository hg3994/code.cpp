
/*

Harshit Gupta | 16th August, 2021
---------------------------------

Problem Statement:
	Design a data structure that simulates an in-memory file system.

	Implement the FileSystem class:

	1. FileSystem() Initializes the object of the system.

	2. List<String> ls(String path)
		If path is a file path, returns a list that only contains this file's name.
		If path is a directory path, returns the list of file and directory names in this directory.
	The answer should in lexicographic order.
	
	3. void mkdir(String path) Makes a new directory according to the given path. The given directory path does not exist. If the middle directories in the path do not exist, you should create them as well.
	
	4. void addContentToFile(String filePath, String content)
		If filePath does not exist, creates that file containing given content.
		If filePath already exists, appends the given content to original content.
	
	5. String readContentFromFile(String filePath) Returns the content in the file at filePath.


Example 1:

	Input
		["FileSystem", "ls", "mkdir", "addContentToFile", "ls", "readContentFromFile"]
		[[], ["/"], ["/a/b/c"], ["/a/b/c/d", "hello"], ["/"], ["/a/b/c/d"]]
	Output
		[null, [], null, null, ["a"], "hello"]

	Explanation
		FileSystem fileSystem = new FileSystem();
		fileSystem.ls("/");                         // return []
		fileSystem.mkdir("/a/b/c");
		fileSystem.addContentToFile("/a/b/c/d", "hello");
		fileSystem.ls("/");                         // return ["a"]
		fileSystem.readContentFromFile("/a/b/c/d"); // return "hello"

------

Solution: 

    TC: 
    SC:

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/


class FileSystem {
public:
    // A directory can contain directories and files
    // ls <dir>                         : show files and dirs in that directory (lexo)
    // ls <file>                        : return only this file name
    // mkdir <dir>                      : create dirs
    // addContentToFile <file, string>  : create/append string in the file
    // readContentFromFile <file>       : return file content
    
    // dir -> { [dir], [{file, content}]}
    
    // /        -> {a, }
    // /a       -> {b, }
    // /a/b     -> {c, }
    // /a/b/c   -> { , [{d, "hello"},{e, "world"} ]}

    unordered_map<string, pair<set<string>, set<pair<string, string>> >> fs;
    // NOTE: This can be implemented in a better way if we use unordered_map<string, string> instead of set<pair<string, string>>
    
    FileSystem() { 
        set< pair<string, string> > file_content_list = {};
        set<string> dirlist = {};
        pair< set<string>, set<pair<string, string>> > p = make_pair(dirlist, file_content_list);
        fs["/"] = p;
    }
    
    vector<string> ls(string path) {
        // cout<<"ls: "<<path<<endl;
        if(fs.count(path)){
            // it is a directory
            set<string> dir_list = fs[path].first;
            
            set<pair<string, string>> file_content_list = fs[path].second;
            set<string> files;
            for(auto fc: file_content_list){
                files.insert(fc.first);
            }
            dir_list.merge(files);

            vector<string> v(dir_list.begin(), dir_list.end());
            // cout<<"*** ls done *** "<<path<<endl;
            return v;
        }
        else{
            // it is a file path
            // cout<<std::filesystem::path(path).filename()<<endl;
            vector<string> v;
            v.push_back(std::filesystem::path(path).filename());
            return v;
        }
    }
    
    void showFs(){
        for(auto f : fs){
            cout<<f.first<<" -> ";
            for (auto x : f.second.first){
                cout<<x<<" ,";
            }
            cout<<endl;
        }
    }
    
    void mkdir(string path) {
        // cout<<"mkdir :"<<path<<endl;
        // showFs();
        int i=1;
        string dir = "";
        string lastdir = "/"; // '/' -> ab | /ab -> []
        while(i<path.size()) {
            if( (path[i] == '/' || i == path.size()-1)  ){
                if(i == path.size() - 1)
                    dir += path[i];
                fs[lastdir].first.insert(dir);
                if(lastdir != "/")
                    lastdir += "/";
                lastdir += dir;
                if(fs.count(lastdir) == 0){
                    set< pair<string, string> > file_content_list = {};
                    set<string> dirlist = {};
                    pair< set<string>, set<pair<string, string>> > p = make_pair(dirlist, file_content_list);
                    // insert "/abc" dir into the fs as well
                    fs[lastdir] = p;
                }
                dir = "";
                // showFs();
            }
            else{
                dir += path[i];
            }
            i++;
        }
        // showFs();
        // cout<<"*** mkdir done ***"<<endl;
    }
    
    void addContentToFile(string filePath, string content) {
        string parent_path = std::filesystem::path(filePath).parent_path();
        string filename = std::filesystem::path(filePath).filename();
        if(fs.count(parent_path)){
            // This will be the files in set: fs[parent_path].second
            set<pair<string, string>> files_content_set = fs[parent_path].second;
            for(auto fc: files_content_set){
                if(fc.first == filename){
                    // cout<<"file present already, append content to :"<<fc.second<<endl;
                    pair<string, string> p= make_pair(fc.first, fc.second+content);
                    files_content_set.erase(fc);
                    files_content_set.insert(p);
                    fs[parent_path].second = files_content_set;
                    return;
                }
            }
            
            // file not present, create it with content
            pair<string, string> new_file_content = make_pair(filename, content);
            files_content_set.insert(new_file_content);
            fs[parent_path].second = files_content_set;
            return;
        }
        else{
            // wont come here I guess
            cout<<"Exception in addContentToFile()"<<endl;
        }
    }
    
    string readContentFromFile(string filePath) {
        string parent_path = std::filesystem::path(filePath).parent_path();
        string filename = std::filesystem::path(filePath).filename();
        
        set<pair<string, string>> files_content_set = fs[parent_path].second;
        for(auto fc: files_content_set){
            // cout<<"fc.first: "<<fc.first<<endl;
            if(fc.first == filename){
                // file present already, return content
                return fc.second;
            }
        }
        return "";
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */