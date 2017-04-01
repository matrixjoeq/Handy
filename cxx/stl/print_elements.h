
#ifndef __HANDY_CXX_STL_PRINT_ELEMENTS_H
#define __HANDY_CXX_STL_PRINT_ELEMENTS_H

namespace handy {

/**
 * print elements in a STL container to output stream with optional seperator
 */
template <class Container, class OStream>
inline void print_elements(const Container& c, OStream& os, const char* sep = " ")
{
    typename Container::const_iterator iter;

    for (iter = c.begin(); iter != c.end(); ++iter) {
        os << *iter << sep;
    }

    os << '\n';
}

} // namespace handy

#endif // __HANDY_CXX_STL_PRINT_ELEMENTS_H
