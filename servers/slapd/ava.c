/* ava.c - routines for dealing with attribute value assertions */

#include "portable.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "slap.h"

int
get_ava(
    BerElement	*ber,
    Ava		*ava
)
{
	if ( ber_scanf( ber, "{ao}", &ava->ava_type, &ava->ava_value )
	    == LBER_ERROR ) {
		Debug( LDAP_DEBUG_ANY, "  get_ava ber_scanf\n", 0, 0, 0 );
		return( LDAP_PROTOCOL_ERROR );
	}
	attr_normalize( ava->ava_type );
	value_normalize( ava->ava_value.bv_val, attr_syntax( ava->ava_type ) );

	return( 0 );
}

void
ava_free(
    Ava	*ava,
    int	freeit
)
{
	free( (char *) ava->ava_type );
	free( (char *) ava->ava_value.bv_val );
	if ( freeit ) {
		free( (char *) ava );
	}
}

