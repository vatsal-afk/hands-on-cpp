#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include "file_indexer.h"

using namespace std;

namespace files {
	FileIndexer::FileIndexer() {
		root = load();
	}
	FileIndexer::~FileIndexer() {
		save();
		destroyTree(root);
	}
	
	void FileIndexer::destroyTree(FileIndexer::node* root) {
		if (!root) {
			return;
		}
		
		destroyTree(root->left);
		destroyTree(root->right);
		
		delete root;
	}
	
	FileIndexer::node* insertFile(FileIndexer::node* root, FileIndexer::node* file) {
		if(root == nullptr) {
			return file;
		}
		
		if (file->fileName < root->fileName) {
        		root->left = insertFile(root->left, file);
    		}
    		else if (file->fileName > root->fileName) {
        		root->right = insertFile(root->right, file);
    		}
		else { // handle duplicate file name
        		cout << "File '" << file->fileName << "' already exists. Skipping insertion." << endl;
        		delete file; // need to modify this...
    		}
		
		return root;
	}
	
	void FileIndexer::createFile(string fileName, int fileSize) {
		FileIndexer::node* file = new FileIndexer::node(fileName, fileSize);
		
		root = insertFile(root, file);
		save();
	}
	
	FileIndexer::node* minNode(FileIndexer::node* root) {
        	if(root == nullptr) {
            	return root;
        	}
      	while(root->left != nullptr) {
      		root = root->left;
      	}
      	
      	return root;
    	}
    	
    	FileIndexer::node* deleteNode(FileIndexer::node* root, string name) {
    		if(root == nullptr) {
            	return root;
        	}
        	else if(name < root->fileName) {
            	root->left = deleteNode(root->left, name);
        	}
        	else if(name > root->fileName) {
            	root->right = deleteNode(root->right, name);
        	}
        	else {
            	if(root->right == nullptr && root->left == nullptr) {
		          delete root;
		          root = nullptr;
		          return root;
            	}
            	else if(root->right == nullptr && root->left != nullptr) {
                		root = root->left;
            	}
            	else if(root->right != nullptr && root->left == nullptr) {
                		root = root->right;
            	}
            	else {
		          FileIndexer::node* right_min = minNode(root->right);
		          root->fileName = right_min->fileName;
		          root->right = deleteNode(root->right, right_min->fileName);
            	}
        	}
        	
        	return root;
    	}

	void FileIndexer::deleteFile(string name) {
		root = deleteNode(root, name);
		save();
	}
	
	FileIndexer::node* searchNode(FileIndexer::node* root, string name) {
    		if(root == nullptr) {
            	return root;
        	}
        	else if(name < root->fileName) {
            	root->left = searchNode(root->left, name);
        	}
        	else if(name > root->fileName) {
            	root->right = searchNode(root->right, name);
        	}
        	
        	return root;
    	}

	void FileIndexer::editFile(string name, string updatedName, int updatedSize) {
		if(updatedName != name) {
			deleteFile(name);
			createFile(updatedName, updatedSize);
		}
		else {
			FileIndexer::node* file;
			file = searchNode(root, name);
			file->fileSize = updatedSize;
		}
	}

	bool FileIndexer::searchFileName(string name) {
		FileIndexer::node* result = searchNode(root, name);
		
		return result != nullptr;
	}
	
	FileIndexer::node* getPreOrder(FileIndexer::node* root, vector<pair<string, int>>& preOrder) {
		if(root == nullptr) {
			return root;
		}
		
		preOrder.push_back({root->fileName, root->fileSize});
		getPreOrder(root->left, preOrder);
		getPreOrder(root->right, preOrder);
		
		return root;
	}

	void FileIndexer::save() {
		vector<pair<string, int>> files;
		root = getPreOrder(root, files);
		
		ofstream MyFile("files.txt");
		
		for(const auto& [name, size] : files) {
    			MyFile << name << "," << size << endl;
		}
		
		MyFile.close();
	}
	
	FileIndexer::node* buildBST(vector<pair<string, int>>& preOrder) {
		FileIndexer::node* root = nullptr;
		for (const auto& [fileName, fileSize] : preOrder) {
			FileIndexer::node* file = new FileIndexer::node(fileName, fileSize);
			root = insertFile(root, file);
		}
		
		return root;
	}

	FileIndexer::node* FileIndexer::load() {
		vector<pair<string, int>> preOrder;
		string fileInfo;
		
		ifstream MyReadFile("files.txt");
		
		while(getline(MyReadFile, fileInfo)) { // get preOrder Traversal
			int commaIndex = fileInfo.find(',');
			string fileName = fileInfo.substr(0, commaIndex);
			int fileSize = stoi(fileInfo.substr(commaIndex + 1, fileInfo.size()));
			
			preOrder.push_back({fileName, fileSize});
		}
		
		int i = 0;
		return buildBST(preOrder);
	}
}

int main() {
    files::FileIndexer indexer; // run tests!

    indexer.createFile("test.txt", 100);
    indexer.createFile("report.pdf", 250);
    indexer.createFile("notes.docx", 300);

    indexer.editFile("report.pdf", "report_final.pdf", 275);
    indexer.deleteFile("test.txt");

    bool found = indexer.searchFileName("notes.docx");
    if(found) {
        cout << "File found!" << endl;
    } 
    else {
        cout << "File not found!" << endl;
    }

    return 0;
}

