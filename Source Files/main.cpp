#include <iostream>
#include "Matrix.cpp"
#include "GaussLine.cpp"


int main(){
  // Matrix mat;
  // auto ret = mat.createMatrix(5,3);
  // ret = mat.fillMatrix("../data/data.bin");
  // std::cout<<std::endl<<mat.getCODE()<<std::endl;
  // 
  // ret = mat.toString(str);
  // std::cout<<"\n"<<str<<std::endl<<mat.getCODE()<<"\n\n";
  
  // std::cout<<"Add row array\n";
  // ret = mat.addRow(new float[3]{3,2,1}, 3);
  // ret = mat.toString(str);
  // std::cout<<str<<std::endl<<mat.getCODE()<<"\n\n";

  
  // std::cout<<"Add row string\n";
  // ret = mat.addRow("6 5 4");
  // ret = mat.toString(str);
  // std::cout<<str<<std::endl<<mat.getCODE()<<"\n\n";

  // std::cout<<"Add column array\n";
  // ret = mat.addColumn(new float[7]{3,2,0,0,-1,-2,10}, 7);
  // ret = mat.toString(str);
  // std::cout<<str<<std::endl<<mat.getCODE()<<"\n\n";

  // std::cout<<"Add column string\n";
  // ret = mat.addColumn("0 9 0 0 6 5 2");
  // ret = mat.toString(str);
  // std::cout<<str<<std::endl<<mat.getCODE()<<"\n\n";

  // float* row = new float[mat.getRowCnt()];
  // ret = mat.getRow(1,row);
  // float* col = new float[mat.getColCnt()];
  // ret = mat.getColumn(2,col);

  // if(!ret){
  //   for (int i = 0; i < mat.getRowCnt(); i++)
  //   {
  //     std::cout<<row[i];
  //   }
  //   std::cout<<std::endl;
  // }
  // if(!ret){
  //   for (int i = 0; i < mat.getColCnt(); i++)
  //   {
  //     std::cout<<col[i];
  //   }
  //   std::cout<<std::endl;
  // }
  
  // std::cout<<"Switch rows\n"; 
  // mat.switchRows(1,4);
  // ret = mat.toString(str);
  // std::cout<<str<<std::endl<<mat.getCODE()<<std::endl<<std::endl;
  
  // std::cout<<"Multiply 1 row by 10\n"; 
  // mat.multiplyRow(1,10);
  // ret = mat.toString(str);
  // std::cout<<str<<std::endl<<mat.getCODE()<<std::endl<<std::endl;

  
  // std::cout<<"Add 0 row * 10 to 4\n"; 
  // ret = mat.addMultipliedRowToAnother(4,0,10);
  // ret = mat.toString(str);
  // std::cout<<str<<std::endl<<mat.getCODE()<<std::endl<<std::endl;

  
  // std::cout<<"Delete zero rows\n"; 
  // ret = mat.deleteZeroRows(); 
  // ret = mat.toString(str);
  // std::cout<<str<<std::endl<<mat.getCODE()<<std::endl<<std::endl;

  // std::cout<<"Subtract from 1 0\n"; 
  // ret = mat.subtractRow(1,0); 
  // ret = mat.toString(str);
  // std::cout<<str<<std::endl<<mat.getCODE()<<std::endl<<std::endl;

  GaussLine gaussLine;
  Matrix rez = gaussLine.run();
  std::string str;
  auto ret = rez.toString(str);
  std::cout<<str<<std::endl<<rez.getCODE()<<std::endl<<std::endl;

  gaussLine.createAMatrix()
}