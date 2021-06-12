#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>


class IterTree
{
private:
    std::map<std::string, std::string> m_map;
    int depth;
    int order;

public:
    IterTree() 
    : depth(1) , order(2)
    {  }
    
    IterTree(std::map<std::string, std::string> mapInit, int _depth, int _order)
    : m_map(mapInit), depth(_depth), order(_order)
    {  }

    ~IterTree();
};


///////////////////////////////////
// Playing around with a tree class
///////////////////////////////////


std::string strings_to_n(int n)
{
	std::string out;
	for(int i=1; i<=n; i++)
		out += std::to_string(i);
	
	return out;
}

/////////////////////////////  MAPS  ///////////////////////////////////////

using Map = std::vector<std::pair<std::string, std::string>>;

////////////////////////////////////////////////////////////////////////////

void printMap(std::vector<std::pair<std::string, std::string>> inMap)
{
	std::cout << "--------------" << std::endl;
	for(const auto& elem : inMap)
	{
		std::cout << elem.first << " --> " << elem.second << std::endl;
	}
	std::cout << "--------------" << std::endl;
}

////////////////////////////////////////////////////////////////////////////

void mapBuild(Map& seed, int maxDepth, int order)
{

	for(int i = 1; i <= maxDepth; i++)
	{
		Map next_pairs;
		// For every current edge in tree
		for (auto &pair : seed)
		{
			// Find the edges that are on the tips
			if (pair.second.size() == i)
			{
				std::string digit_list = strings_to_n(order);

				// Add the newly generated edges
				for(auto &digit : digit_list)
					next_pairs.push_back({ pair.second, pair.second + digit });
			}
		}

		// Adding the next set of leaves to the tree
		for (const auto& new_pairs : next_pairs)
		{
			seed.push_back(new_pairs);
		}
	}
}


////////////////////////////////////////////////////////////////////////////

// vect2f treeStr2Vect2f(
// 					  vect2f &n0,                              // Normal vector we rotate.
// 					  float scaleParam,          			   // Parameter for scaling the 
// 					  std::vector<float> &thetas,              // State of tree based on index-ordered thetas
// 					  std::string in
// 					 )
// {

// 	//TODO Exception for wrong length of thetas vs order

// 	mat2f rotation;
// 	vect2f sum;

// 	std::vector<vect2f> rotatedVlist;
// 	int elem = 0;
// 	float theta;
// 	for(auto i : in)
// 	{
// 		int j = i - '1';

// 		theta = 0;
// 		for(int k = 0; k < j+1; k++)
// 			theta += thetas[j];
		
// 		rotation.setRotation(theta);
// 		rotatedVlist.push_back(scales[elem] * rotation.dot(n0));
// 		elem += 1;
// 	}

// 	for (auto &i : rotatedVlist)
// 		sum = sum + i;
	
// 	return sum;
// }
