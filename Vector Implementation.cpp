#include <iostream>
#include <initializer_list>
using namespace std;

template<typename T>
class Vector
{
private:
    T* vec;

    int vec_size;

public:

    Vector()
    {
        vec = nullptr;
    }

    ~Vector()
    {
        delete[] vec;
    }

    Vector(int size)
    {
        vec = new T[size];
        vec_size = size;
    }

    Vector(std::initializer_list<T> values)
    {
        if (vec != nullptr)
        {
            delete[] vec;
        }

        vec_size = values.size();

        T* temp_vec = new T[vec_size];

        std::copy(values.begin(), values.end(), temp_vec);

        vec = temp_vec;
    }

    Vector(const Vector& other)
    {
        this->vec_size = other.vec_size;

        this->vec = new T[vec_size];

        for (int i = 0; i < this->vec_size; i++)
        {
            this->vec[i] = other.vec[i];
        }
    }

    Vector& operator = (const Vector& other)
    {
        if (this->vec != nullptr)
        {
            delete[] vec;
        }

        this->vec_size = other.vec_size;

        T* temp_vec = new T[this->vec_size];

        for (int i = 0; i < this->vec_size; i++)
        {
            temp_vec[i] = other.vec[i];
        }

        this->vec = temp_vec;

        return *this;
    }

    T& operator [] (int index)
    {
        return vec[index];
    }

    int size()
    {
        return vec_size;
    }

    void push_back(T value)
    {
        if (vec == nullptr)
        {
            return;
        }

        ++vec_size;

        T* temp_vec = new T[vec_size];
        for (int i = 0; i < vec_size - 1; i++)
        {
            temp_vec[i] = vec[i];
        }

        temp_vec[vec_size-1] = value;

        delete[] vec;

        vec = temp_vec;
    }

    void pop_back()
    {
        if (vec == nullptr)
        {
            return;
        }

        --vec_size;

        T* temp_vec = new T[vec_size];

        for (int i = 0; i < vec_size; i++)
        {
            temp_vec[i] = vec[i];
        }

        delete[] vec;

        vec = temp_vec;
    }

    void erase(int index)
    {
        if(vec == nullptr || index >= vec_size || index < 0)
        {
            return;
        }

        --vec_size;

        T* temp_vec = new T[vec_size];

        int temp_index = 0;
        for (int i = 0; i < vec_size + 1; i++)
        {
            if (i != index)
            {
                temp_vec[temp_index] = vec[i];
                ++temp_index;
            }
        }

        delete[] vec;
        vec = temp_vec;
    }

    void erase(int start, int end)
    {
        if (vec == nullptr)
        {
            return;
        }

        if (start > end || (start > vec_size || start < 0) || (end > vec_size || end < 0))
        {
            return;
        }
        else if (start == end)
        {
            this->erase(start);
            return;
        }

        int delta = end - start + 1;

        this->vec_size = this->vec_size - delta;

        T* temp_vec = new int[this->vec_size];

        int temp_index = 0;

        for (int i = 0; i < this->vec_size + delta; i++)
        {
            if (i < start || i > end)
            {
                temp_vec[temp_index] = this->vec[i];
                ++temp_index;
            }
        }

        delete[] vec;

        vec = temp_vec;
    }

    void insert(int index, T el)
    {
        if (vec == nullptr || index >= vec_size || index < 0)
        {
            return;
        }

        ++vec_size;

        T* temp_vec = new T[vec_size];

        int temp_i = 0;

        for (int i = 0; i < vec_size; i++)
        {
           if (i == index)
           {
               temp_vec[i] = el;
               continue;
           }
           temp_vec[i] = vec[temp_i];
           ++temp_i;
        }

        delete[] vec;
        vec = temp_vec;
    }
};

int main()
{
    Vector<int> vec(10);
    Vector<int> v = {1,35,6,3,2};

    v.push_back(10);

    v.pop_back();

    Vector<int> vec1(v);

    v.erase(0, 1);

    v.insert(2, 9);

    for (int i = 0; i < v.size(); i++)
    {
        std::cout << "v: " << v[i] << endl;
    }
}
