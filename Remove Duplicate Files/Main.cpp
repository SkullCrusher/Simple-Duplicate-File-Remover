//David Harkins

#include "AVL_Binary_Tree.h"

#include "sha2.h"

#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>


std::wstring s2ws(const std::string& s){

	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

	//
struct File_Info{

	std::string HASH = "";
	std::string FilePath = "";
	
	long long Size = 0;
};

	//Searched the for folders and files based off the first folder in the std::vector<std::string> &Folder
void Collect_Files(std::vector<std::string> &Folders, AVL_Binary_Tree<File_Info> &AVL_Tree){

	for (unsigned int i = 0; i < Folders.size(); i++){

		std::string FirstFolder = Folders[i];
			
		FirstFolder += "\\*";
		std::wstring stemp = s2ws(FirstFolder);
		LPCWSTR result = stemp.c_str();

		WIN32_FIND_DATA ffd;

		HANDLE hFind = FindFirstFile(result, &ffd);

		if (INVALID_HANDLE_VALUE != hFind){
			do{
				LARGE_INTEGER filesize; // The file size.

				if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){

					int size = sizeof(ffd.cFileName);
					if (ffd.cFileName[0] != '.'){
					
						std::string Path = Folders[i];

						//convert from wide char to narrow char array
						char ch[260];
						char DefChar = ' ';
						WideCharToMultiByte(CP_ACP, 0, ffd.cFileName, -1, ch, 260, &DefChar, NULL);

						//A std:string  using the char* constructor.
						std::string ss(ch);

						Path += "\\";
						Path += ch;

						Folders.push_back(Path);
					}
				}else{
					filesize.LowPart = ffd.nFileSizeLow;
					filesize.HighPart = ffd.nFileSizeHigh;

					std::string Path = Folders[i];

					//convert from wide char to narrow char array
					char ch[260];
					char DefChar = ' ';
					WideCharToMultiByte(CP_ACP, 0, ffd.cFileName, -1, ch, 260, &DefChar, NULL);

					//A std:string  using the char* constructor.
					std::string ss(ch);

					Path += "\\";
					Path += ch;

					File_Info Temp;

					Temp.FilePath = Path;
					Temp.Size = filesize.QuadPart;					


					//filesize.QuadPart
					AVL_Tree.Insert(Temp, filesize.QuadPart);
				}
		
			} while (FindNextFile(hFind, &ffd) != 0);
			//FindClose(hFind);
		}else{
			// Report failure.
		}

	}

	


	//remove(Files[g].c_str());


	//FindClose(hFind);

}

	//Load file by full path and return a pointer to a char *str or null.
char *LoadFileByName(std::string argument){
	std::streampos size;
	char * memblock;

	std::ifstream file(argument.c_str() , std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()){

		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();

		//cout << "the entire file content is in memory";
		//delete[] memblock;
	}else{
		return 0;
		//cout << "Unable to open file";
	}

	return memblock;
}


int main(int argc, char* argv[]) {

	std::string input = "grape";
	std::string output4 = sha512(input);
	std::cout << "sha512('" << input << "'):" << output4 << std::endl;


	char *File_test = LoadFileByName("C:\\a\\cview.7z");

	AVL_Binary_Tree<File_Info> AVL_TREE;

	//folders
	std::vector<std::string> Folders;

	Folders.push_back("C:\\a");

	Collect_Files(Folders, AVL_TREE);


	/*

	std::string Random_String = "Some random data";

	AVL_TREE.Insert(Random_String, 3);
	AVL_TREE.Insert(Random_String, 13);	
	AVL_TREE.Insert(Random_String, 6);
	AVL_TREE.Insert(Random_String, 5);
	AVL_TREE.Insert(Random_String, 12);
	AVL_TREE.Insert(Random_String, 7);
	AVL_TREE.Insert(Random_String, 9);
	AVL_TREE.Insert(Random_String, 10);
	AVL_TREE.Insert(Random_String, 4);
	AVL_TREE.Insert(Random_String, 8);
	AVL_TREE.Insert(Random_String, 11);
	AVL_TREE.Insert(Random_String, 14);
	
	AVL_TREE.Delete(6);
	AVL_TREE.Delete(7);

	*/
	
	return 0;
}
