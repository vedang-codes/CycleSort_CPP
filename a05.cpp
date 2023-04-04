#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include <fstream>
#include <cstddef>

template <typename Iter, typename CompareFunc>
size_t cycle_sort(Iter const &first, Iter const &last, CompareFunc const &cmp) {
    std::size_t writes = 0;
    if(first == last)
        return writes;
    for(auto start = first; start != std::prev(last); start++) {
        auto item = *start;
        auto pos = start;
        for(auto i = std::next(start); i != last; i++) {
            if(cmp(*i, item)) {
                pos++;
            }
        }
        if(pos == start) {
            continue;
        }
        while(item == *pos) {
            pos++;
        }
        std::swap(*pos, item);
        writes++;
        
        while(pos != start) {
            pos = start;
            for(auto i = std::next(start); i != last; i++) {
                if(cmp(*i, item)) {
                    pos++;
                }
            }
            while(item == *pos) {
                pos++;
            }
            std::swap(*pos, item);
            writes++;
        }
    }
    return writes;
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        std::cout << "Usage: " << argv[0] << " <input_file>\n";
        std::cout << "ERROR: Missing filename.\n";
        return 1;
    }
    if(argc >= 3) {
        std::cout << "Usage: " << argv[0] << " <input_file>\n";
        std::cout << "ERROR: Too many arguments.\n";
        return 2;
    }
    if(argc == 2) {
        std::ifstream in;
        std::list<int> l;
        in.open(argv[1]);
        std::copy(std::istream_iterator<int>(in), std::istream_iterator<int>(), back_inserter(l));
        std::cout << "original_data: ";
        std::copy(begin(l), end(l), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
        std::cout << "   num_writes: ";
        std::cout << cycle_sort(begin(l), end(l), std::less<>{});
        std::cout << "\n  sorted_data: ";
        std::copy(begin(l), end(l), std::ostream_iterator<int>(std::cout, " "));
    }

    return 0;
}