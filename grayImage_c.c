/* grayImage_c.c */

#include "mex.h"
#include "matrix.h"
#include "matlab_math.h"

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	int i,j,q;

	int ndims;
	const mwSize* dims;

	int img_row		= 0;
	int img_column	= 0;
	int img_byte	= 0;

	int red		= 0;
	int green	= 0;
	int blue	= 0;
	int gray	= 0;

	float list[3] = {0.299f, 0.587f, 0.114f};

	int index_r = 0;
	int index_g = 0;
	int index_b = 0;

	double* img_data = NULL;

	ndims	= mxGetNumberOfDimensions(prhs[0]);
	dims	= mxGetDimensions(prhs[0]);

	img_data = (double*)mxGetData(prhs[0]);
	
	if (ndims != 3)
	{
		printf("pleas input the rgb image");
	}

	img_row		= dims[0];
	img_column	= dims[1];
	img_byte	= dims[2];

	for (i = 0;i != img_row;i ++)
	{
		for (j = 0;j != img_column;j ++)
		{
			index_r = IMG_INDEX(i,j,0,img_row,img_column,img_byte);
			red		= img_data[index_r];

			index_g = IMG_INDEX(i,j,1,img_row,img_column,img_byte);
			green	= img_data[index_g];

			index_b = IMG_INDEX(i,j,2,img_row,img_column,img_byte);
			blue	= img_data[index_b];

			gray = red*list[0] + green*list[1] + blue*list[2];

			img_data[index_r] = gray;
			img_data[index_g] = gray;
			img_data[index_b] = gray;	
		}
	}
}
