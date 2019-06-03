function [re_im re_mk] = fillImg_fast( im, pt_r, pt_c)

im = double(im);
suim = sum(im,3);

[row_im column_im byte_im] = size(im);

spim = im;
objmk = zeros(row_im, column_im);
objim = zeros(row_im, column_im, byte_im);

jdgmk = zeros(row_im, column_im);

len = row_im*column_im;

stack1 = zeros(len, 2);
stack2 = zeros(len, 2);

iminfo = zeros(1, 3);
ptinfo = zeros(1, 5);

posr = pt_r;
posc = pt_c;


fillFlood(spim, objim, jdgmk, objmk, [posr posc], stack1, stack2, iminfo, ptinfo);


re_im = objim;
re_mk = objmk;



