#ifndef LIST342_H
#define LIST342_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std; 

template <class T> 
class List342{
    public:
        List342();
        List342(const List342<T>& temp_list);
        ~List342();
        bool BuildList(string file_name);
        bool Insert(T* obj);
        bool Remove(T target, T& result);
        bool Peek(T target, T& result) const;
        void DeleteList(); 
        bool Merge(List342<T>& list);
        bool IsEmpty() const;


        int Size() const;
        bool set_size(int number);

        List342<T>& operator+= (const List342<T>& list2);
        List342<T> operator+ (const List342<T>& list2) const;

        bool operator== (const List342<T>& list2) const;
        bool operator!= (const List342<T>& list2) const;


        List342<T>& operator= (const List342<T>& list2);

        template<class U>
        friend ostream& operator<<(ostream& stream, const List342<U>& input);
        template<class U>
        friend istream& operator>>(istream& stream, List342<U>& input);


    private:
        struct Node { 
            T *data;  
            Node *next; 
        }; 
        int size_;
        Node* head_; 
        bool InsertHelper(Node* list1, T* obj);

};

template<class T>
List342<T>:: List342(){

    head_ = nullptr;
    size_ = 0;
}
template <class T>
List342<T>::List342(const List342<T>& temp_list): head_(nullptr), size_(0){
    DeleteList(); 
    *this = temp_list;
}

template<class T>
List342<T>:: ~List342<T> (){
    this->DeleteList();
}
template<class T>
int List342<T>::Size() const{
    return this->size_;
}

template<class T>
bool List342<T>::set_size(int number){
   size_ = number;
   return true;
}

template<class T>
bool List342<T>::Peek(T target, T& result) const{
    Node* ptr = this->head_;
    while(ptr != nullptr){
        if (*ptr->data == target){
            result = target;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}
template <class T>
bool List342<T>::IsEmpty() const{
    if (this->size_ == 0){
        return true;
    } else{
        return false;
    }
}
template <class T>
void List342<T>::DeleteList(){
    Node* deleter_ptr = this->head_;
    while(this->head_ != nullptr){
        T* node_ptr = this->head_->data;
        this->head_ = this->head_->next;
        delete(node_ptr);
        delete(deleter_ptr);
        --this->size_;
        deleter_ptr = this->head_;
    }
    deleter_ptr = nullptr;
}

template<class T>
bool List342<T>::Remove(T target, T& result){
    if (this->IsEmpty()){
        return false;
    }
    Node* ptr = this->head_;
    if (*ptr->data == target){
        this->head_ = this->head_->next;
        result = *ptr->data;
        delete(ptr->data);
        delete(ptr);
        ptr = nullptr;
        --this->size_;
        return true;
    }else{
        while(ptr->next != nullptr){
            if (*ptr->next->data == target){
                Node* temp = ptr->next;
                T* deletion_node = ptr->next->data;
                ptr->next = ptr->next->next;
                temp->next = nullptr;
                result = *deletion_node;
                delete(temp->data);
                delete(temp);
                temp = nullptr;
                --this->size_;
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }
}

template<class T>
bool List342<T>::BuildList(string file_name){
    ifstream file_reader;
    T temp;

    file_reader.open(file_name);
    if (file_reader.is_open()){

        while(!file_reader.eof()){
            file_reader >> temp;
            this->Insert(&temp);
        }

    } else{
        return false;
    }

    file_reader.close();
    return true;
}
template<class U>
istream& operator>>(istream& stream, List342<U>& input){ //inputs obj into list
     U temp;
     cout<<"Enter obj: ";
     stream>>temp;
     input.Insert(&temp);
     return stream;
}

template<class U>
ostream& operator<<(ostream& stream, const List342<U>& input){
    if (input.IsEmpty()){
        return stream;
    }
        typename List342<U>::Node* ptr = input.head_; 
        while(ptr != nullptr){
            stream<<*ptr->data;
            ptr = ptr->next;
        }
        return stream;
}

template <class U>
bool List342<U>::operator== (const List342<U>& list2) const{
    Node* temp_list1 = this->head_;
    Node* temp_list2 = list2.head_;
    if (list2.size_ != this->size_){
        return false;
    } else{
        while(temp_list1 != nullptr){
            if (*temp_list1->data != *temp_list2->data){
                return false;
            }
            temp_list1 = temp_list1->next;
            temp_list2 = temp_list2->next;
        }
        return true;
    }
}

template <class T>
bool List342<T>::operator!= (const List342<T>& list2) const{
    return !(*this == list2);
}

template<class T>
List342<T>& List342<T>::operator+= (const List342<T>& list2){
    if (list2.IsEmpty() || *this == list2 || this == &list2){
        return *this;
    }

    Node* ptr1 = this->head_;
    Node* ptr2 = list2.head_;
    if (this->IsEmpty()){ //if "this" list is empty then we just want to transfer data from list2 to "this" list
        Node* temp_head = new Node();
        T* data_node = new T(); 
        *data_node = *ptr2->data;
        temp_head->data = data_node;
        ptr1 = temp_head;
        this->head_ = ptr1;
        ptr2 = ptr2->next;
        ++size_;
        while(ptr2 != nullptr){
            Node* temp = new Node();
            T* data_node = new T(); 
            *data_node = *ptr2->data;
            temp->data = data_node;
            ptr1->next = temp;
            ptr2 = ptr2->next;
            ptr1 = ptr1->next;
            ++size_;
        }
        return *this;
    }
    while(ptr2 != nullptr && ptr1->next != nullptr){
        if (*ptr1->data == *ptr2->data){
            ptr2 = ptr2->next;
        } else if (*this->head_->data > *ptr2->data){ //check if value needs to be inserted before head
        Node* temp = new Node();
        T* data_node = new T();
        *data_node = *ptr2->data;
        temp->data = data_node;
        ptr2 = ptr2->next;
        temp->next = this->head_;
        this->head_ = temp;
        ptr1 = this->head_;
        ++size_;
        } else if (*ptr1->next->data == *ptr2->data){
            ptr2 = ptr2->next;
        }else if (*ptr1->next->data > *ptr2->data){ //ahead value greater
            Node* temp = new Node();
            T* data_node = new T();
            *data_node = *ptr2->data;
            temp->data = data_node;
            temp->next = ptr1->next;
            ptr1->next = temp;
            ptr2 = ptr2->next;
            ++size_;
        } else {
            ptr1 = ptr1->next;
        }
    }
    while (ptr1->next == nullptr && ptr2 != nullptr){ //handles adding nodes from list2 to tail
        Node* temp = new Node();
        T* data_node = new T();
        *data_node = *ptr2->data;
        temp->data = data_node;
        temp->next = nullptr;
        ptr1->next = temp; 
        ptr2 = ptr2->next;
        ptr1 = ptr1->next;
        ++size_;
    }
    return *this;
}

template<class T>
List342<T> List342<T>::operator+ (const List342<T>& list2) const{ 
    List342<T> temp;
    temp = *this; 
    temp += list2;
    return temp; 

}
template<class T>
List342<T>& List342<T>::operator= (const List342<T>& list2){
    if (!this->IsEmpty()){
        this->DeleteList();
    }
    if (list2 == *this){ //make sure lists are not the same
        return *this;
    }

    Node* temp_ptr = list2.head_;
    //this block of code will initialize the head of the "this" list 
    Node* temp_node = new Node();
    T* data_node = new T(); 
    *data_node = *temp_ptr->data;
    temp_node->data = data_node;
    this->head_= temp_node;
    ++size_;
    Node* list_ptr = this->head_;
    temp_ptr = temp_ptr->next;

    while(temp_ptr != nullptr){
        Node* temp_list_node = new Node();
        T* data_list_node = new T(); 
        *data_list_node = *temp_ptr->data;
        temp_list_node->data = data_list_node;
        list_ptr->next = temp_list_node;
        ++size_;
        list_ptr = list_ptr->next;
        temp_ptr = temp_ptr->next;
    }
    return *this;
}

template<class T>
bool List342<T>::Insert(T* obj){
    if (this->head_ == nullptr){
        Node* tempNode = new Node();
        T* data_node = new T(); 
        *data_node = *obj;
        tempNode->data = data_node;
        this->head_= tempNode;
        ++size_;
    } else{
        Node* listPtr = this->head_;
        if (*listPtr->data == *obj){
            return false;
        }
        bool inserted = InsertHelper(listPtr, obj);
        if (!inserted){
            return false;
        }
        ++size_;
    }
    return true;
}

template<class T>
bool List342<T>::InsertHelper(Node* list1, T* obj){
    while(list1 ->next != nullptr && *list1->next->data < *obj){ //get to the right place
            list1 = list1->next; 
    }
    if (list1->next != nullptr && *list1->next->data == *obj){
        return false;
    }else{
        Node* tempNode = new Node();
        T* data_node = new T(); 
        *data_node = *obj; 
        tempNode->data = data_node; 
        if (*list1->data < *data_node){ //insert after previous node
            tempNode -> next = list1->next;
            list1->next= tempNode; 
        }else{ //insert before previous node
            Node* listPtr = head_;
            tempNode->next = listPtr; 
            head_= tempNode; 
        }
        return true;
    }
}

template<class T>
bool List342<T>::Merge(List342<T>& list){ //list's contents get put into *this list
    if (list.IsEmpty()){
        return false;
    }
    if (&list == this){
        return false;
    }

    Node* ptr1 = this->head_;
    if (this->IsEmpty()){ //if "this" list is empty then we just want to transfer data from list2 to "this" list
        this->head_ = list.head_;
        this->size_ = list.size_;
        list.head_ = nullptr;
        list.size_ = 0;
        return true;
    }
    while(list.head_ != nullptr && ptr1->next != nullptr){
        if (*ptr1->data == *list.head_->data){
            Node* temp = list.head_;
            list.head_= list.head_->next;
            temp->next = nullptr;
            delete(temp->data);
            delete(temp);
            --list.size_;
        }else if (*this->head_->data > *list.head_->data){ //check if value needs to be inserted before head
            Node* temp =  list.head_;
            list.head_ = list.head_->next;
            temp->next = this->head_;
            this->head_ = temp;
            ptr1 = this->head_;
            ++size_;
            --list.size_;
        }  else if (*ptr1->next->data == *list.head_->data){
            Node* temp = list.head_;
            list.head_= list.head_->next;
            temp->next = nullptr;
            delete(temp->data);
            delete(temp);
            --list.size_;
        }else if (*ptr1->next->data > *list.head_->data){ //ahead value greater
            Node* temp =  list.head_;
            list.head_ = list.head_->next;
            temp->next = ptr1->next;
            ptr1->next = temp;
            ++size_;
            --list.size_;
        } else {
            ptr1 = ptr1->next;
        }
    }
    while (ptr1->next == nullptr && list.head_ != nullptr){ //handles adding nodes from list2 to tail
        Node* temp =  list.head_;
        list.head_ = list.head_->next;
        temp->next = nullptr;
        ptr1->next = temp; 
        ptr1 = ptr1->next;
        ++size_;
        --list.size_;
    }
    return true;
}



#endif