#include "CppUnitTest.h"
#include "../brightener.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace brighteningtest
{
	TEST_CLASS(BrighteningTest)
	{
	public:
		
		TEST_METHOD(BrightensWholeImage)
		{
			const auto rawImage = CreateImage(45, 55, 65, 254);
			int attenuatedPixelCount = 0;
			const auto brightenedImage = BrightenWholeImage(rawImage, attenuatedPixelCount);
			Assert::AreEqual(1, attenuatedPixelCount);
			Assert::AreEqual(90, int(brightenedImage->getPixel(1, 0)));
		}

		TEST_METHOD(BrightensWithAnotherImage)
		{
			const auto rawImage = CreateImage(45, 55, 65, 75);
			int attenuatedPixelCount = 0;
			const auto brightenedImage = AddBrighteningImage(
				rawImage, CreateImage(0, 25, 0, 25), attenuatedPixelCount);
            Assert::AreEqual(45, int(brightenedImage->getPixel(0, 0))); // left-side pixel is unchanged
            Assert::AreEqual(80, int(brightenedImage->getPixel(0, 1))); // right-side pixel is brightened
            Assert::AreEqual(0, attenuatedPixelCount);
		}
		shared_ptr<RawImage> CreateImage(uint8_t topLeft, uint8_t topRight, uint8_t bottomLeft, uint8_t bottomRight) {
			return make_shared<RawImage>(2, 2, [=](uint8_t* pixels) {
				pixels[0] = topLeft; pixels[1] = topRight;
				pixels[2] = bottomLeft; pixels[3] = bottomRight;
				});
		}
	};
}
