#pragma once

// --- 8 bits / 1 byte Variables ---
# define I8MIN	-128
# define I8MAX	127
# define U8MIN	0U
# define U8MAX	255U

// --- 16 bits / 2 bytes Variables ---
# define I16MIN	(-32767 - 1)
# define I16MAX	32767
# define U16MIN	0U
# define U16MAX	65535U

// --- 32 bits / 4 bytes Variables ---
# define I32MIN	(-2147483647 - 1)
# define I32MAX	2147483647
# define U32MIN	0U
# define U32MAX	4294967295U

// --- 64 bits / 8 bytes Variables ---
# define I64MIN	(-9223372036854775807LL - 1)
# define I64MAX	9223372036854775807LL
# define U64MIN	0ULL
# define U64MAX	18446744073709551615ULL

#if __cplusplus >= 201103L
	using	i8 = char;
	using	u8 = unsigned char;
	using	i16 = short;
	using	u16 = unsigned short;
	using	i32 = int;
	using	u32 = unsigned int;
	using	i64 = long long;
	using	u64 = unsigned long long;
#else
	typedef char				i8;
	typedef unsigned char		u8;
	typedef short				i16;
	typedef unsigned short		u16;
	typedef int					i32;
	typedef unsigned int		u32;
	typedef long long			i64;
	typedef unsigned long long 	u64;
#endif
