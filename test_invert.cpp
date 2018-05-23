/*************************************************************************
 *   @file : main.cpp
 *   @date : 2018-05-21
 *   @author : jiayunwei 
 ************************************************************************/
#include "invert.h"
/*
   build user index {"id": 1, "desc": "i am jiayunwei"}
*/
int main() {
    std::string indexname = "user";
    //simple i use array
    std::string content[] = {"i am jiayunwei", "my name is jiayunwei", "jiayunwei is my name"};
    Invert invert("desc", SPACESEGMENT);
    for(int i = 0; i < 3; i++) {
        invert.AddDocument(i, content[i]);
    }
    invert.Serialize(indexname);
    return 0;
}
