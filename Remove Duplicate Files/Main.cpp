//David Harkins

#include "AVL_Binary_Tree.h"



#include <iostream>
#include "sha2.h"

using std::string;
using std::cout;
using std::endl;



int main(int argc, char* argv[]) {

	string input = "grape";
	string output1 = sha224(input);
	string output2 = sha256(input);
	string output3 = sha384(input);
	string output4 = sha512(input);

	cout << "sha224('" << input << "'):" << output1 << endl;
	cout << "sha256('" << input << "'):" << output2 << endl;
	cout << "sha384('" << input << "'):" << output3 << endl;
	cout << "sha512('" << input << "'):" << output4 << endl;






	AVL_Binary_Tree<std::string> AVL_TREE;

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
	
	return 0;
}
