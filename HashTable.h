#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<iostream>
#include<cstring>
using namespace  std;
class node_of_table {
            public :
            string word;
            int times;
        };
class HashTable
{
    public:
        ~HashTable();
        HashTable();
        HashTable(unsigned long long int);
        int HashFunction(string);//Made documentation
        int HashFunction2(string,int );//Made documentation
        bool addValue(string);//Made documentation
        bool Search(string,node_of_table*&);//Made documentation
        bool Remove(string);//Made documentation
        node_of_table* GetValueAtIndex(int);//Made documentation
        void PrintAll();//Made documentation
        int countWords();//Made documentation
    private:

        unsigned long long int lenght;//Made documentation
        node_of_table *table;//Made documentation

};

#endif // HASHTABLE_H
