//
//  lists.cpp
//  CF.STL_Containers_List
//
//  Created by Alan Sampson on 3/24/21.
//
//  MARK: - Reference.
//  @see: https://en.cppreference.com/w/cpp/container
//  @see: https://en.cppreference.com/w/cpp/container/list
//

#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>
#include <span>
#include <algorithm>
#include <numeric>
#include <compare>
#include <memory>
#include <type_traits>
#include <list>

using namespace std::literals::string_literals;

//  MARK: - Definitions

//  MARK: - Local Constants.
namespace konst {

auto delimiter(char const dc = '-', size_t sl = 80) -> std::string const {
  auto const dlm = std::string(sl, dc);
  return dlm;
}

static
auto const dlm = delimiter();

static
auto const dot = delimiter('.');

} /* namespace konst */

#if (__cplusplus > 201707L)
#endif  /* (__cplusplus > 201707L) */

//  MARK: - Function Prototype.
auto C_list(int argc, const char * argv[]) -> decltype(argc);

//  MARK: - Implementation.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {
  std::cout << "CF.STL_Containers_List\n"s;
  std::cout << "C++ Version: "s << __cplusplus << std::endl;

  std::cout << '\n' << konst::dlm << std::endl;
  C_list(argc, argv);

  return 0;
}

//  MARK: C_list
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  ================================================================================
//  MARK: namespace clst
namespace clst {

template<typename T>
std::ostream & operator<<(std::ostream & os, const std::list<T> & container) {
  os.put('[');
  char comma[3] = { '\0', ' ', '\0', };
  for (auto const & el : container) {
    os << comma << el;
    comma[0] = ',';
  }
  return os << ']';
}

} /* namespace clst */

//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: C_list()
 */
auto C_list(int argc, const char * argv[]) -> decltype(argc) {
  std::cout << "In "s << __func__ << std::endl;

  /// Member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list"s << '\n';
  {
    // Create a list containing integers
    std::list<int> lst = { 7, 5, 16, 8, };

    // Add an integer to the front of the list
    lst.push_front(25);
    // Add an integer to the back of the list
    lst.push_back(13);

    // Insert an integer before 16 by searching
    auto it = std::find(lst.begin(), lst.end(), 16);
    if (it != lst.end()) {
      lst.insert(it, 42);
    }

    // Print out the list
    std::cout << "lst = { "s;
    for (int nr : lst) {
      std::cout << nr << ", "s;
    }
    std::cout << "};\n"s;

    std::cout << '\n';
  }

  /// Member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - constructor"s << '\n';
  {
    using namespace clst;

    // c++11 initializer list syntax:
    std::list<std::string> words1 { "the"s, "frogurt"s, "is"s, "also"s, "cursed"s, };
    std::cout << "words1: "s << words1 << '\n';

    // words2 == words1
    std::list<std::string> words2(words1.begin(), words1.end());
    std::cout << "words2: "s << words2 << '\n';

    // words3 == words1
    std::list<std::string> words3(words1);
    std::cout << "words3: "s << words3 << '\n';

    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    std::list<std::string> words4(5, "Mo"s);
    std::cout << "words4: "s << words4 << '\n';

    std::cout << '\n';
  }

  /// Member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - operator="s << '\n';
  {
    auto display_sizes = [](std::list<int> const & nums1,
                            std::list<int> const & nums2,
                            std::list<int> const & nums3)
    {
      std::cout << "nums1: "s << nums1.size()
                << " nums2: "s << nums2.size()
                << " nums3: "s << nums3.size() << '\n';
    };

    std::list<int> nums1 { 3, 1, 4, 6, 5, 9, };
    std::list<int> nums2;
    std::list<int> nums3;

    std::cout << "Initially:\n"s;
    display_sizes(nums1, nums2, nums3);

    // copy assignment copies data from nums1 to nums2
    nums2 = nums1;

    std::cout << "After assigment:\n"s;
    display_sizes(nums1, nums2, nums3);

    // move assignment moves data from nums1 to nums3,
    // modifying both nums1 and nums3
    nums3 = std::move(nums1);

    std::cout << "After move assigment:\n"s;
    display_sizes(nums1, nums2, nums3);

    std::cout << '\n';
  }

  /// Member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - assign"s << '\n';
  {
    std::list<char> characters;

    auto print_list = [&](){
      for (char ch : characters) {
        std::cout << ch << ' ';
      }
      std::cout << '\n';
    };

    characters.assign(5, 'a');
    print_list();

    const std::string extra(6, 'b');
    characters.assign(extra.begin(), extra.end());
    print_list();

    characters.assign({ 'C', '+', '+', '1', '1', });
    print_list();

    std::cout << '\n';
  }

  /// Element access
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - front"s << '\n';
  {
    std::list<char> letters { 'o', 'm', 'g', 'w', 't', 'f', };

    if (!letters.empty()) {
      std::cout << "The first character is '"s << letters.front() << "'.\n"s;
    }

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - back"s << '\n';
  {
    std::list<char> letters { 'a', 'b', 'c', 'd', 'e', 'f', };

    if (!letters.empty()) {
      std::cout << "The last character is '"s << letters.back() << "'.\n"s;
    }

    std::cout << '\n';
  }

  /// Iterators
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - begin, end, cbegin, cend, rbegin, rend, crbegin, crend"s << '\n';
  {
    std::list<int> nums { 1, 2, 4, 8, 16, };
    std::list<std::string> fruits { "orange"s, "apple"s, "raspberry"s, };
    std::list<char> empty;

    std::cout << "begin to end\n";
    // Print list.
    std::for_each(nums.begin(), nums.end(), [](int const nr) { std::cout << nr << ' '; });
    std::cout << '\n';

    // Sums all integers in the list nums (if any), printing only the result.
    std::cout << "Sum of nums: "s
              << std::accumulate(nums.begin(), nums.end(), 0) << '\n';

    // Prints the first fruit in the list fruits, checking if there is any.
    if (!fruits.empty()) {
      std::cout << "First fruit: "s << *fruits.begin() << '\n';
    }

    if (empty.begin() == empty.end()) {
      std::cout << "list 'empty' is indeed empty.\n"s;
    }

    std::cout << "rbegin to rend\n";
    // Print list.
    std::for_each(nums.rbegin(), nums.rend(), [](const int n) { std::cout << n << ' '; });
    std::cout << '\n';

    // Sums all integers in the list nums (if any), printing only the result.
    std::cout << "Sum of nums: "s
              << std::accumulate(nums.rbegin(), nums.rend(), 0) << '\n';

    // Prints the first fruit in the list fruits, checking if there is any.
    if (!fruits.empty()) {
      std::cout << "First fruit: "s << *fruits.rbegin() << '\n';
    }

    if (empty.rbegin() == empty.rend()) {
      std::cout << "list 'empty' is indeed empty.\n"s;
    }

    std::cout << '\n';
  }

  /// Capacity
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - empty"s << '\n';
  {
    std::list<int> numbers;
    std::cout << std::boolalpha;
    std::cout << "Initially, numbers.empty(): "s << numbers.empty() << '\n';

    numbers.push_back(42);
    numbers.push_back(13'317);
    std::cout << "After adding elements, numbers.empty(): "s << numbers.empty() << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - size"s << '\n';
  {
    std::list<int> nums { 1, 3, 5, 7, };

    std::cout << "nums contains "s << nums.size() << " elements.\n"s;

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - max_size"s << '\n';
  {
    std::list<char> s_chr;
    std::cout << "Maximum size of a 'list' is "s << s_chr.max_size() << '\n';

    std::cout << '\n';
  }

  /// Modifiers
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - clear"s << '\n';
  {
    std::list<int> container{ 1, 2, 3, };

    auto print = [](int const & nr) { std::cout << ' ' << nr; };

    std::cout << "Before clear:"s;
    std::for_each(container.begin(), container.end(), print);
    std::cout << "\nSize="s << container.size() << '\n';

    std::cout << "Clear\n"s;
    container.clear();

    std::cout << "After clear:"s;
    std::for_each(container.begin(), container.end(), print);
    std::cout << "\nSize=s" << container.size() << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - emplace"s << '\n';
  {
    struct Athing {
        std::string str;
        Athing(std::string str) : str(std::move(str))  { std::cout << " constructed\n"s; }
        Athing(Athing const & other) : str(other.str) { std::cout << " copy constructed\n"s; }
        Athing(Athing && other) : str(std::move(other.str)) { std::cout << " move constructed\n"s; }
        Athing & operator=(Athing const & other) {
          str = other.str;
          std::cout << " copy assigned\n"s;
          return *this;
        }
        Athing & operator=(Athing && other) {
          str = std::move(other.str);
          std::cout << " move assigned\n"s;
          return *this;
        }
    };

    std::list<Athing> container;

    std::cout << "construct 2 times Athing:\n"s;
    Athing two { "two"s };
    Athing three { "three"s };

    std::cout << "emplace:\n"s;
    container.emplace(container.end(), "one"s);

    std::cout << "emplace with Athing &:\n"s;
    container.emplace(container.end(), two);

    std::cout << "emplace with Athing &&:\n"s;
    container.emplace(container.end(), std::move(three));

    std::cout << "content:\n"s;
    for (auto const & obj : container)
      std::cout << ' ' << obj.str;
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - erase"s << '\n';
  {
    auto print_container = [](const std::list<int> & container)
    {
      for (auto & ic : container) {
        std::cout << ic << ' ';
      }
      std::cout << '\n';
    };

    std::list<int> container { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
    print_container(container);

    container.erase(container.begin());
    print_container(container);

    std::list<int>::iterator range_begin = container.begin();
    std::list<int>::iterator range_end = container.begin();
    std::advance(range_begin, 2);
    std::advance(range_end, 5);

    container.erase(range_begin, range_end);
    print_container(container);

    // Erase all even numbers (C++11 and later)
    for (auto it = container.begin(); it != container.end(); ) {
      if (*it % 2 == 0) {
        it = container.erase(it);
      }
      else {
        ++it;
      }
    }
    print_container(container);

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - push_back"s << '\n';
  {
    std::list<std::string> letters;

    letters.push_back("abc"s);
    std::string str = "def"s;
    letters.push_back(std::move(str));

    std::cout << "list holds: "s;
    for (auto && il : letters) {
      std::cout << std::quoted(il) << ' ';
    }
    std::cout << "\nMoved-from string holds "s << std::quoted(str) << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - emplace_back"s << '\n';
  {
    struct President
    {
      std::string name;
      std::string country;
      int year;

      President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {
        std::cout << "I am being constructed.\n"s;
      }

      President(President && other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
      {
        std::cout << "I am being moved.\n"s;
      }

      President & operator=(President const & other) = default;
    };

    std::list<President> elections;
    std::cout << "emplace_back:\n"s;
    auto& ref = elections.emplace_back("Nelson Mandela"s, "South Africa"s, 1994);
    assert(ref.year != 1984 && "uses a reference to the created object (C++17)");

    std::list<President> reElections;
    std::cout << "\npush_back:\n"s;
    reElections.push_back(President("Franklin Delano Roosevelt"s, "the USA"s, 1936));

    std::cout << "\nContents:\n"s;
    for (President const & president: elections) {
      std::cout << president.name << " was elected president of "s
                << president.country << " in "s << president.year << ".\n"s;
    }
    for (President const & president: reElections) {
      std::cout << president.name << " was re-elected president of "s
                << president.country << " in "s << president.year << ".\n"s;
    }

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - pop_back"s << '\n';
  {
    auto print = [](auto const & container) {
      std::cout << "[ "s;
      for (auto const & el : container) {
        std::cout << el << ' ';
      }
      std::cout << "]\n"s;
    };

    std::list<int> numbers;

    print(numbers);

    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(4);

    print(numbers);

    numbers.pop_back();

    print(numbers);

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - resize"s << '\n';
  {
    std::list<int> container = { 1, 2, 3, };
    std::cout << "The list holds:         "s;
    for (auto & el : container) { std::cout << el << ' '; }
    std::cout << '\n';

    container.resize(5);
    std::cout << "After resize up to 5:   "s;
    for (auto & el : container) { std::cout << el << ' '; }
    std::cout << '\n';

    container.resize(2);
    std::cout << "After resize down to 2: "s;
    for (auto & el : container) { std::cout << el << ' '; }
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - swap"s << '\n';
  {
    using namespace clst;

    std::list<int> a1 { 1, 2, 3, }, a2 { 4, 5, };

    auto it1 = std::next(a1.begin());
    auto it2 = std::next(a2.begin());

    int& ref1 = a1.front();
    int& ref2 = a2.front();

    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    a1.swap(a2);
    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

    // Note that after swap the iterators and references stay associated with their
    // original elements, e.g. it1 that pointed to an element in 'a1' with value 2
    // still points to the same element, though this element was moved into 'a2'

    std::cout << '\n';
  }

  /// Operations
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - merge"s << '\n';
  {
    using namespace clst;

    std::list<int> list1 = { 5,9,0,1,3, };
    std::list<int> list2 = { 8,7,2,6,4, };

    list1.sort();
    list2.sort();
    std::cout << "list1:  "s << list1 << '\n';
    std::cout << "list2:  "s << list2 << '\n';
    list1.merge(list2);
    std::cout << "merged: "s << list1 << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - splice"s << '\n';
  {
    using namespace clst;

    std::list<int> list1 = { 1, 2, 3, 4, 5, };
    std::list<int> list2 = { 10, 20, 30, 40, 50, };

    auto it = list1.begin();
    std::advance(it, 2);

    list1.splice(it, list2);

    std::cout << "list1: "s << list1 << '\n';
    std::cout << "list2: "s << list2 << '\n';

    list2.splice(list2.begin(), list1, it, list1.end());

    std::cout << "list1: "s << list1 << '\n';
    std::cout << "list2: "s << list2 << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - remove, remove_if"s << '\n';
  {
    using namespace clst;

    std::list<int> container = { 1, 100, 2, 3, 10, 1, 11, -1, 12, };
    std::cout << "before remove           : "s << container << '\n';

    container.remove(1); // remove both elements equal to 1
    std::cout << "after remove '1''       : "s << container << '\n';

    container.remove_if([](int nr){ return nr > 10; }); // remove all elements greater than 10
    std::cout << "after remove values > 10: "s << container << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - reverse"s << '\n';
  {
    using namespace clst;

    std::list<int> list = { 8, 7, 5, 9, 0, 1, 3, 2, 6, 4, };

    std::cout << "before:     "s << list << '\n';
    list.sort();
    std::cout << "ascending:  "s << list << '\n';
    list.reverse();
    std::cout << "descending: "s << list << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - unique"s << '\n';
  {
    using namespace clst;

    std::list<int> container = { 1, 2, 2, 3, 3, 2, 1, 1, 2, };

    std::cout << "contents before        : "s << container << '\n';

    container.unique();
    std::cout << "contents after unique(): "s << container << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - sort"s << '\n';
  {
    using namespace clst;

    std::list<int> list = { 8, 7, 5, 9, 0, 1, 3, 2, 6, 4, };

    std::cout << "before:     "s << list << '\n';
    list.sort();
    std::cout << "ascending:  "s << list << '\n';
    list.sort(std::greater<int>());
    std::cout << "descending: "s << list << '\n';

    std::cout << '\n';
  }

  /// Non-member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - std::operator==, etc."s << '\n';
  {
    std::list<int> alice { 1, 2, 3, };
    std::list<int> bob   { 7, 8, 9, 10, };
    std::list<int> eve   { 1, 2, 3, };

    std::cout << std::boolalpha;

    // Compare non equal containers
    std::cout << "alice == bob returns "s << (alice == bob) << '\n';
    std::cout << "alice != bob returns "s << (alice != bob) << '\n';
    std::cout << "alice <  bob returns "s << (alice < bob) << '\n';
    std::cout << "alice <= bob returns "s << (alice <= bob) << '\n';
    std::cout << "alice >  bob returns "s << (alice > bob) << '\n';
    std::cout << "alice >= bob returns "s << (alice >= bob) << '\n';

    std::cout << '\n';

    // Compare equal containers
    std::cout << "alice == eve returns "s << (alice == eve) << '\n';
    std::cout << "alice != eve returns "s << (alice != eve) << '\n';
    std::cout << "alice <  eve returns "s << (alice < eve) << '\n';
    std::cout << "alice <= eve returns "s << (alice <= eve) << '\n';
    std::cout << "alice >  eve returns "s << (alice > eve) << '\n';
    std::cout << "alice >= eve returns "s << (alice >= eve) << '\n';
    std::cout << '\n';

#if (__cplusplus > 201707L)
    //  TODO:  add spaceship operator tests
    auto eq = std::is_eq  (alice <=> eve);
    auto ne = std::is_neq (alice <=> eve);
    auto lt = std::is_lt  (alice <=> eve);
    auto le = std::is_lteq(alice <=> eve);
    auto gt = std::is_gt  (alice <=> eve);
    auto ge = std::is_gteq(alice <=> eve);
#endif  /* (__cplusplus > 201707L) */

    std::cout << std::boolalpha;

    std::cout << '\n';
  }

  /// Non-member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - std::swap"s << '\n';
  {
    std::list<int> alice { 1, 2, 3, };
    std::list<int> bob   { 7, 8, 9, 10, };

    auto print = [](int const & nr) { std::cout << ' ' << nr; };

    // Print state before swap
    std::cout << "alice: "s;
    std::for_each(alice.begin(), alice.end(), print);
    std::cout << "\n"s
                 "bob  : "s;
    std::for_each(bob.begin(), bob.end(), print);
    std::cout << '\n';

    std::cout << "-- SWAP\n"s;
    std::swap(alice, bob);

    // Print state after swap
    std::cout << "alice: "s;
    std::for_each(alice.begin(), alice.end(), print);
    std::cout << "\n"s
                 "bob  : "s;
    std::for_each(bob.begin(), bob.end(), print);
    std::cout << '\n';

    std::cout << '\n';
  }

  /// Non-member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_list - std::swap"s << '\n';
  {
    auto print_container = [](std::string_view comment,
                              std::list<char> const & container) {
      std::cout << comment;
      for (auto el : container) {
        std::cout << el << ' ';
      }
      std::cout << '\n';
    };

    std::list<char> cnt(10);
    std::iota(cnt.begin(), cnt.end(), '0');
    print_container("Init:\n"s, cnt);

    std::erase(cnt, '3');
    print_container("Erase '3':\n"s, cnt);

#if (__cplusplus > 201707L)
  //`TODO:  add C++20 feature tests
    auto erased = std::erase_if(cnt, [](char xl) { return (xl - '0') % 2 == 0; });
    print_container("Erase all even numbers:\n"s, cnt);
    std::cout << "In all " << erased << " even numbers were erased.\n"s;
#endif  /* (__cplusplus > 201707L) */

    std::cout << '\n';
  }

  std::cout << std::endl; //  make sure cout is flushed.

  return 0;
}
