#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>

#include "edge.h"
#include "graph.h"
#include "vertex.h"

using std::string;
using std::vector;

class CSVParser {
    public:
        static vector<vector<string> > parseCSV(string filename);
        static Graph dataToGraph(vector<vector<string> >& data);
};
