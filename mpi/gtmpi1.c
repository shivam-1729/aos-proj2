#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "gtmpi.h"


// Todo(Gaurav): MCS-tree barrier with message passing
// Cannot assume that the number of processors will be power of 2 for tree barriers
#define ARRIVAL_N_ARY 4
#define WAKE_UP_N_ARY 2

typedef struct TreeNode {
    bool parent_sense;
    bool have_child[ARRIVAL_N_ARY];
    bool child_not_ready[ARRIVAL_N_ARY];
} TreeNode;

// TreeNode* node;
int process_cnt;

void gtmpi_init(int num_processes) {
    // node = malloc(num_processes * sizeof(TreeNode));
    process_cnt = num_processes;
    // printf("Init completed\n");  // This is being called by every process
}

void wake_up(int my_id) {
    int parent_index = (my_id - 1) / WAKE_UP_N_ARY;      // right shift by 2 would already be optimized by a good compiler.
    bool is_parent = (WAKE_UP_N_ARY*my_id + 1) < process_cnt;
    MPI_Status mpi_result;
    int my_msg, tag = 1;

    if (my_id != 0) {
        MPI_Recv(&my_msg, 1, MPI_INT, parent_index, tag, MPI_COMM_WORLD, &mpi_result);
        // printf("[%d] move to next barrier signal received from %d\n", my_id, parent_index);
    } else {
        printf("Wake-up step has now started\n");
    }

    if (is_parent) {
        for (int j = 1; j <= WAKE_UP_N_ARY && (WAKE_UP_N_ARY * my_id + j) < process_cnt; j++) {
            int child_index = (WAKE_UP_N_ARY * my_id + j);
            my_msg = 1;
            MPI_Send(&my_msg, 1, MPI_INT, child_index, tag, MPI_COMM_WORLD);       // relying on blocking nature
            // printf("[%d] Wake-up signal sent to %d\n", my_id, child_index);
        }
    }
}

// node is passed by value
void arrival_tree(int my_id) {
    // if (my_id < 0 || my_id >= process_cnt) {
    //     fprintf(stderr, "Error: Process ID %d is out of bounds (0 to %d)\n", my_id, process_cnt - 1);
    //     MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    // }

    // TreeNode node;
    // for (int j = 1; j <= ARRIVAL_N_ARY; j++) {
    //     node.have_child[j] = ((ARRIVAL_N_ARY*my_id + j) < process_cnt);
    //     node.child_not_ready[j] = node.have_child[j];       // A non-existant child is ready. Existing children are not ready.
    // }
    // bool is_parent = node.have_child[0];
    bool is_parent = (ARRIVAL_N_ARY*my_id + 1) < process_cnt;
    // bool all_children_not_ready = true;

    int tag = 1;
    MPI_Status mpi_result;
    int my_msg;

    if (is_parent) {
        for (int j = 1; j <= ARRIVAL_N_ARY && (ARRIVAL_N_ARY * my_id + j) < process_cnt; j++) {
            int child_index = (ARRIVAL_N_ARY * my_id + j);
            MPI_Recv(&my_msg, 1, MPI_INT, child_index, tag, MPI_COMM_WORLD, &mpi_result);       // relying on blocking nature
            // printf("[%d] %d is now ready\n", my_id, child_index);
        }
    }
    
    my_msg = 1;
    int parent_index = (my_id - 1) / ARRIVAL_N_ARY;      // right shift by 2 would already be optimized by a good compiler.
    if (my_id != parent_index) {
        MPI_Send(&my_msg, 1, MPI_INT, parent_index, tag, MPI_COMM_WORLD);
        // printf("[%d] Message sent to %d\n", my_id, parent_index);
    } else {
        printf("Arrival step has now completed\n");
    }
    
    // if (my_id != parent) {
    //     node[parent].child_not_ready[child_index] = false;
    // }
}

void gtmpi_barrier(){
    // bool sense = true;
    int my_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    
    // for (int i = 0; i < process_cnt; i++) {
    // node.parent_sense = false;
    // for (int j = 0; j < ARRIVAL_N_ARY; j++) {
    //     node.have_child[j] = ((ARRIVAL_N_ARY*my_id + j) < process_cnt);
    //     node.child_not_ready[j] = node.have_child[j];       // A non-existant child is ready. Existing children are not ready.
    // }
    // }

    arrival_tree(my_id);
    wake_up(my_id);
}

void gtmpi_finalize(){
    // No action required to clean up after using MPI
    // printf("Finalize completed\n"); // This is being called by every process
}

// type treenode record
// parentsense Boolean
// parentpointer Boolean
// childpointers array of Boolean
// havechild array of Boolean
// childnotready array of Boolean
// dummy Boolean pseudodata
// shared node array P of treenode
// nodesmy_id is allocated in shared memory
// locally accessible to processor my_id
// processor private my_id integer a unique virtual processor index
// processor private sense Boolean
// on processor i sense is initially true
// in nodesi
// havechildj true if ij P otherwise false
// parentpointer nodesfloori ch ildno tread yi mod
// or dummy if i
// childpointers nodesipar entse nse or dummy if i P
// childpointers nodesipar entse nse or dummy if i P
// initially childnotready havechild and parentsense false
// procedure treebarrier
// with nodesmy_id do
// repeat until childnotready false false false false
// childnotready havechild prepare for next barrier
// parentpointer false let parent know Im ready
// if not root wait until my parent signals wakeup
// if my_id
// repeat until parentsense sense
// signal children in wakeup tree
// childpointers sense
// childpointers sense
// sense not sense