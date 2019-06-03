clear all
close all
clc

mex stackpush_c.c
mex stackpop_c.c

len_stack = 100;
len_entry = 2;

stack = zeros(len_stack,len_entry);
stack_pos = 0;

entry = [1 1];
test = [2 1];


stackpush_c(stack,stack_pos,entry);

stack(1,1)
stack(1,2)

stack_pos

stackpush_c(stack,stack_pos,test);

stack_pos

stack(2,1)
stack(2,2)

% overflow test
for i = 1:200
	entry = [i 2*i];
	stackpush_c(stack,stack_pos,entry);

	stack_pos
end


result = [1 1];

for i = 1:200
	stackpop_c(stack,stack_pos,result);

	[result stack_pos]
end



