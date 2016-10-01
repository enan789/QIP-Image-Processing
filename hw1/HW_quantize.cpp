// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_quantize:
//
// Quantize I1 to specified number of levels. Apply dither if flag is set.
// Output is in I2.
//
// Written by: ADD YOUR NAMES HERE, 2016
//

void
HW_quantize(ImagePtr I1, int levels, bool dither, ImagePtr I2)
{
	IP_copyImageHeader(I1, I2);
	int w = I1->width();
	int h = I1->height();
	int total = w * h;

	//The scale show
	int scale = (MXGRAY + 1) / levels;

	// compute lut[]
	int i, j, lut[MXGRAY];
	int type;
	int val, nval, noise;
	double ran1;
	int s = 1;
	ChannelPtr<uchar> p1, p2, endd;

	for (i = 0; i < MaxGray; ++i){
		//given code to create the quantization levels
		lut[i] = (int)CLIP((int)(scale * (i / scale) + (scale / 2)), 0, 255);
		//If dither is true set near black pixels in intervals of 5 and near white pixels in intervals of 10 to be quantized'
	}

	if (!dither){
		for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
			IP_getChannel(I2, ch, p2, type);
			for (endd = p1 + total; p1 < endd;) *p2++ = lut[*p1++];
		}
	}

	else{

		for (int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
			IP_getChannel(I2, ch, p2, type);
			for (i = 0; i < h; i++){
				s *= -1;
				for (j = 0; j < w; j++){
					
					ran1 = (double) rand() / RAND_MAX;
					noise = (ran1* (scale / 2))*s;
					val = *p1++ + noise;
					nval = CLIP(val, 0, 255);
					*p2++ = lut[nval];
					s *= -1;
					

				}
			}
		}

	}
}