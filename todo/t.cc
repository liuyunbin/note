
#include <iostream>
#include <vector>

template <class ForwardIterator, class Size, class T>
ForwardIterator search_n(ForwardIterator first,
                         ForwardIterator last,
                         Size            count,
                         const T&        val) {
    ForwardIterator it, limit;
    Size            i;

    limit = first;
    std::advance(limit, std::distance(first, last) - count);

    while (first != limit) {
        it = first;
        i  = 0;
        while (*it == val)  // or: while (pred(*it,val)) for the pred version
        {
            ++it;
            if (++i == count)
                return first;
        }
        ++first;
    }
    return last;
}

int main() {
    std::vector<int> v1 = {1, 1, 1, 1, 1};

    auto it = search_n(v1.begin(), v1.end(), 5, 1);

    if (it == v1.end()) {
        std::cout << "can't find" << std::endl;
    } else {
        std::cout << *it << std::endl;
    }

    return 0;
}
