#include "Automaton.h"

Automaton:: Automaton()
{
   startState = -1;
}

Automaton:: Automaton(const vector<list<pair<char, int> > >& automaton, int startState, const vector<int>& finalStates)
{
   this->startState = startState;
   this->finalStates = finalStates;
   this->automaton = automaton;
}

void Automaton:: addTransition(int startState, char symb, int endState)
{
   while(startState >= automaton.size() || endState >= automaton.size())
   {
       this->operator++();     
   }
   
   automaton[startState].push_front(make_pair(symb, endState));
} 

void Automaton:: removeTransition(int state, char symbol, int transitionState)
{
   automaton[state].remove(make_pair(symbol, state));
}

Automaton Automaton:: operator++(int)
{
   Automaton a = *this;

   ++(*this);

   return a;
}

Automaton& Automaton:: operator++()
{
   this->automaton.push_back(list<pair<char, int> >()); 
   return *this;   
}

void Automaton:: setStartState(int startState)
{
   this->startState = startState;
}

void Automaton:: markFinalStates(const vector<int>& finalStates)
{
   this->finalStates = finalStates;
}

int main()
{
   Automaton ni = Automaton();
 
    
   ni.addTransition(0, 'a', 1);

   return 0;
}
