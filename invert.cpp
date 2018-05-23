/*************************************************************************
 *   @file : inverted_index.cpp
 *   @date : 2018-05-21
 *   @author : jiayunwei 
 ************************************************************************/
#include "invert.h"

#include <fcntl.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>
#include <sys/types.h>  
#include <sys/stat.h>  
//linux
bool create_dir(const std::string& dir) {
    if (access(dir.c_str(), 0) == -1)  {  
        int flag=mkdir(dir.c_str(), 0777);
        if (flag) {
            return false;
        }
    }
    return true;
}

template<typename T>
std::ostream& binary_write(std::ostream& stream, const T& value){
    return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

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

void Invert::Serialize(const std::string &indexpath) {

    if (!create_dir(indexpath)) {
        std::cout << "creat indexpath error" << std::endl;
        return;
    }

    std::ofstream stream_trm(indexpath + "/index.trm", std::ios::binary | std::ios::out | std::ios::app);
    std::ofstream stream_doc(indexpath + "/index.doc", std::ios::binary | std::ios::out | std::ios::app);
    stream_doc.seekp(0, std::ios::end);
    uint64_t total_offset = stream_doc.tellp();
    for(auto iter = _tempInvertTable.begin(); iter != _tempInvertTable.end(); iter++) {
        stream_trm << iter->first << " " << total_offset << std::endl;
        binary_write(stream_doc, (int)iter->second.size());
        total_offset +=  (iter->second.size() + 1) * 4;
        for(auto it = _tempInvertTable[iter->first].begin(); it != _tempInvertTable[iter->first].end(); it++) {
            binary_write(stream_doc, *it);
        }
    }
    stream_trm.close();
    stream_doc.close();
}
