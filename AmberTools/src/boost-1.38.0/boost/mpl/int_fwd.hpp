
#ifndef BOOST_MPL_INT_FWD_HPP_INCLUDED
#define BOOST_MPL_INT_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: int_fwd.hpp,v 1.1 2010/03/29 19:06:02 peters Exp $
// $Date: 2010/03/29 19:06:02 $
// $Revision: 1.1 $

#include <boost/mpl/aux_/adl_barrier.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< BOOST_MPL_AUX_NTTP_DECL(int, N) > struct int_;

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
BOOST_MPL_AUX_ADL_BARRIER_DECL(int_)

#endif // BOOST_MPL_INT_FWD_HPP_INCLUDED