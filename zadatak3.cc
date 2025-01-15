/*                                                                                                                                                                                                /*
Generirati proizvoljnu matricu. Distribuirati pojedni redak
pojedinom računalu(procesu). Formirati donju trokutastu matricu
sa ispisom naziva računala(procesa) koji je ispisao pojedini redak.
Program napisati korištenjem C++ funkcija.
*/

#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

vector<int> triangular_matrix(int redNumb, vector<vector<int>> &matrica)
{
    for (int i = redNumb + 1; i < matrica[redNumb].size(); i++)
    {
        matrica[redNumb][i] = 0;
    }
    return matrica[redNumb];
}

int main(int argc, char **argv)
{
    MPI::Init(argc, argv);

    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();

    vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {4, 5, 6, 7},
        {9, 8, 7, 6},
        {5, 4, 7, 6}};

    int red;
    vector<int> used;
    vector<int> nizMatrice;

    if (size < static_cast<int>(matrix.size()))
    {
        if (rank == 0)
        {
            cout << "Potrebno je više procesa nego što ima redova u matrici!" << endl;
        }
    }
    else
    {
        if (rank == 0)
        {
            for (int i = 0; i < static_cast<int>(matrix.size()); ++i)
            {
                int dest_rank;
                do
                {
                    dest_rank = (rand() % (size - 1)) + 1;
                } while (find(used.begin(), used.end(), dest_rank) != used.end());
                used.push_back(dest_rank);

                MPI::COMM_WORLD.Send(&i, 1, MPI::INT, dest_rank, 0);
            }
        }
        else
        {
            MPI::COMM_WORLD.Recv(&red, 1, MPI::INT, 0, 0);
            nizMatrice = triangular_matrix(red, matrix);

            cout << "Proces: " << rank << " obradjuje red: " << red << " red nakon obrade je: ";
            for (size_t j = 0; j < nizMatrice.size(); ++j)
            {
                cout << nizMatrice[j] << " ";
            }
            cout << endl;
        }
    }

    MPI::Finalize();
    return 0;
}
