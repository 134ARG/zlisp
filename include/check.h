//
// Created by fort64 on 7/9/2021.
//

#ifndef ZLISP_CHECK_H
#define ZLISP_CHECK_H

#define CHECK_OK(status)                                                        \
do {                                                                            \
    if (status != OK) {                                                         \
        LOG_ERROR("Operation Failed.");                                           \
    }                                                                           \
} while(0)

#endif //ZLISP_CHECK_H
