/*
 * SubtleCreek.cpp
 *
 *  Created on: Dec 5, 2015
 *      Author: pavel
 */

#include <iostream>
#include <functional>
#include <unordered_map>

using namespace std;

class Value {
public:
    Value(int value = 0) :
            value(value) {
    }

    friend ostream& operator<<(ostream&, const Value&);

private:
    int value = 0;
};

// http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
class Key {
public:
    Key(const string& name = { }, const string& lastName = { }, const string& prof = { }) :
            _name(name), _lastName(lastName), _prof(prof) {
    }

    friend bool operator==(const Key&, const Key&);
    friend ostream& operator<<(ostream&, const Key&);

    const string& getLastName() const;
    void setLastName(const string& lastName);

    const string& getName() const;
    void setName(const string& name);

    const string& getProf() const;
    void setProf(const string& prof);

private:
    string _name;
    string _lastName;
    string _prof;
};

namespace std {
template<>
struct hash<Key> {
    std::size_t operator()(const Key& k) const {
        return hash<string>()(k.getName()) ^ hash<string>()(k.getLastName()) ^ hash<string>()(k.getProf());
    }
};
}

int main(int argc, char **argv) {
    try {
        cout << "Subtle Creek" << endl;

        unordered_map<string, Value> m1 { { "foo", { 42 } }, { "bar", { 43 } } };

        for (auto i : m1)
            cout << i.first << ", " << i.second << endl;

        unordered_map<Key, Value> m2 { { { "pasha", "shnaider", "programmer" }, { 42 } }, //
                { { "foo", "bar", "quz" }, { 43 } } //
        };

        for (auto i : m2)
            cout << i.first << ", " << i.second << endl;

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}

ostream& operator<<(ostream& out, const Value& r) {
    return out << "[Value: " << r.value << "]";
}

bool operator==(const Key& l, const Key& r) {
    return l._name == r._name && l._lastName == r._lastName && l._prof == r._prof;
}

ostream& operator<<(ostream& out, const Key& r) {
    return out << "[Key: " << r._name << ", " << r._lastName << ", " << r._prof << "]";
}

const string& Key::getLastName() const {
    return _lastName;
}

void Key::setLastName(const string& lastName) {
    _lastName = lastName;
}

const string& Key::getName() const {
    return _name;
}

void Key::setName(const string& name) {
    _name = name;
}

const string& Key::getProf() const {
    return _prof;
}

void Key::setProf(const string& prof) {
    _prof = prof;
}
