
/*
 * slotsig_base.h header file
 *
 * Part of the SlogSig project, an attempt to provide a type-safe
 * signals/slots mechanism for the C++ language.
 * This file provides base support for signals and slots.
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

#ifndef __SLOTSIG_BASES_H__
#define __SLOTSIG_BASES_H__ 1

#include <vector>
#include <map>

namespace SlotSig {

enum SlotSigErrors
{
  NoError = 0,
  NullGlobalFct,      //!< Given a null pointer to a global function (from connect or disconnect)
  KnownGlobalFct,     //!< Given global function already connected (e.g. from connect)
  UnknownGlobalFct,   //!< Given global function unknown (from disconnect)
  DynCastFailed,      //!< Trying to connect a method from a class on an instance of an incompatible type (from connect)
  NullInstance,       //!< Given a null pointer when trying to (dis)connect a class's method (from connect or disconnect)
  KnownSlot,          //!< Given method on given instance already connected (from connect)
  UnknownSlot,        //!< Given method on given instance not connected (from disconnect)
  IsEmitting,         //!< The signal is being run, so you can't modify or re-run it
  EmitInterrupted,    //!< The signal emitting has been interrupted by the predicate (from run_if)
  NullSignal,         //!< Given a null pointer as signal (from connect)
  KnownSignal,        //!< The given signal is already chained (from connect)
  UnknownSignal,      //!< The given signal is not chained (from disconnect)
  UnknownClass        //!< The given class is unknown (from disconnect_all)
} ; // enum SlotSigErrors

const char* error2str(SlotSigErrors error) ;

class SlotBase
{
  public:
    virtual ~SlotBase() ;
} ; // SlotBase

class SlotsSetBase ;

class SignalBase
{
  friend class SlotsSetBase ;

  public:
    SignalBase() ;
    virtual ~SignalBase() ;
    
    virtual SlotSigErrors disconnect_all(void* cl) = 0 ;

  protected:
    virtual void slots_set_deleted (SlotsSetBase* ssb) = 0 ;

} ; // class SignalBase

typedef std::map<SignalBase*, unsigned> signals_map_t ;

class SlotsSetBase
{
    friend class SignalBase ;

  public:
    SlotsSetBase() ;
    virtual ~SlotsSetBase() ;

    void disconnect_all() ;

    void connect_from(SignalBase* sig) ;
    void disconnect_from(SignalBase* sig) ;
    void signal_deleted(SignalBase* sig) ;

  private:
    signals_map_t signals_map ;
} ; // class SlotsSetBase

class UnmanagedConnections
{
  public:
    static UnmanagedConnections* instance() ;
    
    void insert (void* in_class, SignalBase* signal) ;
    void erase (void* in_class, SignalBase* signal) ;
    void erase_class(void* in_class) ;
    void about_to_delete(void* in_class) ;
    void erase_signal(SignalBase* sig) ;
    
  private:
    static UnmanagedConnections* _instance ;
  
    UnmanagedConnections() ;
    UnmanagedConnections(const UnmanagedConnections& uc) ;
    UnmanagedConnections& operator= (const UnmanagedConnections& uc) ;

    typedef std::map<void*, signals_map_t> storage_t ;
    storage_t storage ;
    bool _lock_access ;
} ; // class UnmanagedConnects

//! To be called when you're about to delete an instance from a class that doesn't inherits from SlotsSetBase, and which contains slots
void about_to_delete (void* cl) ;

} // namespace SlotSig

#endif // __SLOTSIG_BASES_H__
