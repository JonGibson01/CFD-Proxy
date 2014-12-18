#ifndef THREADS_H
#define THREADS_H

#include <omp.h>
#include <stdbool.h>

#include "comm_data.h"
#include "solver_data.h"
#include "error_handling.h"


/* getter/setter functions for global increments */
int get_send_increment(int i);
int set_send_increment(int i, int val);
int set_send_increment_local(int i, int val);

/* getter functions for thread local send/recv counts  */
int get_sendcount_local(int i);
int get_recvcount_local(int i);


void initiate_thread_comm_mpi(RangeList *color
			      , comm_data *cd
			      , double *data
			      , int dim2
			      );

void initiate_thread_comm_gaspi(RangeList *color
				, comm_data *cd
				, double *data
				, int dim2
				);
 
void initiate_thread_comm_mpifence(RangeList *color
				   , comm_data *cd
				   , double *data
				   , int dim2
				   );

void initiate_thread_comm_mpipscw(RangeList *color
				  , comm_data *cd
				  , double *data
				  , int dim2
				  );

/* copy per target/source */
void exchange_dbl_copy_in(comm_data *cd
			  , double *sbuf
			  , double *data
			  , int dim2
			  , int i);

void exchange_dbl_copy_out(comm_data *cd
			   , double *rbuf
			   , double *data
			   , int dim2
			   , int i);

/* copy per thread, per target/source */
void exchange_dbl_copy_in_local(double *sbuf
				, double *data
				, int dim2
				, int i);

void exchange_dbl_copy_out_local(double *rbuf
				 , double *data
				 , int dim2
				 , int i);

int my_add_and_fetch(volatile int *ptr, int val);
int my_fetch_and_add(volatile int *ptr, int val);

int this_is_the_first_thread(void);
int this_is_the_last_thread(void);

static __inline void _mm_pause (void)
{
  __asm__ __volatile__ ("rep; nop" : : );
}

#endif
