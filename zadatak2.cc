/*
Za slanje ranga procesa 0 upotrijebljen je MPI::Comm.Bcast svim
procesima unutar komunikatora. Nakon primitka procesi vraćaju
procesu 0 naziv računala koje je primilo poruku. Proces 0 prima
poruku od ostalih procesa MPI::Comm.Irecv. Ispisati na zaslon da
su primljene poruke na strani procesa 0. Program napisati
korištenjem C++ funkcija.
*/

#include <iostream>
#include <vector>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    MPI::Init(argc, argv);
    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();
    int data = 0;
    char hostname[MPI::MAX_PROCESSOR_NAME];
    int len;

    if (rank == 0)
    {
        MPI::COMM_WORLD.Bcast(&data, 1, MPI::INT, 0);
        vector<string> messages;

        for (int i = 1; i < size; i++)
        {
            MPI::Request request = MPI::COMM_WORLD.Irecv(hostname, MPI::MAX_PROCESSOR_NAME, MPI::CHAR, i, 0);
            request.Wait();
            messages.emplace_back(hostname);
        }

        cout << "Primljene poruke na strani procesa 0:" << endl;
        for (const auto &msg : messages)
        {
            cout << msg << endl;
        }
    }
    else
    {
        MPI::COMM_WORLD.Bcast(&data, 1, MPI::INT, 0);
        MPI::Get_processor_name(hostname, len);
        MPI::COMM_WORLD.Send(hostname, len + 1, MPI::CHAR, 0, 0);
    }

    MPI::Finalize();
    return 0;
}
