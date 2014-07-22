
/*
 * slotsig_base.h header file
 *
 * Part of the SlogSig project, an attempt to provide a type-safe
 * signals/slots mechanism for the C++ language.
 * This file provides base support for signals and slots, and should be
 * compiled and linked with your own program.
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

#include <iostream>

#include "slotsig_bases.h"

namespace SlotSig
{

const char* error2str(SlotSigErrors error)
{
  switch ( error )
  {
    case NoError          : return "NoError" ;
    case NullGlobalFct    : return "NullGlobalFct" ;
    case KnownGlobalFct   : return "KnownGlobalFct" ;
    case UnknownGlobalFct : return "UnknownGlobalFct" ;
    case DynCastFailed    : return "DynCastFailed" ;
    case NullInstance     : return "NullInstance" ;
    case KnownSlot        : return "KnownSlot" ;
    case UnknownSlot      : return "UnknownSlot" ;
    case IsEmitting       : return "IsEmitting" ;
    case EmitInterrupted  : return "EmitInterrupted" ;
    case NullSignal       : return "NullSignal" ;
    case KnownSignal      : return "KnownSignal" ;
    case UnknownSignal    : return "UnknownSignal" ;
    case UnknownClass     : return "UnknownClass" ;
  }
  return "UnknownError" ;
}

SlotBase::~SlotBase()
{ }

SignalBase::SignalBase()
{ }

SignalBase::~SignalBase()
{ }

SlotsSetBase::SlotsSetBase() :
  signals_map()
{ }

SlotsSetBase::~SlotsSetBase()
{
  const signals_map_t::const_iterator end = signals_map.end() ;
  signals_map_t::const_iterator iter = signals_map.begin() ;
  while ( iter != end )
    (iter++)->first->slots_set_deleted(this) ;
}

void SlotsSetBase::disconnect_all()
{
  const signals_map_t::const_iterator end = signals_map.end() ;
  signals_map_t::const_iterator iter = signals_map.begin() ;
  while ( iter != end )
    (iter++)->first->slots_set_deleted(this) ;
  signals_map.clear() ;
}

void SlotsSetBase::connect_from(SignalBase* sig)
{
  if ( sig == 0 )
    return ;
  ++(signals_map[sig]) ;
}

void SlotsSetBase::disconnect_from(SignalBase* sig)
{
  if ( sig == 0 )
    return ;
  signals_map_t::iterator iter = signals_map.find(sig) ;
  if ( iter != signals_map.end() )
  {
    if ( iter->second == 1 )
      signals_map.erase(iter) ;
    else
      --(iter->second) ;
  }
}

void SlotsSetBase::signal_deleted(SignalBase* sig)
{
  if ( sig == 0 )
    return ;
  signals_map.erase(sig) ;
}

//--------------------------------------------------------------------------

// static 
UnmanagedConnections* UnmanagedConnections::_instance = 0 ;

// static 
UnmanagedConnections* UnmanagedConnections::instance()
{
  if ( _instance == 0 )
    _instance = new UnmanagedConnections() ;
  return _instance ;
}

void UnmanagedConnections::insert (void* in_class, SignalBase* signal)
{
  if ( _lock_access )
    return ;
  _lock_access = true ;
  storage_t::iterator i = storage.find(in_class) ;
  if ( i == storage.end() )
    storage[in_class][signal] = 1 ;
  else
  {
    signals_map_t::iterator si = i->second.find(signal) ;
    if ( si == i->second.end() )
      (i->second)[signal] = 1 ;
    else
      ++(si->second) ;
  }
  _lock_access = false ;
}

void UnmanagedConnections::erase (void* in_class, SignalBase* signal)
{
  if ( _lock_access )
    return ;
  _lock_access = true ;
  storage_t::iterator i = storage.find(in_class) ;
  if ( i == storage.end() )
  {
    _lock_access = false ;
    return ;
  }
  signals_map_t::iterator si = i->second.find(signal) ;
  if ( si == i->second.end() )
  {
    _lock_access = false ;
    return ;
  }
  --(si->second) ;
  if ( si->second == 0 )
  {
    i->second.erase(si) ;
    if ( i->second.empty() )
      storage.erase(i) ;
  }
  _lock_access = false ;
}

void UnmanagedConnections::erase_class(void* in_class)
{
  if ( _lock_access )
    return ;
  _lock_access = true ;
  storage.erase(in_class) ;
  _lock_access = false ;
}

void UnmanagedConnections::about_to_delete(void* cl)
{
  if ( _lock_access )
    return ;
  _lock_access = true ;
  storage_t::iterator i = storage.find(cl) ;
  if ( i == storage.end() )
  {
    _lock_access = false ;
    return ;
  }
  signals_map_t::iterator si = i->second.begin() ;
  const signals_map_t::iterator se = i->second.end() ;
  while ( si != se )
  {
    si->first->disconnect_all(cl) ;
    ++si ;
  }
  storage.erase(i) ;
  _lock_access = false ;
}

void UnmanagedConnections::erase_signal(SignalBase* sig)
{
  if ( _lock_access )
    return ;
  _lock_access = true ;
  storage_t::iterator it = storage.begin() ;
  while ( it != storage.end() )
    (it++)->second.erase(sig) ;
  _lock_access = false ;
}

UnmanagedConnections::UnmanagedConnections() :
  storage(),
  _lock_access(false)
{ }

UnmanagedConnections::UnmanagedConnections(const UnmanagedConnections& uc)
{ }

UnmanagedConnections& UnmanagedConnections::operator= (const UnmanagedConnections& uc)
{ return *this ; }

void about_to_delete (void* cl)
{
  if ( cl == 0 )
    return ;
  UnmanagedConnections::instance()->about_to_delete(cl) ;
}

} // namespace SlotSig
