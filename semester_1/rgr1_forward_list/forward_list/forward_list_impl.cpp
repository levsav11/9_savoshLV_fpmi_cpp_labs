#include "forward_list_impl.h"

ForwardList::ForwardList() {}

ForwardList::~ForwardList() {
    Clear();
}
ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr), size_(0) {
    Node* tail = nullptr;
    for (Node* it = rhs.head_; it; it = it->next_) {
        Node* node = new Node(it->value_);
        if (!tail) head_ = node;
        else tail->next_ = node;
        tail = node; ++size_;
    }
}
ForwardList::ForwardList(size_t count, int32_t value) 
    : head_(nullptr), size_(0) {
    for (std::size_t i = 0; i < count; ++i) {
        PushFront(value);
    }
}
ForwardList::ForwardList(std::initializer_list<int32_t> init) 
: head_(nullptr), size_(init.size()) {
    Node* last = nullptr;
    for (int32_t value : init) {
        Node* new_node = new Node(value);
        if (last == nullptr) {
            head_ = new_node;
        } else {
            last->next_ = new_node;
        }
        last = new_node;
    }
}
ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) return *this;
    
    Clear();
    
    Node* tail = nullptr;
    for (Node* it = rhs.head_; it; it = it->next_) {
        Node* node = new Node(it->value_);
        if (!tail) head_ = node;
        else tail->next_ = node;
        tail = node; ++size_;
    }
    return *this;
}
void ForwardList::PushFront(int32_t value) {
    Node* new_node = new Node(value);
    new_node->next_ = head_;
    head_ = new_node;
    ++size_;
}
void ForwardList::PopFront() {
    if (head_ == nullptr) return;
    Node* tmp = head_;
    head_ = head_->next_;
    delete tmp;       
    --size_; 
}

void ForwardList::Clear() {
    while (head_ != nullptr) {
        Node* tmp = head_;
        head_ = head_->next_;
        delete tmp;
    }
    size_ = 0;
}

void ForwardList::Remove(int32_t value) {
    Node* prev = nullptr;
    Node* curr = head_;
    while (curr != nullptr) {
        if (curr->value_ == value) {
            Node* tmp = curr;
            if (prev == nullptr) head_ = curr->next_;
            else prev->next_ = curr->next_;
            curr = curr->next_;
            delete tmp;
            --size_;
        } else {
            prev = curr;
            curr = curr->next_;
        }
    }
}

bool ForwardList::FindByValue(int32_t value) {
    Node* curr = head_;
    while (curr != nullptr) {
        if (curr->value_ == value) return true;
        curr = curr->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = head_;
    if (current == nullptr) {
        out << "";
        return;
    }
    while (current->next_ != nullptr) {
        out << current->value_ << ' ';
        current = current->next_;
    }
    out << current->value_;
}

int32_t ForwardList::Front () const{
    if (head_ == nullptr) throw std::out_of_range("List is empty!");
    return head_->value_;
}

size_t ForwardList::Size() const{
    return size_;
}

