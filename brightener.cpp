#include "brightener.h"

uint8_t brightenPixel(const uint8_t inputPixel, const uint8_t brighteningGrayscale, int& attenuatedPixelCount) {
    uint8_t brightened = inputPixel;
    if (int(inputPixel) + brighteningGrayscale > 255) {
        ++attenuatedPixelCount;
        brightened = 255;
    }
    else {
        brightened += brighteningGrayscale;
    }
    return brightened;
}

shared_ptr<BrightenedImage> BrightenWholeImage(const shared_ptr<const RawImage>& inputRawImage, int& attenuatedPixelCount) {
    // For brightening, we add a certain grayscale (25) to every pixel.
    // While brightening, some pixels may cross the max brightness. They are
    // called 'attenuated' pixels
    attenuatedPixelCount = 0;
    auto brightenedImage = 
        make_shared<BrightenedImage>(inputRawImage->m_rows, inputRawImage->m_columns,
            [inputRawImage, &attenuatedPixelCount](uint8_t* initPixels) 
            {
            for (int x = 0; x < inputRawImage->m_rows; x++) {
                for (int y = 0; y < inputRawImage->m_columns; y++) {
                    int index = inputRawImage->pixelIndex(x, y);
                    initPixels[index] =
                        brightenPixel(inputRawImage->getPixel(x, y), 25, attenuatedPixelCount);
                }
            }
        });
    return brightenedImage;
}

shared_ptr<BrightenedImage> AddBrighteningImage(const shared_ptr<RawImage>& inputRawImage, shared_ptr<RawImage> imageToAdd,
    int& attenuatedPixelCount) {
    // Try converting this into an exception, so callers don't always need to check the returned bool
    // if (imageToAdd->m_rows != m_inputImage->m_rows || imageToAdd->m_columns != m_inputImage->m_columns) {
    //     return false;
    // }
    attenuatedPixelCount = 0;
    auto brightenedImage =
        make_shared<BrightenedImage>(inputRawImage->m_rows, inputRawImage->m_columns,
            [inputRawImage, imageToAdd, &attenuatedPixelCount](uint8_t* initPixels) {
            for (int x = 0; x < inputRawImage->m_rows; x++) {
                for (int y = 0; y < inputRawImage->m_columns; y++) {
                    int index = inputRawImage->pixelIndex(x, y);
                    initPixels[index] =
                        brightenPixel(inputRawImage->getPixel(x, y), imageToAdd->getPixel(x, y), attenuatedPixelCount);
                }
            }
    });
    return brightenedImage;
}
