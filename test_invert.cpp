/*************************************************************************
 *   @file : main.cpp
 *   @date : 2018-05-21
 *   @author : jiayunwei 
 ************************************************************************/
#include "invert.h"

int main() {
    std::string content[] = {"i am jiayunwei", "my name is jiayunwei", "jiayunwei is my name"};
    Invert invert("content", SPACESEGMENT);
    for(int i = 0; i < 3; i++) {
        invert.AddDocument(i, content[i]);
    }
    invert.Print();
    return 0;
}
