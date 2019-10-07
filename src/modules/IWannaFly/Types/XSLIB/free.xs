	#define PERL_NO_GET_CONTEXT
	#include <stdlib.h>
	#include "EXTERN.h"
	#include "perl.h"
	#include "XSUB.h"
	MODULE="IWannaFly::Types::free'xs"	PACKAGE="IWannaFly::Types::free'xs"

	void
	iwfperl_free(input)
			void* input
		CODE:
			free(input);
