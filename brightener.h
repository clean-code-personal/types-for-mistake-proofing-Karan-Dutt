#include <cstdint>
#include "image.h"

using namespace std;

shared_ptr<BrightenedImage> BrightenWholeImage(const shared_ptr<const RawImage>& inputImage, int& attenuatedPixelCount);
shared_ptr<BrightenedImage> AddBrighteningImage(const shared_ptr<RawImage>& inputImage, shared_ptr<RawImage> imageToAdd,
    int& attenuatedPixelCount);
