
/*
 * slotsig_storage_policies.h header file
 *
 * Part of the SlogSig project, an attempt to provide a type-safe
 * signals/slots mechanism for the C++ language.
 * This file provides storage policies to customize behaviours of signals/slots.
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

#include <set>
#include <vector>
#include <algorithm>

namespace SlotSig
{

template <typename _ITERATOR_TYPE_,
          typename _STORED_TYPE_>
_ITERATOR_TYPE_ find_equal(_ITERATOR_TYPE_ begin, _ITERATOR_TYPE_ end, _STORED_TYPE_ v)
{
  _ITERATOR_TYPE_ i = begin ;
  while ( i != end )
  {
    if ( (*i) != 0 )
      if ( (*i)->equals(v) )
        return i ;
    ++i ;
  }
  return end ;
}


template <typename _ITERATOR_TYPE_, 
          class _CLASS_TYPE_, 
          typename _METHOD_TYPE_, 
          class _TRUE_TYPE_>
_ITERATOR_TYPE_ find_match(_ITERATOR_TYPE_ begin, 
                     _ITERATOR_TYPE_ end, 
                     _CLASS_TYPE_* in_class, 
                     _METHOD_TYPE_ m, 
                     _TRUE_TYPE_* dummy)
{
  _ITERATOR_TYPE_ i = begin ;
  while ( i != end )
  {
    if ( (*i) != 0 )
    {
      _TRUE_TYPE_* tt = static_cast<_TRUE_TYPE_*>(*i) ;
      if ( tt != 0 )
        if ( tt->matches(in_class, m) )
          return i ;
    }
    ++i ;
  }
  return end ;
}

//! The class used to store slots
template <typename _STORED_TYPE_>
class SimpleStorage
{
  public:
    typedef typename std::vector<_STORED_TYPE_> storage_t ;
    typedef typename storage_t::const_iterator const_iterator ;
    typedef typename storage_t::iterator iterator ;

    SimpleStorage() :
      storage(),
      nb_stored(0)
    {
      free_place = end() ;
    }
    
    ~SimpleStorage()
    { }

    const_iterator begin() const
    { return storage.begin() ; }
    iterator begin()
    { return storage.begin() ; }
    const_iterator end() const
    { return storage.end() ; }
    iterator end()
    { return storage.end() ; }

    size_t capacity() const
    { return storage.size() ; }

    unsigned stored() const
    { return nb_stored ; }

  protected:
    void clear()
    {
      std::fill(begin(), end(), (_STORED_TYPE_)0) ;
      nb_stored = 0 ;
      free_place = begin() ;
    }

    bool insert(_STORED_TYPE_ v)
    {
      if ( nb_stored == storage.size() )
      {
        storage.resize(nb_stored+(nb_stored>>1)+1, 0) ;
        free_place = end() ;
      }
      iterator place = find_free_place() ;
      const iterator e = end() ;
      if ( place == e )
      {
        storage.push_back(v) ;
      }
      else
      {
        *place = v ;
        free_place = ++place ;
        if ( (free_place != e) && ((*free_place) != 0) )
          free_place = e ;
      }
      ++nb_stored ;
      return true ;
    }

    iterator erase(iterator iter)
    {
      if ( iter == end() )
        return iter ;
      *iter = 0 ;
      free_place = iter ;
      --nb_stored ;
      return iter+1 ;
    }

    iterator find_free_place()
    {
      const iterator e = end() ;
      if ( free_place == e )
      {
        free_place = begin() ;
        while ( (free_place != e) && (*free_place != 0) )
          ++free_place ;
      }
      return free_place ;
    }

  private:
    storage_t storage ;
    unsigned nb_stored ;
    iterator free_place ;
} ; // class SimpleStorage<>

} // namespace SlotSig
