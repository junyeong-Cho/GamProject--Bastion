/*
 * Rudy Castan
 * CS200
 * Fall 2022
 */
#pragma once
#include "mat3.h"
#include "vec2.h"


//NDC 공간을 다루는데 특화되어있는 Class 
//(Device space -> NDC space -> Camera space 순으로 이루어짐)
class [[nodiscard]] CameraView
{
public:

    //Display 크기가 변경될 때 마다 둘 중 하나가 불러짐
    void SetFramebufferSize(vec2 the_framebuffer_size) noexcept;
    void SetFramebufferSize(int new_framebuffer_width, int new_framebuffer_height) noexcept;


    //Getter functions
    vec2 GetViewSize() const;

    [[nodiscard]] float GetZoom() const noexcept
    {
        return zoom;
    }


    //No Zoom == 1, Zoom out == > 1
    void SetZoom(float new_zoom) noexcept;


    vec2 CalcViewSizeWithZoom() const noexcept
    {
        return framebuffer_size / zoom;
    }

    

    mat3 BuildCameraToNDC() const noexcept;

    mat3 BuildWindowDeviceToCamera() const noexcept;

private:
    vec2  framebuffer_size{};
    float zoom{1.0f};
};
