#pragma once
#include "Graph.h"
#include <iostream>
#include <fstream>

Graph* LoadFromFile(WCHAR* szFilePath);
void SaveToFile(Graph* graph, WCHAR* szPath);
