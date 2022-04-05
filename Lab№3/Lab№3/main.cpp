#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>
#include <iomanip>
#include <string>
#include <chrono>
using namespace std;

#define N 5

#define INF INT_MAX

struct Node
{
    vector<pair<int, int>> path;

    int reducedMatrix[N][N];

    int cost;

    int vertex;

    int level;
};

Node* newNode(int parentMatrix[N][N], vector<pair<int, int>> const& path,
    int level, int i, int j)
{
    Node* node = new Node;

 
    node->path = path;
    if (level != 0)
    {
        node->path.push_back(make_pair(i, j));
    }

    memcpy(node->reducedMatrix, parentMatrix,
        sizeof node->reducedMatrix);

    for (int k = 0; level != 0 && k < N; k++)
    {
        node->reducedMatrix[i][k] = INF;

        node->reducedMatrix[k][j] = INF;
    }

    node->reducedMatrix[j][0] = INF;

    node->level = level;

    node->vertex = j;

    return node;
}

void rowReduction(int reducedMatrix[N][N], int row[N])
{

    fill_n(row, N, INF);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (reducedMatrix[i][j] < row[i]) {
                row[i] = reducedMatrix[i][j];
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (reducedMatrix[i][j] != INF && row[i] != INF) {
                reducedMatrix[i][j] -= row[i];
            }
        }
    }
}

void columnReduction(int reducedMatrix[N][N], int col[N])
{
    fill_n(col, N, INF);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (reducedMatrix[i][j] < col[j]) {
                col[j] = reducedMatrix[i][j];
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (reducedMatrix[i][j] != INF && col[j] != INF) {
                reducedMatrix[i][j] -= col[j];
            }
        }
    }
}

int calculateCost(int reducedMatrix[N][N])
{
    int cost = 0;

    int row[N];
    rowReduction(reducedMatrix, row);

    int col[N];
    columnReduction(reducedMatrix, col);

    for (int i = 0; i < N; i++)
    {
        cost += (row[i] != INT_MAX) ? row[i] : 0,
            cost += (col[i] != INT_MAX) ? col[i] : 0;
    }

    return cost;
}

void printPath(vector<pair<int, int>> const& list)
{
    for (int i = 0; i < list.size(); i++) {
        cout << list[i].first + 1 << " -> " << list[i].second + 1 << endl;
    }
}

struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->cost > rhs->cost;
    }
};

int solve(int costMatrix[N][N])
{
    priority_queue<Node*, vector<Node*>, comp> pq;

    vector<pair<int, int>> v;

    Node* root = newNode(costMatrix, v, 0, -1, 0);

    root->cost = calculateCost(root->reducedMatrix);

    pq.push(root);

    while (!pq.empty())
    {
        Node* min = pq.top();

        pq.pop();

        int i = min->vertex;

        if (min->level == N - 1)
        {
            min->path.push_back(make_pair(i, 0));

            printPath(min->path);

            return min->cost;
        }

        for (int j = 0; j < N; j++)
        {
            if (min->reducedMatrix[i][j] != INF)
            {
                Node* child = newNode(min->reducedMatrix, min->path,
                    min->level + 1, i, j);

                child->cost = min->cost + min->reducedMatrix[i][j]
                    + calculateCost(child->reducedMatrix);

                pq.push(child);
            }
        }

        delete min;
    }
}

int main()
{
    int n = 11;
    int costMatrix[N][N] =
    {
        {INF, 2 * n, 21 + n, INF, n},
        {n, INF, 15 + n, 68 - n, 84 - n},
        {2 + n, 3 * n, INF, 86, 49 + n},
        {17 + n, 58 - n, 4 * n, INF, 3 * n},
        {93 - n, 66 + n, 52, 13 + n, INF}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(10) << (costMatrix[i][j] == INF ? "INF" : to_string(costMatrix[i][j]));
        }
        cout << "\n\n";
    }

    const auto start_time = std::chrono::system_clock::now();
    cout << "\n\nTotal cost is " << solve(costMatrix) << endl;
    const auto end_time = std::chrono::system_clock::now();
    const chrono::duration<double> diff = end_time - start_time;
    cout << "Duration: "
        << chrono::duration_cast<chrono::milliseconds>(diff).count() << " ms" << endl;

    return 0;
}