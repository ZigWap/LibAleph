/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

/* TODO: consider using KMP alg */
static size_t a_find_internal(const char *str, const char *substr, size_t size, size_t subsize)
{
    const char *end = str + size;
    size_t pos = 0;
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);

    while (*str && (size_t)(end-str) >= subsize)
    {
        if (!memcmp(str, substr, subsize))
            return pos;
        
        pos++;
        str += a_size_chr_cstr(str);
    }

    return A_EOS;    
}
static size_t a_find_offset_internal(const char *str, const char *substr, size_t size, size_t subsize, size_t offset)
{
    const char *at = str + offset, *end = str + size;
    assert(str != NULL && substr != NULL);
    assert(at <= end);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    while ((size_t)(end-at) >= subsize)
    {
        if (!memcmp(at, substr, subsize))
            return (at-str);
        
        at += a_size_chr_cstr(at);
    }
    
    return A_EOS;  
}
size_t a_find(a_cstr str, a_cstr substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_internal(str, substr, a_size(str), a_size(substr));  
}
size_t a_find_cstr(a_cstr str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_internal(str, substr, a_size(str), strlen(substr));  
}
size_t a_find_cstr_cstr(const char *str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_internal(str, substr, strlen(str), strlen(substr)); 
}
size_t a_find_cp(a_cstr str, a_cp codepoint)
{
    char chr[7];
    int size;
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, A_EOS);
    a_to_utf8_size(codepoint, chr, &size);
    
    return a_find_internal(str, chr, a_size(str), size);  
}
size_t a_find_from(a_cstr str, a_cstr substr, size_t index)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_offset_internal(str, substr, a_size(str), a_size(substr),
            a_internal_index_to_offset(str, index)); 
}
size_t a_find_from_cstr(a_cstr str, const char *substr, size_t index)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_offset_internal(str, substr, a_size(str), strlen(substr), 
            a_internal_index_to_offset(str, index)); 
}
size_t a_find_offset(a_cstr str, a_cstr substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_offset_internal(str, substr, a_size(str), a_size(substr), 0);  
}
size_t a_find_offset_cstr(a_cstr str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_offset_internal(str, substr, a_size(str), strlen(substr), 0);  
}
size_t a_find_offset_from(a_cstr str, a_cstr substr, size_t offset)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_offset_internal(str, substr, a_size(str), a_size(substr), offset); 
}
size_t a_find_offset_from_cstr(a_cstr str, const char *substr, size_t offset)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_offset_internal(str, substr, a_size(str), strlen(substr), offset);
}

/********************************************************************/

static size_t a_ifind_internal(const char *str, const char *substr)
{
    size_t pos = 0;
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);

    while (*str)
    {
        if (!a_icmp_min_cstr_cstr(str, substr))
            return pos;
        
        pos++;
        str += a_size_chr_cstr(str);
    }

    return A_EOS;    
}
static size_t a_ifind_offset_internal(const char *str, const char *substr, size_t size, size_t subsize, size_t offset)
{
    const char *at = str + offset, *end = str + size;
    assert(str != NULL && substr != NULL);
    assert(at <= end);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    while ((size_t)(end-at) >= subsize)
    {
        if (!a_icmp_min_cstr_cstr(at, substr))
            return (at-str);
        
        at += a_size_chr_cstr(at);
    }
    
    return A_EOS;  
}
static size_t a_ifind_offset_len_internal(const char *str, const char *substr, size_t size, size_t subsize, size_t offset, size_t *match_len)
{
    const char *at = str + offset, *end = str + size;
    assert(str != NULL && substr != NULL);
    assert(at <= end);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    while ((size_t)(end-at) >= subsize)
    {
        if (!a_icmp_min_cstr_cstr_len(at, substr, match_len))
            return (at-str);
        
        at += a_size_chr_cstr(at);
    }
    
    return A_EOS;  
}
size_t a_ifind(a_cstr str, a_cstr substr)
{
    return a_ifind_internal(str, substr);
}
size_t a_ifind_cstr(a_cstr str, const char *substr)
{
    return a_ifind_internal(str, substr);
}
size_t a_ifind_cstr_cstr(const char *str, const char *substr)
{
    return a_ifind_internal(str, substr);
}
size_t a_ifind_from(a_cstr str, a_cstr substr, size_t index)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_ifind_offset_internal(str, substr, a_size(str), a_size(substr),
            a_internal_index_to_offset(str, index)); 
}
size_t a_ifind_from_cstr(a_cstr str, const char *substr, size_t index)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_find_offset_internal(str, substr, a_size(str), strlen(substr), 
            a_internal_index_to_offset(str, index)); 
}
size_t a_ifind_from_cp(a_cstr str, a_cp codepoint, size_t index)
{
    char b[A_MAX_CHAR];
    int size;
    a_to_utf8_size(codepoint, b, &size);
    
    return a_find_offset_internal(str, b, a_size(str), size, 
            a_internal_index_to_offset(str, index)); 
}
size_t a_ifind_offset_from(a_cstr str, a_cstr substr, size_t offset)
{
    assert(str != NULL && substr != NULL);
    assert(offset <= a_size(str));
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_ifind_offset_internal(str, substr, a_size(str), a_size(substr), offset); 
}
size_t a_ifind_from_len(a_cstr str, a_cstr substr, size_t index, size_t *match_len)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_ifind_offset_len_internal(str, substr, a_size(str), a_size(substr),
            a_internal_index_to_offset(str, index), match_len); 
}
size_t a_ifind_from_len_cstr(a_cstr str, const char *substr, size_t index, size_t *match_len)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_ifind_offset_len_internal(str, substr, a_size(str), strlen(substr),
            a_internal_index_to_offset(str, index), match_len); 
}
size_t a_ifind_offset_from_cstr(a_cstr str, const char *substr, size_t offset)
{
    assert(str != NULL && substr != NULL);
    assert(offset <= a_size(str));
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_ifind_offset_internal(str, substr, a_size(str), strlen(substr), offset); 
}

size_t a_ifind_offset_from_len(a_cstr str, a_cstr substr, size_t offset, size_t *match_len)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_ifind_offset_len_internal(str, substr, a_size(str), a_size(substr), offset, match_len); 
}
size_t a_ifind_offset_from_len_cstr(a_cstr str, const char *substr, size_t offset, size_t *match_len)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, A_EOS);
    
    return a_ifind_offset_len_internal(str, substr, a_size(str), strlen(substr), offset, match_len); 
}