#ifndef JEGP_STRING_REF_HPP
#define JEGP_STRING_REF_HPP

#include <iterator> // reverse_iterator
#include <string>   // char_traits
#include <string_view>
#include <type_traits> // enable_if, is_constructible, is_nothrow_constructible

namespace jegp {

template <class charT, class traits = std::char_traits<charT>>
class Basic_string_ref : public std::basic_string_view<charT, traits> {
private:
    using Base = std::basic_string_view<charT, traits>;

    constexpr Basic_string_ref(Base) noexcept;

public:
    using typename Base::pointer;
    using typename Base::reference;
    using iterator               = pointer;
    using const_iterator         = iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = reverse_iterator;
    using typename Base::size_type;

    constexpr Basic_string_ref() noexcept = default;
    constexpr Basic_string_ref(charT* str);
    constexpr Basic_string_ref(charT* str, size_type len);

    template <
        class T, class = std::enable_if_t<std::is_constructible_v<T, Base>>>
    explicit constexpr operator T() const
        noexcept(std::is_nothrow_constructible_v<T, Base>);

    constexpr iterator begin() const noexcept;
    constexpr iterator end() const noexcept;
    constexpr iterator cbegin() const noexcept;
    constexpr iterator cend() const noexcept;

    constexpr reverse_iterator rbegin() const noexcept;
    constexpr reverse_iterator rend() const noexcept;
    constexpr reverse_iterator crbegin() const noexcept;
    constexpr reverse_iterator crend() const noexcept;

    constexpr reference operator[](size_type pos) const;
    constexpr reference at(size_type pos) const;

    constexpr reference front() const;
    constexpr reference back() const;

    constexpr pointer data() const noexcept;

    constexpr Basic_string_ref
    substr(size_type pos = 0, size_type n = Base::npos) const;
};

using String_ref    = Basic_string_ref<char>;
using u16String_ref = Basic_string_ref<char16_t>;
using u32String_ref = Basic_string_ref<char32_t>;
using wString_ref   = Basic_string_ref<wchar_t>;

} // namespace jegp

//------------------------------------------------------------------------------
// "String_ref.ipp" ------------------------------------------------------------
//------------------------------------------------------------------------------

namespace jegp {

template <class C, class T>
constexpr Basic_string_ref<C, T>::Basic_string_ref(Base b) noexcept : Base{b}
{
}

// Construction ----------------------------------------------------------------

template <class charT, class T>
constexpr Basic_string_ref<charT, T>::Basic_string_ref(charT* str) : Base{str}
{
}
template <class charT, class T>
constexpr Basic_string_ref<charT, T>::Basic_string_ref(
    charT* str, size_type len)
  : Base{str, len}
{
}

template <class C, class T>
template <class U, class>
constexpr Basic_string_ref<C, T>::operator U() const
    noexcept(std::is_nothrow_constructible_v<U, Base>)
{
    return U{static_cast<Base>(*this)};
}

// Iterator support ------------------------------------------------------------

template <class C, class T>
constexpr auto Basic_string_ref<C, T>::begin() const noexcept -> iterator
{
    return data();
}
template <class C, class T>
constexpr auto Basic_string_ref<C, T>::cbegin() const noexcept -> iterator
{
    return begin();
}

template <class C, class T>
constexpr auto Basic_string_ref<C, T>::end() const noexcept -> iterator
{
    return begin() + Base::size();
}
template <class C, class T>
constexpr auto Basic_string_ref<C, T>::cend() const noexcept -> iterator
{
    return end();
}

template <class C, class T>
constexpr auto Basic_string_ref<C, T>::rbegin() const noexcept
    -> reverse_iterator
{
    return reverse_iterator{end()};
}
template <class C, class T>
constexpr auto Basic_string_ref<C, T>::crbegin() const noexcept
    -> reverse_iterator
{
    return rbegin();
}

template <class C, class T>
constexpr auto Basic_string_ref<C, T>::rend() const noexcept -> reverse_iterator
{
    return reverse_iterator{begin()};
}
template <class C, class T>
constexpr auto Basic_string_ref<C, T>::crend() const noexcept
    -> reverse_iterator
{
    return rend();
}

// Element access --------------------------------------------------------------

template <class C, class T>
constexpr auto Basic_string_ref<C, T>::operator[](size_type pos) const
    -> reference
{
    return const_cast<reference>(Base::operator[](pos));
}
template <class C, class T>
constexpr auto Basic_string_ref<C, T>::at(size_type pos) const -> reference
{
    return const_cast<reference>(Base::at(pos));
}

template <class C, class T>
constexpr auto Basic_string_ref<C, T>::front() const -> reference
{
    return const_cast<reference>(Base::front());
}
template <class C, class T>
constexpr auto Basic_string_ref<C, T>::back() const -> reference
{
    return const_cast<reference>(Base::back());
}

template <class C, class T>
constexpr auto Basic_string_ref<C, T>::data() const noexcept -> pointer
{
    return const_cast<pointer>(Base::data());
}

// String operations -----------------------------------------------------------

template <class C, class T>
constexpr auto Basic_string_ref<C, T>::substr(size_type pos, size_type n) const
    -> Basic_string_ref
{
    return Base::substr(pos, n);
}

} // namespace jegp

#endif // JEGP_STRING_REF_HPP