#pragma once

#include <tuple>
#include <TMP_Utils.hpp>

using namespace std;

    template<typename... T>
    struct ParamPack
    {
        //typedef tuple<T...> to_tuple;

        //const tuple<T...> as_tuple = { T()... };
        static const size_t size = sizeof...(T);

        template<typename Ty>
        static array<Ty, size> As_Array()
        {
            return{ T()... };
        }
    };
      // Get i-th element of parameter pack
      // AKA 'implementation'
      // Principle: the element i is the first pack_element of the sub-array starting at indice i-1
    template<int n, typename F, typename... T>
    struct pack_element_at : public pack_element_at<n - 1, T...>
    {};

    template<typename F, typename... T>
    struct pack_element_at<0, F, T...>
    {
        typedef F type;
    };

    // Get i-th element of pack
    // AKA 'interface' for the 'pack' structure
    template<int n, typename P>
    struct pack_element
    {};

    template<int n, typename... T>
    struct pack_element<n, ParamPack<T...>>
    {
        typedef typename pack_element_at<n, T...>::type type;
    };

    // Concat at left (only for structure 'pack')
    template<typename a, typename b>
    struct paramPack_concat_left
    {};

    template<typename a, typename... b>
    struct paramPack_concat_left<a, ParamPack<b...>>
    {
        typedef ParamPack<a, b...> type;
    };

    // Concat 2 BandPacks
    template<typename a, typename b, int n = 0, bool ok = (n < a::size)>
      struct paramPack_concat : public paramPack_concat<a, b, n + 1>
      {
          typedef typename paramPack_concat_left<
              typename pack_element<n, a>::type,
              typename paramPack_concat<a, b, n + 1>::type
          >::type type;
      };

      template<typename a, typename b, int n>
      struct paramPack_concat<a, b, n, false>
      {
          typedef b type;
      };
