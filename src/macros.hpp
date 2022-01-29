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
#include "utils/text.hpp"
#include "json.hpp"
#include "Initalization.hpp"
namespace orm {
  using Expand = int[];
#define Exp (void)orm::Expand
  template <typename T, typename Fn, std::size_t... I>
  inline constexpr void ForEachTuple(T& tuple, Fn&& fn, std::index_sequence<I...>) {
	Exp{ ((void)fn(std::get<I>(tuple)), 0)... };
  }
  template <typename T>
  inline constexpr auto Tuple() { return std::make_tuple(); }
  template <typename T, typename Fn>
  inline constexpr void ForEachField(T* value, Fn&& fn) {
	constexpr const auto tuplE = Tuple<T>();
	ForEachTuple(tuplE, [value, &fn](auto field) { fn(value->*(field)); },
	  std::make_index_sequence<std::tuple_size<decltype(tuplE)>::value>{});
  }
  template <class T> struct is_vector : std::false_type {};
  template <class T> struct is_vector<T[]> : std::false_type {};
  template <class T> struct is_vector<std::vector<T>> : std::true_type {};
  template <class T> struct is_ptr : std::false_type {};
  template <class T> struct is_ptr<T*> : std::true_type {};
  template <class T> struct is_ptr<const T*> : std::true_type {};
  template<typename C> struct vector_pack {};
  template<template<typename, typename> class C, typename A, typename B> struct vector_pack<C<A, B>> { using type = A; };
  template<typename T> using vector_pack_t = typename vector_pack<T>::type;
  template<typename T> struct ptr_pack {};
  template<typename T> struct ptr_pack<T*> { using type = T; };
  template<typename T> using ptr_pack_t = typename ptr_pack<T>::type;
  //Serialization into JSON
  inline void FuckJSON(const tm& _v, const char* s, json& j) {
	std::ostringstream os; os << std::setfill('0');
#ifdef _WIN32
	os << std::setw(4) << _v.tm_year + 1900;
#else
	int y = _v.tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << _v.tm_year - y * 100;
#endif
	os << '-' << std::setw(2) << (_v.tm_mon + 1) << '-' << std::setw(2) << _v.tm_mday << ' ' << std::setw(2)
	  << _v.tm_hour << ':' << std::setw(2) << _v.tm_min << ':' << std::setw(2) << _v.tm_sec; j[s] = os.str();
  }
  template <class T>
  static inline typename std::enable_if<is_text<T>::value, void>::type FuckJSON(const T& _v, const char* s, json& j) {
	j[s] = _v.c_str();
  }
  template <class T>
  static typename std::enable_if<is_vector<T>::value, void>::type FuckJSON(const T& _v, const char* c, json& j) {
	size_t l = _v.size(); if (l) {
	  constexpr auto $ = Tuple<vector_pack_t<T>>(); std::string s; s.reserve(0x3f); s.push_back('[');
	  for (size_t i = 0; i < l; ++i) {
		auto* t = &_v[i]; s.push_back('{'); int8_t k = -1;
		ForEachTuple($, [t, &k, &s](auto& _) {
		  if constexpr (std::is_same<const tm, std::remove_reference_t<decltype(t->*_)>>::value) {
			s.push_back('"'); s += t->$[++k]; s += "\":\""; std::ostringstream os; const tm* time = &(t->*_); os << std::setfill('0');
#ifdef _WIN32
			os << std::setw(4) << time->tm_year + 1900;
#else
			int y = time->tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << time->tm_year - y * 100;
#endif
			os << '-' << std::setw(2) << (time->tm_mon + 1) << '-' << std::setw(2) << time->tm_mday << ' ' << std::setw(2)
			  << time->tm_hour << ':' << std::setw(2) << time->tm_min << ':' << std::setw(2) << time->tm_sec << '"'; s += os.str();
		  } else if constexpr (std::is_same<bool, decltype(t->*_)>::value) {
			s.push_back('"'); s += t->$[++k]; s += "\":", s += t->*_ == true ? "true" : "false";
		  } else if constexpr (std::is_fundamental<std::remove_reference_t<decltype(t->*_)>>::value) {
			s.push_back('"'); s += t->$[++k]; s += "\":" + std::to_string(t->*_);
		  } else if constexpr (std::is_same<const std::string, std::remove_reference_t<decltype(t->*_)>>::value) {
			s.push_back('"'); s += t->$[++k]; s += "\":\"" + t->*_ + "\"";
		  } else if constexpr (is_vector<std::remove_reference_t<decltype(t->*_)>>::value) {
			s.push_back('"'); s += t->$[++k]; s += "\":"; s << &(t->*_);
		  } else if constexpr (is_ptr<std::remove_reference_t<decltype(t->*_)>>::value) {
			s.push_back('"'); s += t->$[++k]; s += "\":"; s << *t->*_;
		  } else {
			s.push_back('"'); s += t->$[++k]; s += "\":"; s << t->*_;
		  } s.push_back(',');
		  }, std::make_index_sequence<std::tuple_size<decltype($)>::value>{}); s[s.size() - 1] = '}'; s.push_back(',');
	  } s[s.size() - 1] = ']'; j[c] = json::parse(s);
	}
  }
  template<typename T>
  inline typename std::enable_if<!is_ptr<T>::value&& std::is_fundamental<T>::value, void>::type FuckJSON(const T& _v, const char* s, json& j) {
	j[s] = _v;
  }
  template <class T>
  static typename std::enable_if<is_ptr<T>::value && !std::is_fundamental<T>::value, void>::type FuckJSON(const T& _v, const char* c, json& j) {
	if (_v == nullptr) {
	  j[c] = nullptr;
	} else {
	  constexpr auto $ = Tuple<ptr_pack_t<T>>(); auto* t = _v; std::string s; s.reserve(0x3f); s.push_back('{'); int8_t k = -1;
	  ForEachTuple($, [t, &k, &s](auto& _) {
		if constexpr (std::is_same<tm, std::remove_reference_t<decltype(t->*_)>>::value) {
		  s.push_back('"'); s += t->$[++k];
		  s += "\":\""; std::ostringstream os; const tm* time = &(t->*_); os << std::setfill('0');
#ifdef _WIN32
		  os << std::setw(4) << time->tm_year + 1900;
#else
		  int y = time->tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << time->tm_year - y * 100;
#endif
		  os << '-' << std::setw(2) << (time->tm_mon + 1) << '-' << std::setw(2) << time->tm_mday << ' ' << std::setw(2)
			<< time->tm_hour << ':' << std::setw(2) << time->tm_min << ':' << std::setw(2) << time->tm_sec << '"'; s += os.str(); s.push_back(',');
		} else if constexpr (std::is_same<bool, decltype(t->*_)>::value) {
		  s.push_back('"'); s += t->$[++k]; s += "\":", s += t->*_ == true ? "true" : "false"; s.push_back(',');
		} else if constexpr (std::is_fundamental<std::remove_reference_t<decltype(t->*_)>>::value) {
		  s.push_back('"'); s += t->$[++k]; s += "\":" + std::to_string(t->*_); s.push_back(',');
		} else if constexpr (std::is_same<std::string, std::remove_reference_t<decltype(t->*_)>>::value) {
		  s.push_back('"'); s += t->$[++k]; s += "\":\"" + t->*_ + "\""; s.push_back(',');
		} else if constexpr (is_vector<std::remove_reference_t<decltype(t->*_)>>::value) {
		  s.push_back('"'); s += t->$[++k]; s += "\":"; s << &(t->*_); s.push_back(',');
		} else if constexpr (is_text<std::remove_reference_t<decltype(t->*_)>>::value) {
		  s.push_back('"'); s += t->$[++k]; s += "\":"; s << t->*_; s.push_back(',');
		} else if constexpr (is_ptr<std::remove_reference_t<decltype(t->*_)>>::value) {
		  s.push_back('"'); s += t->$[++k]; s += "\":"; t->*_ == nullptr ? s += "null" : s << t->*_; s.push_back(',');
		} else {
		  s.push_back('"'); s += t->$[++k]; s += "\":"; s << &(t->*_); s.push_back(',');
		}
		}, std::make_index_sequence<std::tuple_size<decltype($)>::value>{}); s[s.size() - 1] = '}';
		j[c] = json::parse(s);
	}
  }
  //Deserialization into Object
  inline void FuckOop(tm& _v, const char* s, const json& j) {
	std::string d_; try { if (j.contains(s))j.at(s).get_to(d_); } catch (const std::exception&) {
	  _v.tm_year = -1900; _v.tm_mon = -1; _v.tm_mday = 0; _v.tm_hour = 0; _v.tm_min = 0; _v.tm_sec = 0;
	} int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
	if (sscanf(d_.c_str(), "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
	  _v.tm_year = year - 1900; _v.tm_mon = month - 1; _v.tm_mday = day; _v.tm_hour = hour; _v.tm_min = min; _v.tm_sec = sec;
	}
  }
  template <class T>
  static inline typename std::enable_if<is_text<T>::value, void>::type FuckOop(T& _v, const char* s, const json& j) {
	try { _v = j.at(s).get<std::string>(); } catch (const std::exception&) {}
  }
  template <class T>
  static inline typename std::enable_if<is_vector<T>::value, void>::type FuckOop(T& _v, const char* s, const json& j) {
	try { for (auto& t : j.at(s))_v.push_back(t.get<vector_pack_t<T>>()); } catch (const std::exception&) {}
  }
  template<typename T>
  inline typename std::enable_if<!is_ptr<T>::value&& std::is_fundamental<T>::value, void>::type FuckOop(T& _v, const char* s, const json& j) {
	try { j.at(s).get_to(_v); } catch (const std::exception&) {}
  }
  template <class T>
  inline typename std::enable_if<is_ptr<T>::value && !std::is_fundamental<T>::value, void>::type FuckOop(T& _v, const char* s, const json& j) {
	//Pointer cannot be deserialized
  }
}
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
#define PROTO_1(k)      #k
#define PROTO_2(k,...)  #k, EXP(PROTO_1(__VA_ARGS__))
#define PROTO_3(k,...)  #k, EXP(PROTO_2(__VA_ARGS__))
#define PROTO_4(k,...)  #k, EXP(PROTO_3(__VA_ARGS__))
#define PROTO_5(k,...)  #k, EXP(PROTO_4(__VA_ARGS__))
#define PROTO_6(k,...)  #k, EXP(PROTO_5(__VA_ARGS__))
#define PROTO_7(k,...)  #k, EXP(PROTO_6(__VA_ARGS__))
#define PROTO_8(k,...)  #k, EXP(PROTO_7(__VA_ARGS__))
#define PROTO_9(k,...)  #k, EXP(PROTO_8(__VA_ARGS__))
#define PROTO_10(k,...) #k, EXP(PROTO_9(__VA_ARGS__))
#define PROTO_11(k,...) #k, EXP(PROTO_10(__VA_ARGS__))
#define PROTO_12(k,...) #k, EXP(PROTO_11(__VA_ARGS__))
#define PROTO_13(k,...) #k, EXP(PROTO_12(__VA_ARGS__))
#define PROTO_14(k,...) #k, EXP(PROTO_13(__VA_ARGS__))
#define PROTO_15(k,...) #k, EXP(PROTO_14(__VA_ARGS__))
#define PROTO_16(k,...) #k, EXP(PROTO_15(__VA_ARGS__))
#define PROTO_17(k,...) #k, EXP(PROTO_16(__VA_ARGS__))
#define PROTO_18(k,...) #k, EXP(PROTO_17(__VA_ARGS__))
#define PROTO_19(k,...) #k, EXP(PROTO_18(__VA_ARGS__))
#define PROTO_20(k,...) #k, EXP(PROTO_19(__VA_ARGS__))
#define PROTO_21(k,...) #k, EXP(PROTO_20(__VA_ARGS__))
#define PROTO_22(k,...) #k, EXP(PROTO_21(__VA_ARGS__))
#define PROTO_23(k,...) #k, EXP(PROTO_22(__VA_ARGS__))
#define PROTO_24(k,...) #k, EXP(PROTO_23(__VA_ARGS__))
#define PROTO_25(k,...) #k, EXP(PROTO_24(__VA_ARGS__))
#define PROTO_26(k,...) #k, EXP(PROTO_25(__VA_ARGS__))
#define PROTO_27(k,...) #k, EXP(PROTO_26(__VA_ARGS__))
#define PROTO_28(k,...) #k, EXP(PROTO_27(__VA_ARGS__))
#define PROTO_29(k,...) #k, EXP(PROTO_28(__VA_ARGS__))
#define PROTO_30(k,...) #k, EXP(PROTO_29(__VA_ARGS__))
#define PROTO_31(k,...) #k, EXP(PROTO_30(__VA_ARGS__))
#define PROTO_32(k,...) #k, EXP(PROTO_31(__VA_ARGS__))
#define PROTO_N1(N,...) EXP(PROTO_##N(__VA_ARGS__))
#define PROTO_N(N,...) PROTO_N1(N,__VA_ARGS__)

#define COL_1(o,k)      orm::FuckJSON(o.k,#k,j);
#define COL_2(o,k,...)  orm::FuckJSON(o.k,#k,j), EXP(COL_1(o,__VA_ARGS__))
#define COL_3(o,k,...)  orm::FuckJSON(o.k,#k,j), EXP(COL_2(o,__VA_ARGS__))
#define COL_4(o,k,...)  orm::FuckJSON(o.k,#k,j), EXP(COL_3(o,__VA_ARGS__))
#define COL_5(o,k,...)  orm::FuckJSON(o.k,#k,j), EXP(COL_4(o,__VA_ARGS__))
#define COL_6(o,k,...)  orm::FuckJSON(o.k,#k,j), EXP(COL_5(o,__VA_ARGS__))
#define COL_7(o,k,...)  orm::FuckJSON(o.k,#k,j), EXP(COL_6(o,__VA_ARGS__))
#define COL_8(o,k,...)  orm::FuckJSON(o.k,#k,j), EXP(COL_7(o,__VA_ARGS__))
#define COL_9(o,k,...)  orm::FuckJSON(o.k,#k,j), EXP(COL_8(o,__VA_ARGS__))
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

#define ATTR_1(o,k)      orm::FuckOop(o.k,#k,j);
#define ATTR_2(o,k,...)  orm::FuckOop(o.k,#k,j), EXP(ATTR_1(o,__VA_ARGS__))
#define ATTR_3(o,k,...)  orm::FuckOop(o.k,#k,j), EXP(ATTR_2(o,__VA_ARGS__))
#define ATTR_4(o,k,...)  orm::FuckOop(o.k,#k,j), EXP(ATTR_3(o,__VA_ARGS__))
#define ATTR_5(o,k,...)  orm::FuckOop(o.k,#k,j), EXP(ATTR_4(o,__VA_ARGS__))
#define ATTR_6(o,k,...)  orm::FuckOop(o.k,#k,j), EXP(ATTR_5(o,__VA_ARGS__))
#define ATTR_7(o,k,...)  orm::FuckOop(o.k,#k,j), EXP(ATTR_6(o,__VA_ARGS__))
#define ATTR_8(o,k,...)  orm::FuckOop(o.k,#k,j), EXP(ATTR_7(o,__VA_ARGS__))
#define ATTR_9(o,k,...)  orm::FuckOop(o.k,#k,j), EXP(ATTR_8(o,__VA_ARGS__))
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
#define ATTRS(o,...)\
static void to_json(json& j, const o& f) { COL_N(f,NUM_ARGS(__VA_ARGS__),__VA_ARGS__) }\
static void from_json(const json& j, o& f) { ATTR_N(f,NUM_ARGS(__VA_ARGS__),__VA_ARGS__) }

#define STAR_1(o,k)      &o::k
#define STAR_2(o,k,...)  &o::k, EXP(STAR_1(o,__VA_ARGS__))
#define STAR_3(o,k,...)  &o::k, EXP(STAR_2(o,__VA_ARGS__))
#define STAR_4(o,k,...)  &o::k, EXP(STAR_3(o,__VA_ARGS__))
#define STAR_5(o,k,...)  &o::k, EXP(STAR_4(o,__VA_ARGS__))
#define STAR_6(o,k,...)  &o::k, EXP(STAR_5(o,__VA_ARGS__))
#define STAR_7(o,k,...)  &o::k, EXP(STAR_6(o,__VA_ARGS__))
#define STAR_8(o,k,...)  &o::k, EXP(STAR_7(o,__VA_ARGS__))
#define STAR_9(o,k,...)  &o::k, EXP(STAR_8(o,__VA_ARGS__))
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

#define FUCKJSON(o,...)const char* ::o::$[NUM_ARGS(__VA_ARGS__)] = { PROTO_N(NUM_ARGS(__VA_ARGS__),__VA_ARGS__) };\
template<>inline constexpr auto orm::Tuple<o>(){return std::make_tuple(STARS(o,NUM_ARGS(__VA_ARGS__), __VA_ARGS__));}ATTRS(o, __VA_ARGS__)\
std::string& operator<<(std::string& s, o* c) {\
s.push_back('{'); int8_t i = -1;\
ForEachField(c, [&i, c, &s](auto& t) {\
  if constexpr (!is_vector<std::remove_reference_t<decltype(t)>>::value) { s.push_back('"'); s += c->$[++i]; }\
  if constexpr (std::is_same<tm, std::remove_reference_t<decltype(t)>>::value) {\
	s += "\":\""; std::ostringstream os; const tm* time = &t; os << std::setfill('0');\
if constexpr(_IS_WIN32){os << std::setw(4) << time->tm_year + 1900;}else{\
int y = time->tm_year / 100; os << std::setw(2) << 19 + y << std::setw(2) << time->tm_year - y * 100;}\
	os << '-' << std::setw(2) << (time->tm_mon + 1) << '-' << std::setw(2) << time->tm_mday << ' ' << std::setw(2)\
	  << time->tm_hour << ':' << std::setw(2) << time->tm_min << ':' << std::setw(2) << time->tm_sec << '"'; s += os.str();\
  } else if constexpr (std::is_same<bool, std::remove_reference_t<decltype(t)>>::value) {\
	s += "\":", s += t == true ? "true" : "false";\
  } else if constexpr (std::is_fundamental<std::remove_reference_t<decltype(t)>>::value) {\
	s += "\":" + std::to_string(t);\
  } else if constexpr (std::is_same<std::string, std::remove_reference_t<decltype(t)>>::value) {\
	s += "\":\"" + t + "\"";\
  } else if constexpr (is_vector<std::remove_reference_t<decltype(t)>>::value) {\
	size_t l = t.size(); if (l) { s.push_back('"'); s += c->$[++i]; s += "\":"; s << &t; } else { s.pop_back(); }\
  } else if constexpr (is_ptr<std::remove_reference_t<decltype(t)>>::value) {\
    s += "\":";t==nullptr?s+="null":s << t;\
  } else if constexpr (is_text<std::remove_reference_t<decltype(t)>>::value) {\
	s += "\":"; s << t;\
  } else {\
	s += "\":"; s << &t;\
  } s.push_back(',');\
  }); s[s.size() - 1] = '}'; return s;\
  }\
std::string& operator<<(std::string& s, std::vector<o> c) {\
s.push_back('['); size_t l = c.size(); if (l > 0) { s << &c[0];\
  for (size_t i = 1; i < l; ++i) { s.push_back(','), s << &c[i]; }\
} s.push_back(']'); return s; }\
std::ostream& operator<<(std::ostream& s, std::vector<o> c) {\
s << '['; size_t l = c.size(); if (l > 0) { s << &c[0];\
 for (size_t i = 1; i < l; ++i) { s << ',' << &c[i]; }\
} s << ']'; return s; }\
std::string& operator<<(std::string& s, std::vector<o>* c) {\
  s.push_back('['); size_t l = c->size(); if (l > 0) { s << &c->at(0);\
  for (size_t i = 1; i < l; ++i) { s.push_back(','), s << &c->at(i); }\
  } s.push_back(']'); return s;\
}\
std::ostream& operator<<(std::ostream& s, std::vector<o>* c) {\
  s << '['; size_t l = c->size(); if (l > 0) { s << &c->at(0);\
  for (size_t i = 1; i < l; ++i) { s << ',' << &c->at(i); }\
  } s << ']'; return s;\
}\
std::ostream& operator<<(std::ostream& m, o* c) { std::string s; s << c; return m << s; }\
std::ostream& operator<<(std::ostream& m, o& c) { std::string s; s << &c; return m << s; }
#endif
