//
//  systemcall.h
//  SystemProgramming_Rent
//
//  Created by 고상원 on 2019/10/27.
//  Copyright © 2019 고상원. All rights reserved.
//

#ifndef systemcall_h
#define systemcall_h

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void Init(void);
void InitDirectory(void);
void InitFile(void);
void InitData(void);

#endif /* systemcall_h */
