#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H

#include <cstdint>
#include <vector>

#ifndef LIB_API
#define LIB_API __attribute__((visibility("default")))
#endif

namespace Vision::Cpp
{
    class CameraBase
    {
    protected:
        const unsigned int _cameraNumber;

    public:
        CameraBase(unsigned int cameraNumber) : _cameraNumber(cameraNumber) {}
        virtual std::vector<uint8_t> *GrabImage(uint32_t *width, uint32_t *height) = 0;
    };

} // namespace Vision::Cpp

#endif
