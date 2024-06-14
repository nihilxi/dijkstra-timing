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

    // Seed for random number generation
    std::srand(std::time(nullptr));

    // Calculate the number of edges based on the density
    int edges = (density * nodes * (nodes - 1)) / 2;

    // Write the number of nodes and edges to the file
    file << nodes << " " << edges << "\n";

    // Generate edges with random weights
    for (int i = 0; i < edges; i++)
    {
        int nodeA = rand()%(100-1 + 1) + 1;
        int nodeB = rand()%(100-1 + 1) + 1;
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
        std::cout << "Menu wyboru:\n";
        std::cout << "1. Wczytaj z pliku\n";
        std::cout << "2. Wygeneruj losowy graf\n";
        std::cout << "3. Wyswietl graf (macierz/lista)\n";
        std::cout << "4. Uruchom Dijkstra (macierz/lista)\n";
        std::cout << "5. Testowanie\n";
        std::cout << "0. Wyjscie\n";
        std::cout << "Wybierz opcje: ";

        char choice = getch();

        switch (choice)
        {
        case '1':
        {
            std::string name;
            std::cout << "\nNazwa pliku: ";
            std::cin >> name;
            loadFile(name);
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
        case '2':
        {
            generateRandomGraph();
            break;
        }
        case '3':
        {
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
            std::cout << "\nNiepoprawny wybor!\n";
            break;
        }
        }
    }
}