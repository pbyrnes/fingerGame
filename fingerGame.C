#include<iostream>

using namespace std;

int result[5][5][5][5];

int getResult(int,int, int, int);
void applyMove(int,int,int,int,int,int&,int&,int&,int&);
bool validMove(int,int,int,int,int);

int main()
{
  for(int i=0; i<5; i++)
    for(int j=0; j<5; j++)
      for(int k=0; k<5; k++)
        for(int s=0; s<5; s++)
          result[i][j][k][s] = 0;
  for(int i=0; i<5; i++)
    for(int j=0; j<5; j++)
      result[i][j][0][0] = 1;
  for(int i=0; i<5; i++)
    for(int j=0; j<5; j++)
      result[0][0][i][j] = -1;

  bool progress = true;
  int iter = 0;
  while(progress && iter < 1000)
  {
    progress = false;
    if(iter % 100 == 0)
      cout << "starting iteration: " << iter << endl;
    iter++;
    for(int i=0; i<5; i++)
      for(int j=0; j<5; j++)
        for(int k=0; k<5; k++)
          for(int s=0; s<5; s++)
          {
            if(result[i][j][k][s] == 0)
            {
              result[i][j][k][s] = getResult(i,j,k,s);
              if(result[i][j][k][s] != 0)
                progress = true;
            }
          }
  }
  cout << "total number of iterations: " << iter << endl;;
  for(int k=0; k<5; k++)
    for(int s=0; s<5; s++)
    {
      for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
        {
          if(i<=j && k<=s)  
          {
            if(result[i][j][k][s] != -1)
              cout << " ";
            cout << result[i][j][k][s] << " ";
          }
        }
      if(k <= s)
        cout << endl;
    }

  return 0;

}

bool validMove(int a, int b, int c, int d, int m)
{
  switch(m)
  {
    case 0:
      if(a == 0 || c == 0)
        return false;
      c = c+a;
      break;
    case 1:
      if(a == 0 || d==0)
        return false;
      d = d+a;
      break;
    case 2:
      if(b == 0 || c == 0)
        return false;
      c = c+b;
      break;
    case 3:
      if(b == 0 || d ==0)
        return false;
      d = d+b;
      break;
    case 4:
      if(a==0 || b==0)
        return false;
      b = (a+b)%5;
      a = 0;
      break;
    case 5:
      if(a==1 || b == 1)
        return false;
      b = a+b-1;
      a = 1;
      break;
    case 6:
      if(a==2 || b==2)
        return false;
      b = a+b-2;
      a = 2;
      break;
    case 7:
      if(a==3 || b==3)
        return false;
      b = a+b-3;
      a = 3;
      break;
    case 8:
      if(a==4 || b==4)
        return false;
      b = a+b-4;
      a = 4;
      break;
    default:
      cout << "ATTEMPTED NONSENSICAL MOVE" << endl;
  }
  if(a == 5)
    a = 0;
  if(b == 5)
    b = 0;
  if(c == 5)
    c = 0;
  if(d == 5)
    d = 0;

  if(a < 0 || a > 4 ||
     b < 0 || b > 4 ||
     c < 0 || c > 4 ||
     d < 0 || d > 4)
    return false;
  return true;
}

void applyMove(int a, int b, int c, int d, int m, 
              int& newA, int& newB, int& newC, int& newD)
{
  switch(m)
  {
    case 0:
      c = c+a;
      break;
    case 1:
      d = d+a;
      break;
    case 2:
      c = c+b;
      break;
    case 3:
      d = d+b;
      break;
    case 4:
      b = (a+b)%5;
      a = 0;
      break;
    case 5:
      b = a+b-1;
      a = 1;
      break;
    case 6:
      b = a+b-2;
      a = 2;
      break;
    case 7:
      b = a+b-3;
      a = 3;
      break;
    case 8:
      b = a+b-4;
      a = 4;
      break;
    default:
      cout << "ATTEMPTED NONSENSICAL MOVE" << endl;
  }
  if(a == 5)
    a = 0;
  if(b == 5)
    b = 0;
  if(c == 5)
    c = 0;
  if(d == 5)
    d = 0;

  if(a < 0 || a > 4 ||
     b < 0 || b > 4 ||
     c < 0 || c > 4 ||
     d < 0 || d > 4)
  {
    cout << "ERROR: INVALID MOVE APPLIED" << endl;
  }

  newC = a;
  newD = b;
  newA = c;
  newB = d;

  return;
}  

int getResult(int a,int b, int c, int d)
{
cout << endl;
cout << "looking for result for " << a << b << c << d << endl;
  if(result[a][b][c][d] != 0)
  {
    cout << "SHOULD NOT BE DOING THIS" << endl;
    return result[a][b][c][d];
  }
  //check for winning move
  for(int i=0; i<9; i++)
  {
    if(validMove(a,b,c,d,i))
    {
cout << "here's a valid move: " << a << b << c << d << i << endl;
      int a2,b2,c2,d2;
      applyMove(a,b,c,d,i,a2,b2,c2,d2);
cout << "result of move: " << a2 << b2 << c2 << d2 << endl;
      if(result[a2][b2][c2][d2] == -1)
      {
        cout << "found a winning move" << endl;
        return i+1;
      }
//cout << "it's a losing move" << endl;
    }
  }
  //check for undetermined move
  for(int i=0; i<9; i++)
  {
    if(validMove(a,b,c,d,i))
    {
cout << "here's a valid move: " << a << b << c << d << i << endl;
      int a2,b2,c2,d2;
      applyMove(a,b,c,d,i,a2,b2,c2,d2);
cout << "result of move: " << a2 << b2 << c2 << d2 << endl;
      if(result[a2][b2][c2][d2] == 0)
      {
        cout << "result of move still undetermined" << endl;
        return 0;
      }
cout << "it's a losing move" << endl;
    }
  }



  return -1;
}      

