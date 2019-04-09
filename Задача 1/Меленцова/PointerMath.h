#pragma once

#include <cstdint>
typedef uint8_t  u8;
typedef uintptr_t uptr;

//Declarations
namespace pointer_math
{
	u8          alignForwardAdjustment(const void* address, u8 alignment);
	u8          alignForwardAdjustmentWithHeader(const void* address, u8 alignment, u8 header_size);

	void*       add(void* p, size_t x);
	const void* add(const void* p, size_t x);

	void*       subtract(void* p, size_t x);
	const void* subtract(const void* p, size_t x);
}

//Inline Definitions
namespace pointer_math
{
	inline u8 alignForwardAdjustment(const void* address, u8 alignment)
	{
		u8 adjustment = alignment - (reinterpret_cast<uptr>(address)& static_cast<uptr>(alignment - 1));

		if (adjustment == alignment)
			return 0; //already aligned

		return adjustment;
	}

	inline u8 alignForwardAdjustmentWithHeader(const void* address, u8 alignment, u8 header_size)
	{
		u8 adjustment = alignForwardAdjustment(address, alignment);
		u8 needed_space = header_size;
		if(adjustment < needed_space)
		{
			needed_space -= adjustment;
			//Increase adjustment to fit header
			adjustment += alignment * (needed_space / alignment);
			if(needed_space % alignment > 0)
				adjustment += alignment;
		}
		return adjustment;
	}

	inline void* add(void* p, size_t x)
	{
		return (void*)(reinterpret_cast<uptr>(p) + x);
	}

	inline const void* add(const void* p, size_t x)
	{
		return (const void*)(reinterpret_cast<uptr>(p) + x);
	}

	inline void* subtract(void* p, size_t x)
	{
		return (void*)(reinterpret_cast<uptr>(p) - x);
	}

	inline const void* subtract(const void* p, size_t x)
	{
		return (const void*)(reinterpret_cast<uptr>(p) - x);
	}
}
