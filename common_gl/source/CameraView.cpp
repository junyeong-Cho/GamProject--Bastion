#include "CameraView.h"

void CameraView::SetFramebufferSize(vec2 the_framebuffer_size) noexcept
{
	framebuffer_size = the_framebuffer_size;
}

void CameraView::SetFramebufferSize(int new_framebuffer_width, int new_framebuffer_height) noexcept
{
	SetFramebufferSize(vec2{ float(new_framebuffer_width), float(new_framebuffer_height) });
}

vec2 CameraView::GetViewSize() const
{
	return framebuffer_size / zoom;
}

void CameraView::SetZoom(float new_zoom) noexcept
{
	// if new zoom is not 0
		// save as zoom
	assert(new_zoom != 0); 
	zoom = new_zoom;

}

mat3 CameraView::BuildCameraToNDC() const noexcept
{
    //         (v.w/2,v.h/2)              (1,1)
	//      +--------o             +--------o
	//      |        |             |        |
	//      | cam    |     --->    | ndc    |
	//      o--------+             o--------+
	// (-v.w/2,-v.h/2)          (-1,-1)
	//

	// get view size with zoom
	// build and return camera to NDC matrix

	vec2 viewSize = GetViewSize();

	float Sx = 2.0f / viewSize.x;
	float Sy = 2.0f / viewSize.y;
	float Tx = -1.0f;
	float Ty = -1.0f;

	return mat3
	{
		Sx,   0.0f,  Tx,
		0.0f,   Sy,  Ty,
		0.0f, 0.0f, 1.0f
	};
}

mat3 CameraView::BuildWindowDeviceToCamera() const noexcept
{
	//    (0,0)             (-v.w/2,v.h/2)
	//      o--------+             o--------+
	//      |        |             |        |
	//      | win    |     --->    | cam    |
	//      +--------o             +--------o
	//           (f.w,f.h)            (v.w/2,-v.h/2)
	//

	// get view size with zoom
	// build and return window to camera matrix

	vec2 viewSize = GetViewSize();

	float Sx = viewSize.x / framebuffer_size.x;
	float Sy = -viewSize.y / framebuffer_size.y;
	float Tx = -viewSize.x / 2.0f;
	float Ty = viewSize.y / 2.0f;

	return mat3
	{
		Sx,   0.0f,  Tx,
		0.0f,   Sy,  Ty,
		0.0f, 0.0f, 1.0f
	};

}
