#pragma once

#include <string>

using namespace std;

namespace files {
	class FileIndexer {
		public:
			FileIndexer();
			~FileIndexer();
			
			void createFile(std::string fileName, int fileSize);
			void deleteFile(std::string name);
			void editFile(std::string name, string updatedName, int updatedSize);
			bool searchFileName(std::string name);
			
		// private:
			struct node {
				string fileName;
				int fileSize;
				node* left;
				node* right;
				
				node(std::string fileName, int fileSize) : fileName(fileName), fileSize(fileSize), left(nullptr), right(nullptr) {}
			};
			
			node* root;
			
			void save();
			node* load();
			
			void destroyTree(node* root);
	};
};
