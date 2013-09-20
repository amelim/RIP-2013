#include "state.h"

State::State(){
}

double State::distanceToLoc(const Location &loc) const{
  return 0.0;
}

bool State::isGoal(){
  return false;
}

std::vector<State> State::expandState(){

}
