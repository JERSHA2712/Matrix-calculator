#include <iostream>
#include <cmath>
#include "matrix.h"

using namespace std;

Matrix :: Matrix()
{
    row = 0;
    col = 0;
}

Matrix :: Matrix(int r,int c)
{
    row = r;
    col = c;

    pp = new double *[r];
    for(int i=0; i<r; i++)
        pp[i] = new double [c];

    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            pp[i][j] = 0;
}

void Matrix :: setDimension(int r,int c)
{
    for(int i=0;i<row;i++)
        delete [] pp[i];
    delete [] pp;

    row = r;
    col = c;

    pp = new double *[r];
    for(int i=0; i<r; i++)
        pp[i] = new double [c];

    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            pp[i][j] = 0;
}

void Matrix :: read()
{
    cout<<endl<<"Enter the matrix : "<<endl;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            cin>>pp[i][j];
        }
    }
}

void Matrix :: display() const
{
    cout<<endl<<"MATRIX : "<<endl;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            cout<< ((abs(pp[i][j]) < 0.00000000005)? 0.000: pp[i][j]) <<"\t";
        }
        cout<<endl<<endl;
    }
}

Matrix Matrix :: transpose()
{
    Matrix m(col,row);

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            m.pp[j][i] = this->pp[i][j];

    return m;
}

bool Matrix :: checkSquare()
{
    if(row == col)
        return true;
    else
        return false;
}

bool Matrix :: checkSymmetric()
{
    if(row==col)
    {
        Matrix m(row,col);
        m = transpose();

        for(int i=0; i<row; i++)
            for(int j=0; j<col; j++)
                if(m.pp[i][j] != this->pp[i][j])
                    return false;
        return true;
    }
    else
        return false;
}

bool Matrix :: checkTriangular()
{
    if(row==col)
    {
        int flag = 1;

        for(int i=1; i<row; i++)
        {
            for(int j=0; j<i; j++)
            {
                if(pp[i][j] != 0)
                {
                    flag = 0;
                    break;
                }
            }
            if(flag == 0)
                break;
        }

        if(flag)
            return true;

        flag = 1;
        for(int i=0; i<row; i++)
        {
            for(int j=i+1; j<col; j++)
            {
                if(pp[i][j] != 0)
                {
                    flag = 0;
                    break;
                }
            }
            if(flag==0)
                break;
        }

        if(flag)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool Matrix :: checkDiagonal()
{
    if(row==col)
    {
        for(int i=1; i<row; i++)
            for(int j=0; j<i; j++)
                if(pp[i][j] != 0)
                    return false;

        for(int i=0; i<row; i++)
            for(int j=i+1; j<col; j++)
                if(pp[i][j] != 0)
                    return false;

        return true;
    }
    else
        return false;
}

bool Matrix :: operator ==(Matrix m)
{
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            if(pp[i][j]!=m.pp[i][j])
                return false;
    return true;
}

Matrix Matrix :: operator +(Matrix m)
{
    Matrix r(row,col);
    for(int i=0; i<m.row; i++)
        for(int j=0; j<m.col; j++)
            r.pp[i][j] = pp[i][j] + m.pp[i][j];
    return r;
}

Matrix Matrix :: operator -(Matrix m)
{
    Matrix r(row,col);
    for(int i=0; i<m.row; i++)
        for(int j=0; j<m.col; j++)
            r.pp[i][j] = pp[i][j] - m.pp[i][j];
    return r;
}

Matrix Matrix :: operator *(Matrix m)
{
    Matrix r(row,m.col);
    for(int i=0; i<row; i++)
        for(int j=0; j<m.col; j++)
            for(int k=0; k<col; k++)
                r.pp[i][j] += pp[i][k] * m.pp[k][j];
    return r;
}

void Matrix :: editMatrix()
{
    int flag = 1;
    while(flag)
    {
        int r,c,num;
        cout<<"Enter row index : ";
        cin>>r;
        while(r<1 || r>row)
        {
            cout << "Invalid Index! Enter row index again: ";
            cin >> r;
        }
        cout<<"Enter column index : ";
        cin>>c;
        while(c<1 || c>col)
        {
            cout << "Invalid Index! Enter column index again: ";
            cin >> c;
        }
        cout<<"Enter new value : ";
        cin>>num;
        pp[r-1][c-1] = num;
        cout<<"Do you want to edit again? (0 - no , 1 - yes) : ";
        cin>>flag;
    }
}

Matrix Matrix :: scalarMultiplication(double k)
{
    Matrix r(row,col);
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            r.pp[i][j] = k * pp[i][j];
    return r;
}

Matrix Matrix :: tripletNotation()
{
    int c = 0;
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            if(pp[i][j] != 0)
                c++;

    Matrix t(c+1,3);
    t.pp[0][0] = row;
    t.pp[0][1] = col;
    t.pp[0][2] = c;
    int index = 1;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            if(pp[i][j]!=0)
            {
                t.pp[index][0] = i;
                t.pp[index][1] = j;
                t.pp[index][2] = pp[i][j];
                index++;
            }
        }
    }

    return t;
}

int Matrix :: getRow()
{
    return row;
}

int Matrix :: getColumn()
{
    return col;
}

double** Matrix :: getMatrix()
{
    return pp;
}

void Matrix::operations()
{
    int x=1, choice;
    while(x)
    {
        display();
        cout << "Available operations: " << endl;
        cout << "1. Add\n2. Subtract\n3. Scalar Multiplication\n4. Multiplication\n5. Transpose\n6. Edit Matrix\n7.Sparse matrix to triplet notation\n8. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this + temp;
                temp.display();
                break;
            }
            case 2:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this - temp;
                temp.display();
                break;
            }
            case 3:
            {
                Matrix temp(row, col);
                double n;
                cout << "Enter a scalar to multiply: ";
                cin >> n;
                temp = scalarMultiplication(n);
                temp.display();
                break;
            }
            case 4:
            {
                int n;
                cout << "The order of the matrix must be " << col << " x " << "?" << endl;
                cout << "Column: ";
                cin >> n;
                Matrix temp(col, n);
                temp.read();
                temp = *this * temp;
                temp.display();
                break;
            }
            case 5:
            {
                Matrix temp(row, col);
                temp = transpose();
                temp.display();
                break;
            }
            case 6:
            {
                editMatrix();
                cout << "The new matrix:" << endl;
                break;
            }
            case 7:
            {
                Matrix triplet = tripletNotation();
                triplet.display();
                break;
            }
            case 8:
            {
                x=0;
                break;
            }
            default:
            {
                cout << "Invalid choice!" << endl;
            }
        }
    }
}

/*
Matrix :: ~Matrix()
{

}
*/

SquareMatrix::SquareMatrix(): Matrix()
{

}

SquareMatrix::SquareMatrix(int n) : Matrix(n, n)
{

}

void SquareMatrix::operator =(Matrix& m)
{
    row = m.getRow();
    col = m.getColumn();
    pp = m.getMatrix();
}

double SquareMatrix::determinant()
{
    double det=0;
    SquareMatrix temp(row-1);
    int tempi, tempj;
    if (row==1) return pp[0][0];
    if (row==2) return (pp[0][0] * pp[1][1]) - (pp[0][1] * pp[1][0]);
    else
    {
        for(int x=0; x<row; x++)
        {
            tempi = 0;
            for(int i=1; i<row; i++)
            {
                tempj=0;
                for(int j=0; j<row; j++)
                {
                    if(j==x) continue;
                    else
                    {
                        temp.pp[tempi][tempj]=pp[i][j];
                        tempj++;
                    }
                }
                tempi++;
            }
            det = det + (pow(-1, x)* pp[0][x]* temp.determinant());
        }
    }
    return det;
}

SquareMatrix SquareMatrix::cofactor()
{
    SquareMatrix res(row);
    int tempi, tempj;
    SquareMatrix temp(row-1);
    for(int x=0; x<row; x++)
    {
        for(int y=0; y<col; y++)
        {
            tempi=0;
            tempj=0;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(i!=x && j!=y)
                    {
                        temp.pp[tempi][tempj] = pp[i][j];
                        if(tempj<(col-2)) tempj++;
                        else
                        {
                            tempj=0;
                            tempi++;
                        }
                    }
                }
            }
            res.pp[x][y]= pow(-1, x+y) * temp.determinant();
        }
    }
    return res;
}

SquareMatrix SquareMatrix::transpose()
{
    SquareMatrix res(row);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            res.pp[j][i]= pp[i][j];
        }
    }
    return res;
}

SquareMatrix SquareMatrix::adjoint()
{
    SquareMatrix res(row);
    res = cofactor().transpose();
    return res;
}

SquareMatrix SquareMatrix::inverse()
{
    SquareMatrix res(row);
    res = adjoint();
    double det = determinant();
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            res.pp[i][j] = res.pp[i][j]/det;
        }
    }
    return res;
}

void SquareMatrix :: toeplitzDecomposition()
{
    Matrix res(row,col);
    res = *this + transpose();
    res = res.scalarMultiplication(0.5);
    res.display();

    res = *this - transpose();
    res = res.scalarMultiplication(0.5);
    res.display();
}

void SquareMatrix::operations()
{
    int x=1, choice;
    while(x)
    {
        display();
        cout << "Available operations: " << endl;
        cout << "1. Add\n2. Subtract\n3. Scalar Multiplication\n4. Multiplication\n5. Transpose\n6. Edit Matrix\n7. Determinant\n8. Cofactor Matrix\n9. Adjoint Matrix\n10. Inverse Matrix\n11. Teoplitz Decomposition\n12. Sparse matrix to triplet notation\n13. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this + temp;
                temp.display();
                break;
            }
            case 2:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this - temp;
                temp.display();
                break;
            }
            case 3:
            {
                Matrix temp(row, col);
                double n;
                cout << "Enter a scalar to multiply: ";
                cin >> n;
                temp = scalarMultiplication(n);
                temp.display();
                break;
            }
            case 4:
            {
                int n;
                cout << "The order of the matrix must be " << col << " x " << "?" << endl;
                cout << "Column: ";
                cin >> n;
                Matrix temp(col, n);
                temp.read();
                temp = *this * temp;
                temp.display();
                break;
            }
            case 5:
            {
                SquareMatrix temp(row);
                temp = transpose();
                temp.display();
                break;
            }
            case 6:
            {
                editMatrix();
                cout << "The new matrix:" << endl;
                break;
            }
            case 7:
            {
                double d;
                d = determinant();
                cout << "The determinant of the matrix is " << d <<endl;
                break;
            }
            case 8:
            {
                SquareMatrix r(row);
                r = cofactor();
                r.display();
                break;
            }
            case 9:
            {
                SquareMatrix r(row);
                r = adjoint();
                r.display();
                break;
            }
            case 10:
            {
                SquareMatrix r(row);
                r = inverse();
                r.display();
                break;
            }
            case 11:
            {
                toeplitzDecomposition();
                break;
            }
            case 12:
            {
                Matrix triplet = tripletNotation();
                triplet.display();
                break;
            }
            case 13:
            {
                x=0;
                break;
            }
            default:
            {
                cout << "Invalid choice!" << endl;
            }
        }
    }
}

SymmetricMatrix :: SymmetricMatrix() : SquareMatrix()
{

}

SymmetricMatrix :: SymmetricMatrix(int n) : SquareMatrix(n)
{

}

SymmetricMatrix SymmetricMatrix :: transpose()
{
    return *this;
}

void SymmetricMatrix::operator =(Matrix& m)
{
    row = m.getRow();
    col = m.getColumn();
    pp = m.getMatrix();
}

void SymmetricMatrix :: editMatrix()
{
    double **temp_pp;
    temp_pp = new double *[row];
    for(int i=0; i<row; i++)
        temp_pp[i] = new double [col];

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            temp_pp[i][j] = pp[i][j];

    Matrix :: editMatrix();

    if(checkSymmetric())
        return;
    else
    {
        for(int i=0; i<row; i++)
            for(int j=0; j<col; j++)
                pp[i][j] = temp_pp[i][j];
        delete temp_pp;
        cout << endl << "Edited matrix is not symmetric matrix..." << endl;
        return;
    }
}

void SymmetricMatrix::operations()
{
    int x=1, choice;
    while(x)
    {
        display();
        cout << "Available operations: " << endl;
        cout << "1. Add\n2. Subtract\n3. Scalar Multiplication\n4. Multiplication\n5. Transpose\n6. Edit Matrix\n7. Determinant\n8. Cofactor Matrix\n9. Adjoint Matrix\n10. Inverse Matrix\n11. Teoplitz Decomposition\n12. Sparse matrix to triplet notation\n13. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this + temp;
                temp.display();
                break;
            }
            case 2:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this - temp;
                temp.display();
                break;
            }
            case 3:
            {
                Matrix temp(row, col);
                double n;
                cout << "Enter a scalar to multiply: ";
                cin >> n;
                temp = scalarMultiplication(n);
                temp.display();
                break;
            }
            case 4:
            {
                int n;
                cout << "The order of the matrix must be " << col << " x " << "?" << endl;
                cout << "Column: ";
                cin >> n;
                Matrix temp(col, n);
                temp.read();
                temp = *this * temp;
                temp.display();
                break;
            }
            case 5:
            {
                SymmetricMatrix temp(row);
                temp = transpose();
                temp.display();
                break;
            }
            case 6:
            {
                editMatrix();
                cout << "The new matrix:" << endl;
                break;
            }
            case 7:
            {
                double d;
                d = determinant();
                cout << "The determinant of the matrix is " << d <<endl;
                break;
            }
            case 8:
            {
                SquareMatrix r(row);
                r = cofactor();
                r.display();
                break;
            }
            case 9:
            {
                SquareMatrix r(row);
                r = adjoint();
                r.display();
                break;
            }
            case 10:
            {
                SquareMatrix r(row);
                r = inverse();
                r.display();
                break;
            }
            case 11:
            {
                toeplitzDecomposition();
                break;
            }
            case 12:
            {
                Matrix triplet = tripletNotation();
                triplet.display();
                break;
            }
            case 13:
            {
                x=0;
                break;
            }
            default:
            {
                cout << "Invalid choice!" << endl;
            }
        }
    }
}

TriangularMatrix :: TriangularMatrix() : SquareMatrix()
{

}

TriangularMatrix :: TriangularMatrix(int n) : SquareMatrix(n)
{

}

void TriangularMatrix ::operator =(Matrix& m)
{
    row = m.getRow();
    col = m.getColumn();
    pp = m.getMatrix();
}

double TriangularMatrix :: determinant()
{
    double det = 1.0;
    for(int i=0,j=0; i<row,j<col; i++,j++)
        det = det * pp[i][j];
    return det;
}

void TriangularMatrix :: editMatrix()
{
    double **temp_pp;
    temp_pp = new double *[row];
    for(int i=0; i<row; i++)
        temp_pp[i] = new double [col];

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            temp_pp[i][j] = pp[i][j];

    Matrix :: editMatrix();

    if(checkTriangular())
        return;
    else
    {
        for(int i=0; i<row; i++)
            for(int j=0; j<col; j++)
                pp[i][j] = temp_pp[i][j];
        delete temp_pp;
        cout << endl << "Edited matrix is not triangular matrix..." << endl;
        return;
    }
}

void TriangularMatrix::operations()
{
    int x=1, choice;
    while(x)
    {
        display();
        cout << "Available operations: " << endl;
        cout << "1. Add\n2. Subtract\n3. Scalar Multiplication\n4. Multiplication\n5. Transpose\n6. Edit Matrix\n7.Determinant\n8. Cofactor Matrix\n9. Adjoint Matrix\n10. Inverse Matrix\n11. Teoplitz Decomposition\n12. Sparse matrix to triplet notation\n13. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this + temp;
                temp.display();
                break;
            }
            case 2:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this - temp;
                temp.display();
                break;
            }
            case 3:
            {
                Matrix temp(row, col);
                double n;
                cout << "Enter a scalar to multiply: ";
                cin >> n;
                temp = scalarMultiplication(n);
                temp.display();
                break;
            }
            case 4:
            {
                int n;
                cout << "The order of the matrix must be " << col << " x " << "?" << endl;
                cout << "Column: ";
                cin >> n;
                Matrix temp(col, n);
                temp.read();
                temp = *this * temp;
                temp.display();
                break;
            }
            case 5:
            {
                SquareMatrix temp(row);
                temp = transpose();
                temp.display();
                break;
            }
            case 6:
            {
                editMatrix();
                cout << "The new matrix:" << endl;
                break;
            }
            case 7:
            {
                double d;
                d = determinant();
                cout << "The determinant of the matrix is " << d <<endl;
                break;
            }
            case 8:
            {
                SquareMatrix r(row);
                r = cofactor();
                r.display();
                break;
            }
            case 9:
            {
                SquareMatrix r(row);
                r = adjoint();
                r.display();
                break;
            }
            case 10:
            {
                SquareMatrix r(row);
                r = inverse();
                r.display();
                break;
            }
            case 11:
            {
                toeplitzDecomposition();
                break;
            }
            case 12:
            {
                Matrix triplet = tripletNotation();
                triplet.display();
                break;
            }
            case 13:
            {
                x=0;
                break;
            }
            default:
            {
                cout << "Invalid choice!" << endl;
            }
        }
    }
}

DiagonalMatrix :: DiagonalMatrix() : SymmetricMatrix(),TriangularMatrix()
{

}

DiagonalMatrix :: DiagonalMatrix(int n) : SymmetricMatrix(n),TriangularMatrix(n)
{

}

void DiagonalMatrix :: editMatrix()
{
    double **temp_pp;
    temp_pp = new double *[row];
    for(int i=0; i<row; i++)
        temp_pp[i] = new double [col];

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            temp_pp[i][j] = pp[i][j];

    Matrix :: editMatrix();

    if(checkDiagonal())
        return;
    else
    {
        for(int i=0; i<row; i++)
            for(int j=0; j<col; j++)
                pp[i][j] = temp_pp[i][j];
        delete temp_pp;
        cout << endl << "Edited matrix is not diagonal matrix..." << endl;
        return;
    }
}

void DiagonalMatrix::operator =(Matrix& m)
{
    row = m.getRow();
    col = m.getColumn();
    pp = m.getMatrix();
}

DiagonalMatrix DiagonalMatrix :: inverse()
{
    DiagonalMatrix res(row);
    for(int i=0,j=0; i<row,j<SymmetricMatrix :: col; i++,j++)
        res.pp[i][j] = 1/pp[i][j];
    return res;
}

void DiagonalMatrix::operations()
{
    int x=1, choice;
    while(x)
    {
        display();
        cout << "Available operations: " << endl;
        cout << "1. Add\n2. Subtract\n3. Scalar Multiplication\n4. Multiplication\n5. Transpose\n6. Edit Matrix\n7.Determinant\n8. Cofactor Matrix\n9. Adjoint Matrix\n10. Inverse Matrix\n11. Teoplitz Decomposition\n12. Sparse matrix to triplet notation\n13. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this + temp;
                temp.display();
                break;
            }
            case 2:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this - temp;
                temp.display();
                break;
            }
            case 3:
            {
                Matrix temp(row, col);
                double n;
                cout << "Enter a scalar to multiply: ";
                cin >> n;
                temp = scalarMultiplication(n);
                temp.display();
                break;
            }
            case 4:
            {
                int n;
                cout << "The order of the matrix must be " << col << " x " << "?" << endl;
                cout << "Column: ";
                cin >> n;
                Matrix temp(col, n);
                temp.read();
                temp = *this * temp;
                temp.display();
                break;
            }
            case 5:
            {
                SquareMatrix temp(row);
                temp = transpose();
                temp.display();
                break;
            }
            case 6:
            {
                editMatrix();
                cout << "The new matrix:" << endl;
                break;
            }
            case 7:
            {
                double d;
                d = determinant();
                cout << "The determinant of the matrix is " << d <<endl;
                break;
            }
            case 8:
            {
                SquareMatrix r(row);
                r = cofactor();
                r.display();
                break;
            }
            case 9:
            {
                SquareMatrix r(row);
                r = adjoint();
                r.display();
                break;
            }
            case 10:
            {
                SquareMatrix r(row);
                r = inverse();
                r.display();
                break;
            }
            case 11:
            {
                toeplitzDecomposition();
                break;
            }
            case 12:
            {
                Matrix triplet = tripletNotation();
                triplet.display();
                break;
            }
            case 13:
            {
                x=0;
                break;
            }
            default:
            {
                cout << "Invalid choice!" << endl;
            }
        }
    }
}
