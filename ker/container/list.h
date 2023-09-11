//https://devblogs.microsoft.com/oldnewthing/20230804-00/?p=108547
namespace ker {
template <class T>
struct list_node {
    T value{};
    list_node* previous = nullptr;
    list_node* next = nullptr;
    list_node();
    list_node(const T& your_value) : value{your_value} {}
    list_node(T&& your_value) : value{std::move(your_value)} {}
};
template <class T>
class list {
   public:
    list(/* args */);
    ~list();

   private:
    list_node<T>* head_;

};
template <class T>
list<T>::list(/* args */) {}
template <class T>
list<>::~list() {}

}  // namespace ker
