#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  long long minimumCost(string source, string target, vector<char> &original,
                        vector<char> &changed, vector<int> &cost) {
    // dijkstra algorithm (Array data structure)
    unordered_map<char, vector<pair<char, int>>> edges;
    unordered_map<pair<char, char>, long long> minimumCosts;

    // Construct graph
    for (int i = 0; i < original.size(); ++i) {
      auto it = edges.find(original[i]);
      if (it == edges.end()) {
        edges.emplace(original[i],
                      vector<pair<char, int>>{{changed[i], cost[i]}});
      } else {
        it.;
      }
    }

    char u = source[0];
    char v = target[0];

    for ()

      return 0;
  }
};
