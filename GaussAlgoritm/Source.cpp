#include "GaussParall.h"
#include "GaussLine.h"
//#include <time.h> 

void create_matrix_set(int min_mat_size, int max_mat_size, int step, std::string filename) {
    for (int i = min_mat_size; i <= max_mat_size; i += step)
    {
        std::ofstream out;
        std::ofstream out1;
        std::ofstream out2;
        out.open("tests\\" + filename + std::to_string(i) + "_a.txt", std::fstream::out);
        out1.open("tests\\" + filename + std::to_string(i) + "_b.txt", std::fstream::out);
        if (!out || !out1) {
            std::cout << "File error!" << std::endl;
            return;
        }
        out << i << " " << i << std::endl;
        out1 << i << " " << 1 << std::endl;
        for (int j = 0; j < i; j++)
        {
            for (int j = 0; j < i; j++)
            {
                out << std::rand() << " ";
            }
            out << std::endl;
            out1 << std::rand() << std::endl;
        }
        out1.close();
        out.close();
        out2.open("tests\\" + filename + std::to_string(i) + "_correct.txt", std::fstream::out);
        Matrix A, b;
        A.read_from_file("tests/" + filename + std::to_string(i) + "_a.txt");
        b.read_from_file("tests/" + filename + std::to_string(i) + "_b.txt");
        GaussLine solver;
        Matrix x2;
        bool success = solver.solve(A, b);
        x2 = solver.getSolution();
        out2 << x2.rows() << " " << x2.cols() << "\n";
        for (int i = 0; i < x2.rows(); i++)
        {
            out2 << x2(i, 0) << "\n";
        }
        out2.close();

    }

}



int main(int argc, char** argv) {
    const double EPSILON = 1e-6;
    int rank;
    int size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    omp_set_num_threads(4);
    int mat_size = 10;
    try
    {
        if (argc > 1) {
            mat_size = atoi(argv[1]);
        }
    }
    catch (const std::exception&)
    {

    }


    std::string filename = "parall_test";
    /*if (rank == 0) {

        create_matrix_set(10, 100, 10, filename);
    }
    MPI_Finalize();
    return 1;*/
    for (int i = 10; i <= 10; i += 10)
    {
        mat_size = i;
        GaussParall solver(rank, size);
        Matrix A, b, x1;
        int n = 0, m = 0;
        double* matA, * matB;
        bool file_opened = true;
        if (rank == 0) {
            //double start = MPI_Wtime();
            //A.create_random_matrix(mat_size, mat_size);
            //double end = MPI_Wtime();
            //std::cout << "Matrix A created " << end - start << "\n";
            //start = MPI_Wtime();
            //b.create_random_matrix(mat_size, 1);
            //end = MPI_Wtime();
            //std::cout << "Matrix B created " << end - start << "\n";

            A.read_from_file("tests/" + filename + std::to_string(i) + "_a.txt");
            b.read_from_file("tests/" + filename + std::to_string(i) + "_b.txt");

            n = A.rows();
            m = A.cols();
        }
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

        matA = new double[m * n];
        matB = new double[n];
        if (rank == 0) {
            matA = A.get_data();
            matB = b.get_data();
        }
        MPI_Bcast(matA, m * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(matB, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        A.create_from_another_matrix(matA, n, m);
        b.create_from_another_matrix(matB, n, 1);
        /*if(rank == 1)
            b.print();*/

        MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */
        double start = MPI_Wtime();
        bool success = solver.solve(A, b);
        MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */
        double end = MPI_Wtime();
        if (rank == 0) {
            if (success) {

                //std::cout << i << " " << end - start << std::endl;
                x1 = solver.getSolution();
                //x1.round_matrix(EPSILON);
                std::cout << "Parall answer:\n";
                x1.print();

                GaussLine solver;
                Matrix x2, x3;
                start = MPI_Wtime();
                bool success = solver.solve(A, b);
                end = MPI_Wtime();
                std::cout << "\n";
                x2 = solver.getSolution();
                //x2.round_matrix(EPSILON);
                std::cout << "Line answer:\n";
                x2.print();
                x3.read_from_file("tests/" + filename + std::to_string(i) + "_correct.txt");

                std::cout << "\nCorrect answer:\n";
                //x3.round_matrix(EPSILON);
                x3.print();
                bool is_Equal = true;
                for (int i = 0; i < mat_size; i++)
                {
                    //std::cout << std::abs(x1(i, 0) - x2(i, 0)) << "    " << EPSILON << "\n";
                    if (std::fabs(x1(i, 0) - x3(i, 0)) > EPSILON * 100 || std::fabs(x2(i, 0) - x3(i, 0)) > EPSILON * 100)
                    {
                        std::cout << x1(i, 0) << " " << x2(i, 0) << " " << x3(i, 0) << " " << EPSILON << "\n";
                        is_Equal = false;
                        break;
                    }
                }
                if (is_Equal)
                    std::cout << "Number of equations: " << mat_size << "\nAnswers are equal\n";
                else
                    std::cout << "Number of equations: " << mat_size << "\nAnswers are not equal\n";
                x2.clearAll();
            }
        }



        A.clearAll();
        b.clearAll();
        x1.clearAll();
    }





    /*if (rank == 0) {

        Matrix A, b;
        std::cout << "\n\n";
        GaussLine solverLine;

        double start = MPI_Wtime();
        solverLine.solve(A, b);
        double end = MPI_Wtime();
        std::cout << "Time:\t" << end - start << std::endl;

        Matrix x = solverLine.getSolution();
        x.print();
    }*/




    MPI_Finalize();



}