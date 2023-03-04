#include "../Header Files/Matrix.h"


Matrix::Matrix(){
  this->n = 0;
  this->m = 0;
  this->array = nullptr;
  this->code = 0;
}
int Matrix::getRowCnt()
{
  return n;
}

int Matrix::getColCnt()
{
  return m;
}

std::string Matrix::getCODE(){
  return codes[code];
}

CODE Matrix::createMatrix(int n, int m){
  this->n = n;
  this->m = m;
  this->array = new float*[this->n];
  for (int i = 0; i < this->n; i++)
  {
    this->array[i] = new float[this->m];
  }
  code = 0;
  return code;
}

CODE Matrix::fillMatrix(float** source, int rows, int columns){
  if(code!=0){
    return code;
  }
  if (this->array == nullptr || this->n == 0 || this->m == 0){
    code = 1;
    return code;
  }
  if (n!=rows || m != columns){
    code = 2;
    return code;
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      this->array[i][j] = source[i][j];
    }    
  }

  code = 0;
  return code;
}

CODE Matrix::addRow(float *row, int c)
{
  if(code)
    return code;
  
  if(c != m){
    code = 2;
    return code; 
  }

  float** new_array = new float*[n+1];
  for (int i = 0; i < n; i++)
  {
    new_array[i] = new float[m];
    for (int j = 0; j < m; j++)
    {
      new_array[i][j] = array[i][j];
    }
  }

  new_array[n] = new float[m];
  for (int i = 0; i < m; i++)
  {
    new_array[n][i] = row[i];
  }

  n++;
  
  createMatrix(n,m);
  
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      array[i][j] = new_array[i][j];
    }
    
  }
  

  code = 0;
  return code;
  
  
}


CODE Matrix::addRow(std::string row)
{
  if(code)
    return code;

  float* new_row = new float[m];
  bool digit = false;
  std::string new_value = "";
  int k = -1;
  for (int i = 0; i < row.length(); i++)
  {
    if(row[i] != ' ' && digit){
      new_value+=row[i];
    }
    if(row[i] != ' ' && !digit){
      digit = true;
      new_value = row[i];      
    }
    if((row[i] == ' ' || i+1 == row.length()) && digit){
      digit = false;
      k++;
      float value = std::stof(new_value);
      new_row[k] = value;
      
    }  

  }
  if(k==-1){
    code = 4;
    return code;
  }
  if(k+1 != m){
    code = 2;
    return code; 
  }

  float** new_array = new float*[n+1];
  for (int i = 0; i < n; i++)
  {
    new_array[i] = new float[m];
    for (int j = 0; j < m; j++)
    {
      new_array[i][j] = array[i][j];
    }
  }
  new_array[n] = new float[k+1];
  for (int i = 0; i < k+1; i++)
  {
    new_array[n][i] = new_row[i];
  }
  
  n++;
  
  createMatrix(n,m);
  
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      array[i][j] = new_array[i][j];
    }
    
  }

  delete[] new_row;

  code = 0;
  return code;
   
}
CODE Matrix::addColumn(float *column, int c)
{
  if(code)
    return code;
  
  if(c != n){
    code = 2;
    return code; 
  }

  float** new_array = new float*[n];
  for (int i = 0; i < n; i++)
  {
    new_array[i] = new float[m+1];
    for (int j = 0; j < m; j++)
    {
      new_array[i][j] = array[i][j];
    }
  }

  for (int i = 0; i < n; i++)
  {
    new_array[i][m] = column[i];
  }

  m++;
  
  createMatrix(n,m);
  
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      array[i][j] = new_array[i][j];
    }
    
  } 

  code = 0;
  return code;
}


CODE Matrix::addColumn(std::string column){
  if(code)
    return code;

  float* new_column = new float[n];
  bool digit = false;
  std::string new_value = "";
  int k = -1;
  for (int i = 0; i < column.length(); i++)
  {
    if(column[i] != ' ' && digit){
      new_value+=column[i];
    }
    if(column[i] != ' ' && !digit){
      digit = true;
      new_value = column[i];      
    }
    if((column[i] == ' ' || i+1 == column.length()) && digit){
      digit = false;
      k++;
      float value = std::stof(new_value);
      new_column[k] = value;
      
    }  

  }
  if(k==-1){
    code = 4;
    return code;
  }
  if(k+1 != n){
    code = 2;
    return code; 
  }

  float** new_array = new float*[n];
  for (int i = 0; i < n; i++)
  {
    new_array[i] = new float[m+1];
    for (int j = 0; j < m; j++)
    {
      new_array[i][j] = array[i][j];
    }
  }
  for (int i = 0; i < k+1; i++)
  {
    new_array[i][m] = new_column[i];
  }
  
  m++;
  
  createMatrix(n,m);
  
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      array[i][j] = new_array[i][j];
    }
    
  }

  delete[] new_column;

  code = 0;
  return code;
}

CODE Matrix::fillMatrix(std::string filename){
  if(code!=0){
    return code;
  }
  std::ifstream file(filename);

  if(!file){
    code = 3;
    return code;
  }

  int row_cnt = 0;
  int col_cnt = 0;
  std::string elem;
  
  while(file>>elem){  
    array[row_cnt][col_cnt] = std::stof(elem);    
    
    if(col_cnt == m-1){
      col_cnt = 0;
      row_cnt++;
      //std::cout<<row_cnt<<col_cnt<<std::endl;
    }
    else{  
      //std::cout<<row_cnt<<col_cnt<<std::endl;
      col_cnt++;
    }    
    
    if(row_cnt>n-1 && !file.eof()){       
        code = 2;
        return code;
    }  
    
  }
  if(row_cnt<n-1){
    code = 2;
    return code;
  }
  
  file.close();
  code = 0;
  return code;
}

CODE Matrix::toString(std::string &str){
  
  if(code)
    return code;

  str = "";
  for (int i = 0; i < this->n; i++)
  {
    for (int j = 0; j < this->m; j++)
    {
      
      str+=std::to_string(array[i][j]) + " ";
    }
    if(i+1 != n)
      str+="\n";
  }

  code = 0;
  return code;  
}

CODE Matrix::getRow(int rowNumber, float* row){
  if(code)
    return code;

  for (int i = 0; i < m; i++)
  {
    row[i] = array[rowNumber][i];
  }

  code = 0;
  return code;
  
}

CODE Matrix::getColumn(int colNumber, float* col){
  if(code)
    return code;
  for (int i = 0; i < n; i++)
  {
    col[i] = array[i][colNumber];
  }

  code = 0;
  return code;
}

CODE Matrix::switchRows(int sourceRowNumber, int distRowNumber){

  if(code)
    return code;

  if(sourceRowNumber > m || sourceRowNumber < 0 || distRowNumber > m || distRowNumber < 0){
    code = 5;
    return code;
  }

  float* temp = new float[m];
  for (int i = 0; i < m; i++)
  {
    temp[i] = array[sourceRowNumber][i];
    array[sourceRowNumber][i] = array[distRowNumber][i];
    array[distRowNumber][i] = temp[i];
  }

  delete[] temp;

  code = 0;
  return code;
  
}

CODE Matrix::multiplyRow(int rowNumber, float multiplier){
  if(code)
    return code;
  
  if(rowNumber > n || rowNumber < 0){
    code = 5;
    return code;
  }

  for (int i = 0; i < m; i++)
  {
    array[rowNumber][i]*=multiplier;
  }

  code = 0;
  return code;
}

CODE Matrix::addMultipliedRowToAnother(int firstRowNumber, int secondRowNumber, float multiplier){
  if(code)
    return code;
  
  if(firstRowNumber > n || firstRowNumber < 0 || secondRowNumber > n || secondRowNumber < 0){
    code = 5;
    return code;
  }

  for (int i = 0; i < m; i++)
  {
    array[firstRowNumber][i] += array[secondRowNumber][i]*multiplier;
  }

  code = 0;
  return code;
}

CODE Matrix::deleteZeroRows(){
  if(code)
    return code;

  bool isZero = false;
  char* zeroRowNumber = new char[n];
  int zeroCnt = 0;
  for (int i = 0; i < n; i++)
  {
    zeroRowNumber[i] = '0';
  }  

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (array[i][j] != 0){
        isZero = false;
        break;
      }
      if (array[i][j]==0)
        isZero = true;
      
    }
    if(!isZero)
      continue;
    
    if(isZero){
      zeroRowNumber[i] = '1';
      zeroCnt++;
    }
  }

  float** new_array = new float*[n-zeroCnt];
  

  for (int i = 0, k = 0; i < n; i++)
  {
    if(zeroRowNumber[i] == '1')
      continue;
    
    //std::cout<<zeroRowNumber[i]<<' '<<i<<' '<<k<<' ';
    new_array[k] = new float[m];
    for (int j = 0; j < m; j++)
    {
      new_array[k][j] = array[i][j];
    } 
    k++;
  }

  n = n-zeroCnt;
  for (int i = 0; i < n+zeroCnt; i++)
  {
    delete[] array[i];
  }
  delete[] array;

  array = new float*[n];
  for (int i = 0; i < n; i++)
  {
    array[i] = new float[m];
    for (int j = 0; j < m; j++)
    {
      array[i][j] = new_array[i][j];   
      delete[] new_array[i];
    }
  
  }
  delete[] new_array;
  delete[] zeroRowNumber; 
  
  code = 0;
  return code;
}

CODE Matrix::subtractRow(int firstRowNumber, int secondRowNumber){
  if(code)
    return code;

  if(firstRowNumber > m || firstRowNumber < 0 || secondRowNumber > m || secondRowNumber < 0)
    return code = 5;

  for (int i = 0; i < m; i++)
  {
    array[firstRowNumber][i] -= array[secondRowNumber][i];
  }

  return code = 0;
  
}


Matrix::~Matrix(){
  for (int i = 0; i < n; i++)
  {
    delete[] array[i];
  }
  delete[] array;
}
