/*
 * sch_port.h
 *
 *  Created on: Nov 11, 2026
 *      Author: Admin
 */
#ifndef INC_SCH_PORT_H_
#define INC_SCH_PORT_H_
#include <stdint.h>

#ifdef SCH_HOST_TEST
static inline uint32_t SCH_Lock(void)          { return 0u; }
static inline void     SCH_Unlock(uint32_t m)  { (void)m; }
#else
#include "main.h"
static inline uint32_t SCH_Lock(void) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    return primask;
}
static inline void SCH_Unlock(uint32_t primask) {
    __set_PRIMASK(primask);
}
#endif

#endif /* INC_SCH_PORT_H_ */
