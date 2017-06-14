#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "mex.h"
#include "ddm.hpp"
#include "ddmio.hpp"

#include <arageli/arageli.hpp>

using namespace Arageli;

void print_banner()
{
  std::cout << "                                                                         \n";          
  std::cout << "  &&&&&&&    &&                  &&             &&                       \n";          
  std::cout << " &&&   &&&   &&                  &&             &&                       \n";          
  std::cout << " &&&         &&   &&   &&&&&&&   &&   &&&&&&&  &&&&   &&&&&&   &&&&&&&   \n";          
  std::cout << "  &&&&&&&&   &&  &&   &&     &&  &&  &&     &&  &&   &&    &&  &&    &&  \n";          
  std::cout << "        &&&  &&&&&    &&&&&&&&&  &&  &&&&&&&&&  &&   &&    &&  &&    &&  \n";          
  std::cout << " &&     &&&  &&  &&   &&&        &&  &&&        &&   &&    &&  &&    &&  \n";          
  std::cout << "  &&&&&&&&   &&   &&   &&&&&&&   &&   &&&&&&&    &&&  &&&&&&   &&    &&  \n";          
  std::cout << "                                                                         \n";          
  std::cout << "                                                                         \n";          
  std::cout << "                         by Nikolai Yu. Zolotykh                         \n";          
  std::cout << "                                                                         \n";          
  std::cout << "    A lot of help and suggestions from Sergey Lobanov & Sergey Lyalin    \n";          
  std::cout << "                                                                         \n";          
  std::cout << "                  http://www.uic.nnov.ru/~zny/skeleton                   \n";          
  std::cout << "                Skeleton on-line: http://www.arageli.org                 \n";          
  std::cout << "                                                                         \n";          
}


/*
template <class T>
void matrix2array(T* Arr, matrix<T>& Matr)
{
    T* p = Arr; 

    for(matrix<T>::iterator i = Matr.begin(); i != Matr.end(); ++i)
    {
        *(p++) = *i;
    }
}
*/

template <typename T, typename D>
void matrix2array(const matrix<T>& Matr, D* Arr)
{
    size_t m = Matr.nrows();
    size_t n = Matr.ncols();

    D* p = Arr; 

    for (size_t j = 0; j < n; j++)
        for (size_t i = 0; i < m; i++)
            *(p++) = Matr(i, j);
}

template <typename T>
void array2matrix(T* Arr, matrix<T>& Matr)
{
    size_t m = Matr.nrows();
    size_t n = Matr.ncols();

    T* p = Arr; 

    for (size_t j = 0; j < n; j++)
        for (size_t i = 0; i < m; i++)
            Matr(i, j) = *(p++);
}

void mexFunction(int nOut, mxArray *pOut[], int nIn, const mxArray *pIn[])
{
    if (nIn < 1)
    {
        print_banner();
        return;
    }
    
    if (!mxIsDouble(pIn[0]) || mxIsComplex(pIn[0]) || mxGetNumberOfDimensions(pIn[0]) > 2)
        mexErrMsgTxt("Input must be real matrix, double precision");
    
    int m = mxGetM(pIn[0]);
    int n = mxGetN(pIn[0]);
    matrix<double> ine(m, n);
    array2matrix(mxGetPr(pIn[0]), ine);

    matrix<double> equ(0, n);
    if (nIn > 1 && !mxIsEmpty(pIn[1]))
    {
        if (!mxIsDouble(pIn[1]) || mxIsComplex(pIn[1]) || mxGetNumberOfDimensions(pIn[1]) > 2)
            mexErrMsgTxt("Input must be real matrix, double precision");
        int k = mxGetM(pIn[1]);
        int n2 = mxGetN(pIn[1]);
        if (m == 0 || n == 0)
            ine.resize(0, n2);
        else 
            if (n != n2)
                mexErrMsgTxt("The numbers of columns in matrices are different");
        equ.resize(k, n2);
        array2matrix(mxGetPr(pIn[1]), equ);
    }

    matrix<double> ext, bas, dis;
    matrix<size_t> edges_ind;
    INT64 totalnumrays, totalnumedges;

    int edgesflag = 0;
    int order = DDM_MIN_INDEX;
    int prefixed_order = 1;
    int graphadj = 1;
    int plusplus = 1;
    double zero_tol = 1e-8; 

    if (nIn > 2 && !mxIsEmpty(pIn[2]))
        edgesflag = *mxGetPr(pIn[2]);

    if (nIn > 3 && !mxIsEmpty(pIn[3]))
        order = *mxGetPr(pIn[3]);

    if (nIn > 4 && !mxIsEmpty(pIn[4]))
        prefixed_order = *mxGetPr(pIn[4]);

    if (nIn > 5 && !mxIsEmpty(pIn[5]))
        graphadj = *mxGetPr(pIn[5]);

    if (nIn > 6 && !mxIsEmpty(pIn[6]))
        plusplus = *mxGetPr(pIn[6]);

    if (nIn > 7 && !mxIsEmpty(pIn[7]))
        zero_tol = *mxGetPr(pIn[7]);


    int intarith = 0;
    int logonstdout = 0;
    int logfileflag = 0;
    std::ofstream logfile;

    /*----------------------------------------------------------*/

    /*----------------------------------------------------------*/

//std::cout << "m = " << ine.nrows() << "n = " << ine.ncols() << " ine = " << ine << "\n";
//std::cout << "equ = " << equ << "\n";

    ddm(ine, equ, ext, bas, dis, edges_ind, totalnumrays, totalnumedges, 
        edgesflag, order, prefixed_order, graphadj, plusplus, intarith, zero_tol,                               
        logonstdout, logfileflag, logfile);                                                            

//std::cout << totalnumrays << "\n";
//std::cout << totalnumedges << "\n";
//std::cout << dis;

    /*----------------------------------------------------------*/

    pOut[0] = mxCreateDoubleMatrix(ext.nrows(), ext.ncols(), mxREAL);
    matrix2array(ext, mxGetPr(pOut[0]));
    
    if (nOut > 1)
    {
        pOut[1] = mxCreateDoubleMatrix(bas.nrows(), bas.ncols(), mxREAL);
        matrix2array(bas, mxGetPr(pOut[1]));
    }
    if (nOut > 2)
    {
        pOut[2] = mxCreateDoubleMatrix(dis.nrows(), dis.ncols(), mxREAL);
        matrix2array(dis, mxGetPr(pOut[2]));
    }
    if (nOut > 3)
    {
        pOut[3] = mxCreateDoubleMatrix(edges_ind.nrows(), edges_ind.ncols(), mxREAL);
        matrix2array(edges_ind + 1, mxGetPr(pOut[3]));
    }
    if (nOut > 4)
    {
        pOut[4] = mxCreateDoubleScalar(totalnumrays);
    }
    if (nOut > 5)
    {
        pOut[5] = mxCreateDoubleScalar(totalnumedges);
    }
    
}