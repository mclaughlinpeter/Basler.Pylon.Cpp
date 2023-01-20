#include "camerabasler.h"

#include <pylon/PylonIncludes.h>

using namespace Pylon;

namespace Vision::Cpp
{
    CameraBasler::CameraBasler(unsigned int cameraNumber, uint32_t timeoutMs) : CameraBase(cameraNumber), _timeoutMs(timeoutMs)
    {
        try
        {
            // before using any pylon methods, the pylon runtime must be initialized
            PylonInitialize();
            camera = new CInstantCamera(CTlFactory::GetInstance().CreateFirstDevice());
        }
        catch (const GenericException &e)
        {
#ifdef VERBOSE
            std::cerr << "An exception occurred." << std::endl
                      << e.GetDescription() << std::endl;
#endif
            throw std::runtime_error("Unable to open camera on initialization -> shutting down");
        }

#ifdef VERBOSE
        std::cout << "Using device " << camera->GetDeviceInfo().GetModelName() << std::endl;
#endif

        // The parameter MaxNumBuffer can be used to control the count of buffers allocated for grabbing. The default value of this parameter is 10.
        camera->MaxNumBuffer = 10;
    }

    CameraBasler::~CameraBasler()
    {
        // releases all pylon resources
        PylonTerminate();
    }

    std::vector<uint8_t> *CameraBasler::GrabImage(uint32_t *width, uint32_t *height)
    {
        try
        {
            // Create a pylon ImageFormatConverter object
            CImageFormatConverter formatConverter;
            formatConverter.OutputPixelFormat = PixelType_Mono8;

            // Create a pylon image
            CPylonImage pylonImage;

            // This smart pointer will receive the grab result data.
            CGrabResultPtr ptrGrabResult;

            // grab a single image and copy to a buffer prior to creating a cv::Mat object
            camera->GrabOne(_timeoutMs, ptrGrabResult, TimeoutHandling_ThrowException);
            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded())
            {
                // Access the image data.
                *width = ptrGrabResult->GetWidth();
                *height = ptrGrabResult->GetHeight();

#ifdef VERBOSE
                std::cout << "SizeX: " << ptrGrabResult->GetWidth() << std::endl;
                std::cout << "SizeY: " << ptrGrabResult->GetHeight() << std::endl;
#endif

                // Convert the grabbed buffer to a pylon image
                formatConverter.Convert(pylonImage, ptrGrabResult);

                size_t imageSizeBytes = pylonImage.GetImageSize();
#ifdef VERBOSE
                std::cout << "Image size in bytes: " << imageSizeBytes << std::endl;
#endif

                return new std::vector<uint8_t>((uint8_t *)pylonImage.GetBuffer(), (uint8_t *)pylonImage.GetBuffer() + imageSizeBytes);
            }
            else
            {
#ifdef VERBOSE
                std::cerr << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << std::endl;
#endif
                return nullptr;
            }
        }
        catch (const GenericException &e)
        {
#ifdef VERBOSE
            std::cerr << "An exception occurred." << std::endl << e.GetDescription() << std::endl;
#endif
            return nullptr;
        }
    }

} // namespace Vision::Cpp

