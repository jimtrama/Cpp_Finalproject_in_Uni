#include "BST.h"




BST::BST(){

	root = NULL;
	nodes=0;

}
node_of_tree* BST::CreateLeaf(string key){

	node_of_tree* n = new node_of_tree;
	n->key = key;
	n->times=1;
	n->left = NULL;
	n->right = NULL;

	return n;

}
int BST::countNodes()
{
    nodes=0;
    countNodesPrivate(root);
    return nodes;
}
void BST::countNodesPrivate(node_of_tree*Ptr)
{
    if(Ptr==NULL)
        return;
    countNodesPrivate(Ptr->left);
    nodes=nodes+Ptr->times;
    countNodesPrivate(Ptr->right);
}
bool BST::AddLeaf(string key){

	return AddLeafPrivate(key, root);
}

bool BST::AddLeafPrivate(string key, node_of_tree* Ptr){

	if (root == NULL){
		root = CreateLeaf(key);
		return true;
	}else if(key < Ptr->key){
		if(Ptr->left != NULL){
			return AddLeafPrivate(key, Ptr->left);
		}else{
			Ptr->left = CreateLeaf(key);
			return true;
		}
	}else if(key > Ptr->key){
		if(Ptr->right != NULL){
			return AddLeafPrivate(key, Ptr->right);

		}else{
			Ptr->right = CreateLeaf(key);
			return true;
		}
	}else{
		Ptr->times++;
		return true;

	}
	return false;
}


void BST::PrintInOrder(){
	PrintInOrderPrivate(root);
}

void BST::PrintInOrderPrivate(node_of_tree* Ptr){


	if(root != NULL){

		if (Ptr->left != NULL){

			PrintInOrderPrivate(Ptr->left);
		} cout << Ptr->key << " ";
		if (Ptr->right != NULL){

			PrintInOrderPrivate(Ptr->right);
		}
	}else{
		cout << "The tree is empty." << endl;
	}

}

void BST::PrintPreOrder(){
	PrintPreOrderPrivate(root);
}

void BST::PrintPreOrderPrivate(node_of_tree* Ptr){

	if(root != NULL){
		cout << Ptr->key << " ";
		if (Ptr->left != NULL){

			PrintPreOrderPrivate(Ptr->left);
		}
		if (Ptr->right != NULL){

			PrintPreOrderPrivate(Ptr->right);
		}
	}else{
		cout << "The tree is empty." << endl;
	}
}

void BST::PrintPostOrder(){
	PrintPostOrderPrivate(root);
}

void BST::PrintPostOrderPrivate(node_of_tree* Ptr){

	if(root != NULL){
		if (Ptr->left != NULL){

			PrintPostOrderPrivate(Ptr->left);
		}
		if (Ptr->right != NULL){

			PrintPostOrderPrivate(Ptr->right);
		}cout << Ptr->key << " ";
	}else{
		cout << "The tree is empty." << endl;
	}
}

bool BST::SearchTree(std::string key, node_of_tree * &target){
	return SearchTreePrivate(key, root, target);

}

bool BST::SearchTreePrivate(std::string key, node_of_tree* Ptr,node_of_tree* &target){
	target=new node_of_tree;
	if (Ptr != NULL){
		if(key == Ptr->key){
			target->key=Ptr->key;
			target->times = Ptr->times;
			return true;
		}else{
			if(key<Ptr->key){
				return SearchTreePrivate(key, Ptr->left, target);
			}else{
				return SearchTreePrivate(key, Ptr->right, target);
			}
		}
	}else{
		return false;
	}

}



