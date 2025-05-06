#ifndef ADAPTERS_H
#define ADAPTERS_H

#include <iterator>
#include <utility>
#include <type_traits>

// Вспомогательные метафункции
template<typename T> struct is_pair : std::false_type {};
template<typename K, typename V> struct is_pair<std::pair<K, V>> : std::true_type {};
template<typename T> inline constexpr bool is_pair_v = is_pair<T>::value;

// Оператор конвейера
template<typename Range, typename Adapter>
auto operator|(Range&& range, Adapter&& adapter) {
    return std::forward<Adapter>(adapter)(std::forward<Range>(range));
}

// Базовый класс итератора
template<typename Derived, typename Value>
struct IteratorBase {
    using iterator_category = std::input_iterator_tag;
    using value_type = Value;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;
};

// Filter Adapter
template<typename Range, typename Pred>
class FilterAdapter {
    Range range_;
    Pred pred_;

public:
    class Iterator : public IteratorBase<Iterator, typename std::remove_reference_t<
        decltype(*std::begin(std::declval<Range&>()))>> {

        using BaseIter = decltype(std::begin(std::declval<Range&>()));
        BaseIter current_;
        BaseIter end_;
        Pred pred_;

        void advance() {
            while(current_ != end_ && !pred_(*current_)) ++current_;
        }

    public:
        Iterator(BaseIter begin, BaseIter end, Pred pred)
            : current_(begin), end_(end), pred_(std::move(pred)) { advance(); }

        auto& operator++() { ++current_; advance(); return *this; }
        auto operator*() const { return *current_; }

        bool operator==(const Iterator& other) const { return current_ == other.current_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    FilterAdapter(Range range, Pred pred)
        : range_(std::forward<Range>(range)), pred_(std::move(pred)) {}

    auto begin() const { return Iterator(std::begin(range_), std::end(range_), pred_); }
    auto end() const { return Iterator(std::end(range_), std::end(range_), pred_); }
};

struct Filter {
    template<typename Pred>
    auto operator()(Pred&& pred) const {
        return [p = std::forward<Pred>(pred)](auto&& range) {
            return FilterAdapter<decltype(range), std::decay_t<Pred>>(
                std::forward<decltype(range)>(range), std::move(p));
        };
    }
};

inline Filter filter;

// Transform Adapter
template<typename Range, typename Func>
class TransformAdapter {
    Range range_;
    Func func_;

public:
    class Iterator : public IteratorBase<Iterator, decltype(func_(*std::begin(std::declval<Range&>())))> {
        using BaseIter = decltype(std::begin(std::declval<Range&>()));
        BaseIter it_;
        Func func_;

    public:
        Iterator(BaseIter it, Func func) : it_(it), func_(std::move(func)) {}

        auto operator*() const { return func_(*it_); }
        Iterator& operator++() { ++it_; return *this; }

        bool operator==(const Iterator& other) const { return it_ == other.it_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    TransformAdapter(Range range, Func func)
        : range_(std::forward<Range>(range)), func_(std::move(func)) {}

    auto begin() const { return Iterator(std::begin(range_), func_); }
    auto end() const { return Iterator(std::end(range_), func_); }
};

struct Transform {
    template<typename Func>
    auto operator()(Func&& func) const {
        return [f = std::forward<Func>(func)](auto&& range) {
            return TransformAdapter<decltype(range), std::decay_t<Func>>(
                std::forward<decltype(range)>(range), std::move(f));
        };
    }
};

inline Transform transform;

// Take Adapter
template<typename Range>
class TakeAdapter {
    Range range_;
    size_t count_;

public:
    class Iterator : public IteratorBase<Iterator, typename std::remove_reference_t<
        decltype(*std::begin(std::declval<Range&>()))>> {

        using BaseIter = decltype(std::begin(std::declval<Range&>()));
        BaseIter it_;
        BaseIter end_;
        size_t remaining_;

    public:
        Iterator(BaseIter begin, BaseIter end, size_t remaining)
            : it_(begin), end_(end), remaining_(remaining) {}

        auto& operator++() {
            if(it_ != end_ && remaining_ > 0) {
                ++it_;
                --remaining_;
            }
            return *this;
        }

        auto operator*() const { return *it_; }

        bool operator==(const Iterator& other) const {
            return it_ == other.it_ && remaining_ == other.remaining_;
        }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    TakeAdapter(Range range, size_t count)
        : range_(std::forward<Range>(range)), count_(count) {}

    auto begin() const { return Iterator(std::begin(range_), std::end(range_), count_); }
    auto end() const { return Iterator(std::end(range_), std::end(range_), 0); }
};

struct Take {
    auto operator()(size_t count) const {
        return [count](auto&& range) {
            return TakeAdapter<decltype(range)>(std::forward<decltype(range)>(range), count);
        };
    }
};

inline Take take;

// Drop Adapter
template<typename Range>
class DropAdapter {
    Range range_;
    size_t count_;

public:
    class Iterator : public IteratorBase<Iterator, typename std::remove_reference_t<
        decltype(*std::begin(std::declval<Range&>()))>> {

        using BaseIter = decltype(std::begin(std::declval<Range&>()));
        BaseIter it_;
        BaseIter end_;

    public:
        Iterator(BaseIter it, BaseIter end) : it_(it), end_(end) {}

        auto& operator++() { ++it_; return *this; }
        auto operator*() const { return *it_; }

        bool operator==(const Iterator& other) const { return it_ == other.it_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    DropAdapter(Range range, size_t count)
        : range_(std::forward<Range>(range)), count_(count) {}

    auto begin() const {
        auto it = std::begin(range_);
        std::advance(it, std::min(count_, static_cast<size_t>(std::distance(it, std::end(range_)))));
        return Iterator(it, std::end(range_));
    }

    auto end() const {
        return Iterator(std::end(range_), std::end(range_));
    }
};

struct Drop {
    auto operator()(size_t count) const {
        return [count](auto&& range) {
            return DropAdapter<decltype(range)>(std::forward<decltype(range)>(range), count);
        };
    }
};

inline Drop drop;

// Reverse Adapter
template<typename Range>
class ReverseAdapter {
    Range range_;

    using BaseIter = decltype(std::begin(std::declval<Range&>()));
    static_assert(
        std::is_base_of_v<std::bidirectional_iterator_tag,
            typename std::iterator_traits<BaseIter>::iterator_category>,
        "Reverse requires bidirectional iterators"
    );

public:
    class Iterator : public IteratorBase<Iterator, typename std::remove_reference_t<
        decltype(*std::begin(std::declval<Range&>()))>> {

        using ReverseIter = std::reverse_iterator<BaseIter>;
        ReverseIter it_;

    public:
        Iterator(ReverseIter it) : it_(it) {}

        auto& operator++() { ++it_; return *this; }
        auto operator*() const { return *it_; }

        bool operator==(const Iterator& other) const { return it_ == other.it_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    ReverseAdapter(Range range) : range_(std::forward<Range>(range)) {}

    auto begin() const { return Iterator(std::rbegin(range_)); }
    auto end() const { return Iterator(std::rend(range_)); }
};

struct Reverse {
    auto operator()() const {
        return [](auto&& range) {
            return ReverseAdapter<decltype(range)>(std::forward<decltype(range)>(range));
        };
    }
};

inline Reverse reverse;

// Keys Adapter
template<typename Range>
class KeysAdapter {
    Range range_;

    static_assert(
        is_pair_v<typename std::remove_reference_t<
            decltype(*std::begin(std::declval<Range&>()))>>,
        "Keys requires a range of pairs"
    );

public:
    class Iterator : public IteratorBase<Iterator, typename std::remove_const_t<
        typename std::remove_reference_t<decltype(std::begin(std::declval<Range&>())->first)>>> {

        using BaseIter = decltype(std::begin(std::declval<Range&>()));
        BaseIter it_;

    public:
        Iterator(BaseIter it) : it_(it) {}

        auto& operator++() { ++it_; return *this; }
        auto operator*() const { return it_->first; }

        bool operator==(const Iterator& other) const { return it_ == other.it_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    KeysAdapter(Range range) : range_(std::forward<Range>(range)) {}

    auto begin() const { return Iterator(std::begin(range_)); }
    auto end() const { return Iterator(std::end(range_)); }
};

struct Keys {
    auto operator()() const {
        return [](auto&& range) {
            return KeysAdapter<decltype(range)>(std::forward<decltype(range)>(range));
        };
    }
};

inline Keys keys;

// Values Adapter
template<typename Range>
class ValuesAdapter {
    Range range_;

    static_assert(
        is_pair_v<typename std::remove_reference_t<
            decltype(*std::begin(std::declval<Range&>()))>>,
        "Values requires a range of pairs"
    );

public:
    class Iterator : public IteratorBase<Iterator, typename std::remove_const_t<
        typename std::remove_reference_t<decltype(std::begin(std::declval<Range&>())->second)>>> {

        using BaseIter = decltype(std::begin(std::declval<Range&>()));
        BaseIter it_;

    public:
        Iterator(BaseIter it) : it_(it) {}

        auto& operator++() { ++it_; return *this; }
        auto operator*() const { return it_->second; }

        bool operator==(const Iterator& other) const { return it_ == other.it_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    ValuesAdapter(Range range) : range_(std::forward<Range>(range)) {}

    auto begin() const { return Iterator(std::begin(range_)); }
    auto end() const { return Iterator(std::end(range_)); }
};

struct Values {
    auto operator()() const {
        return [](auto&& range) {
            return ValuesAdapter<decltype(range)>(std::forward<decltype(range)>(range));
        };
    }
};

inline Values values;

#endif // ADAPTERS_H