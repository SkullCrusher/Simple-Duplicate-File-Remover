#ifndef AVL_Binary_Tree_H
#define AVL_Binary_Tree_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

template <class T>
class AVL_Binary_Tree{

	struct Node{

		Node* Parent;
		Node* Left_Child;
		Node* Right_Child;

		//The balance of the node.
		int Height;

		long long key;
		std::vector<T> Data; //The data contained by the node.

		Node(){
			//Null out the pointers.
			key = 0;
			Height = 0;
			Parent = NULL;
			Left_Child = NULL;
			Right_Child = NULL;
		}
	};

	private: void Delete_Tree(Node* Argument){

		if (Argument != NULL){

			Delete_Tree(Argument->Left_Child);
			Delete_Tree(Argument->Right_Child);

			delete Argument;
		}

	}

	public: ~AVL_Binary_Tree(){
		Delete_Tree(Root);
	}

	private: Node* Root; //The root pointer.

		 //Default constructor.
	public:	AVL_Binary_Tree(){
		Root = NULL;
	}

		//If the item is not root, or first child of root.
private: void Insert_Not_Root(T InsertObject, long long key, std::vector<std::string> &Duplicate_Files, Node* Argument = NULL, int height = 1){

	//We check if the size if equal then check against the vector.
		//was here, change it to check the vector if it is more then one.

	if (Argument->key == key){

		bool Matched = false;

		//Loop through every element in the node.
		for (unsigned int i = 0; i < Argument->Data.size(); i++){

			//We compare the data to see if they
			if (Argument->Data[i] == InsertObject){

				//Debug?
				int debug = 0;
				here
			}

		}


		

		return;
	}


	//Insert elsewhere			
	if (Argument->key > key){
		//If null put it into that node else follow it.
		if (Argument->Left_Child == NULL){
					

			Node* Temp = new Node();

			Temp->Parent = Argument;
			Temp->key = key;
			//Temp->Data = InsertObject;
			Temp->Data.push_back(InsertObject);

			Temp->Height = height;

			Argument->Left_Child = Temp;

			Node *ForceRebalance = Update_BF_Leaf(Argument->Left_Child); //Update the balance.
			Balance(ForceRebalance); //Rebalancing if required.
		}else{
			Insert_Not_Root(InsertObject, key, Duplicate_Files, Argument->Left_Child, height + 1);
		}
	}else{

		//If null put it into that node else follow it.
		if (Argument->Right_Child == NULL){

			Node* Temp = new Node();

			Temp->Parent = Argument;
			Temp->key = key;
			//Temp->Data = InsertObject;
			Temp->Data.push_back(InsertObject);

			Temp->Height = height;

			Argument->Right_Child = Temp;

			Node *ForceRebalance = Update_BF_Leaf(Argument->Right_Child); //Update the balance.
			Balance(ForceRebalance);  //Rebalancing if required.
		}else{
			Insert_Not_Root(InsertObject, key, Duplicate_Files, Argument->Right_Child, height + 1);
		}
	}
}

		 //Update the balance factor after insertion from leaf.
	private: Node* Update_BF_Leaf(Node* Argument = NULL){

	//If we need to rebalance drop out of our update.
	if (Balance_Factor(Argument) >= 2 || Balance_Factor(Argument) <= -2){
		return Argument;
	}

	//if we have a parent to follow (root does not have one)
	if (Argument->Parent != NULL){
		return Update_BF_Leaf(Argument->Parent);
	}

	return NULL; //We don't need to rebalance this node.
}

		 //Insert a new item.
	public:	void Insert(T InsertObject, long long key, std::vector<std::string> &Duplicate_Files){

		//If the tree is empty
		if (Root == NULL){
			Root = new Node();

			Root->key = key;
			//Root->Data = InsertObject;
			Root->Data.push_back(InsertObject);
		}else{

			//Check if the root and the file are the same size.
		//	was here

			//Insert elsewhere			
			if (Root->key > key){
				//If null put it into that node else follow it.
				if (Root->Left_Child == NULL){
					Node* Temp = new Node();

					Temp->Parent = Root;
					Temp->key = key;
					//Temp->Data = InsertObject;

					Temp->Data.push_back(InsertObject);
					Temp->Height = 1;

					Root->Left_Child = Temp;
				}else{
					Insert_Not_Root(InsertObject, key, Duplicate_Files, Root);
				}
			}else{
				//If null put it into that node else follow it.
				if (Root->Right_Child == NULL){
					Node* Temp = new Node();

					Temp->Parent = Root;
					Temp->key = key;
					//Temp->Data = InsertObject;
					Temp->Data.push_back(InsertObject);


					Temp->Height = 1;

					Root->Right_Child = Temp;
				}else{
					Insert_Not_Root(InsertObject, key, Duplicate_Files, Root);
				}
			}
		}

		return;
	}

		//Used by Balance factor to find the depth of a sub tree.
	private: int Find_Height(Node * Argument = NULL, int height_arg = 0){

	int Height = 0;

	if (Argument->Left_Child != NULL){
		int Temp = Find_Height(Argument->Left_Child, height_arg + 1);

		if (Temp > Height){
			Height = Temp;
		}
	}
	else{
		if (Argument->Height > Height){
			Height = Argument->Height;
		}
	}

	if (Argument->Right_Child != NULL){
		int Temp = Find_Height(Argument->Right_Child, height_arg + 1);

		if (Temp > Height){
			Height = Temp;
		}
	}
	else{
		if (Argument->Height > Height){
			Height = Argument->Height;
		}
	}

	return Height;
}

	private: void Fix_Height(Node* Argument = NULL, int Depth = 0){
	if (Argument == NULL){
		Argument = Root;
	}

	if (Argument->Right_Child != NULL){
		Argument->Right_Child->Parent = Argument;

		Fix_Height(Argument->Right_Child, Depth + 1);
	}
	if (Argument->Left_Child != NULL){
		Argument->Left_Child->Parent = Argument;

		Fix_Height(Argument->Left_Child, Depth + 1);
	}

	Argument->Height = Depth;
}

		 //Used to find the balance factor of the argument node.
	private: int Balance_Factor(Node* Argument = NULL){

	int Height_Left = 0;
	int Height_Right = 0;

	//find the balance factor of left and right children
	if (Argument->Left_Child != NULL){
		Height_Left = Find_Height(Argument->Left_Child);
	}
	else{
		Height_Left = Argument->Height;
	}

	if (Argument->Right_Child != NULL){
		Height_Right = Find_Height(Argument->Right_Child);
	}
	else{
		Height_Right = Argument->Height;
	}

	return (Height_Left - Height_Right);
}

		 //Does all the balancing after Insert_Not_Root is called.
	private: void Balance(Node* Parent = NULL){

	while (Parent != NULL){

		if (Balance_Factor(Parent) == 2){

			//if we have a left-right case
			if (Balance_Factor(Parent->Left_Child) == -1){

				Left_Left_Rotation(Parent->Left_Child->Right_Child);

				Fix_Height();
			}

			//left-left case.
			Left_Right_Rotation(Parent->Left_Child);

			Fix_Height();

			return;
		}

		//Right-Left case
		if (Balance_Factor(Parent) == -2){

			//if we have a left-right case
			if (Balance_Factor(Parent->Right_Child) == 1){

				Right_Right_Rotation(Parent->Right_Child->Left_Child);

				Fix_Height();
			}

			//Right-Right case.
			Right_Left_Rotation(Parent->Right_Child);

			Fix_Height();

			return;
		}

		//Move up the list.
		Parent = Parent->Parent;
	}
}

		 //For Right-Right case.
	private: void Right_Left_Rotation(Node* Rotate){

	Node* B = Rotate->Left_Child;
	Node* Parent = Rotate->Parent;
	Node* GrandParent = Rotate->Parent->Parent;

	Parent->Right_Child = B;
	Parent->Parent = Rotate;

	Rotate->Parent = GrandParent;
	Rotate->Left_Child = Parent;

	//Link in the grand parent if it exists.
	if (Rotate->Parent == NULL){
		Root = Rotate;
	}
	else{
		if (GrandParent->Left_Child == Parent){
			GrandParent->Left_Child = Rotate;
		}
		else{
			GrandParent->Right_Child = Rotate;
		}
	}

}

		 //For Right-Left case.
	private: void Right_Right_Rotation(Node *Rotate){

	Node* C = Rotate->Right_Child;
	Node* GrandParent = Rotate->Parent->Parent;
	Node* Parent = Rotate->Parent;

	Parent->Left_Child = C;
	Parent->Parent = Rotate;

	Rotate->Right_Child = Parent;
	Rotate->Parent = GrandParent;

	GrandParent->Right_Child = Rotate;

	//Check if we are the new root.
	if (Rotate->Parent == NULL){
		Root = Rotate;
	}
}

		 //For Left-Left case.
	private: void Left_Right_Rotation(Node* Rotate){

	Node* C = Rotate->Right_Child; //
	Node* Parent = Rotate->Parent; //
	Node* GrandParent = Parent->Parent; //

	Parent->Left_Child = C;
	Parent->Parent = Rotate;

	Rotate->Right_Child = Parent;
	Rotate->Parent = GrandParent;

	//Link in the grand parent if it exists.
	if (Rotate->Parent == NULL){
		Root = Rotate;
	}
	else{
		if (GrandParent->Left_Child == Parent){
			GrandParent->Left_Child = Rotate;
		}
		else{
			GrandParent->Right_Child = Rotate;
		}
	}
}

		 //For Left-Right case.
	private: void Left_Left_Rotation(Node* Rotate){

	//Confusing right :3
	Node* B = Rotate->Left_Child;
	Node* GrandParent = Rotate->Parent->Parent;
	Node* Parent = Rotate->Parent;

	Parent->Right_Child = B;
	Parent->Parent = Rotate;

	Rotate->Left_Child = Parent;
	Rotate->Parent = GrandParent;

	GrandParent->Left_Child = Rotate;

	if (Rotate->Parent == NULL){
		Root = Rotate;
	}
}

		 //Find the type and spit it out (or provide the node link).
	public: Node* Find_Element(long long key, T &Result, Node* Search_Node = NULL){

	if (Search_Node == NULL){
		Search_Node = Root;
	}

	if (Search_Node->key == key){

		Result = Search_Node->Data;
		return Search_Node;
	}

	if (Search_Node->Left_Child != NULL){
		Node* Temp = Find_Element(key, Result, Search_Node->Left_Child);

		if (Temp != NULL){
			return Temp;
		}
	}

	if (Search_Node->Right_Child != NULL){
		Node* Temp = Find_Element(key, Result, Search_Node->Right_Child);

		if (Temp != NULL){
			return Temp;
		}
	}

	return NULL;
}

		//Find the next smallest node. Basically left -> right until null.
	private: Node* Find_Largiest_Subtree(Node* Search_Node, bool Flip = false){

	Node* Results = NULL;

	if (Flip){

		//First search so left.
		if (Search_Node->Left_Child != NULL){
			Results = Search_Node->Left_Child;

			Node* Temp = Find_Largiest_Subtree(Results);

			if (Temp != NULL){
				Results = Temp;
			}

			return Results;
		}
	}
	else{

		//Right searching
		if (Search_Node->Right_Child != NULL){
			Results = Search_Node->Right_Child;

			Node* Temp = Find_Largiest_Subtree(Results);

			if (Temp != NULL){
				Results = Temp;
			}

			return Results;
		}
	}

	return NULL; //Error?
}

		 //Actually delete the selected node.
	private: void Delete_fun(Node* DeleteObject){


	int Current_Step = 1;

	Node* X = DeleteObject; // be the node with the value we need to delete, 
	Node* Y = NULL; //node in the tree we need to find to take node X's place
	Node* Z_Parent = NULL;
	Node* Z = NULL; //the actual node we take out of the tree.


	while (Current_Step <= 8){

		//1.
		if (Current_Step == 1){
			if (DeleteObject->Right_Child == NULL || DeleteObject->Left_Child == NULL){
				Current_Step = 5;

				Z = X;
			}
		}

		//2.  Otherwise, determine node Y by finding the largest node in node X's left subtree (the in-order predecessor of X − it does not have a right child) or the smallest in its right subtree (the in-order successor of X − it does not have a left child).
		if (Current_Step == 2){
			Y = Find_Largiest_Subtree(DeleteObject, true);
		}

		//3. Exchange all the child and parent links of node X with those of node Y.In this step, the in - order sequence between nodes X and Y is temporarily disturbed, but the tree structure doesn't change.
		if (Current_Step == 3){
			//Make a local copy
			Node* Y_Parent = Y->Parent;
			Node* Y_Right_Child = Y->Right_Child;
			Node* Y_Left_Child = Y->Left_Child;

			Node* X_Parent = X->Parent;
			Node* X_Right_Child = X->Right_Child;
			Node* X_Left_Child = X->Left_Child;

			//False for left
			bool Left_Right = false;
			if (X_Parent->Right_Child == X){
				Left_Right = true;
			}

			//Trade Y
			Y->Parent = X_Parent;
			Y->Right_Child = X_Right_Child;
			Y->Left_Child = X_Left_Child;
			if (Left_Right == false){
				X->Parent->Left_Child = Y;
			}
			else{
				X->Parent->Right_Child = Y;
			}

			//Trade X
			X->Parent = Y_Parent;
			X->Right_Child = Y_Right_Child;
			X->Left_Child = Y_Left_Child;


			//4. Choose node Z to be all the child and parent links of old node Y = those of new node X.
			//Try to fix what we removed.			if (Current_Step == 4){	
			Y_Parent->Right_Child = Y_Left_Child;
			Y_Parent->Parent = Y;
			if (Y_Left_Child != NULL){
				Y_Left_Child->Parent = Y_Parent;
			}

			Z = Y_Parent;

			if (Z != NULL){
				Fix_Height();
				Balance(Y_Parent);

				return;
			}
		}

		//This needs to go before 5 so I switched 5 and 6.
		//6. If node Z was the root(its parent is null), update root.
		if (Current_Step == 5){

			if (Z != NULL){

				if (Z->Parent == NULL){
					if (DeleteObject->Right_Child != NULL){
						Root = DeleteObject->Right_Child;
					}

					if (DeleteObject->Left_Child != NULL){
						Root = DeleteObject->Left_Child;
					}
				}
			}
		}

		//5.  If node Z has a subtree(which then is a leaf), attach it to Z's parent.
		if (Current_Step == 6){

			if (DeleteObject->Right_Child != NULL){

				if (Z->Parent->Left_Child == Z){
					Z->Parent->Left_Child = DeleteObject->Right_Child;

					DeleteObject->Right_Child->Parent = Z->Parent;
				}
				else{
					Z->Parent->Right_Child = DeleteObject->Right_Child;

					DeleteObject->Right_Child->Parent = Z->Parent;
				}
			}
			if (DeleteObject->Left_Child != NULL){

				if (Z->Parent->Left_Child == Z){
					Z->Parent->Left_Child = DeleteObject->Left_Child;

					DeleteObject->Left_Child->Parent = Z->Parent;
				}
				else{
					Z->Parent->Right_Child = DeleteObject->Right_Child;

					DeleteObject->Left_Child->Parent = Z->Parent;
				}
			}
		}


		//7. Delete node Z.
		if (Current_Step == 7){

			if (Z != NULL){
				Z_Parent = Z->Parent;
				delete Z;
			}
		}

		//8. Retrace the path back up the tree(starting with node Z's parent) to the root, adjusting the balance factors as needed.
		if (Current_Step == 8){
			if (Z_Parent != NULL){
				Fix_Height();
				Balance(Z_Parent);
			}
		}

		Current_Step++;
	}
}

		 //Delete a node by the key.
	public:	void Delete(long long key){

	//I don't actually need TempTemp's data I just need it so call find_element
	std::string TempTemp;

	//Find the correct node to delete
	Node *ToDelete = Find_Element(key, TempTemp, NULL);

	Delete_fun(ToDelete);
}

};

#endif 