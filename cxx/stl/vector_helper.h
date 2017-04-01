

#ifndef __HANDY_CXX_STL_VECTOR_HELPER_H
#define __HANDY_CXX_STL_VECTOR_HELPER_H

#include <vector>

namespace handy {

template <class T>
inline typename std::vector<T>::iterator erase_first(std::vector<T>& v, const T& value)
{
    typedef typename std::vector<T>::iterator iter_type;
    iter_type iter = std::find(v.begin(), v.end(), value);
    return iter == v.end() ? iter : v.erase(iter);
}

template <class T>
inline void erase_all(std::vector<T>& v, const T& value)
{
    v.erase(std::remove(v.begin(), v.end(), value), v.end());
}

} // namespace handy
#endif // __HANDY_CXX_STL_VECTOR_HELPER_H
