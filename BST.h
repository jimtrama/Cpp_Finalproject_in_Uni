#ifndef BST_H
#define BST_H
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
struct node_of_tree{

			string key;
			int times;
			node_of_tree* left;
			node_of_tree* right;
		};
class BST
{
	private:


        int nodes;
		node_of_tree* root;

		bool AddLeafPrivate(string key, node_of_tree* Ptr);
		void PrintInOrderPrivate(node_of_tree* Ptr);
		void PrintPreOrderPrivate(node_of_tree* Ptr);
		void PrintPostOrderPrivate(node_of_tree* Ptr);
		bool SearchTreePrivate(string key, node_of_tree* Ptr, node_of_tree* &target);
        void countNodesPrivate(node_of_tree*);
	public:

		BST();
		node_of_tree* CreateLeaf(string key);
		bool AddLeaf(string key);
		int countNodes();
		void PrintInOrder();
		void PrintPreOrder();
		void PrintPostOrder();
		bool SearchTree(string key, node_of_tree* &target);
	};

#endif
