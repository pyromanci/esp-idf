/*
 * SPDX-FileCopyrightText: 2015-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ulp_riscv/ulp_riscv.h"
#include "ulp_riscv/ulp_riscv_utils.h"

void ulp_riscv_rescue_from_monitor(void)
{
    /* Rescue RISCV from monitor state. */
    CLEAR_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_DONE | RTC_CNTL_COCPU_SHUT_RESET_EN);
}

void ulp_riscv_wakeup_main_processor(void)
{
    SET_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_SW_CPU_INT);
}

void ulp_riscv_halt(void)
{
    /* Setting the delay time after RISCV recv `DONE` signal, Ensure that action `RESET` can be executed in time. */
    REG_SET_FIELD(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT_2_CLK_DIS, 0x3F);

    /* suspends the ulp operation*/
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_DONE);

    /* Resets the processor */
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT_RESET_EN);

    while(1);
}

void ulp_riscv_delay_cycles(uint32_t cycles)
{
    uint32_t start = ULP_RISCV_GET_CCOUNT();

    while ((ULP_RISCV_GET_CCOUNT() - start) < cycles) {
        /* Wait */
    }
}

void ulp_riscv_timer_stop(void)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
}

void ulp_riscv_timer_resume(void)
{
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
}
