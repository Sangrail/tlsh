// tlsh.h - TrendLSH  Hash Algorithm

/*
 * Copyright 2013 Trend Micro Incorporated
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _TLSH_H
#define _TLSH_H

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus

#include "tlsh_impl.h"

class TLSH_API Tlsh{

public:
    Tlsh();

    /* allow the user to add data in multiple iterations */
    void update(const unsigned char* data, unsigned int len);

    /* to signal the class there is no more data to be added */
    void final(const unsigned char* data = NULL, unsigned int len = 0);

    /* to get the hex-encoded hash code */
    const char* getHash();

    /* to get the hex-encoded hash code without allocating buffer in TlshImpl - bufSize should be TLSH_STRING_BUFFER_LEN */
    const char* getHash(char *buffer, unsigned int bufSize);  

    /* to bring to object back to the initial state */
    void reset();
    
    /* calculate difference */
    /* The len_diff parameter specifies if the file length is to be included in the difference calculation (len_diff=true) or if it */
    /* is to be excluded (len_diff=false).  In general, the length should be considered in the difference calculation, but there */
    /* could be applications where a part of the adversarial activity might be to add a lot of content.  For example to add 1 million */
    /* zero bytes at the end of a file.  In that case, the caller would want to exclude the length from the calculation. */
    int totalDiff(Tlsh *, bool len_diff=true);
    
    /* validate TrendLSH string and reset the hash according to it */
    int fromTlshStr(const char* str);

    /* Return the version information used to build this library */
    static const char *version();

    // operators
    bool operator==(const Tlsh& other) const;
    bool operator!=(const Tlsh& other) const;

    ~Tlsh();

private:
    /* impl changed from pointer to instance, so save 8 bytes (sizeof TlshImpl*) in the size of Tlsh/TlshImpl */
    TlshImpl impl;
};
#endif

#endif

