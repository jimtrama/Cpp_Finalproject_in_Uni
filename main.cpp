#include <iostream>
#include <fstream>
#include<string>
#include<ctime>

#include "HashTable.h"
#include "BST.h"
#include "AVL.h"

//name of the file
#define file_name "med.txt"
//The size of Q that will be searched
#define Words_to_Search 100000
//Table Size
#define table_size 1000000

int working();
using namespace std;
bool isLetter(char a)
{
    if((a>='a'&&a<='z')||(a>='A'&&a<='Z'))
        return true;
    else
        return false;
}
int Count_words_in_file()
{
    ifstream file;
    file.open(file_name);
    int words=0;
    string line;

    while (!file.eof())
    {

            getline(file,line);
            for(int i =0 ;i<line.length();i++)
            {
                if(isLetter(line[i])&&!isLetter(line[i+1]))
                {
                    words++;
                }
            }


    }
    return words;
}
int main()
{

   working();

}
int working()
{

    ifstream file;
    string line;

    HashTable table(table_size);
    BST tree;
    AVL test;


    string * words_to_search=new string[Words_to_Search] ;



    //Opening the file
    file.open(file_name);
    if(file)
        cout<<"file opened"<<endl;
    else
        cout<<"file not found"<<endl;
    //seeding the randomizer
    srand(time(0));
    //choice takes{0,1,2} for randomly choosing to add or not the word
    //k is the number of the words to be searched
    int choice,k=0;

    int spaces=0;

    clock_t start_file = clock();

    while(!file.eof())
    {
        choice=rand()%3;

        getline(file,line);

        for(int i =0;i<line.length();i++)
        {

            string word;
            char *word_=new char [25];
            int j=0;
            while(isLetter(line[i]))
            {

                word_[j]=line[i];
                i++;
                j++;
            }
            word_[j]='\0';
            word.append(word_);

            if(word!=""&&word!=" "&&word!="  ")
            {



                test.AddLeaf(word);

                if(!table.addValue(word))
                    cout<<"Not enough Space at the Table"<<endl;
                if(!tree.AddLeaf(word))
                    cout<<"something went wrong in tree"<<endl;
                if(choice==2&&k<Words_to_Search-1){
                        words_to_search[k]=word;
                        k++;
                }
            }else
                spaces++;

        }

    }
    cout<<"Spaces:"<<spaces<<endl;
    clock_t stop_file = clock();


    double time_for_file = (double) (stop_file-start_file) / CLOCKS_PER_SEC * 1.0;

    node_of_table *t =new node_of_table;

    clock_t start = clock();
    for(int i =0 ;i<k;i++){
        if(!table.Search(words_to_search[i],t))
            cout<<"Not Found in table"<<endl;

    }
    clock_t end = clock();
    double time_for_table = (double) (end-start) / CLOCKS_PER_SEC * 1.0;


    node_of_tree *tr=new node_of_tree;


    start = clock();
    for(int i =0 ;i<k;i++){

            if(!tree.SearchTree(words_to_search[i],tr))
                cout<<"Not found in tree"<<endl;

    }
    end = clock();
    double time_for_tree = (double) (end-start) / CLOCKS_PER_SEC * 1.0;

    aNode * tra = new aNode;
    start = clock();
    for(int i =0 ;i<k;i++){

            if(!test.SearchTree(words_to_search[i],tra))
                cout<<"Not found in tree"<<endl;

    }
    end = clock();
    double time_for_AVL = (double) (end-start) / CLOCKS_PER_SEC * 1.0;





    cout<<"File :"<<file_name<<endl;
    cout<<"It took :"<<time_for_file<<" to read the file"<<endl;
    cout<<"For :"<<k<<" Searches"<<endl;
    cout<<"Time for Table "<<time_for_table<<"sec."<<endl;
    cout<<"Time for AVL Tree "<<time_for_AVL<<"sec."<<endl;
    cout<<"Time for Tree "<<time_for_tree<<"sec."<<endl;

    cout<<"Words in file : "<<Count_words_in_file();
    return 0;
}
