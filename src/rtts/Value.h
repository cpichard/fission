#ifndef VALUE_H
#define VALUE_H

namespace fission {

/// A Value has a type and a memory space
/// It should know how to allocate and destroy itself
/// We must be able to compare and clone a value
/// In the future, it will have a dedicated allocator
/// First test implementation is similar to boost::any, but using
/// our own rtts rather than c++ rtti
/// The value might have the ability to load and save
class Value {

public:
    Value()
    : m_data(NULL)
    {}

    template<typename ValueType>
    Value(const ValueType &value)
    : m_data(new holder<ValueType>(value))
    {}

    Value(const Value & other)
    //: m_data(other.m_data ? other.m_data.clone() : NULL)
    : m_data(NULL)
    {}

    ~Value() {
        delete m_data;
    }

    class placeholder
    {
    public:
        virtual ~placeholder(){}
        //const std::type_info &type const=0;
        //virtual placeholder *clone() const=0;
    };

    template<typename ValueType>
    class holder : public placeholder
    {
    public:
        holder(const ValueType & value)
        : held(value){}
/*
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }

        virtual placeholder *clone() const
        {
            return new holder(*this);
        }
*/
        ValueType held;
    };
private:
    template<typename ValueType>
    friend ValueType * value_cast(Value *);
    placeholder *m_data;
};

};

#endif//VALUE_H
