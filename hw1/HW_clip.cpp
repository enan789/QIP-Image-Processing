// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_clip:
//
// Clip intensities of image I1 to [t1,t2] range. Output is in I2.
// If    input<t1: output = t1;
// If t1<input<t2: output = input;
// If      val>t2: output = t2;
//
// Written by: ADD YOUR NAMES HERE, 2016
//

void
HW_clip(ImagePtr I1, int t1, int t2, ImagePtr I2)
{
	IP_copyImageHeader(I1, I2);
	int w = I1->width ();
	int h = I1->height();
	int total = w * h;

	// init lookup table
	int i, i2, i3, lut[MXGRAY];
	for (i = 0; i < MXGRAY; ++i){
		if (i <= t1){
			lut[i] = t1;
		}
		else if (i>t1 && i < t2){
			lut[i] = i;
		}
		else if (t2 >= i){
			lut[i] = t2;
		}
		
	}

	// evaluate output: each input pixel indexes into lut[] to eval output
	int type;
	ChannelPtr<uchar> p1, p2, endd;
	for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
		IP_getChannel(I2, ch, p2, type);
		for(endd = p1 + total; p1<endd;) *p2++ = lut[*p1++];
	}
}
