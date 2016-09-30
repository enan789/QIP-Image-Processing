// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_histoStretch:
//
// Apply histogram stretching to I1. Output is in I2.
// Stretch intensity values between t1 and t2 to fill the range [0,255].
//
// Written by: ADD YOUR NAMES HERE, 2016
//

void
HW_histoStretch(ImagePtr I1, int t1, int t2, ImagePtr I2)
{
	//Copy the input image to the output and saved the hieght width and total number of pictures
	IP_copyImageHeader(I1, I2);
	int w = I1->width();
	int h = I1->height();
	int total = w * h;

	// compute lut[] that contain the values of 
	int i, a, b, lut[MXGRAY], check[MXGRAY];

	int nMin = t1;
	int nMax = t2;
	//bool cMin = false;
	//bool cMax = false;

	//I tried to implement the auto Min and Max but was not able to finish so I removed this code from the report.
	/*if (aMin || aMax){
	for (a = 0; a < MaxGray; ++a){
	check[a] = a;
	}
	for (b = 0; b < MaxGray; ++a){
	if (check[b] != 0 && aMin && !cMin){
	nMin = check[b];
	cMin = true;
	}
	if (check[MXGRAY - (b + 1)] !=0 && aMax && !cMax){
	nMax = check[MXGRAY - (b + 1)];
	cMax = true;
	}
	}
	}*/

	for (i = 0; i < MaxGray; ++i){
		//subtract the minimum to make the smallest value used 0
		//then multiply this value 255/range of the min an max to set the highes value to the max
		//the values are clipped incase of outliers
		lut[i] = (int)CLIP((255 * (i - t1) / (t2 - t1)), 0, 255);
	}

	//Get the values of the output pointers and and the save the input value changes
	int type;
	ChannelPtr<uchar> p1, p2, endd;
	for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
		IP_getChannel(I2, ch, p2, type);
		for (endd = p1 + total; p1<endd;) *p2++ = lut[*p1++];
	}
}
