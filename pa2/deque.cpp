/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */ 

/* Constructor for the Deque class */
template <class T>
Deque<T>::Deque(){
    k1 = -1;
    k2 = -1;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */ 
template <class T>
void Deque<T>::pushR(T const& newItem)
{
    if(k1 == -1 && k2 == -1){
        k1++; k2++;
        data.push_back(newItem);
    } else {
        k2++;
        data.push_back(newItem);
    }
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The leftmost item of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    if(k1 == -1 && k2 == -1){
        //Empty Deque
        return T();
    }
    else if(k1 == k2){
        //Single Element
        T ret = data[k1];
        data.clear();
        k1 = -1;
        k2 = -1;
        return ret;
    }

    T ret = data[k1];
    k1++;

    if(k1 >= (k2 - k1) + 1){
        vector<T> sub;
        for(int i = 0; i <= (k2 - k1); i++){
            sub.push_back(data[k1 + i]);
        }
        data = sub;
        k1 = 0;
        k2 = (int)sub.size() - 1;
    }

    return ret;
}

// template <class T>
// void Deque<T>::resize(){
//     vector<T> sub;
//     for(int i = 0; i <= (k2 - k1); i++){
//         sub.push_back(data[k1 + i]);
//     }
//     print();
//     data = sub;
//     k1 = 0;
//     k2 = (int)sub.size() - 1;
//     print();
//     cout<<"\n";
// }

// template <class T>
// void Deque<T>::print(){
//     cout<<"Data: { ";
//     for(int i = 0; i < (int)data.size(); i++){
//         if(i == k1 || i == k2){
//             cout<<"*"<<data[i]<<"*"<<' ';
//         } else {
//             cout<<data[i]<<' ';
//         }
//     }
//     cout<<"}"<<endl;
//     cout<<"Size: "<< data.size()<<"\nk1: "<<k1<<"\nk2: "<<k2<<endl;
//     cout<<"Should Resize: "<< (k1 > (k2 - k1) + 1)<<endl;
// }
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The rightmost item of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    if(k1 == -1 && k2 == -1){
        //Empty Deque
        return T();
    }
    else if(k1 == k2){
        //Single Element
        T ret = data[k1];
        data.clear();
        k1 = -1;
        k2 = -1;
        return ret;
    }
    T ret = data[k2];
    k2--;
    data.pop_back();

    
    if(k1 >= (k2 - k1) + 1){
        vector<T> sub;
        for(int i = 0; i <= (k2 - k1); i++){
            sub.push_back(data[k1 + i]);
        }
        data = sub;
        k1 = 0;
        k2 = (int)sub.size() - 1;
    }

    return ret;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the left of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data[k1];   
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data[k2];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return (k1 == -1 && k2 == -1);
}
