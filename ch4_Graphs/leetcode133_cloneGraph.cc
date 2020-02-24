/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    
    // typedef for easier
    typedef UndirectedGraphNode udgNode;
    
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
    {
        // if empty graph
        if (!node) return nullptr;
        
        // map for visited.
        unordered_set<udgNode*> visited;
        
        // recur - DFS
        udgNode* result = cloneGraphHelper(node, visited);
        
        return result;
        
    }
    
    udgNode* cloneGraphHelper(udgNode* node, unordered_set<udgNode*> &visited)
    {
        if(visited.find(node)!=visited.end()) //found node in visited set.
            return node;
        else
        {
            udgNode* clone = new udgNode(node->label); //visit / process/ clone the node.
            visited.insert(clone);                     //mark the node as visited.
            
            vector<udgNode*>::iterator it;             // process the neighbours.
            for(it=node->neighbors.begin(); it!=node->neighbors.end(); ++it)
                clone->neighbors.push_back(cloneGraphHelper(*it,visited));
            return clone;
        }
    }
    
};