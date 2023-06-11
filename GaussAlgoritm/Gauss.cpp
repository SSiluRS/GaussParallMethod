//#include "Gauss.h"
//
//Gauss::Gauss() {
//    n = 0;
//    eps = 0.00001;
//    code = 0;
//    a = new Matrix();
//    b = new Matrix();
//    x = new Matrix();
//}
//
//std::string Gauss::getCODE() {
//    return codes[code];
//}
//
//CODE Gauss::createAMatrix(int n, float** source) {
//
//    if (code) {
//        a->setCODE(code);
//        return code;
//    }
//    auto ret = a->createMatrix(n, n);
//    ret = a->fillMatrix(source, n, n);
//    if (!ret) {
//        this->n = n;
//    }
//    return code = ret;
//}
//
//CODE Gauss::createAMatrix(int n, std::string filename) {
//
//    if (code) {
//        a->setCODE(code);
//        return code;
//    }
//    auto ret = a->createMatrix(n, n);
//    ret = a->fillMatrix(filename);
//    if (!ret) {
//        this->n = n;
//    }
//    return code = ret;
//}
//
//CODE Gauss::createBMatrix(int n, float** source) {
//    if (code) {
//        b->setCODE(code);
//        return code;
//    }
//    auto ret = b->createMatrix(n, 1);
//    ret = b->fillMatrix(source, n, 1);
//    if (!ret) {
//        this->n = n;
//    }
//    return code = ret;
//}
//
//CODE Gauss::createBMatrix(int n, std::string filename) {
//    if (code) {
//        b->setCODE(code);
//        return code;
//    }
//    auto ret = b->createMatrix(n, 1);
//    ret = b->fillMatrix(filename);
//    if (!ret) {
//        this->n = n;
//    }
//    return code = ret;
//}
//
//CODE Gauss::createXMatrix(int n, float** source)
//{
//    if (code) {
//        x->setCODE(code);
//        return code;
//    }
//    auto ret = x->createMatrix(n, 1);
//    if (!ret) {
//        this->n = n;
//    }
//    return code = ret;
//}
//
//CODE Gauss::getA(Matrix*& a) {
//    a = this->a;
//    return code;
//}
//
//CODE Gauss::getB(Matrix*& b) {
//    b = this->b;
//    return code;
//}
//
//CODE Gauss::getX(Matrix*& x)
//{
//    x = this->x;
//    return code;
//}
//
//bool Gauss::test1()
//{
//    if (code) {
//        a->setCODE(code);
//        b->setCODE(code);
//        x->setCODE(code);
//        return code;
//    }
//
//    std::string A_file = "testa1.txt";
//    std::string B_file = "testb1.txt";
//    std::string Correct_file = "correct1.txt";
//    createAMatrix(3, A_file);
//    createBMatrix(3, B_file);
//    Matrix* correct = new Matrix();
//    correct->createMatrix(3, 1);
//
//    a->fillMatrix(A_file);
//    b->fillMatrix(B_file);
//    std::string str = "";
//    a->toString(str);
//    std::cout << str << "\n" << a->getCODE() << "\n\n";
//    b->toString(str);
//    std::cout << str << "\n" << b->getCODE() << "\n\n";
//    correct->fillMatrix(Correct_file);
//    run();
//    bool isEqual = true;
//    for (int i = 0; i < 3; i++)
//    {
//        float* row_x = nullptr, * row_cor = nullptr;
//        x->getRow(i, row_x);
//        correct->getRow(i, row_cor);
//        if (row_x[0] != row_cor[0]) {
//            isEqual = false;
//            break;
//        }
//    }
//
//    return isEqual;
//}
//
//bool Gauss::test2()
//{
//    if (code) {
//        a->setCODE(code);
//        b->setCODE(code);
//        x->setCODE(code);
//        return code;
//    }
//
//    std::string A_file = "testa2.txt";
//    std::string B_file = "testb2.txt";
//    std::string Correct_file = "correct2.txt";
//    createAMatrix(3, A_file);
//    createBMatrix(3, B_file);
//    Matrix* correct = new Matrix();
//    correct->createMatrix(3, 1);
//
//    a->fillMatrix(A_file);
//    b->fillMatrix(B_file);
//    std::string str = "";
//    a->toString(str);
//    std::cout << str << "\n" << a->getCODE() << "\n\n";
//    b->toString(str);
//    std::cout << str << "\n" << b->getCODE() << "\n\n";
//    correct->fillMatrix(Correct_file);
//    run();
//    bool isEqual = true;
//    for (int i = 0; i < 3; i++)
//    {
//        float* row_x = nullptr, * row_cor = nullptr;
//        x->getRow(i, row_x);
//        correct->getRow(i, row_cor);
//        if (row_x[0] != row_cor[0]) {
//            isEqual = false;
//            break;
//        }
//    }
//
//    return isEqual;
//}