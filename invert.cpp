/*************************************************************************
 *   @file : inverted_index.cpp
 *   @date : 2018-05-21
 *   @author : jiayunwei 
 ************************************************************************/
#include "invert.h"

Invert::Invert(const std::string fieldname, const SEGMENTTYPE type):
    _fieldname(fieldname), _type(type) {
    }

Invert::~Invert() {
}

std::vector<std::string> Invert::Segment (const std::string& content) {
    std::vector<std::string> terms;
    switch(_type) {
        case SPACESEGMENT:
            SplitString(content, terms, " ");
            break;
        case COMMASEGMENT:
            SplitString(content, terms, ",");
            break;
        default:
            break;

    }
    return terms;
}


void Invert::SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c) {
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2-pos1));
         
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}


void Invert::AddDocument(int docid, const std::string& content) {
    std::vector<std::string> terms;
    terms = Segment(content);
    for (auto iter = terms.begin(); iter != terms.end(); iter++) {
        if(_tempInvertTable.find(*iter) == _tempInvertTable.end()) {
            std::set<int> temp;
            temp.insert(docid);
            _tempInvertTable[*iter] = temp;
        }
        else {
            _tempInvertTable[*iter].insert(docid);
        }
    }
}

void Invert::Print() {
    for(auto iter = _tempInvertTable.begin(); iter != _tempInvertTable.end(); iter++) {
        std::cout <<  iter->first << ":";
        for(auto it = _tempInvertTable[iter->first].begin(); it != _tempInvertTable[iter->first].end(); it++) {
            std::cout << *it << ",";
        }
        std::cout << std::endl;
    }
}
