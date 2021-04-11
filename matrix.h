#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

class Matrix
{
    protected:
        int row,col;
        double **pp;

    public:
        Matrix();
        Matrix(int,int);

        void setDimension(int,int);
        void read();
        void display() const;

        bool checkSquare();
        bool checkSymmetric();
        bool checkTriangular();
        bool checkDiagonal();
        bool operator ==(Matrix);

        Matrix operator +(Matrix);
        Matrix operator -(Matrix);
        Matrix operator *(Matrix);
        Matrix transpose();
        Matrix scalarMultiplication(double);
        Matrix tripletNotation();
        void editMatrix();

        int getRow();
        int getColumn();
        double ** getMatrix();

        void operations();

        //~Matrix();
};

class SquareMatrix : public Matrix
{
    public:
        SquareMatrix();
        SquareMatrix(int);
        void operator =(Matrix&);

        double determinant();
        SquareMatrix cofactor();
        SquareMatrix adjoint();
        SquareMatrix inverse();
        SquareMatrix transpose();

        void toeplitzDecomposition();

        void operations();
};

class SymmetricMatrix : virtual public SquareMatrix
{
    public:
        SymmetricMatrix();
        SymmetricMatrix(int);
        SymmetricMatrix transpose();
        void operator =(Matrix&);

        void operations();
        void editMatrix();
};

class TriangularMatrix : virtual public SquareMatrix
{
    public:
        TriangularMatrix();
        TriangularMatrix(int);
        double determinant();
        void operator =(Matrix&);

        void operations();
        void editMatrix();
};

class DiagonalMatrix : public SymmetricMatrix, public TriangularMatrix
{
    public:
        DiagonalMatrix();
        DiagonalMatrix(int);
        DiagonalMatrix inverse();
        void operator =(Matrix&);

        void operations();
        void editMatrix();

};

#endif // MATRIX_H_INCLUDED
