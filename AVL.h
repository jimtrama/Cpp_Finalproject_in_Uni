#ifndef AVL_H
#define AVL_H
#include <string>
using namespace std;

struct aNode{

    std::string key;
    int times;
    aNode* left;
    aNode* right;
    int height;
};

class AVL{

    private:

     	aNode* root;

        aNode* AddLeafPrivate(std::string key, aNode *Ptr);

        int FindHeight(aNode* Ptr);
        int FindDifference(aNode* Ptr);
        int GetHeightOfNode(aNode* Ptr);

        aNode* Balance(string,aNode* Ptr);

        aNode* leftRotate(aNode* Parent);
        aNode* rightRotate(aNode* Parent);


        bool SearchTreePrivate(std::string key, aNode* Ptr, aNode* &target);

        void PrintInOrderPrivate(aNode* Ptr);
        void PrintPreOrderPrivate(aNode* Ptr);
        void PrintPostOrderPrivate(aNode* Ptr);

        aNode* FindSmallestPrivate(aNode* Ptr);

        aNode* RemoveNodePrivate(std::string key, aNode* parent);




    public:

        AVL();

        aNode* CreateLeaf(std::string key);
        void AddLeaf(std::string key);

        bool SearchTree(std::string key, aNode* &target);

        void PrintInOrder();
        void PrintPreOrder();
        void PrintPostOrder();

        aNode* FindSmallest();

        void RemoveNode(std::string key);






};


#endif
