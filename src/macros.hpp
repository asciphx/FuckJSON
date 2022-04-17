
#ifndef MACROS_HPP
#define MACROS_HPP
#include <string>
#include <tuple>
#include <typeinfo>
#include <type_traits>
#include <chrono>
#include <thread>
#include <vector>
#include <ostream>
#include <memory>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <cstdarg>
#include <stdexcept>
#include <string_view>
#include <string.h>
#include <assert.h>
#include <vector>
#include <ctime>
#include <string>
#include <string_view>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <iosfwd>
tm operator+(tm& t, tm& m);tm operator-(tm& t, tm& m);bool operator==(tm& t, tm& m);bool operator!=(tm& t, tm& m);bool operator<(tm& t, tm& m);bool operator>(tm& t, tm& m);bool operator<=(tm& t, tm& m);bool operator>=(tm& t, tm& m);static std::string& toUpperCase(std::string& s);static std::string toUpperCase(const char* s);static std::string& toLowerCase(std::string& s);static std::string toLowerCase(const char* s);static std::string toSqlCase(const char* s);template<typename T> const char* ObjName();static std::string toQuotes(const char* s);std::ostream& operator<<(std::ostream& os, const tm& _v);std::string& operator<<(std::string& s, const tm& _v);
template<unsigned short I = 0x64>class text { unsigned short k = 0, l = 0, u = 0; char* _ = new char[I * 4 + 3]; constexpr const static unsigned short ___ = I * 4 + 3; template<unsigned short A, unsigned short K> friend text<A> operator+(text<A>& t, const text<K>& $); friend std::string& operator<<(std::string& s, text<I>& c) { s.push_back('"'); s += c.c_str(); s.push_back('"'); return s; }; friend std::string& operator<<(std::string& s, const text<I>& c) { s.push_back('"'); s += c.c_str(); s.push_back('"'); return s; }; friend std::ostream& operator<<(std::ostream& s, text<I>& c) { return s << c.c_str(); }; constexpr const static unsigned char UTF$[256] = { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 2, 2 };public: ~text() { delete[]_; _ = nullptr; }; text() { static_assert(I != 0 && I < 0x4000); _[0] = 0; }; text(const char* s) { static_assert(I != 0 && I < 0x4000); while (*s) { u = UTF$[static_cast<unsigned char>(*s)]; while (--u) _[l] = *s++, ++l; ++k; } _[l] = 0; }; text(const text& str) { strcpy(_, str._); l = str.l; k = str.k; } template<unsigned short L> text(text<L>& s) { static_assert(I >= L); strcpy(_, s.c_str()); l = s.length(); k = s.u8size(); } text(const std::string& s) { while (s[l] && k < I) { u = UTF$[static_cast<unsigned char>(s[l])]; while (--u) { _[l] = s[l]; ++l; } ++k; } _[l] = 0; } text& operator = (const char* s) { delete[]_; _ = new char[___]; l = k = 0; while (s[l] && k < I) { u = UTF$[static_cast<unsigned char>(s[l])]; while (--u) { _[l] = s[l]; ++l; } ++k; } _[l] = 0; return *this; } text& operator = (const std::string& s) { delete[]_; _ = new char[___]; l = k = 0; while (s[l] && k < I) { u = UTF$[static_cast<unsigned char>(s[l])]; while (--u) { _[l] = s[l]; ++l; } ++k; } _[l] = 0; return *this; } text& operator = (const text& s) { delete[]_; _ = new char[___]; strcpy(_, s._); l = s.l; k = s.k; return *this; } template<unsigned short L> text& operator = (const text<L>& s) { delete[]_; _ = new char[___]; strncpy(_, s.c_str(), I * 4 + 2); l = s.length(); k = s.u8size(); _[l] = 0; return *this; } inline const char* c_str() const { return _; } inline const unsigned short length() const { return l; } inline const unsigned short u8size() const { return k; } inline char& operator()(unsigned short i) { return i < l ? _[i] : _[l]; } inline text<1> operator[](unsigned short i) { text<1> txt; if (i > k)return txt; unsigned short h = 0, g = 0; const unsigned char* f = reinterpret_cast<unsigned char*>(_); while (h < i) u = UTF$[*f] - 1, ++h, f += u; u = UTF$[*f]; while (++g < u) { txt += *f++; } txt += (char)0; return txt; } inline void operator +=(const char* c) { while (*c && k < I) { u = UTF$[static_cast<unsigned char>(*c)]; while (--u) { _[l++] = *c++; } ++k; } _[l] = 0; } inline void operator +=(char c) { _[l++] = c; ++k; } inline void operator <<(char c) { _[l++] = c; _[l] = 0; ++k; } void operator += (const text& t) { const char* s = t.c_str(); if (&t == this) { int i = 2 * k, p = -1; if (i > I)i = I; while (k < i) { u = UTF$[static_cast<unsigned char>(s[l])]; while (--u) { _[l++] = s[++p]; } ++k; } _[l] = 0; } else { unsigned short i = 0xffff; while (s[++i] && k < I) { u = UTF$[static_cast<unsigned char>(s[l])]; while (--u) { _[l++] = s[i]; } ++k; } _[l] = 0; } } template<unsigned short L> void operator += (const text<L>& t) { const char* s = t.c_str(); while (*s && k < I) { u = UTF$[static_cast<unsigned char>(*s)]; while (--u) { _[l++] = *s++; } ++k; } _[l] = 0; } void operator += (const std::string& t) { const char* s = t.c_str(); while (*s && k < I) { u = UTF$[static_cast<unsigned char>(*s)]; while (--u) { _[l++] = *s++; } ++k; } _[l] = 0; } inline void push_back(const char c) { if (k < I) _[l++] = c, ++k; } inline void push_begin(const char c) { unsigned short i = l; while (i) { _[i] = _[i - 1]; --i; } _[++l] = 0; _[0] = c, ++k; } inline void end() { _[l] = 0; } inline void clear() { _[0] = l = k = 0; }};
#ifdef __cplusplus
extern "C" {
#endif
 static char RES_ASCII[97] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"; static int strLen(const char* s) { const char* e = s; while (*++e); return e - s; } static void strCpy(char* d, const char* s) { while (*s) { *d++ = *s++; }*d = 0; } static char* strStr(char* d, const char* s) { int i = 0, j = 0, l = strLen(d), k = strLen(s); while (i < l&& j < k) if (d[i] == s[j])++i, ++j; else i = i - j + 1, j = 0; if (j == k) { return d + i - k; } return (char*)0; } static int strCmp(const char* c, const char* s) { while (*s == *c && *c && *s)++c, ++s; return *c == *s ? 0 : *c > *s ? 1 : -1; } static int find1CharPosDESC(const char* c, const char d) { for (int l = strLen(c), i = l - 1; i > 0; --i) { if (c[i] == d)return l - i; } return -1; } static int find1CharPosASC(const char* c, const char d) { for (int l = strLen(c), i = 0; i < l; ++i) { if (c[i] == d)return i; }return -1; }  char* subStr(const char* c, int i, int e) { if (e < i || i < 0)return (char*)0; char* w = (char*)malloc(sizeof(char) * (e - i + 1)); int p = 0; while (i < e)w[p++] = c[i++]; w[p] = 0; return w; } char* joinS2CInInt(const char* c, int i, const char* s) { int j = strLen(s), l = strLen(c), p = 0, n = 0, m = 0; char* w = (char*)malloc(sizeof(char) * (l + j)); --i; while (p < i)w[p++] = c[n++]; while (m < j)w[p++] = s[m++]; while (n < l) { w[p++] = c[n++]; } w[p] = '\0'; return w; } char* to8Str(unsigned long long i) { int z = 2; for (unsigned long long a = i; a > 0x7f; a -= 0x7f, a /= 0x100, ++z); unsigned long long b, t = i / 0x100; b = i - t * 0x100 - 32; char* w = (char*)malloc(sizeof(char) * z); w[--z] = '\0'; while (t > 0x7f) { w[--z] = RES_ASCII[b]; i = t; t = i / 0x100; b = i - t * 0x100 - 32; } w[--z] = RES_ASCII[b]; if (z > 0) { t -= 32; w[0] = RES_ASCII[t]; } return w; } char* to4Str(int i) { int t = i / 0x100, b = i - t * 0x100 - 32, z = i > 0x7f7f7f ? 5 : i > 0x7f7f ? 4 : i > 0x7f ? 3 : 2; char* w = (char*)malloc(sizeof(char) * z); w[--z] = 'a'; while (t > 0x7f) { w[--z] = RES_ASCII[b]; i = t; t = i / 0x100; b = i - t * 0x100 - 32; } w[--z] = RES_ASCII[b]; if (z > 0) { t -= 32; w[0] = RES_ASCII[t]; } return w; } static int hack_4str(const char* oid) { int t = 0, i = strLen(oid), j, pow = 1; while (i-- > 0) { char* chr = subStr(oid, i, i + 1); j = 0; while (j++ < 0x61) { char* s = subStr(RES_ASCII, j - 1, j); if (strCmp(chr, s) == 0) { t = t + (j + 0x1f) * pow; pow = pow * 0x100; free(s); break; } free(s); } free(chr); } return t; } static inline constexpr unsigned long long hack8Str(const char* s) { unsigned long long r = s[0]; for (signed char i = 0; ++i < 8 && s[i]; r << 8, r += s[i]); return r; } static inline constexpr int hack4Str(const char* s) { int r = s[0]; for (signed char i = 0; ++i < 4 && s[i]; r << 8, r += s[i]); return r; }  static inline constexpr unsigned long long hackStr(const char* s) { unsigned long long r = s[0] - 0x41; for (unsigned short i = 0; s[++i]; r *= 0x3b, r += s[i] - 0x41); return r; } static inline constexpr unsigned long long hackUrl(const char* s) { unsigned long long r = s[0] - 0x23; for (unsigned char i = 0; s[++i] > 0x22; r << 5, r += s[i] > 0x5e ? s[i] - 0x5f : s[i] > 0x40 ? s[i] - 0x3f : s[i] - 3); return r; }  static inline short atos_(char* c) { short r = 0; if (*c == '-') { while (*++c) r = r * 10 - *c + 0x30; } else { while (*c) r = r * 10 + *c++ - 0x30; } return r; } static inline int atoi_(char* c) { int r = 0; if (*c == '-') { while (*++c) r = r * 10 - *c + 0x30; } else { while (*c) r = r * 10 + *c++ - 0x30; } return r; } static inline long long atol_(char* c) { long long r = 0; if (*c == '-') { while (*++c) r = r * 10 - *c + 0x30; } else { while (*c) r = r * 10 + *c++ - 0x30; } return r; } static inline long long aton_(char* c) { long long r = 0; while (*++c) r = r * 10 - *c + 0x30; return r; } static inline unsigned long long atou_(char* c) { unsigned long long r = 0; while (*c) r = r * 10 + *c++ - 0x30; return r; }
#ifdef __cplusplus
} constexpr unsigned long long operator""_l(const char* s, size_t ) { unsigned long long r = s[0]; for (unsigned long long i = 0; ++i < 8 && s[i]; r << 8, r += s[i]); return r;}constexpr int operator""_i(const char* s, size_t ) { int r = s[0]; for (int i = 0; ++i < 4 && s[i]; r << 8, r += s[i]); return r;}constexpr unsigned long long operator""_a(const char* s, size_t ) { unsigned long long r = s[0] - 0x41; for (unsigned long long i = 1; s[i]; r *= 0x3b, r += s[i++] - 0x41); return r;}
#ifdef _WIN32
#define _IS_WIN 1
#else
#define _IS_WIN 0
#endif
inline std::string_view DecodeURL(std::string& str) { char* o = (char*)str.data(); char* c = (char*)str.data(); const char* e = c + str.size(); while (c < e) { if (*c == '%' && c < e - 2) { char n[3]; n[0] = c[1]; n[1] = c[2]; n[2] = 0; *o = char(strtol(n, nullptr, 16)); c += 2; } else if (o != c) *o = *c; ++o; ++c; } return std::string_view(str.data(), o - str.data());}static std::string& toUpperCase(std::string& s) { char* c = (char*)s.c_str(); if (*c > 0x60 && *c < 0x7b) { *c &= ~0x20; } while (*++c) { if (*c > 0x60 && *c < 0x7b) *c &= ~0x20; } return s;}static std::string toUpperCase(const char* s) { std::string e; if (*s > 0x60 && *s < 0x7b) { e.push_back(*s - 0x20); } while (*++s) { if (*s > 0x60 && *s < 0x7b) { e.push_back(*s - 0x20); } else { e.push_back(*s); } } return e;}static std::string& toLowerCase(std::string& s) { char* c = (char*)s.c_str(); if (*c > 0x40 && *c < 0x5b) { *c |= 0x20; } while (*++c) { if (*c > 0x40 && *c < 0x5b) *c |= 0x20; } return s;}static std::string toLowerCase(const char* s) { std::string e; if (*s > 0x40 && *s < 0x5b) { e.push_back(*s + 0x20); } while (*++s) { if (*s > 0x40 && *s < 0x5b) { e.push_back(*s + 0x20); } else { e.push_back(*s); } } return e;}static std::string toSqlCase(const char* s) { std::string e; if (*s > 0x40 && *s < 0x5b) { e.push_back(*s + 0x20); } while (*++s) { if (*s > 0x40 && *s < 0x5b) { e.push_back(0x5f); e.push_back(*s + 0x20); } else { e.push_back(*s); } } return e;}template<typename T> inline const char* ObjName() { const char* s = typeid(T).name(); if constexpr (_IS_WIN) { while (*++s != 0x20); return ++s; } else { while (*s < 0x3a && *s++ != 0x24) {}; return s; }}template<typename T, typename U> inline uint64_t ObjLink() { const char* s = typeid(T).name(), * c = typeid(U).name(); unsigned long long r = 0; if constexpr (_IS_WIN) { while (*++s != 0x20); while (*++c != 0x20); for (; *++s; r *= 0x3b, r += *s - 0x41); for (; *++c; r *= 0x3b, r += *c - 0x41); } else { while (*s < 0x3a && *s++ != 0x24) {}; while (*c < 0x3a && *c++ != 0x24) {}; for (; *s; r *= 0x3b, r += *s++ - 0x41); for (; *c; r *= 0x3b, r += *c++ - 0x41); } return r;}static std::string toQuotes(const char* s) { std::string e; while (*s) { if (*s == 0x27) { e.push_back(0x27); e.push_back(0x27); } else { e.push_back(*s); } *++s; } return e;}std::ostream& operator<<(std::ostream& os, const tm& _v) {
#ifdef _WIN32
 os << std::setfill('0') << std::setw(4) << _v.tm_year + 1900;
#else
 int y = _v.tm_year / 100; os << std::setfill('0') << std::setw(2) << 19 + y << std::setw(2) << _v.tm_year - y * 100;
#endif
 os << '-' << std::setw(2) << (_v.tm_mon + 1) << '-' << std::setw(2) << _v.tm_mday << ' ' << std::setw(2) << _v.tm_hour << ':' << std::setw(2) << _v.tm_min << ':' << std::setw(2) << _v.tm_sec; return os;}std::string& operator<<(std::string& s, const tm& _v) { std::ostringstream os;
#ifdef _WIN32
 os << std::setfill('0') << std::setw(4) << _v.tm_year + 1900;
#else
 int y = _v.tm_year / 100; os << std::setfill('0') << std::setw(2) << 19 + y << std::setw(2) << _v.tm_year - y * 100;
#endif
 os << '-' << std::setw(2) << (_v.tm_mon + 1) << '-' << std::setw(2) << _v.tm_mday << ' ' << std::setw(2) << _v.tm_hour << ':' << std::setw(2) << _v.tm_min << ':' << std::setw(2) << _v.tm_sec; s = os.str(); return s;}tm operator+(tm& t, tm& m) { tm time; memcpy(&time, &t, sizeof(tm)); time.tm_sec += m.tm_sec; time.tm_min += m.tm_min; time.tm_hour += m.tm_hour; time.tm_mday += m.tm_mday; time.tm_mon += m.tm_mon; time.tm_year += m.tm_year; time.tm_isdst = 0; return time;}tm operator-(tm& t, tm& m) { tm time; memcpy(&time, &t, sizeof(tm)); time.tm_sec -= m.tm_sec; time.tm_min -= m.tm_min; time.tm_hour -= m.tm_hour; time.tm_mday -= m.tm_mday; time.tm_mon -= m.tm_mon; time.tm_year -= m.tm_year; time.tm_isdst = 0; return time;}bool operator==(tm& t, tm& m) { return mktime(&t) == mktime(&m); }bool operator!=(tm& t, tm& m) { return mktime(&t) != mktime(&m); }bool operator<(tm& t, tm& m) { return mktime(&t) < mktime(&m); }bool operator>(tm& t, tm& m) { return mktime(&t) > mktime(&m); }bool operator<=(tm& t, tm& m) { return mktime(&t) <= mktime(&m); }bool operator>=(tm& t, tm& m) { return mktime(&t) >= mktime(&m); }
template<unsigned short I>std::ostream& operator<<(std::ostream& s, text<I> c) { return s << c.c_str(); }template<unsigned short I>text<I> operator+(text<I>& t, const char* c) { unsigned short& l = *((unsigned short*)(&t)), & k = *((unsigned short*)(reinterpret_cast<char*>(&t) + (char)(&reinterpret_cast<char const volatile&>(((text<I>*)0)->*&text<I>::l)))); while (*c && l < I) { unsigned char u = text<I>::UTF$[static_cast<unsigned char>(*c)]; while (--u) t[k] = *c++, ++k; ++l; } t[l] = 0; return t;}
#if _IS_WIN
#define T_INT8 "signed char"_l
#define T_UINT8 " char"_l
#define T_INT16 "short"_l
#define T_UINT16 " short"_l
#define T_INT 'int'
#define T_UINT " int"_l
#define T_INT64 "__int64"_l
#define T_UINT64 " __int64"_l
#define T_BOOL 'bool'
#define T_DOUBLE "double"_l
#define T_FLOAT "float"_l
#define T_TM "struct tm"_l
#define T_TEXT "class text"_l
#define T_STRING "class std::basic_string"_l

#else
#define T_INT8 'a'
#define T_UINT8 'h'
#define T_INT16 's'
#define T_UINT16 't'
#define T_INT 'i'
#define T_UINT 'j'
#define T_INT64 'x'
#define T_UINT64 'y'
#define T_BOOL 'b'
#define T_DOUBLE 'd'
#define T_FLOAT 'f'
#define T_TM '2tm'
#define T_TEXT "4textILt"_l
#define T_STRING "NSt7__cx"_l
#endif

#define T_INT8_ 'a'
#define T_UINT8_ 'h'
#define T_INT16_ 's'
#define T_UINT16_ 't'
#define T_INT_ 'i'
#define T_UINT_ 'j'
#define T_INT64_ 'x'
#define T_UINT64_ 'y'
#define T_BOOL_ 'b'
#define T_DOUBLE_ 'd'
#define T_FLOAT_ 'f'
#define T_TM_ 'm'
#define T_TEXT_ 'e'
#define T_STRING_ 'c'
#define T_POINTER_ '*'
#define T_VECTOR_ '_'
#endif
template<unsigned short I>text<I> operator+(text<I>& t, const std::string& $) { unsigned short& l = *((unsigned short*)(&t)), & k = *((unsigned short*)(reinterpret_cast<char*>(&t) + (char)(&reinterpret_cast<char const volatile&>(((text<I>*)0)->*&text<I>::l)))); char* c = (char*)$.c_str(); while (*c && l < I) { unsigned char u = text<I>::UTF$[static_cast<unsigned char>(*c)]; while (--u) t[k] = *c++, ++k; ++l; } t[l] = 0; return t;}template<unsigned short I, unsigned short K>text<I> operator+(text<I>& t, const text<K>& $) { unsigned short& l = *((unsigned short*)(&t)), & k = *((unsigned short*)(reinterpret_cast<char*>(&t) + (char)(&reinterpret_cast<char const volatile&>(((text<I>*)0)->*&text<I>::l)))); char* c = (char*)$.c_str(); while (*c && l < I) { unsigned char u = text<I>::UTF$[static_cast<unsigned char>(*c)]; while (--u) t[k] = *c++, ++k; ++l; } t[l] = 0; return t;}template<unsigned short I>std::string operator+(std::string& t, const text<I>& $) { char* c = (char*)$.c_str(); while (*c) { t.push_back(*c); ++c; } t.push_back(0); return t;}template<class T>struct is_text: std::false_type {};template<class T>struct is_text<T[]>: std::false_type {};template<unsigned short N>struct is_text<text<N>>: std::true_type {};inline const char* textify(const char* t) { return t; }inline const char* textify(const std::string& t) { return t.c_str(); }inline const std::string textify(const tm& _v) { std::ostringstream os; os << std::setfill('0');
#ifdef _WIN32
 os << std::setw(4) << _v.tm_year + 1900;
#else
 int y = _v.tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << _v.tm_year - y * 100;
#endif
 os << '-' << std::setw(2) << (_v.tm_mon + 1) << '-' << std::setw(2) << _v.tm_mday << ' ' << std::setw(2) << _v.tm_hour << ':' << std::setw(2) << _v.tm_min << ':' << std::setw(2) << _v.tm_sec; return os.str();}template<unsigned short I, typename T>text<I * 2> operator==(const text<I>& o, const T& v) { text<I * 2> x(o); x += '='; if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) { x += '\''; x += textify(v); x += '\''; } else { x += textify(v); } x += (char)0; return x;}template<unsigned short I, unsigned short L>text<I + L + 6> operator||(text<I> o, const text<L>& c) { text<I + L + 6> x; x += '('; x += o; x += " OR "; x += c; x += ')'; x.end(); return x;};template<unsigned short I, typename T>std::string operator>>(text<I> o, const std::vector<T>& c) { std::string s(o.c_str()); s += " IN("; size_t l = c.size(); if (l > 0) { s += textify(c[0]); for (size_t i = 1; i < l; ++i) { s += ',', s += textify(c[i]); } } s.push_back(')'); return s;};
#include "src/Initalization.hpp"
#define JSON_NOEXCEPTION
#include "json.hpp"
using json = nlohmann::json;
#define RUST_CAST reinterpret_cast<char*>
#define Class(class) struct class {
namespace std {
#if _WIN32
#if _HAS_CXX17==0
 struct string_view { string_view(const char*, unsigned long long); [[nodiscard]] size_t length() const; [[nodiscard]] size_t size() const; [[nodiscard]] inline const char* data() const; }; struct nullopt_t { explicit constexpr nullopt_t(int) {} }; template <class T> struct optional { using value_type = T; constexpr optional() noexcept {} constexpr optional(nullopt_t) noexcept {} }; struct any { any(void* v); any& operator=(void*); }; std::string operator+=(std::string& t, const string_view& $) { return t; };
#endif
#elif !defined(_HAS_CXX17)

#endif
}
template<unsigned short I>inline const char* textify(const text<I>& t) { return t.c_str(); }template<typename T>inline typename std::enable_if<std::is_fundamental<T>::value, const std::string>::type textify(const T& t) { return std::to_string(t); }template<unsigned short I, typename T>text<I * 2> operator!=(const text<I>& o, const T& v) { text<I * 2> x(o); x += '<'; x += '>'; if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) { x += '\''; x += textify(v); x += '\''; } else { x += textify(v); } x += (char)0; return x;}
namespace orm { using Expand = int[];
#define Exp (void)orm::Expand
 template <typename T, typename Fn, std::size_t... I> inline constexpr void ForEachTuple(T& tuple, Fn&& fn, std::index_sequence<I...>) { Exp{ ((void)fn(std::get<I>(tuple)), 0)... }; } template <typename T, typename Fn> inline constexpr void ForEachField(T* value, Fn&& fn) { ForEachTuple(T::Tuple, [value, &fn](auto field) { fn(value->*(field)); }, std::make_index_sequence<sizeof(T::$) / sizeof(*T::$)>{}); } template <class T> struct is_vector : std::false_type {}; template <class T> struct is_vector<T[]> : std::false_type {}; template <class T> struct is_vector<std::vector<T>> : std::true_type {}; template <class T> struct is_ptr : std::false_type {}; template <class T> struct is_ptr<T*> : std::true_type {}; template <class T> struct is_ptr<const T*> : std::true_type {}; template<typename C> struct vector_pack {}; template<template<typename, typename> class C, typename A, typename B> struct vector_pack<C<A, B>> { using type = A; }; template<typename T> using vector_pack_t = typename vector_pack<T>::type; template<typename T> struct ptr_pack {}; template<typename T> struct ptr_pack<T*> { using type = T; }; template<typename T> using ptr_pack_t = typename ptr_pack<T>::type;  inline void FuckJSON(const tm& _v, const char* s, json& j) { std::ostringstream os; os << std::setfill('0');
#ifdef _WIN32
 os << std::setw(4) << _v.tm_year + 1900;
#else
 int y = _v.tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << _v.tm_year - y * 100;
#endif
 os << '-' << std::setw(2) << (_v.tm_mon + 1) << '-' << std::setw(2) << _v.tm_mday << ' ' << std::setw(2) << _v.tm_hour << ':' << std::setw(2) << _v.tm_min << ':' << std::setw(2) << _v.tm_sec; j[s] = os.str(); } template <class T> static inline typename std::enable_if<is_text<T>::value || std::is_same_v<T, std::string>, void>::type FuckJSON(const T& _v, const char* s, json& j) { j[s] = _v.c_str(); } template <class T> static typename std::enable_if<is_vector<T>::value, void>::type FuckJSON(const T& _v, const char* c, json& j) { using Y = vector_pack_t<T>; size_t l = _v.size(); if (l) { if constexpr (std::is_same<Y, std::string>::value || std::is_same<Y, tm>::value || is_text<Y>::value) { std::string s; s.reserve(0x1f); s.push_back('['); s.push_back('\"'); if constexpr (std::is_same<Y, std::string>::value) { s += _v[0]; } else { s << _v[0]; } s.push_back('\"'); for (size_t i = 1; i < l; ++i) { s.push_back(','); s.push_back('\"'); if constexpr (std::is_same<Y, std::string>::value) { s += _v[i]; } else { s << _v[i]; } s.push_back('\"'); } s.push_back(']'); j[c] = json::parse(s); } else if constexpr (std::is_fundamental<Y>::value) { std::string s; s.push_back('['); s += std::to_string(_v[0]); for (size_t i = 0; ++i < l; s.push_back(','), s += std::to_string(_v[i])); s.push_back(']'); j[c] = json::parse(s); } else { std::string s; s.reserve(0x3f); s.push_back('['); for (size_t i = 0; i < l; ++i) { auto* t = &_v[i]; s.push_back('{'); int8_t k = -1; ForEachTuple(Y::Tuple, [t, &k, &s](auto& _) { if constexpr (std::is_same<const tm, std::remove_reference_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":\""; std::ostringstream os; const tm* time = &(t->*_); os << std::setfill('0');
#ifdef _WIN32
 os << std::setw(4) << time->tm_year + 1900;
#else
 int y = time->tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << time->tm_year - y * 100;
#endif
 os << '-' << std::setw(2) << (time->tm_mon + 1) << '-' << std::setw(2) << time->tm_mday << ' ' << std::setw(2) << time->tm_hour << ':' << std::setw(2) << time->tm_min << ':' << std::setw(2) << time->tm_sec << '"'; s += os.str(); } else if constexpr (std::is_same<bool, decltype(t->*_)>::value) { s.push_back('"'); s += t->$[++k]; s += "\":", s += t->*_ == true ? "true" : "false"; } else if constexpr (std::is_fundamental<std::remove_reference_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":" + std::to_string(t->*_); } else if constexpr (std::is_same<const std::string, std::remove_reference_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":\"" + t->*_ + "\""; } else if constexpr (is_vector<std::decay_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":"; s << t->*_; } else if constexpr (is_ptr<std::decay_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":"; t->*_ == nullptr ? s += "null" : s << t->*_; } else { s.push_back('"'); s += t->$[++k]; s += "\":"; s << t->*_; } s.push_back(','); }, std::make_index_sequence<sizeof(Y::$) / sizeof(*Y::$)>{}); s[s.size() - 1] = '}'; s.push_back(','); } s[s.size() - 1] = ']'; j[c] = json::parse(s); } } } template<typename T> inline typename std::enable_if<!is_ptr<T>::value&& std::is_fundamental<T>::value, void>::type FuckJSON(const T& _v, const char* s, json& j) { j[s] = _v; } template <class T> static typename std::enable_if<is_ptr<T>::value && !std::is_fundamental<T>::value, void>::type FuckJSON(const T& _v, const char* c, json& j) { if (_v == nullptr) { j[c] = nullptr; } else { using Y = ptr_pack_t<T>; auto* t = const_cast<T>(_v); std::string s; s.reserve(0x3f); s.push_back('{'); int8_t k = -1; ForEachTuple(Y::Tuple, [t, &k, &s](auto& _) { if constexpr (std::is_same<tm, std::remove_reference_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":\""; std::ostringstream os; const tm* time = &(t->*_); os << std::setfill('0');
#ifdef _WIN32
 os << std::setw(4) << time->tm_year + 1900;
#else
 int y = time->tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << time->tm_year - y * 100;
#endif
 os << '-' << std::setw(2) << (time->tm_mon + 1) << '-' << std::setw(2) << time->tm_mday << ' ' << std::setw(2) << time->tm_hour << ':' << std::setw(2) << time->tm_min << ':' << std::setw(2) << time->tm_sec << '"'; s += os.str(); s.push_back(','); } else if constexpr (std::is_same<bool, decltype(t->*_)>::value) { s.push_back('"'); s += t->$[++k]; s += "\":", s += t->*_ == true ? "true" : "false"; s.push_back(','); } else if constexpr (std::is_fundamental<std::remove_reference_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":" + std::to_string(t->*_); s.push_back(','); } else if constexpr (std::is_same<std::string, std::remove_reference_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":\"" + t->*_ + "\""; s.push_back(','); } else if constexpr (is_vector<std::remove_reference_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":"; s << &(t->*_); s.push_back(','); } else if constexpr (is_text<std::remove_reference_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":"; s << t->*_; s.push_back(','); } else if constexpr (is_ptr<std::remove_reference_t<decltype(t->*_)>>::value) { s.push_back('"'); s += t->$[++k]; s += "\":"; t->*_ == nullptr ? s += "null" : s << t->*_; s.push_back(','); } else { s.push_back('"'); s += t->$[++k]; s += "\":"; s << &(t->*_); s.push_back(','); } }, std::make_index_sequence<sizeof(Y::$) / sizeof(*Y::$)>{}); s[s.size() - 1] = '}'; j[c] = json::parse(s); } }  inline void FuckOop(tm& _v, const char* s, const json& j) { std::string d_; try { if (j.contains(s))j.at(s).get_to(d_); } catch (const std::exception&) { _v.tm_year = -1900; _v.tm_mon = -1; _v.tm_mday = 0; _v.tm_hour = 0; _v.tm_min = 0; _v.tm_sec = 0; } int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0; if (sscanf(d_.c_str(), "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) { _v.tm_year = year - 1900; _v.tm_mon = month - 1; _v.tm_mday = day; _v.tm_hour = hour; _v.tm_min = min; _v.tm_sec = sec; } } template <class T> static inline typename std::enable_if<is_text<T>::value || std::is_same_v<T, std::string>, void>::type FuckOop(T& _v, const char* s, const json& j) { try { _v = j.at(s).get<std::string>(); } catch (const std::exception&) {} } template <class T> static inline typename std::enable_if<is_vector<T>::value, void>::type FuckOop(T& _v, const char* s, const json& j) { using Y = vector_pack_t<T>; try { for (auto& t : j.at(s))_v.push_back(t.get<Y>()); } catch (const std::exception&) {} } template<typename T> inline typename std::enable_if<!is_ptr<T>::value&& std::is_fundamental<T>::value, void>::type FuckOop(T& _v, const char* s, const json& j) { try { if (j.contains(s)) { if constexpr (std::is_same_v<bool, T>) { _v = j.at(s).get<short>() == 0 ? false : true; } else { j.at(s).get_to(_v); } } } catch (const std::exception&) {} } template <class T> inline typename std::enable_if<is_ptr<T>::value && !std::is_fundamental<T>::value, void>::type FuckOop(T& _v, const char* s, const json& j) { if (_v != nullptr && j.contains(s)) { *_v = j.at(s).get<ptr_pack_t<T>>(); } }}template<unsigned short I, typename T>text<I * 2> operator<(const text<I>& o, const T& v) { text<I * 2> x(o); x += '<'; if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) { x += '\''; x += textify(v); x += '\''; } else { x += textify(v); } x += (char)0; return x;}template<unsigned short I, typename T>text<I * 2> operator<=(const text<I>& o, const T& v) { text<I * 2> x(o); x += '<'; x += '='; if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) { x += '\''; x += textify(v); x += '\''; } else { x += textify(v); } x += (char)0; return x;}template<unsigned short I, typename T>text<I * 2> operator>=(const text<I>& o, const T& v) { text<I * 2> x(o); x += '>'; x += '='; if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) { x += '\''; x += textify(v); x += '\''; } else { x += textify(v); } x += (char)0; return x;}template<unsigned short I, typename T>text<I * 2> operator>(const text<I>& o, const T& v) { text<I * 2> x(o); x += '>'; if constexpr (std::is_same<T, std::string>::value || std::is_same<T, tm>::value || std::is_same<T, const char*>::value) { x += '\''; x += textify(v); x += '\''; } else { x += textify(v); } x += (char)0; return x;}template<unsigned short I, unsigned short L>text<I + L + 7> operator&&(text<I> o, const text<L>& c) { text<I + L + 7> x; x += '('; x += o; x += " AND "; x += c; x += ')'; x.end(); return x;};
#define EXP(O) O
#ifdef _MSC_VER
#define ARGS_HELPER(_,_64,_63,_62,_61,_60,_59,_58,_57,_56,_55,_54,_53,_52,_51,_50,_49,_48,_47,_46,_45,_44,_43,_42,_41,_40,_39,_38,_37,_36,_35,_34,_33,_32,_31,_30,_29,_28,_27,_26,_25,_24,_23,_22,_21,_20,_19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,N,...) N
#define NUM_ARGS(...) EXP(ARGS_HELPER(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#else
#define ARGS_HELPER(_,_64,_63,_62,_61,_60,_59,_58,_57,_56,_55,_54,_53,_52,_51,_50,_49,_48,_47,_46,_45,_44,_43,_42,_41,_40,_39,_38,_37,_36,_35,_34,_33,_32,_31,_30,_29,_28,_27,_26,_25,_24,_23,_22,_21,_20,_19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,N,...) N
#define NUM_ARGS(...) ARGS_HELPER(0, __VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#endif
#ifndef _WIN32
#define _IS_WIN32 0
#else
#define _IS_WIN32 1
#endif
#define PROTO_1(k) std::string_view(#k, sizeof(#k)-1)
#define PROTO_2(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_1(__VA_ARGS__))
#define PROTO_3(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_2(__VA_ARGS__))
#define PROTO_4(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_3(__VA_ARGS__))
#define PROTO_5(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_4(__VA_ARGS__))
#define PROTO_6(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_5(__VA_ARGS__))
#define PROTO_7(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_6(__VA_ARGS__))
#define PROTO_8(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_7(__VA_ARGS__))
#define PROTO_9(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_8(__VA_ARGS__))
#define PROTO_10(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_9(__VA_ARGS__))
#define PROTO_11(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_10(__VA_ARGS__))
#define PROTO_12(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_11(__VA_ARGS__))
#define PROTO_13(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_12(__VA_ARGS__))
#define PROTO_14(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_13(__VA_ARGS__))
#define PROTO_15(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_14(__VA_ARGS__))
#define PROTO_16(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_15(__VA_ARGS__))
#define PROTO_17(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_16(__VA_ARGS__))
#define PROTO_18(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_17(__VA_ARGS__))
#define PROTO_19(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_18(__VA_ARGS__))
#define PROTO_20(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_19(__VA_ARGS__))
#define PROTO_21(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_20(__VA_ARGS__))
#define PROTO_22(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_21(__VA_ARGS__))
#define PROTO_23(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_22(__VA_ARGS__))
#define PROTO_24(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_23(__VA_ARGS__))
#define PROTO_25(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_24(__VA_ARGS__))
#define PROTO_26(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_25(__VA_ARGS__))
#define PROTO_27(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_26(__VA_ARGS__))
#define PROTO_28(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_27(__VA_ARGS__))
#define PROTO_29(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_28(__VA_ARGS__))
#define PROTO_30(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_29(__VA_ARGS__))
#define PROTO_31(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_30(__VA_ARGS__))
#define PROTO_32(k,...) std::string_view(#k, sizeof(#k)-1), EXP(PROTO_31(__VA_ARGS__))
#define PROTO_N1(N,...) EXP(PROTO_##N(__VA_ARGS__))
#define PROTO_N(N,...) PROTO_N1(N,__VA_ARGS__)

#define COL_1(o,k) orm::FuckJSON(o.k,#k,j);
#define COL_2(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_1(o,__VA_ARGS__))
#define COL_3(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_2(o,__VA_ARGS__))
#define COL_4(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_3(o,__VA_ARGS__))
#define COL_5(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_4(o,__VA_ARGS__))
#define COL_6(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_5(o,__VA_ARGS__))
#define COL_7(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_6(o,__VA_ARGS__))
#define COL_8(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_7(o,__VA_ARGS__))
#define COL_9(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_8(o,__VA_ARGS__))
#define COL_10(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_9(o,__VA_ARGS__))
#define COL_11(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_10(o,__VA_ARGS__))
#define COL_12(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_11(o,__VA_ARGS__))
#define COL_13(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_12(o,__VA_ARGS__))
#define COL_14(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_13(o,__VA_ARGS__))
#define COL_15(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_14(o,__VA_ARGS__))
#define COL_16(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_15(o,__VA_ARGS__))
#define COL_17(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_16(o,__VA_ARGS__))
#define COL_18(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_17(o,__VA_ARGS__))
#define COL_19(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_18(o,__VA_ARGS__))
#define COL_20(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_19(o,__VA_ARGS__))
#define COL_21(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_20(o,__VA_ARGS__))
#define COL_22(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_21(o,__VA_ARGS__))
#define COL_23(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_22(o,__VA_ARGS__))
#define COL_24(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_23(o,__VA_ARGS__))
#define COL_25(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_24(o,__VA_ARGS__))
#define COL_26(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_25(o,__VA_ARGS__))
#define COL_27(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_26(o,__VA_ARGS__))
#define COL_28(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_27(o,__VA_ARGS__))
#define COL_29(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_28(o,__VA_ARGS__))
#define COL_30(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_29(o,__VA_ARGS__))
#define COL_31(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_30(o,__VA_ARGS__))
#define COL_32(o,k,...) orm::FuckJSON(o.k,#k,j), EXP(COL_31(o,__VA_ARGS__))
#define COL_N1(o,N,...) EXP(COL_##N(o,__VA_ARGS__))
#define COL_N(o,N,...) COL_N1(o,N,__VA_ARGS__)

#define ATTR_1(o,k) orm::FuckOop(o.k,#k,j);
#define ATTR_2(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_1(o,__VA_ARGS__))
#define ATTR_3(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_2(o,__VA_ARGS__))
#define ATTR_4(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_3(o,__VA_ARGS__))
#define ATTR_5(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_4(o,__VA_ARGS__))
#define ATTR_6(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_5(o,__VA_ARGS__))
#define ATTR_7(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_6(o,__VA_ARGS__))
#define ATTR_8(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_7(o,__VA_ARGS__))
#define ATTR_9(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_8(o,__VA_ARGS__))
#define ATTR_10(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_9(o,__VA_ARGS__))
#define ATTR_11(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_10(o,__VA_ARGS__))
#define ATTR_12(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_11(o,__VA_ARGS__))
#define ATTR_13(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_12(o,__VA_ARGS__))
#define ATTR_14(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_13(o,__VA_ARGS__))
#define ATTR_15(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_14(o,__VA_ARGS__))
#define ATTR_16(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_15(o,__VA_ARGS__))
#define ATTR_17(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_16(o,__VA_ARGS__))
#define ATTR_18(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_17(o,__VA_ARGS__))
#define ATTR_19(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_18(o,__VA_ARGS__))
#define ATTR_20(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_19(o,__VA_ARGS__))
#define ATTR_21(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_20(o,__VA_ARGS__))
#define ATTR_22(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_21(o,__VA_ARGS__))
#define ATTR_23(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_22(o,__VA_ARGS__))
#define ATTR_24(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_23(o,__VA_ARGS__))
#define ATTR_25(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_24(o,__VA_ARGS__))
#define ATTR_26(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_25(o,__VA_ARGS__))
#define ATTR_27(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_26(o,__VA_ARGS__))
#define ATTR_28(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_27(o,__VA_ARGS__))
#define ATTR_29(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_28(o,__VA_ARGS__))
#define ATTR_30(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_29(o,__VA_ARGS__))
#define ATTR_31(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_30(o,__VA_ARGS__))
#define ATTR_32(o,k,...) orm::FuckOop(o.k,#k,j), EXP(ATTR_31(o,__VA_ARGS__))
#define ATTR_N1(o,N,...) EXP(ATTR_##N(o,__VA_ARGS__))
#define ATTR_N(o,N,...) ATTR_N1(o,N,__VA_ARGS__)
#define ATTRS(o,...)static void to_json(json& j, const o& f) { COL_N(f,NUM_ARGS(__VA_ARGS__),__VA_ARGS__) }static void from_json(const json& j, o& f) { ATTR_N(f,NUM_ARGS(__VA_ARGS__),__VA_ARGS__) }


#define STAR_1(o,k) &o::k
#define STAR_2(o,k,...) &o::k, EXP(STAR_1(o,__VA_ARGS__))
#define STAR_3(o,k,...) &o::k, EXP(STAR_2(o,__VA_ARGS__))
#define STAR_4(o,k,...) &o::k, EXP(STAR_3(o,__VA_ARGS__))
#define STAR_5(o,k,...) &o::k, EXP(STAR_4(o,__VA_ARGS__))
#define STAR_6(o,k,...) &o::k, EXP(STAR_5(o,__VA_ARGS__))
#define STAR_7(o,k,...) &o::k, EXP(STAR_6(o,__VA_ARGS__))
#define STAR_8(o,k,...) &o::k, EXP(STAR_7(o,__VA_ARGS__))
#define STAR_9(o,k,...) &o::k, EXP(STAR_8(o,__VA_ARGS__))
#define STAR_10(o,k,...) &o::k, EXP(STAR_9(o,__VA_ARGS__))
#define STAR_11(o,k,...) &o::k, EXP(STAR_10(o,__VA_ARGS__))
#define STAR_12(o,k,...) &o::k, EXP(STAR_11(o,__VA_ARGS__))
#define STAR_13(o,k,...) &o::k, EXP(STAR_12(o,__VA_ARGS__))
#define STAR_14(o,k,...) &o::k, EXP(STAR_13(o,__VA_ARGS__))
#define STAR_15(o,k,...) &o::k, EXP(STAR_14(o,__VA_ARGS__))
#define STAR_16(o,k,...) &o::k, EXP(STAR_15(o,__VA_ARGS__))
#define STAR_17(o,k,...) &o::k, EXP(STAR_16(o,__VA_ARGS__))
#define STAR_18(o,k,...) &o::k, EXP(STAR_17(o,__VA_ARGS__))
#define STAR_19(o,k,...) &o::k, EXP(STAR_18(o,__VA_ARGS__))
#define STAR_20(o,k,...) &o::k, EXP(STAR_19(o,__VA_ARGS__))
#define STAR_21(o,k,...) &o::k, EXP(STAR_20(o,__VA_ARGS__))
#define STAR_22(o,k,...) &o::k, EXP(STAR_21(o,__VA_ARGS__))
#define STAR_23(o,k,...) &o::k, EXP(STAR_22(o,__VA_ARGS__))
#define STAR_24(o,k,...) &o::k, EXP(STAR_23(o,__VA_ARGS__))
#define STAR_25(o,k,...) &o::k, EXP(STAR_24(o,__VA_ARGS__))
#define STAR_26(o,k,...) &o::k, EXP(STAR_25(o,__VA_ARGS__))
#define STAR_27(o,k,...) &o::k, EXP(STAR_26(o,__VA_ARGS__))
#define STAR_28(o,k,...) &o::k, EXP(STAR_27(o,__VA_ARGS__))
#define STAR_29(o,k,...) &o::k, EXP(STAR_28(o,__VA_ARGS__))
#define STAR_30(o,k,...) &o::k, EXP(STAR_29(o,__VA_ARGS__))
#define STAR_31(o,k,...) &o::k, EXP(STAR_30(o,__VA_ARGS__))
#define STAR_32(o,k,...) &o::k, EXP(STAR_31(o,__VA_ARGS__))
#define STARS_N(o,N,...) EXP(STAR_##N(o,__VA_ARGS__))
#define STARS(o,N,...) STARS_N(o,N,__VA_ARGS__)

#define STAR__1(o,k) decltype(&o::k)
#define STAR__2(o,k,...) decltype(&o::k), EXP(STAR__1(o,__VA_ARGS__))
#define STAR__3(o,k,...) decltype(&o::k), EXP(STAR__2(o,__VA_ARGS__))
#define STAR__4(o,k,...) decltype(&o::k), EXP(STAR__3(o,__VA_ARGS__))
#define STAR__5(o,k,...) decltype(&o::k), EXP(STAR__4(o,__VA_ARGS__))
#define STAR__6(o,k,...) decltype(&o::k), EXP(STAR__5(o,__VA_ARGS__))
#define STAR__7(o,k,...) decltype(&o::k), EXP(STAR__6(o,__VA_ARGS__))
#define STAR__8(o,k,...) decltype(&o::k), EXP(STAR__7(o,__VA_ARGS__))
#define STAR__9(o,k,...) decltype(&o::k), EXP(STAR__8(o,__VA_ARGS__))
#define STAR__10(o,k,...) decltype(&o::k), EXP(STAR__9(o,__VA_ARGS__))
#define STAR__11(o,k,...) decltype(&o::k), EXP(STAR__10(o,__VA_ARGS__))
#define STAR__12(o,k,...) decltype(&o::k), EXP(STAR__11(o,__VA_ARGS__))
#define STAR__13(o,k,...) decltype(&o::k), EXP(STAR__12(o,__VA_ARGS__))
#define STAR__14(o,k,...) decltype(&o::k), EXP(STAR__13(o,__VA_ARGS__))
#define STAR__15(o,k,...) decltype(&o::k), EXP(STAR__14(o,__VA_ARGS__))
#define STAR__16(o,k,...) decltype(&o::k), EXP(STAR__15(o,__VA_ARGS__))
#define STAR__17(o,k,...) decltype(&o::k), EXP(STAR__16(o,__VA_ARGS__))
#define STAR__18(o,k,...) decltype(&o::k), EXP(STAR__17(o,__VA_ARGS__))
#define STAR__19(o,k,...) decltype(&o::k), EXP(STAR__18(o,__VA_ARGS__))
#define STAR__20(o,k,...) decltype(&o::k), EXP(STAR__19(o,__VA_ARGS__))
#define STAR__21(o,k,...) decltype(&o::k), EXP(STAR__20(o,__VA_ARGS__))
#define STAR__22(o,k,...) decltype(&o::k), EXP(STAR__21(o,__VA_ARGS__))
#define STAR__23(o,k,...) decltype(&o::k), EXP(STAR__22(o,__VA_ARGS__))
#define STAR__24(o,k,...) decltype(&o::k), EXP(STAR__23(o,__VA_ARGS__))
#define STAR__25(o,k,...) decltype(&o::k), EXP(STAR__24(o,__VA_ARGS__))
#define STAR__26(o,k,...) decltype(&o::k), EXP(STAR__25(o,__VA_ARGS__))
#define STAR__27(o,k,...) decltype(&o::k), EXP(STAR__26(o,__VA_ARGS__))
#define STAR__28(o,k,...) decltype(&o::k), EXP(STAR__27(o,__VA_ARGS__))
#define STAR__29(o,k,...) decltype(&o::k), EXP(STAR__28(o,__VA_ARGS__))
#define STAR__30(o,k,...) decltype(&o::k), EXP(STAR__29(o,__VA_ARGS__))
#define STAR__31(o,k,...) decltype(&o::k), EXP(STAR__30(o,__VA_ARGS__))
#define STAR__32(o,k,...) decltype(&o::k), EXP(STAR__31(o,__VA_ARGS__))
#define STAR_S_N(o,N,...) EXP(STAR__##N(o,__VA_ARGS__))
#define STAR_S(o,N,...) STAR_S_N(o,N,__VA_ARGS__)

#define SCHEMA(o,...) private: static std::tuple<STAR_S(o,NUM_ARGS(__VA_ARGS__),__VA_ARGS__)> Tuple; const static std::string_view $[];friend std::string& operator<<(std::string& s, o* c); template<typename T,typename Fn>friend constexpr void orm::ForEachField(T* value, Fn&& fn);template<typename U>friend typename std::enable_if<is_vector<U>::value,void>::type orm::FuckJSON(const U& u, const char* s, json& j);template<typename U>friend typename std::enable_if<is_ptr<U>::value&&!std::is_fundamental<U>::value,void>::type orm::FuckJSON(const U& u, const char* c, json& j);


#define FUCKER(o,...)const std::string_view o::$[NUM_ARGS(__VA_ARGS__)] = { PROTO_N(NUM_ARGS(__VA_ARGS__),__VA_ARGS__) }; ATTRS(o, __VA_ARGS__)std::tuple<STAR_S(o, NUM_ARGS(__VA_ARGS__),__VA_ARGS__)> o::Tuple = std::make_tuple(STARS(o, NUM_ARGS(__VA_ARGS__), __VA_ARGS__));std::string& operator<<(std::string& s, o* c) { if (c == nullptr || *((char*)(RUST_CAST(c)+(size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->*std::get<0>(o::Tuple))))) == 0) { s += "null"; return s; } s.push_back('{'); int8_t i = -1; ForEachField(c, [&i, c, &s](auto& t) { using Y=std::remove_reference_t<decltype(t)>; ++i; if constexpr (!is_vector<Y>::value) { s.push_back('"'); s += c->$[i]; } if constexpr (std::is_same<tm, Y>::value) { s += "\":\""; std::ostringstream os; const tm* time = &t; os << std::setfill('0'); if constexpr(_IS_WIN32){os << std::setw(4) << time->tm_year + 1900;}else{ int y = time->tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << time->tm_year - y * 100;} os << '-' << std::setw(2) << (time->tm_mon + 1) << '-' << std::setw(2) << time->tm_mday << ' ' << std::setw(2) << time->tm_hour << ':' << std::setw(2) << time->tm_min << ':' << std::setw(2) << time->tm_sec << '"'; s += os.str(); s.push_back(','); } else if constexpr (std::is_same<bool, Y>::value) { s += "\":", s += t == true ? "true" : "false"; s.push_back(','); } else if constexpr (std::is_fundamental<Y>::value) { s += "\":" + std::to_string(t); s.push_back(','); } else if constexpr (std::is_same<std::string, Y>::value) { s += "\":\"" + t + "\""; s.push_back(','); } else if constexpr (is_vector<Y>::value) { if (t.size()) { s.push_back('"'); s += c->$[i]; s += "\":"; s << &t; s.push_back(','); } } else if constexpr (is_ptr<Y>::value) { s += "\":";t==nullptr?s+="null":s << t; s.push_back(','); } else if constexpr (is_text<Y>::value) { s += "\":"; s << t; s.push_back(','); } else { s += "\":"; s << &t; s.push_back(','); } }); s[s.size() - 1] = '}'; return s; }std::string& operator<<(std::string& s, std::vector<o> c) {s.push_back('['); if (c.size() > 0) { s << &c[0]; for (size_t i = 1; i < c.size(); ++i) { s.push_back(','), s << &c[i]; }} s.push_back(']'); return s; }std::ostream& operator<<(std::ostream& s, std::vector<o> c) {s << '['; if (c.size() > 0) { s << &c[0]; for (size_t i = 1; i < c.size(); ++i) { s << ',' << &c[i]; }} s << ']'; return s; }std::string& operator<<(std::string& s, std::vector<o>* c) { s.push_back('['); if (c->size() > 0) { s << &c->at(0); for (size_t i = 1; i < c->size(); ++i) { s.push_back(','), s << &c->at(i); } } s.push_back(']'); return s;}std::ostream& operator<<(std::ostream& s, std::vector<o>* c) { s << '['; if (c->size() > 0) { s << &c->at(0); for (size_t i = 1; i < c->size(); ++i) { s << ',' << &c->at(i); } } s << ']'; return s;}std::ostream& operator<<(std::ostream& m, o* c) { std::string s; s << c; return m << s; }std::ostream& operator<<(std::ostream& m, o& c) { std::string s; s << &c; return m << s; }

#define FUCKJSON(o,...)SCHEMA(o,__VA_ARGS__)};FUCKER(o,__VA_ARGS__)
#endif
