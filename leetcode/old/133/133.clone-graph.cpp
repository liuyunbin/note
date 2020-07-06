/*
 * [133] Clone Graph
 *
 * https://leetcode.com/problems/clone-graph/description/
 *
 * algorithms
 * Medium (25.16%)
 * Total Accepted:    134.1K
 * Total Submissions: 532.9K
 * Testcase Example:  '{}'
 *
 * 
 * Clone an undirected graph. Each node in the graph contains a label and a
 * list of its neighbors.
 * 
 * 
 * 
 * 
 * OJ's undirected graph serialization:
 * 
 * 
 * Nodes are labeled uniquely.
 * 
 * 
 * We use # as a separator for each node, and , as a separator for node label
 * and each neighbor of the node.
 * 
 * 
 * 
 * 
 * As an example, consider the serialized graph {0,1,2#1,2#2,2}.
 * 
 * 
 * 
 * The graph has a total of three nodes, and therefore contains three parts as
 * separated by #.
 * 
 * First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
 * Second node is labeled as 1. Connect node 1 to node 2.
 * Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming
 * a self-cycle.
 * 
 * 
 * 
 * 
 * Visually, the graph looks like the following:
 * 
 * ⁠      1
 * ⁠     / \
 * ⁠    /   \
 * ⁠   0 --- 2
 * ⁠        / \
 * ⁠        \_/
 * 
 * 
 * 
 * 
 */
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
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL)
            return NULL;
        unordered_map<int, UndirectedGraphNode*> dict;
        return dfs(node, dict);
    }
    UndirectedGraphNode *dfs(UndirectedGraphNode* node, unordered_map<int, UndirectedGraphNode*>& dict) {
        if (node == NULL)
            return NULL;
        if (dict.find(node->label) != dict.end())
            return dict[node->label];
        UndirectedGraphNode* new_node = new UndirectedGraphNode(node->label);
        dict[new_node->label] = new_node;
        for (auto it:node->neighbors)
            new_node->neighbors.push_back(dfs(it, dict));
        return new_node;
    }
};
