﻿/*

	Written by David Harkins,

	Simple Duplicate File Remover:
	Copyright (C) 2015 David Harkins

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation;  version 2 of the License, or 
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.


	Github: https://github.com/SkullCrusher/Simple-Duplicate-File-Remover
	
*/

#include "AVL_Binary_Tree.h"

#include "sha2.h"

#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>


	// Convert the string to wide string.
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

	// Generate the SHA512 by filename, (only accepts ascii or will return empty.)
std::string GenerateFileSHA512(std::string argument);

	// Contains the information about a file.
struct File_Info{

	std::string HASH = "";
	std::string FilePath = "";
	
	long long Size = 0;

		// Compare the two objects.
	friend bool operator == (File_Info& x, File_Info& y) {

			// Check if x has hash of the file.
		if (x.HASH == ""){
			//Generate the hash because it is not there.
			x.HASH = GenerateFileSHA512(x.FilePath);
		}

			// Check if y has hash of the file.
		if (y.HASH == ""){
			//Generate the hash because it is not there.
			y.HASH = GenerateFileSHA512(y.FilePath);
		}

			/* Special case, if one of them is a empty hash then we know it was 
			   unable to load the file so we assume it is not duplicate to prevent data loss. */
		if (x.HASH == "" || y.HASH == ""){
			return false;
		}

			// Compare the hashes to see if they match.
		if (x.HASH == y.HASH){
			return true;
		}else{
			return false;
		}
	}
};

	// Searched the for folders and files based off the first folder in the std::vector<std::string> &Folder
void Collect_Files(std::vector<std::string> &Folders, std::vector<File_Info> &Files, AVL_Binary_Tree<File_Info> &AVL_Tree){

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
					AVL_Tree.Insert(Temp, filesize.QuadPart, Files);
				}
		
			} while (FindNextFile(hFind, &ffd) != 0);
		
		}

			// Clean up.
		FindClose(hFind);
	}
}

	// Load file by full path and return a pointer to a char *str or null.
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

	}else{
		return NULL;
	}

	return memblock;
}

	// Use file path to load a file and SHA512 it and return it.
std::string GenerateFileSHA512(std::string argument){

		//Load the file into memory.
	char *File_test = LoadFileByName(argument.c_str());
	
	if (File_test == NULL){
		return "";
	}


	std::string output = sha512(File_test);

		//We don't need it anymore.
	delete File_test; 

	return output;
}

	// To help people by printing out how to use the tool.
void Print_Usage(){

	printf("Written by David Harkins.\n");
	printf("Usage:\n\n");
	printf("  -D Delete the duplicates.\n");
	printf("  -L Dump all the duplicates to a list.\n");
	printf("  -S Show extra information about the search.\n\n");
	printf("Example: -D -L <Path> -S <Path to folder to check>\n");

}

	// Turns the arguments into usable data.
bool Process_Arguments(int argc, char* argv[], bool &Show_Infomation, bool &Dump_To_File, std::string &Dump_To_File_Path, bool &Delete, std::string &Path_To_Search){

		// Loop through the arguments.
	for (int i = 1; i < argc; i++){

		if (argv[i][0] == '-' && argv[i][1] == 'D'){
			Delete = true;
			continue;
		}


		if (argv[i][0] == '-' && argv[i][1] == 'S'){
			Show_Infomation = true;
			continue;
		}

	
		if (argv[i][0] == '-' && argv[i][1] == 'L'){

				//Make sure there is another argument.
			if ((argc - i) >= 1){
				Dump_To_File = true;

				Dump_To_File_Path = argv[i + 1];
				i++; //Skip the path argument.
			}else{
					//No path provided.
				return false;
			}
		}
		
	}

		// The folder is always last.
	Path_To_Search = argv[argc - 1];


	return true;
}


int main(int argc, char* argv[]) {

		// Only valid combinations require at least 2 arguments.
	if (argc == 1){

		Print_Usage();
		
		return 1;
	}

	std::string Path_To_Search = "";

		// Shows information about duplicate files.
	bool Show_Infomation = false;

		// Should a file be created with duplicate files.
	bool Dump_To_File = false;

		// Where the file should be dumped to.
	std::string Dump_To_File_Path = "";

		// Should the files.
	bool Delete = false;


		//Process the arguments.
	if (!Process_Arguments(argc, argv, Show_Infomation, Dump_To_File, Dump_To_File_Path, Delete, Path_To_Search)){

			//Invalid use of the command line.
		Print_Usage();

		return 2;
	}
	
 
		// The tree for sorting file sizes.
	AVL_Binary_Tree<File_Info> AVL_TREE;

		// Folders (used for removing empty folders.)
	std::vector<std::string> Folders;

		// Used to hold the duplicate files found.
	std::vector<File_Info> Files;


		//Push the root directory onto the stack.
	Folders.push_back(Path_To_Search.c_str());
	
		//Display the starting directory, if the user wants output.
	if (Show_Infomation){
		printf("Starting search of %s.\n", Path_To_Search.c_str());
	}


		//Collect the files and sort them into the avl tree.
	Collect_Files(Folders, Files, AVL_TREE);
	
		//Show the information about the search, if the user wants output.
	if (Show_Infomation){
		long long Total_Duplicate_Size = 0;

		for (unsigned int i = 0; i < Files.size(); i++){
			Total_Duplicate_Size += Files[i].Size;
		}

		printf("Duplicates Found %u, totaling %lld bytes.\n", Files.size(), Total_Duplicate_Size);

	}

		// Should the duplicates be dumped to a file.
	if (Dump_To_File && Files.size() > 0){

		// If the user wants output.
		if (Show_Infomation){
			printf("Logging duplicate file names to file \"%s\"\n", Dump_To_File_Path.c_str());
		}

		std::ofstream Duplicate_Log;
		Duplicate_Log.open(Dump_To_File_Path.c_str());

		for (unsigned int i = 0; i < Files.size(); i++){
			Duplicate_Log << Files[i].FilePath << "\n";
		}

		Duplicate_Log.close();

	}

		// Delete all of the files.
	if (Delete && Files.size() > 0){

			// If the user wants output.
		if (Show_Infomation){
			printf("Deleting %d files.\n", Files.size());
		}

			// Delete selected file.
		for (int i = 0; i < Files.size(); i++){
			remove(Files[i].FilePath.c_str());
		}
	}

	printf("Finished: Be beware the robot overlords, they do not forgive the non-metallic.\n");
			
	return 0;
}
