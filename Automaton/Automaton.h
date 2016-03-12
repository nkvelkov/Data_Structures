#ifndef AUTOMATON_H_INCLUDED
#define AUTOMATON_H_INCLUDED

#include <vector>
#include <list>

using namespace std;

class Automaton
{
   public:
      Automaton();
      Automaton(const vector<list<pair<char, int> > >&, int, const vector<int>&);

      Automaton operator++ (int);
      Automaton& operator++ ();
  
      void setStartState(int);
      void markFinalStates(const vector<int>&);
      void addTransition(int, char, int);
      void removeTransition(int, char, int);

   private:
      int startState; 
      vector<int> finalStates;
      vector<list<pair<char, int> > > automaton; 
};

#endif //AUTOMATON_H_INCLUDED
