#include <algorithm>
#include <cstddef>
#include <iostream>
#include <type_traits>

template <typename T_ = void>
struct S
{
    using T = T_;
};

template <typename T_>
struct O0;
template <typename T_>
using o0 = typename O0<T_>::T;
template <typename T_>
struct O0
{
    using T = typename T_::T;
};

template <typename T1_, typename T2_>
struct O1;
template <typename T1_, typename T2_>
using o1 = typename O1<T1_, T2_>::T;
template <typename T1_, typename T2_>
struct O1
{
    using T = o1<S<T1_>, o0<T2_>>;
};
template <typename T1_>
struct O1<T1_, void>
{
    using T = T1_;
};

template <typename T1_, typename T2_>
struct O2;
template <typename T1_, typename T2_>
using o2 = typename O2<T1_, T2_>::T;
template <typename T1_, typename T2_>
struct O2
{
    using T = o1<o2<T1_, o0<T2_>>, T1_>;
};
template <typename T1_>
struct O2<T1_, void>
{
    using T = void;
};

template <typename T1_, typename T2_>
struct O4;
template <typename T1_, typename T2_>
using o4 = typename O4<T1_, T2_>::T;
template <typename T1_, typename T2_>
struct O4
{
    using T = o4<o0<T1_>, o0<T2_>>;
};
template <typename T1_>
struct O4<T1_, void>
{
    using T = T1_;
};
template <typename T2_>
struct O4<void, T2_>
{
    using T = void;
};
template <>
struct O4<void, void>
{
    using T = void;
};

template <typename T1_, typename T2_>
struct O5;
template <typename T1_, typename T2_>
using o5 = typename O5<T1_, T2_>::T;
template <typename T1_, typename T2_>
struct O5
{
    using T = std::conditional_t<
        std::is_same_v<o4<T1_, T2_>, void>,
        std::conditional_t<std::is_same_v<T1_, T2_>, void, T1_>,
        o5<o4<T1_, T2_>, T2_>>;
};
template <typename T2_>
struct O5<void, T2_>
{
    using T = void;
};

template <typename T1_, typename T2_, typename T3_>
struct O3;
template <typename T1_, typename T2_, typename T3_>
using o3 = typename O3<T1_, T2_, T3_>::T;
template <typename T1_, typename T2_, typename T3_>
struct O3
{
    using T = o5<o2<o3<T1_, o0<T2_>, T3_>, T1_>, T3_>;
};
template <typename T1_, typename T3_>
struct O3<T1_, void, T3_>
{
    using T = S<>;
};

template <typename... Ts_>
struct V;
template <>
struct V<>
{
};
template <typename T_, typename... Ts_>
struct V<T_, V<Ts_...>>
{
    using T = T_;
    using Ts = V<Ts_...>;
};

template <typename T1_, typename T2_, typename T3_>
struct O6;
template <typename T1_, typename T2_, typename T3_>
using o6 = typename O6<T1_, T2_, T3_>::T;
template <typename T1_, typename T2_, typename T3_>
struct O6
{
    using T = o5<o1<o2<typename T1_::T, typename T2_::T>,
                    o6<typename T1_::Ts, typename T2_::Ts, T3_>>,
                 T3_>;
};
template <typename T3_>
struct O6<V<>, V<>, T3_>
{
    using T = void;
};

template <typename T_>
struct R;
template <typename T_>
using r = typename R<T_>::T;
template <>
struct R<V<>>
{
    using T = V<>;
};
template <typename T_>
struct R<V<T_, V<>>>
{
    using T = V<T_, V<>>;
};
template <typename T1_, typename T2_, typename T3_>
struct R<V<T1_, V<T2_, T3_>>>
{
    using T = V<T2_, r<V<T1_, T3_>>>;
};

template <typename T1_, typename T2_, typename T3_>
struct TV;
template <typename T1_, typename T2_, typename T3_>
using tv = typename TV<T1_, T2_, T3_>::T;
template <typename T1_, typename T2_, typename T3_>
struct TV
{
    using T = r<V<o3<T1_, o0<T3_>, T2_>, tv<T1_, T2_, o0<T3_>>>>;
};
template <typename T1_, typename T2_>
struct TV<T1_, T2_, void>
{
    using T = V<>;
};

template <typename T1_, typename T2_, typename T3_, typename T4_, typename T5_>
struct TT;
template <typename T1_, typename T2_, typename T3_, typename T4_, typename T5_>
using tt = typename TT<T1_, T2_, T3_, T4_, T5_>::T;
template <typename T1_, typename T2_, typename T3_, typename T4_, typename T5_>
struct TT
{
    using T = r<V<o6<T1_, tv<o3<T2_, o0<T5_>, T3_>, T3_, T4_>, T3_>,
                  tt<T1_, T2_, T3_, T4_, o0<T5_>>>>;
};
template <typename T1_, typename T2_, typename T3_, typename T4_>
struct TT<T1_, T2_, T3_, T4_, void>
{
    using T = V<>;
};
template <typename T1_, typename T2_, typename T3_, typename T4_>
using tt2 = tt<T1_, T2_, T3_, T4_, T4_>;

template <std::size_t N_>
struct String
{
    constexpr static auto const N{N_};
    char str[N]{};
    char suffix[N - 1]{};
    constexpr String(char const (&str)[N_])
    {
        std::copy(std::cbegin(str), std::cend(str), std::begin(this->str));
        std::copy(std::cbegin(str) + 1, std::cend(str), std::begin(suffix));
    }
};

using B = S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>;
using W = S<S<S<>>>;
using P = S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>;
using N = o0<P>;
using E = V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>, V<S<S<S<>>>, V<void, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<>>>>>>>>, V<void, V<void, V<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>, V<S<S<S<>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>, V<S<S<S<>>>, V<S<S<S<S<S<>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>, V<void, V<S<>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>, V<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<S<>>>>>>>>>>>>>>>>>>>>>>>>>>>>, V<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>;

template <char V>
struct C;
template <char V>
using c = typename C<V>::T;
template <char V>
struct C
{
    using T = S<c<V - 1>>;
};
template <>
struct C<0>
{
    using T = void;
};

template <std::size_t N, String<N> S>
struct String2;
template <String S>
using string2 = typename String2<S.N, S>::T;
template <std::size_t N, String<N> S>
struct String2
{
    using T = V<o4<c<S.str[0]>, B>, string2<String<N - 1>{S.suffix}>>;
};
template <String<2> S>
struct String2<2, S>
{
    using T = V<o4<c<S.str[0]>, B>, V<>>;
};

template <String S>
constexpr std::string operator""_flag()
{
    if constexpr (std::same_as<tt2<string2<S>, W, P, N>, E>)
    {
        return "Lay Harder";
    }
    else
    {
        return "Try Harder";
    }
}

int main()
{
    std::cout << "flag{????????????????????????}"_flag << std::endl;
}
