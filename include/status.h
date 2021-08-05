//
// Created by zry on 2021/7/8.
//

#ifndef ZLISP_STATUS_H
#define ZLISP_STATUS_H

enum status {
	INFO_END_OF_FILE = -1,
	OK,
	ERR_NO_MEM,
	INFO_OBJ_NOT_FOUND,
	ERR_FILE_CURSOR,
	ERR_CDR_IS_SET,
};

#endif  // ZLISP_STATUS_H
