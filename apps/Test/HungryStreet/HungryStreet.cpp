/*
 * HungryStreet.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: pavel
 */

#include <iostream>
#include <vector>

using namespace std;

class OutBuffer: public std::streambuf {
public:
    OutBuffer() :
        _buffer(100) {
        setp(_buffer.data(), _buffer.data() + _buffer.size());
    }
    virtual ~OutBuffer() {
    }

    /**
     *  @brief  Consumes data from the buffer; writes to the
     *          controlled sequence.
     *  @param  __c  An additional character to consume.
     *  @return  eof() to indicate failure, something else (usually
     *           @a __c, or not_eof())
     *
     *  Informally, this function is called when the output buffer
     *  is full (or does not exist, as buffering need not actually
     *  be done).  If a buffer exists, it is @a consumed, with
     *  <em>some effect</em> on the controlled sequence.
     *  (Typically, the buffer is written out to the sequence
     *  verbatim.)  In either case, the character @a c is also
     *  written out, if @a __c is not @c eof().
     *
     *  For a formal definition of this function, see a good text
     *  such as Langer & Kreft, or [27.5.2.4.5]/3-7.
     *
     *  A functioning output streambuf can be created by overriding only
     *  this function (no buffer area will be used).
     *
     *  @note  Base class version does nothing, returns eof().
     */
    virtual int_type overflow(int_type c = traits_type::eof()) {
        cout << __PRETTY_FUNCTION__ << static_cast<void*>(pbase()) << ", " << static_cast<void*>(pptr()) << endl;
        cout << __PRETTY_FUNCTION__ << (pptr() - pbase()) << endl;

        size_t pos = _buffer.size();
        _buffer.resize(_buffer.size() * 2);
        setp(_buffer.data(), _buffer.data() + _buffer.size());
        pbump(pos);
        *pptr() = c;
        pbump(1);

        return traits_type::not_eof(c);
    }

    std::vector<char> _buffer;
};

int main(int argc, char **argv) {
    try {
        cout << "HungryStreet" << endl;

        OutBuffer ob;
        ostream out{&ob};

        string s = R"(
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin posuere consectetur risus, eu blandit sapien maximus nec. 
Proin a urna sagittis, convallis est vel, consectetur mauris. Aliquam ullamcorper ac purus et fermentum. 
Suspendisse potenti. Donec accumsan consectetur ex a convallis. Lorem ipsum dolor sit amet, consectetur adipiscing elit. 
Nunc in tellus nibh. Etiam varius sed ex sed feugiat. Aliquam sed ante id neque dictum ultricies. 
Suspendisse lobortis et mi nec commodo. Sed at viverra velit. Morbi elementum mollis dictum.
)";
        out << s;

        cout << ob._buffer.size() << endl;
        cout << s << endl;
        cout << ob._buffer.data() << endl;

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}

