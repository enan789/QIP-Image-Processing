// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_gammaCorrect:
//
// Gamma correct image I1. Output is in I2.
//
// Written by: ADD YOUR NAMES HERE, 2016
//

void
HW_gammaCorrect(ImagePtr I1, double gamma, ImagePtr I2){
	IP_copyImageHeader(I1, I2);
	int w = I1->width();
	int h = I1->height();
	int total = w * h;
	gamma = 1 / gamma;

	// init lookup table
	int i, i2, i3, lut[MXGRAY];
	for (i = 0; i < MXGRAY; ++i) lut[i] = pow(((double)i / 255), gamma) * 255;

	// evaluate output: each input pixel indexes into lut[] to eval output
	int type;
	ChannelPtr<uchar> p1, p2, endd;
	for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
		IP_getChannel(I2, ch, p2, type);
		for (endd = p1 + total; p1<endd;) *p2++ = lut[*p1++];
	}
}
