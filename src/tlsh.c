#include "tlsh_impl.h"
#include <stdlib.h>
#include <tlshc/tlsh.h>

Tlsh* tlsh_new()
{
    Tlsh* tlsh = malloc(sizeof(Tlsh));
    if (!tlsh)
        return NULL;

    tlsh->impl = tlsh_impl_new();
    if (!tlsh->impl) {
        free(tlsh);
        return NULL;
    }

    return tlsh;
}

void tlsh_free(Tlsh* tlsh)
{
    if (tlsh) {
        tlsh_impl_free(tlsh->impl);
        free(tlsh);
    }
}

int tlsh_update(Tlsh* tlsh, const unsigned char* data, unsigned int len)
{
    int tlsh_option = 0;
    if (tlsh->impl) {
        int res = tlsh_impl_update(tlsh->impl, data, len, tlsh_option);
        if (res) {
            return 1;
        }
    }

    return 0;
}

void tlsh_reset(Tlsh* tlsh)
{
    if (tlsh->impl)
        tlsh_impl_reset(tlsh->impl);
}

int tlsh_final(Tlsh* tlsh, const unsigned char* data, unsigned int len, int tlsh_option)
{
    if (tlsh->impl) {
        if ((data != NULL) && (len > 0)) {
            int res = tlsh_impl_update(tlsh->impl, data, len, tlsh_option);
            if (res) {
                return 1;
            }
        }

        tlsh_impl_final(tlsh->impl, tlsh_option);
    }

    return 0;
}

const char* tlsh_get_hash(Tlsh* tlsh, bool showvers)
{
    if (tlsh->impl)
        return tlsh_impl_hash(tlsh->impl, showvers);
    else
        return "";
}

// Added more functions. There's no (tlsh->impl) check
// int tlsh_impl_total_diff(TlshImpl *tlsh, TlshImpl *other, bool len_diff);
int tlsh_total_diff(Tlsh* tlsh, Tlsh *other, bool len_diff)
{
    return tlsh_impl_total_diff(tlsh->impl, other->impl, len_diff);
}

// int tlsh_impl_from_tlsh_str(TlshImpl *tlsh, const char *str);
int tlsh_from_tlsh_str(Tlsh* tlsh, const char *str)
{
    return tlsh_impl_from_tlsh_str(tlsh->impl, str);
}
