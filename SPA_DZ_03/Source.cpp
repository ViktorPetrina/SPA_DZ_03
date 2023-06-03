#include <iostream>
#include <Windows.h>
#include "Area.h"

using namespace std;

int main()
{
    const int ROWS = 20;
    const int COLS = 40;

    vector<vector<int>> field(ROWS, vector<int>(COLS, 0));

    cout << "\n---- DIJKSTRIN ALGORITAM DEMONSTRACIJA ----\n\n";

    int choice;
    cout << "1) Bez prepreka\n2) Sa preprekama\n";
    bool dalje = false;
    int startRow, startCol;
    int endRow, endCol;


        cout << "\nIzbor: ";
        cin >> choice;


        if (choice == 2)
        {
            cout << "Izaberite oblik prepreke:\n\n1) 'V'\n2) 'H'\n\nIzbor: ";
            cin >> choice;

            int row = 18;
            switch (choice)
            {
            case 1:
                for (int i = 1; i < 19; i++)
                {
                    field[i][i+1] = -1;
                }
                for (int i = 19; i < 37; i++)
                {
                    field[row][i+1] = -1;
                    row--;
                }
                break;

            case 2:
                for (int i = 1; i < 19; i++)
                {
                    field[i][2] = -1;
                }
                for (int i = 1; i < 19; i++)
                {
                    field[i][37] = -1;
                }
                for (int i = 3; i < 37; i++)
                {
                    field[9][i] = -1;
                }
                break;
            }
        }

        bool zauzeta;
        do {
            zauzeta = false;
            cout << "\nUnesite pocetnu tocku: " << endl;
            cout << "Red (max 20): "; cin >> startRow; startRow--;
            cout << "Stupac (max 40): "; cin >> startCol; startCol--;
            
            if (field[startRow][startCol] == -1)
            {
                cout << "Unesena tocka je zauzeta!" << endl;
                zauzeta = true;
            }

        } while (zauzeta);

        do {
            zauzeta = false;
            cout << "\nUnesite ciljanu tocku: " << endl;
            cout << "Red (max 20): "; cin >> endRow; endRow--;
            cout << "Stupac (max 40): "; cin >> endCol; endCol--;

            if (field[endRow][endCol] == -1)
            {
                cout << "Unesena tocka je zauzeta!" << endl;
                zauzeta = true;
            }

        } while (zauzeta);
   

    adjacency_list_t adjacency_list = CreateAdjacencyList(field);

    vector<weight_t> min_distance;
    vector<vertex_t> previous;

    DijkstraComputePaths(startRow * COLS + startCol, adjacency_list, min_distance, previous);

    list<vertex_t> path = DijkstraGetShortestPathTo(endRow * COLS + endCol, previous);

    for (const auto& vertex : path)
    {
        int row = vertex / COLS;
        int col = vertex % COLS;
     
        system("cls");
        PrintField(field, row, col);

        Sleep(10);
    }

    return 0;
}
