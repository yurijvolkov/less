int* build_prefix_function(char* s, int s_len){
    int* p_function;
    int i;
    int border;

    p_function = (int*)malloc(s_len * sizeof(int));

    memset(p_function, 0, s_len);
    border = 0;

    for(i = 1; i < s_len; i++) {
        while(border > 0 && s[i] != s[border])
            border = p_function[border - 1];
        if(s[i] == s[border])
            border++;
        else
            border = 0;
        p_function[i] = border;
    }

    return p_function;
}

int pattern_match(char *s, int s_len, char *_pattern, int p_len, int* result) {
    int* p_function;
    char* pattern;
    int i;
    int count;

    pattern = (char*)calloc( (p_len + s_len + 1) , 1 );
    memcpy(pattern, _pattern, p_len);
    //pattern = realloc(pattern, p_len + s_len + 1);
    pattern[p_len] = '\0';
    for(i = 0; i < s_len; i++) 
        pattern[p_len + i + 1] = s[i]; 

    p_function = build_prefix_function(pattern, p_len + s_len  + 1);
    count = 0;
    for(i = p_len; i < p_len + s_len + 1; i++)
        if(p_function[i] >= p_len)
            result[count++] = i - 2*p_len;           // TODO : make yield return
    return count;
}