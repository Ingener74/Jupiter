/*
 * JupiterError.h
 *
 *  Created on: Aug 7, 2014
 *      Author: pavel
 */

#ifndef JUPITERERROR_H_
#define JUPITERERROR_H_

#include <Jupiter/Common.h>

namespace jupiter
{

#define THROW_JUPITER_ERROR(message) \
    throw JupiterError(std::string(__FILE__) + ":" std::string(__LINE__) + ": " + \
            std::string(__PRETTY_FUNCTION__) + ": " + message)

class JupiterError: public std::runtime_error
{
public:
	JupiterError(const std::string& message = "Jupiter error") :
			std::runtime_error(message + backtrace())
	{
	}

	virtual ~JupiterError() throw ()
	{
	}

	static std::string backtrace()
	{
#ifndef ANDROID
		using namespace std;

		const int buffer_size = 1000;
		void *buffer[ buffer_size ];
		int n = ::backtrace(buffer, buffer_size);

		char** strings = backtrace_symbols(buffer, n);
		if ( strings == nullptr ) return string("i can't print stack trace");

		stringstream res;
		res << endl << "Call stack" << endl;
		for ( int i = 2; i < n; ++i )
		{
			res << i << ": " << strings[ i ] << endl;
		}
		free(strings);
		return res.str();
#endif
	}
};

}  // namespace jupiter

#endif /* JUPITERERROR_H_ */
