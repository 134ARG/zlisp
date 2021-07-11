//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_STATUS_H
#define ZLISP_STATUS_H

enum status {
	OK,
	ERR_NO_MEM,
	ERR_END_OF_FILE = -1,
	ERR_FILE_CURSOR,
	ERR_CDR_IS_SET,
};

#endif //ZLISP_STATUS_H
