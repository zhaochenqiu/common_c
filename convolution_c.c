/* convolution_c.c */

#include "mex.h"
#include "matrix.h"
#include "matlab_math.h"



void mexFunction(int nlhs,mxArray* plhs[],int nrhs,const mxArray* prhs[])
{
	int i,j,q;
	int m,n;

	int ndims;
	const mwSize* dims = NULL;
	
	int sum_tp = 0;
	int sum_value = 0;
	int value = 0;
	int index = 0;

	int template[3][3];
	int tp_row		= 0;
	int tp_column	= 0;

	int img_row		= 0;
	int img_column	= 0;
	int img_byte	= 0;

	int convimg_row		= 0;
	int convimg_column	= 0;
	int convimg_byte	= 0;

	double* tp_data		= NULL;
	double* img_data	= NULL;
	double* convimg_data = NULL;

	if (nrhs != 3)
	{
		printf("Usage: convolution_c(convimage,image,template)\n");
		return;
	}

	
	dims = mxGetDimensions(prhs[0]);
	img_row		= dims[0];
	img_column	= dims[1];
	img_byte	= dims[2];
	img_data		= (double*)mxGetData(prhs[1]);

	
	dims = mxGetDimensions(prhs[1]);
	convimg_row		= dims[0];
	convimg_column	= dims[1];
	convimg_byte	= dims[2];
	convimg_data	= (double*)mxGetData(prhs[0]);

	
	dims = mxGetDimensions(prhs[2]);
	tp_row		= dims[0];
	tp_column	= dims[1];
	tp_data		= (double*)mxGetData(prhs[2]);

	sum_tp = 0;
	for (i = 0;i != tp_row;i ++)
	{
		for (j = 0;j != tp_column;j ++)
		{
			index = IMG_INDEX(i,j,0,tp_row,tp_column,1);
			template[i][j] = tp_data[index];
			sum_tp += template[i][j];
		}
	}

	if (sum_tp == 0)
	{
		printf("please input the correct template \n");
	}

	for (i = 1;i != img_row - 1;i ++)
	{
		for (j = 1;j != img_column - 1;j ++)
		{
			for (q = 0;q != img_byte;q ++)
			{
				sum_value = 0;
				value = 0;
							
				for (m = 0;m != 3;m ++)
				{
					for (n = 0;n != 3;n ++)
					{
						index = IMG_INDEX((int)(i - 1 + m),(int)(j - 1 + n),q,img_row,img_column,img_byte);
						value = img_data[index];
						value *= template[m][n];
						sum_value += value;
					}
				}
				

				index = IMG_INDEX(i,j,q,img_row,img_column,img_byte);
				convimg_data[index] = sum_value/sum_tp;
			}
		}
	}
}

