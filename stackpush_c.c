/* stackpush_c */

#include "mex.h"
#include "matrix.h"
#include "matlab_math.h"



void mexFunction(int nlhs,mxArray* plhs[],int nrhs, const mxArray* prhs[])
{
	int j;
	int stack_ipos;
	int index_stack;
	int index_entry;
	double tempvalue;

	int ndims;
	const mwSize* dims = NULL;

	int stack_row		= 0;
	int stack_column	= 0;
	double* stack_data	= NULL;

	int entry_row		= 0;
	int entry_column	= 0;
	double* entry_data	= NULL;

	double* pos	= NULL;

	if (nrhs != 3)
	{
		printf("Usage: stackpush_c(stack,pos,entry)\n");
		return;
	}

	dims = mxGetDimensions(prhs[0]);

	stack_row		= dims[0];
	stack_column	= dims[1];
	stack_data		= (double*)mxGetData(prhs[0]);


	dims = mxGetDimensions(prhs[2]);

	entry_row		= dims[0];
	entry_column	= dims[1];
	entry_data		= (double*)mxGetData(prhs[2]);

	if (entry_column != stack_column)
	{
		printf("the column of entry must the same with stack\n");
		return;
	}

	pos = (double*)mxGetData(prhs[1]);
	stack_ipos = (int)pos[0];

	if (stack_ipos == stack_row)
	{
		printf("stack overflow \n");
		return;
	}

	for (j = 0;j != stack_column;j ++)
	{
		index_stack = (int)MATRIX_INDEX(stack_ipos,j,stack_row,stack_column);
		index_entry = (int)MATRIX_INDEX(0,j,1,entry_column);

		tempvalue = (double)entry_data[index_entry];
		stack_data[index_stack] = tempvalue;
	}

	stack_ipos ++;
	pos[0] = (double)stack_ipos;
}
