	#define PERL_NO_GET_CONTEXT
	#include <stdlib.h>
	#include "EXTERN.h"
	#include "perl.h"
	#include "XSUB.h"
	MODULE="MyUtils::NullXS"	PACKAGE="MyUtils::NullXS"

	void*
	myperlxs__null()
		CODE:
			RETVAL = NULL;

	void
	myperlxs__free(input)
			void* input
		CODE:
			free(input);
