
/*
 * slotsig_base.h header file
 *
 * Part of the SlogSig project, an attempt to provide a type-safe
 * signals/slots mechanism for the C++ language.
 * This file provides some common tools for the library.
 *
 * Copyright (C) 2003 Yves Bailly <kafka_AT_kafka-fr_DOT_net>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
*/

#ifndef __SLOTSIG_TOOLS_H__
#define __SLOTSIG_TOOLS_H__ 1

namespace SlotSig
{

//! Class to guess the optimal way to transmit parameters
/*!
  Inspired by the TypeTraits class described by Andrei Alexandrescu, in his
  wonderful book "Modern C++ Design" (Addison-Wesley, ISBN 0-201-70431-5).
  Much simpler though, because I don't need all of the Loki library (at least
  for now, who knows), and (sorry Andrei) I don't like type lists - my own
  taste. Should also be more specialized, to take care of simple types (int,
  bool, char...) which are better transmitted by value than by reference.
*/
template <typename _PARAM_TYPE_>
struct Type2Param
{
  enum { type_is_reference = false,
         param_is_reference = true } ;
  typedef _PARAM_TYPE_& ParamType ;
} ;

template <typename _PARAM_TYPE_>
struct Type2Param<_PARAM_TYPE_&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef _PARAM_TYPE_& ParamType ;
} ;

template <typename _PARAM_TYPE_>
struct Type2Param<_PARAM_TYPE_*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef _PARAM_TYPE_* ParamType ;
} ;

template <typename _PARAM_TYPE_>
struct Type2Param<_PARAM_TYPE_*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef _PARAM_TYPE_*& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'bool' basic type

template <>
struct Type2Param<bool>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef bool ParamType ;
} ;

template <>
struct Type2Param<bool&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef bool& ParamType ;
} ;

template <>
struct Type2Param<bool*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef bool* ParamType ;
} ;

template <>
struct Type2Param<bool*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef bool& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'char' basic type

template <>
struct Type2Param<char>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef char ParamType ;
} ;

template <>
struct Type2Param<char&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef char& ParamType ;
} ;

template <>
struct Type2Param<char*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef char* ParamType ;
} ;

template <>
struct Type2Param<char*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef char& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'unsigned char' basic type

template <>
struct Type2Param<unsigned char>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef unsigned char ParamType ;
} ;

template <>
struct Type2Param<unsigned char&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef unsigned char& ParamType ;
} ;

template <>
struct Type2Param<unsigned char*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef unsigned char* ParamType ;
} ;

template <>
struct Type2Param<unsigned char*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef unsigned char& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'short' basic type

template <>
struct Type2Param<short>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef short ParamType ;
} ;

template <>
struct Type2Param<short&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef short& ParamType ;
} ;

template <>
struct Type2Param<short*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef short* ParamType ;
} ;

template <>
struct Type2Param<short*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef short& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'unsigned short' basic type

template <>
struct Type2Param<unsigned short>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef unsigned short ParamType ;
} ;

template <>
struct Type2Param<unsigned short&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef unsigned short& ParamType ;
} ;

template <>
struct Type2Param<unsigned short*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef unsigned short* ParamType ;
} ;

template <>
struct Type2Param<unsigned short*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef unsigned short& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'int' basic type

template <>
struct Type2Param<int>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef int ParamType ;
} ;

template <>
struct Type2Param<int&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef int& ParamType ;
} ;

template <>
struct Type2Param<int*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef int* ParamType ;
} ;

template <>
struct Type2Param<int*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef int& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'unsigned int' basic type

template <>
struct Type2Param<unsigned int>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef unsigned int ParamType ;
} ;

template <>
struct Type2Param<unsigned int&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef unsigned int& ParamType ;
} ;

template <>
struct Type2Param<unsigned int*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef unsigned int* ParamType ;
} ;

template <>
struct Type2Param<unsigned int*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef unsigned int& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'long' basic type

template <>
struct Type2Param<long>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef long ParamType ;
} ;

template <>
struct Type2Param<long&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef long& ParamType ;
} ;

template <>
struct Type2Param<long*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef long* ParamType ;
} ;

template <>
struct Type2Param<long*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef long& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'unsigned long' basic type

template <>
struct Type2Param<unsigned long>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef unsigned long ParamType ;
} ;

template <>
struct Type2Param<unsigned long&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef unsigned long& ParamType ;
} ;

template <>
struct Type2Param<unsigned long*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef unsigned long* ParamType ;
} ;

template <>
struct Type2Param<unsigned long*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef unsigned long& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'float' basic type

template <>
struct Type2Param<float>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef float ParamType ;
} ;

template <>
struct Type2Param<float&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef float& ParamType ;
} ;

template <>
struct Type2Param<float*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef float* ParamType ;
} ;

template <>
struct Type2Param<float*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef float& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'double' basic type

template <>
struct Type2Param<double>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef double ParamType ;
} ;

template <>
struct Type2Param<double&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef double& ParamType ;
} ;

template <>
struct Type2Param<double*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef double* ParamType ;
} ;

template <>
struct Type2Param<double*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef double& ParamType ;
} ;

//--------------------------------------------------------------------------
// Handles 'long double' basic type

template <>
struct Type2Param<long double>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef long double ParamType ;
} ;

template <>
struct Type2Param<long double&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef long double& ParamType ;
} ;

template <>
struct Type2Param<long double*>
{
  enum { type_is_reference = false,
         param_is_reference = false } ;
  typedef long double* ParamType ;
} ;

template <>
struct Type2Param<long double*&>
{
  enum { type_is_reference = true,
         param_is_reference = true } ;
  typedef long double& ParamType ;
} ;

} // namespace SlotSig

#endif //__SLOTSIG_TOOLS_H__
