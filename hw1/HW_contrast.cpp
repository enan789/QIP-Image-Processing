// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_contrast:
//
// Apply contrast enhancement to I1. Output is in I2.
// Stretch intensity difference from reference value (128) by multiplying
// difference by "contrast" and adding it back to 128. Shift result by
// adding "brightness" value.
//
// Written by: ADD YOUR NAMES HERE, 2016
//
void
HW_contrast(ImagePtr I1, double brightness, double contrast, ImagePtr I2)
{
	//copy the input image to the output and save hieght, width, and total number of pixels
	IP_copyImageHeader(I1, I2);
	int w = I1->width();
	int h = I1->height();
	int total = w * h;

	//create a reference to the middle value of the pixels
	int reference = 128;
	double slope;
	//if the contrast is set so that if the if zero the contr value is 1 at 0 and 5 at 100 and goes between this  if the value is >=0.
	//But if the value is less than zero the value should go between close to zero and 1 which works with the following equation
	if (contrast >= 0){
		slope = contrast / 25 + 1;
	}
	else{
		slope = contrast / 133 + 1;
	}
	// compute lut[]
	int i, lut[MXGRAY];
	for (i = 0; i < MXGRAY; ++i) {
		//the distance of th contrast is found by subtracting it by middle value and can be used to imagine an x value.
		//the contrast acts as a slope and the brightness as a constant.
		//the end to brighten the image by being closer to white. CLIP makes sure if they past 0 or 255 they will be set to them
		lut[i] = CLIP((i - reference)*slope + reference + brightness, 0, 255);
	}
	
	int type;
	ChannelPtr<uchar> p1, p2, endd;
	for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
		IP_getChannel(I2, ch, p2, type);
		for (endd = p1 + total; p1<endd;) *p2++ = lut[*p1++];
	}
}
