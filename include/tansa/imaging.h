#ifndef TANSA_IMAGING_H_
#define TANSA_IMAGING_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

namespace tansa {


enum ImageFormat {
	ImageGrayscale,
	ImageRGB
};

enum ImageOutputFormat {
	ImageJPEG
};

struct ImageSubRegion {
	unsigned offset; /**< Start pixel offset of very beginning of this region */
	unsigned start; /**< Start pixel index relative to 'offset' of the first pixel which should be processed */
	unsigned size; /**< Relative to offset, this is the total number of pixels in this part of the image */
};


// A grayscale image
struct Image {
	unsigned width;
	unsigned height;
	uint8_t depth; /**< Number of bytes per pixel */
	uint8_t *data;

	void copyTo(Image *other) {
		other->data = (uint8_t *) malloc(width*height);
		memcpy(other->data, this->data, width*height);
		other->width = width;
		other->height = height;
	}

	ImageSubRegion all() {
		ImageSubRegion r;
		r.offset = 0;
		r.start = 0;
		r.size = width * height;
		return r;
	}






};

struct ImageSize {
	unsigned width;
	unsigned height;
};



}


#endif