
/*
  This fixes the ugly line-number bug in boost
  found at: https://svn.boost.org/trac/boost/attachment/ticket/2569/boost_serialization.patch
 */

#include <boost/version.hpp>

#if (BOOST_VERSION / 100 % 1000 < 38) && (BOOST_VERSION / 100 % 1000 > 35)



#undef BOOST_CLASS_EXPORT_GUID
#define BOOST_CLASS_EXPORT_GUID(T, K)                                   \
	namespace                                                           \
	{                                                                   \
	   template< typename U >                                           \
	   class init_guid;                                                 \
	   template<>                                                       \
	   class init_guid<T>                                               \
	   {                                                                \
	       static ::boost::archive::detail::guid_initializer<T> const & \
	       guid_initializer_;                                           \
	   };                                                               \
	   ::boost::archive::detail::guid_initializer<T> const &            \
	       init_guid<T>::guid_initializer_ =                            \
	           ::boost::serialization::singleton<                       \
	               ::boost::archive::detail::guid_initializer<T>        \
	           >::get_mutable_instance().export_guid(K);                \
	} 


#endif
