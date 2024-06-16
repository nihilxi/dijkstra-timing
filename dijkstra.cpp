#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <conio.h>
#include <vector>
#include <chrono>
#include <time.h>

std::vector<std::vector<int>> matrix;
int nodes, edges;
long double avg;

void dijkstra(int startNode)
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
    std::ifstream file(name);
    std::string line;
    getline(file, line);
    std::stringstream ss(line);
    ss >> nodes >> edges;
    int node1, node2, weight;
    std::vector<int> row;
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
            for (int j = 0; j < nodes; ++j)
            {
                if (matrix[i][j] != -1)
                {
                    std::cout << j + 1 << "(" << matrix[i][j] << ") ";
                }
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
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
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
            std::string name;
            std::cout << "\nHow many trials?: ";
            std::cin >> trials;
            std::cout << "Enter the start node: ";
            std::cin >> startNode;
            std::cout << "Enter file name: ";
            std::cin >> name;
            name += ".txt";
            std::ofstream writeFile(name);
            for (int i = 0; i < trials; i++)
            {
                start = std::chrono::high_resolution_clock::now();
                dijkstra(startNode);
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<long double> elapsed = end - start;
                avg += elapsed.count();
                writeFile << elapsed.count() << ";\n";
            }
            avg /= trials;
            std::cout << "Average time: " << avg << "s\n";
            writeFile << avg << ";\n";
            writeFile.close();
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