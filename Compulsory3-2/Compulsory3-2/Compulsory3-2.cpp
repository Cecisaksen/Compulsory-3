#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Graph {

private:
    int nodes;
    vector<vector<int>> adjacencyList;

public:
    Graph(int n) : nodes(n), adjacencyList(n) {}

    void addEdge(int node1, int node2) {
        if (node1 >= 0 && node1 < nodes && node2 >= 0 && node2 < nodes) {
            adjacencyList[node1].push_back(node2);
            adjacencyList[node2].push_back(node1);
        }
        else {
            cout << "Invalid node indices for edge insertion." << endl;
        }
    }

    int getNumberOfNodes() const {
        return nodes;
    }

    vector<int> getAdjacentNodes(int node) const {
        return adjacencyList[node];
    }

    vector<int> getAllNodes() const {
        vector<int> allNodes;
        for (int i = 0; i < nodes; ++i) {
            allNodes.push_back(i);
        }
        return allNodes;
    }

    vector<pair<int, int>> getAllEdges() const {
        vector<pair<int, int>> allEdges;
        for (int i = 0; i < nodes; ++i) {
            for (const auto& neighbour : adjacencyList[i]) {
                if (i < neighbour) {
                    allEdges.push_back({ i, neighbour });
                }
            }
        }
        return allEdges;
    }

    bool isEmpty() const {
        return nodes == 0;
    }

    void insertNode() {
        nodes++;
        adjacencyList.push_back({});
    }

    void deleteNode(int node) {
        if (node >= 0 && node < nodes) {
            nodes--;
            adjacencyList.erase(adjacencyList.begin() + node);
            for (auto& neighbors : adjacencyList) {
                auto it = find(neighbors.begin(), neighbors.end(), node);
                if (it != neighbors.end()) {
                    neighbors.erase(it);
                }
            }
        }
        else {
            cout << "Invalid node index for deletion." << endl;
        }
    }

    void insertEdge(int node1, int node2) {
        if (node1 >= 0 && node1 < nodes && node2 >= 0 && node2 < nodes) {
            adjacencyList[node1].push_back(node2);
            adjacencyList[node2].push_back(node1);
        }
        else {
            cout << "Invalid node indices for edge insertion." << endl;
        }
    }

    void deleteEdge(int node1, int node2) {
        if (node1 >= 0 && node1 < nodes && node2 >= 0 && node2 < nodes) {
            auto it1 = find(adjacencyList[node1].begin(), adjacencyList[node1].end(), node2);
            auto it2 = find(adjacencyList[node2].begin(), adjacencyList[node2].end(), node1);

            if (it1 != adjacencyList[node1].end() && it2 != adjacencyList[node2].end()) {
                adjacencyList[node1].erase(it1);
                adjacencyList[node2].erase(it2);
            }
            else {
                cout << "Edge does not exist." << endl;
            }
        }
        else {
            cout << "Invalid node indices for edge deletion." << endl;
        }
    }

    void printList() const {
        for (int i = 0; i < nodes; ++i) {
            cout << "Adjacent nodes to node " << i << ": ";
            for (const auto& neighbor : adjacencyList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void depthFirstPreorderTraversal(int currentNode, vector<bool>& visited) {
        if (!visited[currentNode]) {
            cout << currentNode << " ";
            visited[currentNode] = true;

            for (int neighbor : adjacencyList[currentNode]) {
                depthFirstPreorderTraversal(neighbor, visited);
            }
        }
    }
};

int main() {

    Graph MyGraph(5);

    MyGraph.addEdge(0, 1);
    MyGraph.addEdge(0, 2);
    MyGraph.addEdge(1, 3);
    MyGraph.addEdge(2, 4);

    cout << "Number of nodes: " << MyGraph.getNumberOfNodes() << endl;

    MyGraph.printList();

    cout << "All nodes in the graph: ";
    for (const auto& node : MyGraph.getAllNodes()) {
        cout << node << " ";
    }
    cout << endl;

    cout << "All edges in the graph: ";
    for (const auto& edge : MyGraph.getAllEdges()) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;

    cout << "Is the graph empty? " << (MyGraph.isEmpty() ? "Yes" : "No") << endl;

    MyGraph.insertNode();
    cout << "Number of nodes after inserting a new node: " << MyGraph.getNumberOfNodes() << endl;

    MyGraph.insertEdge(0, 5);
    cout << "All edges after inserting a new edge: ";
    for (const auto& edge : MyGraph.getAllEdges()) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;

    // the triversal worked when i commented this out:) 

   /* MyGraph.deleteNode(2);
    cout << "All nodes after deleting a node: ";
    for (const auto& node : MyGraph.getAllNodes()) {
        cout << node << " ";
    }
    cout << endl;

    MyGraph.deleteEdge(1, 3);
    cout << "All edges after deleting an edge: ";
    for (const auto& edge : MyGraph.getAllEdges()) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;*/

    cout << "Updated adjacency list:" << endl;
    MyGraph.printList();

    cout << "Depth-First Traversal starting from node 0: ";
    vector<bool> visited(MyGraph.getNumberOfNodes(), false);
    MyGraph.depthFirstPreorderTraversal(0, visited);
    cout << endl;


 
    return 0;
}
