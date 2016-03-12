
#include <cstdio>
#include "SuffixTrie.h"

SuffixTrie:: SuffixTrie(const string& T)
{
   this->T = T;
   buildSuffixTrie(T);
}


SuffixTrie:: SuffixTrie(const SuffixTrie& other)
{
   copySuffixTrie(other);

}

SuffixTrie& SuffixTrie:: operator= (const SuffixTrie& other)
{
   if (this != &other)
   {
      deleteSuffixTrie();
      copySuffixTrie(other);
   }

   return *this;
}

SuffixTrie:: ~SuffixTrie()
{
   deleteSuffixTrie();
}

void SuffixTrie:: deleteSuffixTrie()
{
   delete auxiliary ;
   deleteSuffixNodes(root);
}

void SuffixTrie:: deleteSuffixNodes(Node* &curNode)
{
   for(int i = 0; i < MAX_NUM_ELEMENTS; ++i)
   {
      if (curNode->nodes[i] != NULL)
      {
         deleteSuffixNodes(curNode->nodes[i]);
      }
   }
   delete curNode;
   curNode = NULL;
}

void SuffixTrie:: copySuffixTrie(const SuffixTrie& other) 
{
   this->T = other.T;
   buildSuffixTrie(other.T);
}

void SuffixTrie:: buildSuffixTrie(const string& T)
{
   auxiliary = new Node();
   root = new Node();

   for(int i = 0; i < MAX_NUM_ELEMENTS; ++i)
   {
      auxiliary->nodes[i] = root;
   }

   root->suffix_link = auxiliary;   

   top = root;

   for(int i = 0; i < T.size(); ++i)
   {
      appendCharacter(T[i]);
   }  
}

void SuffixTrie:: appendCharacter(char f)
{
   Node* curNode = top, *newNode, *prevNode; 
  
   while(!has_character(curNode, f)) 
   {
      newNode = new Node();
      newNode->is_final = true;
 
      curNode->nodes[f - (int)'a'] = newNode; 
      if (curNode != root) 
      {
         curNode->is_final = false;
      }

      if (curNode != top)
      {
         prevNode->suffix_link = newNode;
      }

      curNode = curNode->suffix_link; 
      prevNode = newNode; 
   }

   prevNode->suffix_link = curNode->nodes[f - (int)'a'];
   top = top->nodes[f - (int)'a'];
}

bool SuffixTrie:: has_character(const Node* curNode, char t) const
{
   return curNode->nodes[t-(int)'a'] != NULL;
}

bool SuffixTrie:: is_substring(const string& other) const
{
   Node* curNode = root, *nextNode;
   int i = 0; 

   while (i < other.size())
   {
      nextNode = curNode->nodes[other[i] - (int)'a'];
      if (nextNode != NULL)
      {
         curNode = nextNode; 
         ++i;
      } else {
         return false;
      } 
   } 
   return true; 
}

bool SuffixTrie:: is_suffix(const string& other) const
{
   Node* curNode = root, *nextNode;
   int i = 0; 

   while (i < other.size())
   {
      nextNode = curNode->nodes[other[i] - (int)'a'];
      if (nextNode != NULL)
      {
         curNode = nextNode; 
         ++i;
      } else {
         return false;
      } 
   } 
   return curNode->is_final; 
}

int main(int argc, char** argv)
{
    SuffixTrie trie("cacao");

    return 0;
}
