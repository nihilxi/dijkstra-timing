#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <conio.h>
#include <vector>

std::vector<std::vector<int>> matrix;
int nodes, edges;

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
        std::cout << "4. Run Dijkstra (matrix/list)\n";
        std::cout << "5. Test\n";
        std::cout << "0. Exit\n";
        std::cout << "Select option: ";

        char choice = getch();

        switch (choice)
        {
        case '1':
        {
            std::string name;
            std::cout << "\nNazwa pliku: ";
            std::cin >> name;
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
            for (int i = 0; i < nodes; ++i)
            {
                for (int j = 0; j < nodes; ++j)
                {
                    std::cout << matrix[i][j] << " ";
                }
                std::cout << std::endl;
            }
            break;
        }
        case '4':
        {
            break;
        }
        case '5':
        {
            break;
        }
        case '0':
        {
            return 0;
        }
        default:
        {
            std::cout << "\nIncorrect choice!\n";
            break;
        }
        }
    }
}