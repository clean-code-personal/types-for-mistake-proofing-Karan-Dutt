#include <iostream>
#include "brightener.h"

void StoreImageAnalytics(std::shared_ptr<RawImage> rawImage) {
	// This function will store the raw (non-brightened) image for analytics
	// Here we're just pretending :)
	std::cout << "- Storing the raw image for analytics\n";
}

int main() {
	const auto rawImage = std::make_shared<RawImage>(512, 512, [](uint8_t* pixels) {});
	std::cout << "Brightening a 512 x 512 image\n";
	int attenuatedPixelCount = 0;
	auto brightenedImage = BrightenWholeImage(rawImage, attenuatedPixelCount);
	std::cout << "Attenuated " << attenuatedPixelCount << " pixels\n";

	// Oops, mistake! This is passing the brightened image instead of raw.
	// Can you make this mistake show up at compile-time?
	StoreImageAnalytics(rawImage);
}
