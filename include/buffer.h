
#ifndef __BUFFER_H__
#define __BUFFER_H__ 1

#include "platform_types.h"
#include <cstring>

template<class T>
class Buffer {

public:

				Buffer(s32 mWidth, s32 mHeight, T* mArray) : width(mWidth), height(mHeight), 
								pitch(mWidth * sizeof(T)), buffer(mArray), pixelCount(mWidth* mHeight) {};

				~Buffer() { delete[] buffer; };

				inline void Clear(const u8 color) {
								memset(buffer, color, pitch * height);
				}

				inline T& operator()(size_t x, size_t y) {
								return buffer[y * width + x];
				}


				T *buffer;
				s32 width;
				s32 height;
				s32 pitch;
				u32 pixelCount;
				
};

#endif