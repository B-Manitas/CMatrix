/**
 * @file CBool.hpp
 * @brief This file contains the definition and implementation of the cbool class.
 *
 * @author Manitas Bahri <https://github.com/b-manitas>
 * @date 2023
 * @license MIT License
 */

#ifndef CBOOL_HPP
#define CBOOL_HPP

// INCLUDE
#include <iostream>

/**
 * @brief This class is a wrapper for the bool type.
 * 
 * @details This class is a wrapper for the bool type. It allows to use the bool type in a cmatrix object.
 */
class cbool
{
private:
    // ATTRIBUTES
    char m_value = false;

    // PRIVATE METHODS
    /**
     * @brief Convert any type to bool.
     * 
     * @tparam T The type to convert.
     * @param v The value to convert.
     * @return char The converted value.
     */
    template <class T> char __to_bool(const T &v) const { return (bool)v; }

public:
    // CONSTRUCTORS
    cbool() : m_value(false) {}
    ~cbool() {}
    
    template <class T> cbool(const T &m_value) : m_value(__to_bool(m_value)) {}

    // GETTERS
    /**
     * @brief Get the value of the cbool object.
     * 
     * @return char The value of the cbool object.
     */
    char value() const { return m_value; }

    // UNARY OPERATORS
    cbool operator!() const { return cbool(!m_value); }
    
    // LOGICAL OPERATORS
    cbool operator&&(const cbool &b) const { return cbool(m_value && b.m_value); }
    cbool operator||(const cbool &b) const { return cbool(m_value || b.m_value); }
    
    // COMPARISON OPERATORS
    cbool operator==(const cbool &b) const { return cbool(m_value == b.m_value); }
    cbool operator!=(const cbool &b) const { return cbool(m_value != b.m_value); }
    cbool operator<(const cbool &b) const { return cbool(m_value < b.m_value); }
    cbool operator<=(const cbool &b) const { return cbool(m_value <= b.m_value); }
    cbool operator>(const cbool &b) const { return cbool(m_value > b.m_value); }
    cbool operator>=(const cbool &b) const { return cbool(m_value >= b.m_value); }
    
    template <class T> cbool operator==(const T &b) const { return cbool(m_value == __to_bool(b)); }
    template <class T> cbool operator!=(const T &b) const { return cbool(m_value != __to_bool(b)); }
    template <class T> cbool operator<(const T &b) const { return cbool(m_value < __to_bool(b)); }
    template <class T> cbool operator<=(const T &b) const { return cbool(m_value <= __to_bool(b)); }
    template <class T> cbool operator>(const T &b) const { return cbool(m_value > __to_bool(b)); }
    template <class T> cbool operator>=(const T &b) const { return cbool(m_value >= __to_bool(b)); }

    // ARITHMETIC OPERATORS
    cbool operator+(const cbool &b) const { return cbool(m_value || b.m_value); }
    cbool operator-(const cbool &b) const { return cbool(int(m_value) - int(b.m_value)); }
    cbool operator*(const cbool &b) const { return cbool(m_value && b.m_value); }

    // ASSIGNMENT OPERATORS
    cbool &operator=(const cbool &b) { if (this != &b) m_value = b.m_value; return *this; }
    cbool &operator+=(const cbool &b) { m_value += b.m_value; return *this; }
    cbool &operator-=(const cbool &b) { m_value -= b.m_value; return *this; }
    cbool &operator*=(const cbool &b) { m_value *= b.m_value; return *this; }

    // STREAM OPERATORS
    friend std::ostream &operator<<(std::ostream &os, const cbool &b) { return os << +b.m_value; }
    friend std::istream &operator>>(std::istream &is, cbool &b) { return is >> b.m_value; }

    // CONVERSION OPERATORS
    operator bool() const { return m_value; }
};

#endif // CBOOL_HPP
