	#define PERL_NO_GET_CONTEXT
	#include <stdlib.h>
	#include "EXTERN.h"
	#include "perl.h"
	#include "XSUB.h"
	MODULE="IWannaFly::DivXS"	PACKAGE="IWannaFly::DivXS"

	HV*
	iwf_perlxs_div(numer,denom)
			int numer
			int denom
		CODE:
			div_t tmp = div(numer,denom);
			RETVAL = newHV();
			hv_store(RETVAL,"quot",4,newSViv(tmp.quot),0);
			hv_store(RETVAL,"rem",4,newSViv(tmp.rem),0);
