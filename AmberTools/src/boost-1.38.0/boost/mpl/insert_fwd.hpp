
#ifndef BOOST_MPL_INSERT_FWD_HPP_INCLUDED
#define BOOST_MPL_INSERT_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: insert_fwd.hpp,v 1.1 2010/03/29 19:06:02 peters Exp $
// $Date: 2010/03/29 19:06:02 $
// $Revision: 1.1 $

namespace boost { namespace mpl {

template< typename Tag > struct insert_impl;
template< typename Sequence, typename Pos_or_T, typename T > struct insert;

}}

#endif // BOOST_MPL_INSERT_FWD_HPP_INCLUDED