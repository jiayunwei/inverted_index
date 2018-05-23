/*************************************************************************
 *   @file : inverted_index.h
 *   @date : 2018-05-21
 *   @author : jiayunwei 
 ************************************************************************/
#ifndef _INVERTED_H
#define _INVERTED_H
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include<fstream>

enum SEGMENTTYPE {
    SPACESEGMENT = 0,
    COMMASEGMENT = 1,
};

class Invert {
    public:
        Invert(const std::string fieldname, const SEGMENTTYPE type);
        ~Invert();
        void AddDocument(int docid, const std::string& content);
        void Serialize(const std::string &indexpath);
        void Print();
    private:
        std::map<std::string, std::set<int> > _tempInvertTable;
        std::string _fieldname;
        SEGMENTTYPE _type;
    private:
        std::vector<std::string> Segment(const std::string& content);
        void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
};
#endif
