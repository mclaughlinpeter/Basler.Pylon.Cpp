#ifndef CAMERA_BASLER_H
#define CAMERA_BASLER_H

#include "camerabase.h"

// forward declaration
namespace Pylon
{
    class CInstantCamera;
}

namespace Vision::Cpp
{
    extern "C++"
    {
        class LIB_API CameraBasler : public CameraBase
        {
        public:
            CameraBasler(unsigned int cameraNumber, uint32_t timeoutMs);
            ~CameraBasler();
            std::vector<uint8_t> *GrabImage(uint32_t *width, uint32_t *height) override;

        private:
            Pylon::CInstantCamera *camera;
            const uint32_t _timeoutMs;
        };
    }

} // namespace Vision::Cpp

#endif
