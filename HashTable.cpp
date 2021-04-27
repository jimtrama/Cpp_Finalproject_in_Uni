#include "HashTable.h"
HashTable::~HashTable()
{
    delete[] table;
}
HashTable::HashTable()
{
    lenght=0;

}
HashTable::HashTable(unsigned long long int l)
{
    //creating an empty table
    lenght=l;
    table=new node_of_table[lenght];
    for(int i =0 ;i<lenght;i++)
    {
        table[i].word=new char[30];
        table[i].times=0;
        table[i].word="NULL";
    }

}
//Hash Function that sums the values of the letters mod the size of the table
int HashTable::HashFunction(string key)
{
    int index=0;
    for(int i =0 ; i<key.length();i++)
        index+=(int)key[i];
    index=index%lenght;
    return index;

}
//2nd Hash Function
int HashTable::HashFunction2 (string key ,int see)
{
   int seed = see;
   unsigned long index = 0;
   for(int i = 0; i <key.length(); i++)
   {
      index += (index * seed) + (int)key[i];
   }
   return index % lenght;
}
bool HashTable::addValue(string key)
{
    //Getting the result of the hash function
    int index = HashFunction(key);

    //Case 1. the word is already in the table spot
    if(table[index].word==key)
    {
        table[index].times++;
        return true;
    }
    //Case 2. the spot is empty or deleted
    if(table[index].word=="NULL"||table[index].word=="NNULL")
    {
        table[index].word=key;
        table[index].times++;
        return true;
    }
    //Case 3. the spot is occupied

    int temp;
    //Finding the previous element of the table
    if(index==0)
    {
        temp=lenght-1;
    }
    else
        temp=index-1;
    //looping throw the table to find the next available spot {Double hashing}
    int seed=0;
    while(table[index].word!="NULL"&&temp!=index&&seed!=lenght&&table[index].word!="NNULL"&&table[index].word!=key)
    {
        if(index==lenght-1)
        {
           index=0;
        }else
        {
           index=HashFunction2(key,seed);
           seed++;
        }
    }
    //The spot was empty or deleted
    if(table[index].word=="NULL"||table[index].word=="NNULL")
    {
        table[index].word=key;
        table[index].times++;
        return true;
    }
    //The spot had the word already
    if (table[index].word==key)
    {
        table[index].times++;
        return true;
    }
    //The table was full
    return false;

}
bool HashTable::Search(string key,node_of_table *&t)
{
    //Getting the result of the hash function
    int index=HashFunction(key);
    //Finding the previous element of the table
    int temp;
    if(index==0)
    {
        temp=lenght-1;
    }
    else
        temp=index-1;
    //Loping throw table until the key matches the word OR table[index]==NULL OR
    //we made a circle of the table
    int seed=0;
    while(table[index].word!=key&&table[index].word!="NULL"&&temp!=index&&seed!=lenght)
    {

        if(index==lenght-1)
            index=0;
        else{
            index=HashFunction2(key,seed);
            seed++;
        }

    }

    //Checking if we found the key
    if(table[index].word==key)
    {
        t->times=table[index].times;
        t->word=table[index].word;
        return true;
    }
    //If not return false
    return false;


}
bool HashTable::Remove(string key)
{
    int index=HashFunction(key);
    int temp;
    //for finding the previous item in the table
    if(index==0)
    {
        temp=lenght-1;
    }
    else
        temp=index-1;
    //Searching for the element...
    int seed =0 ;
    while(table[index].word!=key&&table[index].word!="NULL"&&temp!=index&&seed!=lenght)
    {
        if(index==lenght-1)
            index=0;
        else{
            index=HashFunction2(key,seed);
            seed++;
        }
    }
    //If found it the replace the spot with NNULL and 0
    if(table[index].word==key)
    {
        table[index].times=0;
        table[index].word="NNULL";
        return true;
    }
    //Else the key not exists
    return false;
}
node_of_table* HashTable::GetValueAtIndex(int key)
{
    node_of_table *t=new node_of_table;
    t->word=new char [20];
    t->word=table[key].word;
    t->times=table[key].times;
    return t;
}

void HashTable::PrintAll()
{
    node_of_table * temp = new node_of_table ;
    for(int i =0;i<lenght;i++){
        temp = GetValueAtIndex(i);
        cout<<temp->word<<":"<<temp->times<<endl;

    }
}
int HashTable::countWords()
{
    int words=0;
    for(int i =0;i<lenght;i++)
    {
        node_of_table *t = new node_of_table;
        t= GetValueAtIndex(i);
        if(t->word!="NULL"&&t->word!="NNULL")
            words+=t->times;
    }
    return words;
}


