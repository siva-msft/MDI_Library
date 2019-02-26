/*! \file
 *
 * \brief Class declaration for handling communication between connected codes
 */

#ifndef MDI_COMMUNICATOR
#define MDI_COMMUNICATOR

#include <vector>
#include "mdi_global.h"

class Communicator
{
  public:
    Communicator(int type_);
    virtual int send(const char* buf, int count, MDI_Datatype datatype) = 0;
    virtual int recv(char* buf, int count, MDI_Datatype datatype) = 0;

  private:
    int type;
};

class CommunicatorMPI : public Communicator
{
  public:
    CommunicatorMPI(int type_, int mpi_comm_, int mpi_rank_)
      : Communicator(type_) { 
      this->mpi_comm = mpi_comm_;
      this->mpi_rank = mpi_rank_;
    };
    int send(const char* buf, int count, MDI_Datatype datatype);
    int recv(char* buf, int count, MDI_Datatype datatype);

  private:
    int mpi_comm;
    int mpi_rank;
};


class CommunicatorTCP : public Communicator
{
  public:
    CommunicatorTCP(int type_, int sockfd_)
      : Communicator(type_) { 
      this->sockfd = sockfd_;
    };
    int send(const char* buf, int count, MDI_Datatype datatype);
    int recv(char* buf, int count, MDI_Datatype datatype);

  private:
    int sockfd;
};


//this is the number of communicator handles that have been returned by MDI_Accept_Communicator()
static int returned_comms = 0;

extern std::vector <Communicator*> communicators;

#endif