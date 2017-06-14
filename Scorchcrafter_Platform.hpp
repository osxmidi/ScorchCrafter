#ifndef SCORCHCRAFTER_PLATFORM_DEFS_CPP_INC
#define SCORCHCRAFTER_PLATFORM_DEFS_CPP_INC

#include <cinttypes>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <sys/types.h>
#include <cstddef>
#include <climits>
#include <string>

namespace ScorchCrafter
{
	namespace DataTypes
	{
	#ifndef SCORCHCRAFTER_DATA_TYPES_DEFINED
	#define SCORCHCRAFTER_DATA_TYPES_DEFINED

		using namespace std;

		// Floating-point types
		// Note: Depending on the compiler, control word settings, and command-line options, "long double" can potentially
		//     be a number of different bits in size when it comes to precision, typically it will be 80 or 128
		//     but in some cases can even be 64 or even 32 or something else!
		typedef float f32;
		typedef double f64;
		typedef long double f80;		// Extended-bit floating-point type, please don't use this too often for real-time running operations
	#ifdef _GLIBCXX_USE_FLOAT128
		typedef __float128 f128;		// 128-bit floating-point type, please don't use this (ever) for real-time running operations, and other times only if it is REALLY needed and practical
	#else
		typedef long double f128;		// 128-bit (or something hopefully greater than 64 bits) floating-point type, please don't use this (ever) for real-time running operations, and other times only if it is REALLY needed and practical
	#endif // _GLIBCXX_USE_FLOAT128

		// Integer types
	#if(__cplusplus >= 201103L) // C++11 support
		typedef int8_t s8;
		typedef int16_t s16;
		typedef int32_t s32;
		typedef int64_t s64;

		typedef uint8_t u8;
		typedef uint16_t u16;
		typedef uint32_t u32;
		typedef uint64_t u64;
	#else
		typedef signed __int8 s8;
		typedef signed __int16 s16;
		typedef signed __int32 s32;
		typedef signed __int64 s64;

		typedef unsigned __int8 u8;
		typedef unsigned __int16 u16;
		typedef unsigned __int32 u32;
		typedef unsigned __int64 u64;
	#endif // C++11 support

		// A few math constants
		static const f32 SCRFT_e_f32 = (f32) 2.71828182845904523536028747135266249775724709369995f;
		static const f64 SCRFT_e_f64 = (f64) 2.71828182845904523536028747135266249775724709369995;
		static const f80 SCRFT_e_f80 = (f80) 2.71828182845904523536028747135266249775724709369995L;

		static const f32 SCRFT_pi_f32 = (f32) 3.14159265358979323846264338327950288419716939937510f;
		static const f64 SCRFT_pi_f64 = (f64) 3.14159265358979323846264338327950288419716939937510;
		static const f80 SCRFT_pi_f80 = (f80) 3.14159265358979323846264338327950288419716939937510L;

		static const f32 SCRFT_dn_f32 = f32 ( (f80) powl( (f80) 10.L, (f80) -24.L ) );
		static const f64 SCRFT_dn_f64 = f64 ( (f80) powl( (f80) 10.L, (f80) -30.L ) );
		static const f80 SCRFT_dn_f80 = f80 ( (f80) powl( (f80) 10.L, (f80) -30.L ) );

		enum Scft_Bool
		{
			Scft_FALSE = 0u,
			Scft_TRUE = 1u
		};

	#endif // ifndef SCORCHCRAFTER_DATA_TYPES_DEFINED

		#ifdef SCRFT_RESTRICT
		#	undef SCRFT_RESTRICT
		#endif // SCRFT_RESTRICT

		#ifdef SCRFT_RESTRICT_PTR
		#	undef SCRFT_RESTRICT_PTR
		#endif // SCRFT_RESTRICT_PTR

		#ifdef SCRFT_RESTRICT_REF
		#	undef SCRFT_RESTRICT_REF
		#endif // SCRFT_RESTRICT_REF

		#ifdef SCRFT_EXPORT
		#	undef SCRFT_EXPORT
		#endif // SCRFT_EXPORT

		#define SCRFT_RESTRICT __restrict__
		#define SCRFT_RESTRICT_PTR *__restrict__
		#define SCRFT_RESTRICT_REF &__restrict__

	#ifdef SCRFT_STATIC
		#define SCRFT_EXPORT __attribute__ ((visibility ("default")))
		#define SCRFT_IMPORT __attribute__ ((visibility ("default")))
	#else
		#define SCRFT_EXPORT __attribute__ ((dllexport))
		#define SCRFT_IMPORT __attribute__ ((dllimport))
	#endif // SCRFT_STATIC

	#if(__cplusplus >= 201103L) // C++11 support

		constexpr Scft_Bool operator!(const Scft_Bool &other)
		{
			return ( (other == Scft_FALSE) ? Scft_TRUE : Scft_FALSE );
		}

	// f64 functions
		constexpr f64 scft_Abs64(const f64 &inp)
		{
			return f64 ( (inp >= 0.0) ? inp : -inp );
		}

		constexpr f64 scft_Min64(const f64 SCRFT_RESTRICT_REF inp_a, const f64 SCRFT_RESTRICT_REF inp_b)
		{
			return f64 ( (inp_a < inp_b) ? inp_a : inp_b );
		}
		constexpr f64 scft_Max64(const f64 SCRFT_RESTRICT_REF inp_a, const f64 SCRFT_RESTRICT_REF inp_b)
		{
			return f64 ( (inp_a > inp_b) ? inp_a : inp_b );
		}
		constexpr f64 scft_Clamp64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF inp_min, const f64 SCRFT_RESTRICT_REF inp_max)
		{
			return f64 (	(inp > inp_max) ?
								inp_max
							:
								( (inp < inp_min) ?
									inp_min
								:
									inp ) );
		}

		constexpr f64 scft_Avg64(const f64 SCRFT_RESTRICT_REF inp_a, const f64 SCRFT_RESTRICT_REF inp_b, const f64 SCRFT_RESTRICT_REF skew_toward_b)
		{
			return f64 (	(inp_a * (1.0 - skew_toward_b)) +
							(inp_b * skew_toward_b) );
		}

		constexpr f64 scft_ExpFx64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF fac)
		{
			return f64 (	(inp >=  0.0) ?
								( 1.0 - pow( fac, -inp ))
							:
								(-1.0 + pow( fac,  inp )) );
		}
		constexpr f64 scft_ExpFxA64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF fac)
		{
			return f64 (	(inp >=  0.0) ?
								( 1.0 - pow( fac, -inp ))
							:
								( 1.0 - pow( fac,  inp )) );
		}

		constexpr f64 scft_PowFx64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF fac)
		{
					return f64 (	(inp <= -1.0) ?
										-1.0
									:
									(inp >=  1.0) ?
										1.0
									:
									(inp >=  0.0) ?
										( 1.0 - pow( 1.0 - inp, fac ))
									:
										(-1.0 + pow( 1.0 + inp, fac ))	);
		}
		constexpr f64 scft_PowFxA64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF fac)
		{
					return f64 (	(inp <= -1.0) ?
										1.0
									:
									(inp >=  1.0) ?
										1.0
									:
									(inp >=  0.0) ?
										(1.0 - pow( 1.0 - inp, fac ))
									:
										(1.0 - pow( 1.0 + inp, fac ))	);
		}

	// f80 functions
		constexpr f80 scft_Abs80(const f80 &inp)
		{
			return f80 ( (inp >= 0.0L) ? inp : -inp );
		}

		constexpr f80 scft_Min80(const f80 SCRFT_RESTRICT_REF inp_a, const f80 SCRFT_RESTRICT_REF inp_b)
		{
			return f80 ( (inp_a < inp_b) ? inp_a : inp_b );
		}
		constexpr f80 scft_Max80(const f80 SCRFT_RESTRICT_REF inp_a, const f80 SCRFT_RESTRICT_REF inp_b)
		{
			return f80 ( (inp_a > inp_b) ? inp_a : inp_b );
		}
		constexpr f80 scft_Clamp80(const f80 SCRFT_RESTRICT_REF inp, const f80 SCRFT_RESTRICT_REF inp_min, const f80 SCRFT_RESTRICT_REF inp_max)
		{
			return f80 (	(inp > inp_max) ?
								inp_max
							:
								( (inp < inp_min) ?
									inp_min
								:
									inp ) );
		}

		constexpr f80 scft_Avg80(const f80 SCRFT_RESTRICT_REF inp_a, const f80 SCRFT_RESTRICT_REF inp_b, const f80 SCRFT_RESTRICT_REF skew_toward_b)
		{
			return f80 (	(inp_a * (1.0L - skew_toward_b)) +
							(inp_b * skew_toward_b) );
		}

	#else // C++11 support

		inline Scft_Bool operator!(const Scft_Bool &other)
		{
			return ( (other == Scft_FALSE) ? Scft_TRUE : Scft_FALSE );
		}

	// f64 functions
		inline f64 scft_Abs64(const f64 &inp) const
		{
			return f64 ( (inp >= 0.0) ? inp : -inp );
		}

		inline f64 scft_Min64(const f64 SCRFT_RESTRICT_REF inp_a, const f64 SCRFT_RESTRICT_REF inp_b) const
		{
			return f64 ( (inp_a < inp_b) ? inp_a : inp_b );
		}
		inline f64 scft_Max64(const f64 SCRFT_RESTRICT_REF inp_a, const f64 SCRFT_RESTRICT_REF inp_b) const
		{
			return f64 ( (inp_a > inp_b) ? inp_a : inp_b );
		}
		inline f64 scft_Clamp64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF inp_min, const f64 SCRFT_RESTRICT_REF inp_max) const
		{
			return f64 (	(inp > inp_max) ?
								inp_max
							:
								( (inp < inp_min) ?
									inp_min
								:
									inp ) );
		}

		inline f64 scft_Avg64(const f64 SCRFT_RESTRICT_REF inp_a, const f64 SCRFT_RESTRICT_REF inp_b, const f64 SCRFT_RESTRICT_REF skew_toward_b) const
		{
			return f64 (	(inp_a * (1.0 - skew_toward_b)) +
							(inp_b * skew_toward_b) );
		}

		inline f64 scft_ExpFx64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF fac) const
		{
			return f64 (	(inp >=  0.0) ?
								( 1.0 - pow( fac, -inp ))
							:
								(-1.0 + pow( fac,  inp )) );
		}
		inline f64 scft_ExpFxA64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF fac) const
		{
			return f64 (	(inp >=  0.0) ?
								( 1.0 - pow( fac, -inp ))
							:
								( 1.0 - pow( fac,  inp )) );
		}

		inline f64 scft_PowFx64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF fac) const
		{
					return f64 (	(inp <= -1.0) ?
										-1.0
									:
									(inp >=  1.0) ?
										1.0
									:
									(inp >=  0.0) ?
										( 1.0 - pow( 1.0 - inp, fac ))
									:
										(-1.0 + pow( 1.0 + inp, fac ))	);
		}
		inline f64 scft_PowFxA64(const f64 SCRFT_RESTRICT_REF inp, const f64 SCRFT_RESTRICT_REF fac) const
		{
					return f64 (	(inp <= -1.0) ?
										1.0
									:
									(inp >=  1.0) ?
										1.0
									:
									(inp >=  0.0) ?
										(1.0 - pow( 1.0 - inp, fac ))
									:
										(1.0 - pow( 1.0 + inp, fac ))	);
		}

	// f80 functions
		inline f80 scft_Abs80(const f80 &inp) const
		{
			return f80 ( (inp >= 0.0L) ? inp : -inp );
		}

		inline f80 scft_Min80(const f80 SCRFT_RESTRICT_REF inp_a, const f80 SCRFT_RESTRICT_REF inp_b) const
		{
			return f80 ( (inp_a < inp_b) ? inp_a : inp_b );
		}
		inline f80 scft_Max80(const f80 SCRFT_RESTRICT_REF inp_a, const f80 SCRFT_RESTRICT_REF inp_b) const
		{
			return f80 ( (inp_a > inp_b) ? inp_a : inp_b );
		}
		inline f80 scft_Clamp80(const f80 SCRFT_RESTRICT_REF inp, const f80 SCRFT_RESTRICT_REF inp_min, const f80 SCRFT_RESTRICT_REF inp_max) const
		{
			return f80 (	(inp > inp_max) ?
								inp_max
							:
								( (inp < inp_min) ?
									inp_min
								:
									inp ) );
		}

		inline f80 scft_Avg80(const f80 SCRFT_RESTRICT_REF inp_a, const f80 SCRFT_RESTRICT_REF inp_b, const f80 SCRFT_RESTRICT_REF skew_toward_b) const
		{
			return f80 (	(inp_a * (1.0L - skew_toward_b)) +
							(inp_b * skew_toward_b) );
		}

	#endif // C++11 support

	} // namespace DataTypes

	namespace Base {}
	namespace Modules {}
	namespace Plugins {}
} // namespace ScorchCrafter

#endif // SCORCHCRAFTER_PLATFORM_DEFS_CPP_INC
