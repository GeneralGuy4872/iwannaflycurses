	#define PERL_NO_GET_CONTEXT
	#include <stdlib.h>
	#include "EXTERN.h"
	#include "perl.h"
	#include "XSUB.h"
	extern struct classtyp;
	MODULE="IWannaFly::Types::Struct::classtype'xs"	PACKAGE="IWannaFly::Types::Struct::classtype'xs"

	void*
	iwfperl_malloc_struct_classtyp()
		CODE:
			RETVAL = malloc(sizeof(struct classtyp));
		OUTPUT:
			RETVAL

	void*
	iwfperl_calloc_struct_classtyp()
		CODE:
			RETVAL = calloc(1,sizeof(struct classtyp));
		OUTPUT:
			RETVAL

	HV*
	iwfperl_new_struct_classtyp()
		CODE:
			RETVAL = newHV();
			hv_store(RETVAL,"Ptr",3,newSViv(NULL),0);
			hv_store(RETVAL,"role",4,newSV(0),0);
			hv_store(RETVAL,"class",5,newSV(0),0);
			hv_store(RETVAL,"align",5,newSV(0),0);
			hv_store(RETVAL,"charismatic",11,newSV(0),0);
			hv_store(RETVAL,"scorned",7,newSV(0),0);
		OUTPUT:
			RETVAL

	HV*
	iwfperl_fetch_struct_classtyp(ptr)
			struct classtyp* ptr;
		CODE:
			RETVAL = newHV();
			hv_store(RETVAL,"Ptr",3,newSViv(ptr),0);
			hv_store(RETVAL,"role",4,newSViv(ptr->role),0);
			hv_store(RETVAL,"class",5,newSViv(ptr->class),0);
			hv_store(RETVAL,"align",5,newSViv(ptr->align),0);
			hv_store(RETVAL,"charismatic",11,newSViv(ptr->charismatic),0);
			hv_store(RETVAL,"scorned",7,newSViv(ptr->scorned),0);
		OUTPUT:
			RETVAL

	void
	iwfperl_sync_struct_classtype(input)
			HV* input
		CODE:
			SV** = hv_fetch(input,"Ptr",3,0);
			if (ptr != NULL) {
				if (hv_fetch(foo,"role",4,0) != NULL) {
					((struct classtyp*)SvIV(*ptr))->role = SvIV(*hv_fetch(foo,"role",4,0));
					}
				if (hv_fetch(foo,"role",4,0) != NULL) {
					((struct classtyp*)SvIV(*ptr))->class = SvIV(*hv_fetch(foo,"class",5,0));
					}
				if (hv_fetch(foo,"align",5,0) != NULL) {
					((struct classtyp*)SvIV(*ptr))->align = SvIV(*hv_fetch(foo,"align",5,0));
					}
				if (hv_fetch(foo,"charismatic",11,0) != NULL) {
					((struct classtyp*)SvIV(*ptr))->charismatic = SvIV(*hv_fetch(foo,"charismatic",11,0));
					}
				if (hv_fetch(foo,"scorned",7,0) != NULL) {
					((struct classtyp*)SvIV(*ptr))->scorned = SvIV(*hv_fetch(foo,"scorned",7,0));
					}
