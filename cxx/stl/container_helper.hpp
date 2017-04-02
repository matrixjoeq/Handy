

#ifndef __HANDY_CXX_STL_CONTAINER_HELPER_H
#define __HANDY_CXX_STL_CONTAINER_HELPER_H

#include <algorithm>
#include <map>


namespace handy {

/**
 * print elements in a STL Sequence to output stream with optional seperator
 */
template <class Sequence, class OStream>
inline void print_elements(const Sequence& c, OStream& os, const char* sep = " ")
{
    typename Sequence::const_iterator iter;

    for (iter = c.begin(); iter != c.end(); ++iter) {
        os << *iter << sep;
    }

    os << '\n';
}

/**
 * erase the first element which value equals to specific one
 */
template <class Sequence, class T>
inline typename Sequence::iterator erase_first(Sequence& seq, const T& value)
{
    typename Sequence::iterator iter = std::find(seq.begin(), seq.end(), value);
    return (iter == seq.end() ? iter : seq.erase(iter));
}

template <class Key, class Value>
inline typename std::map<Key, Value>::iterator erase_first(std::map<Key, Value>& map, const Value& value)
{
	for (typename std::map<Key, Value>::iterator iter = map.begin(); iter != map.end(); ++iter) {
		if (iter->second == value) {
#if (__cplusplus < 201103L) // C++ 98
			map.erase(iter++);
			return iter;
#else
			return map.erase(iter);
#endif
		}
	}
	
	return map.end();
}

template <class Key, class Value>
inline typename std::multimap<Key, Value>::iterator erase_first(std::multimap<Key, Value>& map, const Value& value)
{
	for (typename std::multimap<Key, Value>::iterator iter = map.begin(); iter != map.end(); ++iter) {
		if (iter->second == value) {
#if (__cplusplus < 201103L) // C++ 98
			map.erase(iter++);
			return iter;
#else
			return map.erase(iter);
#endif
		}
	}
	
	return map.end();
}

/**
 * erase all the elements whose value equal to specific one
 */
template <class Sequence, class T>
inline void erase_all(Sequence& seq, const T& value)
{
    seq.erase(std::remove(seq.begin(), seq.end(), value), seq.end());
}

template <class Key, class Value>
inline void erase_all(std::map<Key, Value>& map, const Value& value)
{
	for (typename std::map<Key, Value>::iterator iter = map.begin(); iter != map.end(); ) {
		if (iter->second == value) {
			map.erase(iter++);
		}
		else {
			++iter;
		}
	}
}

template <class Key, class Value>
inline void erase_all(std::multimap<Key, Value>& map, const Value& value)
{
	for (typename std::multimap<Key, Value>::iterator iter = map.begin(); iter != map.end(); ) {
		if (iter->second == value) {
			map.erase(iter++);
		}
		else {
			++iter;
		}
	}
}

} // namespace handy
#endif // __HANDY_CXX_STL_CONTAINER_HELPER_H
