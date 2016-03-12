#ifndef SUFFIXTRIE_H_INCLUDED
#define SUFFIXTRIE_H_INCLUDED

#include <string>
 
using namespace std; 

#define MAX_NUM_ELEMENTS 28

 
struct Node
{ 
   Node() 
   {
      suffix_link = NULL;
      for (int i = 0; i < MAX_NUM_ELEMENTS; ++i) {
         nodes[i] = NULL;
      }
      is_final = true; 
   }
   Node* suffix_link;
   Node* nodes[MAX_NUM_ELEMENTS];
   bool is_final;
};

class SuffixTrie
{
    public:

       SuffixTrie(const string& T);
       SuffixTrie(const SuffixTrie&);
       SuffixTrie& operator = (const SuffixTrie&);
       virtual ~SuffixTrie(); 

       void appendCharacter(char);

       bool is_substring(const string&) const;
       bool is_suffix(const string&) const; 
  
       void print_suffix_trie() const;

    private:
       void copySuffixTrie(const SuffixTrie&);
       void deleteSuffixTrie();
     
       void buildSuffixTrie(const string&);
       void deleteSuffixNodes(Node* &);
      
       bool has_character(const Node*, char) const;

       Node* auxiliary;      
       Node* root;
       Node* top;

       string T;       
};

#endif // SUFFIXTRIE_H_INCLUDED
