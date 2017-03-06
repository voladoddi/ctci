//
//  graph_knights_tour_chessboard_dijkstra.cc
//  IKprobs
//
//  Created by Pooja Voladoddi on 3/6/17.
//  Copyright (c) 2017 none. All rights reserved.
//

/*
 * Complete the function below.
 */

#include<utility>
#include<unordered_set>
#include<unordered_map>
#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;


// ------ UTIL -------
/* all required structures for Graph */
typedef pair<int,int> Vertex;

/* all criteria required to get a vertex */
typedef pair<Vertex, int> MyPairType;


struct CompareSecond
{
    bool operator()(const MyPairType& left, const MyPairType& right) const
    {
        return left.second < right.second;
    }
};

Vertex get_min_distance_vertex(map<Vertex,int> distMap)
{
    pair<Vertex, int> min  = *min_element(distMap.begin(), distMap.end(), CompareSecond());
    return min.first;  // compare (int) distances to get min dist, return vertex.
}

/* count moves */
int countMoves(Vertex target, unordered_map<Vertex,Vertex> pmap)
{
    int moves = 0;
    Vertex curr = target;
    while(pmap[curr])
        // COMPILE ERROR : no match for ‘operator[]’ (operand types are ‘std::unordered_map, std::pair >’ and ‘Vertex {aka std::pair}’)
    {
        moves+=1;
        curr = pmap[curr];
        // COMPILE ERROR : no match for ‘operator[]’ (operand types are ‘std::unordered_map, std::pair >’ and ‘Vertex {aka std::pair}’)
    }
    
    return moves;
}

/* get neighbours */
vector<Vertex> get_neighbours(Vertex curr, int rows, int cols)
{
    vector<Vertex> n;
    if (curr.first <rows && curr.second <cols && curr.first >=0 && curr.second >=0)
    {
        if( curr.first+1 < cols && curr.second+2 < rows)
            n.push_back(make_pair(curr.first+1,curr.second+2));
        if( curr.first+2 < cols && curr.second+1 < rows)
            n.push_back(make_pair(curr.first+2,curr.second+1));
        if( curr.first+2 < cols && curr.second-1 < rows)
            n.push_back(make_pair(curr.first+2,curr.second-1));
        if( curr.first+1 < cols && curr.second-2 < rows)
            n.push_back(make_pair(curr.first+1,curr.second-2));
        
        if( curr.first-1 < cols && curr.second+2 < rows)
            n.push_back(make_pair(curr.first-1,curr.second+2));
        if( curr.first-2 < cols && curr.second+1 < rows)
            n.push_back(make_pair(curr.first-2,curr.second+1));
        if( curr.first-2 < cols && curr.second-1 < rows)
            n.push_back(make_pair(curr.first-2,curr.second-1));
        if( curr.first-1 < cols && curr.second-2 < rows)
            n.push_back(make_pair(curr.first-1,curr.second-2));
    }
    return n;
    
}

/* get distance */
int distance_between_vertices(Vertex source, Vertex target)
{
    float x =  (source.first - target.first)*(source.first - target.first);
    float y =  (source.second - target.second)*(source.second - target.second);
    return (int) sqrt(x+y);
}

// ---------------
int minimumMoves(int rows, int cols, int startx, int starty, int endx, int endy) {
    
    
    Vertex source = make_pair(startx,starty);
    Vertex target = make_pair(endx,endy);
    
    map<Vertex,int> distanceMap;                // distance is the minimum distance required to reach this current visited vertex.
    unordered_map<Vertex,Vertex> pathMap;       // pathMap is to trace the path until current visited Vertex.
    unordered_set<Vertex> Q;                    // Q is a set of vertices in chessboard graph.
    
    // initialize Graph ===> O(N^2) assuming rows = cols = n in a chessboard.
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j)
        {
            Q.insert(make_pair(i,j));
        }
    }
    
    // Iterate over set, and then assign distanceMap and pathMap values.
    for ( auto it = Q.begin(); it != Q.end(); ++it )
    {
        distanceMap[it++] = INT_MAX;
    }
    
    // Make distanceMap[source] = 0;
    distanceMap[source] = 0;
    
    // Dijkstra's.
    // Ref 1 : finding minimum in map -- http://stackoverflow.com/questions/2659248/finding-minimum-value-in-a-map
    while(!Q.empty())
    {
        Vertex currVertex = get_min_distance_vertex(distanceMap);
        if(currVertex.first==target.first && currVertex.second==target.second){
            return countMoves(currVertex, pathMap);
        }
        
        Q.erase(Q.find(currVertex));
        vector<Vertex>neighbours = get_neighbours(currVertex,rows,cols);
        if(neighbours.empty())
            break;
        
        for(auto it = neighbours.begin(); it!= neighbours.end();it++)
        {
            int updateDist = distanceMap[currVertex] + distance_between_vertices(currVertex,*it);
            if (updateDist < distanceMap[*it])
            {
                distanceMap[*it] = updateDist;
                pathMap[*it] = currVertex;
            }
        }
    }
    
    
    // return all valid distances here.
    return -1; //no possible move.
}

int main()
{
    
    int rows = 8;
    int cols = 8;
    int startx = 0;
    int starty = 4;
    int endx = 2;
    int endy = 4;
    
    cout << minimumMoves(rows, cols, startx, starty, endx, endy) << endl;
    
    return 0;
}
