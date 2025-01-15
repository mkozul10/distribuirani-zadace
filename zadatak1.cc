/*
Napišite program korištenjem C++ funkcija u kojem će jedan
proces poslati vektor od 100 elemenata svim ostalim procesima,
nakon čega će svaki proces vratiti taj vektor procesu pošiljatelju,
ali uvećan za N+1, gdje je N broj procesa. Pripazite na količinu
vraćenih podataka!
*/

#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    MPI::Init(argc, argv);

    int rank = MPI::COMM_WORLD.Get_rank();
    int proc_size = MPI::COMM_WORLD.Get_size();
    vector<int> vektor(100);

    if (rank == 0)
    {

        for (int i = 0; i < 100; i++)
        {
            vektor[i] = i + 1;
        }

        for (int i = 1; i < proc_size; i++)
        {
            MPI::COMM_WORLD.Send(vektor.data(), 100, MPI::INT, i, 0);
        }
    }
    else
    {

        MPI::COMM_WORLD.Recv(vektor.data(), 100, MPI::INT, 0, 0);

        for (int i = 0; i < 100; i++)
        {
            vektor[i] += rank + 1;
        }

        MPI::COMM_WORLD.Send(vektor.data(), 100, MPI::INT, 0, 0);
    }

    if (rank == 0)
    {

        for (int i = 1; i < proc_size; i++)
        {
            MPI::COMM_WORLD.Recv(vektor.data(), 100, MPI::INT, i, 0);
            cout << "Proces " << i << ": ";
            for (int j = 0; j < 100; j++)
            {
                cout << vektor[j] << " ";
            }
            cout << endl;
        }
    }

    MPI::Finalize();
    return 0;
}
