#include "AVL.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


AVL::AVL(){
    root = NULL;
}

int AVL::GetHeightOfNode(aNode * Ptr)
{
    if(Ptr==NULL)
        return 0;
    else
        return Ptr->height;
}
int AVL::FindHeight(aNode* Ptr){
    int h=0;
    if(root == NULL){
        cout << "The avl tree is empty." << endl;
        return h;
    }else{
        if (Ptr !=NULL){
            int leftHeight = FindHeight(Ptr->left);          //Find the height of the left subtree.
            int rightHeight = FindHeight(Ptr->right);        //Find the height of the right subtree.
            if (leftHeight > rightHeight){
                h = leftHeight + 1;
            }else{                                                  //Get the max height and return it
                h = rightHeight + 1;
            }
        }return h;
    } return h;
}



int AVL::FindDifference(aNode* Ptr){

    int leftHeight = GetHeightOfNode(Ptr->left);                             //Find the Height of the left and right Subtrees and get the difference.
    int rightHeight = GetHeightOfNode(Ptr->right);                           //diff >= 1 : Left subtree is bigger.
    int diff = leftHeight - rightHeight;                                     //diff <= -1 : Right subtree is bigger.
    return diff;

}

aNode* AVL::Balance(string key,aNode *Ptr){

    int balance = FindDifference(Ptr);


    if (balance > 1 && key < Ptr->left->key)
        return rightRotate(Ptr);


    if (balance < -1 && key > Ptr->right->key)
        return leftRotate(Ptr);


    if (balance > 1 && key > Ptr->left->key)
    {

        Ptr->left = leftRotate(Ptr->left);                  //Left-Right Case is when the node that causes the tree to be imbalanced is
        return rightRotate(Ptr);
    }


    if (balance < -1 && key < Ptr->right->key)
    {

        Ptr->right = rightRotate(Ptr->right);               //Right-Left Case is when the node that causes the tree to be imbalanced is
        return leftRotate(Ptr);
    }
    return Ptr;
}

aNode* AVL::leftRotate(aNode* x){

    aNode *y = x->right;
    aNode *T2 = y->left;


    y->left = x;
    x->right = T2;


    x->height = max(GetHeightOfNode(x->left),
                    GetHeightOfNode(x->right)) + 1;
    y->height = max(GetHeightOfNode(y->left),
                    GetHeightOfNode(y->right)) + 1;


    return y;
}

aNode* AVL::rightRotate(aNode* y){

    aNode *x = y->left;
    aNode *T2 = x->right;


    x->right = y;
    y->left = T2;


    y->height = max(GetHeightOfNode(y->left),
                    GetHeightOfNode(y->right)) + 1;
    x->height = max(GetHeightOfNode(x->left),
                    GetHeightOfNode(x->right)) + 1;


    return x;
}





aNode* AVL::CreateLeaf(string key){

    aNode* n = new aNode;                                   //create a new leaf(node) for the tree using the nNode struct. Every node has a key, the times the word appears
    n->key = key;                                           //and a left and right pointer, pointing to the children of the node. At the begining, those ptrs are NULL.
    n->times = 1;
    n->left = NULL;
    n->right = NULL;
    n->height=1;
    return n;
}

void AVL::AddLeaf(std::string key){
    root=AddLeafPrivate(key, root);
}

aNode* AVL::AddLeafPrivate(std::string key, aNode* Ptr){                          //Adding a node to the tree. Everytime a node is added, call the Balance method.


    if(Ptr == NULL){

        return(AVL::CreateLeaf(key));
                                                    //If root is NULL create a node that will be the root.

    }else if(key < Ptr->key){                                                   //If the key passed is less than this node's key add the key to the node's left child

        Ptr->left=AddLeafPrivate(key, Ptr->left);                                         //If this node has a left child, then repeat for the child node.


    }else if(key > Ptr->key){                                                   //Else If the key passed is greater than this node's key add the key to the node's right child

            Ptr->right=AddLeafPrivate(key, Ptr->right);                                        //If this node has a right child, then repeat for the child node

    }else{
        Ptr->times++;
        return Ptr;                                                       //The word already exists, so +1 to the times variable.

    }

    Ptr=Balance(key,Ptr);



    return Ptr;

                                                             //Call the balance method to check if the Tree became unbalanced.
}

bool AVL::SearchTree(std::string key, aNode * &target){
	return SearchTreePrivate(key, root, target);

}
bool AVL::SearchTreePrivate(std::string key, aNode* Ptr,aNode* &target){		//Search the tree for a node containing a key and return a bool statement.
	if (Ptr != NULL){
		if(key == Ptr->key){													//The key is found
			target->key=Ptr->key;												//Pass the needed data of the node to the node ptr target by reference.
			target->times = Ptr->times;
			return true;
		}else{
			if(key<Ptr->key){													//The key is smaller than this node's key. Call the method recursively for the left child of the node.
				return SearchTreePrivate(key, Ptr->left, target);
			}else{
				return SearchTreePrivate(key, Ptr->right, target);				//The key is greater than this node's key. Call the method recursively for the right child of the node.
			}
		}
	}else{
		return false;															//Key is not found.
	}

}

void AVL::PrintInOrder(){
    AVL::PrintInOrderPrivate(root);
}

void AVL::PrintInOrderPrivate(aNode* Ptr){
    if (Ptr!=NULL){                                                            //If the root ptr is not NULL then there is a tree that we can print
                                                   //If the left ptr is not NULL then call the method recursively for the left child.

        AVL::PrintInOrderPrivate(Ptr->left);

        cout << Ptr->key << " \n";                                              //Print this node's key.
                                                        //If the right ptr is not NULL then call the method recursively for the right child.
        AVL::PrintInOrderPrivate(Ptr->right);

    }

}

void AVL::PrintPreOrder(){
	PrintPreOrderPrivate(root);
}
void AVL::PrintPreOrderPrivate(aNode* Ptr){

	if(root != NULL){															//If the root ptr is not NULL then there is a tree that we can print.
		cout << Ptr->key << " ";													//Print this node's key.
		if (Ptr->left != NULL){														//If the left ptr is not NULL then call the method recursively for the left child.

			AVL::PrintPreOrderPrivate(Ptr->left);
		}
		if (Ptr->right != NULL){													//If the right ptr is not NULL then call the method recursively for the right child.

			AVL::PrintPreOrderPrivate(Ptr->right);
		}
	}else{
		cout << "The tree is empty." << endl;
	}
}
void AVL::PrintPostOrder(){
	AVL::PrintPostOrderPrivate(root);
}
void AVL::PrintPostOrderPrivate(aNode* Ptr){

	if(root != NULL){															//If the root ptr is not NULL then there is a tree that we can print
		if (Ptr->left != NULL){														//If the left ptr is not NULL then call the method recursively for the left child.

			AVL::PrintPostOrderPrivate(Ptr->left);
		}
		if (Ptr->right != NULL){													//If the right ptr is not NULL then call the method recursively for the right child.

			AVL::PrintPostOrderPrivate(Ptr->right);
		}cout << Ptr->key << " ";													//Print this node's key.
	}else{
		cout << "The tree is empty." << endl;
	}
}

aNode* AVL::FindSmallest(){

    return AVL::FindSmallestPrivate(root);

}

aNode* AVL::FindSmallestPrivate(aNode* Ptr){

    if(root == NULL){

        cout << "The tree is empty";
        return NULL;

    }else{

        while(Ptr->left!=NULL)
        {
            Ptr=Ptr->left;
        }
        return Ptr;
    }
}

void AVL::RemoveNode(std::string key){
    root=AVL::RemoveNodePrivate(key, root);
}

aNode* AVL::RemoveNodePrivate(std::string key, aNode* root){

    if (root == NULL)
        return root;

    if ( key < root->key )
        root->left = RemoveNodePrivate( key,root->left);

    else if( key > root->key )
        root->right = RemoveNodePrivate( key,root->right);


    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            aNode *temp = root->left?root->left:root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            delete(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            aNode* temp = FindSmallestPrivate(root->right);

            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = RemoveNodePrivate(temp->key,root->right);
        }
    }

    // If the tree had only one node
    // then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(GetHeightOfNode(root->left),GetHeightOfNode(root->right));

    // STEP 3:  BALANCE

    root=Balance(key,root);

    return root;

}




