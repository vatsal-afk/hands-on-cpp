#pragma once

#include <string>

namespace files {
	class FileIndexer {
		public:
			FileIndexer();
			~FileIndexer();
			
			void createFile(std::string name, int size);
			void deleteFile(std::string name);
			void editFile(std::string name, int updatedSize);
			vector<std::string> searchFileName(std::string name);
		private:
			struct node {
				string fileName;
				int fileSize;
				string* left;
				string* right;
			};
			
			node* root;
			
			void save();
			void load();
	}
};
