#include "GenerateAssumes.h"
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv) 
{
  // Initialize the MPI environment
  ProcessIfs* ifs = new ProcessIfs();MPI_Init(&argc, &argv);int my_rank; MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  // Find out rank, size
  int world_rank=-1;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size=-1;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int token;

  MPI_Barrier(MPI_COMM_WORLD);

  // Processes 1, 2, and 3 will send some data to process 0
  if (world_rank == 1)
  {
    token = 10;
    MPI_Send(&token, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
    cout << "\nProcess 1 sending " << token << " to Process 0\n";
  }

  else if (world_rank == 2)
  {
    token = 10;
    MPI_Send(&token, 1, MPI_INT, 0, 20, MPI_COMM_WORLD);
    cout << "\nProcess 2 sending " << token << " to Process 0\n";
  }

  else if (world_rank == 3)
  {
    token = 30;
    MPI_Send(&token, 1, MPI_INT, 0, 30, MPI_COMM_WORLD);
    cout << "\nProcess 3 sending " << token << " to Process 0\n";
  }

  else if (world_rank == 0)
  {
    MPI_Status status;
    MPI_Recv(&token, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    cout << "\nProcess 0 recieved " << token << "\n";
    if(token == 5+5)
    {
      ifs->storeInfo("token",bo_eq,10,49,51,47);ifs->storeInfo("token",bo_ne,20,53,55,47);MPI_Recv(&token, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else if(token == 20)
    {
      ifs->storeInfo("token",bo_ne,10,49,51,47);ifs->storeInfo("token",bo_eq,20,53,55,47);MPI_Recv(&token, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else
    {
      ifs->storeInfo("token",bo_ne,10,49,51,47);ifs->storeInfo("token",bo_ne,20,53,55,47);MPI_Recv(&token, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Recv(&token, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  }
  MPI_Finalize();ifs->transferInfoToScheduler(my_rank);
}
