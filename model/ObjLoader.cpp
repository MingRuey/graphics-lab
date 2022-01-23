#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>

#include "ObjLoader.h"


void parse_v_vn(const string &line, float &d1, float &d2, float &d3) {
    string skip;
    std::stringstream ss(line);
    ss >> skip;
    ss >> d1;
    ss >> d2;
    ss >> d3;
}

face parse_f(const string &line) {
    char skip;
    std::stringstream ss(line);
    ss >> skip;

    uint32_t parsed[6] = {0};
    for (int i = 0; i < 3; i++) {
        string item;
        ss >> item;

        size_t sep;
        if ((sep = item.find("//")) == string::npos) throw std::exception("Parse face failed");
        parsed[2 * i] = std::atoi(item.substr(0, sep).c_str());
        parsed[2 * i + 1] = std::atoi(item.substr(sep + 2).c_str());
    }
    return {parsed[0], parsed[2], parsed[4], parsed[1], parsed[3], parsed[5]};
}

ObjLoader::ObjLoader(string file) {
    std::ifstream infile(file);
    if (infile.fail()) {
        std::cout << "Invalid file path '" << file << "'" << std::endl;
        exit(1);
    }

    int l = 0;
    float d1, d2, d3;
    string line;
    while (std::getline(infile, line)) {
        l++;
        if (line.rfind("v ", 0) == 0) {
            parse_v_vn(line, d1, d2, d3);
            vertices.emplace_back(d1, d2, d3);
        } else if (line.rfind("vn ", 0) == 0) {
            parse_v_vn(line, d1, d2, d3);
            normals.emplace_back(d1, d2, d3);
        } else if (line.rfind("f ", 0) == 0) {
            face res = parse_f(line);
            faces.push_back(res);
        } else {
            // unexpected line handling
            // not comment && not empty
            if (line.rfind('#', 0) != 0) {
                if (!std::all_of(line.begin(), line.end(), isspace)) {
                    std::cout << "WARNING: ignore unexpected line " << l << " in obj file " << file << std::endl;
                }
            }
        }
    }
}
