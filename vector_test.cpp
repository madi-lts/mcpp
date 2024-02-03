#ifndef MVECTOR_H
#define MVECTOR_H

#include <iostream>
#include <cmath>
#include <vector>
#include <random>

template <typename T>
class mvector: public std::vector<T> {
    using std::vector<T> :: vector;
    public:
        mvector operator-() {
            mvector<T> return_value(this->size());
            for (T& elem: return_value) {
                auto i = &elem - &return_value[0];
                return_value[i] = -(*this)[i];
            }
            return return_value;
        }

        mvector operator+=(const mvector &a) {
            for (T& elem: *this) {
                auto i = &elem - &(*this)[0];
                (*this)[i] += a[i];
            }
            return *this;
        }

        mvector operator-=(const mvector &a) {
            for (T& elem: *this) {
                auto i = &elem - &(*this)[0];
                (*this)[i] -= a[i];
            }
            return *this;
        }

        mvector operator*=(const double t) {
            for (T& elem: *this) {
                auto i = &elem - &(*this)[0];
                (*this)[i] *= t;
            }
            return *this;
        }

        mvector operator/=(const double t) {
            for (T& elem: *this) {
                auto i = &elem - &(*this)[0];
                (*this)[i] /= t;
            }
            return *this;
        }

        double length_sq() {
            return dot((*this),(*this));
        }

        double length() {
            return sqrt((*this).length_sq());
        }

        bool near_zero() {
             bool return_value = true;
             const auto epsilon = 1e-8;
             for (T& elem: *this) {
                return_value = return_value && (std::fabs(elem) < epsilon);
             }
             return return_value;
        }

        mvector random() {
            std::uniform_real_distribution<double> uniform(-1,1);
            std::default_random_engine random_engine;
            for (T& elem: *this) {
                elem = uniform(random_engine);
            }
            return *this;
        }

        mvector random(const double min, const double max) {
            std::uniform_real_distribution<double> uniform(min,max);
            std::default_random_engine random_engine;
            for (T& elem: *this) {
                elem = uniform(random_engine);
            }
            return *this;
        }
};

// Vector addition: a + b
template <typename T>
mvector<T> operator+(const mvector<T>& a, const mvector<T>& b) {
    mvector<T> return_value(a.size());
    for (T& elem: return_value) {
        auto i = &elem - &return_value[0];
        return_value[i] += a[i] + b[i];
    }
    return return_value;
}

// Vector subtraction: a - b
template <typename T>
mvector<T> operator-(const mvector<T>& a, const mvector<T>& b) {
    mvector<T> return_value(a.size());
    for (T& elem: return_value) {
        auto i = &elem - &return_value[0];
        return_value[i] += a[i] - b[i];
    }
    return return_value;
}

// Vector dot product: a*b
template <typename T>
T dot(const mvector<T>& a, const mvector<T>& b) {
    T return_value = 0;
    for (const T& elem: a) {
        auto i = &elem - &a[0];
        return_value += a[i] * b[i];
    }
    return return_value;
}

// Elementwise product: a*b
template <typename T>
mvector<T> operator*(const mvector<T>& a, const mvector<T>&b) {
    mvector<T> return_value(a.size());
    for (const T& elem: a) {
        auto i = &elem - &a[0];
        return_value[i] = a[i] * b[i];
    }
    return return_value;
}

// Cross product: a x b
template <typename T>
mvector<T> cross(const mvector<T>& a, const mvector<T>&b) {
    mvector<T> return_value(a.size());
    return_value[0] = a[1] * b[2] - a[2]*b[1];
    return_value[1] = a[2] * b[0] - a[0]*b[2];
    return_value[2] = a[0] * b[1] - a[1]*b[0];
    return return_value;
}

// Scalar multiplication: t*a
template <typename T>
mvector<T> operator*(const T t, const mvector<T>&a) {
    mvector<T> return_value(a.size());
    for (const T& elem: a) {
        auto i = &elem - &a[0];
        return_value[i] += t * a[i];
    }
    return return_value;
}

template <typename T>
mvector<T> operator*(const mvector<T>&a, const T t) {
    return t*a;
}

// Scalar division: a/t
template <typename T>
mvector<T> operator/(const mvector<T>&a, const T t) {
    return (1/t) * a;
}

// Unit vector
template <typename T>
mvector<T> unit_vector(mvector<T>& a) {
    return a/a.length();
}

template <typename T>
std::ostream& operator <<(std::ostream& output, const std::vector<T>& data)
{
    output << "[";
    for (const T& x : data) {
        auto i = &x - &data[0];
        output << x;
        if (i < data.size() - 1) output << ", ";
    }
    output << "]";
    return output;
}

// Type aliases for vector
using point = mvector<double>;
using color = mvector<int>;

int main () {
    mvector<double> a{1,2,3,4,5};
    std::cout << unit_vector(a).length() << "\n";
}

#endif