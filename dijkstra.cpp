#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <conio.h>
#include <vector>
#include <chrono>
#include <time.h>
#include <queue>

std::vector<std::vector<int>> matrix;
std::vector<std::vector<std::pair<int, int>>> list;
int nodes, edges;
long double avg[2];

void dijkstra(int startNode, bool print, std::string name)
{
    std::vector<int> distance(nodes, INT_MAX);
    std::vector<bool> visited(nodes, false);
    distance[startNode - 1] = 0;

    for (int count = 0; count < nodes - 1; ++count)
    {
        int minDistance = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < nodes; ++i)
        {
            if (!visited[i] && distance[i] <= minDistance)
            {
                minDistance = distance[i];
                minIndex = i;
            }
        }

        visited[minIndex] = true;

        for (int i = 0; i < nodes; ++i)
        {
            if (!visited[i] && matrix[minIndex][i] != -1 && distance[minIndex] != INT_MAX &&
                distance[minIndex] + matrix[minIndex][i] < distance[i])
            {
                distance[i] = distance[minIndex] + matrix[minIndex][i];
            }
        }
    }
    if (print)
    {
        name += "_matrix_results.txt";
        std::ofstream writeFile(name);
        for (int i = 0; i < nodes; ++i)
        {
            if (distance[i] == INT_MAX)
            {
                writeFile << "-1 ";
            }
            else
            {
                writeFile << distance[i] << " ";
            }
        }
        writeFile.close();
    }
}

void dijkstraList(int startNode, bool print)
{
    std::vector<int> distance(nodes, INT_MAX);
    std::vector<bool> visited(nodes, false);
    distance[startNode - 1] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, startNode));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (visited[u - 1])
        {
            continue;
        }

        visited[u - 1] = true;

        for (auto neighbor : list[u - 1])
        {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!visited[v - 1] && distance[u - 1] != INT_MAX && distance[u - 1] + weight < distance[v - 1])
            {
                distance[v - 1] = distance[u - 1] + weight;
                pq.push(std::make_pair(distance[v - 1], v));
            }
        }
    }
}

void generateRandomGraph()
{
    int nodes;
    double density;
    std::string filename;

    std::cout << "\nEnter the number of nodes: ";
    std::cin >> nodes;
    std::cout << "Enter the density (between 0 and 1): ";
    std::cin >> density;
    std::cout << "Enter file name: ";
    std::cin >> filename;

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::srand(std::time(nullptr));

    int edges = (density * nodes * (nodes - 1)) / 2;

    file << nodes << " " << edges << "\n";

    for (int i = 0; i < edges; i++)
    {
        int nodeA = std::rand() % nodes + 1;
        int nodeB = std::rand() % nodes + 1;
        while (nodeA == nodeB)
        {
            nodeB = std::rand() % nodes;
        }
        int weight = std::rand() % 100 + 1;
        file << nodeA << " " << nodeB << " " << weight << "\n";
    }

    file.close();
}

void loadFile(const std::string name)
{
    std::vector<int> row;
    int node1, node2, weight;
    matrix.clear();
    list.clear();

    std::ifstream file(name);
    std::string line;
    getline(file, line);
    std::stringstream ss(line);
    ss >> nodes >> edges;

    for (int i = 0; i < nodes; ++i)
    {
        for (int j = 0; j < nodes; ++j)
        {
            row.push_back(-1);
        }
        matrix.push_back(row);
        row.clear();
    }

    for (int i = 0; i < edges; i++)
    {
        getline(file, line);
        std::stringstream ss(line);
        ss >> node1 >> node2 >> weight;
        if (matrix[node1 - 1][node2 - 1] == -1 || matrix[node1 - 1][node2 - 1] > weight)
        {
            matrix[node1 - 1][node2 - 1] = weight;
        }
    }
    for (int i = 0; i < nodes; i++)
    {
        std::vector<std::pair<int, int>> temp;
        for (int j = 0; j < nodes; j++)
        {
            if (matrix[i][j] != -1)
            {
                temp.push_back(std::make_pair(j, matrix[i][j]));
            }
        }
        list.push_back(temp);
    }
    file.close();
}

void printMatrix(char choice)
{
    if (choice == '1')
    {
        std::cout << "\nMatrix:\n";
        for (int i = 0; i < nodes; ++i)
        {
            for (int j = 0; j < nodes; ++j)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    else if (choice == '2')
    {
        std::cout << "\nList:\n";
        for (int i = 0; i < nodes; ++i)
        {
            std::cout << i + 1 << ": ";
            for (int j = 0; j < list[i].size(); ++j)
            {
                std::cout << "[" << list[i][j].first + 1 << " " << list[i][j].second << "] ";
            }
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "\nIncorrect choice!\n";
    }
    std::system("pause");
}

int main()
{
    while (true)
    {
        std::system("cls");
        std::cout << "Menu:\n";
        std::cout << "1. Load from file\n";
        std::cout << "2. Generate random graph\n";
        std::cout << "3. Display graph (matrix/list)\n";
        std::cout << "4. Run Dijkstra\n";
        std::cout << "0. Exit\n";
        std::cout << "Select option: ";

        char choice = getch();

        switch (choice)
        {
        case '1':
        {
            std::string name;
            std::cout << "\nFile name: ";
            std::cin >> name;
            name += ".txt";
            loadFile(name);
            break;
        }
        case '2':
        {
            generateRandomGraph();
            break;
        }
        case '3':
        {
            std::cout << "\n1. Matrix\n2. List\nSelect option:\n";
            char choice = getch();
            printMatrix(choice);
            break;
        }
        case '4':
        {
            int startNode;
            int trials;
            bool print = false;
            std::string name;
            std::cout << "\nHow many trials?: ";
            std::cin >> trials;
            std::cout << "Enter the start node: ";
            std::cin >> startNode;
            std::cout << "Enter file name for time results: ";
            std::cin >> name;
            std::cout << "Printing graph results? (y/n): ";
            char choice = getch();
            if (choice == 'y')
            {
                print = true;
            }
            std::ofstream writeFile(name + ".txt");
            for (int i = 0; i < trials; i++)
            {
                auto start_matrix = std::chrono::high_resolution_clock::now();
                dijkstra(startNode, print, name);
                auto end_matrix = std::chrono::high_resolution_clock::now();

                auto start_list = std::chrono::high_resolution_clock::now();
                dijkstraList(startNode, print);
                auto end_list = std::chrono::high_resolution_clock::now();

                auto duration_matrix = std::chrono::duration_cast<std::chrono::microseconds>(end_matrix - start_matrix).count();
                auto duration_list = std::chrono::duration_cast<std::chrono::microseconds>(end_list - start_list).count();

                avg[0] += duration_matrix;
                avg[1] += duration_list;

                writeFile << duration_matrix << ";";
                writeFile << duration_list << ";\n";
                print = false;
            }
            avg[0] /= trials;
            avg[1] /= trials;
            std::cout << "\nAverage matrix time: " << avg[0] << "s";
            std::cout << "\nAverage list time: " << avg[1] << "s\n";
            writeFile << avg[0] << ";";
            writeFile << avg[1] << ";\n";
            writeFile.close();
            system("pause");
            break;
        }
        case '0':
        {
            return 0;
        }
        default:
        {
            std::cout << "\nIncorrect choice!\n";
            std::system("pause");
            break;
        }
        }
    }
}
