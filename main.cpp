#include <iostream>
#include "matrix.h"
using namespace std;

int main()
{
    cout<<"\tMATRIX CALCULATOR"<<endl<<endl;
    int r, c;
    cout<<"Enter number of rows : ";
    cin>>r;
    cout<<"Enter number of columns : ";
    cin>>c;

    Matrix *ptr = new Matrix(r,c);
    ptr->read();

    if(ptr->checkDiagonal())
    {
        DiagonalMatrix dm(r);
        dm = *ptr;
        dm.operations();
    }
    else if(ptr->checkSymmetric())
    {
        SymmetricMatrix sm(r);
        sm = *ptr;
        sm.operations();
    }
    else if(ptr->checkTriangular())
    {
        TriangularMatrix tm(r);
        tm = *ptr;
        tm.operations();
    }
    else if(ptr->checkSquare())
    {
        SquareMatrix s(r);
        s = *ptr;
        s.operations();
    }
    else
    {
        Matrix m(r,c);
        m = *ptr;
        m.operations();
    }
    delete ptr;

    return 0;
}
