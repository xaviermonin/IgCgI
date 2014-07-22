
/*
 * auto-generated slotsig_6.h header file
 *
 * Part of the SlogSig project, an attempt to provide a type-safe
 * signals/slots mechanism for the C++ language.
 * This file provides support for signals and slots using 6 parameter(s)
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

#ifndef __SLOTSIG_6_H__
#define __SLOTSIG_6_H__ 1

#include <stdexcept>
#include <list>
#include <set>

#include "slotsig_tools.h"
#include "slotsig_bases.h"
#include "slotsig_policies.h"

namespace SlotSig {

/*!
  \brief Base virtual class for slots receiving 6 parameters.
*/
template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
class Slot6 : public SlotBase
{ 
  public:
    //! Runs the stored slot, whatever it is
    virtual _RETURN_TYPE_ run(typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const = 0 ;
    //! Returns \c true if the given slot is the same as self
    virtual bool equals(Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sl) const = 0 ;
    //! Returns the class from which the slot is called
    /*!
      Returns 0 if it's a global function, or if the class does not inherit
      from SlotsSetBase.
    */
    virtual SlotsSetBase* in_base() const ;
    //! Returns a pointer on the thing from which the slot is called
    /*!
      Returns 0 if it's a global function.
    */
    virtual void* in_class_void() const ;
    //! Duplicates self.
    virtual Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* clone() const = 0 ;
} ; // class Slot6<>

/*!
  \brief Class to hold slots which are global functions receiving 6 parameters.
*/
template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
class SlotGlobal6 : public Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>
{
  public:
    typedef _RETURN_TYPE_ (*global_slot_t) (_ARG0_TYPE_ arg0, _ARG1_TYPE_ arg1, _ARG2_TYPE_ arg2, _ARG3_TYPE_ arg3, _ARG4_TYPE_ arg4, _ARG5_TYPE_ arg5) ;

    SlotGlobal6 (global_slot_t gs) ;

    virtual bool equals(Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sl) const ;
    virtual _RETURN_TYPE_ run(typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const ;
    bool matches(void* v, global_slot_t gs) const ;
    const global_slot_t& the_slot() const ;
    virtual Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* clone() const ;

  private:
    global_slot_t global_slot ;
} ; // class SlotGlobal6<>

/*!
  \brief Class to hold slots which are class's methods receiving 6 parameters.
*/
template <class _CLASS_TYPE_, typename _RETURN_TYPE_, typename _METHOD_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
class SlotInClass6 : public Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>
{
  public:
    SlotInClass6 (_CLASS_TYPE_* c, _METHOD_TYPE_ m) ;
    
    virtual _RETURN_TYPE_ run(typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const ;
    virtual bool equals(Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sl) const ;
    bool matches(_CLASS_TYPE_* c, _METHOD_TYPE_ m) const ;
    virtual SlotsSetBase* in_base() const ;
    virtual void* in_class_void() const ;
    const _METHOD_TYPE_& the_slot() const ;
    virtual Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* clone() const ;

  protected:
    _CLASS_TYPE_* _in_class ;
    _METHOD_TYPE_ _method ;
} ; // class SlotInClass6

/*!
  \brief The class used to send a signal with 6 parameters.
*/
template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
class Sig6 : public SignalBase,
                public SimpleStorage<Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*>
{
  public:
    typedef _RETURN_TYPE_ (*global_slot_t) (_ARG0_TYPE_ arg0, _ARG1_TYPE_ arg1, _ARG2_TYPE_ arg2, _ARG3_TYPE_ arg3, _ARG4_TYPE_ arg4, _ARG5_TYPE_ arg5) ;
    typedef SimpleStorage<Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*> Storage ;

    template <class _IN_CLASS>
    struct MethodTypes
    {
      typedef _RETURN_TYPE_ (_IN_CLASS::*method_t) (_ARG0_TYPE_ arg0, _ARG1_TYPE_ arg1, _ARG2_TYPE_ arg2, _ARG3_TYPE_ arg3, _ARG4_TYPE_ arg4, _ARG5_TYPE_ arg5) ;
      typedef _RETURN_TYPE_ (_IN_CLASS::*method_const_t) (_ARG0_TYPE_ arg0, _ARG1_TYPE_ arg1, _ARG2_TYPE_ arg2, _ARG3_TYPE_ arg3, _ARG4_TYPE_ arg4, _ARG5_TYPE_ arg5) const ;
    } ;
    
    typedef std::set<Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*> SignalsSet ;
    typedef std::list<Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*> SlotsList ;

    explicit Sig6(bool ensure_unique = true) ;
    Sig6(const Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>& sig) ;
    ~Sig6() ;
    
    Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>& 
      operator= (const Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>& sig) ;
    Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* clone() const ;
    
    bool ensure_unique() const ;
    SlotSigErrors set_ensure_unique(bool ensure) ;
    SlotSigErrors enforce_unique() ;

    unsigned nb_connected() const ;
    size_t capacity() const ;

    // Connection methods
    
    SlotSigErrors connect (Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sig) ;
    SlotSigErrors connect (global_slot_t f) ;
    template <class _CLASS_TYPE_>
    SlotSigErrors connect (_CLASS_TYPE_* in_class) ;
    template <class _CLASS_TYPE_, class _PARENT_CLASS_>
    SlotSigErrors connect (_CLASS_TYPE_* in_class,
                  _RETURN_TYPE_ (_PARENT_CLASS_::*method)(_ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_)) ;
    template <class _CLASS_TYPE_, class _PARENT_CLASS_>
    SlotSigErrors connect (_CLASS_TYPE_* in_class,
                  _RETURN_TYPE_ (_PARENT_CLASS_::*method)(_ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_) const) ;

    // Disconnection methods
    
    //! Will disconnect everything, slots and chained signals
    SlotSigErrors disconnect_all() ;
    //! Will disconnect any slot from the given instance, or global slots if 0
    virtual SlotSigErrors disconnect_all(void* cl) ;
    
    SlotSigErrors disconnect(Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sig) ;
    SlotSigErrors disconnect (global_slot_t f) ;
    template <class _CLASS_TYPE_>
    SlotSigErrors disconnect (_CLASS_TYPE_* in_class) ;
    template <class _CLASS_TYPE_, class _PARENT_CLASS_>
    SlotSigErrors disconnect (_CLASS_TYPE_* in_class,
                     _RETURN_TYPE_ (_PARENT_CLASS_::*methode)(_ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_)) ;
    template <class _CLASS_TYPE_, class _PARENT_CLASS_>
    SlotSigErrors disconnect (_CLASS_TYPE_* in_class,
                     _RETURN_TYPE_ (_PARENT_CLASS_::*methode)(_ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_) const) ;

    bool is_emitting() const ;

    // Signal emitting methods
    
    SlotSigErrors run(typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const ;
    template <class _ACCUMULATOR_>
    SlotSigErrors run(_ACCUMULATOR_& accum, typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const ;
    template <class _PREDICATE_>
    SlotSigErrors run_if(_PREDICATE_& pred, typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const ;

  protected:
    virtual void slots_set_deleted (SlotsSetBase* ssb) ;
    void clone_from(const Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>& sig) ;
    void chain_from(Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sig) ;
    void unchain_from(Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sig) ;

  private:
    template <class _CLASS_TYPE_, typename _METHOD_TYPE_>
    SlotSigErrors connect_gen (_CLASS_TYPE_* in_class, _METHOD_TYPE_ method) ;
    template <class _CLASS_TYPE_, typename _METHOD_TYPE_>
    SlotSigErrors disconnect_gen (_CLASS_TYPE_* in_class, _METHOD_TYPE_ method) ;

    mutable bool _is_emitting ;
    unsigned _nb_unmanaged_connect ;
    bool _ensure_unique ;
    
    SignalsSet _chained_signals ;
    SignalsSet _chained_from ;
} ; // class Sig6<>

//==========================================================================

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotsSetBase* Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::in_base() const
{
  return 0 ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
void* Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::in_class_void() const
{
  return 0 ;
}

//--------------------------------------------------------------------------

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::SlotGlobal6 (global_slot_t gs) :
  global_slot(gs)
{ }

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
bool SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  equals(Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sl) const
{
  SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sg =
    static_cast<SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*>(sl) ;
  if ( sg != 0 )
    return sg->matches((void*)0, global_slot) ;
  else
    return false ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
_RETURN_TYPE_ SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  run(typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const
{
  return global_slot(arg0, arg1, arg2, arg3, arg4, arg5) ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
bool SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::matches(void* v, 
  typename SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::global_slot_t gs) const
{
  return ((v == 0) && (gs == global_slot)) ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
const typename SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::global_slot_t& 
SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::the_slot() const
{
  return global_slot ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* 
SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::clone() const
{
  return new SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>(global_slot) ;
}

//--------------------------------------------------------------------------

template <class _CLASS_TYPE_, typename _RETURN_TYPE_, typename _METHOD_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  SlotInClass6 (_CLASS_TYPE_* c, _METHOD_TYPE_ m) :
  Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>(),
  _in_class(c),
  _method(m)
{ }

template <class _CLASS_TYPE_, typename _RETURN_TYPE_, typename _METHOD_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* 
SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  clone() const
{
  return new 
    SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>(
      _in_class, _method) ;
}

template <class _CLASS_TYPE_, typename _RETURN_TYPE_, typename _METHOD_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
_RETURN_TYPE_ 
  SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  run(typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const
{
  return (_in_class->*_method)(arg0, arg1, arg2, arg3, arg4, arg5) ;
}

template <class _CLASS_TYPE_, typename _RETURN_TYPE_, typename _METHOD_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
bool 
  SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  equals(Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sl) const
{
  SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sic =
    static_cast<SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*>(sl) ;
  if ( sic != 0 )
    return sic->matches(_in_class, _method) ;
  return false ;
}

template <class _CLASS_TYPE_, typename _RETURN_TYPE_, typename _METHOD_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
bool 
  SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  matches(_CLASS_TYPE_* c, _METHOD_TYPE_ m) const
{
  return ((_in_class == c) && (_method == m)) ;
}

template <class _CLASS_TYPE_, typename _RETURN_TYPE_, typename _METHOD_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotsSetBase* 
  SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  in_base() const
{
  return dynamic_cast<SlotsSetBase*>(_in_class) ;
}

template <class _CLASS_TYPE_, typename _RETURN_TYPE_, typename _METHOD_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
void* 
  SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  in_class_void() const
{
  return (void*)_in_class ;
}

template <class _CLASS_TYPE_, typename _RETURN_TYPE_, typename _METHOD_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
const _METHOD_TYPE_& 
  SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  the_slot() const
{
  return _method ;
}

//--------------------------------------------------------------------------

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  Sig6(bool ensure_unique) :
  SignalBase(),
  SimpleStorage<Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*>(),
  _is_emitting(false),
  _ensure_unique(ensure_unique)
{ }

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  Sig6(const Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>& sig) :
  SignalBase(),
  SimpleStorage<Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*>(),
  _is_emitting(false),
  _nb_unmanaged_connect(0),
  _ensure_unique(false)
{
  clone_from(sig) ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  ~Sig6()
{
  if ( _is_emitting )
    throw std::logic_error("SlotSig6 : should not delete a signal while emitting !") ;
  if ( _nb_unmanaged_connect > 0 )
    UnmanagedConnections::instance()->erase_signal(this) ;
  const typename Storage::const_iterator e = this->end() ;
  typename Storage::const_iterator i = this->begin() ;
  while ( i != e )
  {
    if ( (*i) != 0 )
    {
      SlotsSetBase* ssb = (*i)->in_base() ;
      if ( ssb != 0 )
        ssb->signal_deleted(this) ;
      delete (*i) ;
    }
    ++i ;
  }
  // Unchain signals
  while ( _chained_from.begin() != _chained_from.end() )
    (*(_chained_from.begin()))->disconnect(this) ;
  while ( _chained_signals.begin() != _chained_signals.end() )
    disconnect(*(_chained_signals.begin())) ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>& 
  Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  operator= (const Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>& sig)
{
  if ( ! _is_emitting )
    clone_from(sig) ;
  return *this ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  clone() const
{
  Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* new_sig = 
    new Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>(*this) ;
  return new_sig ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  disconnect_all()
{
  if ( _is_emitting )
    return IsEmitting ;
  if ( _nb_unmanaged_connect > 0 )
    UnmanagedConnections::instance()->erase_signal(this) ;
  typename Storage::iterator i = this->begin() ;
  while ( i != this->end() )
  {
    if ( (*i) != 0 )
    {
      SlotsSetBase* ssb = (*i)->in_base() ;
      if ( ssb != 0 )
        ssb->disconnect_from(this) ;
      delete (*i) ;
      i = erase(i) ;
    }
    else
      ++i ;
  }
  // Unchain signals
  while ( _chained_from.begin() != _chained_from.end() )
    (*(_chained_from.begin()))->disconnect(this) ;
  while ( _chained_signals.begin() != _chained_signals.end() )
    disconnect(*(_chained_signals.begin())) ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  disconnect_all(void* cl)
{
  typename Storage::iterator i = this->begin() ;
  bool found = false ;
  while ( i != this->end() )
  {
    if ( (*i) != 0 )
    {
      if ( (*i)->in_class_void() == cl )
      {  
        found = true ;
        SlotsSetBase* ssb = (*i)->in_base() ;
        if ( ssb != 0 )
          ssb->disconnect_from(this) ;
        else
        {
          UnmanagedConnections::instance()->erase(cl, this) ;
          --_nb_unmanaged_connect ;
        }
        i = erase(i) ;
      }
      else
        ++i ;
    }
    else
      ++i ;
  }
  if ( found )
    return NoError ;
  else
    return UnknownClass ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
bool Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  ensure_unique() const
{
  return _ensure_unique ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  set_ensure_unique(bool ensure)
{
  if ( _is_emitting )
    return IsEmitting ;
  if ( ensure == _ensure_unique )
    return NoError ;
  _ensure_unique = ensure ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  enforce_unique()
{
  if ( _is_emitting )
    return IsEmitting ;
  typename Storage::iterator e = this->end() ;
  typename Storage::iterator i = this->begin() ;
  SlotsList tmp_store ;
  const unsigned nb_conn = nb_connected() ;
  unsigned nb_done = 0 ;
  while ( (i != e) && (nb_done < nb_conn) )
  {
    if ( (*i) != 0 )
    {
      typename SlotsList::iterator i2 =
        find_equal(tmp_store.begin(), tmp_store.end(), *i) ;
      if ( i2 == tmp_store.end() )
        tmp_store.push_back(*i) ;
      ++nb_done ;
    }
    ++i ;
  }
  this->clear() ;
  const typename SlotsList::const_iterator tmp_e = tmp_store.end() ;
  typename SlotsList::const_iterator tmp_i = tmp_store.begin() ;
  while ( tmp_i != tmp_e )
    insert(*(tmp_i++)) ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
unsigned Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  nb_connected() const
{
  return Storage::stored() ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
size_t Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  capacity() const
{
  return Storage::capacity() ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  connect (Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sig)
{
  if ( _is_emitting )
    return IsEmitting ;
  if ( sig == 0 )
    return NullSignal ;
  if ( _chained_signals.insert(sig).second )
    sig->chain_from(this) ;
  else
    return KnownSignal ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  disconnect (Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sig)
{
  if ( _is_emitting )
    return IsEmitting ;
  if ( sig == 0 )
    return NullSignal ;
  if ( _chained_signals.erase(sig) > 0 )
    sig->unchain_from(this) ;
  else
    return UnknownSignal ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
void Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  chain_from(Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sig)
{
  if ( sig == 0 )
    return ;
  _chained_from.insert(sig) ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
void Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  unchain_from(Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* sig)
{
  if ( sig == 0 )
    return ;
  _chained_from.erase(sig) ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  connect (global_slot_t f)
{
  if ( _is_emitting )
    return IsEmitting ;
  if ( f == 0 )
    return NullGlobalFct ;
  if ( _ensure_unique )
  {
    typename Storage::iterator i =
      find_match(this->begin(), this->end(), (void*)0, f, (SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*)0) ;
    if ( i != this->end() )
      return KnownGlobalFct ;
  }
  SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* slot =
    new SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>(f) ;
  if ( insert(slot) )
    return NoError ;
  else
  {
    delete slot ;
    return KnownGlobalFct ;
  }
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _CLASS_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  connect (_CLASS_TYPE_* in_class)
{
  return connect (in_class, &_CLASS_TYPE_::operator()) ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _CLASS_TYPE_, class _PARENT_CLASS_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  connect (_CLASS_TYPE_* in_class,
              _RETURN_TYPE_ (_PARENT_CLASS_::*method)(_ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_))
{
  _PARENT_CLASS_* parent_class = dynamic_cast<_PARENT_CLASS_*>(in_class) ;
  if ( parent_class != 0 )
    return connect_gen (parent_class, method) ;
  else
    return DynCastFailed ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _CLASS_TYPE_, class _PARENT_CLASS_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  connect (_CLASS_TYPE_* in_class,
              _RETURN_TYPE_ (_PARENT_CLASS_::*method)(_ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_) const)
{
  _PARENT_CLASS_* parent_class = dynamic_cast<_PARENT_CLASS_*>(in_class) ;
  if ( parent_class != 0 )
    return connect_gen (parent_class, method) ;
  else
    return DynCastFailed ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  disconnect (global_slot_t f)
{
  if ( _is_emitting )
    return IsEmitting ;
  if ( f == 0 )
    return NullGlobalFct ;
  typename Storage::iterator i =
    find_match(this->begin(), this->end(), (void*)0, f, (SlotGlobal6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*)0) ;
  if ( i == this->end() )
    return UnknownGlobalFct ;
  delete *i ;
  erase(i) ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _CLASS_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  disconnect (_CLASS_TYPE_* in_class)
{
  return disconnect(in_class, &_CLASS_TYPE_::operator()) ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _CLASS_TYPE_, class _PARENT_CLASS_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  disconnect (_CLASS_TYPE_* in_class,
                  _RETURN_TYPE_ (_PARENT_CLASS_::*methode)(_ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_))
{ _PARENT_CLASS_* parent_class = dynamic_cast<_PARENT_CLASS_*>(in_class) ;
  if ( parent_class != 0 )
    return disconnect_gen (parent_class, methode) ;
  else
    return DynCastFailed ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _CLASS_TYPE_, class _PARENT_CLASS_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  disconnect (_CLASS_TYPE_* in_class,
                  _RETURN_TYPE_ (_PARENT_CLASS_::*methode)(_ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_) const)
{ _PARENT_CLASS_* parent_class = dynamic_cast<_PARENT_CLASS_*>(in_class) ;
  if ( parent_class != 0 )
    return disconnect_gen (parent_class, methode) ;
  else
    return DynCastFailed ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
bool Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  is_emitting() const
{
  return _is_emitting ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  run(typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const
{
  if ( _is_emitting )
    return IsEmitting ;
  _is_emitting = true ;
  // First calls chained signals
  const typename SignalsSet::const_iterator se = _chained_signals.end() ;
  typename SignalsSet::const_iterator si = _chained_signals.begin() ;
  while ( si != se )
  {
    if ( (*si) != 0 )
      (*si)->run(arg0, arg1, arg2, arg3, arg4, arg5) ;
    ++si ;
  }
  // Then calls slots
  const typename Storage::const_iterator e = this->end() ;
  typename Storage::const_iterator i = this->begin() ;
  while ( i != e )
  {
    if ( (*i) != 0 )
      (*i)->run(arg0, arg1, arg2, arg3, arg4, arg5) ;
    ++i ;
  }
  _is_emitting = false ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _ACCUMULATOR_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  run(_ACCUMULATOR_& accum, typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const
{
  if ( _is_emitting )
    return IsEmitting ;
  _is_emitting = true ;
  // First calls chained signals
  const typename SignalsSet::const_iterator se = _chained_signals.end() ;
  typename SignalsSet::const_iterator si = _chained_signals.begin() ;
  while ( si != se )
  {
    if ( (*si) != 0 )
      (*si)->run(accum, arg0, arg1, arg2, arg3, arg4, arg5) ;
    ++si ;
  }
  // Then calls slots
  const typename Storage::const_iterator e = this->end() ;
  typename Storage::const_iterator i = this->begin() ;
  while ( i != e )
  {
    if ( (*i) != 0 )
      accum((*i)->run(arg0, arg1, arg2, arg3, arg4, arg5)) ;
    ++i ;
  }
  _is_emitting = false ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _PREDICATE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  run_if(_PREDICATE_& pred, typename Type2Param<_ARG0_TYPE_>::ParamType arg0, typename Type2Param<_ARG1_TYPE_>::ParamType arg1, typename Type2Param<_ARG2_TYPE_>::ParamType arg2, typename Type2Param<_ARG3_TYPE_>::ParamType arg3, typename Type2Param<_ARG4_TYPE_>::ParamType arg4, typename Type2Param<_ARG5_TYPE_>::ParamType arg5) const
{
  if ( _is_emitting )
    return IsEmitting ;
  _is_emitting = true ;
  // First calls chained signals
  const typename SignalsSet::const_iterator se = _chained_signals.end() ;
  typename SignalsSet::const_iterator si = _chained_signals.begin() ;
  while ( si != se )
  {
    if ( (*si) != 0 )
      if ( (*si)->run_if(pred, arg0, arg1, arg2, arg3, arg4, arg5) == EmitInterrupted )
      {
        _is_emitting = false ;
        return EmitInterrupted ;
      }
    ++si ;
  }
  // Then calls slots
  const typename Storage::const_iterator e = this->end() ;
  typename Storage::const_iterator i = this->begin() ;
  while ( i != e )
  {
    if ( (*i) != 0 )
    {
      if ( ! pred((*i)->run(arg0, arg1, arg2, arg3, arg4, arg5)) )
      {
        _is_emitting = false ;
        return EmitInterrupted ;
      }
    }
    ++i ;
  }
  _is_emitting = false ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
void Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  slots_set_deleted (SlotsSetBase* ssb)
{
  if ( ssb == 0 )
    return ;
  typename Storage::iterator i = this->begin() ;
  while ( i != this->end() )
  {
    if ( (*i) != 0 )
    {
      if ( (*i)->in_base() == ssb )
      {
        delete *i ;
        i = erase(i) ;
      }
      else
        ++i ;
    }
    else
      ++i ;
  }
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _CLASS_TYPE_, typename _METHOD_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  connect_gen (_CLASS_TYPE_* in_class,
                  _METHOD_TYPE_ method)
{
  if ( _is_emitting )
    return IsEmitting ;
  if ( in_class == 0 )
    return NullInstance ;
  if ( _ensure_unique )
  {
    typename Storage::iterator i =
      find_match(this->begin(), this->end(), in_class, method,
      (SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*)0) ;
    if ( i != this->end() )
      return KnownSlot ;
  }
  SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* slot =
    new SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>(in_class, method) ;
  if ( insert(slot) )
  {
    SlotsSetBase* ssb = dynamic_cast<SlotsSetBase*>(in_class) ;
    if ( ssb != 0 )
      ssb->connect_from(this) ;
    else
    {
      UnmanagedConnections::instance()->insert(in_class, this) ;
      ++_nb_unmanaged_connect ;
    }
    return NoError ;
  }
  else
  {
    delete slot ;
    return KnownSlot ;
  }
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
template <class _CLASS_TYPE_, typename _METHOD_TYPE_>
SlotSigErrors Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  disconnect_gen (_CLASS_TYPE_* in_class,
                    _METHOD_TYPE_ method)
{
  if ( _is_emitting )
    return IsEmitting ;
  if ( in_class == 0 )
    return NullInstance ;
  typename Storage::iterator i =
    find_match(this->begin(), this->end(), in_class, method,
    (SlotInClass6<_CLASS_TYPE_, _RETURN_TYPE_, _METHOD_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>*)0) ;
  if ( i == this->end() )
    return UnknownSlot ;
  SlotsSetBase* ssb = dynamic_cast<SlotsSetBase*>(in_class) ;
  if ( ssb != 0 )
    ssb->disconnect_from(this) ;
  else
  {
    UnmanagedConnections::instance()->erase(in_class, this) ;
    --_nb_unmanaged_connect ;
  }
  delete *i ;
  erase(i) ;
  return NoError ;
}

template <typename _RETURN_TYPE_, typename _ARG0_TYPE_, typename _ARG1_TYPE_, typename _ARG2_TYPE_, typename _ARG3_TYPE_, typename _ARG4_TYPE_, typename _ARG5_TYPE_>
void Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>::
  clone_from(const Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>& sig)
{
  if ( _is_emitting )
    return ;
  typedef Sig6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_> other_type ;
  disconnect_all() ;
  const typename other_type::const_iterator e = sig.end() ;
  typename other_type::const_iterator i = sig.begin() ;
  while ( i != e )
  {
    if ( (*i) != 0 )
    {
      Slot6<_RETURN_TYPE_, _ARG0_TYPE_, _ARG1_TYPE_, _ARG2_TYPE_, _ARG3_TYPE_, _ARG4_TYPE_, _ARG5_TYPE_>* new_slot = (*i)->clone() ;
      if ( new_slot != 0 )
      {
        if ( insert(new_slot) )
        {
          SlotsSetBase* ssb = new_slot->in_base() ;
          if ( ssb != 0 )
            ssb->connect_from(this) ;
          else
          {
            UnmanagedConnections::instance()->insert(new_slot->in_class_void(), this) ;
            ++_nb_unmanaged_connect ;
          }
        }
        else
          delete new_slot ;
      }
    }
    ++i ;
  }
  // the chained signals
  const typename SignalsSet::const_iterator se = sig._chained_signals.end() ;
  typename SignalsSet::const_iterator si = sig._chained_signals.begin() ;
  set_ensure_unique(sig.ensure_unique()) ;
  while ( si != se )
  {
    connect (*si) ;
    ++si ;
  }
}

} // namespace SlotSig

#endif // __SLOTSIG_6_H__
