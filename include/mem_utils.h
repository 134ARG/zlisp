//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_MEM_UTILS_H
#define ZLISP_MEM_UTILS_H

#define CLEANUP_FREE          __attribute__((__cleanup__(freep)))
#define CLEANUP(CLEANUP_FUNC) __attribute__((__cleanup__(CLEANUP_FUNC)))

#define TAKE_PTR(PTR)                                                  \
    __extension__({                                                    \
        __typeof__(PTR) PTR_ = (PTR);                                  \
        (PTR)                = NULL;                                   \
        PTR_;                                                          \
    })

#endif //ZLISP_MEM_UTILS_H
