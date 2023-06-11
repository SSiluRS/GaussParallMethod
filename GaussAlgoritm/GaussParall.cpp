#include "GaussParall.h"

GaussParall::GaussParall(int rank, int size) {
    this->rank = rank;
    this->size = size;
}

bool GaussParall::solve(Matrix& A, Matrix& b) {
    int n = A.rows();
    if (n != b.rows()) {
        std::cerr << "Error: The sizes of the matrices do not match!" << std::endl;
        return false;
    }
    int m = A.cols();

    int row_per_proc_global = n / size;
    int row_delete_cnt = 0;
    if (rank == 0) {
        if (row_per_proc_global == 0) {
            row_delete_cnt = size - n;
        }
    }

    MPI_Bcast(&row_delete_cnt, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank >= size - row_delete_cnt) {
        return false;
    }
    size -= row_delete_cnt;
    row_per_proc_global = n / size;
    int row_remainder = n % size;
    int start_row = rank * row_per_proc_global + std::min(rank, row_remainder);
    int end_row = start_row + row_per_proc_global + (rank < row_remainder ? 1 : 0);

    int row_per_proc_local = end_row - start_row;

    Matrix A_local(row_per_proc_local, m);
    Matrix B_local(row_per_proc_local, 1);
    
    int* sendcountsA = new int[size];
    int* displsA = new int[size];
    int* sendcountsB = new int[size];
    int* displsB = new int[size];
    
#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        sendcountsA[i] = (n / size + (i < row_remainder ? 1 : 0)) * m;
        sendcountsB[i] = (n / size + (i < row_remainder ? 1 : 0));
        displsA[i] = (i * row_per_proc_global + std::min(i, row_remainder)) * m;
        displsB[i] = i * row_per_proc_global + std::min(i, row_remainder);
    }    

     //print calculated send counts and displacements for each process
    //if (0 == rank) {
    //    for (int i = 0; i < size; i++) {
    //        printf("sendcountsA[%d] = %d\tdisplsA[%d] = %d\n", i, sendcountsA[i], i, displsA[i]);
    //        //printf("sendcountsB[%d] = %d\tdisplsB[%d] = %d\n", i, sendcountsB[i], i, displsB[i]);
    //    }
    //}

    MPI_Scatterv(A.get_data(), sendcountsA, displsA, MPI_DOUBLE, A_local.get_data(), sendcountsA[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatterv(b.get_data(), sendcountsB, displsB, MPI_DOUBLE, B_local.get_data(), sendcountsB[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

    delete[] sendcountsA;
    delete[] displsA;
    delete[] sendcountsB;
    delete[] displsB;
    
    MPI_Status status;
    int ii = -1;
    int r = -5;
    int pivot_proc = 10;
    for (int i = 0; i < m - 1; i++) {

        if (start_row <= i && end_row > i) {
            pivot_proc = rank;
            for (int j = 0; j < size; j++)
            {
                if (j != pivot_proc) {
                    MPI_Send(&pivot_proc, 1, MPI_INT, j, j, MPI_COMM_WORLD);
                }
            }
        }
        else {
            MPI_Recv(&pivot_proc, 1, MPI_INT, MPI_ANY_SOURCE, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank >= pivot_proc) {

            int local_pivot_row = i - start_row >= 0 ? i - start_row : 0;
            double local_pivot_val = A_local(local_pivot_row, i);
#pragma omp parallel
            {
                int local_parall_pivot_row = local_pivot_row;
                double local_parall_pivot_val = local_pivot_val;
#pragma omp for 
                for (int j = local_pivot_row + 1; j < row_per_proc_local; j++)
                {
                    double cur_val = A_local(j, i);
                    if (std::fabs(cur_val) > std::fabs(local_parall_pivot_val))
                    {
                        local_parall_pivot_row = j;
                        local_parall_pivot_val = cur_val;
                    }
                }
#pragma omp critical
                {
                    if (local_parall_pivot_val > local_pivot_val)
                    {
                        local_pivot_val = local_parall_pivot_val;
                        local_pivot_row = local_parall_pivot_row;
                    }
                }
            }

            int global_pivot_row = rank * row_per_proc_global + std::min(rank, row_remainder) + local_pivot_row;
            int another_local_pivot_row = 0;
            double another_local_pivot_val = 0;
            double global_pivot_val = 0;
            int swap_proc = pivot_proc;
            if (rank == pivot_proc) {
                global_pivot_val = local_pivot_val;

                for (int j = pivot_proc + 1; j < size; j++) {

                    MPI_Recv(&another_local_pivot_val, 1, MPI_DOUBLE, j, j, MPI_COMM_WORLD, &status);

                    MPI_Recv(&another_local_pivot_row, 1, MPI_INT, j, j, MPI_COMM_WORLD, &status);
                    if (std::fabs(another_local_pivot_val) > std::fabs(global_pivot_val)) {
                        global_pivot_val = another_local_pivot_val;

                        global_pivot_row = j * row_per_proc_global + std::min(j, row_remainder) + another_local_pivot_row;
                        swap_proc = j;
                    }
                }
            }
            else {
                MPI_Ssend(&local_pivot_val, 1, MPI_DOUBLE, pivot_proc, rank, MPI_COMM_WORLD);
                MPI_Ssend(&local_pivot_row, 1, MPI_INT, pivot_proc, rank, MPI_COMM_WORLD);
            }

            MPI_Bcast(&global_pivot_row, 1, MPI_INT, pivot_proc, MPI_COMM_WORLD);
            MPI_Bcast(&global_pivot_val, 1, MPI_DOUBLE, pivot_proc, MPI_COMM_WORLD);
            
            MPI_Bcast(&swap_proc, 1, MPI_INT, pivot_proc, MPI_COMM_WORLD);
            
            if (global_pivot_row != i) {
                if (rank == pivot_proc) {
                    if (swap_proc == rank) {
                        A_local.swap_rows(local_pivot_row, i - start_row);
                        B_local.swap_rows(local_pivot_row, i - start_row);
                    }
                    else {
                        double* recv_row_data = new double[m], recv_b_data;
                        MPI_Recv(recv_row_data, m, MPI_DOUBLE, swap_proc, swap_proc, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        MPI_Recv(&recv_b_data, 1, MPI_DOUBLE, swap_proc, swap_proc, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                        MPI_Ssend(&A_local(i - start_row, 0), m, MPI_DOUBLE, swap_proc, pivot_proc, MPI_COMM_WORLD);
                        MPI_Ssend(&B_local(i - start_row, 0), 1, MPI_DOUBLE, swap_proc, pivot_proc, MPI_COMM_WORLD);

                        A_local.set_row(i - start_row, recv_row_data);
                        B_local(i - start_row, 0) = recv_b_data;

                        delete[] recv_row_data;
                    }
                }
                else {
                    if (swap_proc == rank) {
                        MPI_Ssend(&A_local(local_pivot_row, 0), m, MPI_DOUBLE, pivot_proc, rank, MPI_COMM_WORLD);

                        MPI_Ssend(&B_local(local_pivot_row, 0), 1, MPI_DOUBLE, pivot_proc, rank, MPI_COMM_WORLD);
                        double* recv_row_data = new double[m], recv_b_data;
                        MPI_Recv(recv_row_data, m, MPI_DOUBLE, pivot_proc, pivot_proc, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        MPI_Recv(&recv_b_data, 1, MPI_DOUBLE, pivot_proc, pivot_proc, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                        A_local.set_row(local_pivot_row, recv_row_data);
                        B_local(local_pivot_row, 0) = recv_b_data;

                        delete[] recv_row_data;
                    }
                }

            }
            double* pivot_row;
            double pivot_b = 0;
            if (rank == pivot_proc) {
                pivot_row = &A_local(i - start_row, 0);
                pivot_b = B_local(i - start_row, 0);
                for (int j = pivot_proc + 1; j < size; j++)
                {
                    MPI_Send(&A_local(i - start_row, 0), m, MPI_DOUBLE, j, pivot_proc, MPI_COMM_WORLD);
                    MPI_Send(&B_local(i - start_row, 0), 1, MPI_DOUBLE, j, pivot_proc, MPI_COMM_WORLD);
                }
            }
            else {
                pivot_row = new double[m];
                MPI_Recv(pivot_row, m, MPI_DOUBLE, pivot_proc, pivot_proc, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&pivot_b, 1, MPI_DOUBLE, pivot_proc, pivot_proc, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

            for (int k = start_row; k < end_row; k++) {

                if (k <= i) {
                    continue;
                }
                int local_k = k - start_row;

                double multiplier = A_local(local_k, i) / pivot_row[i];

#pragma omp parallel for
                for (int j = i; j < m; j++) {
                    A_local(local_k, j) -= multiplier * pivot_row[j];

                    if (Matrix::is_equal(std::fabs(A_local(local_k, j)), 0.))
                        A_local(local_k, j) = 0;
                }
                B_local(local_k, 0) -= multiplier * pivot_b;
                if (Matrix::is_equal(std::fabs(B_local(local_k, 0)), 0.))
                    B_local(local_k, 0) = 0;
            }

            if (rank != pivot_proc) delete[] pivot_row;

        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    int k = n - 1;
    Matrix* x;
    int x_size = row_per_proc_local;
    if (rank != size-1) {
        int prev_proc_x_size = 0;
        MPI_Probe(rank + 1, 1, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_DOUBLE, &prev_proc_x_size);
        x_size += prev_proc_x_size;

        x = new Matrix(x_size, 1);

        MPI_Recv(&(*x)(row_per_proc_local, 0), prev_proc_x_size, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, &status);

        MPI_Probe(rank + 1, 2, MPI_COMM_WORLD, &status);
        int cnt = 0;
        MPI_Get_count(&status, MPI_INT, &cnt);
        MPI_Recv(&k, 1, MPI_INT, rank + 1, 2, MPI_COMM_WORLD, &status);

        
    }
    else {
        x = new Matrix(x_size, 1);
    }


    for (int local_k = k - start_row; local_k >= 0; local_k--)
    {
        (*x)(local_k, 0) = B_local(local_k, 0);
        double sum = 0;
#pragma omp parallel for reduction (+:sum)
        for (int j = k + 1; j < m; j++) {
            sum = sum + A_local(local_k, j) * (*x)(j - start_row, 0);
        }
        (*x)(local_k, 0) -= sum;
        (*x)(local_k, 0) /= A_local(local_k, k);
        (*x)(local_k, 0) = (*x)(local_k, 0);
        if (Matrix::is_equal(std::fabs((*x)(local_k, 0)), 0.)) {
            (*x)(local_k, 0) = 0;
        }

        k -= 1;
    }
    
    if (rank != 0)
    {     
        MPI_Send(&(*x)(0, 0), x_size, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD);        
        MPI_Send(&k, 1, MPI_INT, rank - 1, 2, MPI_COMM_WORLD);
        return false;
    }
    else if(rank == 0) {
        this->x = *x;
    }

    A_local.clearAll();
    B_local.clearAll();

    return true;
}

Matrix GaussParall::getSolution()
{
    return x;
}

